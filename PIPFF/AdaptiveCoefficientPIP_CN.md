# 构型自适应系数 PIP：一种 PIP 力场与神经网络的乘法耦合构想

> 研究构想记录。本文档独立于当前 RSI 论文，用于保存尚待数值验证的模型设计。

## 1. 出发点

经验力场通常计算成本低、外推相对稳定，但拟合精度有限；机器学习势能面具有更高的拟合能力，却往往需要付出更大的数据和计算成本。因此，一类自然的研究路线是以经验力场作为基线，再由机器学习模型拟合其误差。

对于 PIP-NN，不一定需要额外选择一套外部经验力场。PIP 最初并不是作为神经网络描述符提出的：裸 PIP 展开

$$
E_{\mathrm{PIP}}(\mathbf R)=\sum_i c_iP_i(\mathbf R)
$$

本身就是一种具有严格置换对称性、全局光滑性和解析力的线性势能模型。因此，可以让 PIP 同时承担两种角色：既是神经网络的输入描述符，也是势能主干中的显式基函数。

## 2. 构型依赖的 PIP 系数

记 PIP 描述符向量为

$$
\mathbf p(\mathbf R)
=
\bigl(P_1(\mathbf R),\ldots,P_D(\mathbf R)\bigr)^{\mathsf T}.
$$

神经网络仍以这些 PIP 为输入，但不只输出一个标量能量，而是输出一组与 PIP 通道对应的调制量。最初设想的模型为

$$
E(\mathbf R)
=
\sum_{i=1}^{D}
w_i P_i(\mathbf R)
f\!\left(o_i(\mathbf p(\mathbf R))\right)
+E_{\mathrm{res}}(\mathbf p(\mathbf R)),
$$

其中

$$
f(x)=\frac{x}{\sqrt{1+x^2}}.
$$

函数 \(f\) 是奇函数，在原点附近近似线性，值域有界为 \((-1,1)\)，并且

$$
f'(x)=(1+x^2)^{-3/2}.
$$

于是每一个 PIP 的常数系数被推广为构型依赖的有效系数

$$
w_i^{\mathrm{eff}}(\mathbf R)
=w_i f\!\left(o_i(\mathbf p(\mathbf R))\right).
$$

这可以理解为一种构型自适应 PIP 力场：PIP 提供显式的全局代数基，神经网络根据当前构型调节各个基函数的贡献，而标量残差分支补充乘法主干未能表示的部分。

另一种保留裸 PIP 基线的形式为

$$
E(\mathbf R)
=
\sum_{i=1}^{D}
w_i P_i(\mathbf R)
\left[1+\lambda f\!\left(o_i(\mathbf p(\mathbf R)))\right)\right]
+E_{\mathrm{res}}(\mathbf p(\mathbf R)).
$$

当门控网络和残差网络为零时，该模型严格化为裸 PIP 势。参数 \(\lambda\) 控制构型依赖修正的幅度；当 \(0<\lambda\leq 1\) 时，还可以限制每个基函数系数相对于裸 PIP 基线的变化范围。纯门控形式和基线保持形式哪一种更有效，应由实验决定。

## 3. 编码器—解码器与乘法残差

由于 PIP 数量 \(D\) 通常显著大于神经网络隐藏层宽度，可以把门控网络写成编码器—解码器：

$$
\mathbf p
\xrightarrow{\mathrm{Encoder}}
\mathbf h
\xrightarrow{\mathrm{Decoder}}
\mathbf o.
$$

其中 \(\mathbf h\) 是低维潜变量，解码器输出与 PIP 通道对应的调制量 \(\mathbf o\)。从网络结构看，原始 PIP 向量构成一条通向能量输出的显式跳跃连接，解码器则对这条连接进行逐通道的乘法调制。因此，该模型可以视为带有乘法残差的 PIP 编码器—解码器。

与普通 PIP-NN 相比，网络不再完全负责从描述符重新构造势能，而是学习如何修改一套显式的 PIP 力场。低维瓶颈还约束了不同 PIP 系数的协同变化，使有效系数只能沿有限维潜在模式随构型改变。

## 4. 大规模 PIP 输入的线性压缩

当 PIP 数量达到数千甚至更多时，没有必要把编码器再次解码到全部 \(D\) 个 PIP 通道。可以首先引入一个普通的可训练稠密矩阵

$$
\mathbf q=A\mathbf p,
\qquad
A\in\mathbb R^{K\times D},
\qquad
K\ll D,
$$

并在压缩通道 \(\mathbf q\) 上进行编码、解码和乘法调制：

$$
\begin{aligned}
\mathbf h&=\operatorname{Enc}(\mathbf q),\\
\mathbf o&=\operatorname{Dec}(\mathbf h),\\
E(\mathbf R)
&=
\sum_{a=1}^{K}w_aq_a(\mathbf R)
\left[1+\lambda f(o_a)\right]
+r(\mathbf h).
\end{aligned}
$$

矩阵 \(A\) 不需要预先由 PCA、人工分组或稀疏选择确定，而可以与其余参数共同训练，由显式曲率优化器处理各层之间的强参数耦合。每个 \(q_a\) 仍是置换不变 PIP 的线性组合，因此整个模型严格保持置换不变性。

这种压缩主要减少解码器的参数量、内存占用和网络求值成本。如果全部 \(D\) 个原始 PIP 仍被显式计算，它并不会自动消除 PIP 本身的求值成本；稠密投影 \(A\mathbf p\) 还需要约 \(O(DK)\) 次运算。第一阶段可以先采用普通稠密矩阵验证模型结构，只有在结构确实有效后，再考虑稀疏投影、分块投影或将线性组合与 PIP 求值融合。

## 5. 编码器—解码器双残差结构

面向更深的 PIP 网络，可以在编码器—解码器主体中同时保留两类跳跃连接：

1. 每两个隐藏层之间的局部残差，用于改善深层网络的优化和曲率条件；
2. 从原始 PIP 或其线性压缩层通向各个残差块的描述符残差，用于防止高维 PIP 信息经过瓶颈后被逐层遗失。

经过线性压缩后，记

$$
\mathbf q=A\mathbf p.
$$

对于通用 PIP 势，还可以引入不破坏置换对称性的体系信息 \(\mathbf c\)，例如原子总数、各元素的原子数、分子数或其他离散体系标签的嵌入，并定义

$$
\mathbf z=
\left[
\mathbf q,\,
\mathbf c
\right].
$$

初始隐藏状态为

$$
\mathbf h_0=E_{\mathrm{in}}(\mathbf z).
$$

第 \(l\) 个双残差块可以写为

$$
\mathbf h_{l+1}
=
\mathbf h_l
+\alpha_l F_l(\mathbf h_l)
+\beta_l S_l(\mathbf z).
$$

其中，\(\mathbf h_l\) 是跨越当前两层变换的局部残差；\(S_l(\mathbf z)\) 是从压缩描述符和体系信息直接传入当前深度的描述符残差。最简单的两层残差变换和描述符投影分别为

$$
F_l(\mathbf h)
=
W_{l,2}
\phi\!\left(W_{l,1}\mathbf h+\mathbf b_{l,1}\right)
+\mathbf b_{l,2},
$$

$$
S_l(\mathbf z)=V_l\mathbf z.
$$

系数 \(\alpha_l\) 和 \(\beta_l\) 可以固定，也可以作为可训练标量。将它们初始化为较小值，可以使初始深层网络接近较浅模型，再由优化器逐步开放各个增量通道。为避免同一描述符随深度被重复加入而造成尺度随层数增长，\(\beta_l\) 可以从零或约 \(1/L\) 开始。

这一结构可概括为：

```text
PIP ──→ 线性压缩 q ──→ Encoder ──→ Block 1 ──→ Block 2 ──→ … ──→ Decoder
             │                         ↑            ↑                    │
             └─────────────────────────┴────────────┴────────────────────┘
                         描述符残差           层间残差
```

局部残差使每个两层模块只需学习对当前隐藏表示的增量修正；描述符残差则使每个深层模块都能够重新读取原始的压缩 PIP，而不要求编码器的低维瓶颈一次性、永久地保存全部相关信息。这两条路径分别解决深度优化和描述符信息保持问题，因此称为编码器—解码器双残差结构（encoder–decoder dual-residual architecture）。

与构型自适应系数 PIP 结合时，解码器输出与 \(K\) 个压缩 PIP 通道对应的门控量

$$
\mathbf o=\operatorname{Decoder}(\mathbf h_L),
$$

最终能量可以写为

$$
E
=
E_{\mathrm{base}}(\mathbf c)
+\sum_{a=1}^{K}
w_aq_a
\left[1+\lambda f(o_a)\right]
+r(\mathbf h_L).
$$

对于跨组成和跨体系规模的通用势，\(E_{\mathrm{base}}\) 可以包含显式的元素基准能

$$
E_{\mathrm{base}}(\mathbf c)
=
\sum_Z n_Z\varepsilon_Z,
$$

从而先处理能量随原子数增长的基本广延部分。这里允许输入的是原子总数、元素计数等置换不变量；任意指定的原子序号不能直接作为体系信息输入，否则会破坏同类原子置换不变性。

第一版原型不需要引入注意力、归一化或更复杂的门控机制。应先依次比较两层 MLP、普通深层 MLP、仅含局部残差的深层网络，以及完整双残差网络，从而分别判断深度、局部残差和描述符长程传递是否产生超过拟合波动的实际收益。

## 6. 低秩构型依赖展开的解释

在门控函数的近线性区间内，令 \(f(\mathbf o)\approx\mathbf o\)，并局部线性化解码器为

$$
\mathbf o\approx B\mathbf q.
$$

乘法修正项近似为

$$
\Delta E
\approx
\mathbf q^{\mathsf T}\operatorname{diag}(\mathbf w)B\mathbf q
=
\mathbf p^{\mathsf T}
A^{\mathsf T}\operatorname{diag}(\mathbf w)BA
\mathbf p.
$$

因此，这一结构在局部相当于一个秩受压缩维数 \(K\) 限制的 PIP 二次耦合。非线性编码器和解码器则把它推广为构型依赖的低秩 PIP 展开。这说明线性压缩不仅是计算技巧，也构成了模型归纳偏置的一部分。

## 7. 对称性与力

由于 \(P_i(\mathbf R)\)、\(q_a(\mathbf R)\)、门控量和残差均由置换不变量构成，模型的总能量严格满足相应的原子置换不变性。力可以通过自动微分或解析链式法则得到。对于单个乘法项，存在

$$
\nabla_{\mathbf R}\!\left[P_i f(o_i)\right]
=
f(o_i)\nabla_{\mathbf R}P_i
+P_i f'(o_i)\nabla_{\mathbf R}o_i.
$$

第二项是普通线性 PIP 力场中不存在的构型依赖修正。它提高了表达能力，也可能成为训练域外不稳定性的来源，因此模型评估不能只考察能量误差，还应检查力、轨迹稳定性和外推行为。

## 8. 需要实验回答的问题

该结构的主要假设不是它必然获得更低的插值误差，而是：在相近参数量和计算成本下，显式 PIP 力场主干与低维构型依赖调制能否改善小数据学习、物理外推或分子动力学稳定性。

最小消融实验应至少比较：

1. 裸线性 PIP；
2. 普通 PIP-NN；
3. 裸 PIP 加标量神经网络修正；
4. 不含标量残差的乘法门控 PIP；
5. 乘法门控 PIP 加受限的小型标量残差；
6. 带可训练线性压缩的低秩乘法门控 PIP；
7. 普通深层 PIP-NN、局部残差 PIP-NN 和编码器—解码器双残差 PIP-NN。

比较时应匹配模型参数量或实际推理成本，并同时考察能量误差、力误差、小样本效率、构型分布外测试、解离或反应路径行为以及长时间动力学稳定性。

一个关键风险是无约束的 \(E_{\mathrm{res}}\) 可能独自学习全部势能，使乘法 PIP 分支退化为无效装饰。初步实验可以先取消残差分支，随后再逐渐增加一个容量受限或带正则化的残差网络。另一项风险是 \(A\)、\(w_a\) 与后续网络层之间存在尺度和基变换冗余，可能产生病态的参数方向；显式曲率优化器可能缓解这一问题，必要时也可对 \(A\) 采用轻微权重衰减或行归一化。

## 9. 暂定名称

这一构想可以暂称为：

- 构型自适应系数 PIP（configuration-adaptive-coefficient PIP）；
- 自适应 PIP 力场（adaptive PIP potential）；
- 低秩自适应 PIP 势（low-rank adaptive PIP potential，用于包含线性压缩的版本）；
- 编码器—解码器双残差 PIP 网络（encoder–decoder dual-residual PIP network）。

其核心并不是简单地把经验力场与机器学习势相加，而是让神经网络在 PIP 所定义的显式势能基上学习受低维潜变量控制的构型依赖系数。
