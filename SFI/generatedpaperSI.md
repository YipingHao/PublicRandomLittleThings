\documentclass[journal=jctc,manuscript=article]{achemso}
\usepackage{xcolor}
\usepackage{caption}
\usepackage{graphicx} % Required for inserting images
\usepackage{amsmath}
\usepackage{amssymb}
\usepackage{geometry}
%
\usepackage{booktabs}

\usepackage{tabularx}
\usepackage{wrapfig}
\newcolumntype{Y}{>{\centering\arraybackslash}X}


\usepackage[version=4]{mhchem}
%\newcommand*\mycommand[1]{\texttt{\emph{#1}}}

%\AtEveryBibitem{\clearfield{eprint}}
%\newcommand{\figref}[1]{S\ref{#1}}

\renewcommand{\thefigure}{S\arabic{figure}} %
\setcounter{figure}{0} % 


\usepackage{fancyhdr} % 导入 fancyhdr 包
%\usepackage{lipsum}   % 仅用于生成示例文本

% 定义页码格式
\renewcommand{\thepage}{S-\arabic{page}}

% 设置页眉和页脚样式
\fancypagestyle{plain}{
    \fancyhf{} % 清除所有默认设置
    \fancyfoot[C]{\thepage} % 在页脚中央放置页码
    \renewcommand{\headrulewidth}{0pt} % 移除页眉线
}

% 确保文档正文也使用该页眉页脚样式
\pagestyle{plain}

% 如果需要从 S-1 开始计数，则不需要额外设置，因为默认是从 1 开始的。
% 如果需要从其他数字开始，例如 S-5：
%\setcounter{page}{5}

\title{Supporting Information for: New Algorithms to Generate Permutationally Invariant Polynomials and Fundamental Invariants for Potential Energy Surface Fitting}
\author{Yiping Hao}
\affiliation{State Key Laboratory of Molecular Reaction Dynamics, Dalian Institute of Chemical Physics, Chinese Academy of Science, Dalian 116023, People’s Republic of China}
\alsoaffiliation{School of Chemical Sciences, University of Chinese Academy of Sciences, Beijing 100049, China}
\author{Xiaoxiao Lu}
%\email{fayelulu@dicp.ac.cn}
\affiliation{State Key Laboratory of Molecular Reaction Dynamics, Dalian Institute of Chemical Physics, Chinese Academy of Science, Dalian 116023, People’s Republic of China}

\author{Bina Fu}
\email{bina@dicp.ac.cn}
\affiliation{State Key Laboratory of Molecular Reaction Dynamics, Dalian Institute of Chemical Physics, Chinese Academy of Science, Dalian 116023, People’s Republic of China}
\alsoaffiliation{Hefei National Laboratory, Hefei 230088, China}
\alsoaffiliation{School of Chemical Sciences, University of Chinese Academy of Sciences, Beijing 100049, China}

\author{Dong H. Zhang}
%\email{zhangdh@dicp.ac.cn}
\affiliation{State Key Laboratory of Molecular Reaction Dynamics, Dalian Institute of Chemical Physics, Chinese Academy of Science, Dalian 116023, People’s Republic of China}
\alsoaffiliation{Hefei National Laboratory, Hefei 230088, China}
\alsoaffiliation{School of Chemical Sciences, University of Chinese Academy of Sciences, Beijing 100049, China}




\begin{document}

\maketitle


%\begin{wrapfigure}{r}{0.32\textwidth}
%\centering

%\caption{Speed comparison on a 15-atom molecule, tropolone.}
%\label{tab:abstract}
%\end{wrapfigure}





%\subsection{Fundamental of the New Algorithm for Construction the Action of Reynold Operator}
\subsection{The Mathematical Principles Overview of the New Algorithm}
In a finite group, the order can vastly exceed the minimum number of its generators. For example, the order of the permutation group $S_N$ is $N!$, yet it requires only two generators. This property serves as the foundation of our algorithm. Traditional methods for generating invariant polynomials, such as those based on Reynolds operators, involve traversing the entire finite group, which has an order approximately proportional to $\prod_i N_i!$, where $N_i$ is the number of atoms of the $i$-th type. The time complexity of these methods, being factorial in the number of identical atoms, presents a considerable computational challenge for large systems. 
Our approach seeks to exploit the efficiency of using a small subset of generators rather than the complete symmetry group, offering a substantial computational advantage. This requires addressing two key issues: first, determining the appropriate generating set for the symmetry group of the molecular system in question, and second, understanding how to compute invariants from these generators.
For the first question, it is encouraging that, for an $N$-atom system, the number of necessary generators for its symmetry group can be fewer than $N$. Regarding the second question, the concept of graph connectivity emerges as a pivotal tool in computing invariants using these generators. We will begin by presenting some fundamental propositions along with concise proofs. While some of these propositions are already established in algebra textbooks, others, due to their simplicity, may also have been previously noted and implicitly used in relevant work.

\paragraph{Proposition 1.1 Given a group $G$ with its finite generation set $G_s$ and its action on a finite set $K$. The set $K$ is invariant under action of $G$ if and only if $K$ is invariant under action of a generation set $G_s$.\\}
$\bf{PROOF}$ 

$\Rightarrow\ \forall g \in G,\ k\in K\ gk=k$ , then $\ \forall g_s \in G_s\subset G,\ k\in K\ g_sk=k$.

$\Leftarrow\forall g \in G,\ g = \prod_{i}g_{si}\ g_{si} \in G_s$, for $\forall\ k\in K, gk = \prod_{i}g_{si}k = g_{s1}(g_{s2}\cdots(g_{sn-1}(g_{sn}k)))=k$.$\newline$


 

Consider a undirected graph $\mathcal{G}=\left\langle \mathcal{V},\ \mathcal{E}\right\rangle$, $\mathcal{V}$ denotes the set of nodes and $\mathcal{E}$ denotes the set of edges which are unordered pairs of elements of $\mathcal{V}$. If there are $N_G$ vertices and maximum of degree is $M_G$, then we can do connected component judge by depth-first search or broadth-first search within a time and space complexity of $O(N_GM_G)$. 

\paragraph{Proposition 1.2 Given a group $G$ with its finite generation set $G_s$ and its action on a finite set $K$. Regard $K$ as the vertices set $\mathcal{V}_K$ of a undirected graph $\mathcal{G}_K$. And the edges set $\mathcal{E_K}$ of $\mathcal{G}_K$ corresponds with all the actions of the generation set $G_s$ i.e. if there is an action among $g_{i}\in G_s,\ k_1,k_2\in K$ that is $g_ik_1=k_2$, then there is an edge between $k_1,k_2\in \mathcal{V}_K$; and on the contrary if there is an edge between $k_1,k_2\in \mathcal{V}_K$, then there is a generator $g_i$ that $g_ik_1=k_2$ or $g_ik_2=k_1$. Then each orbit under $G$ is the very set of all vertices within each connected component of $\mathcal{G}_K$.\\}
$\bf{PROOF}$ 

$k_1,k_2$ are in the same orbit.

$\Longleftrightarrow$ there is $g\in G$ that $gk_1=k_2$.

$\Longleftrightarrow$ there is $\prod_{i}g_{si}$ that each $\ g_{si} \in G_s$ and $\prod_{i}g_{si}k_1=k_2$

$\Rightarrow$ $k_1$ and $k_2$ are in the same connected component.

$\Rightarrow$ there is $\ g_{si} \in G_s$, $\ op\left(g_{si}\right) = g_{si}$ or $g^{-1}_{si}$ and $\prod_{i}op\left(g_{si}\right)k_1=k_2$

$\Rightarrow$ there is $g\in G$ that $g_ik_1=k_2$.
$\newline$



\paragraph{Proposition 1.3 $\left\{(1i)\ i = 2,3,\cdots N\right\}$ is an generator set of $S_N$. And $\left\{(12),\ (123\cdots N)\right\}$ is one of the minimal generator set of $S_N$\\}
$\bf{PROOF}$ Details have been listed in many algebra textbooks such as \cite{hungerford2012algebra}. The sketch of the proof is as follows: any elements of a permutation group $S_N$ are products of disjoint cycles like $\left(i_1i_2i_3\cdots i_r\right),\ (r< N)$, and any cycles are products of transpositions $\left(i_1i_2\right)$ and $\left(i_1i_2\right)=\left(1i_2\right)\left(1i_1\right)\left(1i_2\right)$. As for the last half, let $a = (12)$ and $b = (123\cdots N)$, then $b^{-1}=b^{N-1}$ and $b^{i+1}a{b^{-i-1}}=(i\ \ i+1), 0 \leq i < N-1$

For simplicity, in the algorithm described in this paper, we use a larger set $\left\{(1i)\ i = 2,3,\cdots N\right\}$, rather than the minimal generating set $\left\{(12),\ (123\cdots N)\right\}$. All the elements in the former set is of order 2, this property allows us to do the connectivity judgement on-the-fly(without explicit construction of the graph). Such choice does not significantly increase the computational time of the algorithm.


\paragraph{Proposition 1.4 $G_{s1}$, $G_{s2}$ are the Generation Set of finite group $G_1$ and $G_2$. If a finite group $G=\left<G_1,G_2\right>$, then $G_{s1}\cup G_{s2}$ is a Generation Set of $G$.} 
The above four propositions, especially Proposition 1.3, embody the core idea of our new algorithm. Astute readers can now grasp how our algorithm functions and how it functions correctly. By treating all $d$-th order monomials as vertices of an undirected graph, and by summing over all monomials corresponding to pairs of vertices within each connected component of the graph, we obtain permutation-invariant polynomials. The following text is divided into four parts: 1) defining some symbols and rigorously discussing how the permutation action of the permutation group of atomic positions "transfers" to atomic distances; 2) specifically introducing the process of obtaining permutation-invariant polynomials by monomial symmetrization accomplished by generators; 3) discussing the problem of generating elements of the permutation group of identical atoms in molecular systems; 4) discussing how to remove redundancy from permutation-symmetric polynomials to obtain sets of descriptors such as fundamental invariants.



\subsection{Symbols, Concepts, and the Action from the Permutation Group of Identical Atoms}

Suppose there is a N-atom system with arbitrary permutation symmetry i.e. its potential keeps invariable under the action of permutation of identical atoms or molecules. Such action must be a subgroup $\mathbf{H}$ of permutation group $S_N$. And it naturally induces an action of bond lengths i.e. atom distances. We denote atom distances as $r_{ij}$ . They are not invariable under action of $\mathbf{H}$, even though they are constant under rotation and translation. To construct potential energy surface which is invariable under all the rotation, translation and permutation, permutation invariable polynomials of bond length is a well-performed descriptor set in small system. Now we should begin with some basic notations and concepts.
\paragraph{Definitions 2.1.1\\} 

Bond length actually is a partition of set $R^{'}=\lbrace {r_{ij}\ |\ 1 \leq {i,j} \leq N, i \neq j}\rbrace$. Let $r_{ij} \sim r_{ji}$, we get a partition (quotient class) $\overline{r_{ij}}=\lbrace{r_{ij},r_{ji}}\rbrace\subset R^{'}$, denoted as $R$.

Let $P=\mathbb{Q}[R]$ be the ring of polynomial in $R$ over $\mathbb{Q}$, and then define $P_d =\lbrace  {f \in P\ | \ deg(f) = d}\rbrace$. Define the homogeneous polynomial set $H = \lbrace  {f \in P\ | f\ is\ homogeneous\  and\ monic}\rbrace$ and $H_d = H \cap P_d$. Define the monomial set $M = \lbrace  {f \in H\ | f\ is\ monomial}\rbrace$ and $M_d = M \cap H_d$.

Obviously,
$$M=\bigcup^{\infty}_{d=0}{M_d}$$
$$P=\bigcup^{\infty}_{d=0}{P_d}$$
$$H=\bigcup^{\infty}_{d=0}{H_d}$$
$$R \subset	M_1 \subset H_1\subset	P_1, \qquad M_d \subset H_d \subset P_d $$
$$R \subset	M \subset H\subset	P$$

Define the permutation group of $P$, $H$, $M$, $R$ are $S_P$, $S_H$, $S_M$, $S_R$. And define the permutation group of all N atoms is $S_N$. We have
$$\left| R^{'}\right| = \frac{N(N-1)}{2}=N_R$$
$$\left| M_d\right|=\tbinom{N_R + d - 1}{d}$$

\paragraph{Definitions 2.1.2 Polynomial as a set of Monomials\\}

Any polynomial $f\in P$ is a linear combination of monomials in $M$, that is $f=\sum_{m\in M} mC^{m}_{f}$. We denote $\mathcal{S}(f)$ as a subset of $M$ that is $\mathcal{S}(f) = \left\{m\in M| C^{m}_{f} \neq 0\right\}$.

\paragraph{Definitions 2.1.3 Action of $S_N$ on $R$\\}

For $\overline{r_{ij}}\in\ R,\ s \in S_N$, define $\ s(\overline{r_{ij}}) = s\cdot \overline{r_{ij}} = \overline{r_{s(i)s(j)}}$.  If $i\neq j$, then $s(i)\neq s(j)$ and then $s$ maps any element of $R$ into $R$.

\paragraph{Proposition 2.2.1  Action of $S_N$ on $R$ is a well-defined action which induces a homomorphism from $S_N$ to $S_R$\\}

$\bf{PROOF}$ 
(1) Action of Identical element: $Id|_{S_N}(\overline{r_{ij}}) = \overline{r_{Id|_{S_N}(i)Id|_{S_N}(j)}} = \overline{r_{ij}}$; (2) Associative law of the action: $\forall s_1, s_2 \in S_N,\ (s_1s_2)(\overline{r_{ij}}) = \overline{r_{(s_1s_2)(i)(s_1s_2)(j)}}=s_1(\overline{r_{s_2(i)s_2(j)}})=s_1(s_2(\overline{r_{ij}}))$.

\paragraph{Proposition 2.2.2 Let $f:\ S_N \longrightarrow S_R$ denote the homomorphism induced by the action of $S_N$ on $R,\ ker(f) = Id|_{S_N}$ , when $N \geq 3$.\\}

$\bf{PROOF}$ For $a\in S_N,\ a \neq \ Id|_{S_N}$, there must be an index $i$ that $a(i) \neq i$, otherwise $a=Id|_{S_N}$.Define $b = f(a)$. Because $N \geq 3$, we choose another two indices $j,\ k$ that $i\neq j,\  j\neq k,\ k \neq i$.If $b(\overline{r_{ij}})\neq\overline{r_{ij}}$, $b \neq Id|_{S_P}$, else $b(\overline{r_{ij}})=\overline{r_{ij}}$. There must be $a(i) = j, \ a(j) = i$, and then $b(\overline{r_{ik}}) = \overline{r_{ja(k)}} \neq \overline{r_{ik}}$, since $j\neq i,\  j\neq k$. Thus $b \neq Id|_{S_P}$. Thus $b=f(a) \neq Id|_{S_P}$ i.e. $ker(f) = Id|_{S_N}\bf{}$. 

\paragraph{Definitions 2.2.3 Action of $S_N$ on $M$, $H$, $P$\\}

Action of $S_N$ on $R$ induces the action on $M$. $For\ m=\prod_{k=1}^Mx_k,\  x_k = \overline{r_{ij}}\in\ R \ and\ s \in\ S_N$
$$s(m) = \prod_{k=1}^Ms(x_k)$$
Action of $S_N$ on $M$ induces the action on $P$, $H$. $For\ f=\sum_{k=1}^Mc_km_k,\  m_k = \prod_{k=1}^Mx_k\in\ M \ and\ s \in\ S_N$
$$s(f)=\sum_{k=1}^Mc_ks(m_k)$$
\paragraph{Proposition 2.2.4 The action of $S_N$ and any of its subgroups $H \leq S_N$ on $P$, $H$, $M$, $R$ is faithful, when $N \geq 3$.\\}
$\bf{PROOF}$ Action can be regarded as a homomorphism $f$ from the group to the permutation group of acted set. When the map is injective i.e. $ker(f)=Id$, the action is faithful. By $\bf{Proposition\ 1.2.2}$ The action of $S_N$ on $R$ is faithful. If there is a set $X \subset Y$ with an action of a group $G$ on $Y$, and $X$ is close under the action. If action of $G$ on $X$ is faithful, then action of $G$ on $Y$ is faithful. Because  $R \subset	M\subset	H \subset	P$, the action of $S_N$ on $P$, $H$, $M$, $R$ is faithful. The action of a group is faithful, then the action of all of its subgroup is faithful. Thus the action of $H$ is faithful.

\paragraph{Definitions 2.3.1 Monomial Order of $M$\\}
A monomial order is a given total order of a monomial set. There are diverse proper definitions of monomial order, and which one is adopted depends on demand. In this work, we choose the graded lexicographic monomial ordering. By a monomial order, we can sort
the formation of a polynomial $f\in P$. Then we write leading monomial of $f$ as $LM\left(f\right)$ and leading coefficient of $f$ as $LC\left(f\right)$, and then leading term of $f$ as $LT\left(f\right)$. 




%\section{New Algorithm of Construction the Action of Reynold Operator}

\subsection{Monomial Symmetrization and the Shortest Invariant Polynomial(SIP)}

%\paragraph{3.1 Monomial Symmetrization and the Shortest Invariant Polynomial(SIP)\\}
Given a monimial $m_d\in M_d$, and a group $G\subset S_N$, $m_d$ must be in an orbit $orbit\left(m_d\right)$ which has length of $\left|orbit\left(m_d\right)\right|$. Define $G\left(m_d\right)=\sum_{m\in orbit\left(m_d\right)}m$. $G\left(m_d\right)$ is invariant under $G$: for $h\in G$, $hG\left(m_d\right)=\sum_{m\in orbit\left(m_d\right)}hm=\sum_{m\in h(orbit\left(m_d\right))}m=\sum_{m\in orbit\left(m_d\right)}m$. And it is shortest invariant polynomial containing $m_d$: $\forall f\in P$ that is $\forall g \in G,\ gf=f$ and $m_d \in \mathcal{S}(f)$ there must be $\mathcal{S}\left((G\left(m_d\right)\right)\subset\mathcal{S}(f)$. Otherwise, $f$ can not be invariant under $G$. 

Given an action of $G$, there is an action of so-called Reynold type operator ${Rey}_G\left(m_d\right)=\sum_{g\in G}g\left(m_d\right)$. After the action, the monimial ${Rey}_G\left(m_d\right)$ became an invariant polynomial under $G$: for $h\in G$, $h{Rey}_G\left(m_d\right)=\sum_{g\in G}hg\left(m_d\right)=\sum_{h^{-1}j\in G}j\left(m_d\right)=\sum_{j\in hG}j\left(m_d\right)=\sum_{j\in G}j\left(m_d\right)$. And we have ${Rey}_G\left(m_d\right)=\frac{\left|G\right|}{\left|orbit\left(m_d\right)\right|}\sum_{m\in orbit\left(m_d\right)}m$.
$\newline$



Just as the proposition 1.2 implies, we can regard the monomial set $M_d$ as a vertices set $\mathcal{V}_d$ of a graph $\mathcal{G}_d$ i.e. for $m_1,\ m_2 \in M_d$, there is $m_1,\ m_2 \in \mathcal{G}_d$ too. Suppose there is a group $G \leq S_N$ with its generation set $G_s$, they can act on polynomials as we defined previously. Then we could construct the edges of $\mathcal{G}_d$ by following method: if $\exists g_s \in G_s g_s\left(m_1\right) = m_2$, then add an edge $\left(m_1,\ m_2\right)$ in the set of edges $\mathcal{E}_d$. After the addition, we get a complete graph $\mathcal{G}_d$. By the connectivity judgement, the $\mathcal{G}_d$ would divorce into shards of connected subgraphs $\mathcal{G}_{ds},\ s\ = 0,\ 1,\ 2, \dots$. We assert that the sum of all monomial of a subgraph $p = \sum_{m_i\in \mathcal{G}_{ds}}m_i$ is an invariant under action of $G$.

\paragraph{Proposition 3.1 $p = \sum_{m_i\in \mathcal{G}_{ds}}m_i$ is an invariant under action of $G$, and it will not be sum of two monic homogeneous invariant polymomials of degree $d$ i.e. $p\neq f_1+f_2$, in other words, it is the shortest invariant polynomial containing its monomials.\\}
$\bf{PROOF}$ By proposition 1.2 and 3.1.
%$\bf{PROOF}$ According to proposition 2.1.1, the first part of this assertion is true if it is} invariant under action of its generation set $G_s$. $\forall g_s \in G_s,\forall\ m_1\in \mathcal{G}_{ds},\ g_s(m_1) = m_2\in M_d$, then $m_2 \in \mathcal{G}_{ds}$ must be true because there is an edge $\left(m_1,\ m_2\right)$ between these two monomials, then they are in the same shard of connected subgraph $\mathcal{G}_{ds}$. Thus the action of $g_s$ is a map $f:\ \mathcal{G}_{ds}\to\mathcal{G}_{ds}$. The action of $S_N$ is faithful, so does $G$ and $G_s$. Thus the map $f$ is injective and then bijective by the fact that $\mathcal{G}_{ds}$ is a finite set. Finally we get $g_s(p) = p$. If $p=f_1+f_2$ and $f_1 \neq 0, f_2 \neq 0$ and they're both monic. Then $LM\left(f_1\right)\neq LM\left(f_2\right)$, otherwise $LC\left(p\right)=2$. What's more $\mathcal{S}(f_1)\cap\mathcal{S}(f_2)=\emptyset$ by the similar reason. $LM\left(f_1\right),\ LM\left(f_2\right) \in \mathcal{G}_{ds}$, they are in the same connected subgraph, thus there is a connect path between $LM\left(f_1\right)$ and $LM\left(f_2\right)$. In other words $\exists g \in G$, $g = g_{s1}g_{s2}\cdots g_{sn},\ g(LM\left(f_1\right)) = LM\left(f_2\right)$, thus $g(f_1)\neq f_1$, $f_1$ is not invariant which is a contradiction.

 
%$$\exists$$
 
If we make a connectivity judgment on the set $M_d$, the number of vertices is $\left| M_d\right|$, and the upper bound of the degree of a vertex is the number of group generators $\left| G_s\right|$ which is a constant for the order of the polynomial. Suppose those monomials are contained in a sequence list by some monomial order, then it takes $O(ln(\left| M_d\right|)d)$ to locate each monomial in their sequence list. The factor $d$ comes form that it takes $O(ln(\left| M_d\right|)d)$ to compare the monomial order of order d. Thus the time complexity to build such graph $\mathcal{G}_d$ is $O(ln(\left| M_d\right|) d\left| M_d\right|\left|G_s\right|)$, slightly higher than the time complexity of $O(\left| M_d\right|\left| G_s\right|)$ making connectivity judgments. Furthermore, we must remind that it is possible to determine the connectivity of the graph $\mathcal{G}_d$ during its construction process, thus eliminating the necessity to store every edge of the graph. 



We will see $\left| G_s\right|$ grows almost linearly as atom amount $N$ grows, thus it leads to a trivial burden. However, $\left| M_d\right|=\tbinom{N_R + d - 1}{d}$ grows almost exponentially as $d$ grows. Thus our algorithm faces essential difficulties when dealing with high-order permutation-invariant polynomials, although there are some strategies described below that can alleviate this situation. Anyway we have a method to construct all $d$ degree homogeneous invariant polynomials through connectivity judgment. The next two problems we face is: for an actual molecular system, how to find the generator set of the permutation group; how to obtain the generator set of the permutation invariant polynomial ring after constructing the overall permutation invariant polynomial.

\subsection{Generator Set of the Permutation Group of a Molecular System}


Permutation of identical atoms or molecules of a N-atom system forms a subgroup $\mathbf{H}$ of the permutation group $S_N$. Initially, we only consider the permutation of identical atoms. Assume that there are $X$ kinds of identical atoms and $Ni$ atoms of each kind. Then there is $\sum_{i=1}^XN_i=N$. All the permutation operation of identical atoms of the same kind can be regarded as an independent permutation group $S_{N_i}^\prime$. This group is isomorphic to a certain subgroup of $S_N$ or literally $S_{N_i}^\prime \leq S_N$ and $\mathbf{H} = \prod_{i=1}^XS_{N_i}^\prime$. For the reason that each $S_{N_i}^\prime$ operate on completely different atom subsets (subsets without intersection), $S_{N_i}^\prime \cap S_{N_j}^\prime = {Id}_{S_N}$ when $i \neq j$ and when $a \in S_{N_i}^\prime,\ b\in S_{N_j}^\prime,\ i \neq j$, we have $ab=ba$. It follows that $S_{N_i}^\prime \lhd \mathbf{H}$ and then $\mathbf{H} = \prod_{i=1}^XS_{N_i}^\prime=\oplus_{i=1}^XS_{N_i}^\prime$ as proposition 1.4. If we define $\mathfrak{Ge}\left(G^\prime\right)$ as a proper generator set of $G^\prime$, then $\cup_{i=1}^X\mathfrak{Ge}\left(S_{N_i}^\prime\right)$ is a generator set of $\mathbf{H}$. If we choose generator set by the method mentioned after proposition 1.3, then $\left|\cup_{i=1}^X\mathfrak{Ge}\left(S_{N_i}^\prime\right)\right| = \sum_{i=1}^X(N_i-1)= N-X$. 

When many-body expansion is used to fit intermolecular interactions, the exchange symmetry of identical atoms $\mathbf{H}$ will be broken into the combination of the permutation symmetry of identical molecules $\mathbf{H_{inter}}$ and the intramolecular permutation symmetry $\mathbf{H_{intra}}$. In other words $\mathbf{H}=\left<\mathbf{H_{intra}}, \mathbf{H_{inter}}\right>$. Sometimes in order to speed up calculations by subtracting some uninteresting redundant symmetries when studying large-scale systems, molecular permutation symmetries are also used. The MFI method was invented for such scenarios. Suppose there is a system of N atoms, in which there are $Y$ kinds of molecules, the amount of $k$-th molecules is $Y_k$. We label each molecule of such system as $\left[k,j\right]$ for the j-th molecule of k-th kind. Then we define $N_{ki}$ as the amount of the i-th identical atoms of k-th kind. We have $\sum_{k=1}^Y(Y_k\sum_{i=1}^XN_{ki}) = N$ and $\sum_k^YY_kN_{ki}=N_i$. We define $S_{j{N_{ki}}}^\prime$ the intramolecular permutation subgroup of the j-th molecule of k-th kinds of molecoles and the i-th identical atom by the same way with aforementioned method. If follows that $\mathbf{H_{kj}}=\prod_{i=1}^X S_{j{N_{ki}}}^\prime$ be the intramolecular permutation group of molecule $\left[k,j\right]$. For all $j$ with the same $k$, their permutation group $\mathbf{H_{kj}}$ are isomorphic to each other. Obviously, $\mathbf{H_{intra}}=\prod_{k}\prod_{j}\mathbf{H_{kj}}$ is the total group of atom permutation. For the same reasons as above $\mathbf{H_{intra}}=\oplus_{k}\oplus_{j}\mathbf{H_{kj}}$. And then generator set of $\mathbf{H_{intra}}$ is a union of all the generator set of $\mathbf{H_{kj}}$. Actually it is $\cup_{k=1}^Y\cup_{j=1}^{Y_K}\mathfrak{Ge}\left(\mathbf{H_{kj}}\right) = \cup_{k=1}^Y\cup_{j=1}^{Y_K}\cup_{i=1}^{X}\mathfrak{Ge}\left(S_{j{N_{ki}}}^\prime\right)$.


As for $\mathbf{H_{inter}}$, the permutation subgroup of $Y_k$ identical molecules (is the k-th kind molecule of the N-atom system) is isomorphic to a subgroup of $S_N$ just as intramolecular permutation symmetry subgroup $S_{N_i}^\prime$ is. Thus we denote such subgroup as $S_{Y_k}^{\prime\prime}$. And for the same reasons as above, $\mathbf{H_{intra}}=\prod_{k}S_{Y_k}^{\prime\prime}=\oplus_{k}S_{Y_k}^{\prime\prime}$, videlicet, $\cup_{k=1}^Y\mathfrak{Ge}\left(S_{Y_k}^{\prime\prime}\right)$ is a generator set of $\mathbf{H_{intra}}$. Then we could extract generator set of $\mathbf{H_{inter}}$ just as $\mathbf{H_{intra}}$. Eventually we got a generator set of the entire system which is $\left(\cup_{k=1}^Y\cup_{j=1}^{Y_K}\cup_{i=1}^{X}\mathfrak{Ge}\left(S_{j{N_{ki}}}^\prime\right)\right)\cup\left(\cup_{k=1}^Y\mathfrak{Ge}\left(S_{Y_k}^{\prime\prime}\right)\right)$.

It is worth noting that existence of $\mathbf{H_{intra}}$ converts many elements of $\mathcal{Ge}\left(H_{inter}\right)$ into redundancy. All the $\mathbf{H_{kj}}$ that $j != 1$ could be constructed by $\mathbf{H_{k1}}$ and $\mathbf{H_{intra}}$. Thus $\left(\cup_{k=1}^Y\cup_{i=1}^{X}\mathfrak{Ge}\left(S_{1{N_{ki}}}^\prime\right)\right)\cup\left(\cup_{k=1}^Y\mathfrak{Ge}\left(S_{Y_k}^{\prime\prime}\right)\right)$ is sufficient for the system in question and it is obvious that the order of such set is less than $N$.

\subsection{Fundamental Invariant Construction from Monomial Symmetrization}

 Amount of invariant polynomials from monomial symmetrization(IPMS) inflates rapidly as the polynomial degree cutoff $d$ and system size $N$ grow. Adopting fundamental invariant (FI) as a effective substitute could significantly reduce the number of polynomials.
 
 FI is the minimal generation set of invariant polynomial ring ${K^\mathbf{H}\left[r\right]}$ as well as a subset of invariant polynomials from monomial symmetrization. (It is worth noting that generation set of a ring is a different concept from generation set of a group or an ideal.) There is no fixed method for selecting FI as generators from those invariant polynomials, just as there is for selecting a set of bases from a linear space. After construction of all invariant polynomials formula until degree $d$, the method we adopted to choose FI from IPMS is straightforward and even to be clumsy. It is done by mathematical induction. Initially, all the IPMS of order one is in the generation set of invariant polynomial ring, choose all of them as FI. And then suppose we have constructed all FIs whose order is less than $d$ and all IPMS of order $d$. We denote the FIs set as $F_{d-1}=\left\{f_{i}|deg\left(f_{i}\right)\leq d-1\right\}$. Continued product of $f_{i}$ or a monomial of $f_{i}$, we denote it as $\prod_if_{i}^{n_i}$ which is also homogeneous permutation invariant and can be expressed as linear combination of many IPMS. Thus the set $C_d=\left\{c=\prod_if_i^{n_i}|deg\left(c\right)=d,\ f_i\in F_{d-1}\right\}$ is a set of constrains of IPMS of order $d$. They will form a linear equation $ZP=C$, $Z$ is a matrix of natural number, $P$ denotes all the interested IPMS, and $C$ is all the polynomials $c_{di}\in C_d$. The row of matrix $Z$ is $\left|C_d\right|$ and the column is amount of interested IPMS of order $d$ and we denote it as $P_d$. If $rank\left(Z\right)=P_d$, the equation as one solution all the IPMS are linear combination of polynomials of some $c_{di}$, so none of them are new FIs. Otherwise $rank\left(Z\right)<P_d$, we can choose $P_d-rank\left(Z\right)$ linearly independent IPMS as new FIs of degree $d$.
 
As the degree $d$ grows, $\left|F\right|$ and then $\left|C\right|$ expands massively, leading to a significant burden of solving such equation. There is a method based on fundamental invariant of order one could relieve such burden. We define $C^\prime_d=\left\{c=\prod_if_i^{n_i}|deg\left(c\right)=d,\ f_i\in F_1\right\}$. Any IPMS or FI $p$ must belong to a certain $c_{di} \in C^\prime_d$ i.e. $\mathcal{S}(p) \subset\mathcal{S}(c_{di})$. For the reason that (1): $c_{di}$ is invariant under action of $\mathbf{H}$; (2):  $\mathcal{S}(c_{di})\cap \mathcal{S}(c_{dj})=\emptyset$, when $i\neq j$; (3): $\cup_{c_{di}\in C^\prime_d}\mathcal{S}(c_{di})=M_d$. Denote the $c_{di}$ that a certain IPMS or FI $p$ of degree $d$ belongs to as $\mathcal{C}(p)$. The set $C^\prime_d$ materially provides a division of IPMS of order $d$. In the process that generation of IPMS, we can perform connectivity judgement in each $c_{di}$ instead of the whole $M_d$. Moreover, $C^\prime_d$ is valid for shrinkage of consumption of the linear equation $ZP=C$ by partition strategy determined on $c_{di}$. For a certain $c_{di}$, firstly define the set $F(c_{di})=\left\{f_i\in F_d|\ \exists c_{kj},\ \mathcal{C}(f_i)c_{kj}=c_{di}\right\}$ and then $C(c_{di})=\left\{c=\prod_if_i^{n_i}|deg\left(c\right)=d,\ f_i\in F(c_{di})\right\}$. There is $C(c_{di})\subset C_d$, and $C(c_{di})$ contains exactly all the constraints for FIs selection of the IPMS belonging to $c_{di}$. Thus relying on partition of $M_d$ by $c_i$ and partition of $C_d$ by $C(c_{di})$, we can construct a partition of linear equation $ZP=C$ which is denoted as $Z(di)P(di)=C(di)$. Dimension of $Z(di)$ is significantly less than $Z$. Solving all the $Z(di)P(di)=C(di)$ will be remarkably faster than solving the entire $ZP=C$ for the reason that time consumption of a linear equation is cubic of matrix dimension.

\subsection{A more detailed sample of this algorithm on $\text{Mg}_4$}

The symmetry group of $\text{Mg}_4$ is $S_4$, which has $4!=24$ elements. Its minimal generator set has two elements $a=(12)$ and $b=(1234)$. Their actions on the corresponding bondlength set are:
$$a=\begin{pmatrix} 
R_{1,2} & R_{1,3} & R_{1,4} & R_{2,3} & R_{2,4} & R_{3,4}\\
R_{1,2} & R_{2,3} & R_{2,4} & R_{1,3} & R_{1,4} & R_{3,4} 
\end{pmatrix}$$
$$b=\begin{pmatrix} 
R_{1,2} & R_{1,3} & R_{1,4} & R_{2,3} & R_{2,4} & R_{3,4}\\
R_{2,3} & R_{2,4} & R_{1,2} & R_{3,4} & R_{1,3} & R_{1,4} 
\end{pmatrix}$$. 
Without loss of performance, we adopted a simpler generator set in the program, which has three elements $g_1=(1,2)$, $g_2=(1,3)$ and $g_3=(1,4)$.
Their actions on the corresponding bondlength set are:
$$g_1=\begin{pmatrix} 
R_{1,2} & R_{1,3} & R_{1,4} & R_{2,3} & R_{2,4} & R_{3,4}\\
R_{1,2} & R_{2,3} & R_{2,4} & R_{1,3} & R_{1,4} & R_{3,4} 
\end{pmatrix}$$
$$g_2=\begin{pmatrix} 
R_{1,2} & R_{1,3} & R_{1,4} & R_{2,3} & R_{2,4} & R_{3,4}\\
R_{2,3} & R_{1,3} & R_{3,4} & R_{1,2} & R_{2,4} & R_{1,4} 
\end{pmatrix}$$. 
$$g_3=\begin{pmatrix} 
R_{1,2} & R_{1,3} & R_{1,4} & R_{2,3} & R_{2,4} & R_{3,4}\\
R_{2,4} & R_{3,4} & R_{1,4} & R_{2,3} & R_{1,2} & R_{1,3} 
\end{pmatrix}$$. 
As mention before, there is no unique choice of generator set. The later one was chosen because the three elements are all of order two. Once we have one of the generator set of the $\text{Mg}_4$,  we can produce the polynomial of degree one. The six monomials of degree one are internuclear distances themselves. We can regard them as vertices of a graph. 
If there is one generator that transforms a monomial $m_1$ to another one $m_2$, we can add an edge between them. Once all the generators have been applied to all the vertices, the result is an undirected graph. 

\begin{figure}[htbp]
    \centering
    \includegraphics[scale=0.64]{graph/order_1.pdf}
%    \includegraphics[scale=0.0625]{1_15.png}
    \caption{The connected components of order one, within undirected graphs by the two generator sets.}
    \label{fig:order_1}
\end{figure}

The upper part of Figure \ref{fig:order_1} shows the corresponding graph resulting from the action of generator set $\{a=(12), b=(1234)\}$ on the 6 monomials of degree one, and the lower part shows the corresponding graph resulting from the action of the generator set $\{g_1=(1,2), g_2=(1,3), g_3=(1,4)\}$. Different choices of generator set lead to different resulting undirected graphs, but the connected components of the different undirected graphs remain unaltered. After summing all the monomials within the same connected component, all the invariant polynomials of degree one will be constructed. In the case of $\text{Mg}_4$, there is only one connected component in the undirected graph of degree one monomials. Thus, there is only one invariant polynomial of degree one, which is $f_{1,1}=R_{1,2} + R_{1,3} + R_{1,4} + R_{2,3} + R_{2,4} + R_{3,4}$. Connectivity judgment is done through DFS or BFS. 

\begin{figure}[htbp]
    \centering
    \includegraphics[scale=0.56]{graph/order_2.pdf}
%    \includegraphics[scale=0.0625]{1_15.png}
    \caption{The 3 connected components of order two in undirected graphs by the generator set $\{g_1, g_2, g_3\}$.}
    \label{fig:order_2}
\end{figure}

Now we can repeat the same process for all the monomials of degree two. 
$\text{Mg}_4$ contains 21 monomials of degree two, which are represented as vertices in a graph. A generator set is chosen to act on these vertices, and the results of the group action are used to construct a graph. Figure \ref{fig:order_2} illustrates the corresponding graph generated by the action of the generator set ${g_1=(1,2), g_2=(1,3), g_3=(1,4)}$. The resulting graph consists of three distinct connected components.
The corresponding polynomials are:
$$f_{2,1}=R^2_{1,2} + R^2_{1,3} + R^2_{1,4} + R^2_{2,3} + R^2_{2,4} + R^2_{3,4}$$
$$f_{2,2}=R_{1,2}R_{1,3} + R_{1,2}R_{1,4} + R_{1,2}R_{2,3}+R_{1,2}R_{2,4} + R_{1,3}R_{1,4} + R_{1,3}R_{2,3}$$
$$+R_{1,3}R_{3,4} + R_{1,4}R_{2,4} + R_{1,4}R_{3,4} + R_{2,3}R_{2,4} + R_{2,3}R_{3,4}+ R_{2,4}R_{3,4}$$
$$f_{2,3}=R_{1,2}R_{3,4} + R_{1,3}R_{2,4} + R_{1,4}R_{2,3}$$
Different choices of the generator set result in different undirected graphs. However, the connected components of these graphs remain unchanged. A linear constraint arises from the invariant polynomial of degree one:
$$f_{2,1}+2f_{2,2}+2f_{2,3}=f^2_{1,1}$$.
Thus, only two of the three degree-two polynomials are independent, and any two can be chosen. This independence can be established by solving the indeterminate linear equation. 
By iteratively applying the steps described above and using mathematical induction on the polynomial degree, one can systematically derive invariant polynomials of any desired degree.








\bibliography{ref}

\end{document}
