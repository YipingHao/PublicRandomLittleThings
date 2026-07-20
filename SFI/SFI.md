# 可分多项式势能面

置换不变量描述符是一类向神经网络势能面（potential energy surface, PES）中严格引入全同粒子置换对称性的技术。设一个含 $N$ 个原子的体系，其笛卡尔坐标为

$$
Q=(\mathbf q_1,\ldots,\mathbf q_N)\in(\mathbb R^3)^N,
$$

全同原子的允许置换构成群 $G\leq S_N$。若 $\sigma$ 仅交换相同元素或相同分子中的等价原子，则 Born--Oppenheimer 势能满足

$$
V(\sigma Q)=V(Q),\qquad \sigma\in G.
$$

同时，孤立体系的势能还满足平移和旋转不变性。使用两两距离

$$
r_{ij}=\lVert\mathbf q_i-\mathbf q_j\rVert,
\qquad 1\leq i<j\leq N,
$$

或其单调变换 $x_{ij}=u(r_{ij})$（例如 Morse 型变量 $e^{-r_{ij}/a}$）可先消去平移和转动自由度。记全部成对变量组成的向量为

$$
x=(x_1,\ldots,x_M)\in\mathbb R^M,
\qquad M=\binom N2.
$$

原子置换通过

$$
\sigma\cdot x_{ij}=x_{\sigma(i)\sigma(j)}
$$

诱导出 $G$ 在键变量上的置换表示 $\rho:G\to S_M$。下文为简洁起见仍将其像记为 $G$。置换不变多项式环定义为

$$
\mathbb K[x]^G
=\{f\in\mathbb K[x_1,\ldots,x_M]:f(\sigma x)=f(x),\ \forall\sigma\in G\},
$$

其中通常取特征为零的域 $\mathbb Q$、$\mathbb R$ 或 $\mathbb C$。若 $m=x_1^{\alpha_1}\cdots x_M^{\alpha_M}$ 是一个单项式，则其轨道和

$$
\mathcal O_G(m)=\sum_{m'\in Gm}m'
$$

是不变多项式。固定总次数 $d=|\alpha|=\sum_i\alpha_i$ 后，所有次数为 $d$ 的单项式个数为

$$
|\mathcal M_d|=\binom{M+d-1}{d}.
$$

参考文档 `generatedpaperSI.md` 所述的生成算法不必枚举整个群：选取有限生成集 $G_s\subset G$，以 $\mathcal M_d$ 中的单项式为顶点，并在 $m$ 与 $s\cdot m$（$s\in G_s$）之间连边。图的每个连通分量恰好是一个 $G$-轨道，因此对分量内的单项式求和即可得到全部 $d$ 次轨道和。若采用 $N_i-1$ 个换位生成第 $i$ 类的 $S_{N_i}$，则 $|G_s|$ 随原子数至多线性增长；但顶点数 $|\mathcal M_d|$ 仍随 $M$ 和 $d$ 急剧增长。这说明新算法消除了显式遍历 $|G|\approx\prod_iN_i!$ 的阶乘瓶颈，却没有消除单项式空间本身的组合爆炸。

传统置换不变多项式（PIP）方法常采用次数截断

$$
\mathcal P_{\leq D}^G
=\bigoplus_{d=0}^{D}\mathbb K[x]_d^G,
$$

其维数可由 Molien 级数描述：

$$
H_G(t)=\sum_{d\geq0}\dim\mathbb K[x]_d^G\,t^d
=\frac1{|G|}\sum_{g\in G}\frac1{\det(I-t\rho(g))}.
$$

因此，直到 $D$ 次的独立不变量数为 $\sum_{d=0}^D[t^d]H_G(t)$。这给出了描述符数量的严格计数工具，也表明其增长不仅取决于键数和截断次数，还取决于群在键空间上的具体表示，不能只用一个与体系无关的简单幂律概括。

基本不变量（fundamental invariants, FI）试图进一步压缩 PIP。有限群在特征为零的多项式环上的不变量环是有限生成的，故存在有限集合

$$
F=\{f_1,\ldots,f_L\}\subset\mathbb K[x]^G,
\qquad
\mathbb K[x]^G=\mathbb K[f_1,\ldots,f_L].
$$

这意味着任意不变多项式均可写成 $P(f_1,\ldots,f_L)$。然而，代数生成集要求重构整个不变量环，通常比势能拟合所需的“区分构型”更强；而且 $L$、各 $f_i$ 的次数以及展开后的项数仍可能很大。对大体系，即使只计算一次高次 FI，也会带来明显的内存、训练和推理成本。

本文考虑较弱的目标：只要求描述符能够分离群轨道。设 $X\subseteq\mathbb R^M$ 是所研究的键变量域，映射

$$
\Phi_F:X\longrightarrow\mathbb R^L,
\qquad
\Phi_F(x)=(f_1(x),\ldots,f_L(x))
$$

由不变量组成。称 $F$ 在 $X$ 上是一个**可分集**（separating set），若

$$
\Phi_F(x)=\Phi_F(y)
\quad\Longleftrightarrow\quad
y\in Gx,
\qquad x,y\in X.
$$

其中“$\Leftarrow$”来自每个 $f_i$ 的 $G$-不变性，真正需要验证的是“$\Rightarrow$”。由可分集构成的描述符称为可分基本不变量（separating fundamental invariants, SFI）。这里的“基本”指用于描述商空间 $X/G$ 的基本坐标，而不宣称它们生成整个环 $\mathbb K[x]^G$。SFI 的目标是在保持轨道单射性的前提下减少描述符数量、次数和单项式项数。

需要区分三个层次：代数生成集一定是可分集；可分集不一定生成不变量环；有限阶截断或仅在训练数据上数值可分，则未必在整个物理构型域上可分。神经网络

$$
\widehat V(x)=\mathcal N(\Phi_F(x))
$$

自动满足 $G$-不变性。若 $\Phi_F$ 在目标构型域上连续且可分，则它不会因描述符碰撞而迫使两个不等价构型具有同一预测值；这正是 SFI 对势能拟合的核心保证。需要强调的是，可分性只排除信息论上的碰撞，不自动保证低阶网络易于逼近，也不自动给出良好的数值条件数。

# 可分基本不变量

以下固定有限群 $G\leq S_M$ 对 $\mathbb R^M$ 作坐标置换。对 $x,y\in X$，定义轨道等价关系

$$
x\sim_G y
\quad\Longleftrightarrow\quad
\exists g\in G,\ y=gx.
$$

商空间 $X/G$ 的点是轨道 $[x]_G$。任意不变量 $f$ 都可下降为商空间上的函数 $\bar f([x]_G)=f(x)$。所以可分性的准确含义不是“$\Phi$ 在 $X$ 上普通单射”，而是诱导映射

$$
\overline\Phi_F:X/G\longrightarrow\mathbb R^{|F|}
$$

为单射。对任何 $g\in G$，$x$ 与 $gx$ 本来就应具有相同描述符。

代数完备性与可分性可以写成两个不同的量词结构：

$$
\begin{aligned}
&\text{代数生成：}
&&\forall h\in\mathbb K[x]^G,\ \exists P,\ h=P(f_1,\ldots,f_L);\\
&\text{轨道可分：}
&&\forall x\not\sim_Gy,\ \exists f_i\in F,\ f_i(x)\neq f_i(y).
\end{aligned}
$$

前者是对所有不变多项式的函数表达能力作要求，后者只要求有限个坐标在点的层面不发生碰撞。若 $F$ 生成 $\mathbb K[x]^G$，而存在 $x\not\sim_Gy$ 却有 $f_i(x)=f_i(y)$ 对全部 $i$ 成立，则任何 $P(F)$ 在两点也相等；但有限群不变量总能分离不同轨道（附录给出构造性证明），产生矛盾。因此

$$
\text{代数完备}\quad\Longrightarrow\quad\text{可分}.
$$

逆命题通常不成立。一个可分集可能遗漏大量用于表达其他多项式所需的代数生成元，却仍能把每个轨道唯一编码。这种差异正是压缩 FI 的空间来源。

对于指定候选集 $F$，可分性可转化为“碰撞方程”是否存在非等价解：

$$
f_i(x)-f_i(y)=0,\qquad i=1,\ldots,|F|.
$$

全局可分要求该方程的解集合恰好为 $\bigcup_{g\in G}\{(x,gx):x\in X\}$。在代数闭域上可用理想与消元检验；在受约束的实构型域上，还需同时加入 Cayley--Menger、正距离和其他几何约束。数值采样只能发现反例，不能单独构成全局证明。

从维数上也能得到一个必要的下界。若 $X$ 含有 $\mathbb R^M$ 中的开集，有限群商 $X/G$ 仍为 $M$ 维，因此任何连续嵌入式描述符至少需要 $M$ 个实输出：

$$
|F|\geq M.
$$

但 $M$ 个不变量只是维数下界，并不保证足够。对一般有限置换群，商空间的拓扑和轨道分支可能要求更多坐标；只有在特殊群作用或限制后的物理域上，才可能用恰好 $M$ 个不变量实现全局可分。因此“$M$ 个键长就一定存在 $M$ 个多项式可分”的说法需要附加条件，不能由维数计数直接推出。

## 代数学完备基组的可分冗余性

真正的可分冗余是指：某个不变量为了多项式地生成整个不变量环而不可缺少，但删除它以后，剩余不变量仍能在所研究的实构型域上分离全部群轨道。甲醛 $\mathrm{CH_2O}$ 给出了一个简单而真实的分子例子。

把两个全同氢原子记为 $\mathrm H_1,\mathrm H_2$。甲醛的全同原子置换群为

$$
G=S_2(\mathrm H)=\{e,\tau\},
\qquad
\tau=(\mathrm H_1\,\mathrm H_2).
$$

使用完整的六个两体距离作为内部变量：

$$
r_{\mathrm{CO}},\quad r_{\mathrm{H_1H_2}},\quad
r_{\mathrm{CH_1}},\quad r_{\mathrm{CH_2}},\quad
r_{\mathrm{OH_1}},\quad r_{\mathrm{OH_2}}.
$$

氢交换 $\tau$ 固定 $r_{\mathrm{CO}}$ 和 $r_{\mathrm{H_1H_2}}$，并同时交换另外两对变量：

$$
r_{\mathrm{CH_1}}\longleftrightarrow r_{\mathrm{CH_2}},
\qquad
r_{\mathrm{OH_1}}\longleftrightarrow r_{\mathrm{OH_2}}.
$$

定义两对变量的和与差

$$
\begin{aligned}
a&=r_{\mathrm{CH_1}}+r_{\mathrm{CH_2}},
&u&=r_{\mathrm{CH_1}}-r_{\mathrm{CH_2}},\\
b&=r_{\mathrm{OH_1}}+r_{\mathrm{OH_2}},
&v&=r_{\mathrm{OH_1}}-r_{\mathrm{OH_2}}.
\end{aligned}
$$

于是群作用化为

$$
\tau:(u,v)\longmapsto(-u,-v),
$$

而 $r_{\mathrm{CO}},r_{\mathrm{H_1H_2}},a,b$ 均保持不变。对特征不为 $2$ 的域 $\mathbb K$，偶数总次数的单项式生成 $\mathbb K[u,v]^{G}$，所以完整不变量环为

$$
\mathbb K[r]^G
=\mathbb K[
r_{\mathrm{CO}},r_{\mathrm{H_1H_2}},a,b,
u^2,uv,v^2
].
$$

为了同时显出代数生成和轨道可分之间的差异，改取三个二次不变量

$$
q=u^2-v^2,\qquad
p=2uv,\qquad
s=u^2+v^2.
$$

它们满足

$$
u^2=\frac{s+q}{2},
\qquad
v^2=\frac{s-q}{2},
\qquad
uv=\frac p2.
$$

因此可以选择如下 FI：

$$
F_{\mathrm{FI}}
=\{
r_{\mathrm{CO}},r_{\mathrm{H_1H_2}},a,b,q,p,s
\},
$$

并且

$$
\mathbb K[r]^G=\mathbb K[F_{\mathrm{FI}}].
$$

这三个二次量之间存在代数关系

$$
s^2=q^2+p^2.
$$

尽管如此，$s$ 不能由 $q,p$ 多项式生成。若存在多项式 $P$ 使 $s=P(q,p)$，将 $(u,v)$ 同时缩放为 $(tu,tv)$ 可知 $P$ 必须是一阶齐次多项式，即 $s=\alpha q+\beta p$。分别代入 $(u,v)=(1,0)$ 和 $(0,1)$，会得到相互矛盾的 $\alpha=1$ 与 $\alpha=-1$。所以

$$
s\notin\mathbb K[q,p],
$$

它对于上述代数生成集是不可删除的。

但在真实分子所对应的实构型域上，$s$ 对轨道可分是冗余的。令

$$
z=u+\mathrm i v,
$$

则

$$
z^2=q+\mathrm i p.
$$

若两个实构型在 $q,p$ 上取值相同，则 $z'^2=z^2$，从而

$$
z'=z
\quad\text{或}\quad
z'=-z.
$$

第一种情况给出 $(u',v')=(u,v)$；第二种情况给出 $(u',v')=(-u,-v)$，恰好对应交换 $\mathrm H_1,\mathrm H_2$。再结合相同的 $a,b$，

$$
\begin{aligned}
r_{\mathrm{CH_1}}&=\frac{a+u}{2},
&r_{\mathrm{CH_2}}&=\frac{a-u}{2},\\
r_{\mathrm{OH_1}}&=\frac{b+v}{2},
&r_{\mathrm{OH_2}}&=\frac{b-v}{2},
\end{aligned}
$$

可知两组完整键长要么完全相同，要么仅相差允许的氢交换。因此

$$
F_{\mathrm{SFI}}
=\{
r_{\mathrm{CO}},r_{\mathrm{H_1H_2}},a,b,q,p
\}
$$

已经在实距离空间上分离全部 $S_2(\mathrm H)$ 轨道，并且

$$
F_{\mathrm{SFI}}\subsetneq F_{\mathrm{FI}},
\qquad
\mathbb K[F_{\mathrm{SFI}}]\subsetneq\mathbb K[r]^G.
$$

被删除的 $s$ 可以由

$$
s=\sqrt{q^2+p^2}
$$

在实数上唯一恢复，但这种恢复不是多项式运算。这正是代数完备性比实轨道可分性更强的具体来源。对于一般的三维甲醛构型，六个距离变量具有非空内部，故上述非生成性不会被额外的距离恒等式消除；若预先把体系严格限制在平面子空间，则还需在加入 Cayley--Menger 约束后的坐标环中重新讨论。

## 用幂和多项式表达可分性

草稿中曾把这一构造称为“一阶多项式”，但这里存在两种容易混淆的次数概念。对原始键变量而言，

$$
p_k(x)=\sum_{i=1}^{M}x_i^k
$$

是 $k$ 次多项式；但若先逐键构造特征 $\phi_k(x_i)=x_i^k$，则 $p_k$ 是对这些单键特征的一次求和，也就是

$$
p_k=\sum_i\phi_k(x_i).
$$

因此它可以称为“对单键特征的一阶池化”，而不能称为“关于原始键长的一次多项式”。这一区分对复杂度很重要：直接用逐元素幂和累加计算全部 $p_1,\ldots,p_M$，代价约为 $O(M^2)$，无需展开包含大量项的轨道和。

对任意 $x\in\mathbb C^M$，幂和

$$
p_k(x)=\sum_{i=1}^M x_i^k,
\qquad k=1,\ldots,M,
$$

能够唯一确定无序多重集 $\{x_1,\ldots,x_M\}$。证明可由 Newton 恒等式给出。定义初等对称多项式 $e_0=1$，

$$
e_k=\sum_{1\leq i_1<\cdots<i_k\leq M}
x_{i_1}\cdots x_{i_k},
$$

则

$$
k e_k=\sum_{i=1}^k(-1)^{i-1}e_{k-i}p_i,
\qquad k=1,\ldots,M.
$$

所以 $p_1,\ldots,p_M$ 递归确定 $e_1,\ldots,e_M$，进而确定首一多项式

$$
q_x(t)=\prod_{i=1}^M(t-x_i)
=t^M-e_1t^{M-1}+e_2t^{M-2}-\cdots+(-1)^Me_M.
$$

$q_x$ 的根连同重数恰为该无序多重集。因此

$$
(p_1(x),\ldots,p_M(x))=(p_1(y),\ldots,p_M(y))
\quad\Longleftrightarrow\quad
y=\pi x\ \text{for some }\pi\in S_M.
$$

这说明 $\{p_1,\ldots,p_M\}$ 不仅分离 $S_M$ 轨道，而且生成对称多项式环 $\mathbb Q[x]^{S_M}$（特征为零时与 $\{e_1,\ldots,e_M\}$ 等价）。

然而分子对称群是原子置换在边上的诱导像

$$
\rho(G)\leq S_M.
$$

当 $N=3$ 且三个原子全同，$M=3$，诱导像等于 $S_3$；当 $N\geq4$ 时，即便 $G=S_N$，也只有 $|\rho(G)|=N!$，远小于 $M!$。因此一个 $S_M$ 轨道通常分裂为许多 $\rho(G)$ 轨道：对一般位置、即所有键值互异的点，分裂数为

$$
\frac{M!}{|\rho(G)|}
=\frac{M!}{|G|}
\quad(N\geq3\text{ 时边作用忠实}).
$$

幂和在整个 $S_M$ 轨道上恒定，因而无法区分这些更细的小轨道。换言之，

$$
\text{幂和相等}
\Longleftrightarrow
\text{键长多重集相等},
$$

但通常不能推出“存在一个允许的原子置换把两个带标号键图相互映射”。

对多个一次轨道 $B_i$，可分别使用块幂和

$$
p_{i,k}=\sum_{x_j\in B_i}x_j^k,
\qquad k=1,\ldots,|B_i|.
$$

它们能恢复每个 $B_i$ 内的无序键值多重集，并分离扩大群

$$
\widetilde G=\prod_iS_{B_i}.
$$

由于真实诱导群通常满足 $G\subsetneq\widetilde G$，块幂和仍可能丢失跨块或块内的关联。它们可以作为低成本 SFI 候选集的骨架，但必须加入能把 $\widetilde G$ 轨道细分为 $G$ 轨道的关联不变量。一个直接的设计原则是：先用幂和恢复各类键值多重集，再逐步加入最短轨道和；每加入一个候选多项式，就检验它是否消除了当前仍存在的碰撞。最终集合是否可分，应由严格证明、符号计算或针对物理域的完备检验决定，而不能只由训练集上的经验表现决定。

## 为什么使用幂和多项式

幂和多项式的吸引力不仅来自它能够恢复无序键长多重集，还来自它极短的表达式和天然的递归计算结构。势能面构造中通常不直接使用裸键长 $r$，而先采用一个随距离衰减的单键变量

$$
x=f_1(r).
$$

常见选择包括倒数变量和指数型变量：

$$
f_1(r)=\frac1r,
\qquad\text{或}\qquad
f_1(r)=\exp\left(-\frac{r-r_0}{a}\right).
$$

在此基础上定义第 $k$ 阶单键特征

$$
f_k(r)=f_1(r)^k.
$$

它满足非常简单的递推关系

$$
f_0(r)=1,
\qquad
f_k(r)=f_{k-1}(r)f_1(r).
$$

因此，对倒数变量有

$$
f_k(r)=r^{-k},
$$

对指数变量有

$$
f_k(r)=
\exp\left(-\frac{k(r-r_0)}a\right).
$$

两者都不需要为每个 $k$ 重新调用除法、指数函数或通用乘方函数。只需计算一次 $f_1(r)$，后续各阶便可通过一次乘法递推得到。

需要准确区分单键递推和幂和递推。满足

$$
f_k(r)=g\bigl(f_{k-1}(r),f_1(r)\bigr),
\qquad
g(a,b)=ab,
$$

的是每条键上的单键特征。相应的块幂和为

$$
p_{\alpha,k}
=\sum_{r_j\in B_\alpha}f_k(r_j).
$$

一般不能仅由 $p_{\alpha,k-1}$ 和 $p_{\alpha,1}$ 直接计算 $p_{\alpha,k}$，因为求和已经丢失了每条键之间的一一对应关系。正确而高效的实现方式是先在逐键层面递推 $f_k(r_j)$，再对所属变量块求和。若用向量

$$
\mathbf f_k=
\bigl(f_k(r_1),\ldots,f_k(r_M)\bigr)
$$

表示全部单键特征，则整个计算可以写成

$$
\mathbf f_k=\mathbf f_{k-1}\odot\mathbf f_1,
\qquad
p_{\alpha,k}
=\sum_{j:r_j\in B_\alpha}(\mathbf f_k)_j,
$$

其中 $\odot$ 表示逐元素乘法。

这一结构对多项式生成软件尤其有利。传统的高阶 PIP 生成首先要枚举

$$
|\mathcal M_k|=\binom{M+k-1}{k}
$$

个 $k$ 次单项式，再判断它们在群作用下的轨道。随着 $k$ 增大，候选单项式数会发生组合爆炸。幂和则始终复用一次变量轨道的模板

$$
b_\alpha=\sum_{r_j\in B_\alpha}x_j.
$$

生成程序只需在一次单项式层面确定各变量块 $B_\alpha$，随后把模板中的单键变量 $x_j$ 替换成递推得到的 $f_k(r_j)$：

$$
b_\alpha
\quad\longrightarrow\quad
p_{\alpha,k}
=\sum_{r_j\in B_\alpha}f_k(r_j).
$$

程序不需要符号展开 $f_1(r_j)^k$，也不需要显式生成、存储或遍历高阶单项式集合。多项式的表示长度始终与块内键数成正比，而不会随总次数产生组合膨胀。

若共有 $M$ 条键，并需要计算从 $1$ 到截断阶数 $D$ 的全部幂和，计算过程可以概括为：对每条键只计算一次 $f_1(r_j)$；随后执行 $D-1$ 次逐元素乘法，并在每一阶进行分块累加。其时间复杂度为

$$
O(MD),
$$

所需的昂贵倒数或指数函数调用只有 $O(M)$ 次。采用流式实现时，只需保留当前的 $\mathbf f_k$ 和每个变量块的累加器。若一次变量轨道共有 $s$ 个，工作内存为

$$
O(M+s),
$$

存储全部输出 $\{p_{\alpha,k}\}_{1\leq\alpha\leq s,1\leq k\leq D}$ 另需 $O(sD)$ 空间。相比之下，展开式 PIP 的生成和求值成本还要乘上随 $M,k$ 快速增长的轨道数与轨道长度。

递推结构同样可以用于力的计算。设 $f_k=f_{k-1}f_1$，则

$$
\frac{\mathrm d f_k}{\mathrm d r}
=f_1\frac{\mathrm d f_{k-1}}{\mathrm d r}
+f_{k-1}\frac{\mathrm d f_1}{\mathrm d r},
$$

也可以直接写成

$$
\frac{\mathrm d f_k}{\mathrm d r}
=k f_1(r)^{k-1}\frac{\mathrm d f_1}{\mathrm d r}.
$$

因此，能量描述符及其关于键长的导数都能共享同一组逐键中间量，适合向量化、并行化和自动微分实现。

从神经网络势能面的角度看，这些性质使幂和成为一种很有吸引力的基础描述符：公式短、无需高阶符号生成、推理路径规则，并且计算量随键数和最高阶数线性增长。它并不自动解决上一节所述的分子置换群精细轨道可分问题，但可以低成本地编码每类键长的无序多重集，再由少量关联不变量补充原子邻接和跨块同步信息。

递推也有数值边界。指数变量通常可通过选择 $a,r_0$ 使主要采样区域内的 $|f_1(r)|$ 不超过或接近 $1$，从而避免高次幂爆炸；但阶数过高时仍可能出现下溢和不同长键信息被压缩的问题。倒数变量在非物理的小距离区域可能迅速增大。实际实现应结合物理距离范围选择尺度、最高阶数和归一化方式，并监控递推误差与描述符条件数。

## 键长可分和构型可分

完整键长空间 $\mathbb R_+^M$ 中并非每一点都对应 $\mathbb R^3$ 中的合法构型。定义距离映射

$$
D:(\mathbb R^3)^N\longrightarrow\mathbb R_+^M,
\qquad
D(Q)=(r_{ij})_{i<j},
$$

其像记为 $\mathcal E_{N,3}=D((\mathbb R^3)^N)$，称为三维欧氏距离域。三角不等式只是合法性的必要条件之一；对 $N>4$，还需要所有相关 Cayley--Menger 条件和秩条件。令平方距离矩阵 $\Delta$ 满足 $\Delta_{ij}=r_{ij}^2$，中心化矩阵

$$
J=I-\frac1N\mathbf1\mathbf1^{\mathsf T},
$$

则距离来自某个三维构型当且仅当 Gram 矩阵

$$
B=-\frac12J\Delta J
$$

半正定且 $\operatorname{rank}(B)\leq3$。因此，SFI 真正需要可分的域通常是 $\mathcal E_{N,3}/G$，而不是整个 $\mathbb R_+^M/G$。在较大的非物理空间上不可分，并不必然意味着在物理距离域上不可分；反过来，仅在一批物理样本上未发现碰撞也不构成证明。

完整的带标号两两距离能确定构型，但需要明确所模掉的刚体对称。若两个构型 $Q,Q'$ 具有完全相同的距离矩阵，则存在正交矩阵 $O\in O(3)$ 和平移 $t\in\mathbb R^3$，使

$$
\mathbf q_i'=O\mathbf q_i+t.
$$

所以距离对平移以及包括镜像在内的 $O(3)$ 变换不变。若势能对反射也不敏感，则距离是完整的内部坐标；若研究手性敏感性质并只希望模掉 $SO(3)$ 旋转，则还需加入有向体积等赝标量，例如

$$
\chi_{ijkl}
=(\mathbf q_j-\mathbf q_i)\cdot
\bigl((\mathbf q_k-\mathbf q_i)\times(\mathbf q_l-\mathbf q_i)\bigr),
$$

因为纯距离不能区分一对对映体。

幂和失败的四原子反例可以写得很明确。对四个全同原子，六条边组成完全图 $K_4$。取 $a\neq b>0$，考虑两种边着色：

$$
\begin{aligned}
A:&\quad r_{12}=r_{13}=r_{14}=a,
&&r_{23}=r_{24}=r_{34}=b;\\
B:&\quad r_{12}=r_{23}=r_{34}=a,
&&r_{13}=r_{14}=r_{24}=b.
\end{aligned}
$$

两者都有三个 $a$ 和三个 $b$，故对任意 $k\geq1$，

$$
p_k(A)=3a^k+3b^k=p_k(B).
$$

但在 $A$ 中，三条 $a$ 边构成度数序列 $(3,1,1,1)$ 的星形 $K_{1,3}$；在 $B$ 中，它们构成度数序列 $(2,2,1,1)$ 的路径 $P_4$。图的度数序列在顶点置换下不变，所以不存在 $S_4$ 原子置换把 $A$ 变成 $B$。取 $a=\sqrt2,b=1$ 时，两者还都是合法的三维距离矩阵。事实上，$A$ 的中心化 Gram 矩阵特征值为

$$
\left\{0,\frac12,\frac12,\frac54\right\},
$$

而 $B$ 的为

$$
\left\{0,\frac34,\frac{3-\sqrt5}{4},\frac{3+\sqrt5}{4}\right\}.
$$

两组特征值均非负且秩为 $3$，故这不是非物理键空间中人为制造的碰撞，而是物理构型域中的真实反例。

这个反例说明“键长多重集可分”与“分子构型可分”不同：前者只知道有哪些边长，后者还必须知道每个长度依附于哪些原子以及这些依附关系在允许置换下是否等价。关联轨道和能够补充这种图结构信息。例如二次轨道和会区分共享一个顶点的边对与互不相邻的边对：

$$
q_{\mathrm{adj}}
=\sum_{\{ij,ik\}}x_{ij}x_{ik},
\qquad
q_{\mathrm{opp}}
=x_{12}x_{34}+x_{13}x_{24}+x_{14}x_{23}.
$$

在四原子全同体系中，这两个量正对应参考论文 $\mathrm{Mg}_4$ 示例中的两类二次边轨道，并携带幂和缺失的邻接信息。构造 SFI 的实质，就是用尽可能少且尽可能低成本的这类关联不变量，使描述符从“边长直方图”提升为对物理距离图的轨道单射编码。

# 附录

## 有限群和有限变元下代数完备推出可分的证明

设 $\mathbb K$ 为特征不整除 $|G|$ 的无限域，有限群 $G$ 线性作用于 $\mathbb K^M$。先证明：任意两个不同轨道 $Gx\neq Gy$ 都能被某个 $G$-不变多项式分开。

因为 $Gx\cup Gy$ 是有限点集，可对该有限集合做多元插值。一个显式构造如下。对每个 $u\in Gx\cup Gy$ 和每个 $v\neq u$，选择一个线性函数 $\ell_{uv}$ 使 $\ell_{uv}(u)\neq\ell_{uv}(v)$，并定义

$$
L_u(z)=\prod_{v\neq u}
\frac{\ell_{uv}(z)-\ell_{uv}(v)}
{\ell_{uv}(u)-\ell_{uv}(v)}.
$$

于是 $L_u(u)=1$，且对集合中任意 $v\neq u$，$L_u(v)=0$。令

$$
h(z)=\sum_{u\in Gx}L_u(z),
$$

便有 $h=1$ 于 $Gx$，$h=0$ 于 $Gy$。再用 Reynolds 算符对称化：

$$
\mathcal R_Gh(z)
=\frac1{|G|}\sum_{g\in G}h(g^{-1}z).
$$

对任意 $a\in G$，换元 $g'=a^{-1}g$ 得

$$
(\mathcal R_Gh)(az)
=\frac1{|G|}\sum_{g\in G}h(g^{-1}az)
=(\mathcal R_Gh)(z),
$$

故 $\mathcal R_Gh\in\mathbb K[z]^G$。又因为 $Gx,Gy$ 各自在群作用下封闭，

$$
(\mathcal R_Gh)(x)=1,
\qquad
(\mathcal R_Gh)(y)=0.
$$

因此有限群不变量能够分离不同轨道。

现在设 $F=\{f_1,\ldots,f_L\}$ 代数生成 $\mathbb K[x]^G$。反设它不可分，则存在 $x\not\sim_Gy$ 满足

$$
f_i(x)=f_i(y),\qquad i=1,\ldots,L.
$$

由上一步，存在 $h\in\mathbb K[x]^G$ 使 $h(x)\neq h(y)$。但代数完备性给出某个多项式 $P\in\mathbb K[t_1,\ldots,t_L]$，使

$$
h=P(f_1,\ldots,f_L).
$$

于是

$$
h(x)=P(f_1(x),\ldots,f_L(x))
=P(f_1(y),\ldots,f_L(y))=h(y),
$$

矛盾。因此 $F$ 必为可分集。这个证明也说明原草稿中的插值—Reynolds 思路是合适的；关键是先在两个完整轨道的有限并集上插值，使目标函数在每个轨道上分别取常数，再对称化。若一开始只令多项式在代表点 $x,y$ 上取不同值，对称化后差异可能被平均掉。

## 用划分构造可分冗余的失败尝试

在找到甲醛例子之前，一个自然的尝试是利用一次轨道给高阶单项式分块，再把各块上的局部可分性拼成全局可分性。这个尝试没有构造出真正的可分冗余，但它澄清了局部轨道与全局轨道的差异，并给出了有用的生成算法剪枝。

设体系含若干类全同原子，第 $i$ 类原子的置换群为 $H_i$，则全同原子置换群通常写成

$$
G=H_1\times\cdots\times H_t.
$$

把由第 $i,j$ 类原子形成的距离变量集合记为 $B_{ij}$。当 $i=j$ 时，$B_{ii}$ 上的诱导群来自 $H_i$；当 $i\neq j$ 时，$B_{ij}$ 上的诱导群来自 $H_i\times H_j$。相应的一次轨道和为

$$
b_{ij}=\sum_{x\in B_{ij}}x.
$$

更一般地，把所有非空的一次变量轨道编号为

$$
R=B_1\sqcup\cdots\sqcup B_s,
\qquad
b_\alpha=\sum_{x\in B_\alpha}x.
$$

对总次数为 $d$ 的单项式

$$
m=\prod_{x\in R}x^{n_x},
$$

定义它在各变量块中的多重次数

$$
\deg_{B_\alpha}(m)=\sum_{x\in B_\alpha}n_x,
\qquad
\boldsymbol\delta(m)=
\bigl(\deg_{B_1}m,\ldots,\deg_{B_s}m\bigr).
$$

因为每个 $B_\alpha$ 在 $G$ 的作用下封闭，所以

$$
\boldsymbol\delta(gm)=\boldsymbol\delta(m),
\qquad g\in G.
$$

次数为 $d$ 的单项式集合因此按照 $d$ 的弱组成分解：

$$
\mathcal M_d
=\bigsqcup_{\substack{\boldsymbol k\in\mathbb N^s\\
\sum_\alpha k_\alpha=d}}
\mathcal M_{d,\boldsymbol k},
\qquad
\mathcal M_{d,\boldsymbol k}
=\{m:\boldsymbol\delta(m)=\boldsymbol k\}.
$$

另一方面，

$$
b^{\boldsymbol k}
=\prod_{\alpha=1}^s b_\alpha^{k_\alpha}
$$

展开后的支撑恰好是 $\mathcal M_{d,\boldsymbol k}$。不同 $\boldsymbol k$ 的支撑互不相交，而任一单项式轨道和 $\mathcal O_G(m)$ 完全落在唯一的多重次数块内。这一划分对计算仍然非常重要：PIP 的连通分量搜索、FI 的线性约束以及候选 SFI 的筛选都可以逐块进行。

最初的设想是：对每个纯块 $\mathbb K[B_\alpha]$ 分别选择代数完备因而可分的不变量集，再把这些局部集合联合起来；这样似乎可以删除支撑属于

$$
b_\alpha^{k_\alpha}b_\beta^{k_\beta},
\qquad
\alpha\neq\beta,\quad k_\alpha,k_\beta>0,
$$

的全部混合不变量。但这个推理忽略了局部群元素之间的兼容性。记 $G_\alpha$ 为 $G$ 在 $B_\alpha$ 上的诱导像，并考虑同时限制映射

$$
\Psi:G\longrightarrow\prod_{\alpha=1}^sG_\alpha,
\qquad
g\longmapsto
\bigl(g|_{B_1},\ldots,g|_{B_s}\bigr).
$$

假设两个全局键长构型 $x,y$ 在每个纯块的可分不变量上取值都相同。局部可分性只能推出：对每个 $\alpha$，分别存在某个 $g_\alpha\in G_\alpha$ 使

$$
y|_{B_\alpha}=g_\alpha\bigl(x|_{B_\alpha}\bigr).
$$

要推出全局等价，还必须存在同一个 $g\in G$ 同时实现所有这些变换，即所需元组必须满足

$$
(g_1,\ldots,g_s)\in\operatorname{im}\Psi.
$$

一般情况下 $\Psi$ 并不满射。同一个原子置换因子 $H_i$ 会同步作用于所有含指标 $i$ 的块，例如

$$
B_{ii},\qquad B_{ij},\qquad B_{ik}.
$$

在这些块上分别找到的 $H_i$ 置换可能互不一致。于是可能出现所有局部限制都分别等价、但不存在一个全局群元素沟通两个完整构型的情形。此时混合不变量记录的正是这种同步或配对信息，可能是全局可分所必需的。

反过来，若 $\Psi$ 的像确实是各块诱导群的完整直积，使各块上的群元素能够自由组合，那么局部可分集的并集的确能够全局可分。然而在这种情况下，混合轨道和已经满足乘积分解

$$
\mathcal O_G(m_\alpha m_\beta)
=\mathcal O_{G_\alpha}(m_\alpha)
 \mathcal O_{G_\beta}(m_\beta),
$$

相应的不变量环也分解为张量积。因此这些混合项不仅对可分性不必要，对代数生成同样不必要；真正的最小代数生成集本来就不需要它们。

所以，这个划分尝试落在两个极端：

1. 若各块相互交错，纯块可分性不能拼成全局可分性，混合项可能同时为代数生成和轨道可分所需要。
2. 若各块完全独立，混合项虽然可以删除，但它们本身已经是代数冗余，不能体现“代数生成所需而可分不需”的差异。

因此，多重次数划分没有直接构造出代数学完备基组中的可分冗余。它真正提供的是计算分块、代数冗余识别以及对群作用同步性的诊断。下一节给出由这一失败尝试保留下来的有效结论：如何利用群生成元充分地判定两个划分是否独立，以及何时可以安全删除它们之间的混合生成元。

## 不相交划分不含有生成元

这里给出“不交错变量块不需要混合生成元”的严格版本。设变量集分成不相交的两部分 $R=R_U\sqcup R_V$，令

$$
A=\mathbb K[R_U],\qquad B=\mathbb K[R_V].
$$

假设 $G=G_U\times G_V$，且作用满足

$$
(g_U,g_V)\cdot(u,v)=(g_Uu,g_Vv),
$$

即 $G_U$ 在 $R_V$ 上恒等，$G_V$ 在 $R_U$ 上恒等。多项式环自然同构为

$$
\mathbb K[R]\cong A\otimes_{\mathbb K}B.
$$

对任意 $f\in A\otimes B$，先分别使用两侧的 Reynolds 算符

$$
\mathcal R_U=\frac1{|G_U|}\sum_{g_U\in G_U}g_U,
\qquad
\mathcal R_V=\frac1{|G_V|}\sum_{g_V\in G_V}g_V.
$$

两算符作用于不同变量，故彼此交换，且

$$
\mathcal R_G=\mathcal R_U\mathcal R_V.
$$

若 $f\in(A\otimes B)^G$，则

$$
f=\mathcal R_Gf\in A^{G_U}\otimes B^{G_V}.
$$

反向包含显然成立，因此

$$
(A\otimes B)^{G_U\times G_V}
=A^{G_U}\otimes B^{G_V}.
$$

若 $A^{G_U}=\mathbb K[F_U]$、$B^{G_V}=\mathbb K[F_V]$，则

$$
\mathbb K[R]^G=\mathbb K[F_U\cup F_V].
$$

所以任何同时含 $R_U$ 与 $R_V$ 变量的轨道和，都能写成两侧生成元的多项式，不可能是一个必需的新基本生成元。更具体地，对 $m_U\in A,m_V\in B$，

$$
\begin{aligned}
\mathcal O_G(m_Um_V)
&=\sum_{u\in G_Um_U}\sum_{v\in G_Vm_V}uv\\
&=\left(\sum_{u\in G_Um_U}u\right)
  \left(\sum_{v\in G_Vm_V}v\right).
\end{aligned}
$$

这就是轨道和乘积分解。

同理，若 $S_U\subset A^{G_U}$、$S_V\subset B^{G_V}$ 分别可分，且

$$
s(x_U,x_V)=s(y_U,y_V),\qquad
\forall s\in S_U\cup S_V,
$$

则存在 $g_U\in G_U,g_V\in G_V$ 使 $y_U=g_Ux_U,y_V=g_Vx_V$，即 $y=(g_U,g_V)x$。故 $S_U\cup S_V$ 在乘积域上可分。

上述结论依赖“作用独立”而非仅仅“变量集合不相交”。若真实群是 $G_U\times G_V$ 的真子群，特别是对角子群

$$
G=\{(g,g):g\in H\}\subset H\times H,
$$

则分别观察两块只能确定各自的 $H$-轨道，却无法确定两块使用的是不是同一个群元素；此时混合不变量记录的正是同步关系，可能不可删除。因此，在实际 SFI 筛选中，判定某一划分“不含生成元”应依次验证：变量块在 $G$ 下封闭；$G$ 在各块上的作用核给出独立直积分解；目标构型域也按相同方式分解。只满足第一项时，只能安全地做多重次数分块，不能据此删除所有混合生成元。

上述直积条件可以利用群生成元和图连通性的观点转化为一个易于实现的算法判据。设 $G_s$ 是算法实际采用的群生成集，$B_i,B_j$ 是两个不同的一次变量轨道。对每个 $s\in G_s$，分别检查其在两个变量块上的限制。若

$$
\forall s\in G_s,\qquad
s|_{B_i}=\operatorname{id}_{B_i}
\quad\text{或}\quad
s|_{B_j}=\operatorname{id}_{B_j},
$$

即不存在一个生成元同时非平凡地置换 $B_i$ 和 $B_j$ 中的变量，则 $G_s$ 在 $B_i\sqcup B_j$ 上的限制可以分成

$$
G_{s,i}
=\{s|_{B_i\sqcup B_j}:s|_{B_j}=\operatorname{id}_{B_j}\},
\qquad
G_{s,j}
=\{s|_{B_i\sqcup B_j}:s|_{B_i}=\operatorname{id}_{B_i}\}.
$$

第一类生成元仅作用于 $B_i$，第二类仅作用于 $B_j$。由于两类生成元的支撑不相交，它们两两交换，因而在这两个变量块上的诱导群满足

$$
G|_{B_i\sqcup B_j}
=\langle G_{s,i}\rangle\times\langle G_{s,j}\rangle.
$$

所以该逐生成元检查一旦通过，就足以证明 $B_i$ 与 $B_j$ 的作用相互独立，并可安全地排除只由这两个部分混合产生的新基本生成元。算法可以写成

$$
\operatorname{Independent}(B_i,B_j)=
\bigwedge_{s\in G_s}
\left[
\left(s|_{B_i}=\operatorname{id}_{B_i}\right)
\lor
\left(s|_{B_j}=\operatorname{id}_{B_j}\right)
\right].
$$

这里的“恒等”必须指逐变量恒等，即 $s(x)=x$ 对块内每个 $x$ 都成立，而不能只检查一次不变量

$$
b_i=\sum_{x\in B_i}x
$$

是否保持不变。事实上，只要 $s$ 将 $B_i$ 映射到自身，就总有 $s(b_i)=b_i$；这一等式不能区分恒等作用和块内的非平凡置换。

这个生成元判据是**充分而不必要**的，并且依赖生成集的选择。若检查通过，两块一定独立；若检查失败，只能说明当前生成集中出现了同时作用于两块的“交错生成元”，不能据此证明两块一定相关。生成元选择不佳时，算法会保守地把实际无关的两个部分判为相关。例如设真实作用为直积

$$
G=\langle a\rangle\times\langle b\rangle.
$$

采用自然生成集

$$
G_s=\{(a,e),(e,b)\}
$$

时，每个生成元只作用于一侧，检查通过；但也可以选择

$$
G_s'=\{(a,b),(e,b)\}.
$$

当 $a,b$ 均为二阶元时，这仍生成同一个直积群，因为 $(a,b)(e,b)=(a,e)$。然而生成元 $(a,b)$ 同时非平凡地作用于两个变量块，所以上述逐生成元检查失败，并将两个实际独立的部分暂时判为“相关”。因此，该算法不会把真正相关的块误删为无关，但可能因生成元交错而保留本可删除的混合候选项。实际实现中宜选用支撑尽可能小、尽可能原子化的生成元；若初次检查失败，还可以尝试分解或更换生成集后再次检查。
