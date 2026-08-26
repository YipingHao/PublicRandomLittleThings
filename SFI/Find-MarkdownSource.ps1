[CmdletBinding()]
param(
    [string]$ClueText = '置换不变量描述符是一种向神经网络势能面中引入置换不变性的技术',
    [string[]]$Roots,
    [switch]$SkipLiveSearch,
    [string]$OutputPath = (Join-Path $PSScriptRoot 'markdown-source-search-results.csv')
)

Set-StrictMode -Version Latest
$ErrorActionPreference = 'Stop'

$rg = Get-Command rg -ErrorAction Stop
$results = [System.Collections.Generic.List[object]]::new()
$seen = [System.Collections.Generic.HashSet[string]]::new(
    [System.StringComparer]::OrdinalIgnoreCase
)

if (-not $Roots -or $Roots.Count -eq 0) {
    $Roots = @(
        Get-PSDrive -PSProvider FileSystem |
            Where-Object {
                $_.Root -and
                $_.Root -eq [System.IO.Path]::GetPathRoot($_.Root) -and
                (Test-Path -LiteralPath $_.Root -PathType Container)
            } |
            Select-Object -ExpandProperty Root -Unique
    )
}

function Add-LiveResult {
    param([string]$Path, [string]$Reason)
    if (-not (Test-Path -LiteralPath $Path -PathType Leaf) -or -not $seen.Add($Path)) {
        return
    }
    $item = Get-Item -LiteralPath $Path
    $results.Add([pscustomobject]@{
        Kind             = 'LiveFile'
        MatchReason      = $Reason
        FullName         = $item.FullName
        OriginalResource = ''
        SnapshotTime     = $null
        LengthBytes      = $item.Length
        LastWriteTime    = $item.LastWriteTime
    })
}

if (-not $SkipLiveSearch) {
    $namePatterns = @(
        'SFI.md',
        '*Separating*Fundamental*Invariant*.md',
        '*Fundamental*Invariant*PES*.md'
    )

    foreach ($root in $Roots) {
        Write-Host "Searching live Markdown under $root ..."
        foreach ($pattern in $namePatterns) {
            Get-ChildItem -LiteralPath $root -Filter $pattern -File -Recurse -Force `
                -ErrorAction SilentlyContinue |
                ForEach-Object { Add-LiveResult -Path $_.FullName -Reason 'FileName' }
        }

        # Search content rather than relying on a possibly changed filename.
        $matches = & $rg.Source -l -F --hidden --no-messages -g '*.md' -- $ClueText $root
        foreach ($match in @($matches)) {
            Add-LiveResult -Path $match -Reason 'ContentClue'
        }
    }
}

$historyRoots = @(
    Join-Path $env:APPDATA 'Code\User\History'
    Join-Path $env:APPDATA 'Cursor\User\History'
) | Where-Object { Test-Path -LiteralPath $_ -PathType Container }

foreach ($historyRoot in $historyRoots) {
    Write-Host "Searching editor history under $historyRoot ..."
    $matches = & $rg.Source -l -F --hidden --no-messages -- $ClueText $historyRoot
    foreach ($match in @($matches)) {
        if (-not $seen.Add($match)) {
            continue
        }

        $item = Get-Item -LiteralPath $match
        $entriesPath = Join-Path $item.DirectoryName 'entries.json'
        $resource = ''
        $snapshotTime = $item.LastWriteTime

        if (Test-Path -LiteralPath $entriesPath -PathType Leaf) {
            try {
                $history = Get-Content -LiteralPath $entriesPath -Raw | ConvertFrom-Json
                $resource = [uri]::UnescapeDataString([string]$history.resource)
                $entry = $history.entries | Where-Object { $_.id -eq $item.Name } | Select-Object -First 1
                if ($entry) {
                    $snapshotTime = [DateTimeOffset]::FromUnixTimeMilliseconds(
                        [int64]$entry.timestamp
                    ).LocalDateTime
                }
            }
            catch {
                Write-Warning "Could not parse history metadata '$entriesPath': $($_.Exception.Message)"
            }
        }

        $results.Add([pscustomobject]@{
            Kind             = 'EditorHistory'
            MatchReason      = 'ContentClue'
            FullName         = $item.FullName
            OriginalResource = $resource
            SnapshotTime     = $snapshotTime
            LengthBytes      = $item.Length
            LastWriteTime    = $item.LastWriteTime
        })
    }
}

$ordered = @($results | Sort-Object Kind, SnapshotTime, FullName)
$ordered | Export-Csv -LiteralPath $OutputPath -NoTypeInformation -Encoding UTF8

Write-Host ''
Write-Host "Found $($ordered.Count) candidate(s)."
Write-Host "Report: $OutputPath"
$ordered | Format-Table Kind, MatchReason, FullName, OriginalResource, SnapshotTime -AutoSize -Wrap

