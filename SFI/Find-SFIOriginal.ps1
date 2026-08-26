[CmdletBinding()]
param(
    [string]$ReferencePath = (Join-Path $PSScriptRoot 'SFI.md'),
    [string[]]$Roots,
    [switch]$IncludeSimilarNames,
    [string]$OutputPath = (Join-Path $PSScriptRoot 'SFI-search-results.csv')
)

Set-StrictMode -Version Latest
$ErrorActionPreference = 'Stop'

if (-not (Test-Path -LiteralPath $ReferencePath -PathType Leaf)) {
    throw "Reference file not found: $ReferencePath"
}

$referenceFile = Get-Item -LiteralPath $ReferencePath
$referenceFullPath = $referenceFile.FullName
$referenceHash = (Get-FileHash -LiteralPath $referenceFullPath -Algorithm SHA256).Hash

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

$patterns = @('SFI.md')
if ($IncludeSimilarNames) {
    $patterns = @('*SFI*.md', '*SFI*.md.*', '*SFI*.bak')
}

Write-Host "Reference: $referenceFullPath"
Write-Host "SHA-256:   $referenceHash"
Write-Host "Roots:     $($Roots -join ', ')"
Write-Host "Patterns:  $($patterns -join ', ')"
Write-Host ''

$seen = [System.Collections.Generic.HashSet[string]]::new(
    [System.StringComparer]::OrdinalIgnoreCase
)
$matches = [System.Collections.Generic.List[object]]::new()

foreach ($root in $Roots) {
    if (-not (Test-Path -LiteralPath $root -PathType Container)) {
        Write-Warning "Skipping missing or inaccessible root: $root"
        continue
    }

    Write-Host "Searching $root ..."
    foreach ($pattern in $patterns) {
        # -Force includes hidden items. Access-denied and transient filesystem
        # errors are ignored so one protected folder cannot stop the search.
        $files = Get-ChildItem -LiteralPath $root -File -Filter $pattern -Recurse -Force `
            -ErrorAction SilentlyContinue

        foreach ($file in $files) {
            if (-not $seen.Add($file.FullName)) {
                continue
            }

            try {
                $hash = (Get-FileHash -LiteralPath $file.FullName -Algorithm SHA256).Hash
                $samePath = $file.FullName.Equals(
                    $referenceFullPath,
                    [System.StringComparison]::OrdinalIgnoreCase
                )
                $sameContent = $hash -eq $referenceHash

                $preview = @(
                    Get-Content -LiteralPath $file.FullName -TotalCount 20 -ErrorAction Stop |
                        Where-Object { -not [string]::IsNullOrWhiteSpace($_) } |
                        Select-Object -First 3
                ) -join ' | '

                $matches.Add([pscustomobject]@{
                    IsDifferentContent = -not $sameContent
                    IsReferencePath     = $samePath
                    FullName            = $file.FullName
                    LengthBytes         = $file.Length
                    CreationTime        = $file.CreationTime
                    LastWriteTime       = $file.LastWriteTime
                    SHA256              = $hash
                    Preview             = $preview
                })
            }
            catch {
                Write-Warning "Found but could not inspect '$($file.FullName)': $($_.Exception.Message)"
            }
        }
    }
}

$ordered = @(
    $matches |
        Sort-Object @{ Expression = 'IsDifferentContent'; Descending = $true },
                    @{ Expression = 'LastWriteTime'; Descending = $false }
)

$ordered | Export-Csv -LiteralPath $OutputPath -NoTypeInformation -Encoding UTF8

Write-Host ''
Write-Host "Found $($ordered.Count) candidate(s)."
Write-Host "Report: $OutputPath"

$different = @($ordered | Where-Object { $_.IsDifferentContent })
if ($different.Count -gt 0) {
    Write-Host ''
    Write-Host "Different-content candidate(s):" -ForegroundColor Green
    $different |
        Select-Object FullName, LengthBytes, CreationTime, LastWriteTime, SHA256, Preview |
        Format-List
}
else {
    Write-Host ''
    Write-Host 'No same-name file with different content was found.' -ForegroundColor Yellow
    if (-not $IncludeSimilarNames) {
        Write-Host 'Try again with -IncludeSimilarNames to look for backups or renamed variants.'
    }
}
