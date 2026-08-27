# 理论与方法

本文从置换不变量环的代数生成问题出发，将势能面描述符的目标放宽为对物理构型轨道的分离，并据此构造一种按照关联阶与递推深度组织的置换不变量。理论上严格可分的不变量集为方法提供设计目标；实际计算则采用有限关联阶与有限递推深度的截断，在严格置换不变的前提下寻求精度与计算成本之间的平衡。因此，除非另有证明，本文不把任意有限截断描述符宣称为全局严格可分集。

## 1. 分子置换对称性与构型商空间

考虑由 $N$ 个原子组成的分子体系，其笛卡尔坐标记为

$$
Q=(\mathbf q_1,\ldots,\mathbf q_N)\in(\mathbb R^3)^N.
$$

允许交换的全同原子构成有限置换群 $G\leq S_N$。在 Born--Oppenheimer 近似下，标量势能满足

$$
V(\sigma Q)=V(Q),
\qquad \sigma\in G.
$$

孤立体系的势能还对平移和正交变换不变。使用全部两两距离

$$
r_{ij}=\lVert\mathbf q_i-\mathbf q_j\rVert,
\qquad 1\leq i<j\leq N,
$$

可以消去平移和包括反射在内的 $O(3)$ 自由度。记边变量数为

$$
M=\binom N2,
$$

并将全部距离或其单射变换排列为

$$
x=(x_1,\ldots,x_M),
\qquad x_{ij}=u(r_{ij}).
$$

常见的 $u$ 包括 Morse 型、倒数型和有理型变量。原子置换通过

$$
\sigma\cdot x_{ij}=x_{\sigma(i)\sigma(j)}
$$

诱导出 $G$ 在边变量上的置换表示 $\rho:G\to S_M$。下文在不引起混淆时仍将其像记为 $G$。

对构型域 $X$，定义轨道等价关系

$$
x\sim_Gy
\quad\Longleftrightarrow\quad
\exists g\in G,\ y=gx.
$$

势能描述符真正需要编码的对象不是带标号空间 $X$，而是商空间 $X/G$。由一组不变量 $F=\{f_1,\ldots,f_L\}$ 定义映射

$$
\Phi_F:X\longrightarrow\mathbb R^L,
\qquad
\Phi_F(x)=\bigl(f_1(x),\ldots,f_L(x)\bigr).
$$

由于每个 $f_i$ 均为 $G$-不变量，$\Phi_F$ 在同一轨道上取值相同，并诱导商空间映射

$$
\overline\Phi_F:X/G\longrightarrow\mathbb R^L.
$$

因此，所谓描述符“保留构型信息”，准确含义应是 $\overline\Phi_F$ 为单射，而不是 $\Phi_F$ 在带标号空间上普通单射。

## 2. 代数完备性与轨道可分性

设 $\mathbb K$ 为特征为零的域。有限群 $G$ 在多项式环上的不变量环为

$$
\mathbb K[x]^G
=\{f\in\mathbb K[x]:f(gx)=f(x),\ \forall g\in G\}.
$$

一组不变量 $F=\{f_1,\ldots,f_L\}$ 若满足

$$
\mathbb K[x]^G=\mathbb K[f_1,\ldots,f_L],
$$

则称其代数生成整个不变量环。换言之，对任意 $h\in\mathbb K[x]^G$，存在多项式 $P$ 使

$$
h=P(f_1,\ldots,f_L).
$$

相比之下，$F$ 在 $X$ 上可分是指

$$
\Phi_F(x)=\Phi_F(y)
\quad\Longrightarrow\quad
x\sim_Gy,
\qquad x,y\in X.
$$

两种要求的量词结构不同：

$$
\begin{aligned}
&\text{代数生成：}
&&\forall h\in\mathbb K[x]^G,\ \exists P,\ h=P(F);\\
&\text{轨道可分：}
&&\forall x\not\sim_Gy,\ \exists f_i\in F,\ f_i(x)\neq f_i(y).
\end{aligned}
$$

### 2.1 代数生成推出轨道可分

有限群不变量能够分离不同轨道。事实上，若 $Gx\neq Gy$，可先在有限点集 $Gx\cup Gy$ 上构造一个多项式，使其在 $Gx$ 上取值 $1$、在 $Gy$ 上取值 $0$，再用 Reynolds 算符

$$
\mathcal R_Gh(z)
=\frac1{|G|}\sum_{g\in G}h(g^{-1}z)
$$

将其对称化，即得到一个能够区分两个轨道的 $G$-不变多项式。

若 $F$ 代数生成 $\mathbb K[x]^G$，但存在 $x\not\sim_Gy$ 满足 $\Phi_F(x)=\Phi_F(y)$，则所有 $P(F)$ 在两点上都相等，与有限群不变量能够分离不同轨道矛盾。因此

$$
\boxed{
\text{代数完备}\ \Longrightarrow\ \text{轨道可分}
}.
$$

逆命题一般不成立。可分集只要求商空间坐标不发生碰撞，不要求所有其他不变多项式都能由这些坐标作多项式表达。这正是压缩代数生成集的理论空间。

### 2.2 甲醛中的可分冗余

考虑甲醛 $\mathrm{CH_2O}$，允许交换两个全同氢原子：

$$
G=S_2(\mathrm H)=\{e,\tau\}.
$$

除固定的 $r_{\mathrm{CO}}$ 和 $r_{\mathrm{H_1H_2}}$ 外，定义

$$
\begin{aligned}
a&=r_{\mathrm{CH_1}}+r_{\mathrm{CH_2}},
&u&=r_{\mathrm{CH_1}}-r_{\mathrm{CH_2}},\\
b&=r_{\mathrm{OH_1}}+r_{\mathrm{OH_2}},
&v&=r_{\mathrm{OH_1}}-r_{\mathrm{OH_2}}.
\end{aligned}
$$

氢交换作用为

$$
\tau:(u,v)\mapsto(-u,-v),
$$

而 $r_{\mathrm{CO}},r_{\mathrm{H_1H_2}},a,b$ 保持不变。定义三个二次不变量

$$
q=u^2-v^2,
\qquad
p=2uv,
\qquad
s=u^2+v^2.
$$

由

$$
u^2=\frac{s+q}{2},
\qquad
v^2=\frac{s-q}{2},
\qquad
uv=\frac p2,
$$

可知

$$
F_{\mathrm{FI}}
=\{r_{\mathrm{CO}},r_{\mathrm{H_1H_2}},a,b,q,p,s\}
$$

代数生成完整不变量环。三个二次不变量满足

$$
s^2=q^2+p^2,
$$

但 $s$ 不能由 $q,p$ 作多项式表达，因而对上述代数生成集不可删除。

另一方面，令 $z=u+\mathrm i v$，则

$$
z^2=q+\mathrm i p.
$$

若两个实构型具有相同的 $q,p$，则 $z'=z$ 或 $z'=-z$，即

$$
(u',v')=(u,v)
\quad\text{或}\quad
(u',v')=(-u,-v).
$$

后者恰好对应交换两个氢原子。因此

$$
F_{\mathrm{sep}}
=\{r_{\mathrm{CO}},r_{\mathrm{H_1H_2}},a,b,q,p\}
$$

已经在实构型域上分离全部 $S_2(\mathrm H)$ 轨道。被删除的量可由

$$
s=\sqrt{q^2+p^2}
$$

连续恢复，但这种恢复不是多项式运算。该例说明，为生成整个不变量环所必需的坐标，可能对实轨道分离是冗余的。

## 3. 幂和：键值多重集恢复及其局限

### 3.1 幂和恢复无标号多重集

对 $M$ 个边变量定义幂和

$$
p_n(x)=\sum_{i=1}^{M}x_i^n,
\qquad n=1,\ldots,M.
$$

令 $e_0=1$，$e_k$ 为第 $k$ 个初等对称多项式。Newton 恒等式给出

$$
k e_k
=\sum_{i=1}^{k}(-1)^{i-1}e_{k-i}p_i,
\qquad k=1,\ldots,M.
$$

因此 $p_1,\ldots,p_M$ 递归确定 $e_1,\ldots,e_M$，进而确定首一多项式

$$
q_x(t)
=\prod_{i=1}^{M}(t-x_i)
=t^M-e_1t^{M-1}+\cdots+(-1)^Me_M.
$$

$q_x$ 的根及其重数恰为无标号多重集 $\{x_1,\ldots,x_M\}$，故

$$
(p_1(x),\ldots,p_M(x))
=(p_1(y),\ldots,p_M(y))
$$

当且仅当存在某个 $\pi\in S_M$ 使 $y=\pi x$。

幂和的计算不需要展开所有高次单项式。若只计算前 $D$ 阶，可在逐变量层面递推

$$
x_i^{n+1}=x_i^n x_i,
$$

并在每阶累加。总时间复杂度为

$$
O(MD),
$$

工作内存可保持为 $O(M)$。完整递推到 $D=M$ 时，时间复杂度为 $O(M^2)$。

### 3.2 过度对称化

幂和恢复的是无标号边值多重集，其不变群为整个边置换群 $S_M$。但真实分子允许的边置换只来自原子置换的诱导像

$$
\rho(G)\leq S_M.
$$

原子数大于3的时候，$\rho(G)$ 是 $S_M$ 的真子群。幂和因此引入了额外的、并不属于真实分子对称性的边置换不变性。换言之，它可能把多个不同的 $\rho(G)$ 轨道压缩到同一个边值多重集。

### 3.3 四原子反例

考虑四个全同原子和六条两两距离。取两个正数 $a\neq b$，定义三种边长分配：

$$
\begin{aligned}
A:\quad &r_{12}=r_{13}=r_{14}=a,\\
B:\quad &r_{12}=r_{13}=r_{23}=a,\\
C:\quad &r_{12}=r_{23}=r_{34}=a,
\end{aligned}
$$

其余三条边均取 $b$。三种分配中，取值为 $a$ 的边分别呈星形、三角形和三边路径式排列。三者具有完全相同的无标号边值多重集

$$
\{a,a,a,b,b,b\},
$$

故对任意 $n\geq1$，

$$
p_n(A)=p_n(B)=p_n(C)=3a^n+3b^n.
$$

然而三种边长邻接关系不同，不存在原子置换将其相互变换，因此它们属于不同的 $S_4$ 构型轨道。

这不是由非物理边长制造的反例。取

$$
a=\sqrt2,
\qquad b=1,
$$

三种距离分配对应的中心化 Gram 矩阵谱分别为

$$
\operatorname{spec}(B_A)
=\left\{0,\frac12,\frac12,\frac54\right\},
$$

$$
\operatorname{spec}(B_B)
=\left\{0,\frac14,1,1\right\},
$$

以及

$$
\operatorname{spec}(B_C)
=\left\{0,\frac34,
\frac{3-\sqrt5}{4},
\frac{3+\sqrt5}{4}\right\}.
$$

三者均半正定且秩为 $3$，因而都是合法的三维四原子构型。这个反例说明

$$
\boxed{
\text{恢复键值多重集}
\not\Longrightarrow
\text{全局恢复分子构型}
}.
$$

## 4. 物理距离域上的泛型构型重构

虽然幂和在抽象边空间中具有过度对称化，但分子距离并不是彼此独立的任意正数。令平方距离矩阵 $\Delta$ 满足

$$
\Delta_{ij}=r_{ij}^2,
$$

并定义中心化矩阵

$$
J=I-\frac1N\mathbf1\mathbf1^{\mathsf T}.
$$

相应的 Gram 矩阵为

$$
B=-\frac12J\Delta J.
$$

距离来自某个三维构型，当且仅当

$$
B\succeq0,
\qquad
\operatorname{rank}(B)\leq3.
$$

因此三维物理距离域 $\mathcal E_{N,3}$ 的一般维数为 $3N-6$，而抽象边空间的维数为 $M=\binom N2$。二者的余维为

$$
M-(3N-6)
=\frac{(N-3)(N-4)}2.
$$

当 $N=4$ 时余维为零，这解释了为什么一个无标号六边多重集可以在开区域内对应多个不同四面体。当 $N\geq5$ 时，Cayley--Menger 与秩关系开始显著限制合法的边值重排。

Boutin 和 Kemper 证明：对于 $N\geq m+2$ 个位于 $\mathbb R^m$ 中的一般位置点，其全部无标号两两距离能够唯一确定点构型，模掉平移、旋转、反射和点重标号。更准确地，存在一个非零多项式 $F(Q)$，使得 $F(Q)\neq0$ 时构型可由距离分布重构；不可由该定理保证的构型被包含在真代数集合 $F(Q)=0$ 中。因而在具有连续非退化密度的随机采样下，一般位置构型以概率一可重构。相关定理见 [Boutin 与 Kemper](https://arxiv.org/abs/math/0304192) 及其[后续重构判据](https://arxiv.org/abs/math/0311004)。

对三维全同原子体系，这给出

$$
N\geq5
\quad\Longrightarrow\quad
\text{完整距离多重集在一般位置上可重构}.
$$

若 $u(r)$ 为单射距离变换，则 $\{u(r_{ij})\}$ 与 $\{r_{ij}\}$ 包含相同信息。因此，完整的前 $M$ 个幂和在 $N\geq5$ 的三维全同原子物理构型域上具有泛型轨道可分性。

这一结论有四个边界。第一，它是泛型结论而非全局结论，不能排除特殊物理构型上的碰撞。第二，三维 $N=4$ 不满足定理条件。第三，只取 $D<M$ 个低阶矩时一般不能恢复完整距离多重集。第四，多元素体系或一般置换子群只允许部分原子重标号，需结合按元素类型划分的变量轨道另行分析。因此，本文将泛型重构视为低成本递推描述符的理论动机，而不把它当作任意有限截断的严格可分证明。

### 4.1 描述符碰撞的拟合后果

描述符映射 $\Phi$ 本身可以是连续的，但若存在

$$
\Phi(x)=\Phi(y),
\qquad
x\not\sim_Gy,
$$

且

$$
V(x)\neq V(y),
$$

则不存在单值函数 $\overline V$ 使

$$
V=\overline V\circ\Phi.
$$

任何只接收 $\Phi$ 作为输入的确定性回归模型，都必须在同一描述符纤维上的不同能量之间折中。即使严格碰撞位于低测度集合，其邻域也可能出现较小的描述符分离间隔和较差的逆映射条件。高关联信息的作用是进一步细化描述符纤维、减少碰撞和近碰撞；有限截断是否已经充分，仍需由理论证书或数值实验判断。

## 5. 多项式次数与关联阶

对单项式

$$
m=\prod_{e=1}^{M}x_e^{a_e},
$$

定义代数次数

$$
\deg(m)=\sum_{e=1}^{M}a_e,
$$

以及关联阶

$$
\operatorname{corr}(m)
=\left|\{e:a_e>0\}\right|.
$$

对多项式 $f=\sum_m c_m m$，可定义

$$
\operatorname{corr}(f)
=\max_{c_m\neq0}\operatorname{corr}(m).
$$

显然

$$
\operatorname{corr}(m)\leq\deg(m).
$$

例如

$$
x_e^{100}
$$

的代数次数为 $100$，但关联阶为 $1$；而

$$
x_{e_1}x_{e_2}x_{e_3}
$$

的代数次数和关联阶均为 $3$。因此，提高单变量幂次和增加同时耦合的变量数量是两种不同的信息增强方式。

### 5.1 四原子例子的关联层次

回到第 3.3 节的三个四原子构型。全部一关联矩只记录六条边的无标号值分布，因而不能区分 $A,B,C$。

对两条边，可以区分共享一个原子的相邻边对和没有公共原子的不相交边对。考虑相邻边对上的二关联统计。构型 $A$ 与 $B$ 均含有

$$
3\text{ 对 }(a,a),
\qquad
6\text{ 对 }(a,b),
\qquad
3\text{ 对 }(b,b),
$$

而构型 $C$ 的相邻边对统计不同。因此二关联量能够将 $C$ 与 $A,B$ 分开，但即使使用任意二元函数对全部相邻和不相交边对作轨道聚合，$A$ 与 $B$ 仍然无法区分。

三关联量可以突破这一限制。例如三角形边乘积的置换不变量

$$
T_{\triangle}
=\sum_{1\leq i<j<k\leq4}
x_{ij}x_{ik}x_{jk}
$$

在 $A,B$ 上分别为

$$
T_{\triangle}(A)=b^3+3a^2b,
$$

$$
T_{\triangle}(B)=a^3+3ab^2,
$$

二者之差为

$$
T_{\triangle}(A)-T_{\triangle}(B)
=(b-a)^3\neq0.
$$

这个例子表明

$$
\boxed{
\text{增加递推次数}
\neq
\text{增加关联阶}
}.
$$

前者提高固定关联阶内的单变量分辨率，后者引入新的多变量联合信息。

## 6. 一般 $k$-关联置换不变量的递推构造

设 $E$ 为所选基本变量的索引集合，$G$ 在 $E$ 上作置换。取由 $k$ 个互异基本变量组成的有序元组

$$
\mathbf e=(e_1,\ldots,e_k)\in E^k,
$$

群按

$$
g\mathbf e=(ge_1,\ldots,ge_k)
$$

作用。记 $\mathcal O\subset E^k$ 为一个 $k$-元组轨道。

对每个基本变量 $z_e$，构造单变量递推特征

$$
\phi_0(z_e),\phi_1(z_e),\ldots,\phi_D(z_e).
$$

对递推次数多重指标

$$
\boldsymbol\nu=(\nu_1,\ldots,\nu_k),
$$

定义 $k$-关联轨道不变量

$$
C_{\mathcal O;\boldsymbol\nu}(Q)
=\sum_{(e_1,\ldots,e_k)\in\mathcal O}
\prod_{j=1}^{k}
\phi_{\nu_j}(z_{e_j}(Q)).
$$

### 6.1 置换不变性

对任意 $g\in G$，变量满足

$$
z_e(gQ)=z_{g^{-1}e}(Q).
$$

因此

$$
\begin{aligned}
C_{\mathcal O;\boldsymbol\nu}(gQ)
&=\sum_{(e_1,\ldots,e_k)\in\mathcal O}
\prod_{j=1}^{k}
\phi_{\nu_j}(z_{g^{-1}e_j}(Q))\\
&=\sum_{(e'_1,\ldots,e'_k)\in g^{-1}\mathcal O}
\prod_{j=1}^{k}
\phi_{\nu_j}(z_{e'_j}(Q))\\
&=C_{\mathcal O;\boldsymbol\nu}(Q),
\end{aligned}
$$

因为 $g^{-1}\mathcal O=\mathcal O$。故任意关联阶、任意递推次数下的 $C_{\mathcal O;\boldsymbol\nu}$ 都严格满足所选分子置换对称性。

### 6.2 单变量递推

普通幂基满足

$$
\phi_0(z)=1,
\qquad
\phi_1(z)=z,
\qquad
\phi_{n+1}(z)=z\phi_n(z).
$$

为改善高阶数值条件，可将 $z$ 映射到 $[-1,1]$，并使用第一类 Chebyshev 多项式

$$
T_0(z)=1,
\qquad
T_1(z)=z,
$$

$$
T_{n+1}(z)=2zT_n(z)-T_{n-1}(z),
$$

或 Legendre 多项式

$$
P_0(z)=1,
\qquad
P_1(z)=z,
$$

$$
P_{n+1}(z)
=\frac{(2n+1)zP_n(z)-nP_{n-1}(z)}{n+1}.
$$

两类正交多项式的第 $n$ 项均为首项非零的 $n$ 次多项式，因此递推至相同最高次数 $D$ 时，它们与普通幂基张成相同的单变量多项式空间；在一关联多重集恢复问题中，递推至 $D=M$ 因而保留了前 $M$ 个普通幂矩的精确信息。它们的优势在于 $z\in[-1,1]$ 时幅值有界，避免普通高次幂的指数动态范围。

在固定 $k$-元组轨道 $\mathcal O$ 后，提高 $\nu_j$ 只需更新各基本变量上的单变量递推值，无需重新生成整个高总次数单项式空间。这使关联结构的枚举和单变量次数提升成为两个独立步骤。

### 6.3 计算复杂度

设基本变量数为 $L$，最高递推深度为 $D$。预计算全部单变量递推值的时间复杂度为

$$
O(LD).
$$

对选定的描述符集合 $\mathcal S$，直接轨道聚合的额外成本为

$$
O\!\left(
\sum_{(\mathcal O,\boldsymbol\nu)\in\mathcal S}
k|\mathcal O|
\right).
$$

若对某个 $k$ 保留所有满足 $1\leq\nu_j\leq D$ 的多重指标，则其数量可达 $O(D^k)$。因此，递推消除了对完整高次单项式空间的重复生成，但并不意味着关联阶和递推深度可以无限增加；实际计算仍需对二者同时截断。

## 7. 关联阶—递推深度二维截断

传统 PIP 常使用单一总次数截断

$$
\deg(m)\leq D.
$$

本文将描述符复杂度拆分为两个独立参数：

$$
K=\text{最高关联阶},
\qquad
D=\text{最高单变量递推深度}.
$$

实际候选集合满足

$$
\operatorname{corr}(C)\leq K,
\qquad
0\leq\nu_j\leq D.
$$

$K$ 控制同时耦合的不同内坐标数量及其组合成本，$D$ 控制固定关联结构内部的单变量分辨率。该二维层次允许优先使用较低关联阶的高递推次数信息，而不是因总次数较高就把它们与高关联、多指标组合项同时删除。

严格轨道可分通常需要足够大的候选集合及额外的代数或实几何验证，其成本对较大体系可能仍不可接受。本文因而采用可分性启发的有限截断：所有保留量严格置换不变，但不宣称任意有限 $K,D$ 已经全局分离物理构型轨道。截断参数通过描述符规模、推理成本和拟合误差共同确定。

### 7.1 低关联优先的经验假设

在固定描述符数量下，低关联阶不变量同时耦合的内坐标较少，表达式通常更短，求值所需乘法与索引组合也更少。当基本距离变量随键长衰减时，包含远距离变量的乘积贡献进一步受到抑制。基于这些性质，本文提出一个有限范围内的经验假设：在所研究的分子与数据分布上，优先保留低关联阶不变量可能获得更有利的精度—成本比。

该假设不是“关联阶必然等于空间局部性”的普遍定理。本文仅通过固定描述符数量或固定模型规模下的数值比较检验它，不将有限体系上的观察推广为无条件结论。

## 8. 多种内坐标上的一阶关联递推增强

纯距离一关联矩主要编码边值分布。为以较低的显式关联枚举成本补充联合几何信息，本文进一步对键角和二面角等派生内坐标构造一次轨道递推不变量。

记内坐标类型为

$$
\gamma\in\{r,\theta,\varphi\}.
$$

对每类内坐标，其索引集合在群作用下分解为若干一次轨道

$$
B_{\gamma,1},\ldots,B_{\gamma,s_\gamma}.
$$

定义统一的一阶递推量

$$
F_{\gamma,\alpha,n}(Q)
=\sum_{u\in B_{\gamma,\alpha}}
\phi_n(z_\gamma(u;Q)).
$$

该式对每个派生变量只作一次池化，因此在派生内坐标层面属于一阶关联；但角度和二面角本身分别携带三体和四体几何关系。

### 8.1 键长通道

首先使用元素对的单键共价半径和对距离无量纲化：

$$
\rho_{ij}
=\frac{r_{ij}}{R_i^{\mathrm{cov}}+R_j^{\mathrm{cov}}}.
$$

共价半径可采用 Pyykkö 和 Atsumi 的单键共价半径表。随后可选择以下映射到有限区间的径向变量：

$$
z_{\mathrm{rat}}(\rho)
=\frac{\rho-m}{\rho+m},
\qquad m>0,
$$

$$
z_{\mathrm{Morse}}(\rho)
=2e^{-a\rho}-1,
\qquad a>0,
$$

以及

$$
z_{\mathrm{Gaussian}}(\rho)
=2e^{-b(\rho-c)^2}-1,
\qquad b>0.
$$

有理与 Morse 映射在 $\rho>0$ 上单调，可作为保留径向排序信息的基础通道。Gaussian 映射在中心 $c$ 两侧不是单射，因此不能单独承担严格分离任务，但可以作为强调特定距离尺度的补充通道。不同映射和不同正交多项式基可以并行构成多尺度径向描述。

### 8.2 键角通道

对中心原子 $j$ 及两个端点 $i,k$，定义

$$
z_\theta(i,j,k)
=\cos\theta_{ijk}
=\frac{
(\mathbf q_i-\mathbf q_j)\cdot
(\mathbf q_k-\mathbf q_j)
}{r_{ij}r_{jk}}.
$$

该变量天然位于 $[-1,1]$。使用 Chebyshev 递推时，

$$
T_n(\cos\theta)=\cos(n\theta),
$$

因而无需显式计算 $\theta=\arccos z_\theta$，也不需要通过 $\sqrt{1-z_\theta^2}$ 构造正弦通道。这避免了额外反三角函数及其在 $z_\theta=\pm1$ 附近的数值病态。

虽然角度通道在派生变量上采用一阶轨道求和，但 $\cos\theta_{ijk}$ 若用距离表示，联合依赖同一三原子子构型中的三条距离。因此它能够补充单独键值多重集缺少的三体联合几何信息。第 3.3 节的三个四原子构型具有不同的角度余弦多重集；对角度余弦作一阶关联递推并保留必要的多个递推次数，即可将三者区分。

### 8.3 二面角通道

对四个原子 $i,j,k,l$，令

$$
\mathbf b_1=\mathbf q_j-\mathbf q_i,
\qquad
\mathbf b_2=\mathbf q_k-\mathbf q_j,
\qquad
\mathbf b_3=\mathbf q_l-\mathbf q_k,
$$

并定义两个平面法向量

$$
\mathbf n_1=\mathbf b_1\times\mathbf b_2,
\qquad
\mathbf n_2=\mathbf b_2\times\mathbf b_3.
$$

二面角余弦为

$$
z_\varphi(i,j,k,l)
=\cos\varphi_{ijkl}
=\frac{\mathbf n_1\cdot\mathbf n_2}
{\lVert\mathbf n_1\rVert\lVert\mathbf n_2\rVert}.
$$

对 $z_\varphi$ 使用相同的 Chebyshev 或 Legendre 递推，可以在不显式计算有符号二面角的情况下提供四体几何信息。一个二面角余弦若完全改写为距离函数，最多联合依赖该四原子子构型中的六条距离。因此，这里所谓“一阶关联”严格指派生二面角变量上的一次轨道聚合；相对于底层距离变量，它以较低的显式枚举成本注入了更高联合阶的几何信息，但并不等同于关于距离变换变量的低阶多项式。

纯余弦通道对 $\varphi$ 与 $-\varphi$ 取值相同，因而不编码手性符号；这与纯距离描述符的 $O(3)$ 不变性一致。若目标物理量需要区分对映体，则必须另行加入具有确定变换性质的有向体积或赝标量通道。

当中心键长度为零或任一法向量退化时，二面角本身不定义。实际能量与力计算应避免把任意常数约定误认为光滑物理延拓，并对退化构型设置合理的采样边界、正则化或替代坐标。

### 8.4 变量数量与计算成本

对 $N$ 个原子，全部两两距离数为

$$
M_r=\binom N2.
$$

以中心原子和无序端点对枚举的键角数为

$$
M_\theta
=N\binom{N-1}{2}
=\frac{N(N-1)(N-2)}2.
$$

以无序中心边和无序端点对枚举的二面角余弦数为

$$
M_\varphi
=\binom N2\binom{N-2}{2}
=\frac{N(N-1)(N-2)(N-3)}4.
$$

若三类变量的最高递推深度分别为 $D_r,D_\theta,D_\varphi$，则几何量构造和一阶递推聚合的主成本为

$$
O\!\left(
D_rM_r
+D_\theta M_\theta
+D_\varphi M_\varphi
\right).
$$

因此，该方案避免了高总次数单项式的组合枚举，但若显式使用全部二面角，仍存在 $O(N^4)$ 的几何枚举成本。本文的效率结论应限定在实际采用的体系规模、内坐标通道和递推截断范围内。

## 9. 可微计算与力

单变量递推和轨道聚合均由加法、乘法及可微几何映射组成，适合通过解析链式法则或自动微分计算力。以普通乘法递推为例，若

$$
\phi_n(r)=\phi_{n-1}(r)\phi_1(r),
$$

则

$$
\frac{\mathrm d\phi_n}{\mathrm dr}
=\phi_1\frac{\mathrm d\phi_{n-1}}{\mathrm dr}
+\phi_{n-1}\frac{\mathrm d\phi_1}{\mathrm dr}.
$$

Chebyshev 与 Legendre 三项递推也可对递推式直接求导，能量和导数共享相同的单变量中间量。对一般 $k$-关联量，乘积导数为

$$
\frac{\partial}{\partial r_e}
\prod_{j=1}^{k}\phi_{\nu_j}(z_{e_j})
=\sum_{s=1}^{k}
\left[
\frac{\partial\phi_{\nu_s}(z_{e_s})}{\partial r_e}
\prod_{j\neq s}\phi_{\nu_j}(z_{e_j})
\right].
$$

当 $e$ 不属于该关联元组时相应导数为零。规则化的递推与聚合形式能够避免对展开后每个高次单项式分别生成导数表达式。

需要强调的是，可微计算图并不自动保证所有几何区域数值良好。零键长、共线角和退化二面角会导致几何归一化病态；高阶递推也可能造成 Jacobian 条件数恶化。实际训练应结合物理采样范围、尺度归一化和导数稳定性检查。

## 10. 方法保证与适用边界

本文构造的每个轨道聚合量都严格满足指定的全同原子置换不变性。完整幂和在满足条件的物理距离域上具有泛型重构能力，一般 $k$-关联递推则提供了逐步增加联合几何信息的系统路径。多种内坐标的一阶递推以较低的显式关联枚举成本补充三体和四体几何信息。

另一方面，有限关联阶、有限递推深度和有限内坐标通道共同构成经验截断。它们不自动满足全局严格可分性，也不保证在所有体系上优于代数完备 FI。本文所验证的是以下三项性质：

1. 描述符的严格置换不变性；
2. 相对于显式高次不变量的规则递推计算路径与成本降低；
3. 在所测试数据集上的精度—成本表现。

严格全局可分仍可通过碰撞方程、消元、实代数证书或完备数值搜索进一步研究，但这不是实际有限截断成立的前提。本文将轨道分离视为描述符设计方向，将关联阶与递推深度作为可控近似的两个主要坐标。

## 参考文献提示

1. M. Boutin and G. Kemper, “On Reconstructing $n$-Point Configurations from the Distribution of Distances or Areas,” *Advances in Applied Mathematics* **32**, 709–735 (2004). [arXiv:math/0304192](https://arxiv.org/abs/math/0304192).
2. M. Boutin and G. Kemper, “Which Point Configurations Are Determined by the Distribution of Their Pairwise Distances?” *International Journal of Computational Geometry & Applications* **17**, 31–43 (2007). [arXiv:math/0311004](https://arxiv.org/abs/math/0311004).
3. P. Pyykkö and M. Atsumi, “Molecular Single-Bond Covalent Radii for Elements 1–118,” *Chemistry—A European Journal* **15**, 186–197 (2009). [DOI: 10.1002/chem.200800987](https://doi.org/10.1002/chem.200800987).


# SI

本节给出正文所使用结论的详细推导。正文仅保留这些结论及其物理含义；以下证明用于明确其适用条件和逻辑边界。

## 代数完备高于可分性的数学证明

设特征为零的域 $\mathbb K$ 上有限群 $G$ 线性作用于 $\mathbb K^d$，相应的不变量环为

$$
\mathbb K[x]^G
=\{h\in\mathbb K[x]:h(gx)=h(x),\ \forall g\in G\}.
$$

若有限集合

$$
F_{\mathrm{gen}}=\{f_1,\ldots,f_L\}
$$

满足

$$
\mathbb K[x]^G=\mathbb K[f_1,\ldots,f_L],
$$

则称其代数生成不变量环。若对给定构型域 $X$ 中任意 $x,y$，

$$
f_i(x)=f_i(y)\quad(i=1,\ldots,L)
\quad\Longrightarrow\quad
y\in Gx,
$$

则称 $F_{\mathrm{gen}}$ 在 $X$ 上分离 $G$-轨道。

**命题 S1.** 对有限群作用，任意代数生成集都是轨道可分集。

**证明。** 首先证明有限群不变量能够分离任意两个不同轨道。若 $Gx\neq Gy$，则 $Gx$ 和 $Gy$ 是两个不相交的有限点集。由于 $\mathbb K$ 是无限域，可以选择一个线性函数 $\ell$，使其在有限集合 $Gx\cup Gy$ 的各点上取值互不相同。由单变量 Lagrange 插值，存在多项式 $L$，使

$$
L(\ell(z))=
\begin{cases}
1,&z\in Gx,\\
0,&z\in Gy.
\end{cases}
$$

令 $h=L\circ\ell$，并用 Reynolds 算符将其对称化：

$$
\mathcal R_Gh(z)
=\frac1{|G|}\sum_{g\in G}h(g^{-1}z).
$$

$\mathcal R_Gh$ 是 $G$-不变多项式，并且在 $Gx$ 上恒为 $1$、在 $Gy$ 上恒为 $0$，因此能够区分这两个轨道。

若代数生成集 $F_{\mathrm{gen}}$ 不能分离某两个轨道，则存在 $x\not\sim_Gy$ 满足 $f_i(x)=f_i(y)$。然而任意不变量都可写为

$$
h=P(f_1,\ldots,f_L),
$$

所以所有不变量在 $x,y$ 上均相等，这与上面的轨道分离多项式矛盾。因此

$$
\text{代数完备}\quad\Longrightarrow\quad\text{轨道可分}.
$$

逆命题一般不成立。轨道可分只要求描述符映射在商空间 $X/G$ 上为单射，并不要求其他不变多项式能够由该描述符作多项式表达。这里“代数完备高于可分性”指前者是逻辑上更强的要求，而不单纯指两类集合的元素数量。

## 甲醛例子详解

考虑甲醛 $\mathrm{CH_2O}$，其非平凡置换对称性是两个氢原子的交换。记

$$
\begin{aligned}
c&=r_{\mathrm{CO}},&
d&=r_{\mathrm{H_1H_2}},\\
a&=r_{\mathrm{CH_1}}+r_{\mathrm{CH_2}},&
u&=r_{\mathrm{CH_1}}-r_{\mathrm{CH_2}},\\
b&=r_{\mathrm{OH_1}}+r_{\mathrm{OH_2}},&
v&=r_{\mathrm{OH_1}}-r_{\mathrm{OH_2}}.
\end{aligned}
$$

氢交换保持 $a,b,c,d$ 不变，并使

$$
(u,v)\longmapsto(-u,-v).
$$

因此关于 $u,v$ 的不变量环由 $u^2,uv,v^2$ 生成。作线性组合

$$
q=u^2-v^2,\qquad
p=2uv,\qquad
s=u^2+v^2,
$$

即可得到一组代数完备不变量

$$
F_{\mathrm{gen}}
=\{a,b,c,d,q,p,s\}.
$$

三者满足

$$
s^2=q^2+p^2.
$$

尽管 $s$ 不能由 $q,p$ 作多项式表达，它在实构型域上可以连续恢复：

$$
s=\sqrt{q^2+p^2}.
$$

更直接地，令 $z=u+\mathrm iv$，则

$$
z^2=q+\mathrm ip.
$$

若两个实构型具有相同的 $q,p$，则 $z'^2=z^2$，从而 $z'=z$ 或 $z'=-z$。前者对应同一个带标号构型，后者恰好对应两个氢原子的交换。因此

$$
F_{\mathrm{sep}}
=\{a,b,c,d,q,p\}
$$

已经分离所有实构型轨道。

最后说明这里的恢复确实不是多项式关系。若存在多项式 $P(q,p)=s$，沿 $v=0$ 有 $P(q,0)=q$ 对所有 $q\geq0$ 成立，因而作为多项式恒等式必须有 $P(q,0)=q$；但沿 $u=0$ 又要求 $P(q,0)=-q$ 对所有 $q\leq0$ 成立，产生矛盾。这个例子具体展示了代数生成集可以严格大于实轨道可分集。

## 幂和多项式可以划分键长的无序多重集合

设 $M$ 个键长变量或其单射变换为 $x_1,\ldots,x_M$，定义前 $M$ 个幂和

$$
p_n(x)=\sum_{i=1}^{M}x_i^n,
\qquad n=1,\ldots,M.
$$

令 $e_k$ 为第 $k$ 个初等对称多项式并令 $e_0=1$。Newton 恒等式为

$$
k e_k
=\sum_{i=1}^{k}(-1)^{i-1}e_{k-i}p_i,
\qquad k=1,\ldots,M.
$$

因此 $p_1,\ldots,p_M$ 依次确定 $e_1,\ldots,e_M$，进而确定首一多项式

$$
q_x(t)
=t^M-e_1t^{M-1}+\cdots+(-1)^Me_M
=\prod_{i=1}^{M}(t-x_i).
$$

$q_x$ 的根及其重数恰好构成无序多重集合 $\{x_1,\ldots,x_M\}$。由此得到

$$
\bigl(p_1(x),\ldots,p_M(x)\bigr)
=\bigl(p_1(y),\ldots,p_M(y)\bigr)
$$

当且仅当 $x$ 和 $y$ 只相差某个 $S_M$ 中的变量置换。若只保留 $D<M$ 个幂和，则上述完整恢复结论一般不再成立。

这一结论严格恢复的是无标号键值多重集合，而不必然恢复分子构型。对四个全同原子，取 $a\neq b$ 并考虑

$$
\begin{aligned}
A:\quad&r_{12}=r_{13}=r_{14}=a,\\
B:\quad&r_{12}=r_{13}=r_{23}=a,\\
C:\quad&r_{12}=r_{23}=r_{34}=a,
\end{aligned}
$$

其余三条距离均为 $b$。三种分配都具有多重集合

$$
\{a,a,a,b,b,b\},
$$

因而任意阶幂和都相同。另一方面，每个原子关联的 $a$ 型边数分别为

$$
(3,1,1,1),\qquad
(2,2,2,0),\qquad
(2,2,1,1),
$$

所以不存在原子置换将三种分配相互转换。

该反例可以由合法的三维构型实现。取

$$
a=\sqrt2,\qquad b=1,
$$

对每种距离分配构造平方距离矩阵 $\Delta$，再令

$$
J=I-\frac14\mathbf1\mathbf1^{\mathsf T},
\qquad
B=-\frac12J\Delta J.
$$

三个中心化 Gram 矩阵的谱分别为

$$
\operatorname{spec}(B_A)
=\left\{0,\frac12,\frac12,\frac54\right\},
$$

$$
\operatorname{spec}(B_B)
=\left\{0,\frac14,1,1\right\},
$$

$$
\operatorname{spec}(B_C)
=\left\{0,\frac34,
\frac{3-\sqrt5}{4},
\frac{3+\sqrt5}{4}\right\}.
$$

三者均为半正定矩阵且秩为 $3$，所以都对应合法的三维四原子构型。这证明“严格恢复键长多重集合”并不自动推出“全局恢复分子构型轨道”。

## 物理距离域上的泛型构型重构

由任意 $N$ 点构型得到的平方距离矩阵满足

$$
\Delta_{ij}=r_{ij}^2.
$$

令

$$
J=I-\frac1N\mathbf1\mathbf1^{\mathsf T},
\qquad
B=-\frac12J\Delta J.
$$

$\Delta$ 是某个三维欧氏构型的距离矩阵，当且仅当

$$
B\succeq0,\qquad \operatorname{rank}(B)\leq3.
$$

因此，除去整体平移与转动后，一般三维构型的自由度为 $3N-6$，而抽象边空间的维数为

$$
M=\binom N2.
$$

两者的维数差为

$$
M-(3N-6)=\frac{(N-3)(N-4)}2.
$$

当 $N=4$ 时该差为零，非退化合法距离在局部不存在额外的等式型余维约束，尽管仍须满足三角不等式和半正定性等不等式条件；当 $N\geq5$ 时，秩条件和 Cayley--Menger 关系开始以等式形式限制任意的边值重排。

这里采用代数几何意义下的“一般位置”或“泛型”概念：若某一性质在除去一个真代数集合之后成立，则称它泛型成立。Boutin 和 Kemper 的重构结果表明，对于 $N\geq m+2$ 个位于 $\mathbb R^m$ 中的一般位置点，全部无标号两两距离唯一确定该点构型，允许相差欧氏等距变换和点的重标号。等价地，存在一个非零多项式 $F(Q)$，使得

$$
F(Q)\neq0
$$

时构型可以从距离分布中重构。定理未覆盖的构型包含在真代数集合 $F(Q)=0$ 中。该集合在 $\mathbb R^{mN}$ 中具有 Lebesgue 零测度。因此，只要构型采样分布相对于 Lebesgue 测度具有连续密度，采中例外集合的概率为零。

对三维全同原子体系，$m=3$，所以

$$
N\geq5
\quad\Longrightarrow\quad
\text{完整距离多重集合泛型确定构型轨道}.
$$

若径向变换 $u(r)$ 为单射，则 $\{u(r_{ij})\}$ 和 $\{r_{ij}\}$ 含有相同信息。结合上一节的 Newton 恒等式可知，前 $M$ 个完整幂和对 $N\geq5$ 的三维全同原子体系具有泛型轨道可分性。

该结论具有以下限制：

1. 它是泛型而非全局结论，不能排除特殊构型上的严格碰撞。
2. 它不适用于 $N=4$ 的情形，上一节已经给出物理反例。
3. 它要求完整恢复距离多重集合，不能直接推广到只取 $D<M$ 个低阶矩的有限截断。
4. 对多元素体系，允许的原子重标号群通常是 $S_{N_1}\times\cdots\times S_{N_s}$ 而不是 $S_N$；需要按照元素类型构造相应的变量轨道，不能直接套用全同点的无标号距离结论。
5. 零测度只描述严格碰撞的概率，不保证例外集合附近的逆映射具有良好条件数。近碰撞仍可能影响势能拟合。

## 更一般的递推技巧

设 $E$ 为基本变量的索引集合，有限置换群 $G$ 在 $E$ 上作用。对由 $k$ 个互异索引组成的有序元组

$$
\mathbf e=(e_1,\ldots,e_k),
$$

记其轨道为 $\mathcal O\subset E^k$。在每个基本变量 $z_e$ 上计算单变量递推基

$$
\phi_0(z_e),\phi_1(z_e),\ldots,\phi_D(z_e).
$$

对多重指标 $\boldsymbol\nu=(\nu_1,\ldots,\nu_k)$ 定义

$$
C_{\mathcal O;\boldsymbol\nu}(Q)
=\sum_{(e_1,\ldots,e_k)\in\mathcal O}
\prod_{j=1}^{k}\phi_{\nu_j}(z_{e_j}(Q)).
$$

若基本变量满足

$$
z_e(gQ)=z_{g^{-1}e}(Q),
$$

则对任意 $g\in G$，

$$
\begin{aligned}
C_{\mathcal O;\boldsymbol\nu}(gQ)
&=\sum_{\mathbf e\in\mathcal O}
\prod_{j=1}^{k}\phi_{\nu_j}(z_{g^{-1}e_j}(Q))\\
&=\sum_{\mathbf e'\in g^{-1}\mathcal O}
\prod_{j=1}^{k}\phi_{\nu_j}(z_{e'_j}(Q))\\
&=C_{\mathcal O;\boldsymbol\nu}(Q),
\end{aligned}
$$

其中最后一步使用了 $g^{-1}\mathcal O=\mathcal O$。因此任意关联阶和任意递推深度下，该轨道聚合都严格满足指定的置换不变性。

最直接的单变量递推是幂基

$$
\phi_0(z)=1,\qquad
\phi_1(z)=z,\qquad
\phi_{n+1}(z)=z\phi_n(z).
$$

若先将 $z$ 变换到 $[-1,1]$，还可以使用 Chebyshev 递推

$$
T_0(z)=1,\qquad T_1(z)=z,\qquad
T_{n+1}(z)=2zT_n(z)-T_{n-1}(z),
$$

或 Legendre 递推

$$
P_0(z)=1,\qquad P_1(z)=z,
$$

$$
P_{n+1}(z)
=\frac{(2n+1)zP_n(z)-nP_{n-1}(z)}{n+1}.
$$

由于 $T_n$ 和 $P_n$ 都是具有非零最高次项的 $n$ 次多项式，从

$$
\{1,z,\ldots,z^D\}
$$

到

$$
\{T_0,\ldots,T_D\}
\quad\text{或}\quad
\{P_0,\ldots,P_D\}
$$

的换基矩阵为可逆三角矩阵。因此在相同最高次数 $D$ 下，三种基张成相同的单变量多项式空间；换用正交多项式改变的是数值条件和特征组合，而不是该截断空间的代数信息容量。

若基本变量数为 $L$，预计算全部深度不超过 $D$ 的单变量递推量需要

$$
O(LD)
$$

次基本运算。对选定描述符集合 $\mathcal S$，直接轨道聚合的额外成本为

$$
O\!\left(
\sum_{(\mathcal O,\boldsymbol\nu)\in\mathcal S}
k|\mathcal O|
\right).
$$

如果在固定关联阶 $k$ 下保留所有满足 $1\leq\nu_j\leq D$ 的多重指标，其数量仍可达到 $O(D^k)$。因此递推减少了重复生成和求值高次单项式的成本，但没有消除随关联阶产生的组合增长；实际算法仍需同时截断关联阶和递推深度。

## 可微计算与力

设模型能量写为描述符的函数

$$
\widehat V(Q)=\mathcal N\bigl(F_1(Q),\ldots,F_L(Q)\bigr).
$$

第 $i$ 个原子的预测力为

$$
\widehat{\mathbf F}_i
=-\nabla_{\mathbf q_i}\widehat V
=-\sum_{\alpha=1}^{L}
\frac{\partial\mathcal N}{\partial F_\alpha}
\nabla_{\mathbf q_i}F_\alpha.
$$

单变量递推可以在计算函数值的同时递推其导数。例如，若

$$
\phi_{n+1}(z)=z\phi_n(z),
$$

则对任意笛卡尔分量 $R$，

$$
\frac{\partial\phi_{n+1}}{\partial R}
=\frac{\partial z}{\partial R}\phi_n
+z\frac{\partial\phi_n}{\partial R}.
$$

Chebyshev 递推的导数相应满足

$$
\frac{\partial T_{n+1}}{\partial R}
=2\frac{\partial z}{\partial R}T_n
+2z\frac{\partial T_n}{\partial R}
-\frac{\partial T_{n-1}}{\partial R}.
$$

对一般 $k$-关联乘积，

$$
\frac{\partial}{\partial R}
\prod_{j=1}^{k}\phi_{\nu_j}(z_{e_j})
=\sum_{s=1}^{k}
\left[
\frac{\partial\phi_{\nu_s}(z_{e_s})}{\partial R}
\prod_{j\neq s}\phi_{\nu_j}(z_{e_j})
\right].
$$

求和、单变量递推和轨道聚合均由标准可微运算组成，因而可以直接嵌入自动微分框架。能量和力计算可以共享单变量递推值以及轨道乘积等中间量，不需要先把高次多项式完全展开，再逐项生成独立的导数表达式。

可微计算图并不等于所有几何区域都数值良好。距离导数在零键长处不定义；角度余弦包含键长归一化；二面角余弦还包含两个平面法向量的归一化。当键长趋近于零或相关原子趋于共线时，这些表达式可能出现较大的导数或失去定义。实际训练与动力学计算应保证采样位于物理构型域内，并结合尺度归一化、分母正则化或替代坐标检查力的数值稳定性。
