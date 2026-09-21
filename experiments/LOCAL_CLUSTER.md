# CMG_PIP 内网集群环境说明

> 本文件供本机开发者与 Agent 使用，独立存放在 `PublicRandomLittleThings/experiments/`，不属于
> CMG_PIP 主仓库。文件含内网地址和集群拓扑；向 GitHub 或其他远端推送前，必须确认目标仓库的
> 可见性与访问策略，也不要在公开日志中披露这些信息。硬件、磁盘余量和仓库提交均为
> **2026-09-21 的探测快照**。执行任务前通常最多只需按需同步仓库并检查目标节点的 `/share` 余量。

## 1. 基本原则

- Windows 用户为 `dicp`，集群账户为 `Hyper`。
- `c0` 是**登录节点和 SSH 跳板机**，不是计算节点。禁止在 `c0` 上编译大型目标、运行测试或启动长任务。
- 实际计算节点为 `C14-1` 至 `C14-11`。它们可从 `c0` 通过对应主机名访问。
- 各计算节点的 `/share` 是彼此独立的挂载/本地文件系统。一个节点上的 `/share/Hyper`、工作副本和
  测试输出**必然不会自动传播到其他节点**；需要在每个目标节点分别创建、同步或复制。
- 在计算节点上，用户项目统一放在 `/share/Hyper/git/`；需要时可安全执行
  `mkdir -p /share/Hyper/git`。
- 长任务只在明确选定的 C14 计算节点上运行。启动前通常只需安全同步仓库并确认 `/share` 有足够空间；
  CPU、内存和 GPU 硬件配置一般无需重复探测。

## 2. SSH 访问

Windows 使用系统 OpenSSH：

```powershell
ssh c0
```

本机 `C:\Users\dicp\.ssh\config` 当前包含：

- `C0` / `c0`：`10.159.200.26`，用户 `Hyper`；
- `C14-6`、`C14-7`、`C14-8`、`C14-9`：均以 `C0` 为 `ProxyJump`。

未写入本机 SSH 配置的节点可显式使用跳板：

```powershell
ssh -J c0 Hyper@C14-10
```

也可以先登录 `c0`，再从登录节点进入计算节点：

```bash
ssh C14-10
```

执行一次性远端检查时，可从 PowerShell 使用嵌套 SSH：

```powershell
ssh c0 'ssh C14-10 "hostname; pwd"'
```

不要使用 `StrictHostKeyChecking=no` 绕过主机身份校验。当前 `c0` 上访问 `C14-1` 时会报告已保存的
RSA 主机密钥发生变化（`/home/Hyper/.ssh/known_hosts` 第 46 行）。连接目前可以完成，但在管理员确认
新指纹前，不要自动删除或替换该记录。2026-09-21 探测到的新 RSA 指纹为：

```text
SHA256:hi6W5bg9VCDiivYdapeEiqRkkcyHNbKEe9Z4qVWJ3LY
```

## 3. 登录节点 c0

| 项目 | 快照 |
|---|---|
| SSH 别名 | `c0` / `C0` |
| 实际主机名 | `cluster` |
| 系统 | Rocky Linux 9.7 |
| CPU | 16 个逻辑 CPU |
| 内存 | 31 GiB |
| Home | `/home/Hyper` |
| 角色 | 登录、跳板、裸 Git 主仓库存储 |

未发现常见的 `sbatch`、`srun`、`qsub`、`bsub` 等调度器命令。即使没有调度器，也不得把测试直接放在
`c0` 上运行。

## 4. C14 计算节点硬件快照

硬件配置通常稳定，磁盘余量则可能变化。下表用于选择候选节点；实际运行前按需检查 `/share` 即可，
不要求重复查询 CPU、内存或 GPU。

| 节点 | 操作系统 | CPU | 内存 | GPU | `/share` 容量 | 当时可用 |
|---|---|---|---:|---|---:|---:|
| C14-1 | CentOS 7 | 8 核 Xeon E5-2609 2.40 GHz | 125 GiB | 1× Tesla P100 16 GiB | 504 GiB | 85 GiB |
| C14-2 | CentOS 7 | 16 核 Xeon E5-2650 2.00 GHz | 125 GiB | 1× Tesla V100 16 GiB | 496 GiB | 210 GiB |
| C14-3 | CentOS 7 | 24 核 Xeon Silver 4214 2.20 GHz | 125 GiB | 8× A100 PCIe 40 GiB | 839 GiB | 47 GiB |
| C14-4 | CentOS 7 | 56 核 Xeon Gold 6348 2.60 GHz | 1.0 TiB | 10× A100 PCIe 80 GiB | 3.5 TiB | 30 GiB |
| C14-5 | CentOS 7 | 64 核 Xeon Platinum 8375C 2.90 GHz | 1.0 TiB | 10× A100 PCIe 80 GiB | 3.5 TiB | 96 GiB |
| C14-6 | CentOS 7 | 64 核 Xeon Platinum 8375C 2.90 GHz | 1.0 TiB | 10× A100 PCIe 80 GiB | 3.5 TiB | 310 GiB |
| C14-7 | Rocky Linux 9.6 | 64 核 AMD EPYC 7502 | 251 GiB | 8× A100 SXM4 40 GiB | 720 GiB | 148 GiB |
| C14-8 | Rocky Linux 9.7 | 64 核 AMD EPYC 7502 | 251 GiB | 8× A100 SXM4 40 GiB | 720 GiB | 7.4 GiB |
| C14-9 | Rocky Linux 9.7 | 64 核 AMD EPYC 7502 | 251 GiB | 8× A100 SXM4 40 GiB | 720 GiB | 276 GiB |
| C14-10 | Rocky Linux 9.7 | 64 核 AMD EPYC 7502 | 251 GiB | 8× A100 SXM4 40 GiB | 720 GiB | 100 GiB |
| C14-11 | Rocky Linux 9.7 | 64 核 AMD EPYC 7502 | 251 GiB | 8× A100 SXM4 40 GiB | 720 GiB | 20 GiB |

2026-09-21 探测时，`C14-10` 几乎空载，适合 CMG_PIP 的 CPU 长测试；这不是永久分配，使用前必须再次
确认。`C14-8` 的 `/share` 当时接近满盘，不适合产生大量新日志。

所有节点均发现 `bash`、`g++`、`make` 和 `git`。Rocky Linux 节点上的 GCC 为 11.5.0。
所有节点的 `PATH` 中均未发现 `geng` 或 `nauty-geng`；运行 MinFill 10--14 边服务器验证前，需要在
用户目录准备 nauty `geng`，不能在 `c0` 上编译或运行验证。

## 5. Git 裸仓库与工作副本

`c0` 的 `/home/Hyper/git/` 是主裸仓库目录。当前相关仓库为：

```text
/home/Hyper/git/CMG_PIP.git
/home/Hyper/git/FIgenerator.git
```

两者的裸仓库 `HEAD` 均已指向 `refs/heads/main`。计算节点通过共享可见的 `/home/Hyper/git/*.git`
克隆，不需要访问公网：

```bash
mkdir -p /share/Hyper/git
git clone /home/Hyper/git/CMG_PIP.git /share/Hyper/git/CMG_PIP
git clone /home/Hyper/git/FIgenerator.git /share/Hyper/git/FIgenerator
```

各计算节点的标准工作副本位置为：

```text
/share/Hyper/git/CMG_PIP
/share/Hyper/git/FIgenerator
```

更新已有工作副本前必须先检查本地改动，并只允许快进：

```bash
cd /share/Hyper/git/CMG_PIP
git status --short
git pull --ff-only
```

`--ff-only` 是安全限制，不是强制覆盖选项：只有当前本地提交是远端新提交的直接祖先时，Git 才会把
分支指针向前移动；如果本地存在独立提交、分支已经分叉或需要自动合并，命令会直接失败，不会创建
merge commit，也不会执行 rebase。该命令仍会把干净工作树更新到新提交，所以必须先运行
`git status --short`。如果输出非空，应停止并报告，不得 reset、stash、clean 或覆盖用户内容。部分旧
CentOS 节点的 Git 不支持 `git -C`，自动化脚本应使用 `cd /share/Hyper/git/<repo>` 后再运行 Git 命令。

另有一个 CMG_PIP 裸仓库位于：

```text
/share/tmp/Hyper02/git/CMG_PIP.git
```

本地仓库将它配置为 `PublicServer`；日常计算节点同步仍优先使用 `/home/Hyper/git/CMG_PIP.git`。

## 6. 2026-09-21 同步状态

- `CMG_PIP`：C14-1 至 C14-11 均为 `main`，提交
  `f9c0069f5c272a1a94f8e4a886fb4b0425c75867`，当时工作树全部干净。
- `FIgenerator`：主仓库和所有节点均位于 `main`，提交
  `0818f0e33e38426885872d20fb4d6ae54f6aa2b9`。
- C14-1 至 C14-8、C14-10、C14-11 的 `FIgenerator` 工作树当时干净。
- C14-9 的 `FIgenerator` 已是最新提交，但有 12 项未提交改动；同步时特意未执行 pull，后续 Agent 必须
  继续保留这些内容，除非用户明确要求处理。

## 7. 运行任务前的简化检查

通常最多执行以下两类检查：确认 `/share` 余量，以及在工作树干净时快进同步仓库。

```bash
df -h /share
cd /share/Hyper/git/CMG_PIP
git status --short
git pull --ff-only
```

只有 `git status --short` 为空时才执行 pull；否则停止并保留用户修改。没有磁盘密集型输出且仓库已经
同步时，这两项也不必机械重复。长跑任务应把日志保存在对应计算节点的 `/share/Hyper` 下。
