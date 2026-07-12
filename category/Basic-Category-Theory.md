Basic Category Theory

TOM LEINSTER

University of Edinburgh

First published as Basic Category Theory, Cambridge Studies in Advanced Mathematics, Vol. 143, Cambridge University Press, Cambridge, 2014. ISBN 978-1-107-04424-1 (hardback).

Information on this title:

http://www.cambridge.org/9781107044241

© Tom Leinster 2014

This arXiv version is published under a Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International licence (CC BY-NC-SA 4.0).

Licence information:

https://creativecommons.org/licenses/by-nc-sa/4.0

© Tom Leinster 2014, 2016

## Preface to the arXiv version

This book was first published by Cambridge University Press in 2014, and is now being published on the arXiv by mutual agreement. CUP has consistently supported the mathematical community by allowing authors to make free versions of their books available online. Readers may, in turn, wish to support CUP by buying the printed version, available at http://www.cambridge.org/ 9781107044241.

This electronic version is not only free; it is also freely editable. For instance, if you would like to teach a course using this book but some of the examples are unsuitable for your class, you can remove them or add your own. Similarly, if there is notation that you dislike, you can easily change it; or if you want to reformat the text for reading on a particular device, that is easy too.

In legal terms, this text is released under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International licence (CC BY-NC-SA 4.0). The licence terms are available at the Creative Commons website, https:// creativecommons.org/licenses/by-nc-sa/4.0. Broadly speaking, the licence allows you to edit and redistribute this text in any way you like, as long as you include an accurate statement about authorship and copyright, do not use it for commercial purposes, and distribute it under this same licence.

In technical terms, all you need to do in order to edit this book is to download the source files from the arXiv and use LATEX (or pdflatex) in the usual way.

This version is identical to the printed version except for the correction of a small number of minor errors. Thanks to all those who pointed these out, including Martin Brandenburg, Miguel Couto, Bradley Hicks, Thomas Moeller, and Yaokun Wu.

Tom Leinster, December 2016

## Contents

Note to the reader page vii

Introduction 1

1 Categories, functors and natural transformations 9

1.1 Categories 10

1.2 Functors 17

1.3 Natural transformations 27

2 Adjoints 41

2.1 Definition and examples 41

2.2 Adjunctions via units and counits 50

2.3 Adjunctions via initial objects 58

3 Interlude on sets 65

3.1 Constructions with sets 66

3.2 Small and large categories 73

3.3 Historical remarks 78

4 Representables 83

4.1 Definitions and examples 84

4.2 The Yoneda lemma 93

4.3 Consequences of the Yoneda lemma 99

5 Limits 107

5.1 Limits: definition and examples 107

5.2 Colimits: definition and examples 126

5.3 Interactions between functors and limits 136

6 Adjoints, representables and limits 142

6.1 Limits in terms of representables and adjoints 142

6.2 Limits and colimits of presheaves 146

6.3 Interactions between adjoint functors and limits 158

Appendix Proof of the general adjoint functor theorem 171

Further reading 174

Index of notation 177

Index 178

## Note to the reader

This is not a sophisticated text. In writing it, I have assumed no more mathematical knowledge than might be acquired from an undergraduate degree at an ordinary British university, and I have not assumed that you are used to learning mathematics by reading a book rather than attending lectures. Furthermore, the list of topics covered is deliberately short, omitting all but the most fundamental parts of category theory. A 'further reading' section points to suitable follow-on texts.

There are two things that every reader should know about this book. One concerns the examples, and the other is about the exercises.

Each new concept is illustrated with a generous supply of examples, but it is not necessary to understand them all. In courses I have taught based on earlier versions of this text, probably no student has had the background to understand every example. All that matters is to understand enough examples that you can connect the new concepts with mathematics that you already know.

As for the exercises, I join every other textbook author in exhorting you to do them; but there is a further important point. In subjects such as number theory and combinatorics, some questions are simple to state but extremely hard to answer. Basic category theory is not like that. To understand the question is very nearly to know the answer. In most of the exercises, there is only one possible way to proceed. So, if you are stuck on an exercise, a likely remedy is to go back through each term in the question and make sure that you understand it in full. Take your time. Understanding, rather than problem solving, is the main challenge of learning category theory.

Citations such as Mac Lane (1971) refer to the sources listed in 'Further reading'.

This book developed out of master's-level courses taught several times at the University of Glasgow and, before that, at the University of Cambridge. In turn, the Cambridge version was based on Part III courses taught for many years by Martin Hyland and Peter Johnstone. Although this text is significantly different from any of their courses, I am conscious that certain exercises, lines of development and even turns of phrase have persisted through that long evolution. I would like to record my indebtedness to them, as well as my thanks to François Petit, my past students, the anonymous reviewers, and the staff of Cambridge University Press.

## Introduction

Category theory takes a bird's eye view of mathematics. From high in the sky, details become invisible, but we can spot patterns that were impossible to detect from ground level. How is the lowest common multiple of two numbers like the direct sum of two vector spaces? What do discrete topological spaces, free groups, and fields of fractions have in common? We will discover answers to these and many similar questions, seeing patterns in mathematics that you may never have seen before.

The most important concept in this book is that of universal property. The further you go in mathematics, especially pure mathematics, the more universal properties you will meet. We will spend most of our time studying different manifestations of this concept.

Like all branches of mathematics, category theory has its own special vocabulary, which we will meet as we go along. But since the idea of universal property is so important, I will use this introduction to explain it with no jargon at all, by means of examples.

Our first example of a universal property is very simple.

Example 0.1 Let 1 denote a set with one element. (It does not matter what this element is called.) Then 1 has the following property:

for all sets $X$ , there exists a unique map from $X$ to 1 .

(In this context, the words 'map', 'mapping' and 'function' all mean the same thing.)

Indeed, let $X$ be a set. There exists a map $X \rightarrow  1$ , because we can define $f$ : $X \rightarrow  1$ by taking $f\left( x\right)$ to be the single element of 1 for each $x \in  X$ . This is the unique map $X \rightarrow  1$ , because there is no choice in the matter: any map $X \rightarrow  1$ must send each element of $X$ to the single element of 1 .

Phrases of the form 'there exists a unique such-and-such satisfying some condition' are common in category theory. The phrase means that there is one and only one such-and-such satisfying the condition. To prove the existence part, we have to show that there is at least one. To prove the uniqueness part, we have to show that there is at most one; in other words, any two such-and-suches satisfying the condition are equal.

Properties such as this are called 'universal' because they state how the object being described (in this case, the set 1) relates to the entire universe in which it lives (in this case, the universe of sets). The property begins with the words 'for all sets $X$ ', and therefore says something about the relationship between 1 and every set $X$ : namely, that there is a unique map from $X$ to 1 .

Example 0.2 This example involves rings, which in this book are always taken to have a multiplicative identity, called 1. Similarly, homomorphisms of rings are understood to preserve multiplicative identities.

The ring $\mathbb{Z}$ has the following property: for all rings $R$ , there exists a unique homomorphism $\mathbb{Z} \rightarrow  R$ .

To prove existence, let $R$ be a ring. Define a function $\phi  : \mathbb{Z} \rightarrow  R$ by

$$
\phi \left( n\right)  = \left\{  \begin{array}{ll} \frac{1 + \cdots  + 1}{n} & \text{ if }n > 0, \\  0 & \text{ if }n = 0, \\   - \phi \left( {-n}\right) & \text{ if }n < 0 \end{array}\right.
$$

$\left( {n \in  \mathbb{Z}}\right)$ . A series of elementary checks confirms that $\phi$ is a homomorphism.

To prove uniqueness, let $R$ be a ring and let $\psi  : \mathbb{Z} \rightarrow  R$ be a homomorphism. We show that $\psi$ is equal to the homomorphism $\phi$ just defined. Since homomorphisms preserve multiplicative identities, $\psi \left( 1\right)  = 1$ . Since homomorphisms preserve addition,

$$
\psi \left( n\right)  = \psi \left( \underset{n}{\underbrace{1 + \cdots  + 1}}\right)  = \underset{n}{\underbrace{\psi \left( 1\right)  + \cdots  + \psi \left( 1\right) }} = \underset{n}{\underbrace{1 + \cdots  + 1}} = \phi \left( n\right)
$$

for all $n > 0$ . Since homomorphisms preserve zero, $\psi \left( 0\right)  = 0 = \phi \left( 0\right)$ . Finally, since homomorphisms preserve negatives, $\psi \left( n\right)  =  - \psi \left( {-n}\right)  =  - \phi \left( {-n}\right)  = \phi \left( n\right)$ whenever $n < 0$ .

Crucially, there can be essentially only one object satisfying a given universal property. The word 'essentially' means that two objects satisfying the same universal property need not literally be equal, but they are always isomorphic. For example:

Lemma 0.3 Let $A$ be a ring with the following property: for all rings $R$ , there exists a unique homomorphism $A \rightarrow  R$ . Then $A \cong  \mathbb{Z}$ .

Proof Let us call a ring with this property ’initial’. We are given that $A$ is initial, and we proved in Example 0.2 that $\mathbb{Z}$ is initial.

Since $A$ is initial, there is a unique homomorphism $\phi  : A \rightarrow  \mathbb{Z}$ . Since $\mathbb{Z}$ is initial, there is a unique homomorphism ${\phi }^{\prime } : \mathbb{Z} \rightarrow  A$ . Now ${\phi }^{\prime } \circ  \phi  : A \rightarrow  A$ is a homomorphism, but so too is the identity map ${1}_{A} : A \rightarrow  A$ ; hence, since $A$ is initial, ${\phi }^{\prime } \circ  \phi  = {1}_{A}$ . (This follows from the uniqueness part of initiality, taking ’ $R$ ’ to be $A$ .) Similarly, $\phi  \circ  {\phi }^{\prime } = {1}_{\mathbb{Z}}$ . So $\phi$ and ${\phi }^{\prime }$ are mutually inverse, and therefore define an isomorphism between $A$ and $\mathbb{Z}$ .

This proof has very little to do with rings. It really belongs at a higher level of generality. To properly understand this, and to convey more fully the idea of universal property, it will help to consider some more complex examples.

Example 0.4 Let $V$ be a vector space with a basis ${\left( {v}_{s}\right) }_{s \in  S}$ . (For example, if $V$ is finite-dimensional then we might take $S = \{ 1,\ldots , n\}$ .) If $W$ is another vector space, we can specify a linear map from $V$ to $W$ simply by saying where the basis elements go. Thus, for any $W$ , there is a natural one-to-one correspondence between

linear maps $V \rightarrow  W$

and

functions $S \rightarrow  W$ .

This is because any function defined on the basis elements extends uniquely to a linear map on $V$ .

Let us rephrase this last statement. Define a function $i : S \rightarrow  V$ by $i\left( s\right)  = {v}_{s} \; \left( {s \in  S}\right)$ . Then $V$ together with $i$ has the following universal property:

![10_675_1332_275_149_0.jpg](images/10_675_1332_275_149_0.jpg)

This diagram means that for all vector spaces $W$ and all functions $f : S \rightarrow  W$ , there exists a unique linear map $\bar{f} : V \rightarrow  W$ such that $\bar{f} \circ  i = f$ . The symbol $\forall$ means 'for all', and the symbols $\exists$ ! mean 'there exists a unique'.

Another way to say ’ $\bar{f} \circ  i = f$ ’ is ’ $\bar{f}\left( {v}_{s}\right)  = f\left( s\right)$ for all $s \in  S$ ’. So, the diagram asserts that every function $f$ defined on the basis elements extends uniquely to a linear map $\bar{f}$ defined on the whole of $V$ . In other words still, the function is bijective.

$$
\{ \text{ linear maps }V \rightarrow  W\} \; \rightarrow  \;\{ \text{ functions }S \rightarrow  W\}
$$

$\bar{f}\; \mapsto  \;\bar{f} \circ  i$

Example 0.5 Given a set $S$ , we can build a topological space $D\left( S\right)$ by equipping $S$ with the discrete topology: all subsets are open. With this topology, any map from $S$ to a space $X$ is continuous.

Again, let us rephrase this. Define a function $i : S \rightarrow  D\left( S\right)$ by $i\left( s\right)  = s \; \left( {s \in  S}\right)$ . Then $D\left( S\right)$ together with $i$ has the following universal property:

![11_617_631_318_151_0.jpg](images/11_617_631_318_151_0.jpg)

In other words, for all topological spaces $X$ and all functions $f : S \rightarrow  X$ , there exists a unique continuous map $\bar{f} : D\left( S\right)  \rightarrow  X$ such that $\bar{f} \circ  i = f$ . The continuous map $\bar{f}$ is the same thing as the function $f$ , except that we are regarding it as a continuous map between topological spaces rather than a mere function between sets.

You may feel that this universal property is almost too trivial to mean anything. But if we change the definition of $D\left( S\right)$ - say from the discrete to the indiscrete topology, in which the only open sets are $\varnothing$ and $S$ - then the property becomes false. So this property really does say something about the discrete topology. What it says is that all maps out of a discrete space are continuous.

Indeed, given $S$ , the universal property determines $D\left( S\right)$ and $i$ uniquely (or rather, uniquely up to isomorphism; but who could want more?). The proof of this is similar to that of Lemma 0.3 above and Lemma 0.7 below.

Example 0.6 Given vector spaces $U, V$ and $W$ , a bilinear map $f : U \times  V \rightarrow \; W$ is a function $f$ that is linear in each variable:

$$
f\left( {u,{v}_{1} + \lambda {v}_{2}}\right)  = f\left( {u,{v}_{1}}\right)  + {\lambda f}\left( {u,{v}_{2}}\right) ,
$$

$$
f\left( {{u}_{1} + \lambda {u}_{2}, v}\right)  = f\left( {{u}_{1}, v}\right)  + {\lambda f}\left( {{u}_{2}, v}\right)
$$

for all $u,{u}_{1},{u}_{2} \in  U, v,{v}_{1},{v}_{2} \in  V$ , and scalars $\lambda$ . A good example is the scalar product (dot product), which is a bilinear map

$$
{\mathbb{R}}^{n} \times  {\mathbb{R}}^{n} \rightarrow  \mathbb{R}
$$

$$
\left( {\mathbf{u},\mathbf{v}}\right) \; \mapsto  \;\mathbf{u}.\mathbf{v}
$$

of real vector spaces. The vector product (cross product) ${\mathbb{R}}^{3} \times  {\mathbb{R}}^{3} \rightarrow  {\mathbb{R}}^{3}$ is also bilinear.

Let $U$ and $V$ be vector spaces. It is a fact that there is a ’universal bilinear map out of $U \times  V$ ’. In other words, there exist a certain vector space $T$ and a certain bilinear map $b : U \times  V \rightarrow  T$ with the following universal property:(0.1)

![12_670_454_287_150_0.jpg](images/12_670_454_287_150_0.jpg)

Roughly speaking, this property says that bilinear maps out of $U \times  V$ correspond one-to-one with linear maps out of $T$ .

Even without knowing that such a $T$ and $b$ exist, we can immediately prove that this universal property determines $T$ and $b$ uniquely up to isomorphism. The proof is essentially the same as that of Lemma 0.3, but looks more complicated because of the more complicated universal property.

Lemma 0.7 Let $U$ and $V$ be vector spaces. Suppose that $b : U \times  V \rightarrow  T$ and ${b}^{\prime } : U \times  V \rightarrow  {T}^{\prime }$ are both universal bilinear maps out of $U \times  V$ . Then $T \cong  {T}^{\prime }$ . More precisely, there exists a unique isomorphism $j : T \rightarrow  {T}^{\prime }$ such that $j \circ  b = {b}^{\prime }$ .

In the proof that follows, it does not actually matter what 'bilinear', 'linear' or even 'vector space' mean. The hard part is getting the logic straight. That done, you should be able to see that there is really only one possible proof. For instance, to use the universality of $b$ , we will have to choose some bilinear map $f$ out of $U \times  V$ . There are only two in sight, $b$ and ${b}^{\prime }$ , and we use each in the appropriate place.

Proof In diagram (0.1), take $\left( {U \times  V\overset{f}{ \rightarrow  }W}\right)$ to be $\left( {U \times  V\overset{{b}^{\prime }}{ \rightarrow  }{T}^{\prime }}\right)$ . This gives a linear map $j : T \rightarrow  {T}^{\prime }$ satisfying $j \circ  b = {b}^{\prime }$ . Similarly, using the universality of ${b}^{\prime }$ , we obtain a linear map ${j}^{\prime } : {T}^{\prime } \rightarrow  T$ satisfying ${j}^{\prime } \circ  {b}^{\prime } = b$ :

![12_709_1400_207_241_0.jpg](images/12_709_1400_207_241_0.jpg)

Now ${j}^{\prime } \circ  j : T \rightarrow  T$ is a linear map satisfying $\left( {{j}^{\prime } \circ  j}\right)  \circ  b = b$ ; but also, the identity map ${1}_{T} : T \rightarrow  T$ is linear and satisfies ${1}_{T} \circ  b = b$ . So by the uniqueness part of the universal property of $b$ , we have ${j}^{\prime } \circ  j = {1}_{T}$ . (Here we took the ’ $f$ ’ of (0.1) to be $b$ .) Similarly, $j \circ  {j}^{\prime } = {1}_{{T}^{\prime }}$ . So $j$ is an isomorphism.

In Example 0.6, it was stated that given vector spaces $U$ and $V$ , there exists a pair $\left( {T, b}\right)$ with the universal property of (0.1). We just proved that there is essentially only one such pair $\left( {T, b}\right)$ . The vector space $T$ is called the tensor product of $U$ and $V$ , and is written as $U \otimes  V$ . Tensor products are very important in algebra. They reduce the study of bilinear maps to the study of linear maps, since a bilinear map out of $U \times  V$ is really the same thing as a linear map out of $U \otimes  V$ .

However, tensor products will not be important in this book. The real lesson for us is that it is safe to speak of the tensor product, not just a tensor product, and the reason for that is Lemma 0.7. This is a general point that applies to anything satisfying a universal property.

Once you know a universal property of an object, it often does no harm to forget how it was constructed. For instance, if you look through a pile of algebra books, you will find several different ways of constructing the tensor product of two vector spaces. But once you have proved that the tensor product satisfies the universal property, you can forget the construction. The universal property tells you all you need to know, because it determines the object uniquely up to isomorphism.

Example 0.8 Let $\theta  : G \rightarrow  H$ be a homomorphism of groups. Associated with $\theta$ is a diagram

$$
\ker \left( \theta \right) \overset{\iota }{ \rightarrow  }G\underset{\varepsilon }{ \rightarrow  }H \tag{0.2}
$$

where $\iota$ is the inclusion of $\ker \left( \theta \right)$ into $G$ and $\varepsilon$ is the trivial homomorphism. ’Inclusion’ means that $\iota \left( x\right)  = x$ for all $x \in  \ker \left( \theta \right)$ , and ’trivial’ means that $\varepsilon \left( g\right)  = 1$ for all $g \in  G$ . The symbol $\hookrightarrow$ is often used for inclusions; it is a combination of a subset symbol $\subset$ and an arrow.

The map $\iota$ into $G$ satisfies $\theta  \circ  \iota  = \varepsilon  \circ  \iota$ , and is universal as such. Exercise 0.11 asks you to make this precise.

Here is our final example of a universal property.

Example 0.9 Take a topological space covered by two open subsets: $X = \; U \cup  V$ . The diagram

![13_670_1577_216_174_0.jpg](images/13_670_1577_216_174_0.jpg)

of inclusion maps has a universal property in the world of topological spaces and continuous maps, as follows:(0.3)

![14_644_418_332_278_0.jpg](images/14_644_418_332_278_0.jpg)

The diagram means that given $Y, f$ and $g$ such that $f \circ  i = g \circ  j$ , there is exactly one continuous map $h : X \rightarrow  Y$ such that $h \circ  {j}^{\prime } = f$ and $h \circ  {i}^{\prime } = g$ .

Under favourable conditions, the induced diagram

![14_662_846_299_188_0.jpg](images/14_662_846_299_188_0.jpg)

of fundamental groups has the same property in the world of groups and group homomorphisms. This is van Kampen's theorem. In fact, van Kampen stated his theorem in a much more complicated way. Stating it transparently requires some categorical language, but he was working in the 1930s, before category theory had been born.

You have now seen several examples of universal properties. As this book progresses, we will develop different ways of talking about them. Once we have set up the basic vocabulary of categories and functors, we will study adjoint functors, then representable functors, then limits. Each of these provides an approach to universal properties, and each places the idea in a different light. For instance, Examples 0.4 and 0.5 can most readily be described in terms of adjoint functors, Example 0.6 via representable functors, and Examples 0.1, 0.2, 0.8 and 0.9 in terms of limits.

## Exercises

0.10 Let $S$ be a set. The indiscrete topological space $I\left( S\right)$ is the space whose set of points is $S$ and whose only open subsets are $\varnothing$ and $S$ itself. Imitating Example 0.5, find a universal property satisfied by the space $I\left( S\right)$ .

0.11 Fix a group homomorphism $\theta  : G \rightarrow  H$ . Find a universal property satisfied by the pair $\left( {\ker \left( \theta \right) ,\iota }\right)$ of diagram (0.2). (This property can - indeed, must - make reference to $\theta$ .)

0.12 Verify the universal property shown in diagram (0.3).

0.13 Denote by $\mathbb{Z}\left\lbrack  x\right\rbrack$ the polynomial ring over $\mathbb{Z}$ in one variable.

(a) Prove that for all rings $R$ and all $r \in  R$ , there exists a unique ring homomorphism $\phi  : \mathbb{Z}\left\lbrack  x\right\rbrack   \rightarrow  R$ such that $\phi \left( x\right)  = r$ .

(b) Let $A$ be a ring and $a \in  A$ . Suppose that for all rings $R$ and all $r \in  R$ , there exists a unique ring homomorphism $\phi  : A \rightarrow  R$ such that $\phi \left( a\right)  = r$ . Prove that there is a unique isomorphism $\iota  : \mathbb{Z}\left\lbrack  x\right\rbrack   \rightarrow  A$ such that $\iota \left( x\right)  = a$ .

0.14 Let $X$ and $Y$ be vector spaces.

(a) For the purposes of this exercise only, a cone is a triple $\left( {V,{f}_{1},{f}_{2}}\right)$ consisting of a vector space $V$ , a linear map ${f}_{1} : V \rightarrow  X$ , and a linear map ${f}_{2} : V \rightarrow  Y$ . Find a cone $\left( {P,{p}_{1},{p}_{2}}\right)$ with the following property: for all cones $\left( {V,{f}_{1},{f}_{2}}\right)$ , there exists a unique linear map $f : V \rightarrow  P$ such that ${p}_{1} \circ  f = {f}_{1}$ and ${p}_{2} \circ  f = {f}_{2}$

(b) Prove that there is essentially only one cone with the property stated in (a). That is, prove that if $\left( {P,{p}_{1},{p}_{2}}\right)$ and $\left( {{P}^{\prime },{p}_{1}^{\prime },{p}_{2}^{\prime }}\right)$ both have this property then there is an isomorphism $i : P \rightarrow  {P}^{\prime }$ such that ${p}_{1}^{\prime } \circ  i = {p}_{1}$ and ${p}_{2}^{\prime } \circ  i = {p}_{2}$ .

(c) For the purposes of this exercise only, a cocone is a triple $\left( {V,{f}_{1},{f}_{2}}\right)$ consisting of a vector space $V$ , a linear map ${f}_{1} : X \rightarrow  V$ , and a linear map ${f}_{2} : Y \rightarrow  V$ . Find a cocone $\left( {Q,{q}_{1},{q}_{2}}\right)$ with the following property: for all cocones $\left( {V,{f}_{1},{f}_{2}}\right)$ , there exists a unique linear map $f : Q \rightarrow  V$ such that $f \circ  {q}_{1} = {f}_{1}$ and $f \circ  {q}_{2} = {f}_{2}$ .

(d) Prove that there is essentially only one cocone with the property stated in (c), in a sense that you should make precise.

## 1 Categories, functors and natural transformations

A category is a system of related objects. The objects do not live in isolation: there is some notion of map between objects, binding them together.

Typical examples of what 'object' might mean are 'group' and 'topological space', and typical examples of what 'map' might mean are 'homomorphism' and 'continuous map', respectively. We will see many examples, and we will also learn that some categories have a very different flavour from the two just mentioned. In fact, the 'maps' of category theory need not be anything like maps in the sense that you are most likely to be familiar with.

Categories are themselves mathematical objects, and with that in mind, it is unsurprising that there is a good notion of 'map between categories'. Such maps are called functors. More surprising, perhaps, is the existence of a third level: we can talk about maps between functors, which are called natural transformations. These, then, are maps between maps between categories.

In fact, it was the desire to formalize the notion of natural transformation that led to the birth of category theory. By the early 1940s, researchers in algebraic topology had started to use the phrase 'natural transformation', but only in an informal way. Two mathematicians, Samuel Eilenberg and Saunders Mac Lane, saw that a precise definition was needed. But before they could define natural transformation, they had to define functor; and before they could define functor, they had to define category. And so the subject was born.

Nowadays, the uses of category theory have spread far beyond algebraic topology. Its tentacles extend into most parts of pure mathematics. They also reach some parts of applied mathematics; perhaps most notably, category theory has become a standard tool in certain parts of computer science. Applied mathematics is more than just applied differential equations!

### 1.1 Categories

## Definition 1.1.1 A category $\mathcal{A}$ consists of:

- a collection ob $\left( \mathcal{A}\right)$ of objects;

- for each $A, B \in  \operatorname{ob}\left( \mathcal{A}\right)$ , a collection $\mathcal{A}\left( {A, B}\right)$ of maps or arrows or morphisms from $A$ to $B$ ;

- for each $A, B, C \in  \operatorname{ob}\left( \mathcal{A}\right)$ , a function

$$
\mathcal{A}\left( {B, C}\right)  \times  \mathcal{A}\left( {A, B}\right)  \rightarrow  \mathcal{A}\left( {A, C}\right)
$$

$$
\left( {g, f}\right) \; \mapsto  \;g \circ  f
$$

called composition;

- for each $A \in  \operatorname{ob}\left( \mathcal{A}\right)$ , an element ${1}_{A}$ of $\mathcal{A}\left( {A, A}\right)$ , called the identity on $A$ , satisfying the following axioms:

- associativity: for each $f \in  \mathcal{A}\left( {A, B}\right) , g \in  \mathcal{A}\left( {B, C}\right)$ and $h \in  \mathcal{A}\left( {C, D}\right)$ , we have $\left( {h \circ  g}\right)  \circ  f = h \circ  \left( {g \circ  f}\right)$ ;

- identity laws: for each $f \in  \mathcal{A}\left( {A, B}\right)$ , we have $f \circ  {1}_{A} = f = {1}_{B} \circ  f$ .

Remarks 1.1.2 (a) We often write:

$$
A \in  \mathcal{A}\text{ to mean }A \in  \operatorname{ob}\left( \mathcal{A}\right) \text{ ; }
$$

$$
f : A \rightarrow  B\text{ or }A\overset{f}{ \rightarrow  }B\;\text{ to mean }\;f \in  \mathcal{A}\left( {A, B}\right) ;
$$

$$
{gf}\text{ to mean }g \circ  f\text{ . }
$$

People also write $\mathcal{A}\left( {A, B}\right)$ as ${\operatorname{Hom}}_{\mathcal{A}}\left( {A, B}\right)$ or $\operatorname{Hom}\left( {A, B}\right)$ . The notation 'Hom' stands for homomorphism, from one of the earliest examples of a category.

(b) The definition of category is set up so that in general, from each string

$$
{A}_{0}\overset{{f}_{1}}{ \rightarrow  }{A}_{1}\overset{{f}_{2}}{ \rightarrow  }\cdots \overset{{f}_{n}}{ \rightarrow  }{A}_{n}
$$

of maps in $\mathcal{A}$ , it is possible to construct exactly one map

$$
{A}_{0} \rightarrow  {A}_{n}
$$

(namely, ${f}_{n}{f}_{n - 1}\cdots {f}_{1}$ ). If we are given extra information then we may be able to construct other maps ${A}_{0} \rightarrow  {A}_{n}$ ; for instance, if we happen to know that ${A}_{n - 1} = {A}_{n}$ , then ${f}_{n - 1}{f}_{n - 2}\cdots {f}_{1}$ is another such map. But we are speaking here of the general situation, in the absence of extra information.

For example, a string like this with $n = 4$ gives rise to maps

$$
{A}_{0}\overbrace{\underset{\left( {{f}_{4}{f}_{3}}\right) {f}_{2}{f}_{1}{d}_{1} \rightarrow  {A}_{0}}{ \rightarrow  }} \rightarrow  {A}_{4},
$$

but the axioms imply that they are equal. It is safe to omit the brackets and write both as ${f}_{4}{f}_{3}{f}_{2}{f}_{1}$ .

Here it is intended that $n \geq  0$ . In the case $n = 0$ , the statement is that for each object ${A}_{0}$ of a category, it is possible to construct exactly one map ${A}_{0} \rightarrow  {A}_{0}$ (namely, the identity ${1}_{{A}_{0}}$ ). An identity map can be thought of as a zero-fold composite, in much the same way that the number 1 can be thought of as the product of zero numbers.

(c) We often speak of commutative diagrams. For instance, given objects and maps

![18_705_697_260_168_0.jpg](images/18_705_697_260_168_0.jpg)

in a category, we say that the diagram commutes if ${gf} = {jih}$ . Generally, a diagram is said to commute if whenever there are two paths from an object $X$ to an object $Y$ , the map from $X$ to $Y$ obtained by composing along one path is equal to the map obtained by composing along the other.

(d) The slightly vague word 'collection' means roughly the same as 'set', although if you know about such things, it is better to interpret it as meaning 'class'. We come back to this in Chapter 3.

(e) If $f \in  \mathcal{A}\left( {A, B}\right)$ , we call $A$ the domain and $B$ the codomain of $f$ . Every map in every category has a definite domain and a definite codomain. (If you believe it makes sense to form the intersection of an arbitrary pair of abstract sets, you should add to the definition of category the condition that $\mathcal{A}\left( {A, B}\right)  \cap  \mathcal{A}\left( {{A}^{\prime },{B}^{\prime }}\right)  = \varnothing$ unless $A = {A}^{\prime }$ and $B = {B}^{\prime }$ .)

Examples 1.1.3 (Categories of mathematical structures) (a) There is a category Set described as follows. Its objects are sets. Given sets $A$ and $B$ , a map from $A$ to $B$ in the category Set is exactly what is ordinarily called a map (or mapping, or function) from $A$ to $B$ . Composition in the category is ordinary composition of functions, and the identity maps are again what you would expect.

In situations such as this, we often do not bother to specify the composition and identities. We write 'the category of sets and functions', leaving the reader to guess the rest. In fact, we usually go further and call it just 'the category of sets'.

(b) There is a category Grp of groups, whose objects are groups and whose maps are group homomorphisms.

(c) Similarly, there is a category Ring of rings and ring homomorphisms.

(d) For each field $k$ , there is a category ${\mathbf{{Vect}}}_{k}$ of vector spaces over $k$ and linear maps between them.

(e) There is a category Top of topological spaces and continuous maps.

This chapter is mostly about the interaction between categories, rather than what goes on inside them. We will, however, need the following definition.

Definition 1.1.4 A map $f : A \rightarrow  B$ in a category $\mathcal{A}$ is an isomorphism if there exists a map $g : B \rightarrow  A$ in $\mathcal{A}$ such that ${gf} = {1}_{A}$ and ${fg} = {1}_{B}$ .

In the situation of Definition 1.1.4, we call $g$ the inverse of $f$ and write $g = {f}^{-1}$ . (The word ’the’ is justified by Exercise 1.1.13.) If there exists an isomorphism from $A$ to $B$ , we say that $A$ and $B$ are isomorphic and write $A \cong  B$ .

Example 1.1.5 The isomorphisms in Set are exactly the bijections. This statement is not quite a logical triviality. It amounts to the assertion that a function has a two-sided inverse if and only if it is injective and surjective.

Example 1.1.6 The isomorphisms in Grp are exactly the isomorphisms of groups. Again, this is not quite trivial, at least if you were taught that the definition of group isomorphism is 'bijective homomorphism'. In order to show that this is equivalent to being an isomorphism in Grp, you have to prove that the inverse of a bijective homomorphism is also a homomorphism.

Similarly, the isomorphisms in Ring are exactly the isomorphisms of rings.

Example 1.1.7 The isomorphisms in Top are exactly the homeomorphisms. Note that, in contrast to the situation in Grp and Ring, a bijective map in Top is not necessarily an isomorphism. A classic example is the map

$$
\lbrack 0,1) \rightarrow  \{ z \in  \mathbb{C}\left| \right| z \mid   = 1\}
$$

$$
t\; \mapsto  \;{e}^{2\pi it}
$$

which is a continuous bijection but not a homeomorphism.

The examples of categories mentioned so far are important, but could give a false impression. In each of them, the objects of the category are sets with structure (such as a group structure, a topology, or, in the case of Set, no structure at all). The maps are the functions preserving the structure, in the appropriate sense. And in each of them, there is a clear sense of what the elements of a given object are.

However, not all categories are like this. In general, the objects of a category are not 'sets equipped with extra stuff'. Thus, in a general category, it does not make sense to talk about the 'elements' of an object. (At least, it does not make sense in an immediately obvious way; we return to this in Definition 4.1.25.) Similarly, in a general category, the maps need not be mappings or functions in the usual sense. So:

The objects of a category need not be remotely like sets.

The maps in a category need not be remotely like functions.

The next few examples illustrate these points. They also show that, contrary to the impression that might have been given so far, categories need not be enormous. Some categories are small, manageable structures in their own right, as we now see.

Examples 1.1.8 (Categories as mathematical structures) (a) A category can be specified by saying directly what its objects, maps, composition and identities are. For example, there is a category ∅ with no objects or maps at all. There is a category1with one object and only the identity map. It can be drawn like this:

(Since every object is required to have an identity map on it, we usually do not bother to draw the identities.) There is another category that can be drawn as

$$
\bullet   \rightarrow   \bullet  \;\text{ or }\;A\overset{f}{ \rightarrow  }B,
$$

with two objects and one non-identity map, from the first object to the second. (Composition is defined in the only possible way.) To reiterate the points made above, it is not obvious what an ’element’ of $A$ or $B$ would be, or how one could regard $f$ as a ’function’ of any sort.

It is easy to make up more complicated examples. For instance, here are three more categories:

![20_448_1412_772_160_0.jpg](images/20_448_1412_772_160_0.jpg)

(b) Some categories contain no maps at all apart from identities (which, as categories, they are obliged to have). These are called discrete categories. A discrete category amounts to just a class of objects. More poetically, a category is a collection of objects related to one another to a greater or lesser degree; a discrete category is the extreme case in which each object is totally isolated from its companions.

(c) A group is essentially the same thing as a category that has only one object and in which all the maps are isomorphisms.

To understand this, first consider a category $\mathcal{A}$ with just one object. It is not important what letter or symbol we use to denote the object; let us call it $A$ . Then $\mathcal{A}$ consists of a set (or class) $\mathcal{A}\left( {A, A}\right)$ , an associative composition function

$$
\circ   : \mathcal{A}\left( {A, A}\right)  \times  \mathcal{A}\left( {A, A}\right)  \rightarrow  \mathcal{A}\left( {A, A}\right) ,
$$

and a two-sided unit ${1}_{A} \in  \mathcal{A}\left( {A, A}\right)$ . This would make $\mathcal{A}\left( {A, A}\right)$ into a group, except that we have not mentioned inverses. However, to say that every map in $\mathcal{A}$ is an isomorphism is exactly to say that every element of $\mathcal{A}\left( {A, A}\right)$ has an inverse with respect to $\circ$ .

If we write $G$ for the group $\mathcal{A}\left( {A, A}\right)$ , then the situation is this:

category $\mathcal{A}$ with single object $A\;$ corresponding group $G$

maps in $\mathcal{A}$ elements of $G$

○ in A in $G$

${1}_{A} \; 1 \in  G$

The category $\mathcal{A}$ looks something like this:

![21_726_1057_114_115_0.jpg](images/21_726_1057_114_115_0.jpg)

The arrows represent different maps $A \rightarrow  A$ , that is, different elements of the group $G$ .

What the object of $\mathcal{A}$ is called makes no difference. It matters exactly as much as whether we choose $x$ or $y$ or $t$ to denote some variable in an algebra problem, which is to say, not at all. Later we will define 'equivalence' of categories, which will enable us to make a precise statement: the category of groups is equivalent to the category of (small) one-object categories in which every map is an isomorphism (Example 3.2.11).

The first time one meets the idea that a group is a kind of category, it is tempting to dismiss it as a coincidence or a trick. But it is not; there is real content.

To see this, suppose that your education had been shuffled and that you already knew about categories before being taught about groups. In your first group theory class, the lecturer declares that a group is supposed to be the system of all symmetries of an object. A symmetry of an object $X$ , she says, is a way of mapping $X$ to itself in a reversible or invertible manner. At this point, you realize that she is talking about a very special type of category. In general, a category is a system consisting of all the mappings (not usually just the invertible ones) between many objects (not usually just one). So a group is just a category with the special properties that all the maps are invertible and there is only one object.

(d) The inverses played no essential part in the previous example, suggesting that it is worth thinking about 'groups without inverses'. These are called monoids.

Formally, a monoid is a set equipped with an associative binary operation and a two-sided unit element. Groups describe the reversible transformations, or symmetries, that can be applied to an object; monoids describe the not-necessarily-reversible transformations. For instance, given any set $X$ , there is a group consisting of all bijections $X \rightarrow  X$ , and there is a monoid consisting of all functions $X \rightarrow  X$ . In both cases, the binary operation is composition and the unit is the identity function on $X$ . Another example of a monoid is the set $\mathbb{N} = \{ 0,1,2,\ldots \}$ of natural numbers, with + as the operation and 0 as the unit. Alternatively, we could take the set $\mathbb{N}$ with $\cdot$ as the operation and 1 as the unit.

A category with one object is essentially the same thing as a monoid, by the same argument as for groups. This is stated formally in Example 3.2.11.

(e) A preorder is a reflexive transitive binary relation. A preordered set $\left( {S, \leq  }\right)$ is a set $S$ together with a preorder $\leq$ on it. Examples: $S = \mathbb{R}$ and $\leq$ has its usual meaning; $S$ is the set of subsets of $\{ 1,\ldots ,{10}\}$ and $\leq$ is $\subseteq$ (inclusion); $S = \mathbb{Z}$ and $a \leq  b$ means that $a$ divides $b$ .

A preordered set can be regarded as a category $\mathcal{A}$ in which, for each $A, B \in  \mathcal{A}$ , there is at most one map from $A$ to $B$ . To see this, consider a category $\mathcal{A}$ with this property. It is not important what letter we use to denote the unique map from an object $A$ to an object $B$ ; all we need to record is which pairs $\left( {A, B}\right)$ of objects have the property that a map $A \rightarrow  B$ does exist. Let us write $A \leq  B$ to mean that there exists a map $A \rightarrow  B$ .

Since $\mathcal{A}$ is a category, and categories have composition, if $A \leq  B \leq \; C$ then $A \leq  C$ . Since categories also have identities, $A \leq  A$ for all $A$ . The associativity and identity axioms are automatic. So, $\mathcal{A}$ amounts to a collection of objects equipped with a transitive reflexive binary relation, that is, a preorder. One can think of the unique map $A \rightarrow  B$ as the statement or assertion that $A \leq  B$ .

An order on a set is a preorder $\leq$ with the property that if $A \leq  B$ and $B \leq  A$ then $A = B$ . (Equivalently, if $A \cong  B$ in the corresponding category then $A = B$ .) Ordered sets are also called partially ordered sets or posets.

An example of a preorder that is not an order is the divisibility relation on $\mathbb{Z}$ : for there we have $2\left| {-2\text{ and } - 2}\right| 2$ but $2 \neq   - 2$ .

Here are two ways of constructing new categories from old.

Construction 1.1.9 Every category $\mathcal{A}$ has an opposite or dual category ${\mathcal{A}}^{\text{ op }}$ , defined by reversing the arrows. Formally, $\mathrm{{ob}}\left( {\mathcal{A}}^{\text{ op }}\right)  = \mathrm{{ob}}\left( \mathcal{A}\right)$ and ${\mathcal{A}}^{\mathrm{{op}}}\left( {B, A}\right)  = \mathcal{A}\left( {A, B}\right)$ for all objects $A$ and $B$ . Identities in ${\mathcal{A}}^{\mathrm{{op}}}$ are the same as in $\mathcal{A}$ . Composition in ${\mathcal{A}}^{\mathrm{{op}}}$ is the same as in $\mathcal{A}$ , but with the arguments reversed. To spell this out: if $A\overset{f}{ \rightarrow  }B\overset{g}{ \rightarrow  }C$ are maps in ${\mathcal{A}}^{\text{ op }}$ then $A\overset{f}{ \leftarrow  }B\overset{g}{ \leftarrow  }C$ are maps in $\mathcal{A}$ ; these give rise to a map $A\overset{f \circ  g}{ \leftarrow  }C$ in $\mathcal{A}$ , and the composite of the original pair of maps is the corresponding map $A \rightarrow  C$ in ${\mathcal{A}}^{\mathrm{{op}}}$ .

So, arrows $A \rightarrow  B$ in $\mathcal{A}$ correspond to arrows $B \rightarrow  A$ in ${\mathcal{A}}^{\mathrm{{op}}}$ . According to the definition above, if $f : A \rightarrow  B$ is an arrow in $\mathcal{A}$ then the corresponding arrow $B \rightarrow  A$ in ${\mathcal{A}}^{\text{ op }}$ is also called $f$ . Some people prefer to give it a different name, such as ${f}^{\text{ op }}$ .

Remark 1.1.10 The principle of duality is fundamental to category theory. Informally, it states that every categorical definition, theorem and proof has a dual, obtained by reversing all the arrows. Invoking the principle of duality can save work: given any theorem, reversing the arrows throughout its statement and proof produces a dual theorem. Numerous examples of duality appear throughout this book.

Construction 1.1.11 Given categories $\mathcal{A}$ and $\mathcal{B}$ , there is a product category $\mathcal{A} \times  \mathcal{B}$ , in which

$$
\mathrm{{ob}}\left( {\mathcal{A} \times  \mathcal{B}}\right)  = \mathrm{{ob}}\left( \mathcal{A}\right)  \times  \mathrm{{ob}}\left( \mathcal{B}\right) ,
$$

$$
\left( {\mathcal{A} \times  \mathcal{B}}\right) \left( {\left( {A, B}\right) ,\left( {{A}^{\prime },{B}^{\prime }}\right) }\right)  = \mathcal{A}\left( {A,{A}^{\prime }}\right)  \times  \mathcal{B}\left( {B,{B}^{\prime }}\right) .
$$

Put another way, an object of the product category $\mathcal{A} \times  \mathcal{B}$ is a pair $\left( {A, B}\right)$ where $A \in  \mathcal{A}$ and $B \in  \mathcal{B}$ . A map $\left( {A, B}\right)  \rightarrow  \left( {{A}^{\prime },{B}^{\prime }}\right)$ in $\mathcal{A} \times  \mathcal{B}$ is a pair $\left( {f, g}\right)$ where $f : A \rightarrow  {A}^{\prime }$ in $\mathcal{A}$ and $g : B \rightarrow  {B}^{\prime }$ in $\mathcal{B}$ . For the definitions of composition and identities in $\mathcal{A} \times  \mathcal{B}$ , see Exercise 1.1.14.

## Exercises

1.1.12 Find three examples of categories not mentioned above.

1.1.13 Show that a map in a category can have at most one inverse. That is, given a map $f : A \rightarrow  B$ , show that there is at most one map $g : B \rightarrow  A$ such that ${gf} = {1}_{A}$ and ${fg} = {1}_{B}$ .

1.1.14 Let $\mathcal{A}$ and $\mathcal{B}$ be categories. Construction 1.1.11 defined the product category $\mathcal{A} \times  \mathcal{B}$ , except that the definitions of composition and identities in $\mathcal{A} \times  \mathcal{B}$ were not given. There is only one sensible way to define them; write it down.

1.1.15 There is a category Toph whose objects are topological spaces and whose maps $X \rightarrow  Y$ are homotopy classes of continuous maps from $X$ to $Y$ . What do you need to know about homotopy in order to prove that Toph is a category? What does it mean, in purely topological terms, for two objects of Toph to be isomorphic?

### 1.2 Functors

One of the lessons of category theory is that whenever we meet a new type of mathematical object, we should always ask whether there is a sensible notion of 'map' between such objects. We can ask this about categories themselves. The answer is yes, and a map between categories is called a functor.

Definition 1.2.1 Let $\mathcal{A}$ and $\mathcal{B}$ be categories. A functor $F : \mathcal{A} \rightarrow  \mathcal{B}$ consists of:

- a function

$$
\mathrm{{ob}}\left( \mathcal{A}\right)  \rightarrow  \mathrm{{ob}}\left( \mathcal{B}\right) ,
$$

written as $A \mapsto  F\left( A\right)$ ;

- for each $A,{A}^{\prime } \in  \mathcal{A}$ , a function

$$
\mathcal{A}\left( {A,{A}^{\prime }}\right)  \rightarrow  \mathcal{B}\left( {F\left( A\right) , F\left( {A}^{\prime }\right) }\right) ,
$$

written as $f \mapsto  F\left( f\right)$ ,

satisfying the following axioms:

- $F\left( {{f}^{\prime } \circ  f}\right)  = F\left( {f}^{\prime }\right)  \circ  F\left( f\right)$ whenever $A\overset{f}{ \rightarrow  }{A}^{\prime }\overset{{f}^{\prime }}{ \rightarrow  }{A}^{\prime \prime }$ in $\mathcal{A}$ ;

- $F\left( {1}_{A}\right)  = {1}_{F\left( A\right) }$ whenever $A \in  \mathcal{A}$ .

Remarks 1.2.2 (a) The definition of functor is set up so that from each string

$$
{A}_{0}\overset{{f}_{1}}{ \rightarrow  }\cdots \overset{{f}_{n}}{ \rightarrow  }{A}_{n}
$$

of maps in $\mathcal{A}$ (with $n \geq  0$ ), it is possible to construct exactly one map

$$
F\left( {A}_{0}\right)  \rightarrow  F\left( {A}_{n}\right)
$$

in $\mathcal{B}$ . For example, given maps

$$
{A}_{0}\overset{{f}_{1}}{ \rightarrow  }{A}_{1}\overset{{f}_{2}}{ \rightarrow  }{A}_{2}\overset{{f}_{3}}{ \rightarrow  }{A}_{3}\overset{{f}_{4}}{ \rightarrow  }{A}_{4}
$$

in $\mathcal{A}$ , we can construct maps

$$
F\left( {A}_{0}\right) \xrightarrow[{\frac{F\left( {{f}_{4}{f}_{3}}\right) F\left( {{f}_{2}{f}_{1}}\right) }{F\left( {1}_{{A}_{4}}\right) F\left( {f}_{4}\right) F\left( {{f}_{3}{f}_{2}}\right) F\left( {f}_{1}\right) } \rightarrow  F\left( {A}_{4}\right) }]{}
$$

in $\mathcal{B}$ , but the axioms imply that they are equal.

(b) We are familiar with the idea that structures and the structure-preserving maps between them form a category (such as Grp, Ring, etc.). In particular, this applies to categories and functors: there is a category CAT whose objects are categories and whose maps are functors.

One part of this statement is that functors can be composed. That is, given functors $\mathcal{A}\overset{F}{ \rightarrow  }\mathcal{B}\overset{G}{ \rightarrow  }\mathcal{C}$ , there arises a new functor $\mathcal{A}\overset{G \circ  F}{ \rightarrow  }\mathcal{C}$ , defined in the obvious way. Another is that for every category $\mathcal{A}$ , there is an identity functor ${1}_{\mathcal{A}} : \mathcal{A} \rightarrow  \mathcal{A}$ .

Examples 1.2.3 Perhaps the easiest examples of functors are the so-called forgetful functors. (This is an informal term, with no precise definition.) For instance:

(a) There is a functor $U : \operatorname{Grp} \rightarrow  \operatorname{Set}$ defined as follows: if $G$ is a group then $U\left( G\right)$ is the underlying set of $G$ (that is, its set of elements), and if $f$ : $G \rightarrow  H$ is a group homomorphism then $U\left( f\right)$ is the function $f$ itself. So $U$ forgets the group structure of groups and forgets that group homomorphisms are homomorphisms.

(b) Similarly, there is a functor Ring $\rightarrow$ Set forgetting the ring structure on rings, and (for any field $k$ ) there is a functor ${\operatorname{Vect}}_{k} \rightarrow$ Set forgetting the vector space structure on vector spaces.

(c) Forgetful functors do not have to forget all the structure. For example, let $\mathbf{{Ab}}$ be the category of abelian groups. There is a functor Ring $\rightarrow  \mathbf{{Ab}}$ that forgets the multiplicative structure, remembering just the underlying additive group. Or, let Mon be the category of monoids. There is a functor $U :$ Ring $\rightarrow$ Mon that forgets the additive structure, remembering just the underlying multiplicative monoid. (That is, if $R$ is a ring then $U\left( R\right)$ is the set $R$ made into a monoid via $\cdot$ and 1.)

(d) There is an inclusion functor $U : \mathbf{{Ab}} \rightarrow  \mathbf{{Grp}}$ defined by $U\left( A\right)  = A$ for any abelian group $A$ and $U\left( f\right)  = f$ for any homomorphism $f$ of abelian groups. It forgets that abelian groups are abelian.

The forgetful functors in examples (a)-(c) forget structure on the objects, but that of example (d) forgets a property. Nevertheless, it turns out to be convenient to use the same word, 'forgetful', in both situations.

Although forgetting is a trivial operation, there are situations in which it is powerful. For example, it is a theorem that the order of any finite field is a prime power. An important step in the proof is to simply forget that the field is a field, remembering only that it is a vector space over its subfield $\{ 0,1,1 + 1,1 + 1 + 1,\ldots \}$ .

Examples 1.2.4 Free functors are in some sense dual to forgetful functors (as we will see in the next chapter), although they are less elementary. Again, 'free functor' is an informal but useful term.

(a) Given any set $S$ , one can build the free group $F\left( S\right)$ on $S$ . This is a group containing $S$ as a subset and with no further properties other than those it is forced to have, in a sense made precise in Section 2.1. Intuitively, the group $F\left( S\right)$ is obtained from the set $S$ by adding just enough new elements that it becomes a group, but without imposing any equations other than those forced by the definition of group.

A little more precisely, the elements of $F\left( S\right)$ are formal expressions or words such as ${x}^{-4}y{x}^{2}z{y}^{-3}$ (where $x, y, z \in  S$ ). Two such words are seen as equal if one can be obtained from the other by the usual cancellation rules, so that, for example, ${x}^{3}{xy},{x}^{4}y$ , and ${x}^{2}{y}^{-1}y{x}^{2}y$ all represent the same element of $F\left( S\right)$ . To multiply two words, just write one followed by the other; for instance, ${x}^{-4}{yx}$ times ${xz}{y}^{-3}$ is ${x}^{-4}y{x}^{2}z{y}^{-3}$ .

This construction assigns to each set $S$ a group $F\left( S\right)$ . In fact, $F$ is a functor: any map of sets $f : S \rightarrow  {S}^{\prime }$ gives rise to a homomorphism of groups $F\left( f\right)  : F\left( S\right)  \rightarrow  F\left( {S}^{\prime }\right)$ . For instance, take the map of sets

$$
f : \{ w, x, y, z\}  \rightarrow  \{ u, v\}
$$

defined by $f\left( w\right)  = f\left( x\right)  = f\left( y\right)  = u$ and $f\left( z\right)  = v$ . This gives rise to a homomorphism

$$
F\left( f\right)  : F\left( {\{ w, x, y, z\} }\right)  \rightarrow  F\left( {\{ u, v\} }\right) ,
$$

which maps ${x}^{-4}y{x}^{2}z{y}^{-3} \in  F\left( {\{ w, x, y, z\} }\right)$ to

$$
{u}^{-4}u{u}^{2}v{u}^{-3} = {u}^{-1}v{u}^{-3} \in  F\left( {\{ u, v\} }\right) .
$$

(b) Similarly, we can construct the free commutative ring $F\left( S\right)$ on a set $S$ , giving a functor $F$ from Set to the category CRing of commutative rings. In fact, $F\left( S\right)$ is something familiar, namely, the ring of polynomials over $\mathbb{Z}$ in commuting variables ${x}_{s}\left( {s \in  S}\right)$ . (A polynomial is, after all, just a formal expression built from the variables using the ring operations +, - and $\cdot$ .) For example, if $S$ is a two-element set then $F\left( S\right)  \cong  \mathbb{Z}\left\lbrack  {x, y}\right\rbrack$ .

(c) We can also construct the free vector space on a set. Fix a field $k$ . The free functor $F :$ Set $\rightarrow  {\mathbf{{Vect}}}_{k}$ is defined on objects by taking $F\left( S\right)$ to be a vector space with basis $S$ . Any two such vector spaces are isomorphic; but it is perhaps not obvious that there is any such vector space at all, so we have to construct one. Loosely, $F\left( S\right)$ is the set of all formal $k$ -linear combinations of elements of $S$ , that is, expressions

$$
\mathop{\sum }\limits_{{s \in  S}}{\lambda }_{s}s
$$

where each ${\lambda }_{s}$ is a scalar and there are only finitely many values of $s$ such that ${\lambda }_{s} \neq  0$ . (This restriction is imposed because one can only take finite sums in a vector space.) Elements of $F\left( S\right)$ can be added:

$$
\mathop{\sum }\limits_{{s \in  S}}{\lambda }_{s}s + \mathop{\sum }\limits_{{s \in  S}}{\mu }_{s}s = \mathop{\sum }\limits_{{s \in  S}}\left( {{\lambda }_{s} + {\mu }_{s}}\right) s.
$$

There is also a scalar multiplication on $F\left( S\right)$ :

$$
c \cdot  \mathop{\sum }\limits_{{s \in  S}}{\lambda }_{s}s = \mathop{\sum }\limits_{{s \in  S}}\left( {c{\lambda }_{s}}\right) s
$$

$\left( {c \in  k}\right)$ . In this way, $F\left( S\right)$ becomes a vector space.

To be completely precise and avoid talking about 'expressions', we can define $F\left( S\right)$ to be the set of all functions $\lambda  : S \rightarrow  k$ such that $\{ s \in  S \mid \; \lambda \left( s\right)  \neq  0\}$ is finite. (Think of such a function $\lambda$ as corresponding to the expression $\mathop{\sum }\limits_{{s \in  S}}\lambda \left( s\right) s$ .) To define addition on $F\left( S\right)$ , we must define for each $\lambda ,\mu  \in  F\left( S\right)$ a sum $\lambda  + \mu  \in  F\left( S\right)$ ; it is given by

$$
\left( {\lambda  + \mu }\right) \left( s\right)  = \lambda \left( s\right)  + \mu \left( s\right)
$$

$\left( {s \in  S}\right)$ . Similarly, the scalar multiplication is given by $\left( {c \cdot  \lambda }\right) \left( s\right)  = c \cdot  \lambda \left( s\right) \; \left( {c \in  k,\lambda  \in  F\left( S\right) , s \in  S}\right)$ .

Rings and vector spaces have the special property that it is relatively easy to write down an explicit formula for the free functor. The case of groups is much more typical. For most types of algebraic structure, describing the free functor requires as much fussy work as it does for groups. We return to this point in Example 2.1.3 and Example 6.3.11 (where we see how to avoid the fussy work entirely).

Examples 1.2.5 (Functors in algebraic topology) Historically, some of the first examples of functors arose in algebraic topology. There, the strategy is to learn about a space by extracting data from it in some clever way, assembling that data into an algebraic structure, then studying the algebraic structure instead of the original space. Algebraic topology therefore involves many functors from categories of spaces to categories of algebras.

(a) Let ${\mathbf{{Top}}}_{ * }$ be the category of topological spaces equipped with a basepoint, together with the continuous basepoint-preserving maps. There is a functor ${\pi }_{1} : {\mathbf{{Top}}}_{ * } \rightarrow  \mathbf{{Grp}}$ assigning to each space $X$ with basepoint $x$ the fundamental group ${\pi }_{1}\left( {X, x}\right)$ of $X$ at $x$ . (Some texts use the simpler notation ${\pi }_{1}\left( X\right)$ , ignoring the choice of basepoint. This is more or less safe if $X$ is path-connected, but strictly speaking, the basepoint should always be specified.)

That ${\pi }_{1}$ is a functor means that it not only assigns to each space-with-basepoint $\left( {X, x}\right)$ a group ${\pi }_{1}\left( {X, x}\right)$ , but also assigns to each basepoint-preserving continuous map

$$
f : \left( {X, x}\right)  \rightarrow  \left( {Y, y}\right)
$$

a homomorphism

$$
{\pi }_{1}\left( f\right)  : {\pi }_{1}\left( {X, x}\right)  \rightarrow  {\pi }_{1}\left( {Y, y}\right) .
$$

Usually ${\pi }_{1}\left( f\right)$ is written as ${f}_{ * }$ . The functoriality axioms say that ${\left( g \circ  f\right) }_{ * } = \; {g}_{ * } \circ  {f}_{ * }$ and ${\left( {1}_{\left( X, x\right) }\right) }_{ * } = {1}_{{\pi }_{1}\left( {X, x}\right) }$ .

(b) For each $n \in  \mathbb{N}$ , there is a functor ${H}_{n} :$ Top $\rightarrow$ Ab assigning to a space its $n$ th homology group (in any of several possible senses).

Example 1.2.6 Any system of polynomial equations such as

$$
2{x}^{2} + {y}^{2} - 3{z}^{2} = 1 \tag{1.1}
$$

$$
{x}^{3} + x = {y}^{2} \tag{1.2}
$$

gives rise to a functor CRing $\rightarrow$ Set. Indeed, for each commutative ring $A$ , let $F\left( A\right)$ be the set of triples $\left( {x, y, z}\right)  \in  A \times  A \times  A$ satisfying equations (1.1) and (1.2). Whenever $f : A \rightarrow  B$ is a ring homomorphism and $\left( {x, y, z}\right)  \in  F\left( A\right)$ , we have $\left( {f\left( x\right) , f\left( y\right) , f\left( z\right) }\right)  \in  F\left( B\right)$ ; so the map of rings $f : A \rightarrow  B$ induces a map of sets $F\left( f\right)  : F\left( A\right)  \rightarrow  F\left( B\right)$ . This defines a functor $F :$ CRing $\rightarrow$ Set.

In algebraic geometry, a scheme is a functor CRing $\rightarrow$ Set with certain properties. (This is not the most common way of phrasing the definition, but it is equivalent.) The functor $F$ above is a simple example.

Example 1.2.7 Let $G$ and $H$ be monoids (or groups, if you prefer), regarded as one-object categories $\mathcal{G}$ and $\mathcal{H}$ . A functor $F : \mathcal{G} \rightarrow  \mathcal{H}$ must send the unique object of $\mathcal{G}$ to the unique object of $\mathcal{H}$ , so it is determined by its effect on maps. Hence, the functor $F : \mathcal{G} \rightarrow  \mathcal{H}$ amounts to a function $F : G \rightarrow  H$ such that $F\left( {{g}^{\prime }g}\right)  = F\left( {g}^{\prime }\right) F\left( g\right)$ for all ${g}^{\prime }, g \in  G$ , and $F\left( 1\right)  = 1$ . In other words, a functor $\mathcal{G} \rightarrow  \mathcal{H}$ is just a homomorphism $G \rightarrow  H$ .

Example 1.2.8 Let $G$ be a monoid, regarded as a one-object category $\mathcal{G}$ . A functor $F : \mathcal{G} \rightarrow$ Set consists of a set $S$ (the value of $F$ at the unique object of $\mathcal{G}$ ) together with, for each $g \in  G$ , a function $F\left( g\right)  : S \rightarrow  S$ , satisfying the functoriality axioms. Writing $\left( {F\left( g\right) }\right) \left( s\right)  = g \cdot  s$ , we see that the functor $F$ amounts to a set $S$ together with a function

$$
G \times  S \rightarrow  S
$$

$$
\left( {g, s}\right) \; \mapsto  \;g \cdot  s
$$

satisfying $\left( {{g}^{\prime }g}\right)  \cdot  s = {g}^{\prime } \cdot  \left( {g \cdot  s}\right)$ and $1 \cdot  s = s$ for all $g,{g}^{\prime } \in  G$ and $s \in  S$ . In other words, a functor $\mathcal{G} \rightarrow$ Set is a set equipped with a left action by $G$ : a left $G$ -set, for short.

Similarly, a functor $\mathcal{G} \rightarrow  {\operatorname{Vect}}_{k}$ is exactly a $k$ -linear representation of $G$ , in the sense of representation theory. This can reasonably be taken as the definition of representation.

Example 1.2.9 When $A$ and $B$ are (pre)ordered sets, a functor between the corresponding categories is exactly an order-preserving map, that is, a function $f : A \rightarrow  B$ such that $a \leq  {a}^{\prime } \Rightarrow  f\left( a\right)  \leq  f\left( {a}^{\prime }\right)$ . Exercise 1.2.22 asks you to verify this.

Sometimes we meet functor-like operations that reverse the arrows, with a map $A \rightarrow  {A}^{\prime }$ in $\mathcal{A}$ giving rise to a map $F\left( A\right)  \leftarrow  F\left( {A}^{\prime }\right)$ in $\mathcal{B}$ . Such operations are called contravariant functors.

Definition 1.2.10 Let $\mathcal{A}$ and $\mathcal{B}$ be categories. A contravariant functor from $\mathcal{A}$ to $\mathcal{B}$ is a functor ${\mathcal{A}}^{\mathrm{{op}}} \rightarrow  \mathcal{B}$ .

To avoid confusion, we write ’a contravariant functor from $\mathcal{A}$ to $\mathcal{B}$ ’ rather than ’a contravariant functor $\mathcal{A} \rightarrow  \mathcal{B}$ ’.

Functors $\mathcal{C} \rightarrow  \mathcal{D}$ correspond one-to-one with functors ${\mathcal{C}}^{\text{ op }} \rightarrow  {\mathcal{D}}^{\text{ op }}$ , and ${\left( {\mathcal{A}}^{\text{ op }}\right) }^{\text{ op }} = \mathcal{A}$ , so a contravariant functor from $\mathcal{A}$ to $\mathcal{B}$ can also be described as a functor $\mathcal{A} \rightarrow  {\mathcal{B}}^{\text{ op }}$ . Which description we use is not enormously important, but in the long run, the convention in Definition 1.2.10 makes life easier.

An ordinary functor $\mathcal{A} \rightarrow  \mathcal{B}$ is sometimes called a covariant functor from $\mathcal{A}$ to $\mathcal{B}$ , for emphasis.

Example 1.2.11 We can tell a lot about a space by examining the functions on it. The importance of this principle in twentieth- and twenty-first-century mathematics can hardly be exaggerated.

For example, given a topological space $X$ , let $C\left( X\right)$ be the ring of continuous real-valued functions on $X$ . The ring operations are defined ’pointwise’: for instance, if ${p}_{1},{p}_{2} : X \rightarrow  \mathbb{R}$ are continuous maps then the map ${p}_{1} + {p}_{2} : X \rightarrow  \mathbb{R}$ is defined by

$$
\left( {{p}_{1} + {p}_{2}}\right) \left( x\right)  = {p}_{1}\left( x\right)  + {p}_{2}\left( x\right)
$$

$\left( {x \in  X}\right)$ . A continuous map $f : X \rightarrow  Y$ induces a ring homomorphism $C\left( f\right)$ : $C\left( Y\right)  \rightarrow  C\left( X\right)$ , defined at $q \in  C\left( Y\right)$ by taking $\left( {C\left( f\right) }\right) \left( q\right)$ to be the composite map

$$
X\overset{f}{ \rightarrow  }Y\overset{q}{ \rightarrow  }\mathbb{R}
$$

Note that $C\left( f\right)$ goes in the opposite direction from $f$ . After checking some axioms (Exercise 1.2.26), we conclude that $C$ is a contravariant functor from Top to Ring.

While this particular example will not play a large part in this text, it is worth close attention. It illustrates the important idea of a structure whose elements are maps (in this case, a ring whose elements are continuous functions). The way in which $C$ becomes a functor, via composition, is also important. Similar constructions will be crucial in later chapters.

For certain classes of space, the passage from $X$ to $C\left( X\right)$ loses no information: there is a way of reconstructing the space $X$ from the ring $C\left( X\right)$ . For this and related reasons, it is sometimes said that 'algebra is dual to geometry'.

Example 1.2.12 Let $k$ be a field. For any two vector spaces $V$ and $W$ over $k$ , there is a vector space

$$
\operatorname{Hom}\left( {V, W}\right)  = \{ \text{ linear maps }V \rightarrow  W\} .
$$

The elements of this vector space are themselves maps, and the vector space operations (addition and scalar multiplication) are defined pointwise, as in the last example.

Now fix a vector space $W$ . Any linear map $f : V \rightarrow  {V}^{\prime }$ induces a linear map

$$
{f}^{ * } : \operatorname{Hom}\left( {{V}^{\prime }, W}\right)  \rightarrow  \operatorname{Hom}\left( {V, W}\right) ,
$$

defined at $q \in  \operatorname{Hom}\left( {{V}^{\prime }, W}\right)$ by taking ${f}^{ * }\left( q\right)$ to be the composite map

$$
V\overset{f}{ \rightarrow  }{V}^{\prime }\overset{q}{ \rightarrow  }W
$$

This defines a functor

$$
\operatorname{Hom}\left( {-, W}\right)  : {\mathbf{{Vect}}}_{k}^{\text{ op }} \rightarrow  {\mathbf{{Vect}}}_{k}.
$$

The symbol '-' is a blank or placeholder, into which arguments can be inserted. Thus, the value of $\operatorname{Hom}\left( {-, W}\right)$ at $V$ is $\operatorname{Hom}\left( {V, W}\right)$ . Sometimes we use a blank space instead of -, as in $\operatorname{Hom}\left( {\;, W}\right)$ .

An important special case is where $W$ is $k$ , seen as a one-dimensional vector space over itself. The vector space $\operatorname{Hom}\left( {V, k}\right)$ is called the dual of $V$ , and is written as ${V}^{ * }$ . So there is a contravariant functor

$$
{\left(  \right) }^{ * } = \operatorname{Hom}\left( {-, k}\right)  : {\mathbf{{Vect}}}_{k}^{\text{ op }} \rightarrow  {\mathbf{{Vect}}}_{k}
$$

sending each vector space to its dual.

Example 1.2.13 For each $n \in  \mathbb{N}$ , there is a functor ${H}^{n} : {\operatorname{Top}}^{\text{ op }} \rightarrow  \mathbf{{Ab}}$ assigning to a space its $n$ th cohomology group.

Example 1.2.14 Let $G$ be a monoid, regarded as a one-object category $\mathcal{G}$ . A functor ${\mathcal{G}}^{\text{ op }} \rightarrow$ Set is a right $G$ -set, for essentially the same reasons as in Example 1.2.8.

That left actions are covariant functors and right actions are contravariant functors is a consequence of a basic notational choice: we write the value of a function $f$ at an element $x$ as $f\left( x\right)$ , not $\left( x\right) f$ .

Contravariant functors whose codomain is Set are important enough to have their own special name.

Definition 1.2.15 Let $\mathcal{A}$ be a category. A presheaf on $\mathcal{A}$ is a functor ${\mathcal{A}}^{\text{ op }} \rightarrow$ Set.

The name comes from the following special case. Let $X$ be a topological space. Write $\mathcal{O}\left( X\right)$ for the poset of open subsets of $X$ , ordered by inclusion. View $\mathcal{O}\left( X\right)$ as a category, as in Example 1.1.8(e). Thus, the objects of $\mathcal{O}\left( X\right)$ are the open subsets of $X$ , and for $U,{U}^{\prime } \in  \mathcal{O}\left( X\right)$ , there is one map $U \rightarrow  {U}^{\prime }$ if $U \subseteq  {U}^{\prime }$ , and there are none otherwise. A presheaf on the space $X$ is a presheaf on the category $\mathcal{O}\left( X\right)$ . For example, given any space $X$ , there is a presheaf $F$ on $X$ defined by

$$
F\left( U\right)  = \{ \text{ continuous functions }U \rightarrow  \mathbb{R}\}
$$

$\left( {U \in  \mathcal{O}\left( X\right) }\right)$ and, whenever $U \subseteq  {U}^{\prime }$ are open subsets of $X$ , by taking the map $F\left( {U}^{\prime }\right)  \rightarrow  F\left( U\right)$ to be restriction. Presheaves, and a certain class of presheaves called sheaves, play an important role in modern geometry.

We know very well that for functions between sets, it is sometimes useful to consider special kinds of function such as injections, surjections and bijections. We also know that the notions of injection and subset are related: for instance, whenever $B$ is a subset of $A$ , there is an injection $B \rightarrow  A$ given by inclusion. In this section and the next, we introduce some similar notions for functors between categories, beginning with the following definitions.

![32_413_370_800_185_0.jpg](images/32_413_370_800_185_0.jpg)

Figure 1.1 Fullness and faithfulness.

Definition 1.2.16 A functor $F : \mathcal{A} \rightarrow  \mathcal{B}$ is faithful (respectively, full) if for each $A,{A}^{\prime } \in  \mathcal{A}$ , the function

$$
\mathcal{A}\left( {A,{A}^{\prime }}\right)  \rightarrow  \mathcal{B}\left( {F\left( A\right) , F\left( {A}^{\prime }\right) }\right)
$$

$$
f\; \mapsto  \;F\left( f\right)
$$

is injective (respectively, surjective).

Warning 1.2.17 Note the roles of $A$ and ${A}^{\prime }$ in the definition. Faithfulness does not say that if ${f}_{1}$ and ${f}_{2}$ are distinct maps in $\mathcal{A}$ then $F\left( {f}_{1}\right)  \neq  F\left( {f}_{2}\right)$ (Exercise 1.2.27). In the situation of Figure 1.1, $F$ is faithful if for each $A,{A}^{\prime }$ and $g$ as shown, there is at most one dotted arrow that $F$ sends to $g$ . It is full if for each such $A,{A}^{\prime }$ and $g$ , there is at least one dotted arrow that $F$ sends to $g$ .

Definition 1.2.18 Let $\mathcal{A}$ be a category. A subcategory $\mathcal{S}$ of $\mathcal{A}$ consists of a subclass ob $\left( \mathcal{S}\right)$ of $\operatorname{ob}\left( \mathcal{A}\right)$ together with, for each $S,{S}^{\prime } \in  \operatorname{ob}\left( \mathcal{S}\right)$ , a subclass $\mathcal{S}\left( {S,{S}^{\prime }}\right)$ of $\mathcal{A}\left( {S,{S}^{\prime }}\right)$ , such that $\mathcal{S}$ is closed under composition and identities. It is a full subcategory if $\mathcal{S}\left( {S,{S}^{\prime }}\right)  = \mathcal{A}\left( {S,{S}^{\prime }}\right)$ for all $S,{S}^{\prime } \in  \operatorname{ob}\left( \mathcal{S}\right)$ .

A full subcategory therefore consists of a selection of the objects, with all of the maps between them. So, a full subcategory can be specified simply by saying what its objects are. For example, $\mathbf{{Ab}}$ is the full subcategory of $\mathbf{{Grp}}$ consisting of the groups that are abelian.

Whenever $\mathcal{S}$ is a subcategory of a category $\mathcal{A}$ , there is an inclusion functor $I : \mathcal{S} \rightarrow  \mathcal{A}$ defined by $I\left( S\right)  = S$ and $I\left( f\right)  = f$ . It is automatically faithful, and it is full if and only if $\mathcal{S}$ is a full subcategory.

Warning 1.2.19 The image of a functor need not be a subcategory. For example, consider the functor

![33_384_413_781_159_0.jpg](images/33_384_413_781_159_0.jpg)

defined by $F\left( A\right)  = X, F\left( B\right)  = F\left( {B}^{\prime }\right)  = Y, F\left( C\right)  = Z, F\left( f\right)  = p$ , and $F\left( g\right)  = q$ . Then $p$ and $q$ are in the image of $F$ , but ${qp}$ is not.

## Exercises

1.2.20 Find three examples of functors not mentioned above.

1.2.21 Show that functors preserve isomorphism. That is, prove that if $F$ : $\mathcal{A} \rightarrow  \mathcal{B}$ is a functor and $A,{A}^{\prime } \in  \mathcal{A}$ with $A \cong  {A}^{\prime }$ , then $F\left( A\right)  \cong  F\left( {A}^{\prime }\right)$ .

1.2.22 Prove the assertion made in Example 1.2.9. In other words, given ordered sets $A$ and $B$ , and denoting by $\mathcal{A}$ and $\mathcal{B}$ the corresponding categories, show that a functor $\mathcal{A} \rightarrow  \mathcal{B}$ amounts to an order-preserving map $A \rightarrow  B$ .

1.2.23 Two categories $\mathcal{A}$ and $\mathcal{B}$ are isomorphic, written as $\mathcal{A} \cong  \mathcal{B}$ , if they are isomorphic as objects of CAT.

(a) Let $G$ be a group, regarded as a one-object category all of whose maps are isomorphisms. Then its opposite ${G}^{\mathrm{{op}}}$ is also a one-object category all of whose maps are isomorphisms, and can therefore be regarded as a group too. What is ${G}^{\mathrm{{op}}}$ , in purely group-theoretic terms? Prove that $G$ is isomorphic to ${G}^{\mathrm{{op}}}$ .

(b) Find a monoid not isomorphic to its opposite.

1.2.24 Is there a functor $Z : \operatorname{Grp} \rightarrow  \operatorname{Grp}$ with the property that $Z\left( G\right)$ is the centre of $G$ for all groups $G$ ?

1.2.25 Sometimes we meet functors whose domain is a product $\mathcal{A} \times  \mathcal{B}$ of categories. Here you will show that such a functor can be regarded as an interlocking pair of families of functors, one defined on $\mathcal{A}$ and the other defined on $\mathcal{B}$ . (This is very like the situation for bilinear and linear maps.)

(a) Let $F : \mathcal{A} \times  \mathcal{B} \rightarrow  \mathcal{C}$ be a functor. Prove that for each $A \in  \mathcal{A}$ , there is a functor ${F}^{A} : \mathcal{B} \rightarrow  \mathcal{C}$ defined on objects $B \in  \mathcal{B}$ by ${F}^{A}\left( B\right)  = F\left( {A, B}\right)$ and on maps $g$ in $\mathcal{B}$ by ${F}^{A}\left( g\right)  = F\left( {{1}_{A}, g}\right)$ . Prove that for each $B \in  \mathcal{B}$ , there is a functor ${F}_{B} : \mathcal{A} \rightarrow  \mathcal{C}$ defined similarly.

(b) Let $F : \mathcal{A} \times  \mathcal{B} \rightarrow  \mathcal{C}$ be a functor. With notation as in (a), show that the families of functors ${\left( {F}^{A}\right) }_{A \in  \mathcal{A}}$ and ${\left( {F}_{B}\right) }_{B \in  \mathcal{B}}$ satisfy the following two conditions:

- if $A \in  \mathcal{A}$ and $B \in  \mathcal{B}$ then ${F}^{A}\left( B\right)  = {F}_{B}\left( A\right)$ ;

- if $f : A \rightarrow  {A}^{\prime }$ in $\mathcal{A}$ and $g : B \rightarrow  {B}^{\prime }$ in $\mathcal{B}$ then ${F}^{{A}^{\prime }}\left( g\right)  \circ  {F}_{B}\left( f\right)  = {F}_{{B}^{\prime }}\left( f\right)  \circ \; {F}^{A}\left( g\right)$ .

(c) Now take categories $\mathcal{A},\mathcal{B}$ and $\mathcal{C}$ , and take families of functors ${\left( {F}^{A}\right) }_{A \in  \mathcal{A}}$ and ${\left( {F}_{B}\right) }_{B \in  \mathcal{B}}$ satisfying the two conditions in (b). Prove that there is a unique functor $F : \mathcal{A} \times  \mathcal{B} \rightarrow  \mathcal{C}$ satisfying the equations in (a). (There is a unique functor' means in particular that there is a functor, so you have to prove existence as well as uniqueness.)

1.2.26 Fill in the details of Example 1.2.11, thus constructing a functor $C$ : ${\text{ Top }}^{\text{ op }} \rightarrow$ Ring.

1.2.27 Find an example of a functor $F : \mathcal{A} \rightarrow  \mathcal{B}$ such that $F$ is faithful but there exist distinct maps ${f}_{1}$ and ${f}_{2}$ in $\mathcal{A}$ with $F\left( {f}_{1}\right)  = F\left( {f}_{2}\right)$ .

1.2.28 (a) Of the examples of functors appearing in this section, which are faithful and which are full?

(b) Write down one example of a functor that is both full and faithful, one that is full but not faithful, one that is faithful but not full, and one that is neither.

1.2.29 (a) What are the subcategories of an ordered set? Which are full? (b) What are the subcategories of a group? (Careful!) Which are full?

### 1.3 Natural transformations

We now know about categories. We also know about functors, which are maps between categories. Perhaps surprisingly, there is a further notion of 'map between functors'. Such maps are called natural transformations. This notion only applies when the functors have the same domain and codomain:

$$
A\overset{F}{\underset{G}{ \rightarrow  }}\mathcal{B}\text{ . }
$$

To see how this might work, let us consider a special case. Let $\mathcal{A}$ be the discrete category (Example 1.1.8(b)) whose objects are the natural numbers $0,1,2,\ldots$ A functor $F$ from $\mathcal{A}$ to another category $\mathcal{B}$ is simply a sequence

$\left( {{F}_{0},{F}_{1},{F}_{2},\ldots }\right)$ of objects of $\mathcal{B}$ . Let $G$ be another functor from $\mathcal{A}$ to $\mathcal{B}$ , consisting of another sequence $\left( {{G}_{0},{G}_{1},{G}_{2},\ldots }\right)$ of objects of $\mathcal{B}$ . It would be reasonable to define a ’map’ from $F$ to $G$ to be a sequence

$$
\left( {{F}_{0}\overset{{\alpha }_{0}}{ \rightarrow  }{G}_{0},{F}_{1}\overset{{\alpha }_{1}}{ \rightarrow  }{G}_{1},{F}_{1}\overset{{\alpha }_{2}}{ \rightarrow  }{G}_{2},\ldots }\right)
$$

of maps in $\mathcal{B}$ . The situation can be depicted as follows:

<table><tr><td>$\mathcal{A}$</td><td>0</td><td>1</td><td>2</td><td></td></tr></table>

![35_767_617_436_177_0.jpg](images/35_767_617_436_177_0.jpg)

(The right-hand diagram should not be understood too literally. Some of the objects ${F}_{i}$ or ${G}_{i}$ might be equal, and there might be much else in $\mathcal{B}$ besides what is shown.)

This suggests that in the general case, a natural transformation between functors $\mathcal{A}\overset{\overset{F}{ \rightarrow  }}{\underset{G}{ \rightarrow  }}\mathcal{B}$ should consist of maps ${\alpha }_{A} : F\left( A\right)  \rightarrow  G\left( A\right)$ , one for each $A \in  \mathcal{A}$ . In the example above, the category $\mathcal{A}$ had the special property of not containing any nontrivial maps. In general, we demand some kind of compatibility between the maps in $\mathcal{A}$ and the maps ${\alpha }_{A}$ .

Definition 1.3.1 Let $\mathcal{A}$ and $\mathcal{B}$ be categories and let $\mathcal{A}\frac{F}{G} \geq  \mathcal{B}$ be functors. A natural transformation $\alpha  : F \rightarrow  G$ is a family ${\left( F\left( A\right) \overset{{\alpha }_{A}}{ \rightarrow  }G\left( A\right) \right) }_{A \in  \mathcal{A}}$ of maps in $\mathcal{B}$ such that for every map $A\overset{f}{ \rightarrow  }{A}^{\prime }$ in $\mathcal{A}$ , the square(1.3)

![35_660_1348_232_179_0.jpg](images/35_660_1348_232_179_0.jpg)

commutes. The maps ${\alpha }_{A}$ are called the components of $\alpha$ .

Remarks 1.3.2 (a) The definition of natural transformation is set up so that from each map $A\overset{f}{ \rightarrow  }{A}^{\prime }$ in $\mathcal{A}$ , it is possible to construct exactly one map $F\left( A\right)  \rightarrow  G\left( {A}^{\prime }\right)$ in $\mathcal{B}$ . When $f = {1}_{A}$ , this map is ${\alpha }_{A}$ . For a general $f$ , it is the diagonal of the square (1.3), and 'exactly one' implies that the square commutes.

(b) We write

$$
A\underset{G}{\underbrace{ \Downarrow  \alpha }}B
$$

to mean that $\alpha$ is a natural transformation from $F$ to $G$ .

Example 1.3.3 Let $\mathcal{A}$ be a discrete category, and let $F, G : \mathcal{A} \rightarrow  \mathcal{B}$ be functors. Then $F$ and $G$ are just families ${\left( F\left( A\right) \right) }_{A \in  \mathcal{A}}$ and ${\left( G\left( A\right) \right) }_{A \in  \mathcal{A}}$ of objects of $\mathcal{B}$ . A natural transformation $\alpha  : F \rightarrow  G$ is just a family ${\left( F\left( A\right) \overset{{\alpha }_{A}}{ \rightarrow  }G\left( A\right) \right) }_{A \in  \mathcal{A}}$ of maps in $\mathcal{B}$ , as claimed above in the case ob $\mathcal{A} = \mathbb{N}$ . In principle, this family must satisfy the naturality axiom (1.3) for every map $f$ in $\mathcal{A}$ ; but the only maps in $\mathcal{A}$ are the identities, and when $f$ is an identity, this axiom holds automatically.

Example 1.3.4 Recall from Examples 1.1.8 that a group (or more generally, a monoid) $G$ can be regarded as a one-object category. Also recall from Example 1.2.8 that a functor from the category $G$ to Set is nothing but a left $G$ -set. (Previously we used $\mathcal{G}$ to denote the category corresponding to the group $G$ ; from now on we use $G$ to denote them both.) Take two $G$ -sets, $S$ and $T$ . Since $S$ and $T$ can be regarded as functors $G \rightarrow$ Set, we can ask: what is a natural transformation

$$
G\underset{T}{\underbrace{\frac{s}{\parallel \alpha }}}\text{ Set, }
$$

in concrete terms?

Such a natural transformation consists of a single map in Set (since $G$ has just one object), satisfying some axioms. Precisely, it is a function $\alpha  : S \rightarrow  T$ such that $\alpha \left( {g \cdot  s}\right)  = g \cdot  \alpha \left( s\right)$ for all $s \in  S$ and $g \in  G$ . (Why?) In other words, it is just a map of $G$ -sets, sometimes called a $G$ -equivariant map.

Example 1.3.5 Fix a natural number $n$ . In this example, we will see how 'determinant of an $n \times  n$ matrix' can be understood as a natural transformation.

For any commutative ring $R$ , the $n \times  n$ matrices with entries in $R$ form a monoid ${M}_{n}\left( R\right)$ under multiplication. Moreover, any ring homomorphism $R \rightarrow \; S$ induces a monoid homomorphism ${M}_{n}\left( R\right)  \rightarrow  {M}_{n}\left( S\right)$ . This defines a functor ${M}_{n} :$ CRing $\rightarrow$ Mon from the category of commutative rings to the category of monoids.

Also, the elements of any ring $R$ form a monoid $U\left( R\right)$ under multiplication, giving another functor $U :$ CRing $\rightarrow$ Mon.

Now, every $n \times  n$ matrix $X$ over a commutative ring $R$ has a determinant $\mathop{\det }\limits_{R}\left( X\right)$ , which is an element of $R$ . Familiar properties of determinant -

$$
\mathop{\det }\limits_{R}\left( {XY}\right)  = \mathop{\det }\limits_{R}\left( X\right) \mathop{\det }\limits_{R}\left( Y\right) ,\;\mathop{\det }\limits_{R}\left( I\right)  = 1
$$

- tell us that for each $R$ , the function $\mathop{\det }\limits_{R} : {M}_{n}\left( R\right)  \rightarrow  U\left( R\right)$ is a monoid homomorphism. So, we have a family of maps

$$
{\left( {M}_{n}\left( R\right) \overset{{\det }_{R}}{ \rightarrow  }U\left( R\right) \right) }_{R \in  \mathbf{{CRing}}},
$$

and it makes sense to ask whether they define a natural transformation

![37_617_704_320_111_0.jpg](images/37_617_704_320_111_0.jpg)

Indeed, they do. That the naturality squares commute (check!) reflects the fact that determinant is defined in the same way for all rings. We do not use one definition of determinant for one ring and a different definition for another ring. Generally speaking, the naturality axiom (1.3) is supposed to capture the idea that the family ${\left( {\alpha }_{A}\right) }_{A \in  \mathcal{A}}$ is defined in a uniform way across all $A \in  \mathcal{A}$ .

Construction 1.3.6 Natural transformations are a kind of map, so we would expect to be able to compose them. We can. Given natural transformations

![37_675_1109_210_171_0.jpg](images/37_675_1109_210_171_0.jpg)

there is a composite natural transformation

![37_678_1346_196_108_0.jpg](images/37_678_1346_196_108_0.jpg)

defined by ${\left( \beta  \circ  \alpha \right) }_{A} = {\beta }_{A} \circ  {\alpha }_{A}$ for all $A \in  \mathcal{A}$ . There is also an identity natural transformation

![37_686_1539_181_109_0.jpg](images/37_686_1539_181_109_0.jpg)

on any functor $F$ , defined by ${\left( {1}_{F}\right) }_{A} = {1}_{F\left( A\right) }$ . So for any two categories $\mathcal{A}$ and $\mathcal{B}$ , there is a category whose objects are the functors from $\mathcal{A}$ to $\mathcal{B}$ and whose maps are the natural transformations between them. This is called the functor category from $\mathcal{A}$ to $\mathcal{B}$ , and written as $\left\lbrack  {\mathcal{A},\mathcal{B}}\right\rbrack$ or ${\mathcal{B}}^{\mathcal{A}}$ .

Example 1.3.7 Let 2 be the discrete category with two objects. A functor from 2 to a category $\mathcal{B}$ is a pair of objects of $\mathcal{B}$ , and a natural transformation is a pair of maps. The functor category $\left\lbrack  {2,\mathcal{B}}\right\rbrack$ is therefore isomorphic to the product category $\mathcal{B} \times  \mathcal{B}$ (Construction 1.1.11). This fits well with the alternative notation ${\mathcal{B}}^{2}$ for the functor category.

Example 1.3.8 Let $G$ be a monoid. Then $\left\lbrack  {G,\text{ Set }}\right\rbrack$ is the category of left $G$ - sets, and $\left\lbrack  {{G}^{\mathrm{{op}}},\text{ Set }}\right\rbrack$ is the category of right $G$ -sets (Example 1.2.14).

Example 1.3.9 Take ordered sets $A$ and $B$ , viewed as categories (as in Example 1.1.8(e)). Given order-preserving maps $A\underset{g}{\underbrace{f}} \geq  B$ , viewed as functors (as in Example 1.2.9), there is at most one natural transformation

![38_737_817_147_111_0.jpg](images/38_737_817_147_111_0.jpg)

and there is one if and only if $f\left( a\right)  \leq  g\left( a\right)$ for all $a \in  A$ . (The naturality axiom (1.3) holds automatically, because in an ordered set, all diagrams commute.) So $\left\lbrack  {A, B}\right\rbrack$ is an ordered set too; its elements are the order-preserving maps from $A$ to $B$ , and $f \leq  g$ if and only if $f\left( a\right)  \leq  g\left( a\right)$ for all $a \in  A$ .

Everyday phrases such as 'the cyclic group of order 6' and 'the product of two spaces' reflect the fact that given two isomorphic objects of a category, we usually neither know nor care whether they are actually equal. This is enormously important.

In particular, the lesson applies when the category concerned is a functor category. In other words, given two functors $F, G : \mathcal{A} \rightarrow  \mathcal{B}$ , we usually do not care whether they are literally equal. (Equality would imply that the objects $F\left( A\right)$ and $G\left( A\right)$ of $\mathcal{B}$ were equal for all $A \in  \mathcal{A}$ , a level of detail in which we have just declared ourselves to be uninterested.) What really matters is whether they are naturally isomorphic.

Definition 1.3.10 Let $\mathcal{A}$ and $\mathcal{B}$ be categories. A natural isomorphism between functors from $\mathcal{A}$ to $\mathcal{B}$ is an isomorphism in $\left\lbrack  {\mathcal{A},\mathcal{B}}\right\rbrack$ .

An equivalent form of the definition is often useful:

Lemma 1.3.11 Let $\mathcal{A}\underset{G}{\underbrace{ \Downarrow  \alpha }}.\&$ be a natural transformation. Then $\alpha$ is a natural isomorphism if and only if ${\alpha }_{A} : F\left( A\right)  \rightarrow  G\left( A\right)$ is an isomorphism for all $A \in  \mathcal{A}$ .

Proof Exercise 1.3.26.

Of course, we say that functors $F$ and $G$ are naturally isomorphic if there exists a natural isomorphism from $F$ to $G$ . Since natural isomorphism is just isomorphism in a particular category (namely, $\left\lbrack  {\mathcal{A},\mathcal{B}}\right\rbrack$ ), we already have notation for this: $F \cong  G$ .

Definition 1.3.12 Given functors $\mathcal{A}\overset{\overset{F}{ \rightarrow  }}{\underset{G}{ \rightarrow  }}\mathcal{B}$ , we say that

$$
F\left( A\right)  \cong  G\left( A\right) \text{ naturally in }A
$$

if $F$ and $G$ are naturally isomorphic.

This alternative terminology can be understood as follows. If $F\left( A\right)  \cong  G\left( A\right)$ naturally in $A$ then certainly $F\left( A\right)  \cong  G\left( A\right)$ for each individual $A$ , but more is true: we can choose isomorphisms ${\alpha }_{A} : F\left( A\right)  \rightarrow  G\left( A\right)$ in such a way that the naturality axiom (1.3) is satisfied.

Example 1.3.13 Let $F, G : \mathcal{A} \rightarrow  \mathcal{B}$ be functors from a discrete category $\mathcal{A}$ to a category $\mathcal{B}$ . Then $F \cong  G$ if and only if $F\left( A\right)  \cong  G\left( A\right)$ for all $A \in  \mathcal{A}$ .

So in this case, $F\left( A\right)  \cong  G\left( A\right)$ naturally in $A$ if and only if $F\left( A\right)  \cong  G\left( A\right)$ for all $A$ . But this is only true because $\mathcal{A}$ is discrete. In general, it is emphatically false. There are many examples of categories and functors $\mathcal{A}\overset{\overset{F}{ \rightarrow  }}{\underset{G}{ \rightarrow  }}\mathcal{B}$ such that $F\left( A\right)  \cong  G\left( A\right)$ for all $A \in  \mathcal{A}$ , but not naturally in $A$ . Exercise 1.3.31 gives an example from combinatorics.

Example 1.3.14 Let FDVect be the category of finite-dimensional vector spaces over some field $k$ . The dual vector space construction defines a contravariant functor from FDVect to itself (Example 1.2.12), and the double dual construction therefore defines a covariant functor from FDVect to itself.

Moreover, we have for each $V \in$ FDVect a canonical isomorphism ${\alpha }_{V}$ : $V \rightarrow  {V}^{* * }$ . Given $v \in  V$ , the element ${\alpha }_{V}\left( v\right)$ of ${V}^{* * }$ is ’evaluation at $v$ ’; that is, ${\alpha }_{V}\left( v\right)  : {V}^{ * } \rightarrow  k$ maps $\phi  \in  {V}^{ * }$ to $\phi \left( v\right)  \in  k$ . That ${\alpha }_{V}$ is an isomorphism is a standard result in the theory of finite-dimensional vector spaces.

This defines a natural transformation

![39_637_1613_275_132_0.jpg](images/39_637_1613_275_132_0.jpg)

from the identity functor to the double dual functor. By Lemma 1.3.11, $\alpha$ is a natural isomorphism. So ${1}_{\text{ FDVect }} \cong  {\left( \right) }^{* * }$ . Equivalently, in the language of Definition 1.3.12, $V \cong  {V}^{* * }$ naturally in $V$ .

This is one of those occasions on which category theory makes an intuition precise. In some informal sense, evident before you learn anything about category theory, the isomorphism between a finite-dimensional vector space and its double dual is 'natural' or 'canonical': no arbitrary choices are needed in order to define it. In contrast, to specify an isomorphism between $V$ and its single dual ${V}^{ * }$ , we need to make an arbitrary choice of basis, and the isomorphism really does depend on the basis that we choose.

In the example on vector spaces, the word canonical was used. It is an informal word, meaning something like 'God-given' or 'defined without making arbitrary choices’. For example, for any two sets $A$ and $B$ , there is a canonical bijection $A \times  B \rightarrow  B \times  A$ defined by $\left( {a, b}\right)  \mapsto  \left( {b, a}\right)$ , and there is a canonical function $A \times  B \rightarrow  A$ defined by $\left( {a, b}\right)  \mapsto  a$ . But the function $B \rightarrow  A$ defined by ’choose an element ${a}_{0} \in  A$ and send everything to ${a}_{0}$ ’ is not canonical, because the choice of ${a}_{0}$ is arbitrary.

The concept of natural isomorphism leads unavoidably to another central concept: equivalence of categories.

Two elements of a set are either equal or not. Two objects of a category can be equal, not equal but isomorphic, or not even isomorphic. As explained before Definition 1.3.10, the notion of equality between two objects of a category is unreasonably strict; it is usually isomorphism that we care about. So:

- the right notion of sameness of two elements of a set is equality;

- the right notion of sameness of two objects of a category is isomorphism.

When applied to a functor category $\left\lbrack  {\mathcal{A},\mathcal{B}}\right\rbrack$ , the second point tells us that:

- the right notion of sameness of two functors $\mathcal{A} \rightrightarrows  \mathcal{B}$ is natural isomorphism.

But what is the right notion of sameness of two categories? Isomorphism is unreasonably strict, as if $\mathcal{A} \cong  \mathcal{B}$ then there are functors

$$
A\overset{F}{\underset{G}{ \rightarrow  }}\mathcal{B} \tag{1.4}
$$

such that

$$
G \circ  F = {1}_{\mathcal{A}}\;\text{ and }\;F \circ  G = {1}_{\mathcal{B}}, \tag{1.5}
$$

and we have just seen that the notion of equality between functors is too strict. The most useful notion of sameness of categories, called 'equivalence', is

looser than isomorphism. To obtain the definition, we simply replace the unreasonably strict equalities in (1.5) by isomorphisms. This gives

$$
G \circ  F \cong  {1}_{\mathcal{A}}\;\text{ and }\;F \circ  G \cong  {1}_{\mathcal{B}}.
$$

Definition 1.3.15 An equivalence between categories $\mathcal{A}$ and $\mathcal{B}$ consists of a pair (1.4) of functors together with natural isomorphisms

$$
\eta  : {1}_{\mathcal{A}} \rightarrow  G \circ  F,\;\varepsilon  : F \circ  G \rightarrow  {1}_{\mathcal{B}}.
$$

If there exists an equivalence between $\mathcal{A}$ and $\mathcal{B}$ , we say that $\mathcal{A}$ and $\mathcal{B}$ are equivalent, and write $\mathcal{A} \simeq  \mathcal{B}$ . We also say that the functors $F$ and $G$ are equivalences.

The directions of $\eta$ and $\varepsilon$ are not very important, since they are isomorphisms anyway. The reason for this particular choice will become apparent when we come to discuss adjunctions (Section 2.2).

Warning 1.3.16 The symbol $\cong$ is used for isomorphism of objects of a category, and in particular for isomorphism of categories (which are objects of CAT). The symbol $\simeq$ is used for equivalence of categories. At least, this is the convention used in this book and by most category theorists, although it is far from universal in mathematics at large.

There is a very useful alternative characterization of those functors that are equivalences. First, we need a definition.

Definition 1.3.17 A functor $F : \mathcal{A} \rightarrow  \mathcal{B}$ is essentially surjective on objects if for all $B \in  \mathcal{B}$ , there exists $A \in  \mathcal{A}$ such that $F\left( A\right)  \cong  B$ .

Proposition 1.3.18 A functor is an equivalence if and only if it is full, faithful and essentially surjective on objects.

Proof Exercise 1.3.32.

This result can be compared to the theorem that every bijective group homomorphism is an isomorphism (that is, its inverse is also a homomorphism), or that a natural transformation whose components are isomorphisms is itself an isomorphism (Lemma 1.3.11). Those two results are useful because they allow us to show that a map is an isomorphism without directly constructing an inverse. Proposition 1.3.18 provides a similar service, enabling us to prove that a functor $F$ is an equivalence without actually constructing an ’inverse’ $G$ , or indeed an $\eta$ or an $\varepsilon$ (in the notation of Definition 1.3.15).

A corollary of Proposition 1.3.18 invites us to view full and faithful functors as, essentially, inclusions of full subcategories:

Corollary 1.3.19 Let $F : \mathcal{C} \rightarrow  \mathcal{D}$ be a full and faithful functor. Then $\mathcal{C}$ is equivalent to the full subcategory ${\mathcal{C}}^{\prime }$ of $\mathcal{D}$ whose objects are those of the form $F\left( C\right)$ for some $C \in  \mathcal{C}$ .

Proof The functor ${F}^{\prime } : \mathcal{C} \rightarrow  {\mathcal{C}}^{\prime }$ defined by ${F}^{\prime }\left( C\right)  = F\left( C\right)$ is full and faithful (since $F$ is) and essentially surjective on objects (by definition of ${\mathcal{C}}^{\prime }$ ).

This result is true, with the same proof, whether we interpret 'of the form $F\left( C\right)$ ’ to mean ’equal to $F\left( C\right)$ ’ or ’isomorphic to $F\left( C\right)$ ’.

Example 1.3.20 Let $\mathcal{A}$ be any category, and let $\mathcal{B}$ be any full subcategory containing at least one object from each isomorphism class of $\mathcal{A}$ . Then the inclusion functor $\mathcal{B} \hookrightarrow  \mathcal{A}$ is faithful (like any inclusion of subcategories), full, and essentially surjective on objects. Hence $\mathcal{B} \simeq  \mathcal{A}$ .

So if we take a category and remove some (but not all) of the objects in each isomorphism class, the slimmed-down version is equivalent to the original. Conversely, if we take a category and throw in some more objects, each of them isomorphic to one of the existing objects, it makes no difference: the new, bigger, category is equivalent to the old one.

For example, let FinSet be the category of finite sets and functions between them. For each natural number $n$ , choose a set $\mathbf{n}$ with $n$ elements, and let $\mathcal{B}$ be the full subcategory of FinSet with objects $\mathbf{0},\mathbf{1},\ldots$ . Then $\mathcal{B} \simeq$ FinSet, even though $\mathcal{B}$ is in some sense much smaller than FinSet.

Example 1.3.21 In Example 1.1.8(d), we saw that monoids are essentially the same thing as one-object categories. With the definition of equivalence in hand, we are nearly ready to make this statement precise. We are missing some set-theoretic language, and we will return to this result once we have that language (Example 3.2.11), but the essential point can be stated now.

Let $\mathcal{C}$ be the full subcategory of CAT whose objects are the one-object categories. Let Mon be the category of monoids. Then $\mathcal{C} \simeq$ Mon. To see this, first note that given any object $A$ of any category, the maps $A \rightarrow  A$ form a monoid under composition (at least, subject to some set-theoretic restrictions). There is, therefore, a canonical functor $F : \mathcal{C} \rightarrow$ Mon sending a one-object category to the monoid of maps from the single object to itself. This functor $F$ is full and faithful (by Example 1.2.7) and essentially surjective on objects. Hence $F$ is an equivalence.

Example 1.3.22 An equivalence of the form ${\mathcal{A}}^{\text{ op }} \simeq  \mathcal{B}$ is sometimes called a duality between $\mathcal{A}$ and $\mathcal{B}$ . One says that $\mathcal{A}$ is dual to $\mathcal{B}$ . There are many famous dualities in which $\mathcal{A}$ is a category of algebras and $\mathcal{B}$ is a category of spaces; recall the slogan 'algebra is dual to geometry' from Example 1.2.11.

Here are some quite advanced examples, well beyond the scope of this book.

- Stone duality: the category of Boolean algebras is dual to the category of totally disconnected compact Hausdorff spaces.

- Gelfand-Naimark duality: the category of commutative unital ${C}^{ * }$ -algebras is dual to the category of compact Hausdorff spaces. $\left( {{C}^{ * }\text{ -algebras are certain }}\right.$ algebraic structures important in functional analysis.)

- Algebraic geometers have several notions of 'space', one of which is 'affine variety'. Let $k$ be an algebraically closed field. Then the category of affine varieties over $k$ is dual to the category of finitely generated $k$ -algebras with no nontrivial nilpotents.

- Pontryagin duality: the category of locally compact abelian topological groups is dual to itself. As the words 'topological group' suggest, both sides of the duality are algebraic and geometric. Pontryagin duality is an abstraction of the properties of the Fourier transform.

Example 1.3.23 It is rarely useful to consider a category of structured objects in which the maps do not respect that structure. For instance, let $\mathcal{A}$ be the category whose objects are groups and whose maps are all functions between them, not necessarily homomorphisms. Let ${\mathbf{{Set}}}_{ \neq  \varnothing }$ be the category of nonempty sets. The forgetful functor $U : \mathcal{A} \rightarrow  {\mathbf{{Set}}}_{ \neq  \varnothing }$ is full and faithful. It is a (not profound) fact that every nonempty set can be given at least one group structure, so $U$ is essentially surjective on objects. Hence $U$ is an equivalence. This implies that the category $\mathcal{A}$ , although defined in terms of groups, is really just the category of nonempty sets.

Remarks 1.3.24 Here is a kind of review of the chapter so far. We have defined:

- categories (Section 1.1);

- functors between categories (Section 1.2);

- natural transformations between functors (Section 1.3);

- composition of functors

$$
\cdot   \rightarrow   \cdot   \rightarrow   \cdot
$$

and the identity functor on any category (Remark 1.2.2(b));

- composition of natural transformations

![43_733_1631_113_116_0.jpg](images/43_733_1631_113_116_0.jpg)

and the identity natural transformation on any functor (Construction 1.3.6).

This composition of natural transformations is sometimes called vertical composition. There is also horizontal composition, which takes natural transformations

![44_653_494_318_117_0.jpg](images/44_653_494_318_117_0.jpg)

and produces a natural transformation

![44_715_720_194_118_0.jpg](images/44_715_720_194_118_0.jpg)

traditionally written as ${\alpha }^{\prime } * \alpha$ . The component of ${\alpha }^{\prime } * \alpha$ at $A \in  \mathcal{A}$ is defined to be the diagonal of the naturality square

![44_655_983_312_180_0.jpg](images/44_655_983_312_180_0.jpg)

In other words, ${\left( {\alpha }^{\prime } * \alpha \right) }_{A}$ can be defined as either ${\alpha }_{G\left( A\right) }^{\prime } \circ  {F}^{\prime }\left( {\alpha }_{A}\right)$ or ${G}^{\prime }\left( {\alpha }_{A}\right)  \circ  {\alpha }_{F\left( A\right) }^{\prime }$ ; it makes no difference which, since they are equal.

The special cases of horizontal composition where either $\alpha$ or ${\alpha }^{\prime }$ is an identity are especially important, and have their own notation. Thus,

![44_424_1381_776_114_0.jpg](images/44_424_1381_776_114_0.jpg)

where ${\left( {\alpha }^{\prime }F\right) }_{A} = {\alpha }_{F\left( A\right) }^{\prime }$ , and

![44_424_1616_779_112_0.jpg](images/44_424_1616_779_112_0.jpg)

where ${\left( {F}^{\prime }\alpha \right) }_{A} = {F}^{\prime }\left( {\alpha }_{A}\right)$ .

Vertical and horizontal composition interact well: natural transformations obey the interchange law,

$$
\left( {{\beta }^{\prime } \circ  {\alpha }^{\prime }}\right)  * \left( {\beta  \circ  \alpha }\right)  = \left( {{\beta }^{\prime } * \beta }\right)  \circ  \left( {{\alpha }^{\prime } * \alpha }\right)  : {F}^{\prime } \circ  F \rightarrow  {H}^{\prime } \circ  H.
$$

![45_630_442_290_172_0.jpg](images/45_630_442_290_172_0.jpg)

As usual, a statement on composition is accompanied by a statement on identities: ${1}_{{F}^{\prime }} * {1}_{F} = {1}_{{F}^{\prime } \circ  F}$ too.

All of this enables us to construct, for any categories $\mathcal{A},{\mathcal{A}}^{\prime }$ and ${\mathcal{A}}^{\prime \prime }$ , a functor

$$
\left\lbrack  {{\mathcal{A}}^{\prime },{\mathcal{A}}^{\prime \prime }}\right\rbrack   \times  \left\lbrack  {\mathcal{A},{\mathcal{A}}^{\prime }}\right\rbrack   \rightarrow  \left\lbrack  {\mathcal{A},{\mathcal{A}}^{\prime \prime }}\right\rbrack
$$

given on objects by $\left( {{F}^{\prime }, F}\right)  \mapsto  {F}^{\prime } \circ  F$ and on maps by $\left( {{\alpha }^{\prime },\alpha }\right)  \mapsto  {\alpha }^{\prime } * \alpha$ . In particular, if ${F}^{\prime } \cong  {G}^{\prime }$ and $F \cong  G$ then ${F}^{\prime } \circ  F \cong  {G}^{\prime } \circ  G$ , since functors preserve isomorphism (Exercise 1.2.21).

(The existence of this functor is similar to the fact that inside a category $\mathcal{C}$ , we have, for any objects $A,{A}^{\prime }$ and ${A}^{\prime \prime }$ , a function

$$
\mathcal{C}\left( {{A}^{\prime },{A}^{\prime \prime }}\right)  \times  \mathcal{C}\left( {A,{A}^{\prime }}\right)  \rightarrow  \mathcal{C}\left( {A,{A}^{\prime \prime }}\right) ,
$$

given by $\left( {{f}^{\prime }, f}\right)  \mapsto  {f}^{\prime } \circ  f$ .)

The diagrams above contain not only objects (0-dimensional) and arrows $\rightarrow$ (1-dimensional), but also double arrows $\Rightarrow$ sweeping out 2-dimensional regions between arrows. What we are implicitly doing is called 2-category theory. There is a 2-category of categories, functors and natural transformations, whose anatomy we have just been describing. If we are really serious about categories, we have to get serious about 2-categories. And if we are really serious about 2-categories, we have to get serious about 3-categories... and before we know it, we are studying $\infty$ -categories. But in this book, we climb no higher than the first rung or two of this infinite ladder.

## Exercises

1.3.25 Find three examples of natural transformations not mentioned above.

1.3.26 Prove Lemma 1.3.11.

1.3.27 Let $\mathcal{A}$ and $\mathcal{B}$ be categories. Prove that $\left\lbrack  {{\mathcal{A}}^{\mathrm{{op}}},{\mathcal{B}}^{\mathrm{{op}}}}\right\rbrack   \cong  {\left\lbrack  \mathcal{A},\mathcal{B}\right\rbrack  }^{\mathrm{{op}}}$ .

1.3.28 Let $A$ and $B$ be sets, and denote by ${B}^{A}$ the set of functions from $A$ to $B$ . Write down:

(a) a canonical function $A \times  {B}^{A} \rightarrow  B$ ;

(b) a canonical function $A \rightarrow  {B}^{\left( {B}^{A}\right) }$ .

(Although in principle there could be many such canonical functions, in both these cases there is only one.)

1.3.29 Here we consider natural transformations between functors whose domain is a product category $\mathcal{A} \times  \mathcal{B}$ . Your task is to show that naturality in two variables simultaneously is equivalent to naturality in each variable separately.

Take functors $F, G : \mathcal{A} \times  \mathcal{B} \rightarrow  \mathcal{C}$ . For each $A \in  \mathcal{A}$ , there are functors ${F}^{A},{G}^{A} : \mathcal{B} \rightarrow  \mathcal{C}$ , as in Exercise 1.2.25. Similarly, for each $B \in  \mathcal{B}$ , there are functors ${F}_{B},{G}_{B} : \mathcal{A} \rightarrow  \mathcal{C}$ .

Let ${\left( {\alpha }_{A, B} : F\left( A, B\right)  \rightarrow  G\left( A, B\right) \right) }_{A \in  \mathcal{A}, B \in  \mathcal{B}}$ be a family of maps. Show that this family is a natural transformation $F \rightarrow  G$ if and only if it satisfies the following two conditions:

- for each $A \in  \mathcal{A}$ , the family ${\left( {\alpha }_{A, B} : {F}^{A}\left( B\right)  \rightarrow  {G}^{A}\left( B\right) \right) }_{B \in  \mathcal{B}}$ is a natural transformation ${F}^{A} \rightarrow  {G}^{A}$ ;

- for each $B \in  \mathcal{B}$ , the family ${\left( {\alpha }_{A, B} : {F}_{B}\left( A\right)  \rightarrow  {G}_{B}\left( A\right) \right) }_{A \in  \mathcal{A}}$ is a natural transformation ${F}_{B} \rightarrow  {G}_{B}$ .

1.3.30 Let $G$ be a group. For each $g \in  G$ , there is a unique homomorphism $\phi  : \mathbb{Z} \rightarrow  G$ satisfying $\phi \left( 1\right)  = g$ . Thus, elements of $G$ are essentially the same thing as homomorphisms $\mathbb{Z} \rightarrow  G$ . When groups are regarded as one-object categories, homomorphisms $\mathbb{Z} \rightarrow  G$ are in turn the same as functors $\mathbb{Z} \rightarrow  G$ . Natural isomorphism defines an equivalence relation on the set of functors $\mathbb{Z} \rightarrow \; G$ , and, therefore, an equivalence relation on $G$ itself. What is this equivalence relation, in purely group-theoretic terms?

(First have a guess. For a general group $G$ , what equivalence relations on $G$ can you think of?)

1.3.31 A permutation of a set $X$ is a bijection $X \rightarrow  X$ . Write $\operatorname{Sym}\left( X\right)$ for the set of permutations of $X$ . A total order on a set $X$ is an order $\leq$ such that for all $x, y \in  X$ , either $x \leq  y$ or $y \leq  x$ ; so a total order on a finite set amounts to a way of placing its elements in sequence. Write $\operatorname{Ord}\left( X\right)$ for the set of total orders on $X$ .

Let $\mathcal{B}$ denote the category of finite sets and bijections.

(a) Give a definition of Sym on maps in $\mathcal{B}$ in such a way that Sym becomes a functor $\mathcal{B} \rightarrow$ Set. Do the same for Ord. Both your definitions should be canonical (no arbitrary choices).

(b) Show that there is no natural transformation Sym $\rightarrow$ Ord. (Hint: consider identity permutations.)

(c) For an $n$ -element set $X$ , how many elements do the sets $\operatorname{Sym}\left( X\right)$ and $\operatorname{Ord}\left( X\right)$ have?

Conclude that $\operatorname{Sym}\left( X\right)  \cong  \operatorname{Ord}\left( X\right)$ for all $X \in  \mathcal{B}$ , but not naturally in $X \in  \mathcal{B}$ . (The moral is that for each finite set $X$ , there are exactly as many permutations of $X$ as there are total orders on $X$ , but there is no natural way of matching them up.)

1.3.32 In this exercise, you will prove Proposition 1.3.18. Let $F : \mathcal{A} \rightarrow  \mathcal{B}$ be a functor.

(a) Suppose that $F$ is an equivalence. Prove that $F$ is full, faithful and essentially surjective on objects. (Hint: prove faithfulness before fullness.)

(b) Now suppose instead that $F$ is full, faithful and essentially surjective on objects. For each $B \in  \mathcal{B}$ , choose an object $G\left( B\right)$ of $\mathcal{A}$ and an isomorphism ${\varepsilon }_{B} : F\left( {G\left( B\right) }\right)  \rightarrow  B$ . Prove that $G$ extends to a functor in such a way that ${\left( {\varepsilon }_{B}\right) }_{B \in  \mathcal{B}}$ is a natural isomorphism ${FG} \rightarrow  {1}_{\mathcal{B}}$ . Then construct a natural isomorphism ${1}_{\mathcal{A}} \rightarrow  {GF}$ , thus proving that $F$ is an equivalence.

1.3.33 This exercise makes precise the idea that linear algebra can equivalently be done with matrices or with linear maps.

Fix a field $k$ . Let Mat be the category whose objects are the natural numbers and with

$$
\operatorname{Mat}\left( {m, n}\right)  = \{ n \times  m\text{ matrices over }k\} .
$$

Prove that Mat is equivalent to FDVect, the category of finite-dimensional vector spaces over $k$ . Does your equivalence involve a canonical functor from Mat to FDVect, or from FDVect to Mat?

(Part of the exercise is to work out what composition in the category Mat is supposed to be; there is only one sensible possibility. Proposition 1.3.18 makes the exercise easier.)

1.3.34 Show that equivalence of categories is an equivalence relation. (Not as obvious as it looks.)

2

## Adjoints

The slogan of Saunders Mac Lane's book Categories for the Working Mathematician is:

Adjoint functors arise everywhere.

We will see the truth of this, meeting examples of adjoint functors from diverse parts of mathematics. To complement the understanding provided by examples, we will approach the theory of adjoints from three different directions, each of which carries its own intuition. Then we will prove that the three approaches are equivalent.

Understanding adjointness gives you a valuable addition to your mathematical toolkit. Most professional pure mathematicians know what categories and functors are, but far fewer know about adjoints. More should: adjoint functors are both common and easy, and knowing about adjoints helps you to spot patterns in the mathematical landscape.

### 2.1 Definition and examples

Consider a pair of functors in opposite directions, $F : \mathcal{A} \rightarrow  \mathcal{B}$ and $G : \mathcal{B} \rightarrow \; \mathcal{A}$ . Roughly speaking, $F$ is said to be left adjoint to $G$ if, whenever $A \in  \mathcal{A}$ and $B \in  \mathcal{B}$ , maps $F\left( A\right)  \rightarrow  B$ are essentially the same thing as maps $A \rightarrow  G\left( B\right)$ .

Definition 2.1.1 Let $\mathcal{A}\overset{F}{\underset{{G}_{G}}{ \rightarrow  }}\mathcal{B}$ be categories and functors. We say that $F$ is left adjoint to $G$ , and $G$ is right adjoint to $F$ , and write $F \dashv  G$ , if

$$
\mathcal{B}\left( {F\left( A\right) , B}\right)  \cong  \mathcal{A}\left( {A, G\left( B\right) }\right) \tag{2.1}
$$

naturally in $A \in  \mathcal{A}$ and $B \in  \mathcal{B}$ . The meaning of ’naturally’ is defined below. An adjunction between $F$ and $G$ is a choice of natural isomorphism (2.1).

’Naturally in $A \in  \mathcal{A}$ and $B \in  \mathcal{B}$ , means that there is a specified bijection (2.1) for each $A \in  \mathcal{A}$ and $B \in  \mathcal{B}$ , and that it satisfies a naturality axiom. To state it, we need some notation. Given objects $A \in  \mathcal{A}$ and $B \in  \mathcal{B}$ , the correspondence (2.1) between maps $F\left( A\right)  \rightarrow  B$ and $A \rightarrow  G\left( B\right)$ is denoted by a horizontal bar, in both directions:

$$
\left( {F\left( A\right) \overset{g}{ \rightarrow  }B}\right)  \mapsto  \left( {A\overset{\bar{g}}{ \rightarrow  }G\left( B\right) }\right) ,
$$

$$
\left( {F\left( A\right) \overset{\bar{f}}{ \rightarrow  }B}\right)  \leftrightarrow  \left( {A\overset{f}{ \rightarrow  }G\left( B\right) }\right) .
$$

So $\overline{\bar{f}} = f$ and $\overline{\bar{g}} = g$ . We call $\bar{f}$ the transpose of $f$ , and similarly for $g$ . The naturality axiom has two parts:

$$
\overline{\left( F\left( A\right) \overset{g}{ \rightarrow  }B\overset{q}{ \rightarrow  }{B}^{\prime }\right) } = \left( {A\overset{\bar{g}}{ \rightarrow  }G\left( B\right) \overset{G\left( q\right) }{ \rightarrow  }G\left( {B}^{\prime }\right) }\right) \tag{2.2}
$$

(that is, $\overline{q \circ  g} = G\left( q\right)  \circ  \bar{g}$ ) for all $g$ and $q$ , and

$$
\overline{\left( {A}^{\prime } \rightarrow  A \rightarrow  G\left( B\right) \right) } = \left( {F\left( {A}^{\prime }\right) \overset{F\left( p\right) }{ \rightarrow  }F\left( A\right) \overset{\bar{f}}{ \rightarrow  }B}\right) \tag{2.3}
$$

for all $p$ and $f$ . It makes no difference whether we put the long bar over the left or the right of these equations, since bar is self-inverse.

Remarks 2.1.2 (a) The naturality axiom might seem ad hoc, but we will see in Chapter 4 that it simply says that two particular functors are naturally isomorphic. In this section, we ignore the naturality axiom altogether, trusting that it embodies our usual intuitive idea of naturality: something defined without making any arbitrary choices.

(b) The naturality axiom implies that from each array of maps

$$
{A}_{0} \rightarrow  \cdots  \rightarrow  {A}_{n},\;F\left( {A}_{n}\right)  \rightarrow  {B}_{0},\;{B}_{0} \rightarrow  \cdots  \rightarrow  {B}_{m},
$$

it is possible to construct exactly one map

$$
{A}_{0} \rightarrow  G\left( {B}_{m}\right) \text{ . }
$$

Compare the comments on the definitions of category, functor and natural transformation (Remarks 1.1.2(b), 1.2.2(a), and 1.3.2(a)).

(c) Not only do adjoint functors arise everywhere; better, whenever you see a pair of functors $\mathcal{A} \rightleftarrows  \mathcal{B}$ , there is an excellent chance that they are adjoint (one way round or the other).

For example, suppose you get talking to a mathematician who tells you that her work involves Lie algebras and associative algebras. You try to object that you don't know what either of those things is, but she carries on talking anyway, explaining that there's a way of turning any Lie algebra into an associative algebra, and also a way of turning any associative algebra into a Lie algebra. At this point, even without knowing what she's talking about, you should bet her that one process is adjoint to the other. This almost always works.

(d) A given functor $G$ may or may not have a left adjoint, but if it does, it is unique up to isomorphism, so we may speak of 'the left adjoint of G'. The same goes for right adjoints. We prove this later (Example 4.3.13).

You might ask 'what do we gain from knowing that two functors are adjoint?' The uniqueness is a crucial part of the answer. Let us return to the example of (c). It would take you only a few minutes to learn what Lie algebras are, what associative algebras are, and what the standard functor $G$ is that turns an associative algebra into a Lie algebra. What about the functor $F$ in the opposite direction? The description of $F$ that you will find in most algebra books (under 'universal enveloping algebra') takes much longer to understand. However, you can bypass that process completely, just by knowing that $F$ is the left adjoint of $G$ . Since $G$ can have only one left adjoint, this characterizes $F$ completely. In a sense, it tells you all you need to know.

Examples 2.1.3 (Algebra: free 4 forgetful) Forgetful functors between categories of algebraic structures usually have left adjoints. For instance:

(a) Let $k$ be a field. There is an adjunction

![50_789_1158_90_145_0.jpg](images/50_789_1158_90_145_0.jpg)

where $U$ is the forgetful functor of Example 1.2.3(b) and $F$ is the free functor of Example 1.2.4(c). Adjointness says that given a set $S$ and a vector space $V$ , a linear map $F\left( S\right)  \rightarrow  V$ is essentially the same thing as a function $S \rightarrow  U\left( V\right)$ .

We saw this in Example 0.4, but let us now check it in detail.

Fix a set $S$ and a vector space $V$ . Given a linear map $g : F\left( S\right)  \rightarrow  V$ , we may define a map of sets $\bar{g} : S \rightarrow  U\left( V\right)$ by $\bar{g}\left( s\right)  = g\left( s\right)$ for all $s \in  S$ . This gives a function

$$
{\operatorname{\mathbf{V} \mathbf{e} \mathbf{c} \mathbf{t} }}_{k}\left( {F\left( S\right) , V}\right)  \rightarrow  \operatorname{\mathbf{S} \mathbf{e} \mathbf{t} }\left( {S, U\left( V\right) }\right)
$$

$$
g\; \mapsto  \;\bar{g}
$$

In the other direction, given a map of sets $f : S \rightarrow  U\left( V\right)$ , we may define a linear map $\bar{f} : F\left( S\right)  \rightarrow  V$ by $\bar{f}\left( {\mathop{\sum }\limits_{{s \in  S}}{\lambda }_{s}s}\right)  = \mathop{\sum }\limits_{{s \in  S}}{\lambda }_{s}f\left( s\right)$ for all formal linear combinations $\sum {\lambda }_{s}s \in  F\left( S\right)$ . This gives a function

$$
\operatorname{Set}\left( {S, U\left( V\right) }\right)  \rightarrow  {\operatorname{Vect}}_{k}\left( {F\left( S\right) , V}\right)
$$

$$
f\; \mapsto  \;\bar{f}\text{ . }
$$

These two functions 'bar' are mutually inverse: for any linear map $g$ : $F\left( S\right)  \rightarrow  V$ , we have

$$
\overline{\bar{g}}\left( {\mathop{\sum }\limits_{{s \in  S}}{\lambda }_{s}s}\right)  = \mathop{\sum }\limits_{{s \in  S}}{\lambda }_{s}\bar{g}\left( s\right)  = \mathop{\sum }\limits_{{s \in  S}}{\lambda }_{s}g\left( s\right)  = g\left( {\mathop{\sum }\limits_{{s \in  S}}{\lambda }_{s}s}\right)
$$

for all $\sum {\lambda }_{s}s \in  F\left( S\right)$ , so $\overline{\bar{g}} = g$ , and for any map of sets $f : S \rightarrow  U\left( V\right)$ , we have

$$
\bar{\bar{f}}\left( s\right)  = \bar{f}\left( s\right)  = f\left( s\right)
$$

for all $s \in  S$ , so $\overline{\bar{f}} = f$ . We therefore have a canonical bijection between ${\operatorname{\mathbf{V} \mathbf{e} \mathbf{c} \mathbf{t} }}_{k}\left( {F\left( S\right) , V}\right)$ and $\operatorname{\mathbf{S} \mathbf{e} \mathbf{t} }\left( {S, U\left( V\right) }\right)$ for each $S \in  \operatorname{\mathbf{S} \mathbf{e} \mathbf{t} }$ and $V \in  {\operatorname{\mathbf{V} \mathbf{e} \mathbf{c} \mathbf{t} }}_{k}$ , as required.

Here we have been careful to distinguish between the vector space $V$ and its underlying set $U\left( V\right)$ . Very often, though, in category theory as in mathematics at large, the symbol for a forgetful functor is omitted. In this example, that would mean dropping the $U$ and leaving the reader to figure out whether each occurrence of $V$ is intended to denote the vector space itself or its underlying set. We will soon start using such notational shortcuts ourselves.

(b) In the same way, there is an adjunction

![51_754_1276_90_143_0.jpg](images/51_754_1276_90_143_0.jpg)

where $F$ and $U$ are the free and forgetful functors of Examples 1.2.3(a) and 1.2.4(a).

The free group functor is tricky to construct explicitly. In Chapter 6, we will prove a result (the general adjoint functor theorem) guaranteeing that $U$ and many functors like it all have left adjoints. To some extent, this removes the need to construct $F$ explicitly, as observed in Remark 2.1.2(d). The point can be overstated: for a group theorist, the more descriptions of free groups that are available, the better. Explicit constructions really can be useful. But it is an important general principle that forgetful functors of this type always have left adjoints.

(c) There is an adjunction

![52_791_406_87_147_0.jpg](images/52_791_406_87_147_0.jpg)

where $U$ is the inclusion functor of Example 1.2.3(d). If $G$ is a group then $F\left( G\right)$ is the abelianization ${G}_{\mathrm{{ab}}}$ of $G$ . This is an abelian quotient group of $G$ , with the property that every map from $G$ to an abelian group factorizes uniquely through ${G}_{\mathrm{{ab}}}$ :

![52_749_719_173_149_0.jpg](images/52_749_719_173_149_0.jpg)

Here $\eta$ is the natural map from $G$ to its quotient ${G}_{\mathrm{{ab}}}$ , and $A$ is any abelian group. (We have adopted the abuse of notation advertised in example (a), omitting the symbol $U$ at several places in this diagram.) The bijection

$$
\mathbf{{Ab}}\left( {{G}_{\mathrm{{ab}}}, A}\right)  \cong  \operatorname{Grp}\left( {G, U\left( A\right) }\right)
$$

is given in the left-to-right direction by $\psi  \mapsto  \psi  \circ  \eta$ , and in the right-to-left direction by $\phi  \mapsto  \overline{\phi }$ .

(To construct ${G}_{\mathrm{{ab}}}$ , let ${G}^{\prime }$ be the smallest normal subgroup of $G$ containing ${xy}{x}^{-1}{y}^{-1}$ for all $x, y \in  G$ , and put ${G}_{\mathrm{{ab}}} = G/{G}^{\prime }$ . The kernel of any homomorphism from $G$ to an abelian group contains ${G}^{\prime }$ , and the universal property follows.)

(d) There are adjunctions

![52_768_1322_135_141_0.jpg](images/52_768_1322_135_141_0.jpg)

between the categories of groups and monoids. The middle functor $U$ is inclusion. The left adjoint $F$ is, again, tricky to describe explicitly. Informally, $F\left( M\right)$ is obtained from $M$ by throwing in an inverse to every element. (For example, if $M$ is the additive monoid of natural numbers then $F\left( M\right)$ is the group of integers.) Again, the general adjoint functor theorem (Theorem 6.3.10) guarantees the existence of this adjoint.

This example is unusual in that forgetful functors do not usually have right adjoints. Here, given a monoid $M$ , the group $R\left( M\right)$ is the submonoid of $M$ consisting of all the invertible elements.

The category Grp is both a reflective and a coreflective subcategory of Mon. This means, by definition, that the inclusion functor Grp $\hookrightarrow$ Mon has both a left and a right adjoint. The previous example tells us that $\mathbf{{Ab}}$ is a reflective subcategory of Grp.

(e) Let Field be the category of fields, with ring homomorphisms as the maps. The forgetful functor Field $\rightarrow$ Set does not have a left adjoint. (For a proof, see Example 6.3.5.) The theory of fields is unlike the theories of groups, rings, and so on, because the operation $x \mapsto  {x}^{-1}$ is not defined for all $x$ (only for $x \neq  0$ ).

Remark 2.1.4 At several points in this book, we make contact with the idea of an algebraic theory. You already know several examples: the theory of groups is an algebraic theory, as are the theory of rings, the theory of vector spaces over $\mathbb{R}$ , the theory of vector spaces over $\mathbb{C}$ , the theory of monoids, and (rather trivially) the theory of sets. After reading the description below, you might conclude that the word 'theory' is overly grand, and that 'definition' would be more appropriate. Nevertheless, this is the established usage.

We will not need to define 'algebraic theory' formally, but it will be important to have the general idea. Let us begin by considering the theory of groups.

A group can be defined as a set $X$ equipped with a function $\cdot   : X \times  X \rightarrow  X$ (multiplication), another function ${\left( \right) }^{-1} : X \rightarrow  X$ (inverse), and an element $e \in \; X$ (the identity), satisfying a familiar list of equations. More systematically, the three pieces of structure on $X$ can be seen as maps of sets

$$
\because {X}^{2} \rightarrow  X,\;{\left( \right) }^{-1} : {X}^{1} \rightarrow  X,\;e : {X}^{0} \rightarrow  X,
$$

where in the last case, ${X}^{0}$ is the one-element set 1 and we are using the observation that a map $1 \rightarrow  X$ of sets is essentially the same thing as an element of $X$ .

(You may be more familiar with a definition of group in which only the multiplication and perhaps the identity are specified as pieces of structure, with the existence of inverses required as a property. In that approach, the definition is swiftly followed by a lemma on uniqueness of inverses, guaranteeing that it makes sense to speak of the inverse of an element. The two approaches are equivalent, but for many purposes, it is better to frame the definition in the way described in the previous paragraph.)

An algebraic theory consists of two things: first, a collection of operations, each with a specified arity (number of inputs), and second, a collection of equations. For example, the theory of groups has one operation of arity 2, one of arity 1, and one of arity 0 . An algebra or model for an algebraic theory consists of a set $X$ together with a specified map ${X}^{n} \rightarrow  X$ for each operation of arity $n$ , such that the equations hold everywhere. For example, an algebra for the theory of groups is exactly a group.

A more subtle example is the theory of vector spaces over $\mathbb{R}$ . This is an algebraic theory with, among other things, an infinite number of operations of arity 1: for each $\lambda  \in  \mathbb{R}$ , we have the operation $\lambda  \cdot   -  : X \rightarrow  X$ of scalar multiplication by $\lambda$ (for any vector space $X$ ). There is nothing special about the field $\mathbb{R}$ here; the only point is that it was chosen in advance. The theory of vector spaces over $\mathbb{R}$ is different from the theory of vector spaces over $\mathbb{C}$ , because they have different operations of arity 1 .

In a nutshell, the main property of algebras for an algebraic theory is that the operations are defined everywhere on the set, and the equations hold everywhere too. For example, every element of a group has a specified inverse, and every element $x$ satisfies the equation $x \cdot  {x}^{-1} = 1$ . This is why the theories of groups, rings, and so on, are algebraic theories, but the theory of fields is not.

Example 2.1.5 There are adjunctions

![54_744_944_135_143_0.jpg](images/54_744_944_135_143_0.jpg)

where $U$ sends a space to its set of points, $D$ equips a set with the discrete topology, and I equips a set with the indiscrete topology.

Example 2.1.6 Given sets $A$ and $B$ , we can form their (cartesian) product $A \times  B$ . We can also form the set ${B}^{A}$ of functions from $A$ to $B$ . This is the same as the set $\operatorname{Set}\left( {A, B}\right)$ , but we tend to use the notation ${B}^{A}$ when we want to emphasize that it is an object of the same category as $A$ and $B$ .

Now fix a set $B$ . Taking the product with $B$ defines a functor

$$
-  \times  B : \;\text{ Set } \rightarrow  \text{ Set }
$$

$$
A\; \mapsto  \;A \times  B.
$$

(Here we are using the blank notation introduced in Example 1.2.12.) There is also a functor

$$
{\left( -\right) }^{B} : \text{ Set } \rightarrow  \text{ Set }
$$

$$
C\; \mapsto  \;{C}^{B}
$$

Moreover, there is a canonical bijection

$$
\operatorname{Set}\left( {A \times  B, C}\right)  \cong  \operatorname{Set}\left( {A,{C}^{B}}\right)
$$

for any sets $A$ and $C$ . It is defined by simply changing the punctuation: given a map $g : A \times  B \rightarrow  C$ , define $\bar{g} : A \rightarrow  {C}^{B}$ by

$$
\left( {\bar{g}\left( a\right) }\right) \left( b\right)  = g\left( {a, b}\right)
$$

![55_645_359_265_293_0.jpg](images/55_645_359_265_293_0.jpg)

Figure 2.1 In Set, a map $A \times  B \rightarrow  C$ can be seen as a way of assigning to each element of $A$ a map $B \rightarrow  C$ .

$\left( {a \in  A, b \in  B}\right)$ , and in the other direction, given $f : A \rightarrow  {C}^{B}$ , define $\bar{f}$ : $A \times  B \rightarrow  C$ by

$$
\bar{f}\left( {a, b}\right)  = \left( {f\left( a\right) }\right) \left( b\right)
$$

$\left( {a \in  A, b \in  B}\right)$ . Figure 2.1 shows an example with $A = B = C = \mathbb{R}$ . By slicing up the surface as shown, a map ${\mathbb{R}}^{2} \rightarrow  \mathbb{R}$ can be seen as a map from $\mathbb{R}$ to $\{$ maps $\mathbb{R} \rightarrow  \mathbb{R}\}$ .

Putting all this together, we obtain an adjunction

![55_712_1199_129_140_0.jpg](images/55_712_1199_129_140_0.jpg)

for every set $B$ .

Definition 2.1.7 Let $\mathcal{A}$ be a category. An object $I \in  \mathcal{A}$ is initial if for every $A \in  \mathcal{A}$ , there is exactly one map $I \rightarrow  A$ . An object $T \in  \mathcal{A}$ is terminal if for every $A \in  \mathcal{A}$ , there is exactly one map $A \rightarrow  T$ .

For example, the empty set is initial in Set, the trivial group is initial in Grp, and $\mathbb{Z}$ is initial in Ring (Example 0.2). The one-element set is terminal in Set, the trivial group is terminal (as well as initial) in Grp, and the trivial (one-element) ring is terminal in Ring. The terminal object of CAT is the category 1 containing just one object and one map (necessarily the identity on that object).

A category need not have an initial object, but if it does have one, it is unique up to isomorphism. Indeed, it is unique up to unique isomorphism, as follows.

Lemma 2.1.8 Let I and ${I}^{\prime }$ be initial objects of a category. Then there is a unique isomorphism $I \rightarrow  {I}^{\prime }$ . In particular, $I \cong  {I}^{\prime }$ .

Proof Since $I$ is initial, there is a unique map $f : I \rightarrow  {I}^{\prime }$ . Since ${I}^{\prime }$ is initial, there is a unique map ${f}^{\prime } : {I}^{\prime } \rightarrow  I$ . Now ${f}^{\prime } \circ  f$ and ${1}_{I}$ are both maps $I \rightarrow  I$ , and $I$ is initial, so ${f}^{\prime } \circ  f = {1}_{I}$ . Similarly, $f \circ  {f}^{\prime } = {1}_{{I}^{\prime }}$ . Hence $f$ is an isomorphism, as required.

Example 2.1.9 Initial and terminal objects can be described as adjoints. Let $\mathcal{A}$ be a category. There is precisely one functor $\mathcal{A} \rightarrow  \mathbf{1}$ . Also, a functor $\mathbf{1} \rightarrow \; \mathcal{A}$ is essentially just an object of $\mathcal{A}$ (namely, the object to which the unique object of1is mapped). Viewing functors $\mathbf{1} \rightarrow  \mathcal{A}$ as objects of $\mathcal{A}$ , a left adjoint to $\mathcal{A} \rightarrow  \mathbf{1}$ is exactly an initial object of $\mathcal{A}$ .

Similarly, a right adjoint to the unique functor $\mathcal{A} \rightarrow  \mathbf{1}$ is exactly a terminal object of $\mathcal{A}$ .

Remark 2.1.10 In the language introduced in Remark 1.1.10, the concept of terminal object is dual to the concept of initial object. (More generally, the concepts of left and right adjoint are dual to one another.) Since any two initial objects of a category are uniquely isomorphic, the principle of duality implies that the same is true of terminal objects.

Remark 2.1.11 Adjunctions can be composed. Take adjunctions

$$
A\overset{\overset{F}{ \rightarrow  }}{\underset{G}{ \leftarrow  }}{A}^{\prime }\overset{\overset{{F}^{\prime }}{ \rightarrow  }}{\underset{{G}^{\prime }}{ \leftarrow  }}{A}^{\prime \prime }
$$

where the $\bot$ symbol is a rotated $\dashv$ (thus, $F \dashv  G$ and ${F}^{\prime } \dashv  {G}^{\prime }$ ). Then we obtain an adjunction

$$
\mathcal{A}\frac{{F}^{\prime } \circ  F}{ < \frac{1}{G \circ  {G}^{\prime }}}{\mathcal{A}}^{\prime \prime }
$$

since for $A \in  \mathcal{A}$ and ${A}^{\prime \prime } \in  {\mathcal{A}}^{\prime \prime }$ ,

$$
{\mathcal{A}}^{\prime \prime }\left( {{F}^{\prime }\left( {F\left( A\right) }\right) ,{A}^{\prime \prime }}\right)  \cong  {\mathcal{A}}^{\prime }\left( {F\left( A\right) ,{G}^{\prime }\left( {A}^{\prime \prime }\right) }\right)  \cong  \mathcal{A}\left( {A, G\left( {{G}^{\prime }\left( {A}^{\prime \prime }\right) }\right) }\right)
$$

naturally in $A$ and ${A}^{\prime \prime }$ .

## Exercises

2.1.12 Find three examples of adjoint functors not mentioned above. Do the same for initial and terminal objects.

2.1.13 What can be said about adjunctions between discrete categories?

2.1.14 Show that the naturality equations (2.2) and (2.3) can equivalently be replaced by the single equation

$$
\overline{\left( {A}^{\prime }\overset{p}{ \rightarrow  }A\overset{f}{ \rightarrow  }G\left( B\right) \overset{G\left( q\right) }{ \rightarrow  }G\left( {B}^{\prime }\right) \right) } = \left( {F\left( {A}^{\prime }\right) \overset{F\left( p\right) }{ \rightarrow  }F\left( A\right) \overset{\bar{f}}{ \rightarrow  }B\overset{q}{ \rightarrow  }{B}^{\prime }}\right)
$$

for all $p, f$ and $q$ .

2.1.15 Show that left adjoints preserve initial objects: that is, if $\mathcal{A}\overset{\overset{F}{ \rightarrow  }}{\overset{\overset{F}{ \leftarrow  }}{\underset{G}{ \rightarrow  }}}\mathcal{B}$ and $I$ is an initial object of $\mathcal{A}$ , then $F\left( I\right)$ is an initial object of $\mathcal{B}$ . Dually, show that right adjoints preserve terminal objects.

(In Section 6.3, we will see this as part of a bigger picture: right adjoints preserve limits and left adjoints preserve colimits.)

2.1.16 Let $G$ be a group.

(a) What interesting functors are there (in either direction) between Set and the category $\left\lbrack  {G,\text{ Set }}\right\rbrack$ of left $G$ -sets? Which of those functors are adjoint to which?

(b) Similarly, what interesting functors are there between ${\mathbf{{Vect}}}_{k}$ and the category $\left\lbrack  {G,{\mathbf{{Vect}}}_{k}}\right\rbrack$ of $k$ -linear representations of $G$ , and what adjunctions are there between those functors?

2.1.17 Fix a topological space $X$ , and write $\mathcal{O}\left( X\right)$ for the poset of open subsets of $X$ , ordered by inclusion. Let

$$
\Delta  : \mathbf{{Set}} \rightarrow  \left\lbrack  {\mathcal{O}{\left( X\right) }^{\mathrm{{op}}},\mathbf{{Set}}}\right\rbrack
$$

be the functor assigning to a set $A$ the presheaf ${\Delta A}$ with constant value $A$ . Exhibit a chain of adjoint functors

$$
\Lambda  + \Pi  + \Delta  + \Gamma  + \nabla
$$

### 2.2 Adjunctions via units and counits

In the previous section, we met the definition of adjunction. In this section and the next, we meet two ways of rephrasing the definition. The one in this section is most useful for theoretical purposes, while the one in the next fits well with many examples.

To start building the theory of adjoint functors, we have to take seriously the naturality requirement (equations (2.2) and (2.3)), which has so far been ignored. Take an adjunction $\mathcal{A}\underset{ \leftarrow  G}{\overset{F}{ \rightleftharpoons  }}\mathcal{B}$ . Intuitively, naturality says that as $A$ varies in $\mathcal{A}$ and $B$ varies in $\mathcal{B}$ , the isomorphism between $\mathcal{B}\left( {F\left( A\right) , B}\right)$ and $\mathcal{A}\left( {A, G\left( B\right) }\right)$ varies in a way that is compatible with all the structure already in place. In other words, it is compatible with composition in the categories $\mathcal{A}$ and $\mathcal{B}$ and the action of the functors $F$ and $G$ .

But what does 'compatible' mean? Suppose, for example, that we have maps

$$
F\left( A\right) \overset{g}{ \rightarrow  }B\overset{q}{ \rightarrow  }{B}^{\prime }
$$

in $\mathcal{B}$ . There are two things we can do with this data: either compose then take the transpose, which produces a map $\overline{q \circ  g} : A \rightarrow  G\left( {B}^{\prime }\right)$ , or take the transpose of $g$ then compose it with $G\left( q\right)$ , which produces a potentially different map $G\left( q\right)  \circ  \bar{g} : A \rightarrow  G\left( {B}^{\prime }\right)$ . Compatibility means that they are equal; and that is the first naturality equation (2.2). The second is its dual, and can be explained in a similar way.

For each $A \in  \mathcal{A}$ , we have a map

$$
\left( {A\overset{{\eta }_{A}}{ \rightarrow  }{GF}\left( A\right) }\right)  = \overline{\left( F\left( A\right) \overset{1}{ \rightarrow  }F\left( A\right) \right) }.
$$

Dually, for each $B \in  \mathcal{B}$ , we have a map

$$
\left( {{FG}\left( B\right) \overset{{\varepsilon }_{B}}{ \rightarrow  }B}\right)  = \overline{\left( G\left( B\right) \overset{1}{ \rightarrow  }G\left( B\right) \right) }.
$$

(We have begun to omit brackets, writing ${GF}\left( A\right)$ instead of $G\left( {F\left( A\right) }\right)$ , etc.) These define natural transformations

$$
\eta  : {1}_{\mathcal{A}} \rightarrow  G \circ  F,\;\varepsilon  : F \circ  G \rightarrow  {1}_{\mathcal{B}},
$$

called the unit and counit of the adjunction, respectively.

Example 2.2.1 Take the usual adjunction ${\operatorname{Vect}}_{k}\underset{F}{\underbrace{ \rightarrow  }}$ Set. Its unit $\eta  : {1}_{\text{ Set }} \rightarrow \; U \circ  F$ has components

$$
{\eta }_{S} : \;S \rightarrow  {UF}\left( S\right)  = \left\{  {\text{ formal }k\text{ -linear sums }\mathop{\sum }\limits_{{s \in  S}}{\lambda }_{s}s}\right\}
$$

$$
s \mapsto  s
$$

$\left( {S \in  \mathbf{{Set}}}\right)$ . The component of the counit $\varepsilon$ at a vector space $V$ is the linear map

$$
{\varepsilon }_{V} : {FU}\left( V\right)  \rightarrow  V
$$

that sends a formal linear sum $\mathop{\sum }\limits_{{v \in  V}}{\lambda }_{v}v$ to its actual value in $V$ .

The vector space ${FU}\left( V\right)$ is enormous. For instance, if $k = \mathbb{R}$ and $V$ is the vector space ${\mathbb{R}}^{2}$ , then $U\left( V\right)$ is the set ${\mathbb{R}}^{2}$ and ${FU}\left( V\right)$ is a vector space with one basis element for every element of ${\mathbb{R}}^{2}$ ; thus, it is uncountably infinite-dimensional. Then ${\varepsilon }_{V}$ is a map from this infinite-dimensional space to the 2- dimensional space $V$ .

Lemma 2.2.2 Given an adjunction $F \dashv  G$ with unit $\eta$ and counit $\varepsilon$ , the triangles

![59_553_581_447_153_0.jpg](images/59_553_581_447_153_0.jpg)

commute.

Remark 2.2.3 These are called the triangle identities. They are commutative diagrams in the functor categories $\left\lbrack  {\mathcal{A},\mathcal{B}}\right\rbrack$ and $\left\lbrack  {\mathcal{B},\mathcal{A}}\right\rbrack$ , respectively. For an explanation of the notation, see Remarks 1.3.24 (particularly the special cases mentioned on page 37). An equivalent statement is that the triangles(2.4)

![59_479_975_589_163_0.jpg](images/59_479_975_589_163_0.jpg)

commute for all $A \in  \mathcal{A}$ and $B \in  \mathcal{B}$ .

Proof of Lemma 2.2.2 We prove that the triangles (2.4) commute. Let $A \in \; \mathcal{A}$ . Since $\overline{{1}_{{GF}\left( A\right) }} = {\varepsilon }_{F\left( A\right) }$ , equation (2.3) gives

$$
\overline{\left( A\overset{{\eta }_{A}}{ \rightarrow  }GF\left( A\right) \overset{1}{ \rightarrow  }GF\left( A\right) \right) } = \left( {F\left( A\right) \overset{F\left( {\eta }_{A}\right) }{ \rightarrow  }{FGF}\left( A\right) \overset{{\varepsilon }_{F\left( A\right) }}{ \rightarrow  }F\left( A\right) }\right) .
$$

But the left-hand side is $\overline{{\eta }_{A}} = \overline{\overline{{1}_{F\left( A\right) }}} = {1}_{F\left( A\right) }$ , proving the first identity. The second follows by duality.

Amazingly, the unit and counit determine the whole adjunction, even though they appear to know only the transposes of identities. This is the main content of the following pair of results.

Lemma 2.2.4 Let $\mathcal{A}\underset{G}{\underbrace{\frac{F}{ < 1 > }}}\mathcal{B}$ be an adjunction, with unit $\eta$ and counit $\varepsilon$ . Then

$$
\bar{g} = G\left( g\right)  \circ  {\eta }_{A}
$$

for any $g : F\left( A\right)  \rightarrow  B$ , and

$$
\bar{f} = {\varepsilon }_{B} \circ  F\left( f\right)
$$

for any $f : A \rightarrow  G\left( B\right)$ .

Proof For any map $g : F\left( A\right)  \rightarrow  B$ , we have

$$
\overline{\left( F\left( A\right) \overset{g}{ \rightarrow  }B\right) } = \overline{\left( F\left( A\right) \overset{1}{ \rightarrow  }F\left( A\right) \overset{g}{ \rightarrow  }B\right) }
$$

$$
= \left( {A\overset{{\eta }_{A}}{ \rightarrow  }{GF}\left( A\right) \overset{G\left( g\right) }{ \rightarrow  }G\left( B\right) }\right)
$$

by equation (2.2), giving the first statement. The second follows by duality.

Theorem 2.2.5 Take categories and functors $\mathcal{A}\overset{\overset{F}{ \rightarrow  }}{\underset{G}{ \rightarrow  }}\mathcal{B}$ . There is a one-toone correspondence between:

(a) adjunctions between $F$ and $G$ (with $F$ on the left and $G$ on the right);

(b) pairs $\left( {{1}_{\mathcal{A}}\overset{\eta }{ \rightarrow  }{GF},{FG}\overset{\varepsilon }{ \rightarrow  }{1}_{\mathcal{B}}}\right)$ of natural transformations satisfying the triangle identities.

(Recall that by definition, an adjunction between $F$ and $G$ is a choice of isomorphism (2.1) for each $A$ and $B$ , satisfying the naturality equations (2.2) and (2.3).)

Proof We have shown that every adjunction between $F$ and $G$ gives rise to a pair $\left( {\eta ,\varepsilon }\right)$ satisfying the triangle identities. We now have to show that this process is bijective. So, take a pair $\left( {\eta ,\varepsilon }\right)$ of natural transformations satisfying the triangle identities. We must show that there is a unique adjunction between $F$ and $G$ with unit $\eta$ and counit $\varepsilon$ .

Uniqueness follows from Lemma 2.2.4. For existence, take natural transformations $\eta$ and $\varepsilon$ as in (b). For each $A$ and $B$ , define functions

$$
\mathcal{B}\left( {F\left( A\right) , B}\right)  \rightleftarrows  \mathcal{A}\left( {A, G\left( B\right) }\right) \text{ , } \tag{2.5}
$$

both denoted by a bar, as follows. Given $g \in  \mathcal{B}\left( {F\left( A\right) , B}\right)$ , put $\bar{g} = G\left( g\right)  \circ  {\eta }_{A} \in \; \mathcal{A}\left( {A, G\left( B\right) }\right)$ . Similarly, in the opposite direction, put $\bar{f} = {\varepsilon }_{B} \circ  F\left( f\right)$ .

I claim that for each $A$ and $B$ , the two functions $g \mapsto  \bar{g}$ and $f \mapsto  \bar{f}$ are mutually inverse. Indeed, given a map $g : F\left( A\right)  \rightarrow  B$ in $\mathcal{B}$ , we have a commutative diagram

![60_608_1630_405_174_0.jpg](images/60_608_1630_405_174_0.jpg)

The composite map from $F\left( A\right)$ to $B$ by one route around the outside of the diagram is

$$
{\varepsilon }_{B} \circ  {FG}\left( g\right)  \circ  F\left( {\eta }_{A}\right)  = {\varepsilon }_{B} \circ  F\left( \bar{g}\right)  = \overline{\bar{g}},
$$

and by the other is $g \circ  1 = g$ , so $\overline{\bar{g}} = g$ . Dually, $\overline{\bar{f}} = f$ for any map $f : A \rightarrow  G\left( B\right)$ in $\mathcal{A}$ . This proves the claim.

It is straightforward to check the naturality equations (2.2) and (2.3). The functions (2.5) therefore define an adjunction. Finally, its unit and counit are $\eta$ and $\varepsilon$ , since the component of the unit at $A$ is

$$
\overline{{1}_{F\left( A\right) }} = G\left( {1}_{F\left( A\right) }\right)  \circ  {\eta }_{A} = 1 \circ  {\eta }_{A} = {\eta }_{A},
$$

and dually for the counit.

Corollary 2.2.6 Take categories and functors $\mathcal{A} \leq  \frac{F}{G} \geq  \mathcal{B}$ . Then $F \dashv  G$ if and only if there exist natural transformations $1\overset{\eta }{ \rightarrow  }{GF}$ and ${FG}\overset{\varepsilon }{ \rightarrow  }1$ satisfying the triangle identities.

Example 2.2.7 An adjunction between ordered sets consists of order-preserving maps $A\overset{\overset{f}{ \leftarrow  }}{\underset{g}{ \rightarrow  }}B$ such that

$$
\forall a \in  A,\forall b \in  B,\;f\left( a\right)  \leq  b \Leftrightarrow  a \leq  g\left( b\right) . \tag{2.6}
$$

This is because both sides of the isomorphism (2.1) in the definition of adjunction are sets with at most one element, so they are isomorphic if and only if they are both empty or both nonempty. The naturality requirements (2.2) and (2.3) hold automatically, since in an ordered set, any two maps with the same domain and codomain are equal.

Recall from Example 1.3.9 that if $C\frac{p}{q} \geq  D$ are order-preserving maps of ordered sets then there is at most one natural transformation from $p$ to $q$ , and there is one if and only if $p\left( c\right)  \leq  q\left( c\right)$ for all $c \in  C$ . The unit of the adjunction above is the statement that $a \leq  {gf}\left( a\right)$ for all $a \in  A$ , and the counit is the statement that ${fg}\left( b\right)  \leq  b$ for all $b \in  B$ . The triangle identities say nothing, since they assert the equality of two maps in an ordered set with the same domain and codomain.

In the case of ordered sets, Corollary 2.2.6 states that condition (2.6) is equivalent to:

$$
\forall a \in  A, a \leq  {gf}\left( a\right) \;\text{ and }\;\forall b \in  B,{fg}\left( b\right)  \leq  b.
$$

This equivalence can also be proved directly (Exercise 2.2.10).

For instance, let $X$ be a topological space. Take the set $\mathcal{C}\left( X\right)$ of closed subsets of $X$ and the set $\mathcal{P}\left( X\right)$ of all subsets of $X$ , both ordered by $\subseteq$ . There are order-preserving maps

$$
\mathcal{P}\left( X\right) \overset{\mathrm{{Cl}}}{\underset{i}{ \rightarrow  }}\mathcal{C}\left( X\right)
$$

where $i$ is the inclusion map and $\mathrm{{Cl}}$ is closure. This is an adjunction, with $\mathrm{{Cl}}$ left adjoint to $i$ , as witnessed by the fact that

$$
\operatorname{Cl}\left( A\right)  \subseteq  B \Leftrightarrow  A \subseteq  B
$$

for all $A \subseteq  X$ and closed $B \subseteq  X$ . An equivalent statement is that $A \subseteq  \mathrm{{Cl}}\left( A\right)$ for all $A \subseteq  X$ and $\mathrm{{Cl}}\left( B\right)  \subseteq  B$ for all closed $B \subseteq  X$ . Either way, we see that the topological operation of closure arises as an adjoint functor.

Remark 2.2.8 Theorem 2.2.5 states that an adjunction may be regarded as a quadruple $\left( {F, G,\eta ,\varepsilon }\right)$ of functors and natural transformations satisfying the triangle identities. An equivalence $\left( {F, G,\eta ,\varepsilon }\right)$ of categories (as in Definition 1.3.15) is not necessarily an adjunction. It is true that $F$ is left adjoint to $G$ (Exercise 2.3.10), but $\eta$ and $\varepsilon$ are not necessarily the unit and counit (because there is no reason why they should satisfy the triangle identities).

Remark 2.2.9 There is a way of drawing natural transformations that makes the triangle identities intuitively plausible. Suppose, for instance, that we have categories and functors

$$
\mathcal{A}\overset{{F}_{1}}{ \rightarrow  }{\mathcal{C}}_{1}\overset{{F}_{2}}{ \rightarrow  }{\mathcal{C}}_{2}\overset{{F}_{3}}{ \rightarrow  }{\mathcal{C}}_{3}\overset{{F}_{4}}{ \rightarrow  }\mathcal{B},\;\mathcal{A}\overset{{G}_{1}}{ \rightarrow  }{\mathcal{D}}_{1}\overset{{G}_{2}}{ \rightarrow  }\mathcal{B}
$$

and a natural transformation $\alpha  : {F}_{4}{F}_{3}{F}_{2}{F}_{1} \rightarrow  {G}_{2}{G}_{1}$ . We usually draw $\alpha$ like this:

![62_475_1322_672_160_0.jpg](images/62_475_1322_672_160_0.jpg)

However, we can also draw $\alpha$ as a string diagram:

![62_543_1543_536_264_0.jpg](images/62_543_1543_536_264_0.jpg)

There is nothing special about 4 and 2; we could replace them by any natural numbers $m$ and $n$ . If $m = 0$ then $\mathcal{A} = \mathcal{B}$ and the domain of $\alpha$ is ${1}_{\mathcal{A}}$ (keeping in mind the last paragraph of Remark 1.1.2(b)). In that case, the disk labelled $\alpha$ has no strings coming into the top. Similarly, if $n = 0$ then there are no strings coming out of the bottom.

Vertical composition of natural transformations corresponds to joining string diagrams together vertically, and horizontal composition corresponds to putting them side by side. The identity on a functor $F$ is drawn as a simple string,

$F$

$F$

Now let us apply this notation to adjunctions. The unit and counit are drawn as

![63_484_885_587_160_0.jpg](images/63_484_885_587_160_0.jpg)

The triangle identities now become the topologically plausible equations

![63_347_1102_856_302_0.jpg](images/63_347_1102_856_302_0.jpg)

In both equations, the right-hand side is obtained from the left by simply pulling the string straight.

## Exercises

2.2.10 Let $A\overset{f}{\underset{g}{ \rightarrow  }}B$ be order-preserving maps between ordered sets. Prove directly that the following conditions are equivalent:

(a) for all $a \in  A$ and $b \in  B$ ,

$$
f\left( a\right)  \leq  b \Leftrightarrow  a \leq  g\left( b\right)
$$

(b) $a \leq  g\left( {f\left( a\right) }\right)$ for all $a \in  A$ and $f\left( {g\left( b\right) }\right)  \leq  b$ for all $b \in  B$ .

(Both conditions state that $f \dashv  g$ ; see Example 2.2.7.)

2.2.11 (a) Let $\mathcal{A}\overset{\overset{F}{ \leftarrow  }}{\underset{G}{ \rightarrow  }}\mathcal{B}$ be an adjunction with unit $\eta$ and counit $\varepsilon$ . Write Fix $\left( {GF}\right)$ for the full subcategory of $\mathcal{A}$ whose objects are those $A \in  \mathcal{A}$ such that ${\eta }_{A}$ is an isomorphism, and dually $\operatorname{Fix}\left( {FG}\right)  \subseteq  \mathcal{B}$ . Prove that the adjunction $\left( {F, G,\eta ,\varepsilon }\right)$ restricts to an equivalence $\left( {{F}^{\prime },{G}^{\prime },{\eta }^{\prime },{\varepsilon }^{\prime }}\right)$ between $\operatorname{Fix}\left( {GF}\right)$ and $\operatorname{Fix}\left( {FG}\right)$ .

(b) Part (a) shows that every adjunction restricts to an equivalence between full subcategories in a canonical way. Take some examples of adjunctions and work out what this equivalence is.

2.2.12 (a) Show that for any adjunction, the right adjoint is full and faithful if and only if the counit is an isomorphism.

(b) An adjunction satisfying the equivalent conditions of part (a) is called a reflection. (Compare Example 2.1.3(d).) Of the examples of adjunctions given in this chapter, which are reflections?

2.2.13 (a) Let $f : K \rightarrow  L$ be a map of sets, and denote by ${f}^{ * } : \mathcal{P}\left( L\right)  \rightarrow \; \mathcal{P}\left( K\right)$ the map sending a subset $S$ of $L$ to its inverse image ${f}^{-1}S \subseteq  K$ . Then ${f}^{ * }$ is order-preserving with respect to the inclusion orderings on $\mathcal{P}\left( K\right)$ and $\mathcal{P}\left( L\right)$ , and so can be seen as a functor. Find left and right adjoints to ${f}^{ * }$ .

(b) Now let $X$ and $Y$ be sets, and write $p : X \times  Y \rightarrow  X$ for first projection. Regard a subset $S$ of $X$ as a predicate $S\left( x\right)$ in one variable $x \in  X$ , and similarly a subset $R$ of $X \times  Y$ as a predicate $R\left( {x, y}\right)$ in two variables. What, in terms of predicates, are the left and right adjoints to ${p}^{ * }$ ? For each of the adjunctions, interpret the unit and counit as logical implications. (Hint: the left adjoint to ${p}^{ * }$ is often written as ${\exists }_{Y}$ , and the right adjoint as ${\forall }_{Y}$ .)

2.2.14 Given a functor $F : \mathcal{A} \rightarrow  \mathcal{B}$ and a category $\mathcal{S}$ , there is a functor ${F}^{ * }$ : $\left\lbrack  {\mathcal{B},\mathcal{S}}\right\rbrack   \rightarrow  \left\lbrack  {\mathcal{A},\mathcal{S}}\right\rbrack$ defined on objects $Y \in  \left\lbrack  {\mathcal{B},\mathcal{S}}\right\rbrack$ by ${F}^{ * }\left( Y\right)  = Y \circ  F$ and on maps $\alpha$ by ${F}^{ * }\left( \alpha \right)  = {\alpha F}$ . Show that any adjunction $\mathcal{A}\underset{ < \frac{1}{G}}{\overset{F}{ \rightarrow  }}\mathcal{B}$ and category $\mathcal{S}$ give rise to an adjunction

$$
\left\lbrack  {\mathcal{A},\mathcal{G}}\right\rbrack  \overset{\overset{{G}^{ * }}{ \bot  }}{\underset{{F}^{ * }}{ \rightarrow  }}\left\lbrack  {\mathcal{B},\mathcal{G}}\right\rbrack  .
$$

(Hint: use Theorem 2.2.5.)

### 2.3 Adjunctions via initial objects

We now come to the third formulation of adjointness, which is the one you will probably see most often in everyday mathematics.

Consider once more the adjunction

![65_730_546_90_125_0.jpg](images/65_730_546_90_125_0.jpg)

Let $S$ be a set. The universal property of $F\left( S\right)$ , the vector space whose basis is $S$ , is most commonly stated like this:

given a vector space $V$ , any function $f : S \rightarrow  V$ extends uniquely to a linear map $\bar{f} : F\left( S\right)  \rightarrow  V$ .

As remarked in Example 2.1.3(a), forgetful functors are often forgotten: in this statement,’ $f : S \rightarrow  V$ ’ should strictly speaking be ’ $f : S \rightarrow  U\left( V\right)$ ’. Also, the word 'extends' refers implicitly to the embedding

$$
{\eta }_{S} : \;S \rightarrow  {UF}\left( S\right)
$$

$$
s \mapsto  s
$$

So in precise language, the statement reads:

for any $V \in  {\operatorname{Vect}}_{k}$ and $f \in  \operatorname{Set}\left( {S, U\left( V\right) }\right)$ , there is a unique $\bar{f} \in \; {\operatorname{Vect}}_{k}\left( {F\left( S\right) , V}\right)$ such that the diagram(2.7)

![65_667_1243_217_158_0.jpg](images/65_667_1243_217_158_0.jpg)

commutes.

(Compare Example 0.4.) In this section, we show that this statement is equivalent to the statement that $F$ is left adjoint to $U$ with unit $\eta$ .

To do this, we need a definition.

Definition 2.3.1 Given categories and functors

![65_692_1647_171_160_0.jpg](images/65_692_1647_171_160_0.jpg)

the comma category $\left( {P \Rightarrow  Q}\right)$ (often written as $\left( {P \downarrow  Q}\right)$ ) is the category defined as follows:

- objects are triples $\left( {A, h, B}\right)$ with $A \in  \mathcal{A}, B \in  \mathcal{B}$ , and $h : P\left( A\right)  \rightarrow  Q\left( B\right)$ in $\mathcal{C}$ ;

- maps $\left( {A, h, B}\right)  \rightarrow  \left( {{A}^{\prime },{h}^{\prime },{B}^{\prime }}\right)$ are pairs $\left( {f : A \rightarrow  {A}^{\prime }, g : B \rightarrow  {B}^{\prime }}\right)$ of maps such that the square

![66_714_571_223_175_0.jpg](images/66_714_571_223_175_0.jpg)

commutes.

Remark 2.3.2 Given $\mathcal{A},\mathcal{B},\mathcal{C}, P$ and $Q$ as above, there are canonical functors and a canonical natural transformation as shown:

![66_696_902_232_155_0.jpg](images/66_696_902_232_155_0.jpg)

In a suitable 2-categorical sense, $\left( {P \Rightarrow  Q}\right)$ is universal with this property.

Example 2.3.3 Let $\mathcal{A}$ be a category and $A \in  \mathcal{A}$ . The slice category of $\mathcal{A}$ over $A$ , denoted by $\mathcal{A}/A$ , is the category whose objects are maps into $A$ and whose maps are commutative triangles. More precisely, an object is a pair $\left( {X, h}\right)$ with $X \in  \mathcal{A}$ and $h : X \rightarrow  A$ in $\mathcal{A}$ , and a map $\left( {X, h}\right)  \rightarrow  \left( {{X}^{\prime },{h}^{\prime }}\right)$ in $\mathcal{A}/A$ is a map $f : X \rightarrow  {X}^{\prime }$ in $\mathcal{A}$ making the triangle

![66_688_1324_244_151_0.jpg](images/66_688_1324_244_151_0.jpg)

commute.

Slice categories are a special case of comma categories. Recall from Example 2.1.9 that functors $\mathbf{1} \rightarrow  \mathcal{A}$ are just objects of $\mathcal{A}$ . Now, given an object $A$ of $\mathcal{A}$ , consider the comma category $\left( {{1}_{\mathcal{A}} \Rightarrow  A}\right)$ , as in the diagram

![66_728_1644_168_163_0.jpg](images/66_728_1644_168_163_0.jpg)

An object of $\left( {{1}_{\mathcal{A}} \Rightarrow  A}\right)$ is in principle a triple $\left( {X, h, B}\right)$ with $X \in  \mathcal{A}, B \in  \mathbf{1}$ , and $h : X \rightarrow  A$ in $\mathcal{A}$ ; but1has only one object, so it is essentially just a pair $\left( {X, h}\right)$ . Hence the comma category $\left( {{1}_{\mathcal{A}} \Rightarrow  A}\right)$ has the same objects as the slice category $\mathcal{A}/A$ . One can check that it has the same maps too, so that $\mathcal{A}/A \cong  \left( {{1}_{\mathcal{A}} \Rightarrow  A}\right)$ .

Dually (reversing all the arrows), there is a coslice category $A/\mathcal{A} \cong  (A \Rightarrow \; {1}_{\mathcal{A}}$ ), whose objects are the maps out of $A$ .

Example 2.3.4 Let $G : \mathcal{B} \rightarrow  \mathcal{A}$ be a functor and let $A \in  \mathcal{A}$ . We can form the comma category $\left( {A \Rightarrow  G}\right)$ , as in the diagram

![67_697_706_159_157_0.jpg](images/67_697_706_159_157_0.jpg)

Its objects are pairs $\left( {B \in  \mathcal{B}, f : A \rightarrow  G\left( B\right) }\right)$ . A map $\left( {B, f}\right)  \rightarrow  \left( {{B}^{\prime },{f}^{\prime }}\right)$ in $\left( {A \Rightarrow  G}\right)$ is a map $q : B \rightarrow  {B}^{\prime }$ in $\mathcal{B}$ making the triangle

![67_678_981_194_160_0.jpg](images/67_678_981_194_160_0.jpg)

commute.

Notice how this diagram resembles the diagram (2.7) in the vector space example. We will use comma categories $\left( {A \Rightarrow  G}\right)$ to capture the kind of universal property discussed there.

Speaking casually, we say that $f : A \rightarrow  G\left( B\right)$ is an object of $\left( {A \Rightarrow  G}\right)$ , when what we should really say is that the pair $\left( {B, f}\right)$ is an object of $\left( {A \Rightarrow  G}\right)$ . There is potential for confusion here, since there may be different objects $B,{B}^{\prime }$ of $\mathcal{B}$ with $G\left( B\right)  = G\left( {B}^{\prime }\right)$ . Nevertheless, we will often use this convention.

We now make the connection between comma categories and adjunctions.

Lemma 2.3.5 Take an adjunction $\mathcal{A}\frac{F}{ < \frac{1}{G}}\mathcal{B}$ and an object $A \in  \mathcal{A}$ . Then the unit map ${\eta }_{A} : A \rightarrow  {GF}\left( A\right)$ is an initial object of $\left( {A \Rightarrow  G}\right)$ .

Proof Let $\left( {B, f : A \rightarrow  G\left( B\right) }\right)$ be an object of $\left( {A \Rightarrow  G}\right)$ . We have to show that there is exactly one map from $\left( {F\left( A\right) ,{\eta }_{A}}\right)$ to $\left( {B, f}\right)$ .

A map $\left( {F\left( A\right) ,{\eta }_{A}}\right)  \rightarrow  \left( {B, f}\right)$ in $\left( {A \Rightarrow  G}\right)$ is a map $q : F\left( A\right)  \rightarrow  B$ in $\mathcal{B}$ such

that(2.8)

![68_708_399_205_159_0.jpg](images/68_708_399_205_159_0.jpg)

commutes. But $G\left( q\right)  \circ  {\eta }_{A} = \bar{q}$ by Lemma 2.2.4, so (2.8) commutes if and only if $f = \bar{q}$ , if and only if $q = \bar{f}$ . Hence $\bar{f}$ is the unique map $\left( {F\left( A\right) ,{\eta }_{A}}\right)  \rightarrow  \left( {B, f}\right)$ in $\left( {A \Rightarrow  G}\right)$ .

We now meet our third and final formulation of adjointness.

Theorem 2.3.6 Take categories and functors $\mathcal{A}\widehat{\underset{G}{ \rightarrow  }}\mathcal{B}$ . There is a one-toone correspondence between:

(a) adjunctions between $F$ and $G$ (with $F$ on the left and $G$ on the right);

(b) natural transformations $\eta  : {1}_{\mathcal{A}} \rightarrow  {GF}$ such that ${\eta }_{A} : A \rightarrow  {GF}\left( A\right)$ is initial in $\left( {A \Rightarrow  G}\right)$ for every $A \in  \mathcal{A}$ .

Proof We have just shown that every adjunction between $F$ and $G$ gives rise to a natural transformation $\eta$ with the property stated in (b). To prove the theorem, we have to show that every $\eta$ with the property in (b) is the unit of exactly one adjunction between $F$ and $G$ .

By Theorem 2.2.5, an adjunction between $F$ and $G$ amounts to a pair $\left( {\eta ,\varepsilon }\right)$ of natural transformations satisfying the triangle identities. So it is enough to prove that for every $\eta$ with the property in (b), there exists a unique natural transformation $\varepsilon  : {FG} \rightarrow  {1}_{\mathcal{B}}$ such that the pair $\left( {\eta ,\varepsilon }\right)$ satisfies the triangle identities.

Let $\eta  : {1}_{\mathcal{A}} \rightarrow  {GF}$ be a natural transformation with the property in (b).

Uniqueness Suppose that $\varepsilon ,{\varepsilon }^{\prime } : {FG} \rightarrow  {1}_{\mathcal{B}}$ are natural transformations such that both $\left( {\eta ,\varepsilon }\right)$ and $\left( {\eta ,{\varepsilon }^{\prime }}\right)$ satisfy the triangle identities. One of the triangle identities states that for all $B \in  \mathcal{B}$ , the triangle(2.9)

![68_669_1529_284_157_0.jpg](images/68_669_1529_284_157_0.jpg)

commutes. Thus, ${\varepsilon }_{B}$ is a map

$$
\left( {{FG}\left( B\right) , G\left( B\right) \overset{{\eta }_{G\left( B\right) }}{ \rightarrow  }G\left( {{FG}\left( B\right) }\right) }\right)  \rightarrow  \left( {B, G\left( B\right) \overset{1}{ \rightarrow  }G\left( B\right) }\right)
$$

in $\left( {G\left( B\right)  \Rightarrow  G}\right)$ . The same is true of ${\varepsilon }_{B}^{\prime }$ . But ${\eta }_{G\left( B\right) }$ is initial, so there is only one such map, so ${\varepsilon }_{B} = {\varepsilon }_{B}^{\prime }$ . This holds for all $B$ , so $\varepsilon  = {\varepsilon }^{\prime }$ .

Existence For $B \in  \mathcal{B}$ , define ${\varepsilon }_{B} : {FG}\left( B\right)  \rightarrow  B$ to be the unique map

$$
\left( {{FG}\left( B\right) ,{\eta }_{G\left( B\right) }}\right)  \rightarrow  \left( {B,{1}_{G\left( B\right) }}\right)
$$

in $\left( {G\left( B\right)  \Rightarrow  G}\right)$ . (So by definition of ${\varepsilon }_{B}$ , triangle (2.9) commutes.) We show that ${\left( {\varepsilon }_{B}\right) }_{B \in  \mathcal{B}}$ is a natural transformation ${FG} \rightarrow  1$ such that $\eta$ and $\varepsilon$ satisfy the triangle identities.

To prove naturality, take $B\overset{q}{ \rightarrow  }{B}^{\prime }$ in $\mathcal{B}$ . We have commutative diagrams

![69_407_754_735_280_0.jpg](images/69_407_754_735_280_0.jpg)

So $q \circ  {\varepsilon }_{B}$ and ${\varepsilon }_{{B}^{\prime }} \circ  {FG}\left( q\right)$ are both maps ${\eta }_{G\left( B\right) } \rightarrow  G\left( q\right)$ in $\left( {G\left( B\right)  \Rightarrow  G}\right)$ , and since ${\eta }_{G\left( B\right) }$ is initial, they must be equal. This proves naturality of $\varepsilon$ with respect to $q$ . Hence $\varepsilon$ is a natural transformation.

We have already observed that one of the triangle identities, equation (2.9), holds. The other states that for $A \in  \mathcal{A}$ ,

![69_645_1245_261_160_0.jpg](images/69_645_1245_261_160_0.jpg)

commutes. To prove it, we repeat our previous technique: there are commutative diagrams so by initiality of ${\eta }_{A}$ , we have ${\varepsilon }_{F\left( A\right) } \circ  F\left( {\eta }_{A}\right)  = {1}_{F\left( A\right) }$ , as required.

![69_415_1509_717_298_0.jpg](images/69_415_1509_717_298_0.jpg)

In Section 6.3 we will meet the adjoint functor theorems, which state conditions under which a functor is guaranteed to have a left adjoint. The following corollary is the starting point for their proofs.

Corollary 2.3.7 Let $G : \mathcal{B} \rightarrow  \mathcal{A}$ be a functor. Then $G$ has a left adjoint if and only if for each $A \in  \mathcal{A}$ , the category $\left( {A \Rightarrow  G}\right)$ has an initial object.

Proof Lemma 2.3.5 proves 'only if'. To prove 'if', let us choose for each $A \in  \mathcal{A}$ an initial object of $\left( {A \Rightarrow  G}\right)$ and call it $\left( {F\left( A\right) ,{\eta }_{A} : A \rightarrow  {GF}\left( A\right) }\right)$ . (Here $F\left( A\right)$ and ${\eta }_{A}$ are just the names we choose to use.) For each map $f : A \rightarrow  {A}^{\prime }$ in $\mathcal{A}$ , let $F\left( f\right)  : F\left( A\right)  \rightarrow  F\left( {A}^{\prime }\right)$ be the unique map such that

![70_636_798_352_174_0.jpg](images/70_636_798_352_174_0.jpg)

commutes (in other words, the unique map ${\eta }_{A} \rightarrow  {\eta }_{{A}^{\prime }} \circ  f$ in $\left( {A \Rightarrow  G}\right)$ ). It is easily checked that $F$ is a functor $\mathcal{A} \rightarrow  \mathcal{B}$ , and the diagram tells us that $\eta$ is a natural transformation $1 \rightarrow  {GF}$ . So by Theorem 2.3.6, $F$ is left adjoint to $G$ . $\square$

This corollary justifies the claim made at the beginning of the section: that given functors $F$ and $G$ , to have an adjunction $F \dashv  G$ amounts to having maps ${\eta }_{A} : A \rightarrow  {GF}\left( A\right)$ with the universal property stated there.

## Exercises

2.3.8 What can be said about adjunctions between groups (regarded as one-object categories)?

2.3.9 State the dual of Corollary 2.3.7. How would you prove your dual statement?

2.3.10 Let $\left( {F, G,\eta ,\varepsilon }\right)$ be an equivalence of categories, as in Definition 1.3.15. Prove that $F$ is left adjoint to $G$ (heeding the warning in Remark 2.2.8).

2.3.11 Let $\mathcal{A}\overset{U}{\underset{F}{ \leftarrow  }}$ Set be an adjunction. Suppose that for at least one $A \in \; \mathcal{A}$ , the set $U\left( A\right)$ has at least two elements. Prove that for each set $S$ , the unit map ${\eta }_{S} : S \rightarrow  {UF}\left( S\right)$ is injective. What does this mean in the case of the usual adjunction between Grp and Set?

2.3.12 Given sets $A$ and $B$ , a partial function from $A$ to $B$ is a pair $\left( {S, f}\right)$ consisting of a subset $S \subseteq  A$ and a function $S \rightarrow  B$ . (Think of it as like a function from $A$ to $B$ , but undefined at certain elements of $A$ .) Let $\mathbf{{Par}}$ be the category of sets and partial functions.

Show that Par is equivalent to ${\mathbf{{Set}}}_{ * }$ , the category of sets equipped with a distinguished element and functions preserving distinguished elements. Show also that ${\mathbf{{Set}}}_{ * }$ can be described as a coslice category in a simple way.

## 3 Interlude on sets

Sets and functions are ubiquitous in mathematics. You might have the impression that they are most strongly connected with the pure end of the subject, but this is an illusion: think of probability density functions in statistics, data sets in experimental science, planetary motion in astronomy, or flow in fluid dynamics.

Category theory is often used to shed light on common constructions and patterns in mathematics. If we hope to do this in an advanced context, we must begin by settling the basic notions of set and function. That is the purpose of the first section of this chapter.

The definition of category mentions a 'collection' of objects and 'collections' of maps. We will see in the second section that some collections are too big to be sets, which leads to a distinction between 'small' and 'large' collections. This distinction will be needed later, most prominently for the adjoint functor theorems (Chapter 6).

The final section takes a historical look at set theory. It also explains why the approach to sets taken in this chapter is more relevant to most of mathematics than the traditional approach is. None of this section is logically necessary for anything that follows, but it may provide useful perspective.

I do not assume that you have encountered axiomatic set theory of any kind. If you have, it is probably best to put it out of your mind while reading this chapter, as the approach to set theory that we take is quite different from the approach that you are most likely to be familiar with. A brief comparison of the traditional and categorical approaches can be found at the very end of the chapter.

### 3.1 Constructions with sets

We have made no definition of 'set', nor of 'function'. Nevertheless, guided by our intuition, we can list some properties that we expect the world of sets and functions to have. For instance, we can describe some of the sets that we think ought to exist, and some ways of building new sets from old.

Intuitively, a set is a bag of points:

![73_712_611_128_149_0.jpg](images/73_712_611_128_149_0.jpg)

(There may, of course, be infinitely many.) These points, or elements, are not related to one another in any way. They are not in any order, they do not come with any algebraic structure (for instance, there is no specified way of multiplying elements together), and there is no sense of what it means for one point to be close to another. In particular examples, we might have some extra structure in mind; for instance, we often equip the set of real numbers with an order, a field structure and a metric. But to view $\mathbb{R}$ as a mere set is to ignore all that structure, to regard it as no more than a bunch of featureless points.

Intuitively, a function $A \rightarrow  B$ is an assignment of a point in bag $B$ to each point in bag $A$ :

![73_603_1145_347_145_0.jpg](images/73_603_1145_347_145_0.jpg)

We can do one function after another: given functions

![73_493_1359_568_147_0.jpg](images/73_493_1359_568_147_0.jpg)

we obtain a composite function

![73_490_1571_571_135_0.jpg](images/73_490_1571_571_135_0.jpg)

This composition of functions is associative: $h \circ  \left( {g \circ  f}\right)  = \left( {h \circ  g}\right)  \circ  f$ . There is also an identity function on every set. Hence:

Sets and functions form a category, denoted by Set.

This does not pin things down much: there are many categories, mostly quite unlike the category of sets. So, let us list some of the special features of the category of sets.

The empty set There is a set $\varnothing$ with no elements.

Suppose that someone hands you a pair of sets, $A$ and $B$ , and tells you to specify a function from $A$ to $B$ . Then your task is to specify for each element of $A$ an element of $B$ . The larger $A$ is, the longer the task; the smaller $A$ is, the shorter the task. In particular, if $A$ is empty then the task takes no time at all; we have nothing to do. So there is a function from $\varnothing$ to $B$ specified by doing nothing. On the other hand, there cannot be two different ways to do nothing, so there is only one function from $\varnothing$ to $B$ . Hence:

$\varnothing$ is an initial object of Set.

In case this argument seems unconvincing, here is an alternative. Suppose that we have a set $A$ with disjoint subsets ${A}_{1}$ and ${A}_{2}$ such that ${A}_{1} \cup  {A}_{2} = A$ . Then a function from $A$ to $B$ amounts to a function from ${A}_{1}$ to $B$ together with a function from ${A}_{2}$ to $B$ . So if all the sets are finite, we should have the rule

(number of functions from $A$ to $B$ ) = (number of functions from ${A}_{1}$ to $B$ )

$\times$ (number of functions from ${A}_{2}$ to $B$ ).

In particular, we could take ${A}_{1} = A$ and ${A}_{2} = \varnothing$ . This would force the number of functions from $\varnothing$ to $B$ to be 1 . So if we want this rule to hold (and surely we do!), we had better say that there is exactly one function from $\varnothing$ to $B$ .

What about functions into $\varnothing$ ? There is exactly one function $\varnothing  \rightarrow  \varnothing$ , namely, the identity. This is a special case of the initiality of $\varnothing$ . On the other hand, for a set $A$ that is not empty, there are no functions $A \rightarrow  \varnothing$ , because there is nowhere for elements of $A$ to go.

The one-element set There is a set 1 with exactly one element.

For any set $A$ , there is exactly one function from $A$ to 1, since every element of $A$ must be mapped to the unique element of 1 . That is:

1 is a terminal object of Set.

A function from 1 to a set $B$ is just a choice of an element of $B$ . In short, the functions $1 \rightarrow  B$ are the elements of $B$ . Hence:

The concept of element is a special case of the concept of function.

Products Any two sets $A$ and $B$ have a product, $A \times  B$ . Its elements are the ordered pairs $\left( {a, b}\right)$ with $a \in  A$ and $b \in  B$ . Ordered pairs are familiar from coordinate geometry. All that matters about them is that for $a,{a}^{\prime } \in  A$ and $b,{b}^{\prime } \in  B$ ,

$$
\left( {a, b}\right)  = \left( {{a}^{\prime },{b}^{\prime }}\right)  \Leftrightarrow  a = {a}^{\prime }\text{ and }b = {b}^{\prime }.
$$

More generally, take any set $I$ and any family ${\left( {A}_{i}\right) }_{i \in  I}$ of sets. There is a product set $\mathop{\prod }\limits_{{i \in  I}}{A}_{i}$ , whose elements are families ${\left( {a}_{i}\right) }_{i \in  I}$ with ${a}_{i} \in  {A}_{i}$ for each $i$ . Just as for ordered pairs,

$$
{\left( {a}_{i}\right) }_{i \in  I} = {\left( {a}_{i}^{\prime }\right) }_{i \in  I} \Leftrightarrow  {a}_{i} = {a}_{i}^{\prime }\text{ for all }i \in  I.
$$

Sums Any two sets $A$ and $B$ have a sum $A + B$ .

Thinking of sets as bags of points, the sum of two sets is obtained by putting all the points into one big bag:

![75_469_951_610_155_0.jpg](images/75_469_951_610_155_0.jpg)

If $A$ and $B$ are finite sets with $m$ and $n$ elements respectively, then $A + B$ always has $m + n$ elements. It makes no difference what the elements of $A + B$ are called; as usual, we only care what $A + B$ is up to isomorphism.

There are inclusion functions

$$
A\overset{i}{ \rightarrow  }A + B\overset{j}{ \leftarrow  }B
$$

such that the union of the images of $i$ and $j$ is all of $A + B$ and the intersection of the images is empty.

Sum is sometimes called disjoint union and written as II. It is not to be confused with (ordinary) union $\cup$ . For a start, we can take the sum of any two sets $A$ and $B$ , whereas $A \cup  B$ only really makes sense when $A$ and $B$ come as subsets of some larger set. (For to say what $A \cup  B$ is, we need to know which elements of $A$ are equal to which elements of $B$ .) And even if $A$ and $B$ do come as subsets of some larger set, $A + B$ and $A \cup  B$ can be different. For example, take the subsets $A = \{ 1,2,3\}$ and $B = \{ 3,4\}$ of $\mathbb{N}$ . Then $A \cup  B$ has 4 elements, but $A + B$ has $3 + 2 = 5$ elements.

More generally, any family ${\left( {A}_{i}\right) }_{i \in  I}$ of sets has a sum $\mathop{\sum }\limits_{{i \in  I}}{A}_{i}$ . If $I$ is finite and each ${A}_{i}$ is finite, say with ${m}_{i}$ elements, then $\mathop{\sum }\limits_{{i \in  I}}{A}_{i}$ has $\mathop{\sum }\limits_{{i \in  I}}{m}_{i}$ elements.

Sets of functions For any two sets $A$ and $B$ , we can form the set ${A}^{B}$ of functions from $B$ to $A$ .

This is a special case of the product construction: ${A}^{B}$ is the product $\mathop{\prod }\limits_{{b \in  B}}A$ of the constant family ${\left( A\right) }_{b \in  B}$ . Indeed, an element of $\mathop{\prod }\limits_{{b \in  B}}A$ is a family ${\left( {a}_{b}\right) }_{b \in  B}$ consisting of one element ${a}_{b} \in  A$ for each $b \in  B$ ; in other words, it is a function $B \rightarrow  A$ .

Digression on arithmetic We are using notation reminiscent of arithmetic: $A \times  B, A + B$ , and ${A}^{B}$ . There is good reason for this: if $A$ is a finite set with $m$ elements and $B$ a finite set with $n$ elements, then $A \times  B$ has $m \times  n$ elements, $A + B$ has $m + n$ elements, and ${A}^{B}$ has ${m}^{n}$ elements. Our notation 1 for a one-element set and the alternative notation 0 for the empty set $\varnothing$ also follow this pattern.

All the usual laws of arithmetic have their counterparts for sets:

$$
A \times  \left( {B + C}\right)  \cong  \left( {A \times  B}\right)  + \left( {A \times  C}\right) ,
$$

$$
{A}^{B + C} \cong  {A}^{B} \times  {A}^{C},
$$

$$
{\left( {A}^{B}\right) }^{C} \cong  {A}^{B \times  C},
$$

and so on, where $\cong$ is isomorphism in the category of sets. (For the last one, see Example 2.1.6.) These isomorphisms hold for all sets, not just finite ones.

The two-element set Let 2 be the set $1 + 1$ (a set with two elements!). For reasons that will soon become clear, I will write the elements of 2 as true and false.

Let $A$ be a set. Given a subset $S$ of $A$ , we obtain a function ${\chi }_{S} : A \rightarrow  2$ (the characteristic function of $S \subseteq  A$ ), where

$$
{\chi }_{S}\left( a\right)  = \left\{  \begin{array}{ll} \text{ true } & \text{ if }a \in  S, \\  \text{ false } & \text{ if }a \notin  S \end{array}\right.
$$

$\left( {a \in  A}\right)$ . Conversely, given a function $f : A \rightarrow  2$ , we obtain a subset

$$
{f}^{-1}\{ \text{ true }\}  = \{ a \in  A \mid  f\left( a\right)  = \text{ true }\}
$$

of $A$ . These two processes are mutually inverse; that is, ${\chi }_{S}$ is the unique function $f : A \rightarrow  2$ such that ${f}^{-1}\{$ true $\}  = S$ . Hence:

Subsets of A correspond one-to-one with functions $A \rightarrow  2$ .

We already know that the functions from $A$ to 2 form a set, ${2}^{A}$ . When we are thinking of ${2}^{A}$ as the set of all subsets of $A$ , we call it the power set of $A$ and write it as $\mathcal{P}\left( A\right)$ .

Equalizers It would be nice if, given a set $A$ , we could define a subset $S$ of $A$ by specifying a property that the elements of $S$ are to satisfy:

$$
S = \{ a \in  A \mid  \text{ some property of }a\text{ holds }\} .
$$

It is hard to give a general definition of 'property'. There is, however, a special type of property that is easy to handle: equality of two functions. Precisely, given sets and functions $A\xrightarrow[g]{f}B$ , there is a set

$$
\{ a \in  A \mid  f\left( a\right)  = g\left( a\right) \} .
$$

This set is called the equalizer of $f$ and $g$ , since it is the part of $A$ on which the two functions are equal.

Quotients You are probably familiar with quotient groups and quotient rings (sometimes called factor groups and factor rings) in algebra. Quotients also come up everywhere in topology, such as when we glue together opposite sides of a square to make a cylinder. But the most basic context for quotients is that of sets.

Let $A$ be a set and $\sim$ an equivalence relation on $A$ . There is a set $A/ \sim$ , the quotient of $A$ by $\sim$ , whose elements are the equivalence classes. For example, given a group $G$ and a normal subgroup $N$ , define an equivalence relation $\sim$ on $G$ by $g \sim  h \Leftrightarrow  g{h}^{-1} \in  N$ ; then $G/ \sim   = G/N$ .

There is also a canonical map

$$
p : A \rightarrow  A/ \sim  ,
$$

sending an element of $A$ to its equivalence class. It is surjective, and has the property that $p\left( a\right)  = p\left( {a}^{\prime }\right)  \Leftrightarrow  a \sim  {a}^{\prime }$ . In fact, it has a universal property: any function $f : A \rightarrow  B$ such that

$$
\forall a,{a}^{\prime } \in  A,\;a \sim  {a}^{\prime } \Rightarrow  f\left( a\right)  = f\left( {a}^{\prime }\right) \tag{3.1}
$$

factorizes uniquely through $p$ , as in the diagram

![77_691_1526_167_152_0.jpg](images/77_691_1526_167_152_0.jpg)

Thus, for any set $B$ , the functions $A/ \sim   \rightarrow  B$ correspond one-to-one with the functions $f : A \rightarrow  B$ satisfying (3.1). This fact is at the heart of the famous isomorphism theorems of algebra.

We have now listed the properties of sets and functions that will be most important for us. Here are two more.

Natural numbers A function with domain $\mathbb{N}$ is usually called a sequence. A crucial property of $\mathbb{N}$ is that sequences can be defined recursively: given a set $X$ , an element $a \in  X$ , and a function $r : X \rightarrow  X$ , there is a unique sequence ${\left( {x}_{n}\right) }_{n = 0}^{\infty }$ of elements of $X$ such that

$$
{x}_{0} = a,\;{x}_{n + 1} = r\left( {x}_{n}\right) \text{ for all }n \in  \mathbb{N}.
$$

This property refers to two pieces of structure on $\mathbb{N}$ : the element 0, and the function $s : \mathbb{N} \rightarrow  \mathbb{N}$ defined by $s\left( n\right)  = n + 1$ . Reformulated in terms of functions, and writing ${x}_{n} = x\left( n\right)$ , the property is this: for any set $X$ , element $a \in  X$ , and function $r : X \rightarrow  X$ , there is a unique function $x : \mathbb{N} \rightarrow  X$ such that $x\left( 0\right)  = a$ and $x \circ  s = r \circ  x$ . Exercise 3.1.2 asks you to show that this is a universal property of $\mathbb{N},0$ and $s$ .

Choice Let $f : A \rightarrow  B$ be a map in a category $\mathcal{A}$ . A section (or right inverse) of $f$ is a map $i : B \rightarrow  A$ in $\mathcal{A}$ such that $f \circ  i = {1}_{B}$ .

In the category of sets, any map with a section is certainly surjective. The converse statement is called the axiom of choice:

Every surjection has a section.

It is called ’choice’ because specifying a section of $f : A \rightarrow  B$ amounts to choosing, for each $b \in  B$ , an element of the nonempty set $\{ a \in  A \mid  f\left( a\right)  = b\}$ .

The properties listed above are not theorems, since we do not have rigorous definitions of set and function. What, then, is their status?

Definitions in mathematics usually depend on previous definitions. A vector space is defined as an abelian group with a scalar multiplication. An abelian group is defined as a group with a certain property. A group is defined as a set with certain extra structure. A set is defined as... well, what?

We cannot keep going back indefinitely, otherwise we quite literally would not know what we were talking about. We have to start somewhere. In other words, there have to be some basic concepts not defined in terms of anything else. The concept of set is usually taken to be one of the basic ones, which is why you have probably never read a sentence beginning 'Definition: A set is...'. We will treat function as a basic concept, too.

But now there seems to be a problem. If these basic concepts are not defined in terms of anything else, how are we to know what they really are? How are we going to reason in the watertight, logical way upon which mathematics depends? We cannot simply trust our intuitions, since your intuitive idea of set might be slightly different from mine, and if it came to a dispute about how sets behave, we would have no way of deciding who was right.

The problem is solved as follows. Instead of defining a set to be a such-and-such and a function to be a such-and-such else, we list some properties that we assume sets and functions to have. In other words, we never attempt to say what sets and functions are; we just say what you can do with them.

In his excellent book Mathematics: A Very Short Introduction, Timothy Gowers (2002) considers the question: 'What is the black king in chess?' He swiftly points out that this question is rather peculiar. It is not important that the black king is a small piece of wood, painted a certain colour and carved into a certain shape. We could equally well use a scrap of paper with 'BK' written on it. What matters is what the black king does: it can move in certain ways but not others, according to the rules of chess.

Similarly, we might not be able to say directly what a set or function 'is', but we agree that they are to satisfy all the properties on the list. So the list of properties acts as an agreement on how to use the words 'set' and 'function', just as the rules of chess act as an agreement on how to use the chess pieces.

What we are doing is often referred to as foundations. In this metaphor, the foundation consists of the basic concepts (set and function), which are not built on anything else, but are assumed to satisfy a stated list of properties. On top of the foundations are built some basic definitions and theorems. On top of those are built further definitions and theorems, and so on, towering upwards.

The properties above are stated informally, but they can be formalized using some categorical language. (See Lawvere and Rosebrugh (2003) or Leinster (2014).) In the formal version, we begin by saying that sets and functions form a category, Set. We then list some properties of this category. For example, the category is required to have an initial and a terminal object, and the properties described informally under the headings 'Products' and 'Equalizers' are made formal by the statement that Set 'has limits' (a phrase defined in Chapter 5).

While we were making the list, we were guided by our intuition about sets. But once it is made, our intuition plays no further official role: any disputes about the nature of sets are settled by consulting the list of properties.

(A subtlety arises. Whatever list of properties one writes down, there might be some questions that cannot be settled. In other words, there might be multiple inequivalent categories satisfying all the properties listed. This gets us into the realm of advanced logic: Gödel incompleteness, the continuum hypothesis, and so on, all beyond the scope of this book.)

Now let us look again at the section on the empty set. You might have felt that I was on shaky ground when trying to convince you that $\varnothing$ is initial. But the point is that I do not need to convince you that this is a true statement; I only need to convince you that it is a convenient assumption. Compare the rule for numbers that ${x}^{0} = 1$ . One can reasonably argue that 0 copies of $x$ multiplied together ought to be 1, but really the best justification for this rule is convenience: it makes other rules such as ${x}^{m + n} = {x}^{m} \cdot  {x}^{n}$ true without exception. Indeed, it does not even make sense to ask whether it is 'true' that 0 is initial until we have written down our assumptions about how sets and functions behave. For until then, what could 'true' mean? There is no physical world of sets against which to test such statements.

We can make whatever assumptions about sets we like, but some lead to more interesting mathematics than others. If, for instance, you want to assume that there are no functions from $\varnothing$ to any other set, you can, but the tower of mathematics built on that foundation will look different from what you are used to, and probably not in a good way. For example, the 'number of functions' rule (page 67) will fail, and there will be further unpleasant surprises higher up the tower.

## Exercises

3.1.1 The diagonal functor $\Delta  :$ Set $\rightarrow$ Set $\times$ Set is defined by $\Delta \left( A\right)  = \left( {A, A}\right)$ for all sets $A$ . Exhibit left and right adjoints to $\Delta$ .

3.1.2 In the paragraph headed 'Natural numbers', it was observed that the set $\mathbb{N}$ , together with the element 0 and the function $s : \mathbb{N} \rightarrow  \mathbb{N}$ , has a certain property. This property can be understood as stating that the triple $\left( {\mathbb{N},0, s}\right)$ is the initial object of a certain category $\mathcal{C}$ . Find $\mathcal{C}$ .

### 3.2 Small and large categories

We have now made some assumptions about the nature of sets. One consequence of those assumptions is that in many of the categories we have met, the collection of all objects is too large to form a set. In fact, even the collection of isomorphism classes of objects is often too large to form a set. In this section, I will explain what these statements mean, and prove them.

This section is not of central importance. As this book proceeds, I will say as little as possible about the distinction between sets and collections too large to be sets. Nevertheless, the distinction begins to matter in parts of category theory lying just within the scope of this book (the adjoint functor theorems), as well as beyond.

Given sets $A$ and $B$ , write $\left| A\right|  \leq  \left| B\right|$ (or $\left| B\right|  \geq  \left| A\right|$ ) if there exists an injection $A \rightarrow  B$ . We give no meaning to the expression ’ $\left| A\right|$ ’ or ’ $\left| B\right|$ ’ in isolation. (It would perhaps be more logical to write $A \leq  B$ rather than $\left| A\right|  \leq  \left| B\right|$ , but the notation is well-established.) In the case of finite sets, it just means that the number of elements of $A$ is less than or equal to the number of elements of $B$ .

Since identity maps are injective, $\left| A\right|  \leq  \left| A\right|$ for all sets $A$ , and since the composite of two injections is an injection,

$$
\left| A\right|  \leq  \left| B\right|  \leq  \left| C\right|  \Rightarrow  \left| A\right|  \leq  \left| C\right| .
$$

Also, if $A \cong  B$ then $\left| A\right|  \leq  \left| B\right|  \leq  \left| A\right|$ . Less obvious is the converse:

Theorem 3.2.1 (Cantor-Bernstein) Let $A$ and $B$ be sets. If $\left| A\right|  \leq  \left| B\right|  \leq  \left| A\right|$ then $A \cong  B$ .

Proof Exercise 3.2.12.

These observations tell us that $\leq$ is a preorder (Example 1.1.8(e)) on the collection of all sets. It is not a genuine order, since $\left| A\right|  \leq  \left| B\right|  \leq  \left| A\right|$ only implies that $A \cong  B$ , not $A = B$ . We write $\left| A\right|  = \left| B\right|$ , and say that $A$ and $B$ have the same cardinality, if $A \cong  B$ , or equivalently if $\left| A\right|  \leq  \left| B\right|  \leq  \left| A\right|$ .

As long as we do not confuse equality with isomorphism, the sign $\leq$ behaves as we might imagine. For example, write $\left| A\right|  < \left| B\right|$ if $\left| A\right|  \leq  \left| B\right|$ and $\left| A\right|  \neq  \left| B\right|$ . Then

$$
\left| A\right|  \leq  \left| B\right|  < \left| C\right|  \Rightarrow  \left| A\right|  < \left| C\right| \tag{3.2}
$$

for sets $A, B$ and $C$ . Indeed, we have already established that $\left| A\right|  \leq  \left| C\right|$ , and the strict inequality follows from Theorem 3.2.1.

Here is another fundamental result of set theory.

Theorem 3.2.2 (Cantor) Let $A$ be a set. Then $\left| A\right|  < \left| {\mathcal{P}\left( A\right) }\right|$ .

Recall that $\mathcal{P}\left( A\right)$ is the power set of $A$ . The lemma is easy for finite sets, since if $A$ has $n$ elements then $\mathcal{P}\left( A\right)$ has ${2}^{n}$ elements, and $n < {2}^{n}$ .

Proof Exercise 3.2.13.

Corollary 3.2.3 For every set $A$ , there is a set $B$ such that $\left| A\right|  < \left| B\right|$ .

In other words, there is no biggest set.

We now justify the claim made at the beginning of this section: that for many familiar categories, the collection of isomorphism classes of objects is too large to form a set. We begin by doing this for the category Set itself.

As a clue to why the collection of isomorphism classes of sets might be too large to form a set, consider the following statement: the collection of isomorphism classes of finite sets is too large to form a finite set. This is because there is one isomorphism class of finite sets for each natural number, but there are infinitely many natural numbers.

Proposition 3.2.4 Let I be a set, and let ${\left( {A}_{i}\right) }_{i \in  I}$ be a family of sets. Then there exists a set not isomorphic to any of the sets ${A}_{i}$ .

Proof Put

$$
A = \mathcal{P}\left( {\mathop{\sum }\limits_{{i \in  I}}{A}_{i}}\right) ,
$$

the power set of the sum of the sets ${A}_{i}$ . For each $j \in  I$ , we have the inclusion function ${A}_{j} \rightarrow  \mathop{\sum }\limits_{{i \in  I}}{A}_{i}$ , so by Theorem 3.2.2,

$$
\left| {A}_{j}\right|  \leq  \left| {\mathop{\sum }\limits_{{i \in  I}}{A}_{i}}\right|  < \left| A\right|
$$

Hence $\left| {A}_{j}\right|  < \left| A\right|$ by (3.2), and in particular, ${A}_{j} \ncong  A$ .

We use the word class informally to mean any collection of mathematical objects. All sets are classes, but some classes (such as the class of all sets) are too big to be sets. A class will be called small if it is a set, and large otherwise. For example, Proposition 3.2.4 states that the class of isomorphism classes of sets is large. The crucial point is:

Any individual set is small, but the class of sets is large.

This is even true if we pretend that isomorphic sets are equal.

Although the 'definition' of class is not precise, it will do for our purposes. We make a naive distinction between small and large collections, and implicitly use some intuitively plausible principles (for example, that any subcollection of a small collection is small).

A category $\mathcal{A}$ is small if the class or collection of all maps in $\mathcal{A}$ is small, and large otherwise. If $\mathcal{A}$ is small then the class of objects of $\mathcal{A}$ is small too, since objects correspond one-to-one with identity maps.

A category $\mathcal{A}$ is locally small if for each $A, B \in  \mathcal{A}$ , the class $\mathcal{A}\left( {A, B}\right)$ is small. (So, small implies locally small.) Many authors take local smallness to be part of the definition of category. The class $\mathcal{A}\left( {A, B}\right)$ is often called the hom-set from $A$ to $B$ , although strictly speaking, we should only call it this when $\mathcal{A}$ is locally small.

Example 3.2.5 Set is locally small, because for any two sets $A$ and $B$ , the functions from $A$ to $B$ form a set. This was one of the properties of sets stated in Section 3.1.

Example 3.2.6 Vect ${}_{k}$ , Grp, Ab, Ring and Top are all locally small. For example, given rings $A$ and $B$ , a homomorphism from $A$ to $B$ is a function from $A$ to $B$ with certain properties, and the collection of all functions from $A$ to $B$ is small, so the collection of homomorphisms from $A$ to $B$ is certainly small.

A category is small if and only if it is locally small and its class of objects is small. Again, it may help to consider a similar fact about finiteness: a category $\mathcal{A}$ is finite (that is, the class of all maps in $\mathcal{A}$ is finite) if and only if it is locally finite (that is, each class $\mathcal{A}\left( {A, B}\right)$ is finite) and its class of objects is finite.

Example 3.2.7 Consider the category $\mathcal{B}$ defined in the last paragraph of Example 1.3.20. Its objects correspond to the natural numbers, which form a set, so the class of objects of $\mathcal{B}$ is small. Each hom-set $\mathcal{B}\left( {\mathbf{m},\mathbf{n}}\right)$ is a set (indeed, a finite set), so $\mathcal{B}$ is locally small. Hence $\mathcal{B}$ is small.

A category is essentially small if it is equivalent to some small category. For example, the category of finite sets is essentially small, since by Example 1.3.20, it is equivalent to the small category $\mathcal{B}$ just mentioned.

If two categories $\mathcal{A}$ and $\mathcal{B}$ are equivalent, the class of isomorphism classes of objects of $\mathcal{A}$ is in bijection with that of $\mathcal{B}$ . In a small category, the class of objects is small, so the class of isomorphism classes of objects is certainly small. Hence in an essentially small category, the class of isomorphism classes of objects is small. From this we deduce:

Proposition 3.2.8 Set is not essentially small.

Proof Proposition 3.2.4 states that the class of isomorphism classes of sets is large. The result follows.

By adapting this argument, we can show that many of our standard examples of categories are not essentially small. The strategy is to prove that there are at least as many objects of our category as there are sets.

Example 3.2.9 For any field $k$ , the category ${\mathbf{{Vect}}}_{k}$ of vector spaces over $k$ is not essentially small. As in the proof of Proposition 3.2.8, it is enough to prove that the class of isomorphism classes of vector spaces is large. In other words, it is enough to prove that for any set $I$ and family ${\left( {V}_{i}\right) }_{i \in  I}$ of vector spaces, there exists a vector space not isomorphic to any of the spaces ${V}_{i}$ .

To show this, write ${\operatorname{Vect}}_{k}\xrightarrow[{ < \frac{T}{F}}]{U}$ Set for the free and forgetful functors. As in the proof of Proposition 3.2.4, the set

$$
S = \mathcal{P}\left( {\mathop{\sum }\limits_{{i \in  I}}U\left( {V}_{i}\right) }\right)
$$

has the property that $\left| {U\left( {V}_{i}\right) }\right|  < \left| S\right|$ for all $i \in  I$ . The free vector space $F\left( S\right)$ on $S$ contains a copy of $S$ as a basis, so $\left| S\right|  \leq  \left| {{UF}\left( S\right) }\right|$ . Hence $\left| {U\left( {V}_{i}\right) }\right|  < \left| {{UF}\left( S\right) }\right|$ for all $i$ , and so $F\left( S\right)  \ncong  {V}_{i}$ for all $i$ , as required.

Similarly, none of the categories Grp, Ab, Ring and Top is essentially small (Exercise 3.2.14).

Recall that the category of all categories and functors is written as CAT.

Definition 3.2.10 We denote by Cat the category of small categories and functors between them.

Example 3.2.11 Monoids are by definition sets equipped with certain structure, so the one-object categories that they correspond to are small. Let $\mathcal{M}$ be the full subcategory of Cat consisting of the one-object categories. Then there is an equivalence of categories $\mathbf{{Mon}} \simeq  \mathcal{M}$ . This is proved by the argument in Example 1.3.21, noting that because each object of $\mathcal{M}$ is a small one-object category, the collection of maps from the single object to itself really is a set.

## Exercises

3.2.12 (a) Let $A$ be a set. Let $\theta  : \mathcal{P}\left( A\right)  \rightarrow  \mathcal{P}\left( A\right)$ be a map that is order-preserving with respect to inclusion. A fixed point of $\theta$ is an element $S \in \; \mathcal{P}\left( A\right)$ such that $\theta \left( S\right)  = S$ . By considering

$$
S = \mathop{\bigcup }\limits_{{R \in  \mathcal{P}\left( A\right)  : \theta \left( R\right)  \supseteq  R}}R,
$$

prove that $\theta$ has at least one fixed point.

(b) Take sets and functions $A\overset{f}{ \rightarrow  }B$ . Using (a), show that there is some subset $S$ of $A$ such that $g\left( {B \smallsetminus  {fS}}\right)  = A \smallsetminus  S$ .

(c) Deduce the Cantor-Bernstein theorem (Theorem 3.2.1).

3.2.13 (a) Let $A$ be a set and $f : A \rightarrow  \mathcal{P}\left( A\right)$ a function. By considering

$$
\{ a \in  A \mid  a \notin  f\left( a\right) \} ,
$$

prove that $f$ is not surjective.

(b) Deduce Cantor’s theorem (Theorem 3.2.2): $\left| A\right|  < \left| {\mathcal{P}\left( A\right) }\right|$ for all sets $A$ .

3.2.14 (a) Let $\mathcal{A}$ be a category. Suppose there exists a functor $U : \mathcal{A} \rightarrow$ Set such that $U$ has a left adjoint and for at least one $A \in  \mathcal{A}$ , the set $U\left( A\right)$ has at least two elements. Prove that for any set $I$ and any family ${\left( {A}_{i}\right) }_{i \in  I}$ of objects of $\mathcal{A}$ , there is some object of $\mathcal{A}$ not isomorphic to ${A}_{i}$ for any $i \in  I$ . (Hint: use Exercise 2.3.11.)

(b) Let $\mathcal{A}$ be a category satisfying the assumption of (a). Prove that $\mathcal{A}$ is not essentially small.

(c) Deduce that none of the categories Set, Vect ${}_{k}$ , Grp, Ab, Ring, and Top is essentially small.

3.2.15 Which of the following categories are small? Which are locally small?

(a) Mon, the category of monoids;

(b) $\mathbb{Z}$ , the group of integers, viewed as a one-object category;

(c) $\mathbb{Z}$ , the ordered set of integers;

(d) Cat, the category of small categories;

(e) the multiplicative monoid of cardinals.

3.2.16 Let $O :$ Cat $\rightarrow$ Set be the functor sending a small category to its set of objects. Exhibit a chain of adjoints $C \dashv  D \dashv  O \dashv  I$ .

### 3.3 Historical remarks

The set theory that we began to develop in Section 3.1 is rather different from what many mathematicians think of as set theory. Here I will explain what the socially dominant version of set theory is, why, despite its dominance, it is the object of widespread suspicion, and why the kind of set theory outlined here is a more accurate reflection of how mathematicians use sets in practice.

Cantor's set theory The creation of set theory is generally credited to the German mathematician Georg Cantor, in the late nineteenth century. Previously, sets had seldom been regarded as entities worthy of study in their own right; but Cantor, originally motivated by a problem in Fourier analysis, developed an extensive theory. Among many other things, he showed that there are different sizes of infinity, proving, for instance, that there is no bijection between $\mathbb{N}$ and $\mathbb{R}$ .

Cantor's theory met all the resistance that typically greets a really new idea. His work was criticized as nonsensical, as meaningless, as far too abstract; then later, as all very well but of no use to the mainstream of mathematics. Kronecker, an important mathematician of the day, called him a charlatan and a corrupter of youth. But nowadays, the basics of Cantor's work are on nearly every undergraduate mathematics syllabus.

Times change. In the modern style of mathematics, almost every definition, when unravelled sufficiently, depends on the notion of set. But pre-Cantor, this was not so. It is interesting to try to understand the outlook of mathematicians of the time, who had successfully developed sophisticated subjects such as complex analysis and Galois theory without depending on this notion that we now regard as fundamental.

Before continuing with the history, we need to discuss another fundamental concept.

Types Suppose someone asks you ’is $\sqrt{2} = \pi$ ?’ Your answer is, of course, 'no'. Now suppose someone asks you 'is $\sqrt{2} = \log$ ?' You might frown and wonder if you had heard right, and perhaps your answer would again be 'no'; but it would be a different kind of 'no'. After all, $\sqrt{2}$ is a number, whereas log is a function, so it is inconceivable that they could be equal. A better answer would be 'your question makes no sense'.

This illustrates the idea of types. The square root of 2 is a real number, $\mathbb{Q}$ is a field, ${S}_{3}$ is a group, log is a function from $\left( {0,\infty }\right)$ to $\mathbb{R}$ , and $\frac{d}{dx}$ is an operation that takes as input one function from $\mathbb{R}$ to $\mathbb{R}$ and produces as output another such function. One says that the type of $\sqrt{2}$ is ’real number’, the type of $\mathbb{Q}$ is 'field', and so on. We all have an inbuilt sense of type, and it would not usually occur to us to ask whether two things of different type were equal.

You may have met this idea before if you have programmed computers. Many programming languages require you to declare the type of a variable before you first use it. For example, you might declare that $x$ is to be a variable of type ’real number’, $n$ a variable of type ’integer’, $M$ a variable of type ’ $3 \times  3$ matrix of lists of binary digits', and so on.

The distinction between different types of object has always been instinctively understood. At the beginning of the twentieth century, however, events took a strange turn.

Membership-based set theory Those who came after Cantor sought to compile a definitive list of assumptions to be made about sets: an axiomatization of set theory. The list they arrived at, in the early years of the twentieth century, is known as ZFC (Zermelo-Fraenkel with Choice). It soon became the standard, and it is the only kind of axiomatic set theory that most present-day mathematicians know.

The axiomatization of Zermelo et al. was in some ways similar to the one that we were working towards in the first section of this chapter. But there is at least one crucial difference: whereas we took sets and functions as our basic concepts, they took sets and membership.

At first sight, this difference might seem mild. But when the membership-based approach is used as a foundation on which to build the rest of mathematics, several bizarre features become apparent:

- In the Zermelo approach, everything is a set. For instance, a function is defined as a set with certain properties. Many other things that you would not think of as being sets are, nevertheless, treated as sets: the number $\sqrt{2}$ is a set, the function $\log$ is a set, the operator $\frac{d}{dx}$ is a set, and so on.

You might wonder how this is possible. Perhaps it is useful to compare data storage in a computer, where files of all different types (text, sound, images, and so on) are ultimately encoded as sequences of 0s and 1s. To give an example, in the membership-based set theory presented in most books, the number 4 is encoded as the set

$$
\{ \varnothing ,\{ \varnothing \} ,\{ \varnothing ,\{ \varnothing \} \} ,\{ \varnothing ,\{ \varnothing \} ,\{ \varnothing ,\{ \varnothing \} \} \} \} .
$$

- The virtue of this approach is its simplicity: everything is a set! But the price to be paid is very high: we lose the fundamental notion of type, precisely because everything is regarded as being of type 'set'.

- In the Zermelo approach, the elements of sets are always sets too. This is in conflict with ordinary mathematics. For instance, in ordinary mathematics, $\mathbb{R}$ is certainly a set, but real numbers themselves are not regarded as sets. (After all, what is an element of $\pi$ ?)

- In this approach, membership is a global relation, meaning that for any two sets $A$ and $B$ , it makes sense to ask whether $A \in  B$ . Since this approach views everything as a set, it makes sense to ask such apparently nonsensical questions as ’is $\mathbb{Q} \in  \sqrt{2}$ ?’

Further still, the axioms of ZFC imply that we can form the intersection $A \cap  B$ of any sets $A$ and $B$ . (Its elements are those sets $C$ for which $C \in  A$ and $C \in  B$ .) This makes possible further nonsensical questions such as ’does the cyclic group of order 10 have nonempty intersection with $\mathbb{Z}$ ?’

The answers to these nonsensical questions depend on the fine detail of how mathematical objects (numbers, functions, groups, etc.) are encoded as sets. Even devotees of the membership-based approach agree that this encoding is a matter of convention, just like a word processor's encoding of a document as a string of $0\mathrm{\;s}$ and $1\mathrm{\;s}$ . So the answers to these questions are meaningless.

Set theory today It should now be apparent why many modern-day mathematicians are suspicious of set theory. However often they are told that it is 'the foundation of mathematics', they feel that much of it is irrelevant to their concerns.

To some extent, this is justified. But it is also a symptom of the historical dominance of membership-based set theory: most mathematicians do not realize that there is any other kind. This is a shame. Taking sets and functions (rather than sets and membership) as the basic concepts leads to a theory containing all of the meaningful results of Cantor and others, but with none of the aspects that seem so remote from the rest of mathematics. In particular, the function-based approach respects the fundamental notion of type.

The function-based approach is, of course, categorical, and its advantages are related to more general points about how mathematics looks through categorical eyes. Objects are understood through their place in the ambient category. We get inside an object by probing it with maps to or from other objects. For example, an element of a set $A$ is a map $1 \rightarrow  A$ , and a subset of $A$ is a map $A \rightarrow  2$ . Probing of this kind is the main theme of the next chapter.

Footnote for those familiar with ZFC People brought up on traditional axiomatic set theory often have the following concern when they come across categorical set theory for the first time. The objects and maps of a category form a collection of some kind, perhaps a set, so the notion of category appears to depend on some prior set-like notion. How, then, can sets be axiomatized categorically? Is that not circular?

It is not, because sets can be axiomatized categorically without mentioning categories once. To see how, let us first recall the shape of the ZFC axiomatization of sets. Informally, it looks like this:

- there are some things called sets;

- there is a binary relation on sets, called membership (E);

- some axioms hold.

A categorical axiomatization of sets looks, informally, like this:

- there are some things called sets;

- for each set $A$ and set $B$ , there are some things called functions from $A$ to $B$ ;

- to each function $f$ from $A$ to $B$ and function $g$ from $B$ to $C$ , there is assigned a function $g \circ  f$ from $A$ to $C$ ;

- some axioms hold.

Making precise such phrases as 'some things' requires delicacy, as will be familiar to anyone who has done a logic course. But the difficulties are no worse for categorical axiomatizations of sets than for membership-based axiomatizations such as ZFC.

One popular choice of categorical axioms for set theory can be summarized informally as follows.

1. Composition of functions is associative and has identities.

2. There is a terminal set.

3. There is a set with no elements.

4. A function is determined by its effect on elements.

5. Given sets $A$ and $B$ , one can form their product $A \times  B$ .

6. Given sets $A$ and $B$ , one can form the set of functions from $A$ to $B$ .

7. Given $f : A \rightarrow  B$ and $b \in  B$ , one can form the inverse image ${f}^{-1}\{ b\}$ .

8. The subsets of a set $A$ correspond to the functions from $A$ to $\{ 0,1\}$ .

9. The natural numbers form a set.

10. Every surjection has a section.

This informal summary uses terms such as 'element' and 'inverse image', which can be defined in terms of the basic concepts of set, function and composition. For instance, an element of a set $A$ is defined as a map from the terminal set to $A$ .

It is certainly convenient to express these axioms in terms of categories. For example, the first axiom says that sets and functions form a category, and all ten together can be expressed in categorical jargon as 'sets and functions form a well-pointed topos with natural numbers object and choice'. But in order to state the axioms, it is not necessary to appeal to any general notion of category. They can be expressed directly in terms of sets and functions. For details, see Lawvere and Rosebrugh (2003) or Leinster (2014).

## Exercise

3.3.1 Choose a mathematician at random. Ask them whether they can accurately state any axiomatization of sets (without looking it up). If not, ask them what operating principles they actually use when handling sets in their day-to-day work.

## 4 Representables

A category is a world of objects, all looking at one another. Each sees the world from a different viewpoint.

Consider, for instance, the category of topological spaces, and let us ask how it looks when viewed from the one-point space 1. A map from 1 to a space $X$ is essentially the same thing as a point of $X$ , so we might say that 1 ’sees points’. Similarly, a map from $\mathbb{R}$ to a space $X$ could reasonably be called a curve in $X$ , and in this sense, $\mathbb{R}$ sees curves.

Now consider the category of groups. A map from the infinite cyclic group $\mathbb{Z}$ to a group $G$ amounts to an element of $G$ . (For given $g \in  G$ , there is a unique homomorphism $\phi  : \mathbb{Z} \rightarrow  G$ such that $\phi \left( 1\right)  = g$ .) So, $\mathbb{Z}$ sees elements. Similarly, if $p$ is a prime number then the cyclic group $\mathbb{Z}/p\mathbb{Z}$ sees elements of order 1 or $p$ .

Any ring homomorphism between fields is injective, so in the category of fields, a map $K \rightarrow  L$ is a way of realizing $L$ as an extension of $K$ . Hence each field $K$ sees the extensions of itself. If $K$ and $L$ are fields of different characteristic then there are no homomorphisms between $K$ and $L$ , so the category of fields is the union of disjoint subcategories Field ${}_{0}$ , Field ${}_{2}$ , Field ${}_{3}$ , Field ${}_{5}$ , … consisting of the fields of characteristics $0,2,3,5,\ldots$ . Each field is blind to the fields of different characteristic.

In the ordered set $\left( {\mathbb{R}, \leq  }\right)$ , the object 0 sees whether a number is nonnegative. In other words, if $x$ is nonnegative then there is one map $0 \rightarrow  x$ , and if not, there are none.

We can also ask the dual question: fixing an object of a category, what are the maps into it? Let $S$ be the two-element set, for instance. For an arbitrary set $X$ , the maps from $X$ to $S$ correspond to the subsets of $X$ (as we saw in Section 3.1). Now give $S$ the topology in which one of the singleton subsets is open but the other is not. For any topological space $X$ , the continuous maps from $X$ into $S$ correspond to the open subsets of $X$ .

This chapter explores the theme of how each object sees and is seen by the category in which it lives. We are naturally led to the notion of representable functor, which (after adjunctions) provides our second approach to the idea of universal property.

### 4.1 Definitions and examples

Fix an object $A$ of a category $\mathcal{A}$ . We will consider the totality of maps out of $A$ . To each $B \in  \mathcal{A}$ , there is assigned the set (or class) $\mathcal{A}\left( {A, B}\right)$ of maps from $A$ to $B$ . The content of the following definition is that this assignation is functorial in $B$ : any map $B \rightarrow  {B}^{\prime }$ induces a function $\mathcal{A}\left( {A, B}\right)  \rightarrow  \mathcal{A}\left( {A,{B}^{\prime }}\right)$ .

Definition 4.1.1 Let $\mathcal{A}$ be a locally small category and $A \in  \mathcal{A}$ . We define a functor

$$
{H}^{A} = \mathcal{A}\left( {A, - }\right)  : \mathcal{A} \rightarrow  \text{ Set }
$$

as follows:

- for objects $B \in  \mathcal{A}$ , put ${H}^{A}\left( B\right)  = \mathcal{A}\left( {A, B}\right)$ ;

- for maps $B\overset{g}{ \rightarrow  }{B}^{\prime }$ in $\mathcal{A}$ , define

$$
{H}^{A}\left( g\right)  = \mathcal{A}\left( {A, g}\right)  : \mathcal{A}\left( {A, B}\right)  \rightarrow  \mathcal{A}\left( {A,{B}^{\prime }}\right)
$$

by

$$
p \mapsto  g \circ  p
$$

for all $p : A \rightarrow  B$ .

Remarks 4.1.2 (a) Recall that ’locally small’ means that each class $\mathcal{A}\left( {A, B}\right)$ is in fact a set. This hypothesis is clearly necessary in order for the definition to make sense.

(b) Sometimes ${H}^{A}\left( g\right)$ is written as $g \circ   -$ or ${g}_{ * }$ . All three forms, as well as $\mathcal{A}\left( {A, g}\right)$ , are in use.

Definition 4.1.3 Let $\mathcal{A}$ be a locally small category. A functor $X : \mathcal{A} \rightarrow$ Set is representable if $X \cong  {H}^{A}$ for some $A \in  \mathcal{A}$ . A representation of $X$ is a choice of an object $A \in  \mathcal{A}$ and an isomorphism between ${H}^{A}$ and $X$ .

Representable functors are sometimes just called 'representables'. Only set-valued functors (that is, functors with codomain Set) can be representable.

Example 4.1.4 Consider ${H}^{1} :$ Set $\rightarrow$ Set, where 1 is the one-element set. Since a map from 1 to a set $B$ amounts to an element of $B$ , we have

$$
{H}^{1}\left( B\right)  \cong  B
$$

for each $B \in$ Set. It is easily verified that this isomorphism is natural in $B$ , so ${H}^{1}$ is isomorphic to the identity functor ${1}_{\text{ Set }}$ . Hence ${1}_{\text{ Set }}$ is representable.

Example 4.1.5 All of the 'seeing' functors in the introduction to this chapter are representable. The forgetful functor Top $\rightarrow$ Set is isomorphic to ${H}^{1} =$ Top(1,-), and the forgetful functor Grp $\rightarrow$ Set is isomorphic to $\operatorname{Grp}\left( {\mathbb{Z}, - }\right)$ . For each prime $p$ , there is a functor ${U}_{p} : \operatorname{Grp} \rightarrow$ Set defined on objects by

$$
{U}_{p}\left( G\right)  = \{ \text{ elements of }G\text{ of order 1 or }p\} \text{ , }
$$

and as claimed above, ${U}_{p} \cong  \operatorname{Grp}\left( {\mathbb{Z}/p\mathbb{Z}, - }\right)$ (Exercise 4.1.28). Hence ${U}_{p}$ is representable.

Example 4.1.6 There is a functor ob : Cat $\rightarrow$ Set sending a small category to its set of objects. (The category Cat was introduced in Definition 3.2.10.) It is representable. Indeed, consider the terminal category 1 (with one object and only the identity map). A functor from1to a category $\mathcal{B}$ simply picks out an object of $\mathcal{B}$ . Thus,

$$
{H}^{1}\left( \mathcal{B}\right)  \cong  \mathrm{{ob}}\mathcal{B}\text{ . }
$$

Again, it is easily verified that this isomorphism is natural in $\mathcal{B}$ ; hence ob $\cong$ Cat(1,-). It can be shown similarly that the functor Cat $\rightarrow$ Set sending a small category to its set of maps is representable (Exercise 4.1.31).

Example 4.1.7 Let $M$ be a monoid, regarded as a one-object category. Recall from Example 1.2.8 that a set-valued functor on $M$ is just an $M$ -set. Since the category $M$ has only one object, there is only one representable functor on it (up to isomorphism). As an $M$ -set, the unique representable is the so-called left regular representation of $M$ , that is, the underlying set of $M$ acted on by multiplication on the left.

Example 4.1.8 Let ${\mathbf{{Toph}}}_{ * }$ be the category whose objects are topological spaces equipped with a basepoint and whose arrows are homotopy classes of basepoint-preserving continuous maps. Let ${S}^{1} \in  {\mathbf{{Toph}}}_{ * }$ be the circle. Then for any object $X \in  {\mathbf{{Toph}}}_{ * }$ , the maps ${S}^{1} \rightarrow  X$ in ${\mathbf{{Toph}}}_{ * }$ are the elements of the fundamental group ${\pi }_{1}\left( X\right)$ . Formally, this says that the composite functor

$$
{\mathbf{{Toph}}}_{ * }\overset{{\pi }_{1}}{ \rightarrow  }\mathbf{{Grp}}\overset{U}{ \rightarrow  }\mathbf{{Set}}
$$

is isomorphic to ${\operatorname{Toph}}_{ * }\left( {{S}^{1}, - }\right)$ . In particular, it is representable.

Example 4.1.9 Fix a field $k$ and vector spaces $U$ and $V$ over $k$ . There is a functor

$$
\operatorname{Bilin}\left( {U, V; - }\right)  : {\mathbf{{Vect}}}_{k} \rightarrow  \text{ Set }
$$

whose value $\operatorname{Bilin}\left( {U, V;W}\right)$ at $W \in  {\mathbf{{Vect}}}_{k}$ is the set of bilinear maps $U \times  V \rightarrow \; W$ . It can be shown that this functor is representable; in other words, there is a space $T$ with the property that

$$
\operatorname{Bilin}\left( {U, V;W}\right)  \cong  {\operatorname{Vect}}_{k}\left( {T, W}\right)
$$

naturally in $W$ . This $T$ is the tensor product $U \otimes  V$ , which we met just after the proof of Lemma 0.7.

Adjunctions give rise to representable functors in the following way.

Lemma 4.1.10 Let $\mathcal{A}\overset{\overset{F}{ \rightarrow  }}{\overset{\overset{F}{ \leftarrow  }}{\underset{G}{ \rightarrow  }}}\mathcal{B}$ be locally small categories, and let $A \in  \mathcal{A}$ .

Then the functor

$$
\mathcal{A}\left( {A, G\left( -\right) }\right)  : \mathcal{B} \rightarrow  \text{ Set }
$$

(that is, the composite $\mathcal{B}\overset{G}{ \rightarrow  }\mathcal{A}\overset{{H}^{A}}{ \rightarrow  }$ Set) is representable.

Proof We have

$$
\mathcal{A}\left( {A, G\left( B\right) }\right)  \cong  \mathcal{B}\left( {F\left( A\right) , B}\right)
$$

for each $B \in  \mathcal{B}$ . If we can show that this isomorphism is natural in $B$ , then we will have proved that $\mathcal{A}\left( {A, G\left( -\right) }\right)$ is isomorphic to ${H}^{F\left( A\right) }$ and is therefore representable. So, let $B\overset{q}{ \rightarrow  }{B}^{\prime }$ be a map in $\mathcal{B}$ . We must show that the square

![93_586_1281_378_155_0.jpg](images/93_586_1281_378_155_0.jpg)

commutes, where the horizontal arrows are the bijections provided by the adjunction. For $f : A \rightarrow  G\left( B\right)$ , we have

![93_585_1532_381_180_0.jpg](images/93_585_1532_381_180_0.jpg)

so we must prove that $q \circ  \bar{f} = \overline{G\left( q\right)  \circ  f}$ . This follows immediately from the naturality condition (2.2) in the definition of adjunction (with $g = \bar{f}$ ).

You would not expect a randomly-chosen functor into Set to be representable. In some sense, rather few functors are. However, forgetful functors do tend to be representable:

Proposition 4.1.11 Any set-valued functor with a left adjoint is representable.

Proof Let $G : \mathcal{A} \rightarrow$ Set be a functor with a left adjoint $F$ . Write 1 for the one-point set. Then

$$
G\left( A\right)  \cong  \operatorname{Set}\left( {1, G\left( A\right) }\right)
$$

naturally in $A \in  \mathcal{A}$ (by Example 4.1.4), that is, $G \cong  \operatorname{Set}\left( {1, G\left( -\right) }\right)$ . So by Lemma 4.1.10, $G$ is representable; indeed, $G \cong  {H}^{F\left( 1\right) }$ .

Example 4.1.12 Several of the examples of representables mentioned above arise as in Proposition 4.1.11. For instance, $U :$ Top $\rightarrow$ Set has a left adjoint $D$ (Example 2.1.5), and $D\left( 1\right)  \cong  1$ , so we recover the result that $U \cong  {H}^{1}$ . Similarly, Exercise 3.2.16 asked you to construct a left adjoint $D$ to the objects functor ob : Cat $\rightarrow$ Set. This functor $D$ satisfies $D\left( 1\right)  \cong  \mathbf{1}$ , proving again that ob $\cong  {H}^{1}$ .

Example 4.1.13 The forgetful functor $U : {\mathbf{{Vect}}}_{k} \rightarrow$ Set is representable, since it has a left adjoint. Indeed, if $F$ denotes the left adjoint then $F\left( 1\right)$ is the 1-dimensional vector space $k$ , so $U \cong  {H}^{k}$ . This is also easy to see directly: a map from $k$ to a vector space $V$ is uniquely determined by the image of 1, which can be any element of $V$ ; hence ${\operatorname{Vect}}_{k}\left( {k, V}\right)  \cong  U\left( V\right)$ naturally in $V$ .

Example 4.1.14 Examples 2.1.3 began with the declaration that forgetful functors between categories of algebraic structures usually have left adjoints. Take the category CRing of commutative rings and the forgetful functor $U$ : CRing $\rightarrow$ Set. This general principle suggests that $U$ has a left adjoint, and Proposition 4.1.11 then tells us that $U$ is representable.

Let us see how this works explicitly. Given a set $S$ , let $\mathbb{Z}\left\lbrack  S\right\rbrack$ be the ring of polynomials over $\mathbb{Z}$ in commuting variables ${x}_{s}\left( {s \in  S}\right)$ . (This was called $F\left( S\right)$ in Example 1.2.4(b).) Then $S \mapsto  \mathbb{Z}\left\lbrack  S\right\rbrack$ defines a functor Set $\rightarrow$ CRing, and this is left adjoint to $U$ . Hence $U \cong  {H}^{\mathbb{Z}\left\lbrack  x\right\rbrack  }$ . Again, this can be verified directly: for any ring $R$ , the maps $\mathbb{Z}\left\lbrack  x\right\rbrack   \rightarrow  R$ correspond one-to-one with the elements of $R$ (Exercises 0.13 and 4.1.29).

We have defined, for each object $A$ of our category $\mathcal{A}$ , a functor ${H}^{A} \in$ [ $\mathcal{A}$ , Set]. This describes how $A$ sees the world. As $A$ varies, the view varies. On the other hand, it is always the same world being seen, so the different views from different objects are somehow related. (Compare aerial photos taken from a moving aeroplane, which agree well enough on their overlaps that they can be patched together to make one big picture.) So the family ${\left( {H}^{A}\right) }_{A \in  \mathcal{A}}$ of ’views’ has some consistency to it. What this means is that whenever there is a map between objects $A$ and ${A}^{\prime }$ , there is also a map between ${H}^{A}$ and ${H}^{{A}^{\prime }}$ .

Precisely, a map ${A}^{\prime }\overset{f}{ \rightarrow  }A$ induces a natural transformation

![95_675_530_201_120_0.jpg](images/95_675_530_201_120_0.jpg)

whose $B$ -component (for $B \in  \mathcal{A}$ ) is the function

$$
{H}^{A}\left( B\right)  = \mathcal{A}\left( {A, B}\right)  \rightarrow  {H}^{{A}^{\prime }}\left( B\right)  = \mathcal{A}\left( {{A}^{\prime }, B}\right)
$$

$$
p\; \mapsto  \;p \circ  f.
$$

Again, ${H}^{f}$ goes by a variety of other names: $\mathcal{A}\left( {f, - }\right) ,{f}^{ * }$ , and $-  \circ  f$ .

Note the reversal of direction! Each functor ${H}^{A}$ is covariant, but they come together to form a contravariant functor, as in the following definition.

Definition 4.1.15 Let $\mathcal{A}$ be a locally small category. The functor

$$
{H}^{ \bullet  } : {\mathcal{A}}^{\mathrm{{op}}} \rightarrow  \left\lbrack  {\mathcal{A},\mathbf{{Set}}}\right\rbrack
$$

is defined on objects $A$ by ${H}^{ \bullet  }\left( A\right)  = {H}^{A}$ and on maps $f$ by ${H}^{ \bullet  }\left( f\right)  = {H}^{f}$ .

The symbol $\bullet$ is another type of blank, like-.

All of the definitions presented so far in this chapter can be dualized. At the formal level, this is trivial: reverse all the arrows, so that every $\mathcal{A}$ becomes an ${\mathcal{A}}^{\text{ op }}$ and vice versa. But in our usual examples, the flavour is different. We are no longer asking what objects see, but how they are seen.

Let us first dualize Definition 4.1.1.

Definition 4.1.16 Let $\mathcal{A}$ be a locally small category and $A \in  \mathcal{A}$ . We define a functor

$$
{H}_{A} = \mathcal{A}\left( {-, A}\right)  : {\mathcal{A}}^{\text{ op }} \rightarrow  \text{ Set }
$$

as follows:

- for objects $B \in  \mathcal{A}$ , put ${H}_{A}\left( B\right)  = \mathcal{A}\left( {B, A}\right)$ ;

- for maps ${B}^{\prime }\overset{g}{ \rightarrow  }B$ in $\mathcal{A}$ , define

$$
{H}_{A}\left( g\right)  = \mathcal{A}\left( {g, A}\right)  = {g}^{ * } =  -  \circ  g : \mathcal{A}\left( {B, A}\right)  \rightarrow  \mathcal{A}\left( {{B}^{\prime }, A}\right)
$$

by

$$
p \mapsto  p \circ  g
$$

for all $p : B \rightarrow  A$ .

If you know about dual vector spaces, this construction will seem familiar. In particular, you will not be surprised that a map ${B}^{\prime } \rightarrow  B$ induces a map in the opposite direction, ${H}_{A}\left( B\right)  \rightarrow  {H}_{A}\left( {B}^{\prime }\right)$ .

We now define representability for contravariant set-valued functors. Strictly speaking, this is unnecessary, as a contravariant functor on $\mathcal{A}$ is a covariant functor on ${\mathcal{A}}^{\text{ op }}$ , and we already know what it means for a covariant set-valued functor to be representable. But it is useful to have a direct definition.

Definition 4.1.17 Let $\mathcal{A}$ be a locally small category. A functor $X : {\mathcal{A}}^{\text{ op }} \rightarrow$ Set is representable if $X \cong  {H}_{A}$ for some $A \in  \mathcal{A}$ . A representation of $X$ is a choice of an object $A \in  \mathcal{A}$ and an isomorphism between ${H}_{A}$ and $X$ .

Example 4.1.18 There is a functor

$$
\mathcal{P} : {\mathbf{{Set}}}^{\mathrm{{op}}} \rightarrow  \mathbf{{Set}}
$$

sending each set $B$ to its power set $\mathcal{P}\left( B\right)$ , and defined on maps $g : {B}^{\prime } \rightarrow  B$ by $\left( {\mathcal{P}\left( g\right) }\right) \left( U\right)  = {g}^{-1}U$ for all $U \in  \mathcal{P}\left( B\right)$ . (Here ${g}^{-1}U$ denotes the inverse image or preimage of $U$ under $g$ , defined by ${g}^{-1}U = \left\{  {{x}^{\prime } \in  {B}^{\prime } \mid  g\left( {x}^{\prime }\right)  \in  U}\right\}$ .) As we saw in Section 3.1, a subset amounts to a map into the two-point set 2. Precisely put, $\mathcal{P} \cong  {H}_{2}$ .

Example 4.1.19 Similarly, there is a functor

$$
\mathcal{O} : {\mathbf{{Top}}}^{\mathrm{{op}}} \rightarrow  \text{ Set }
$$

defined on objects $B$ by taking $\mathcal{O}\left( B\right)$ to be the set of open subsets of $B$ . If $S$ denotes the two-point topological space in which exactly one of the two singleton subsets is open, then continuous maps from a space $B$ into $S$ correspond naturally to open subsets of $B$ (Exercise 4.1.30). Hence $\mathcal{O} \cong  {H}_{S}$ , and $\mathcal{O}$ is representable.

Example 4.1.20 In Example 1.2.11, we defined a functor $C : {\mathbf{{Top}}}^{\text{ op }} \rightarrow  \mathbf{{Ring}}$ , assigning to each space the ring of continuous real-valued functions on it. The composite functor

$$
{\mathbf{{Top}}}^{\text{ op }}\overset{C}{ \rightarrow  }\text{ Ring }\overset{U}{ \rightarrow  }\text{ Set }
$$

is representable, since by definition, $U\left( {C\left( X\right) }\right)  = \operatorname{Top}\left( {X,\mathbb{R}}\right)$ for topological spaces $X$ .

Previously, we assembled the covariant representables ${\left( {H}^{A}\right) }_{A \in  \mathcal{A}}$ into one big functor ${H}^{ \bullet  }$ . We now do the same for the contravariant representables ${\left( {H}_{A}\right) }_{A \in  \mathcal{A}}$ .

Any map $A\overset{f}{ \rightarrow  }{A}^{\prime }$ in $\mathcal{A}$ induces a natural transformation

$$
\text{ Non }\frac{{H}_{A}}{\sqrt{{H}_{f}}}\text{ Set }
$$

(also called $\mathcal{A}\left( {-, f}\right) ,{f}_{ * }$ or $f \circ   -$ ), whose component at an object $B \in  \mathcal{A}$ is

$$
{H}_{A}\left( B\right)  = \mathcal{A}\left( {B, A}\right)  \rightarrow  {H}_{{A}^{\prime }}\left( B\right)  = \mathcal{A}\left( {B,{A}^{\prime }}\right)
$$

$$
p\; \mapsto  \;f \circ  p.
$$

Definition 4.1.21 Let $\mathcal{A}$ be a locally small category. The Yoneda embedding of $\mathcal{A}$ is the functor

$$
{H}_{ \bullet  } : \mathcal{A} \rightarrow  \left\lbrack  {{\mathcal{A}}^{\mathrm{{op}}},\mathbf{{Set}}}\right\rbrack
$$

defined on objects $A$ by ${H}_{ \bullet  }\left( A\right)  = {H}_{A}$ and on maps $f$ by ${H}_{ \bullet  }\left( f\right)  = {H}_{f}$ .

Here is a summary of the definitions so far.

For each $A \in  \mathcal{A}$ , we have a functor Putting them all together gives a functor ${\mathcal{A}}^{\text{ op }}\xrightarrow[]{{H}^{ * }}\left\lbrack  {\mathcal{A},\mathbf{{Set}}}\right\rbrack$ . For each $A \in  \mathcal{A}$ , we have a functor $\;{\mathcal{A}}^{\text{ op }}\xrightarrow[]{{H}_{A}}$ Set. Putting them all together gives a functor $\mathcal{A}\overset{{H}_{ \bullet  }}{ \rightarrow  }\left\lbrack  {{\mathcal{A}}^{\text{ op }},\mathbf{{Set}}}\right\rbrack$ .

The second pair of functors is the dual of the first. Both involve contravariance; it cannot be avoided.

In the theory of representable functors, it does not make much difference whether we work with the first or the second pair. Any theorem that we prove about one dualizes to give a theorem about the other. We choose to work with the second pair, the ${H}_{A}\mathrm{\;s}$ and ${H}_{ \bullet  }$ . In a sense to be explained, ${H}_{ \bullet  }$ ’embeds’ $\mathcal{A}$ into $\left\lbrack  {{\mathcal{A}}^{\text{ op }},\text{ Set }}\right\rbrack$ . This can be useful, because the category $\left\lbrack  {{\mathcal{A}}^{\text{ op }},\text{ Set }}\right\rbrack$ has some good properties that $\mathcal{A}$ might not have.

Exercise 4.1.27 asks you to prove that ${H}_{ \bullet  }$ is injective on isomorphism classes of objects. It is strongly recommended that you do it before reading on, as it encapsulates the key ideas of the rest of this chapter.

There is one more functor to define. It unifies the first and second pairs of functors shown above.

Definition 4.1.22 Let $\mathcal{A}$ be a locally small category. The functor

$$
{\operatorname{Hom}}_{\mathcal{A}} : {\mathcal{A}}^{\mathrm{{op}}} \times  \mathcal{A} \rightarrow  \text{ Set }
$$

is defined by

![98_605_405_414_153_0.jpg](images/98_605_405_414_153_0.jpg)

In other words, ${\operatorname{Hom}}_{\mathcal{A}}\left( {A, B}\right)  = \mathcal{A}\left( {A, B}\right)$ and $\left( {{\operatorname{Hom}}_{\mathcal{A}}\left( {f, g}\right) }\right) \left( p\right)  = g \circ  p \circ  f$ , whenever ${A}^{\prime }\overset{f}{ \rightarrow  }A\overset{p}{ \rightarrow  }B\overset{g}{ \rightarrow  }{B}^{\prime }$ .

Remarks 4.1.23 (a) The existence of the functor ${\operatorname{Hom}}_{\mathcal{A}}$ is something like the fact that for a metric space $\left( {X, d}\right)$ , the metric is itself a continuous map $d : X \times  X \rightarrow  \mathbb{R}$ . (If we take two points and move each one slightly, the distance between them changes only slightly.)

(b) In terms of Exercise 1.2.25, ${\operatorname{Hom}}_{\mathcal{A}}$ is the functor ${\mathcal{A}}^{\text{ op }} \times  \mathcal{A} \rightarrow$ Set corresponding to the families of functors ${\left( {H}^{A}\right) }_{A \in  \mathcal{A}}$ and ${\left( {H}_{B}\right) }_{B \in  \mathcal{A}}$ .

(c) In Example 2.1.6, we saw that for any set $B$ , there is an adjunction $\left( {- \times  B}\right)  \dashv \; {\left( -\right) }^{B}$ of functors Set $\rightarrow$ Set. Similarly, for any category $\mathcal{B}$ , there is an adjunction $\left( {- \times  \mathcal{B}}\right)  \dashv  \left\lbrack  {\mathcal{B}, - }\right\rbrack$ of functors $\mathbf{{CAT}} \rightarrow  \mathbf{{CAT}}$ ; in other words, there is a canonical bijection

$$
\operatorname{CAT}\left( {\mathcal{A} \times  \mathcal{B},\mathcal{C}}\right)  \cong  \operatorname{CAT}\left( {\mathcal{A},\left\lbrack  {\mathcal{B},\mathcal{C}}\right\rbrack  }\right)
$$

for $\mathcal{A},\mathcal{B},\mathcal{C} \in  \mathbf{{CAT}}$ . Under this bijection, the functors

$$
{\operatorname{Hom}}_{\mathcal{A}} : {\mathcal{A}}^{\mathrm{{op}}} \times  \mathcal{A} \rightarrow  \text{ Set, }\;{H}^{ \bullet  } : {\mathcal{A}}^{\mathrm{{op}}} \rightarrow  \left\lbrack  {\mathcal{A},\text{ Set }}\right\rbrack
$$

correspond to one another. Thus, ${\operatorname{Hom}}_{\mathcal{A}}$ carries the same information as ${H}^{ \bullet  }$ (or ${H}_{ \bullet  }$ ), presented slightly differently.

Remark 4.1.24 We can now explain the naturality in the definition of adjunction (Definition 2.1.1). Take categories and functors $\mathcal{A}\overset{\overset{F}{ \rightarrow  }}{\underset{G}{ \rightarrow  }}\mathcal{B}$ . They give rise to functors

![98_645_1453_332_169_0.jpg](images/98_645_1453_332_169_0.jpg)

The composite functor $\downarrow$ sends $\left( {A, B}\right)$ to $\mathcal{B}\left( {F\left( A\right) , B}\right)$ ; it can be written as $\mathcal{B}\left( {F\left( -\right) , - }\right)$ . The composite $\rightarrow   \downarrow$ sends $\left( {A, B}\right)$ to $\mathcal{A}\left( {A, G\left( B\right) }\right)$ . Exercise 4.1.32 asks you to show that these two functors

$$
\mathcal{B}\left( {F\left( -\right) , - }\right) ,\mathcal{A}\left( {-, G\left( -\right) }\right)  : {\mathcal{A}}^{\mathrm{{op}}} \times  \mathcal{B} \rightarrow  \text{ Set }
$$

are naturally isomorphic if and only if $F$ and $G$ are adjoint. This justifies the claim in Remark 2.1.2(a): the naturality requirements (2.2) and (2.3) in the definition of adjunction simply assert that two particular functors are naturally isomorphic.

Objects of an arbitrary category do not have elements in any obvious sense. However, sets certainly have elements, and we have observed that an element of a set $A$ is the same thing as a map $1 \rightarrow  A$ . This inspires the following definition.

Definition 4.1.25 Let $A$ be an object of a category. A generalized element of $A$ is a map with codomain $A$ . A map $S \rightarrow  A$ is a generalized element of $A$ of shape $S$ .

'Generalized element' is nothing more than a synonym of 'map', but sometimes it is useful to think of maps as generalized elements.

For example, when $A$ is a set, a generalized element of $A$ of shape 1 is an ordinary element of $A$ , and a generalized element of $A$ of shape $\mathbb{N}$ is a sequence in $A$ . In the category of topological spaces, the generalized elements of shape 1 (the one-point space) are the points, and the generalized elements of shape ${S}^{1}$ (the circle) are, by definition, loops. As this suggests, in categories of geometric objects, we might equally well say ’figures of shape $S$ ’.

In algebra, we are often interested in solutions to equations such as ${x}^{2} + {y}^{2} =$ 1. Perhaps we begin by being particularly interested in solutions in $\mathbb{Q}$ , but then realize that in order to study rational solutions, it will be helpful to study solutions in other rings first. (This is often a fruitful strategy.) Given a ring $A$ , a pair $\left( {a, b}\right)  \in  A \times  A$ satisfying ${a}^{2} + {b}^{2} = 1$ amounts to a homomorphism of rings

$$
\mathbb{Z}\left\lbrack  {x, y}\right\rbrack  /\left( {{x}^{2} + {y}^{2} - 1}\right)  \rightarrow  A.
$$

Thus, the solutions to our equation (in any ring) can be seen as the generalized elements of shape $\mathbb{Z}\left\lbrack  {x, y}\right\rbrack  /\left( {{x}^{2} + {y}^{2} - 1}\right)$ .

For an object $S$ of a category $\mathcal{A}$ , the functor

$$
{H}^{S} : \mathcal{A} \rightarrow  \text{ Set }
$$

sends an object to its set of generalized elements of shape $S$ . The functoriality tells us that any map $A \rightarrow  B$ in $\mathcal{A}$ transforms $S$ -elements of $A$ into $S$ -elements of $B$ . For example, taking $\mathcal{A} =$ Top and $S = {S}^{1}$ , any continuous map $A \rightarrow  B$ transforms loops in $A$ into loops in $B$ .

## Exercises

4.1.26 Find three examples of representable functors not mentioned above.

4.1.27 Let $\mathcal{A}$ be a locally small category, and let $A,{A}^{\prime } \in  \mathcal{A}$ with ${H}_{A} \cong  {H}_{{A}^{\prime }}$ . Prove directly that $A \cong  {A}^{\prime }$ .

4.1.28 Let $p$ be a prime number. Show that the functor ${U}_{p} :$ Grp $\rightarrow$ Set defined in Example 4.1.5 is isomorphic to $\operatorname{Grp}\left( {\mathbb{Z}/p\mathbb{Z}, - }\right)$ . (To check that there is an isomorphism of functors - that is, a natural isomorphism - you will first need to define ${U}_{p}$ on maps. There is only one sensible way to do this.)

4.1.29 Using the result of Exercise 0.13(a), prove that the forgetful functor CRing $\rightarrow$ Set is isomorphic to CRing $\left( {\mathbb{Z}\left\lbrack  x\right\rbrack  , - }\right)$ , as in Example 4.1.14.

4.1.30 The Sierpiński space is the two-point topological space $S$ in which one of the singleton subsets is open but the other is not. Prove that for any topological space $X$ , there is a canonical bijection between the open subsets of $X$ and the continuous maps $X \rightarrow  S$ . Use this to show that the functor $\mathcal{O}$ : ${\mathbf{{Top}}}^{\mathrm{{op}}} \rightarrow$ Set of Example 4.1.19 is represented by $S$ .

4.1.31 Let $M :$ Cat $\rightarrow$ Set be the functor that sends a small category $\mathcal{A}$ to the set of all maps in $\mathcal{A}$ . Prove that $M$ is representable.

4.1.32 Take locally small categories $\mathcal{A}$ and $\mathcal{B}$ , and functors $\mathcal{A} \triangleq  \frac{F}{G} \geq  \mathcal{B}$ . Show that $F$ is left adjoint to $G$ if and only if the two functors

$$
\mathcal{B}\left( {F\left( -\right) , - }\right) ,\mathcal{A}\left( {-, G\left( -\right) }\right)  : {\mathcal{A}}^{\mathrm{{op}}} \times  \mathcal{B} \rightarrow  \text{ Set }
$$

of Remark 4.1.24 are naturally isomorphic. (Hint: this is made easier by using either Exercise 1.3.29 or Exercise 2.1.14.)

### 4.2 The Yoneda lemma

What do representables see?

Recall from Definition 1.2.15 that functors ${\mathcal{A}}^{\text{ op }} \rightarrow$ Set are sometimes called ’presheaves’ on $\mathcal{A}$ . So for each $A \in  \mathcal{A}$ we have a representable presheaf ${H}_{A}$ , and we are asking how the rest of the presheaf category $\left\lbrack  {{\mathcal{A}}^{\text{ op }},\text{ Set }}\right\rbrack$ looks from the viewpoint of ${H}_{A}$ . In other words, if $X$ is another presheaf, what are the maps ${H}_{A} \rightarrow  X$ ?

Newcomers to category theory commonly find that the material presented in this section is where they first get stuck. Typically, the core of the difficulty is in understanding the question just asked. Let us ask it again.

We start by fixing a locally small category $\mathcal{A}$ . We then take an object $A \in  \mathcal{A}$ and a functor $X : {\mathcal{A}}^{\text{ op }} \rightarrow$ Set. The object $A$ gives rise to another functor ${H}_{A} = \mathcal{A}\left( {-, A}\right)  : {\mathcal{A}}^{\text{ op }} \rightarrow$ Set. The question is: what are the maps ${H}_{A} \rightarrow  X$ ? Since ${H}_{A}$ and $X$ are both objects of the presheaf category $\left\lbrack  {{\mathcal{A}}^{\text{ op }},\text{ Set }}\right\rbrack$ , the 'maps' concerned are maps in $\left\lbrack  {{\mathcal{A}}^{\text{ op }},\text{ Set }}\right\rbrack$ . So, we are asking what natural transformations

$$
\text{ who }\frac{{H}_{A}}{x}\text{ Set } \tag{4.1}
$$

there are. The set of such natural transformations is called

$$
\left\lbrack  {{\mathcal{A}}^{\mathrm{{op}}},\mathbf{{Set}}}\right\rbrack  \left( {{H}_{A}, X}\right) \text{ . }
$$

(This is a special case of the notation $\mathcal{B}\left( {B,{B}^{\prime }}\right)$ for the set of maps $B \rightarrow  {B}^{\prime }$ in a category $\mathcal{B}$ . Here, $\mathcal{B} = \left\lbrack  {{\mathcal{A}}^{\mathrm{{op}}},\mathbf{{Set}}}\right\rbrack  , B = {H}_{A}$ , and ${B}^{\prime } = X$ .) We want to know what this set is.

There is an informal principle of general category theory that allows us to guess the answer. Look back at Remarks 1.1.2(b), 1.2.2(a) and 1.3.2(a) on the definitions of category, functor and natural transformation. Each remark is of the form 'from input of one type, it is possible to construct exactly one output of another type'. For example, in Remark 1.1.2(b), the input is a sequence of maps ${A}_{0}\overset{{f}_{1}}{ \rightarrow  }\cdots \overset{{f}_{n}}{ \rightarrow  }{A}_{n}$ , the output is a map ${A}_{0} \rightarrow  {A}_{n}$ , and the statement is that no matter what we do with the input data ${f}_{1},\ldots ,{f}_{n}$ , there is only one map ${A}_{0} \rightarrow  {A}_{n}$ that we can construct.

Let us apply this principle to our question. We have just seen how, given as input an object $A \in  \mathcal{A}$ and a presheaf $X$ on $\mathcal{A}$ , we can construct a set, namely, $\left\lbrack  {{\mathcal{A}}^{\text{ op }},\mathbf{{Set}}}\right\rbrack  \left( {{H}_{A}, X}\right)$ . Are there any other ways to construct a set from the same input data $\left( {A, X}\right)$ ? Yes: simply take the set $X\left( A\right)$ ! The informal principle suggests that these two sets are the same:

$$
\left\lbrack  {{\mathcal{A}}^{\mathrm{{op}}},\mathbf{{Set}}}\right\rbrack  \left( {{H}_{A}, X}\right)  \cong  X\left( A\right) \tag{4.2}
$$

for all $A \in  \mathcal{A}$ and $X \in  \left\lbrack  {{\mathcal{A}}^{\text{ op }},\mathbf{{Set}}}\right\rbrack$ . This turns out to be true; and that is the Yoneda lemma.

Informally, then, the Yoneda lemma says that for any $A \in  \mathcal{A}$ and presheaf $X$ on $\mathcal{A}$ :

A natural transformation ${H}_{A} \rightarrow  X$ is an element of $X\left( A\right)$ .

Here is the formal statement. The proof follows shortly.

Theorem 4.2.1 (Yoneda) Let $\mathcal{A}$ be a locally small category. Then

$$
\left\lbrack  {{\mathcal{A}}^{\mathrm{{op}}},\mathbf{{Set}}}\right\rbrack  \left( {{H}_{A}, X}\right)  \cong  X\left( A\right) \tag{4.3}
$$

naturally in $A \in  \mathcal{A}$ and $X \in  \left\lbrack  {{\mathcal{A}}^{\mathrm{{op}}},\mathbf{{Set}}}\right\rbrack$ .

This is exactly what was stated in (4.2), except that the word 'naturally' has appeared. Recall from Definition 1.3.12 that for functors $F, G : \mathcal{C} \rightarrow  \mathcal{D}$ , the phrase ’ $F\left( C\right)  \cong  G\left( C\right)$ naturally in $C$ ’ means that there is a natural isomorphism $F \cong  G$ . So the use of this phrase in the Yoneda lemma suggests that each side of (4.3) is functorial in both $A$ and $X$ . This means, for instance, that a map $X \rightarrow  {X}^{\prime }$ must induce a map

$$
\left\lbrack  {{\mathcal{A}}^{\mathrm{{op}}},\mathbf{{Set}}}\right\rbrack  \left( {{H}_{A}, X}\right)  \rightarrow  \left\lbrack  {{\mathcal{A}}^{\mathrm{{op}}},\mathbf{{Set}}}\right\rbrack  \left( {{H}_{A},{X}^{\prime }}\right) ,
$$

and that not only does the isomorphism (4.3) hold for every $A$ and $X$ , but also, the isomorphisms can be chosen in a way that is compatible with these induced maps. Precisely, the Yoneda lemma states that the composite functor

$$
{\mathcal{A}}^{\mathrm{{op}}} \times  \left\lbrack  {{\mathcal{A}}^{\mathrm{{op}}},\mathbf{{Set}}}\right\rbrack  \xrightarrow[]{{H}_{ \bullet  }^{\mathrm{{op}}} \times  1}{\left\lbrack  {\mathcal{A}}^{\mathrm{{op}}},\mathbf{{Set}}\right\rbrack  }^{\mathrm{{op}}} \times  \left\lbrack  {{\mathcal{A}}^{\mathrm{{op}}},\mathbf{{Set}}}\right\rbrack  \xrightarrow[]{{\operatorname{Hom}}_{\left\lbrack  {\mathcal{A}}^{\mathrm{{op}}},\mathbf{{Set}}\right\rbrack  }}\mathbf{{Set}}
$$

$\left( {A, X}\right) \; \mapsto  \;\left( {{H}_{A}, X}\right) \; \mapsto  \;\left\lbrack  {{\mathcal{A}}^{\mathrm{{op}}},\mathbf{{Set}}}\right\rbrack  \left( {{H}_{A}, X}\right)$

is naturally isomorphic to the evaluation functor

$$
{\mathcal{A}}^{\mathrm{{op}}} \times  \left\lbrack  {{\mathcal{A}}^{\mathrm{{op}}},\mathbf{{Set}}}\right\rbrack   \rightarrow  \text{ Set }
$$

$$
\left( {A, X}\right) \; \mapsto  \;X\left( A\right) .
$$

If the Yoneda lemma were false then the world would look much more complex. For take a presheaf $X : {\mathcal{A}}^{\text{ op }} \rightarrow$ Set, and define a new presheaf ${X}^{\prime }$ by

$$
{X}^{\prime } = \left\lbrack  {{\mathcal{A}}^{\mathrm{{op}}},\mathbf{{Set}}}\right\rbrack  \left( {{H}_{ \bullet  }, X}\right)  : {\mathcal{A}}^{\mathrm{{op}}} \rightarrow  \mathbf{{Set}},
$$

that is, ${X}^{\prime }\left( A\right)  = \left\lbrack  {{\mathcal{A}}^{\text{ op }},\mathbf{{Set}}}\right\rbrack  \left( {{H}_{A}, X}\right)$ for all $A \in  \mathcal{A}$ . Yoneda tells us that ${X}^{\prime }\left( A\right)  \cong \; X\left( A\right)$ naturally in $A$ ; in other words, ${X}^{\prime } \cong  X$ . If Yoneda were false then starting from a single presheaf $X$ , we could build an infinite sequence $X,{X}^{\prime },{X}^{\prime \prime },\ldots$ of new presheaves, potentially all different. But in reality, the situation is very simple: they are all the same.

The proof of the Yoneda lemma is the longest proof so far. Nevertheless, there is essentially only one way to proceed at each stage. If you suspect that you are one of those newcomers to category theory for whom the Yoneda lemma presents the first serious challenge, an excellent exercise is to work out the proof before reading it. No ingenuity is required, only an understanding of all the terms in the statement.

Proof of the Yoneda lemma We have to define, for each $A$ and $X$ , a bijection between the sets $\left\lbrack  {{\mathcal{A}}^{\mathrm{{op}}},\text{ Set }}\right\rbrack  \left( {{H}_{A}, X}\right)$ and $X\left( A\right)$ . We then have to show that our bijection is natural in $A$ and $X$ .

First, fix $A \in  \mathcal{A}$ and $X \in  \left\lbrack  {{\mathcal{A}}^{\text{ op }},\text{ Set }}\right\rbrack$ . We define functions

$$
\left\lbrack  {{\mathcal{A}}^{\mathrm{{op}}},\mathbf{{Set}}}\right\rbrack  \left( {{H}_{A}, X}\right) \overset{\overset{\left( \begin{matrix} \widehat{} \end{matrix}\right) }{ \leftarrow  }}{\underset{\left( \begin{matrix} \widetilde{} \\  \end{matrix}\right) }{ \rightarrow  }}X\left( A\right) \tag{4.4}
$$

and show that they are mutually inverse. So we have to do four things: define the function(   ), define the function(   ), show that(   )is the identity, and show that $\left( \widetilde{\;}\right)$ is the identity.

- Given $\alpha  : {H}_{A} \rightarrow  X$ , define $\widehat{\alpha } \in  X\left( A\right)$ by $\widehat{\alpha } = {\alpha }_{A}\left( {1}_{A}\right)$ . (How else could we possibly define it?)

- Let $x \in  X\left( A\right)$ . We have to define a natural transformation $\widetilde{x} : {H}_{A} \rightarrow  X$ . That is, we have to define for each $B \in  \mathcal{A}$ a function

$$
{\widetilde{x}}_{B} : {H}_{A}\left( B\right)  = \mathcal{A}\left( {B, A}\right)  \rightarrow  X\left( B\right)
$$

and show that the family $\widetilde{x} = {\left( {\widetilde{x}}_{B}\right) }_{B \in  \mathcal{A}}$ satisfies naturality.

Given $B \in  \mathcal{A}$ and $f \in  \mathcal{A}\left( {B, A}\right)$ , define

$$
{\widetilde{x}}_{B}\left( f\right)  = \left( {X\left( f\right) }\right) \left( x\right)  \in  X\left( B\right) .
$$

(How else could we possibly define it?) This makes sense, since $X\left( f\right)$ is a map $X\left( A\right)  \rightarrow  X\left( B\right)$ . To prove naturality, we must show that for any map ${B}^{\prime }\overset{g}{ \rightarrow  }B$ in $\mathcal{A}$ , the square

![103_586_1173_405_189_0.jpg](images/103_586_1173_405_189_0.jpg)

commutes. To reduce clutter, let us write $X\left( g\right)$ as ${Xg}$ , and so on. Now for all $f \in  \mathcal{A}\left( {B, A}\right)$ , we have

![103_579_1473_426_171_0.jpg](images/103_579_1473_426_171_0.jpg)

and $X\left( {f \circ  g}\right)  = \left( {Xg}\right)  \circ  \left( {Xf}\right)$ by functoriality, so the square does commute.

- Given $x \in  X\left( A\right)$ , we have to show that $\widehat{\widetilde{x}} = x$ , and indeed,

$$
\widehat{\widetilde{x}} = {\widetilde{x}}_{A}\left( {1}_{A}\right)  = \left( {X{1}_{A}}\right) \left( x\right)  = {1}_{X\left( A\right) }\left( x\right)  = x.
$$

- Given $\alpha  : {H}_{A} \rightarrow  X$ , we have to show that $\widetilde{\widehat{\alpha }} = \alpha$ . Two natural transformations are equal if and only if all their components are equal; so, we have to show that ${\left( \widetilde{\widehat{\alpha }}\right) }_{B} = {\alpha }_{B}$ for all $B \in  \mathcal{A}$ . Each side of this equation is a function from ${H}_{A}\left( B\right)  = \mathcal{A}\left( {B, A}\right)$ to $X\left( B\right)$ , and two functions are equal if and only if they take equal values at every element of the domain; so, we have to show that

$$
{\left( \widetilde{\widehat{\alpha }}\right) }_{B}\left( f\right)  = {\alpha }_{B}\left( f\right)
$$

for all $B \in  \mathcal{A}$ and $f : B \rightarrow  A$ in $\mathcal{A}$ . The left-hand side is by definition

$$
{\left( \widetilde{\widehat{\alpha }}\right) }_{B}\left( f\right)  = \left( {Xf}\right) \left( \widehat{\alpha }\right)  = \left( {Xf}\right) \left( {{\alpha }_{A}\left( {1}_{A}\right) }\right) ,
$$

so it remains to prove that

$$
\left( {Xf}\right) \left( {{\alpha }_{A}\left( {1}_{A}\right) }\right)  = {\alpha }_{B}\left( f\right) . \tag{4.5}
$$

By naturality of $\alpha$ (the only tool at our disposal), the square

![104_625_947_396_188_0.jpg](images/104_625_947_396_188_0.jpg)

commutes, which when taken at ${1}_{A} \in  \mathcal{A}\left( {A, A}\right)$ gives equation (4.5).

(The proof is not over yet, but it is worth pausing to consider the significance of the fact that $\widetilde{\widehat{\alpha }} = \alpha$ . Since $\widehat{\alpha }$ is the value of $\alpha$ at ${1}_{A}$ , this implies:

A natural transformation ${H}_{A} \rightarrow  X$ is determined by its value at ${1}_{A}$ .

Just how a natural transformation ${H}_{A} \rightarrow  X$ is determined by its value at ${1}_{A}$ is described in equation (4.5).)

This establishes the bijection (4.4) for each $A \in  \mathcal{A}$ and $X \in  \left\lbrack  {{\mathcal{A}}^{\text{ op }},\mathbf{{Set}}}\right\rbrack$ . We now show that the bijection is natural in $A$ and $X$ .

We employ two mildly labour-saving devices. First, in principle we have to prove naturality of both (̂) and (̃), but by Lemma 1.3.11, it is enough to prove naturality of just one of them. We prove naturality of (̂). Second, by Exercise 1.3.29, $\left( \widehat{\;}\right)$ is natural in the pair $\left( {A, X}\right)$ if and only if it is natural in $A$ for each fixed $X$ and natural in $X$ for each fixed $A$ . So, it remains to check these two types of naturality.

Naturality in $A$ states that for each $X \in  \left\lbrack  {{\mathcal{A}}^{\text{ op }},\mathbf{{Set}}}\right\rbrack$ and $B\overset{f}{ \rightarrow  }A$ in $\mathcal{A}$ , the

square

![105_500_405_554_177_0.jpg](images/105_500_405_554_177_0.jpg)

commutes. For $\alpha  : {H}_{A} \rightarrow  X$ , we have

![105_549_644_458_174_0.jpg](images/105_549_644_458_174_0.jpg)

so we have to show that ${\left( \alpha  \circ  {H}_{f}\right) }_{B}\left( {1}_{B}\right)  = \left( {Xf}\right) \left( {{\alpha }_{A}\left( {1}_{A}\right) }\right)$ . Indeed,

$$
{\left( \alpha  \circ  {H}_{f}\right) }_{B}\left( {1}_{B}\right)  = {\alpha }_{B}\left( {{\left( {H}_{f}\right) }_{B}\left( {1}_{B}\right) }\right)
$$

$$
= {\alpha }_{B}\left( {f \circ  {1}_{B}}\right)  = {\alpha }_{B}\left( f\right)
$$

$$
= \left( {Xf}\right) \left( {{\alpha }_{A}\left( {1}_{A}\right) }\right) ,
$$

where the first step is by definition of composition in $\left\lbrack  {{\mathcal{A}}^{\text{ op }},\mathbf{{Set}}}\right\rbrack$ , the second is by definition of ${H}_{f}$ , and the last is by equation (4.5).

Naturality in $X$ states that for each $A \in  \mathcal{A}$ and map

$$
\text{ . }{\omega }^{\text{ op }}\underset{{X}^{\prime }}{\underbrace{\parallel \theta }}\text{ Set }
$$

in $\left\lbrack  {{\mathcal{A}}^{\text{ op }},\text{ Set }}\right\rbrack$ , the square

![105_494_1315_563_169_0.jpg](images/105_494_1315_563_169_0.jpg)

commutes. For $\alpha  : {H}_{A} \rightarrow  X$ , we have

![105_568_1549_418_163_0.jpg](images/105_568_1549_418_163_0.jpg)

and ${\left( \theta  \circ  \alpha \right) }_{A} = {\theta }_{A} \circ  {\alpha }_{A}$ by definition of composition in $\left\lbrack  {{\mathcal{A}}^{\text{ op }},\text{ Set }}\right\rbrack$ , so the square does commute. This completes the proof.

## Exercises

4.2.2 State the dual of the Yoneda lemma.

4.2.3 One way to understand the Yoneda lemma is to examine some special cases. Here we consider one-object categories.

Let $M$ be a monoid. The underlying set of $M$ can be given a right $M$ -action by multiplication: $x \cdot  m = {xm}$ for all $x, m \in  M$ . This $M$ -set is called the right regular representation of $M$ . Let us write it as $\underline{M}$ .

(a) When $M$ is regarded as a one-object category, functors ${M}^{\mathrm{{op}}} \rightarrow$ Set correspond to right $M$ -sets (Example 1.2.14). Show that the $M$ -set corresponding to the unique representable functor ${M}^{\text{ op }} \rightarrow$ Set is the right regular representation.

(b) Now let $X$ be any right $M$ -set. Show that for each $x \in  X$ , there is a unique map $\alpha  : \underline{M} \rightarrow  X$ of right $M$ -sets such that $\alpha \left( 1\right)  = x$ . Deduce that there is a bijection between \{maps $\underline{M} \rightarrow  X$ of right $M$ -sets\} and $X$ .

(c) Deduce the Yoneda lemma for one-object categories.

### 4.3 Consequences of the Yoneda lemma

The Yoneda lemma is fundamental in category theory. Here we look at three important consequences.

Notation 4.3.1 An arrow decorated with a $\sim$ , as in $A\overset{ \sim  }{ \rightarrow  }B$ , denotes an isomorphism.

## A representation is a universal element

Corollary 4.3.2 Let $\mathcal{A}$ be a locally small category and $X : {\mathcal{A}}^{\mathrm{{op}}} \rightarrow$ Set. Then a representation of $X$ consists of an object $A \in  \mathcal{A}$ together with an element $u \in  X\left( A\right)$ such that:

(4.6)

$$
\text{ for each }B \in  \mathcal{A}\text{ and }x \in  X\left( B\right) \text{ , there is a unique map }\bar{x} : B \rightarrow  A
$$

such that $\left( {X\bar{x}}\right) \left( u\right)  = x$ .

To clarify the statement, first recall that by definition, a representation of $X$ is an object $A \in  \mathcal{A}$ together with a natural isomorphism $\alpha  : {H}_{A}\overset{ \sim  }{ \rightarrow  }X$ . Corollary 4.3.2 states that such pairs $\left( {A,\alpha }\right)$ are in natural bijection with pairs $\left( {A, u}\right)$ satisfying condition (4.6).

Pairs $\left( {B, x}\right)$ with $B \in  \mathcal{A}$ and $x \in  X\left( B\right)$ are sometimes called elements of the presheaf $X$ . (Indeed, the Yoneda lemma tells us that $x$ amounts to a generalized element of $X$ of shape ${H}_{B}$ .) An element $u$ satisfying condition (4.6) is sometimes called a universal element of $X$ . So, Corollary 4.3.2 says that a representation of a presheaf $X$ amounts to a universal element of $X$ .

Proof By the Yoneda lemma, we have only to show that for $A \in  \mathcal{A}$ and $u \in  X\left( A\right)$ , the natural transformation $\widetilde{u} : {H}_{A} \rightarrow  X$ is an isomorphism if and only if (4.6) holds. (Here we are using the notation introduced in the proof of the Yoneda lemma.) Now, $\widetilde{u}$ is an isomorphism if and only if for all $B \in  \mathcal{A}$ , the function

$$
{\widetilde{u}}_{B} : {H}_{A}\left( B\right)  = \mathcal{A}\left( {B, A}\right)  \rightarrow  X\left( B\right)
$$

is a bijection, if and only if for all $B \in  \mathcal{A}$ and $x \in  X\left( B\right)$ , there is a unique $\bar{x} \in  \mathcal{A}\left( {B, A}\right)$ such that ${\widetilde{u}}_{B}\left( \bar{x}\right)  = x$ . But ${\widetilde{u}}_{B}\left( \bar{x}\right)  = \left( {X\bar{x}}\right) \left( u\right)$ , so this is exactly condition (4.6).

Our examples will use the dual form, for covariant set-valued functors:

Corollary 4.3.3 Let $\mathcal{A}$ be a locally small category and $X : \mathcal{A} \rightarrow$ Set. Then a representation of $X$ consists of an object $A \in  \mathcal{A}$ together with an element $u \in  X\left( A\right)$ such that:

(4.7)

$$
\text{ for each }B \in  \mathcal{A}\text{ and }x \in  X\left( B\right) \text{ , there is a unique map }\bar{x} : A \rightarrow  B
$$

such that $\left( {X\bar{x}}\right) \left( u\right)  = x$ .

Proof Follows immediately by duality.

Example 4.3.4 Fix a set $S$ and consider the functor

$$
X = \operatorname{Set}\left( {S, U\left( -\right) }\right)  : \;{\operatorname{Vect}}_{k} \rightarrow  \text{ Set }
$$

$$
V\; \mapsto  \;\operatorname{Set}\left( {S, U\left( V\right) }\right) \text{ . }
$$

Here are two familiar (and true!) statements about $X$ :

(a) there exist a vector space $F\left( S\right)$ and an isomorphism

$$
{\operatorname{Vect}}_{k}\left( {F\left( S\right) , V}\right)  \cong  \operatorname{Set}\left( {S, U\left( V\right) }\right) \tag{4.8}
$$

natural in $V \in  {\mathbf{{Vect}}}_{k}$ (Example 2.1.3(a));

(b) there exist a vector space $F\left( S\right)$ and a function $u : S \rightarrow  U\left( {F\left( S\right) }\right)$ such that:

for each vector space $V$ and function $f : S \rightarrow  U\left( V\right)$ , there is a unique linear map $\bar{f} : F\left( S\right)  \rightarrow  V$ such that

![107_691_1599_217_158_0.jpg](images/107_691_1599_217_158_0.jpg)

commutes (as in the introduction to Section 2.3, where $u$ was called by its usual name, ${\eta }_{S}$ ).

Each of these two statements says that $X$ is representable. Statement (a) says that there is an isomorphism $X\left( V\right)  \cong  \operatorname{Vect}\left( {F\left( S\right) , V}\right)$ natural in $V$ , that is, an isomorphism $X \cong  {H}^{F\left( S\right) }$ . So $X$ is representable, by definition of representability. Statement (b) says that $u \in  X\left( {F\left( S\right) }\right)$ satisfies condition (4.7). So $X$ is representable, by Corollary 4.3.3.

You will have noticed that the first way of saying that $X$ is representable is substantially shorter than the second. Indeed, it is clear that if the situation of (b) holds then there is an isomorphism

$$
{\operatorname{Vect}}_{k}\left( {F\left( S\right) , V}\right) \overset{ \sim  }{ \rightarrow  }\operatorname{Set}\left( {S, U\left( V\right) }\right)
$$

natural in $V$ , defined by $g \mapsto  U\left( g\right)  \circ  u$ . But it looks at first as if (b) says rather more than (a), since it states that the two functors are not only naturally isomorphic, but naturally isomorphic in a rather special way. Corollary 4.3.3 tells us that this is an illusion: all natural isomorphisms (4.8) arise in this way. It is the word 'natural' in (a) that hides the explicit detail.

Example 4.3.5 The same can be said for any other adjunction $\mathcal{A}\underset{ \leftarrow  G}{\overset{F}{ \rightleftharpoons  }}\mathcal{B}$ .

Fix $A \in  \mathcal{A}$ and put

$$
X = \mathcal{A}\left( {A, G\left( -\right) }\right)  : \mathcal{B} \rightarrow  \text{ Set. }
$$

Then $X$ is representable, and this can be expressed in either of the following ways:

(a) $\mathcal{A}\left( {A, G\left( B\right) }\right)  \cong  \mathcal{B}\left( {F\left( A\right) , B}\right)$ naturally in $B$ ; in other words, $X \cong  {H}^{F\left( A\right) }$ (as in Lemma 4.1.10);

(b) the unit map ${\eta }_{A} : A \rightarrow  G\left( {F\left( A\right) }\right)$ is an initial object of the comma category $\left( {A \Rightarrow  G}\right)$ ; that is, ${\eta }_{A} \in  X\left( {F\left( A\right) }\right)$ satisfies condition (4.7).

This observation can be developed into an alternative proof of Theorem 2.3.6, the reformulation of adjointness in terms of initial objects.

Example 4.3.6 For any group $G$ and element $x \in  G$ , there is a unique homomorphism $\phi  : \mathbb{Z} \rightarrow  G$ such that $\phi \left( 1\right)  = x$ . This means that $1 \in  U\left( \mathbb{Z}\right)$ is a universal element of the forgetful functor $U : \mathbf{{Grp}} \rightarrow  \mathbf{{Set}}$ ; in other words, condition (4.7) holds when $\mathcal{A} = \operatorname{Grp}, X = U, A = \mathbb{Z}$ and $u = 1$ . So $1 \in  U\left( \mathbb{Z}\right)$ gives a representation ${H}^{\mathbb{Z}}\overset{ \sim  }{ \rightarrow  }U$ of $U$ .

On the other hand, the same is true with -1 in place of 1 . The isomorphisms ${H}^{\mathbb{Z}}\overset{ \sim  }{ \rightarrow  }U$ coming from 1 and -1 are not equal, because Corollary 4.3.3 provides a one-to-one correspondence between universal elements and representations.

## The Yoneda embedding

Here is a second corollary of the Yoneda lemma.

Corollary 4.3.7 For any locally small category $\mathcal{A}$ , the Yoneda embedding

$$
{H}_{ \bullet  } : \mathcal{A} \rightarrow  \left\lbrack  {{\mathcal{A}}^{\mathrm{{op}}},\mathbf{{Set}}}\right\rbrack
$$

is full and faithful.

Informally, this says that for $A,{A}^{\prime } \in  \mathcal{A}$ , a map ${H}_{A} \rightarrow  {H}_{{A}^{\prime }}$ of presheaves is the same thing as a map $A \rightarrow  {A}^{\prime }$ in $\mathcal{A}$ .

Proof We have to show that for each $A,{A}^{\prime } \in  \mathcal{A}$ , the function

$$
\mathcal{A}\left( {A,{A}^{\prime }}\right)  \rightarrow  \left\lbrack  {{\mathcal{A}}^{\mathrm{{op}}},\mathbf{{Set}}}\right\rbrack  \left( {{H}_{A},{H}_{{A}^{\prime }}}\right) \tag{4.9}
$$

$$
f \mapsto  {H}_{f}
$$

is bijective. By the Yoneda lemma (taking ’ $X$ ’ to be ${H}_{{A}^{\prime }}$ ), the function

$$
\left( \widetilde{}\right)  : {H}_{{A}^{\prime }}\left( A\right)  \rightarrow  \left\lbrack  {{\mathcal{A}}^{\mathrm{{op}}},\mathbf{{Set}}}\right\rbrack  \left( {{H}_{A},{H}_{{A}^{\prime }}}\right) \tag{4.10}
$$

is bijective, so it is enough to prove that the functions (4.9) and (4.10) are equal. Thus, given $f : A \rightarrow  {A}^{\prime }$ , we have to prove that $\widetilde{f} = {H}_{f}$ , or equivalently, $\widehat{{H}_{f}} = f$ . And indeed,

$$
\widehat{{H}_{f}} = {\left( {H}_{f}\right) }_{A}\left( {1}_{A}\right)  = f \circ  {1}_{A} = f,
$$

as required.

In mathematics at large, the word 'embedding' is used (sometimes informally) to mean a map $A \rightarrow  B$ that makes $A$ isomorphic to its image in $B$ . For example, an injection of sets $i : A \rightarrow  B$ might be called an embedding, because it provides a bijection between $A$ and the subset ${iA}$ of $B$ . Similarly, a map $i : A \rightarrow  B$ of topological spaces might be called an embedding if it is a homeomorphism to its image, so that $A \cong  {iA}$ . Corollary 1.3.19 tells us that in category theory, a full and faithful functor $\mathcal{A} \rightarrow  \mathcal{B}$ can reasonably be called an embedding, as it makes $\mathcal{A}$ equivalent to a full subcategory of $\mathcal{B}$ .

In the case at hand, the Yoneda embedding ${H}_{ \bullet  } : \mathcal{A} \rightarrow  \left\lbrack  {{\mathcal{A}}^{\text{ op }},\mathbf{{Set}}}\right\rbrack$ embeds $\mathcal{A}$ into its own presheaf category (Figure 4.1). So, $\mathcal{A}$ is equivalent to the full subcategory of $\left\lbrack  {{\mathcal{A}}^{\text{ op }},\mathbf{{Set}}}\right\rbrack$ whose objects are the representables.

![110_649_355_320_216_0.jpg](images/110_649_355_320_216_0.jpg)

Figure 4.1 A category $\mathcal{A}$ embedded into its presheaf category.

In general, full subcategories are the easiest subcategories to handle. For instance, given objects $A$ and ${A}^{\prime }$ of a full subcategory, we can speak unambiguously of the ’maps’ from $A$ to ${A}^{\prime }$ ; it makes no difference whether this is understood to mean maps in the subcategory or maps in the whole category. Similarly, we can speak unambiguously of isomorphism of objects of the subcategory, as in the following lemma.

Lemma 4.3.8 Let $J : \mathcal{A} \rightarrow  \mathcal{B}$ be a full and faithful functor and $A,{A}^{\prime } \in  \mathcal{A}$ . Then:

(a) a map $f$ in $\mathcal{A}$ is an isomorphism if and only if the map $J\left( f\right)$ in $\mathcal{B}$ is an isomorphism;

(b) for any isomorphism $g : J\left( A\right)  \rightarrow  J\left( {A}^{\prime }\right)$ in $\mathcal{B}$ , there is a unique isomorphism $f : A \rightarrow  {A}^{\prime }$ in $\mathcal{A}$ such that $J\left( f\right)  = g$ ;

(c) the objects $A$ and ${A}^{\prime }$ of $\mathcal{A}$ are isomorphic if and only if the objects $J\left( A\right)$ and $J\left( {A}^{\prime }\right)$ of $\mathcal{B}$ are isomorphic.

Proof Exercise 4.3.15.

Example 4.3.9 In Example 4.3.6, we considered the representations of the forgetful functor $U : \mathbf{{Grp}} \rightarrow  \mathbf{{Set}}$ , and found two different isomorphisms ${H}^{\mathbb{Z}}\overset{ \sim  }{ \rightarrow  }U$ . Did we find all of them?

Since ${H}^{\mathbb{Z}} \cong  U$ , there are as many isomorphisms ${H}^{\mathbb{Z}}\overset{ \sim  }{ \rightarrow  }U$ as there are isomorphisms ${H}^{\mathbb{Z}}\overset{ \sim  }{ \rightarrow  }{H}^{\mathbb{Z}}$ . By Corollary 4.3.7 and Lemma 4.3.8(b), there are as many of these as there are group isomorphisms $\mathbb{Z}\overset{ \sim  }{ \rightarrow  }\mathbb{Z}$ . There are precisely two such (corresponding to the two generators $\pm  1$ of $\mathbb{Z}$ ), so we did indeed find all the isomorphisms ${H}^{\mathbb{Z}} \rightarrow  U$ . Differently put, there are exactly two universal elements of $U\left( \mathbb{Z}\right)$ .

In Section 6.2, we will see that every presheaf can be built from representa-bles, in very roughly the same way that every positive integer can be built from primes.

![111_636_354_283_280_0.jpg](images/111_636_354_283_280_0.jpg)

Figure 4.2 If $\mathcal{A}\left( {B, A}\right)  \cong  \mathcal{A}\left( {B,{A}^{\prime }}\right)$ naturally in $B$ , then $A \cong  {A}^{\prime }$ .

## Isomorphism of representables

In Exercise 4.1.27, you were asked to prove directly that if ${H}_{A} \cong  {H}_{{A}^{\prime }}$ then $A \cong  {A}^{\prime }$ . The proof contains all the main ideas in the proof of the Yoneda lemma. The result itself can also be deduced from the Yoneda lemma, as follows.

Corollary 4.3.10 Let $\mathcal{A}$ be a locally small category and $A,{A}^{\prime } \in  \mathcal{A}$ . Then

$$
{H}_{A} \cong  {H}_{{A}^{\prime }} \Leftrightarrow  A \cong  {A}^{\prime } \Leftrightarrow  {H}^{A} \cong  {H}^{{A}^{\prime }}.
$$

Proof By duality, it is enough to prove the first ' $\Leftrightarrow$ '. This follows from Corollary 4.3.7 and Lemma 4.3.8(c).

Since functors always preserve isomorphism (Exercise 1.2.21), the force of this statement is that

$$
{H}_{A} \cong  {H}_{{A}^{\prime }} \Rightarrow  A \cong  {A}^{\prime }\text{ . }
$$

In other words, if $\mathcal{A}\left( {B, A}\right)  \cong  \mathcal{A}\left( {B,{A}^{\prime }}\right)$ naturally in $B$ , then $A \cong  {A}^{\prime }$ . Thinking of $\mathcal{A}\left( {B, A}\right)$ as ’ $A$ viewed from $B$ ’, the corollary tells us that two objects are the same if and only if they look the same from all viewpoints (Figure 4.2). (If it looks like a duck, walks like a duck, and quacks like a duck, then it probably is a duck.)

Example 4.3.11 Consider Corollary 4.3.10 in the case $\mathcal{A} =$ Grp. Take two groups $A$ and ${A}^{\prime }$ , and suppose someone tells us that $A$ and ${A}^{\prime }$ ’look the same from $B$ ’ (meaning that ${H}_{A}\left( B\right)  \cong  {H}_{{A}^{\prime }}\left( B\right)$ ) for all groups $B$ . Then, for instance:

- ${H}_{A}\left( 1\right)  \cong  {H}_{{A}^{\prime }}\left( 1\right)$ , where 1 is the trivial group. But ${H}_{A}\left( 1\right)  = \operatorname{Grp}\left( {1, A}\right)$ is a one-element set, as is ${H}_{{A}^{\prime }}\left( 1\right)$ , no matter what $A$ and ${A}^{\prime }$ are. So this tells us nothing at all.

- ${H}_{A}\left( \mathbb{Z}\right)  \cong  {H}_{{A}^{\prime }}\left( \mathbb{Z}\right)$ . We know that ${H}_{A}\left( \mathbb{Z}\right)$ is the underlying set of $A$ , and similarly for ${A}^{\prime }$ . So $A$ and ${A}^{\prime }$ have isomorphic underlying sets. But for all we know so far, they might have entirely different group structures.

- ${H}_{A}\left( {\mathbb{Z}/p\mathbb{Z}}\right)  \cong  {H}_{{A}^{\prime }}\left( {\mathbb{Z}/p\mathbb{Z}}\right)$ for every prime $p$ , so by Example 4.1.5, $A$ and ${A}^{\prime }$ have the same number of elements of each prime order.

Each of these isomorphisms gives only partial information about the similarity of $A$ and ${A}^{\prime }$ . But if we know that ${H}_{A}\left( B\right)  \cong  {H}_{{A}^{\prime }}\left( B\right)$ for all groups $B$ , and naturally in $B$ , then $A \cong  {A}^{\prime }$ .

Example 4.3.12 The category of sets is very unusual in this respect. For any set $A$ , we have

$$
A \cong  \operatorname{Set}\left( {1, A}\right)  = {H}_{A}\left( 1\right) ,
$$

so ${H}_{A}\left( 1\right)  \cong  {H}_{{A}^{\prime }}\left( 1\right)$ implies $A \cong  {A}^{\prime }$ . In other words, two objects of Set are the same if they look the same from the point of view of the one-element set. This is a familiar feature of sets: the only thing that matters about a set is its elements!

For a general category, Corollary 4.3.10 tells us that two objects are the same if they have the same generalized elements of all shapes. But the category of sets has a special property: if I choose an object and tell you only what its generalized elements of shape 1 are, then you can deduce exactly what my object must be.

Example 4.3.13 Let $G : \mathcal{B} \rightarrow  \mathcal{A}$ be a functor, and suppose that both $F$ and ${F}^{\prime }$ are left adjoint to $G$ . Then for each $A \in  \mathcal{A}$ , we have

$$
\mathcal{B}\left( {F\left( A\right) , B}\right)  \cong  \mathcal{A}\left( {A, G\left( B\right) }\right)  \cong  \mathcal{B}\left( {{F}^{\prime }\left( A\right) , B}\right)
$$

naturally in $B \in  \mathcal{B}$ , so ${H}^{F\left( A\right) } \cong  {H}^{{F}^{\prime }\left( A\right) }$ , so $F\left( A\right)  \cong  {F}^{\prime }\left( A\right)$ by Corollary 4.3.10. In fact, this isomorphism is natural in $A$ , so that $F \cong  {F}^{\prime }$ . This shows that left adjoints are unique, as claimed in Remark 2.1.2(d). Dually, right adjoints are unique. See also Exercise 4.3.18.

Example 4.3.14 Corollary 4.3.10 implies that if a set-valued functor is isomorphic to both ${H}^{A}$ and ${H}^{{A}^{\prime }}$ then $A \cong  {A}^{\prime }$ . So the functor determines the representing object, if one exists. For instance, take the functor

$$
\operatorname{Bilin}\left( {U, V; - }\right)  : {\mathbf{{Vect}}}_{k} \rightarrow  \text{ Set }
$$

of Example 4.1.9. Corollary 4.3.10 implies that up to isomorphism, there is at most one vector space $T$ such that

$$
\operatorname{Bilin}\left( {U, V;W}\right)  \cong  {\operatorname{Vect}}_{k}\left( {T, W}\right)
$$

naturally in $W$ . It can be shown that there does, in fact, exist such a vector space $T$ . Since all such spaces $T$ are isomorphic, it is legitimate to refer to any of them as the tensor product of $U$ and $V$ .

## Exercises

4.3.15 Prove Lemma 4.3.8.

4.3.16 Let $\mathcal{A}$ be a locally small category. Prove each of the following statements directly (without using the Yoneda lemma).

(a) ${H}_{ \bullet  } : \mathcal{A} \rightarrow  \left\lbrack  {{\mathcal{A}}^{\text{ op }},\mathbf{{Set}}}\right\rbrack$ is faithful.

(b) ${H}_{ \bullet  }$ is full.

(c) Given $A \in  \mathcal{A}$ and a presheaf $X$ on $\mathcal{A}$ , if $X\left( A\right)$ has an element $u$ that is universal in the sense of Corollary 4.3.2, then $X \cong  {H}_{A}$ .

4.3.17 Interpret the theory of Chapter 4 in the case where the category $\mathcal{A}$ is discrete. For example, what do presheaves look like, and which ones are representable? What does the Yoneda lemma tell us? Does its proof become any shorter? What about the corollaries of the Yoneda lemma?

4.3.18 Let $\mathcal{B}$ be a category and $J : \mathcal{C} \rightarrow  \mathcal{D}$ a functor. There is an induced functor

$$
J \circ   -  : \left\lbrack  {\mathcal{B},\mathcal{C}}\right\rbrack   \rightarrow  \left\lbrack  {\mathcal{B},\mathcal{D}}\right\rbrack
$$

defined by composition with $J$ .

(a) Show that if $J$ is full and faithful then so is $J \circ   -$ .

(b) Deduce that if $J$ is full and faithful and $G,{G}^{\prime } : \mathcal{B} \rightarrow  \mathcal{C}$ with $J \circ  G \cong  J \circ  {G}^{\prime }$ then $G \cong  {G}^{\prime }$ .

(c) Now deduce that right adjoints are unique: if $F : \mathcal{A} \rightarrow  \mathcal{B}$ and $G,{G}^{\prime } : \mathcal{B} \rightarrow \; \mathcal{A}$ with $F \dashv  G$ and $F \dashv  {G}^{\prime }$ then $G \cong  {G}^{\prime }$ . (Hint: the Yoneda embedding is full and faithful.)

5

## Limits

Limits, and the dual concept, colimits, provide our third approach to the idea of universal property.

Adjointness is about the relationships between categories. Representability is a property of set-valued functors. Limits are about what goes on inside a category.

The concept of limit unifies many familiar constructions in mathematics. Whenever you meet a method for taking some objects and maps in a category and constructing a new object out of them, there is a good chance that you are looking at either a limit or a colimit. For instance, in group theory, we can take a homomorphism between two groups and form its kernel, which is a new group. This construction is an example of a limit in the category of groups. Or, we might take two natural numbers and form their lowest common multiple. This is an example of a colimit in the poset of natural numbers, ordered by divisibility.

### 5.1 Limits: definition and examples

The definition of limit is very general. We build up to it by first examining some particularly useful types of limit: products, equalizers, and pullbacks.

## Products

Let $X$ and $Y$ be sets. The familiar cartesian product $X \times  Y$ is characterized by the property that an element of $X \times  Y$ is an element of $X$ together with an element of $Y$ . Since elements are just maps from 1, this says that a map $1 \rightarrow  X \times  Y$ amounts to a map $1 \rightarrow  X$ together with a map $1 \rightarrow  Y$ .

A little thought reveals that the same is true when 1 is replaced throughout

by any set $A$ whatsoever. (In other words, a generalized element of $X \times  Y$ of shape $A$ amounts to a generalized element of $X$ of shape $A$ together with a generalized element of $Y$ of shape $A$ .) The bijection between

$$
\text{ maps }A \rightarrow  X \times  Y
$$

and

$$
\text{ pairs of maps }\left( {A \rightarrow  X, A \rightarrow  Y}\right)
$$

is given by composing with the projection maps

$$
X\overset{{p}_{1}}{ \leftrightarrow  }X \times  Y\overset{{p}_{2}}{ \rightarrow  }Y
$$

$$
x \leftarrow  \left( {x, y}\right) \; \mapsto  \;y
$$

This suggests the following definition.

Definition 5.1.1 Let $\mathcal{A}$ be a category and $X, Y \in  \mathcal{A}$ . A product of $X$ and $Y$ consists of an object $P$ and maps

![115_657_946_237_139_0.jpg](images/115_657_946_237_139_0.jpg)

with the property that for all objects and maps(5.1)

![115_657_1153_239_139_0.jpg](images/115_657_1153_239_139_0.jpg)

in $\mathcal{A}$ , there exists a unique map $\bar{f} : A \rightarrow  P$ such that(5.2)

![115_655_1363_241_239_0.jpg](images/115_655_1363_241_239_0.jpg)

commutes. The maps ${p}_{1}$ and ${p}_{2}$ are called the projections.

Remarks 5.1.2 (a) Products do not always exist. For example, if $\mathcal{A}$ is the discrete two-object category

$$
\begin{matrix} {X \bullet  } & & { \bullet  Y} \end{matrix}
$$

then $X$ and $Y$ do not have a product. But when objects $X$ and $Y$ of a category do have a product, it is unique up to isomorphism. (This can be proved directly, much as in Lemma 2.1.8. It also follows from Corollary 6.1.2.) This justifies talking about the product of $X$ and $Y$ .

(b) Strictly speaking, the product consists of the object $P$ together with the projections ${p}_{1}$ and ${p}_{2}$ . But informally, we often refer to $P$ alone as the product of $X$ and $Y$ . We write $P$ as $X \times  Y$ .

Example 5.1.3 Any two sets $X$ and $Y$ have a product in Set. It is the usual cartesian product $X \times  Y$ , equipped with the usual projection maps ${p}_{1}$ and ${p}_{2}$ .

Let us check that this really is a product in the sense of Definition 5.1.1. Take sets and functions as in diagram (5.1). Define $\bar{f} : A \rightarrow  X \times  Y$ by $\bar{f}\left( a\right)  = \; \left( {{f}_{1}\left( a\right) ,{f}_{2}\left( a\right) }\right)$ . Then ${p}_{i} \circ  \bar{f} = {f}_{i}$ for $i = 1,2$ ; that is, diagram (5.2) commutes with $P = X \times  Y$ . Moreover, this is the only map making diagram (5.2) commute. For suppose that $\widehat{f} : A \rightarrow  X \times  Y$ , in place of $\bar{f}$ , also makes (5.2) commute. Let $a \in  A$ , and write $\widehat{f}\left( a\right)$ as $\left( {x, y}\right)$ . Then

$$
{f}_{1}\left( a\right)  = {p}_{1}\left( {\widehat{f}\left( a\right) }\right)  = {p}_{1}\left( {x, y}\right)  = x,
$$

and similarly, ${f}_{2}\left( a\right)  = y$ . Hence $\widehat{f}\left( a\right)  = \left( {{f}_{1}\left( a\right) ,{f}_{2}\left( a\right) }\right)  = \bar{f}\left( a\right)$ for all $a \in  A$ , giving $\widehat{f} = \bar{f}$ , as required.

In general, in any category, the map $\bar{f}$ of diagram (5.2) is usually written as $\left( {{f}_{1},{f}_{2}}\right)$ .

Example 5.1.4 In the category of topological spaces, any two objects $X$ and $Y$ have a product. It is the set $X \times  Y$ equipped with the product topology and the standard projection maps. The product topology is deliberately designed so that a function

$$
A \rightarrow  X \times  Y
$$

$$
t \mapsto  \left( {x\left( t\right) , y\left( t\right) }\right)
$$

is continuous if and only if it is continuous in each coordinate (that is to say, both functions

$$
t \mapsto  x\left( t\right) ,\;t \mapsto  y\left( t\right)
$$

are continuous). This holds for any space $A$ , but the idea is perhaps at its most intuitively appealing when $A = \mathbb{R}$ and we think of $t$ as a time parameter.

A closely related statement is that the product topology is the smallest topology on $X \times  Y$ for which the projections are continuous. Here ’smallest’ means that for any other topology $\mathcal{T}$ on $X \times  Y$ such that ${p}_{1}$ and ${p}_{2}$ are continuous, every subset of $X \times  Y$ open in the product topology is also open in $\mathcal{T}$ . Thus, to define the product topology, we declare just enough sets to be open that the projections are continuous.

Example 5.1.5 Now let $X$ and $Y$ be vector spaces. We can form their direct sum, $X \oplus  Y$ , whose elements can be written as either $\left( {x, y}\right)$ or $x + y$ (with $x \in  X$ and $y \in  Y$ ), according to taste. There are linear projection maps

![117_465_584_618_146_0.jpg](images/117_465_584_618_146_0.jpg)

It can be shown that $X \oplus  Y$ , together with ${p}_{1}$ and ${p}_{2}$ , is the product of $X$ and $Y$ in the category of vector spaces (Exercise 5.1.33).

Examples 5.1.6 (Elements of ordered sets) (a) Let $x, y \in  \mathbb{R}$ . Their minimum $\min \{ x, y\}$ satisfies

$$
\min \{ x, y\}  \leq  x,\;\min \{ x, y\}  \leq  y
$$

and has the further property that whenever $a \in  \mathbb{R}$ with

$$
a \leq  x,\;a \leq  y,
$$

we have $a \leq  \min \{ x, y\}$ . This means exactly that when the poset $\left( {\mathbb{R}, \leq  }\right)$ is viewed as a category, the product of $x, y \in  \mathbb{R}$ is $\min \{ x, y\}$ . The definition of product simplifies when interpreted in a poset, since all diagrams commute.

(b) Fix a set $S$ . Let $X, Y \in  \mathcal{P}\left( S\right)$ . Then $X \cap  Y$ satisfies

$$
X \cap  Y \subseteq  X,\;X \cap  Y \subseteq  Y
$$

and has the further property that whenever $A \in  \mathcal{P}\left( S\right)$ with

$$
A \subseteq  X,\;A \subseteq  Y,
$$

we have $A \subseteq  X \cap  Y$ . This means that $X \cap  Y$ is the product of $X$ and $Y$ in the poset $\left( {\mathcal{P}\left( S\right) , \subseteq  }\right)$ regarded as a category.

(c) Let $x, y \in  \mathbb{N}$ . Their greatest common divisor $\gcd \left( {x, y}\right)$ satisfies

$$
\gcd \left( {x, y}\right) \left| {x,\;\gcd \left( {x, y}\right) }\right| y
$$

(it’s a common divisor!) and has the further property that whenever $a \in  \mathbb{N}$ with

$$
a \mid  x,\;a \mid  y,
$$

we have $a \mid  \gcd \left( {x, y}\right)$ . This means that $\gcd \left( {x, y}\right)$ is the product of $x$ and $y$ in the poset $\left( {\mathbb{N}, \mid  }\right)$ regarded as a category.

Generally, let $\left( {A, \leq  }\right)$ be a poset and $x, y \in  A$ . A lower bound for $x$ and $y$ is an element $a \in  A$ such that $a \leq  x$ and $a \leq  y$ . A greatest lower bound or meet of $x$ and $y$ is a lower bound $z$ for $x$ and $y$ with the further property that whenever $a$ is a lower bound for $x$ and $y$ , we have $a \leq  z$ .

When a poset is regarded as a category, meets are exactly products. They do not always exist, but when they do, they are unique. The meet of $x$ and $y$ is usually written as $x \land  y$ rather than $x \times  y$ . Thus, in the three examples above,

$$
x \land  y = \min \{ x, y\} ,\;X \land  Y = X \cap  Y,\;x \land  y = \gcd \left( {x, y}\right) ,
$$

the second example being the origin of the notation.

We have been discussing products $X \times  Y$ of two objects, so-called binary products. But there is no reason to stick to two. We can just as well talk about products $X \times  Y \times  Z$ of three objects, or of infinitely many objects. The definition changes in the most obvious way:

Definition 5.1.7 Let $\mathcal{A}$ be a category, $I$ a set, and ${\left( {X}_{i}\right) }_{i \in  I}$ a family of objects of $\mathcal{A}$ . A product of ${\left( {X}_{i}\right) }_{i \in  I}$ consists of an object $P$ and a family of maps

$$
{\left( P\overset{{p}_{i}}{ \rightarrow  }{X}_{i}\right) }_{i \in  I}
$$

with the property that for all objects $A$ and families of maps

$$
{\left( A\overset{{f}_{i}}{ \rightarrow  }{X}_{i}\right) }_{i \in  I} \tag{5.3}
$$

there exists a unique map $\bar{f} : A \rightarrow  P$ such that ${p}_{i} \circ  \bar{f} = {f}_{i}$ for all $i \in  I$ .

Remarks 5.1.2 apply equally to this definition. When the product $P$ exists, we write $P$ as $\mathop{\prod }\limits_{{i \in  I}}{X}_{i}$ and the map $\bar{f}$ as ${\left( {f}_{i}\right) }_{i \in  I}$ . We call the maps ${f}_{i}$ the components of the map ${\left( {f}_{i}\right) }_{i \in  I}$ . Taking $I$ to be a two-element set, we recover the special case of binary products.

Example 5.1.8 In ordered sets, the extension from binary to arbitrary products works in the obvious way: given an ordered set $\left( {A, \leq  }\right)$ , a lower bound for a family ${\left( {x}_{i}\right) }_{i \in  I}$ of elements is an element $a \in  A$ such that $a \leq  {x}_{i}$ for all $i$ , and a greatest lower bound or meet of the family is a lower bound greater than any other, written as $\mathop{\bigwedge }\limits_{{i \in  I}}{x}_{i}$ . These are the products in $\left( {A, \leq  }\right)$ .

For example, in $\mathbb{R}$ with its usual ordering, the meet of a family ${\left( {x}_{i}\right) }_{i \in  I}$ is $\inf \left\{  {{x}_{i} \mid  i \in  I}\right\}$ (and one exists if and only if the other does).

Example 5.1.9 What happens to the definition of product when the indexing set $I$ is empty? Let $\mathcal{A}$ be a category. In general, an $I$ -indexed family ${\left( {X}_{i}\right) }_{i \in  I}$ of objects of $\mathcal{A}$ is a function $I \rightarrow  \operatorname{ob}\left( \mathcal{A}\right)$ . When $I$ is empty, there is exactly one such function. In other words, there is exactly one family ${\left( {X}_{i}\right) }_{i \in  \varnothing }$ , the empty family. Similarly, when $I$ is empty, there is exactly one family (5.3) for any given object $A$ .

A product of the empty family therefore consists of an object $P$ of $\mathcal{A}$ such that for each object $A$ of $\mathcal{A}$ , there exists a unique map $\bar{f} : A \rightarrow  P$ . (The condition ’ ${p}_{i} \circ  \bar{f} = {f}_{i}$ for all $i \in  I$ ’ holds trivially.) In other words, a product of the empty family is exactly a terminal object.

We have been writing 1 for terminal objects, which was justified by the fact that in categories such as Set, Top, Ring and Grp, the terminal object has one element. But we have just seen that the terminal object is the product of no things, which in the context of elementary arithmetic is the number 1 . This is a second, related, reason for the notation.

Example 5.1.10 Take an object $X$ of a category $\mathcal{A}$ , and a set $I$ . There is a constant family ${\left( X\right) }_{i \in  I}$ . Its product $\mathop{\prod }\limits_{{i \in  I}}X$ , if it exists, is written as ${X}^{I}$ and called a power of $X$ .

We met powers in Set in Section 3.1. When $X$ is a set, ${X}^{I}$ is the set of functions from $I$ to $X$ , also written as $\operatorname{Set}\left( {I, X}\right)$ .

## Equalizers

To define our second type of limit, we need a preliminary piece of terminology: a fork in a category consists of objects and maps

$$
A\overset{f}{ \rightarrow  }X\overset{s}{ \rightarrow  }Y \tag{5.4}
$$

such that ${sf} = {tf}$ .

Definition 5.1.11 Let $\mathcal{A}$ be a category and let $X\underset{t}{\overset{s}{ \rightarrow  }} \geq  Y$ be objects and maps in $\mathcal{A}$ . An equalizer of $s$ and $t$ is an object $E$ together with a map $E\overset{i}{ \rightarrow  }X$ such that

$$
E\overset{i}{ \rightarrow  }X\overset{s}{ \rightarrow  }Y
$$

is a fork, and with the property that for any fork (5.4), there exists a unique map $\bar{f} : A \rightarrow  E$ such that(5.5)commutes.

![119_700_1653_151_151_0.jpg](images/119_700_1653_151_151_0.jpg)

Remarks 5.1.2 on products apply to equalizers too.

Example 5.1.12 We have already met equalizers in Set (Section 3.1). They really are equalizers in the sense of Definition 5.1.11. Indeed, take sets and functions $X\overset{s}{\underset{t}{ \rightarrow  }}Y$ , write

$$
E = \{ x \in  X \mid  s\left( x\right)  = t\left( x\right) \} ,
$$

and write $i : E \rightarrow  X$ for the inclusion. Then ${si} = {ti}$ , so we have a fork, and one can check that it is universal among all forks on $s$ and $t$ .

An equalizer describes the set of solutions of a single equation, but by combining equalizers with products, we can also describe the solution-set of any system of simultaneous equations. Take a set $\Lambda$ and a family

$$
{\left( X\overset{{s}_{\lambda }}{\underset{{t}_{\lambda }}{ \rightarrow  }}{Y}_{\lambda }\right) }_{\lambda  \in  \Lambda }
$$

of pairs of maps in Set. Then the solution-set

$$
\left\{  {x \in  X \mid  {s}_{\lambda }\left( x\right)  = {t}_{\lambda }\left( x\right) \text{ for all }\lambda  \in  \Lambda }\right\}
$$

is the equalizer of the functions

![120_701_1173_219_146_0.jpg](images/120_701_1173_219_146_0.jpg)

(using the notation introduced after Definition 5.1.7). To see this, observe that for $x \in  X$ ,

$$
{\left( {s}_{\lambda }\right) }_{\lambda  \in  \Lambda }\left( x\right)  = {\left( {t}_{\lambda }\right) }_{\lambda  \in  \Lambda }\left( x\right)  \Leftrightarrow  {\left( {s}_{\lambda }\left( x\right) \right) }_{\lambda  \in  \Lambda } = {\left( {t}_{\lambda }\left( x\right) \right) }_{\lambda  \in  \Lambda }
$$

$$
\Leftrightarrow  {s}_{\lambda }\left( x\right)  = {t}_{\lambda }\left( x\right) \text{ for all }\lambda  \in  \Lambda \text{ , }
$$

as required.

Example 5.1.13 Take continuous maps $X\overset{s}{\underset{t}{ \rightarrow  }}Y$ between topological spaces. We can form their equalizer $E$ in the category of sets, with inclusion map $i : E \rightarrow  X$ , say. Since $E$ is a subset of the space $X$ , it acquires the subspace topology from $X$ , and $i$ is then continuous. This space $E$ , together with $i$ , is the equalizer of $s$ and $t$ .

Showing this amounts to showing that for any fork (5.4) in Top, the induced function $\bar{f}$ is continuous. This follows from the definition of the subspace topology, which is the smallest topology such that the inclusion map is continuous. Compare the remarks on products in Example 5.1.4.

Example 5.1.14 Let $\theta  : G \rightarrow  H$ be a homomorphism of groups. As in Example 0.8, the homomorphism $\theta$ gives rise to a fork

$$
\ker \theta \overset{{\epsilon }^{i}}{ \rightarrow  }G\overset{\theta }{ \rightarrow  }H
$$

where $\iota$ is the inclusion and $\varepsilon$ is the trivial homomorphism. This is an equalizer in Grp. Showing this amounts to showing that the map that we have been calling $\bar{f}$ is a homomorphism, which is left to the reader.

Thus, kernels are a special case of equalizers.

Example 5.1.15 Let $V\underset{t}{ \rightarrow  }W$ be linear maps between vector spaces. There is a linear map $t - s : V \rightarrow  W$ , and the equalizer of $s$ and $t$ in the category of vector spaces is the space $\ker \left( {t - s}\right)$ together with the inclusion map $\ker \left( {t - s}\right)  \hookrightarrow  V$ .

## Pullbacks

We explore one more type of limit before formulating the general definition.

Definition 5.1.16 Let $\mathcal{A}$ be a category, and take objects and maps(5.6)

![121_702_1366_148_152_0.jpg](images/121_702_1366_148_152_0.jpg)

in $\mathcal{A}$ . A pullback of this diagram is an object $P \in  \mathcal{A}$ together with maps ${p}_{1}$ : $P \rightarrow  X$ and ${p}_{2} : P \rightarrow  Y$ such that(5.7)commutes, and with the property that for any commutative square(5.8)

![121_694_1647_164_157_0.jpg](images/121_694_1647_164_157_0.jpg)

![122_732_418_160_161_0.jpg](images/122_732_418_160_161_0.jpg)

in $\mathcal{A}$ , there is a unique map $\bar{f} : A \rightarrow  P$ such that(5.9)

![122_688_656_245_245_0.jpg](images/122_688_656_245_245_0.jpg)

commutes. (For (5.9) to commute means only that ${p}_{1}\bar{f} = {f}_{1}$ and ${p}_{2}\bar{f} = {f}_{2}$ , since the commutativity of the square is already given.)

Again, Remarks 5.1.2 apply.

We call (5.7) a pullback square. Another name for pullback is fibred product. This name is partially explained by the following fact: when $Z$ is a terminal object (and $s$ and $t$ are the only maps they can possibly be), a pullback of the diagram (5.6) is simply a product of $X$ and $Y$ .

Examples 5.1.17 (Pullbacks in Set) The pullback of a diagram (5.6) in Set is

$$
P = \{ \left( {x, y}\right)  \in  X \times  Y \mid  s\left( x\right)  = t\left( y\right) \}
$$

with projections ${p}_{1}$ and ${p}_{2}$ given by ${p}_{1}\left( {x, y}\right)  = x$ and ${p}_{2}\left( {x, y}\right)  = y$ .

Although you might not be familiar with general pullbacks in Set, there are at least two instances that you are likely to have met.

(a) A basic construction with sets and functions is the formation of inverse images. They are an instance of pullbacks. Indeed, given a function $f$ : $X \rightarrow  Y$ and a subset ${Y}^{\prime } \subseteq  Y$ , we obtain a new set, the inverse image

$$
{f}^{-1}{Y}^{\prime } = \left\{  {x \in  X \mid  f\left( x\right)  \in  {Y}^{\prime }}\right\}   \subseteq  X,
$$

and a new function,

$$
\begin{aligned} {f}^{\prime } : \;{f}^{-1}{Y}^{\prime } &  \rightarrow  {Y}^{\prime } \\  x &  \mapsto  f\left( x\right) . \end{aligned}
$$

We also have the inclusion functions $j : {Y}^{\prime } \hookrightarrow  Y$ and $i : {f}^{-1}{Y}^{\prime } \hookrightarrow  X$ . Putting everything together gives a commutative square(5.10)

![123_692_459_215_190_0.jpg](images/123_692_459_215_190_0.jpg)

The data we started with was the lower-right part of this square $\left( {X, Y,{Y}^{\prime }}\right.$ , $f$ and $j$ ), and from it we constructed the rest of the square $\left( {{f}^{-1}{Y}^{\prime },{f}^{\prime }}\right.$ and i).

The square (5.10) is a pullback. Let us verify this in detail. Take any commutative square

![123_711_871_174_181_0.jpg](images/123_711_871_174_181_0.jpg)

We must show that there is a unique map $k : A \rightarrow  {f}^{-1}{Y}^{\prime }$ such that

![123_635_1145_329_291_0.jpg](images/123_635_1145_329_291_0.jpg)

commutes. For uniqueness, let $k$ be a map making the diagram commute. Then for all $a \in  A$ , we have $i\left( {k\left( a\right) }\right)  = g\left( a\right)$ , that is, $k\left( a\right)  = g\left( a\right)$ , and this determines $k$ uniquely. For existence, first note that for all $a \in  A$ we have $f\left( {g\left( a\right) }\right)  = j\left( {h\left( a\right) }\right)  \in  {Y}^{\prime }$ , so $g\left( a\right)  \in  {f}^{-1}{Y}^{\prime }$ . Hence we may define $k$ : $A \rightarrow  {f}^{-1}{Y}^{\prime }$ by $k\left( a\right)  = g\left( a\right)$ for all $a \in  A$ . Then for all $a \in  A$ , we have $i\left( {k\left( a\right) }\right)  = k\left( a\right)  = g\left( a\right)$ and

$$
{f}^{\prime }\left( {k\left( a\right) }\right)  = f\left( {k\left( a\right) }\right)  = f\left( {g\left( a\right) }\right)  = j\left( {h\left( a\right) }\right)  = h\left( a\right) .
$$

Hence $i \circ  k = g$ and ${f}^{\prime } \circ  k = h$ , as required.

(b) Intersection of subsets provides another example of pullbacks. Indeed, let $X$ and $Y$ be subsets of a set $Z$ . Then

![124_735_447_205_156_0.jpg](images/124_735_447_205_156_0.jpg)

is a pullback square, where all the arrows are inclusions of subsets.

In fact, this is a special case of (a), since $X \cap  Y$ is the inverse image of $Y \subseteq  Z$ under the inclusion map $X \hookrightarrow  Z$ .

In the situation of Example 5.1.17(a), where we have a map $f : X \rightarrow  Y$ and a subset ${Y}^{\prime }$ of $Y$ , people sometimes say that ${f}^{-1}{Y}^{\prime }$ is obtained by ’pulling ${Y}^{\prime }$ back’ along $f$ : hence the name.

## The definition of limit

We have now looked at three constructions: products, equalizers and pullbacks. They clearly have something in common. Each starts with some objects and (in the case of equalizers and pullbacks) some maps between them. In each, we aim to construct a new object together with some maps from it to the original objects, with a universal property.

Let us analyse this more closely. What is the starting data in each construction? For (binary) products, it is a pair of objects

$$
{XY} \tag{5.11}
$$

For equalizers, it is a diagram

$$
X\overset{s}{ \rightarrow  }Y \tag{5.12}
$$

For pullbacks, it is a diagram(5.13)

![124_737_1460_152_152_0.jpg](images/124_737_1460_152_152_0.jpg)

In Definition 4.1.25, we met the notion of generalized element, and we saw there that the 'figures' in a geometric object can often be described by maps into it. For instance, a curve in a topological space $A$ can be thought of as a map $\mathbb{R} \rightarrow  A$ . Similarly, an object of a category $\mathcal{A}$ amounts to a functor $D$ : $\mathbf{1} \rightarrow  \mathcal{A}$ ; think of $\mathbf{1} =  -  -$ as an unlabelled object and $D$ as labelling it with the name of an object of $\mathcal{A}$ . And similarly again, a map in a category $\mathcal{A}$ is a functor $2 \rightarrow  \mathcal{A}$ , where $2 =  \bullet   \rightarrow   \bullet$ . (Here2is the category with two objects, say 0 and 1, with one map $0 \rightarrow  1$ , and with no other maps except for identities.) Finally, if we take $\mathbf{I}$ to be one of the categories(5.14)

![125_534_352_478_320_0.jpg](images/125_534_352_478_320_0.jpg)

Figure 5.1 The definition of limit.

![125_372_934_739_160_0.jpg](images/125_372_934_739_160_0.jpg)

then a functor $\mathbf{I} \rightarrow  \mathcal{A}$ consists of data (5.11),(5.12) or (5.13) in $\mathcal{A}$ , respectively.

We have just begun to use the convention that one typeface $\left( {\mathbf{A},\mathbf{B},\mathbf{C},\ldots }\right)$ denotes small categories, and another $\left( {\mathcal{A},\mathcal{B},\mathcal{C},\ldots }\right)$ denotes arbitrary categories. Although not strictly necessary, this convention is helpful, since small categories and arbitrary categories often play different roles in the theory.

Definition 5.1.18 Let $\mathcal{A}$ be a category and $\mathbf{I}$ a small category. A functor $\mathbf{I} \rightarrow  \mathcal{A}$ is called a diagram in $\mathcal{A}$ of shape $\mathbf{I}$ .

So (5.11), (5.12) and (5.13) are diagrams of shape $\mathbf{T},\mathbf{E}$ and $\mathbf{P}$ .

We already have the definitions of product of a diagram of shape $\mathbf{T}$ , equalizer of a diagram of shape $\mathbf{E}$ , and pullback of a diagram of shape $\mathbf{P}$ . We now unify them in the definition of limit (Figure 5.1).

Definition 5.1.19 Let $\mathcal{A}$ be a category, $\mathbf{I}$ a small category, and $D : \mathbf{I} \rightarrow  \mathcal{A}$ a diagram in $\mathcal{A}$ .

(a) A cone on $D$ is an object $A \in  \mathcal{A}$ (the vertex of the cone) together with a family

$$
{\left( A\overset{{f}_{I}}{ \rightarrow  }D\left( I\right) \right) }_{I \in  \mathbf{I}} \tag{5.15}
$$

of maps in $\mathcal{A}$ such that for all maps $I\overset{u}{ \rightarrow  }J$ in $\mathbf{I}$ , the triangle

![126_744_419_180_143_0.jpg](images/126_744_419_180_143_0.jpg)

commutes. (Here and later, we abbreviate $D\left( u\right)$ as ${Du}$ .)

(b) A limit of $D$ is a cone ${\left( L\overset{{p}_{I}}{ \rightarrow  }D\left( I\right) \right) }_{I \in  \mathbf{I}}$ with the property that for any cone (5.15) on $D$ , there exists a unique map $\bar{f} : A \rightarrow  L$ such that ${p}_{I} \circ  \bar{f} = {f}_{I}$ for all $I \in  \mathbf{I}$ . The maps ${p}_{I}$ are called the projections of the limit.

Remarks 5.1.20 (a) Loosely, the universal property says that for any $A \in \; \mathcal{A}$ , maps $A \rightarrow  L$ correspond one-to-one with cones on $D$ with vertex $A$ . (Any map $g : A \rightarrow  L$ gives rise to a cone ${\left( A\overset{{p}_{I}g}{ \rightarrow  }D\left( I\right) \right) }_{I \in  I}$ , and the definition of limit is that for each $A$ , this process is bijective.) In Section 6.1, we will use this thought to rephrase the definition of limit in terms of representability. From this it will follow that limits are unique up to canonical isomorphism, when they exist (Corollary 6.1.2). Alternatively, uniqueness can be proved by the usual kind of direct argument, as in Lemma 2.1.8.

(b) If ${\left( L\overset{{p}_{I}}{ \rightarrow  }D\left( I\right) \right) }_{I \in  \mathbf{I}}$ is a limit of $D$ , we sometimes abuse language slightly by referring to $L$ (rather than the whole cone) as the limit of $D$ . For emphasis, we sometimes call ${\left( L\overset{{p}_{I}}{ \rightarrow  }D\left( I\right) \right) }_{I \in  \mathbf{I}}$ a limit cone. We write $L = \mathop{\lim }\limits_{{ \leftarrow  \mathbf{I}}}D$ . Remark (a) can then be stated as:

A map into $\mathop{\lim }\limits_{{ \leftarrow  \mathbf{I}}}D$ is a cone on $D$ .

(c) By assuming from the outset that the shape category $\mathbf{I}$ is small, we are restricting ourselves to what are officially called small limits. We will seldom be interested in any other kind.

Examples 5.1.21 (Limit shapes) Let $\mathcal{A}$ be any category. Recall the categories $\mathbf{T},\mathbf{E}$ and $\mathbf{P}$ of (5.14).

(a) A diagram $D$ of shape $\mathbf{T}$ in $\mathcal{A}$ is a pair $\left( {X, Y}\right)$ of objects of $\mathcal{A}$ . A cone on $D$ is an object $A$ together with maps ${f}_{1} : A \rightarrow  X$ and ${f}_{2} : A \rightarrow  Y$ (as in Definition 5.1.1), and a limit of $D$ is a product of $X$ and $Y$ .

More generally, let $I$ be a set and write $\mathbf{I}$ for the discrete category on $I$ . A functor $D : \mathbf{I} \rightarrow  \mathcal{A}$ is an $I$ -indexed family ${\left( {X}_{i}\right) }_{i \in  I}$ of objects of $\mathcal{A}$ , and a limit of $D$ is exactly a product of the family ${\left( {X}_{i}\right) }_{i \in  I}$ .

In particular, a limit of the unique functor $\varnothing  \rightarrow  \mathcal{A}$ is a terminal object of $\mathcal{A}$ , where $\varnothing$ denotes the empty category.

(b) A diagram $D$ of shape $\mathbf{E}$ in $\mathcal{A}$ is a parallel pair $X\underset{t}{\overset{s}{ \rightarrow  }}Y$ of maps in $\mathcal{A}$ . A cone on $D$ consists of objects and maps

![127_681_479_236_156_0.jpg](images/127_681_479_236_156_0.jpg)

such that $s \circ  f = g$ and $t \circ  f = g$ . But since $g$ is determined by $f$ , it is equivalent to say that a cone on $D$ consists of an object $A$ and a map $f$ : $A \rightarrow  X$ such that

$$
A\overset{f}{ \rightarrow  }X\overset{\overset{s}{ \rightarrow  }}{\underset{t}{ \rightarrow  }}Y
$$

is a fork. A limit of $D$ is a universal fork on $s$ and $t$ , that is, an equalizer of $s$ and $t$ .

(c) A diagram $D$ of shape $\mathbf{P}$ in $\mathcal{A}$ consists of objects and maps

![127_726_981_146_149_0.jpg](images/127_726_981_146_149_0.jpg)

in $\mathcal{A}$ . Performing a simplification similar to that in (b), we see that a cone on $D$ is a commutative square (5.8). A limit of $D$ is a pullback.

(d) Let $\mathbf{I} = {\left( \mathbb{N}, \leq  \right) }^{\text{ op }}$ . A diagram $D : \mathbf{I} \rightarrow  \mathcal{A}$ consists of objects and maps

$$
\cdots \overset{{s}_{3}}{ \rightarrow  }{X}_{2}\overset{{s}_{2}}{ \rightarrow  }{X}_{1}\overset{{s}_{1}}{ \rightarrow  }{X}_{0}
$$

For example, suppose that we have a set ${X}_{0}$ and a chain of subsets

$$
\cdots  \subseteq  {X}_{2} \subseteq  {X}_{1} \subseteq  {X}_{0}
$$

The inclusion maps form a diagram in Set of the type above, and its limit is $\mathop{\bigcap }\limits_{{i \in  \mathbb{N}}}{X}_{i}$ . In this and similar contexts, limits are sometimes referred to as inverse limits, although many category theorists regard this usage as old-fashioned.

In general, the limit of a diagram $D$ is the terminal object in the category of cones on $D$ , and is therefore an extremal example of a cone on $D$ . The word 'limit' can be understood as meaning 'on the boundary', rather than indicating a limiting process of the type encountered in analysis. Nevertheless, the two ideas make contact in Example 5.1.21(d).

We have said little so far about which limits exist, except to observe in Remark 5.1.2(a) that they do not exist always. We now show that in many familiar categories, all limits do exist; indeed, we can construct them explicitly.

Example 5.1.22 Let $D : \mathbf{I} \rightarrow$ Set and, as a kind of thought experiment, let us ask ourselves what $\mathop{\lim }\limits_{{ \leftarrow  1}}D$ would have to be if it existed. (We do not know yet that it does.) We would have

$$
\mathop{\lim }\limits_{{ \leftarrow  \mathbf{I}}}D \cong  \mathbf{{Set}}\left( {1,\mathop{\lim }\limits_{{ \leftarrow  \mathbf{I}}}D}\right)
$$

$$
\cong  \{ \text{ cones on }D\text{ with vertex 1 }\}
$$

$$
\cong  \left\{  {{\left( {x}_{I}\right) }_{I \in  \mathbf{I}} \mid  {x}_{I} \in  D\left( I\right) }\right. \text{ for all }I \in  \mathbf{I}\text{ and }\left( {Du}\right) \left( {x}_{I}\right)  = {x}_{J}
$$

$$
\text{ for all }\left. {I\overset{u}{ \rightarrow  }J\text{ in }\mathbf{I}}\right\}  \text{ , } \tag{5.16}
$$

where the second isomorphism is by Remark 5.1.20(a) and the third is by definition of cone. In fact,(5.16) really is the limit of $D$ in Set, with projections ${p}_{J} : \mathop{\lim }\limits_{ \leftarrow  }D \rightarrow  D\left( J\right)$ given by ${p}_{J}\left( {\left( {x}_{I}\right) }_{I \in  \mathbf{I}}\right)  = {x}_{J}$ (Exercise 5.1.37). So in Set, all limits exist.

Example 5.1.23 The same formula gives limits in categories of algebras such as Grp, Ring, ${\mathbf{{Vect}}}_{k},\ldots$ . Of course, we also have to say what the group/ring/... structure on the set (5.16) is, but this works in the most straightforward way imaginable. For instance, in ${\mathbf{{Vect}}}_{k}$ , if ${\left( {x}_{I}\right) }_{I \in  \mathbf{I}},{\left( {y}_{I}\right) }_{I \in  \mathbf{I}} \in  \mathop{\lim }\limits_{{ \leftarrow  \mathbf{I}}}D$ then

$$
{\left( {x}_{I}\right) }_{I \in  \mathbf{I}} + {\left( {y}_{I}\right) }_{I \in  \mathbf{I}} = {\left( {x}_{I} + {y}_{I}\right) }_{I \in  \mathbf{I}}.
$$

Example 5.1.24 The same formula also gives limits in Top. The topology on the set (5.16) is the smallest for which the projection maps are continuous.

Definition 5.1.25 (a) Let $\mathbf{I}$ be a small category. A category $\mathcal{A}$ has limits of shape $\mathbf{I}$ if for every diagram $D$ of shape $\mathbf{I}$ in $\mathcal{A}$ , a limit of $D$ exists.

(b) A category has all limits (or properly, has small limits) if it has limits of shape $\mathbf{I}$ for all small categories $\mathbf{I}$ .

Thus, Set, Top, Grp, Ring, Vect ${}_{k},\ldots$ all have all limits.

Similar terminology can be applied to special classes of limits (for instance, 'has pullbacks'). The class of finite limits is particularly important. By definition, a category is finite if it contains only finitely many maps (in which case it also contains only finitely many objects). A finite limit is a limit of shape I for some finite category I. For instance, binary products, terminal objects, equalizers and pullbacks are all finite limits.

The next result tells us that all limits can be built up from limits of just a few familiar, basic types.

Proposition 5.1.26 Let $\mathcal{A}$ be a category.

(a) If $\mathcal{A}$ has all products and equalizers then $\mathcal{A}$ has all limits.

(b) If $\mathcal{A}$ has binary products, a terminal object and equalizers then $\mathcal{A}$ has finite limits.

To understand the idea, consider formula (5.16) for limits in Set. There, the limit of a diagram $D$ is described as the subset of the product $\mathop{\prod }\limits_{{I \in  \mathbf{I}}}D\left( I\right)$ consisting of those elements for which certain equations hold. We saw in Example 5.1.12 that the set of solutions to any system of simultaneous equations can be described via products and equalizers. Thus, we can describe any limit in Set in terms of products and equalizers. And in fact, this same description is valid in any category.

We now examine this idea more closely, in preparation for the proof (Exercise 5.1.38). First-time readers may wish to skip the next two paragraphs, resuming at Example 5.1.27.

Equation (5.16) states that in Set, the limit of a diagram $D : \mathbf{I} \rightarrow$ Set consists of the elements ${\left( {x}_{I}\right) }_{I \in  \mathbf{I}} \in  \mathop{\prod }\limits_{{I \in  \mathbf{I}}}D\left( I\right)$ such that

$$
\left( {Du}\right) \left( {x}_{J}\right)  = {x}_{K}
$$

in $D\left( K\right)$ for each map $J\overset{u}{ \rightarrow  }K$ in $\mathbf{I}$ . For each such map $u$ , define maps

$$
\mathop{\prod }\limits_{{I \in  \mathbf{I}}}D\left( I\right) \xrightarrow[]{{s}_{u}}D\left( I\right)
$$

by

$$
{s}_{u}\left( {\left( {x}_{I}\right) }_{I \in  \mathbf{I}}\right)  = \left( {Du}\right) \left( {x}_{J}\right) ,\;{t}_{u}\left( {\left( {x}_{I}\right) }_{I \in  \mathbf{I}}\right)  = {x}_{K}.
$$

Then $\mathop{\lim }\limits_{ \leftarrow  }D$ is the set of families $x = {\left( {x}_{I}\right) }_{I \in  \mathbf{I}}$ satisfying the equation ${s}_{u}\left( x\right)  = {t}_{u}\left( x\right)$ for each map $u$ in $\mathbf{I}$ . It follows from Example 5.1.12 that $\mathop{\lim }\limits_{ \leftarrow  }D$ is the equalizer of

$$
\mathop{\prod }\limits_{{I \in  \mathbf{I}}}D\left( I\right) \underset{t}{\overset{s}{ \rightarrow  }}\mathop{\sum }\limits_{{J\overset{u}{ \rightarrow  }K\text{ in }\mathbf{I}}}D\left( K\right)
$$

where $s$ and $t$ are the maps with components ${s}_{u}$ and ${t}_{u}$ , respectively.

We have now described any limit in Set in terms of products and equalizers. Although our argument took place entirely in Set, it suggests how we might proceed in an arbitrary category. With this in mind, the proof of Proposition 5.1.26 is routine, and is left as Exercise 5.1.38.

Example 5.1.27 Let CptHff denote the category of compact Hausdorff spaces and continuous maps. It is a classic exercise in topology to show that given continuous maps $s$ and $t$ from a topological space $X$ to a Hausdorff space $Y$ , the subset $\{ x \in  X \mid  s\left( x\right)  = t\left( x\right) \}$ of $X$ is closed. From this it follows that CptHff has equalizers. Also, Tychonoff's theorem states that any product (in Top) of compact spaces is compact, and it is easy to show that any product (in Top) of Hausdorff spaces is Hausdorff. From this it follows that CptHff has all products. Hence by Proposition 5.1.26(a), CptHff has all limits.

Example 5.1.28 Recall from Example 5.1.15 that kernels provide equalizers in ${\mathbf{{Vect}}}_{k}$ . By Proposition 5.1.26(b), finite limits in ${\mathbf{{Vect}}}_{k}$ can always be expressed in terms of $\oplus$ (binary direct sum), $\{ 0\}$ , and kernels. The same is true in Ab.

## Monics

For functions between sets, injectivity is an important concept. For maps in an arbitrary category, injectivity does not make sense, but there is a concept that plays a similar role.

Definition 5.1.29 Let $\mathcal{A}$ be a category. A map $X\overset{f}{ \rightarrow  }Y$ in $\mathcal{A}$ is monic (or a monomorphism) if for all objects $A$ and maps $A\underset{{x}^{\prime }}{\overset{x}{ \rightarrow  }}X$ ,

$$
f \circ  x = f \circ  {x}^{\prime } \Rightarrow  x = {x}^{\prime }.
$$

This can be rephrased suggestively in terms of generalized elements: $f$ is monic if for all generalized elements $x$ and ${x}^{\prime }$ of $X$ (of the same shape), ${fx} = \; f{x}^{\prime } \Rightarrow  x = {x}^{\prime }$ . Being monic is, therefore, the generalized-element analogue of injectivity.

Example 5.1.30 In Set, a map is monic if and only if it is injective. Indeed, if $f$ is injective then certainly $f$ is monic, and for the converse, take $A = 1$ .

Example 5.1.31 In categories of algebras such as Grp, Vect ${}_{k}$ , Ring, etc., it is also true that the monic maps are exactly the injections. Again, it is easy to show that injections are monic. For the converse, take $A = F\left( 1\right)$ where $F$ is the free functor (Examples 2.1.3).

Why is the definition of monic in a chapter on limits? Because of this:

Lemma 5.1.32 A map $X\overset{f}{ \rightarrow  }Y$ is monic if and only if the square

![131_697_425_158_166_0.jpg](images/131_697_425_158_166_0.jpg)

is a pullback.

Proof Exercise 5.1.41.

The significance of this lemma is that whenever we prove a result about limits, a result about monics will follow. For example, we will soon show that the forgetful functors from Grp, ${\mathbf{{Vect}}}_{k}$ , etc., to Set preserve limits (in a sense to be defined), from which it will follow immediately that they also preserve monics. This in turn gives an alternative proof that monics in these categories are injective.

## Exercises

5.1.33 Verify that in the category of vector spaces, the product of two vector spaces is their direct sum (Example 5.1.5).

5.1.34 Take objects and maps $E\overset{i}{ \rightarrow  }X\overset{f}{\underset{g}{ \rightarrow  }}Y$ in some category. If this is an equalizer, is the square

![131_699_1253_152_166_0.jpg](images/131_699_1253_152_166_0.jpg)

necessarily a pullback? What about the converse? Give proofs or counterexamples.

5.1.35 Take a commutative diagram

![131_670_1585_211_121_0.jpg](images/131_670_1585_211_121_0.jpg)

in some category. Suppose that the right-hand square is a pullback. Show that the left-hand square is a pullback if and only if the outer rectangle is a pullback.

5.1.36 Let $D : \mathbf{I} \rightarrow  \mathcal{A}$ be a diagram and ${\left( L\overset{{p}_{I}}{ \rightarrow  }D\left( I\right) \right) }_{I \in  \mathbf{I}}$ a limit cone on $D$ .

(a) Prove that whenever $A\underset{{h}^{\prime }}{\overset{h}{ \rightarrow  }} \lessgtr  L$ are maps such that ${p}_{I} \circ  h = {p}_{I} \circ  {h}^{\prime }$ for all $I \in  \mathbf{I}$ , then $h = {h}^{\prime }$ .

(b) What does the result of (a) mean when $\mathbf{I}$ is the two-object discrete category, $\mathcal{A} =$ Set, and $A = 1$ ? Answer without using any category-theoretic terminology.

5.1.37 Show that the set (5.16) in Example 5.1.22 really is a limit of $D$ .

5.1.38 In this exercise, you will prove Proposition 5.1.26, following the plan described after the statement of that proposition.

(a) Let $\mathcal{A}$ be a category with all products and equalizers. Let $D : \mathbf{I} \rightarrow  \mathcal{A}$ be a diagram in $\mathcal{A}$ . Define maps

$$
\mathop{\prod }\limits_{{I \in  \mathbf{I}}}D\left( I\right) \underset{t}{\overset{s}{ \rightarrow  }}\mathop{\sum }\limits_{{J\overset{u}{ \rightarrow  }K\text{ in }\mathbf{I}}}D\left( K\right)
$$

as follows: given $J\overset{u}{ \rightarrow  }K$ in $\mathbf{I}$ , the $u$ -component of $s$ is the composite

$$
\mathop{\prod }\limits_{{I \in  \mathbf{I}}}D\left( I\right) \overset{{\mathrm{{pr}}}_{J}}{ \rightarrow  }D\left( J\right) \overset{Du}{ \rightarrow  }D\left( K\right)
$$

(where pr denotes a product projection), and the $u$ -component of $t$ is ${\mathrm{{pr}}}_{K}$ . Let $L\overset{p}{ \rightarrow  }\mathop{\prod }\limits_{{I \in  \mathbf{I}}}D\left( I\right)$ be the equalizer of $s$ and $t$ , and write ${p}_{I}$ for the $I$ - component of $p$ . Show that ${\left( L\overset{{p}_{I}}{ \rightarrow  }D\left( I\right) \right) }_{I \in  \mathbf{I}}$ is a limit cone on $D$ , thus proving Proposition 5.1.26(a).

(b) Adapt the argument to prove Proposition 5.1.26(b).

5.1.39 Prove that a category with pullbacks and a terminal object has all finite limits.

5.1.40 Let $\mathcal{A}$ be a category and $A \in  \mathcal{A}$ . A subobject of $A$ is an isomorphism class of monics into $A$ . More precisely, let Monic $\left( A\right)$ be the full subcategory of $\mathcal{A}/A$ whose objects are the monics; then a subobject of $A$ is an isomorphism class of objects of $\operatorname{Monic}\left( A\right)$ .

(a) Let $X\overset{m}{ \rightarrow  }A$ and ${X}^{\prime }\overset{{m}^{\prime }}{ \rightarrow  }A$ be monics in Set. Show that $m$ and ${m}^{\prime }$ are isomorphic in Monic(A) if and only if they have the same image. Deduce that the subobjects of $A$ are in canonical one-to-one correspondence with the subsets of $A$ .

(b) Part (a) says that in Set, subobjects are subsets. What are subobjects in Grp, Ring and Vect ${}_{k}$ ?

(c) What are subobjects in Top? (Careful!)

5.1.41 Prove Lemma 5.1.32.

5.1.42 Let

![133_687_649_177_173_0.jpg](images/133_687_649_177_173_0.jpg)

be a pullback square in some category. Show that if $m$ is monic then so is ${m}^{\prime }$ . (We already know this in the category of sets, by Example 5.1.17(a).)

### 5.2 Colimits: definition and examples

We have seen that examples of limits occur throughout mathematics. It therefore makes sense to examine the dual concept, colimit, and ask whether it is similarly ubiquitous.

By dualizing, we can write down the definition of colimit immediately. We then specialize to sums, coequalizers and pushouts, the duals of products, equalizers and pullbacks.

There are two common conventions for naming dual concepts: sometimes we add or subtract the prefix 'co' (as in limit/colimit), and sometimes we use 'left' and 'right' (as for adjoints). There are also some irregular names, such as terminal/initial object and pullback/pushout.

Definition 5.2.1 Let $\mathcal{A}$ be a category and $\mathbf{I}$ a small category. Let $D : \mathbf{I} \rightarrow  \mathcal{A}$ be a diagram in $\mathcal{A}$ , and write ${D}^{\text{ op }}$ for the corresponding functor ${\mathbf{I}}^{\text{ op }} \rightarrow  {\mathcal{A}}^{\text{ op }}$ . A cocone on $D$ is a cone on ${D}^{\text{ op }}$ , and a colimit of $D$ is a limit of ${D}^{\text{ op }}$ .

Explicitly, a cocone on $D$ is an object $A \in  \mathcal{A}$ (the vertex of the cocone) together with a family

$$
{\left( D\left( I\right) \overset{{f}_{I}}{ \rightarrow  }A\right) }_{I \in  \mathbf{I}} \tag{5.17}
$$

of maps in $\mathcal{A}$ such that for all maps $I\overset{u}{ \rightarrow  }J$ in $\mathbf{I}$ , the diagram

![134_723_432_177_140_0.jpg](images/134_723_432_177_140_0.jpg)

commutes. A colimit of $D$ is a cocone

$$
{\left( D\left( I\right) \overset{{p}_{I}}{ \rightarrow  }C\right) }_{I \in  \mathbf{I}}
$$

with the property that for any cocone (5.17) on $D$ , there is a unique map $\bar{f}$ : $C \rightarrow  A$ such that $\bar{f} \circ  {p}_{I} = {f}_{I}$ for all $I \in  \mathbf{I}$ . The associated picture is the mirror image of Figure 5.1.

Of course, Remarks 5.1.20 apply equally here. We write (the vertex of) the colimit as $\mathop{\lim }\limits_{{ \rightarrow  \mathbf{I}}}D$ , and call the maps ${p}_{I}$ coprojections.

## Sums

Definition 5.2.2 A sum or coproduct is a colimit over a discrete category. (That is, it is a colimit of shape $\mathbf{I}$ for some discrete category I.)

Let ${\left( {X}_{i}\right) }_{i \in  I}$ be a family of objects of a category. Their sum (if it exists) is written as $\mathop{\sum }\limits_{{i \in  I}}{X}_{i}$ or $\mathop{\coprod }\limits_{{i \in  I}}{X}_{i}$ . When $I$ is a finite set $\{ 1,\ldots , n\}$ , we write $\mathop{\sum }\limits_{{i \in  I}}{X}_{i}$ as ${X}_{1} + \; \cdots  + {X}_{n}$ , or as 0 if $n = 0$ .

Example 5.2.3 By the dual of Example 5.1.9, a sum of the empty family is exactly an initial object.

Example 5.2.4 Sums in Set were described in Section 3.1. Let us look in detail at the universal property, in the case of binary sums. Take two sets, ${X}_{1}$ and ${X}_{2}$ . Form their sum, ${X}_{1} + {X}_{2}$ , and consider the inclusions

$$
{X}_{1}\overset{{p}_{1}}{ \rightarrow  }{X}_{1} + {X}_{2} < \overset{{p}_{2}}{ < }{X}_{2}.
$$

This is a colimit cocone. To prove this, we have to prove the following universal property: for any diagram

$$
{X}_{1}\xrightarrow[]{{f}_{1}}A < \xrightarrow[]{{f}_{2}}{X}_{2}
$$

of sets and functions, there is a unique function $\bar{f} : {X}_{1} + {X}_{2} \rightarrow  A$ making

![135_590_424_368_252_0.jpg](images/135_590_424_368_252_0.jpg)

commute. Now, we noted in Section 3.1 that ${p}_{1}$ and ${p}_{2}$ are injections whose images partition ${X}_{1} + {X}_{2}$ . This means that every element $x$ of ${X}_{1} + {X}_{2}$ is either equal to ${p}_{1}\left( {x}_{1}\right)$ for some ${x}_{1} \in  {X}_{1}$ (and this ${x}_{1}$ is then unique), or equal to ${p}_{2}\left( {x}_{2}\right)$ for some ${x}_{2} \in  {X}_{2}$ (and this ${x}_{2}$ is then unique), but not both. So we may define $\bar{f}\left( x\right)$ to be equal to ${f}_{1}\left( {x}_{1}\right)$ in the first case and ${f}_{2}\left( {x}_{2}\right)$ in the second. This defines a function $\bar{f}$ making the diagram commute, and it is clearly the unique function that does so.

Example 5.2.5 Let ${X}_{1}$ and ${X}_{2}$ be vector spaces. There are linear maps

$$
{X}_{1}\overset{{i}_{1}}{ \rightarrow  }{X}_{1} \oplus  {X}_{2} \leftarrow  {}^{{i}_{2}}{X}_{2} \tag{5.18}
$$

defined by ${i}_{1}\left( {x}_{1}\right)  = \left( {{x}_{1},0}\right)$ and ${i}_{2}\left( {x}_{2}\right)  = \left( {0,{x}_{2}}\right)$ , and it can be checked that (5.18) is a colimit cocone in ${\mathbf{{Vect}}}_{k}$ . Hence binary direct sums are sums in the categorical sense. This is remarkable, since we saw in Example 5.1.5 that ${X}_{1} \oplus  {X}_{2}$ is also the product of ${X}_{1}$ and ${X}_{2}$ ! Contrast this with the category of sets (or almost any other category), where sums and products are very different.

Example 5.2.6 Let $\left( {A, \leq  }\right)$ be an ordered set. Upper bounds and least upper bounds (or joins) in $A$ are defined by dualizing the definitions in Example 5.1.6, and, dually, they are sums in the corresponding category. The join of a family ${\left( {x}_{i}\right) }_{i \in  I}$ is written as $\mathop{\bigvee }\limits_{{i \in  I}}{x}_{i}$ . In the binary case (where $I$ has two elements), the join of ${x}_{1}$ and ${x}_{2}$ is written as ${x}_{1} \vee  {x}_{2}$ . A join of the empty family (where $I = \varnothing$ ) is an initial object of the category $A$ , as in Example 5.2.3. Equivalently, it is a least element of $A$ : an element $0 \in  A$ such that $0 \leq  a$ for all $a \in  A$ .

For instance, in $\left( {\mathbb{R}, \leq  }\right)$ , join is supremum and there is no least element. In a power set $\left( {\mathcal{P}\left( S\right) , \subseteq  }\right)$ , join is union and the least element is $\varnothing$ . In $\left( {\mathbb{N}, \mid  }\right)$ , join is lowest common multiple and the least element is 1 (since 1 divides everything). So in this order on the natural numbers, 1 is least; but also, everything divides 0 , so 0 is greatest!

## Coequalizers

We continue to write $\mathbf{E}$ for the category $\bullet   \rightrightarrows   \bullet$ .

Definition 5.2.7 A coequalizer is a colimit of shape $\mathbf{E}$ .

In other words, given a diagram $X\xrightarrow[t]{s}Y$ , a coequalizer of $s$ and $t$ is a map $Y\overset{p}{ \rightarrow  }C$ satisfying $p \circ  s = p \circ  t$ and universal with this property.

We will see that coequalizers are something like quotients. But first, we need some background material on equivalence relations.

Remarks 5.2.8 A binary relation $R$ on a set $A$ can be viewed as a subset $R \subseteq  A \times  A$ . Think of $\left( {a,{a}^{\prime }}\right)  \in  R$ as meaning ’ $a$ and ${a}^{\prime }$ are related’. We can speak of one relation $S$ on $A$ ’containing’ another such relation, $R$ . This means that $R \subseteq  S$ : whenever $a$ and ${a}^{\prime }$ are $R$ -related, they are also $S$ -related.

We will need to use the fact that for any binary relation $R$ on a set $A$ , there is a smallest equivalence relation $\sim$ containing $R$ . This is called the equivalence relation generated by $R$ . ’Smallest’ means that any equivalence relation containing $R$ also contains $\sim$ .

We can construct $\sim$ as the intersection of all equivalence relations on $A$ containing $R$ , since the intersection of any family of equivalence relations is again an equivalence relation. There is also an explicit construction. The rough idea is as follows: writing $x \rightarrow  y$ to mean $\left( {x, y}\right)  \in  R$ , we should have $a \sim  {a}^{\prime }$ if and only if there is a zigzag such as

$$
a \rightarrow  b \leftarrow  c \leftarrow  d \rightarrow  e \leftarrow  {a}^{\prime }
$$

between $a$ and ${a}^{\prime }$ . To make this precise, we first define a relation $S$ on $A$ by

$$
S = \left\{  {\left( {a,{a}^{\prime }}\right)  \in  A \times  A \mid  \left( {a,{a}^{\prime }}\right)  \in  R\text{ or }\left( {{a}^{\prime }, a}\right)  \in  R}\right\}
$$

(which enlarges $R$ to a symmetric relation), then define $\sim$ by declaring that $a \sim  {a}^{\prime }$ if and only if there exist $n \geq  0$ and ${a}_{0},\ldots ,{a}_{n} \in  A$ such that

$$
a = {a}_{0},\left( {{a}_{0},{a}_{1}}\right)  \in  S,\left( {{a}_{1},{a}_{2}}\right)  \in  S,\ldots ,\left( {{a}_{n - 1},{a}_{n}}\right)  \in  S,{a}_{n} = {a}^{\prime }
$$

(which forces reflexivity and transitivity, while preserving the symmetry).

Next, recall some facts about equivalence relations from Section 3.1. Given any equivalence relation $\sim$ on a set $A$ , we can construct the set $A/ \sim$ of equivalence classes and the quotient map $p : A \rightarrow  A/ \sim$ . This quotient map $p$ is surjective and has the property that $p\left( a\right)  = p\left( {a}^{\prime }\right)  \Leftrightarrow  a \sim  {a}^{\prime }$ , for $a,{a}^{\prime } \in  A$ . We saw that for any set $B$ , the maps $A/ \sim   \rightarrow  B$ correspond one-to-one (via composition with $p$ ) with the maps $f : A \rightarrow  B$ such that

$$
\forall a,{a}^{\prime } \in  A,\;a \sim  {a}^{\prime } \Rightarrow  f\left( a\right)  = f\left( {a}^{\prime }\right) . \tag{5.19}
$$

Finally, let us consider this universal property in the case where $\sim$ is the equivalence relation generated by some relation $R$ . Condition (5.19) is then equivalent to:

$$
\forall a,{a}^{\prime } \in  A,\;\left( {a,{a}^{\prime }}\right)  \in  R \Rightarrow  f\left( a\right)  = f\left( {a}^{\prime }\right) . \tag{5.20}
$$

(Proof: define an equivalence relation $\approx$ on $A$ by $a \approx  {a}^{\prime } \Leftrightarrow  f\left( a\right)  = f\left( {a}^{\prime }\right)$ . Condition (5.19) says that $\sim   \subseteq   \approx$ , and condition (5.20) that $R \subseteq   \approx$ . But $\sim$ is the smallest equivalence relation containing $R$ , so these statements are equivalent.) In conclusion, for any set $B$ , the maps $A/ \sim   \rightarrow  B$ correspond one-to-one with the maps $f : A \rightarrow  B$ satisfying (5.20).

Example 5.2.9 Take sets and functions $X\overset{s}{\underset{t}{ \rightarrow  }}Y$ . To find the coequalizer of $s$ and $t$ , we must construct in some canonical way a set $C$ and a function $p$ : $Y \rightarrow  C$ such that $p\left( {s\left( x\right) }\right)  = p\left( {t\left( x\right) }\right)$ for all $x \in  X$ . So, let $\sim$ be the equivalence relation on $Y$ generated by $s\left( x\right)  \sim  t\left( x\right)$ for all $x \in  X$ . (In other words, $\sim$ is generated by the relation

$$
R = \{ \left( {s\left( x\right) , t\left( x\right) }\right)  \mid  x \in  X\}
$$

on $Y$ .) Take the quotient map $p : Y \rightarrow  Y/ \sim$ . By the correspondence described in Remarks 5.2.8, this is indeed the coequalizer of $s$ and $t$ .

Example 5.2.10 For each pair of homomorphisms $A\xrightarrow[t]{s}B$ in $\mathbf{{Ab}}$ , there is a homomorphism $t - s : A \rightarrow  B$ , which gives rise to a subgroup $\operatorname{im}\left( {t - s}\right)$ of $B$ . The coequalizer of $s$ and $t$ is the canonical homomorphism $B \rightarrow  B/\mathrm{{im}}\left( {t - s}\right)$ . (Compare Example 5.1.15.)

Pushouts

Definition 5.2.11 A pushout is a colimit of shape

![137_637_1435_276_166_0.jpg](images/137_637_1435_276_166_0.jpg)

In other words, the pushout of a diagram(5.21)is (if it exists) a commutative square

![137_702_1661_144_146_0.jpg](images/137_702_1661_144_146_0.jpg)

![138_742_415_142_143_0.jpg](images/138_742_415_142_143_0.jpg)

that is universal as such. In other words still, a pushout in a category $\mathcal{A}$ is a pullback in ${\mathcal{A}}^{\mathrm{{op}}}$ .

Example 5.2.12 Take a diagram (5.21) in Set. Its pushout $P$ is $\left( {Y + Z}\right) / \sim$ , where $\sim$ is the equivalence relation on $Y + Z$ generated by $s\left( x\right)  \sim  t\left( x\right)$ for all $x \in  X$ . The coprojection $Y \rightarrow  P$ sends $y \in  Y$ to its equivalence class in $P$ , and similarly for the coprojection $Z \rightarrow  P$ .

For example, let $Y$ and $Z$ be subsets of some set $A$ . Then

![138_690_862_242_154_0.jpg](images/138_690_862_242_154_0.jpg)

is a pushout square in Set. (It is also a pullback square! This coincidence is a special property of the category of sets.) You can check this by verifying the universal property or by using the formula just stated. In this case, the formula takes the two sets $Y$ and $Z$ , places them side by side (giving $Y + Z$ ), then glues the subset $Y \cap  Z$ of $Y$ to the subset $Y \cap  Z$ of $Z$ (giving $\left( {Y + Z}\right) / \sim   = Y \cup  Z$ ).

Example 5.2.13 If $\mathcal{A}$ is a category with an initial object 0, and if $Y, Z \in  \mathcal{A}$ , then a pushout of the unique diagram

![138_742_1319_135_142_0.jpg](images/138_742_1319_135_142_0.jpg)

is exactly a sum of $Y$ and $Z$ .

Example 5.2.14 The van Kampen theorem (Example 0.9) says that given a pushout square in Top satisfying certain further hypotheses, the square in Grp obtained by taking fundamental groups throughout is also a pushout.

Here is one more shape of colimit, dual to that in Example 5.1.21(d).

Example 5.2.15 A diagram $D : \left( {\mathbb{N}, \leq  }\right)  \rightarrow  \mathcal{A}$ consists of objects and maps

$$
{X}_{0}\overset{{s}_{1}}{ \rightarrow  }{X}_{1}\overset{{s}_{2}}{ \rightarrow  }{X}_{2}\overset{{s}_{3}}{ \rightarrow  }\cdots
$$

![139_409_352_733_401_0.jpg](images/139_409_352_733_401_0.jpg)

Figure 5.2 Sphere as (a) a limit, and (b) a colimit.

in $\mathcal{A}$ . Colimits of such diagrams are traditionally called direct limits. Although the old terms 'inverse limit' (Example 5.1.21(d)) and 'direct limit' are made redundant by the general categorical terms 'limit' and 'colimit' respectively, it is worth being aware of them.

With all these examples in mind, we now write down a general formula for colimits in Set.

Example 5.2.16 The colimit of a diagram $D : \mathbf{I} \rightarrow$ Set is given by

$$
\mathop{\lim }\limits_{{ \rightarrow  \mathbf{I}}}D = \left( {\mathop{\sum }\limits_{{I \in  \mathbf{I}}}D\left( I\right) }\right) / \sim
$$

where $\sim$ is the equivalence relation on $\sum D\left( I\right)$ generated by

$$
x \sim  \left( {Du}\right) \left( x\right)
$$

for all $I\overset{u}{ \rightarrow  }J$ in $\mathbf{I}$ and $x \in  D\left( I\right)$ . To see this, note that for any set $A$ , the maps

$$
\left( {\sum D\left( I\right) }\right) / \sim   \rightarrow  A
$$

correspond bijectively with the maps $f : \sum D\left( I\right)  \rightarrow  A$ such that

$$
f\left( x\right)  = f\left( {\left( {Du}\right) \left( x\right) }\right)
$$

for all $u$ and $x$ (by Remarks 5.2.8). These in turn correspond to families of maps ${\left( D\left( I\right) \overset{{f}_{I}}{ \rightarrow  }A\right) }_{I \in  \mathbf{I}}$ such that ${f}_{I}\left( x\right)  = {f}_{J}\left( {\left( {Du}\right) \left( x\right) }\right)$ for all $u$ and $x$ ; but these are exactly the cocones on $D$ with vertex $A$ .

There is a kind of duality between the formulas for limits in Set (Example 5.1.22) and colimits in Set. Whereas the limit is constructed as a subset of a product, the colimit is a quotient of a sum.

Figure 5.2 is intended to convey the difference in flavour between limits and colimits, in a particular topological context. In elementary texts, surfaces are almost always seen as subsets of Euclidean space ${\mathbb{R}}^{3}$ , with the sphere ${S}^{2}$ typically defined as

$$
\left\{  {\left( {x, y, z}\right)  \in  {\mathbb{R}}^{3} \mid  {x}^{2} + {y}^{2} + {z}^{2} = 1}\right\}  .
$$

This is a subspace of the product space ${\mathbb{R}}^{3} = \mathbb{R} \times  \mathbb{R} \times  \mathbb{R}$ , which suggests that it is a limit. Indeed, the sphere is the equalizer

$$
{S}^{2} <  \rightarrow  {\mathbb{R}}^{3}\underset{t}{ \Rightarrow  }\mathbb{R}
$$

where the maps $s, t : {\mathbb{R}}^{3} \rightarrow  \mathbb{R}$ are given by

$$
s\left( {x, y, z}\right)  = {x}^{2} + {y}^{2} + {z}^{2},\;t\left( {x, y, z}\right)  = 1.
$$

(An equation is captured by an equalizer.)

In more advanced mathematics, however, this point of view is used less often. A surface can instead be thought of as the gluing-together of lots of little patches, each isomorphic to the open unit disk $D$ . For example, we could in principle construct an entire bicycle inner tube by gluing together a large number of puncture-repair patches. Figure 5.2(b) shows the simpler example of a sphere made up of two disks glued together. This realizes the sphere as a quotient (gluing) of the sum (disjoint union) of the two copies of $D$ , suggesting that we have constructed the sphere as a colimit. Indeed, the sphere is the coequalizer

$$
{S}^{1} \times  \left( {0,1}\right)  \Leftrightarrow  D + D \rightarrow  {S}^{2}
$$

where ${S}^{1}$ is the circle, the cylinder ${S}^{1} \times  \left( {0,1}\right)$ is the intersection of the two copies of $D$ (the central belt of Figure 5.2(b)), and the two maps into $D + D$ are the inclusions of the cylinder into the first and second copies of $D$ .

One disadvantage of the limit point of view is that it makes an arbitrary choice of coordinate system. It is generally best to think of spaces as freestanding objects, existing independently of any particular embedding into Euclidean space.

One disadvantage of the colimit point of view is that it makes an arbitrary choice of decomposition. For example, we could decompose the sphere into three patches rather than two, or use a different two patches from those shown.

The colimit point of view has the upper hand in modern geometry. (If you are familiar with the definition of manifold, you will recognize that an atlas is essentially a way of viewing a manifold as a colimit of Euclidean balls.) One reason for this is that we are often concerned with maps out of spaces $X$ , such as maps $X \rightarrow  \mathbb{R}$ . Maps out of a colimit are easy; it is in the very definition of colimit that we know what the maps out of it are.

## Epics

Definition 5.2.17 Let $\mathcal{A}$ be a category. A map $X\overset{f}{ \rightarrow  }Y$ in $\mathcal{A}$ is epic (or an epimorphism) if for all objects $Z$ and maps $Y\underset{{g}^{\prime }}{ \rightarrow  }Z$ ,

$$
g \circ  f = {g}^{\prime } \circ  f \Rightarrow  g = {g}^{\prime }.
$$

This is the formal dual of the definition of monic. (In other words, an epic in $\mathcal{A}$ is a monic in ${\mathcal{A}}^{\mathrm{{op}}}$ .) It is in some sense the categorical version of surjec-tivity. But whereas the definition of monic closely resembles the definition of injective, the definition of epic does not look much like the definition of surjective. The following examples confirm that in categories where surjectivity makes sense, it is only sometimes equivalent to being epic.

Example 5.2.18 In Set, a map is epic if and only if it is surjective. If $f$ is surjective then certainly $f$ is epic. To see the converse, take $Z$ to be a two-element set \{true, false\}, take $g$ to be the characteristic function of the image of $f$ (as defined in Section 3.1), and take ${g}^{\prime }$ to be the function with constant value true.

Any isomorphism in any category is both monic and epic. In Set, the converse also holds, since any injective surjective function is invertible (Example 1.1.5).

Example 5.2.19 In categories of algebras, any surjective map is certainly epic. In some such categories, including $\mathbf{{Ab}},{\mathbf{{Vect}}}_{k}$ and $\mathbf{{Grp}}$ , the converse also holds. (The proof is straightforward for $\mathbf{{Ab}}$ and ${\mathbf{{Vect}}}_{k}$ , but much harder for Grp.) However, there are other categories of algebras where it fails. For instance, in Ring, the inclusion $\mathbb{Z} \hookrightarrow  \mathbb{Q}$ is epic but not surjective (Exercise 5.2.23). This is also an example of a map that is monic and epic but not an isomorphism.

Example 5.2.20 In the category of Hausdorff topological spaces and continuous maps, any map with dense image is epic.

Of course, there is a dual of Lemma 5.1.32, saying that a map is epic if and only if a certain square is a pushout.

## Exercises

5.2.21 Let $X\xrightarrow[t]{s}Y$ be maps in some category. Prove that $s = t$ if and only if the equalizer of $s$ and $t$ exists and is an isomorphism, if and only if the coequalizer of $s$ and $t$ exists and is an isomorphism.

5.2.22 (a) Let $X$ be a set and $f : X \rightarrow  X$ a map. Describe the coequalizer of $X\overset{f}{\underset{1}{ \rightarrow  }} \geq  X$ in Set as explicitly as possible.

(b) Do the same in Top rather than Set. When $X$ is the circle ${S}^{1}$ , find an $f$ such that the coequalizer is an uncountable space with the indiscrete topology.

5.2.23 (a) Prove that in the category of monoids, the inclusion $\left( {\mathbb{N},+,0}\right)  \hookrightarrow \; \left( {\mathbb{Z},+,0}\right)$ is epic, even though it is not surjective.

(b) Prove that in the category of rings, the inclusion $\mathbb{Z} \hookrightarrow  \mathbb{Q}$ is epic, even though it is not surjective.

5.2.24 (Compare Exercise 5.1.40.) Let $\mathcal{A}$ be a category and $A \in  \mathcal{A}$ . Define a quotient object of $A$ to be an isomorphism class of epics out of $A$ . That is, let $\operatorname{Epic}\left( A\right)$ be the full subcategory of $A/\mathcal{A}$ whose objects are the epics; then a quotient object of $A$ is an isomorphism class of objects of $\operatorname{Epic}\left( A\right)$ .

(a) Let $A\overset{e}{ \rightarrow  }X$ and $A\overset{{e}^{\prime }}{ \rightarrow  }{X}^{\prime }$ be epics in Set. Show that $e$ and ${e}^{\prime }$ are isomorphic in Epic(A) if and only if they induce the same equivalence relation on $A$ . Deduce that the quotient objects of $A$ are in canonical one-to-one correspondence with the equivalence relations on $A$ .

(b) Assuming the (nontrivial) fact that the epics in Grp are the surjections, show that the quotient objects of a group correspond one-to-one with its normal subgroups.

(The name 'quotient object' is not standard, and indeed there is no standard name for it. Arguably, 'quotient object' would be more suitable for an isomorphism class of regular epics, as defined in the following exercises.)

5.2.25 A map $m : A \rightarrow  B$ is regular monic if there exist an object $C$ and maps $B \rightrightarrows  C$ of which $m$ is an equalizer. A map $m : A \rightarrow  B$ is split monic if there exists a map $e : B \rightarrow  A$ such that ${em} = {1}_{A}$ .

(a) Show that split monic $\Rightarrow$ regular monic $\Rightarrow$ monic.

(b) In Ab, show that all monics are regular but not all monics are split. (Hint for the first part: equalizers in Ab are calculated as in Example 5.1.15.)

(c) In Top, describe the regular monics, and find a monic that is not regular.

5.2.26 Dualizing the definitions in Exercise 5.2.25 gives definitions of regular and split epic.

(a) We saw in Example 5.2.19 that a map may be monic and epic but not an isomorphism. Prove that in any category, a map is an isomorphism if and only if it is both monic and regular epic.

(b) Using the assumption that our category of sets satisfies the axiom of choice (Section 3.1), show that

$$
\text{ epic } \Leftrightarrow  \text{ regular epic } \Leftrightarrow  \text{ split epic }
$$

in Set.

(c) Let us say that a category $\mathcal{A}$ satisfies the axiom of choice if all epics in $\mathcal{A}$ are split. Prove that neither Top nor Grp satisfies the axiom of choice.

5.2.27 The result of Exercise 5.1.42 can be phrased as 'the class of monics is stable under pullback'. It is also a fact that the composite of two monics is always monic; we say that the class of monics is 'closed under composition'.

Consider the following six classes of map:

monics, regular monics, split monics, epics, regular epics, split epics.

Determine whether each class is stable under pullback or closed under composition.

### 5.3 Interactions between functors and limits

We saw in Example 5.1.23 that limits in categories such as Grp, Ring and ${\mathbf{{Vect}}}_{k}$ can be computed by first taking the limit in the category of sets, then equipping the result with a suitable algebraic structure. On the other hand, col-imits in these categories are unlike colimits in Set. For example, the underlying set of the initial object of Grp (which has one element) is not the initial object of Set (which has no elements), and the underlying set of the direct sum $X \oplus  Y$ of two vector spaces is not the sum of the underlying sets of $X$ and $Y$ . So, these forgetful functors interact well with limits and badly with colimits.

In this section, we develop terminology that will enable us to express these thoughts precisely.

Definition 5.3.1 (a) Let $\mathbf{I}$ be a small category. A functor $F : \mathcal{A} \rightarrow  \mathcal{B}$ preserves limits of shape $\mathbf{I}$ if for all diagrams $D : \mathbf{I} \rightarrow  \mathcal{A}$ and all cones ${\left( A\overset{{p}_{I}}{ \rightarrow  }D\left( I\right) \right) }_{I \in  \mathbf{I}}$ on $D,$

$$
{\left( A\overset{{p}_{I}}{ \rightarrow  }D\left( I\right) \right) }_{I \in  \mathbf{I}}\text{ is a limit cone on }D\text{ in }\mathcal{A}
$$

$$
\Rightarrow  {\left( F\left( A\right) \overset{F{p}_{I}}{ \rightarrow  }FD\left( I\right) \right) }_{I \in  \mathbf{I}}\text{ is a limit cone on }F \circ  D\text{ in }\mathcal{B}\text{ . }
$$

(b) A functor $F : \mathcal{A} \rightarrow  \mathcal{B}$ preserves limits if it preserves limits of shape $\mathbf{I}$ for all small categories $\mathbf{I}$ .

(c) Reflection of limits is defined as in (a), but with $\Leftarrow$ in place of $\Rightarrow$ .

Of course, the same terminology applies to colimits.

Here is a different way to state the definition of preservation. A functor $F$ : $\mathcal{A} \rightarrow  \mathcal{B}$ preserves limits if and only if it has the following property: whenever $D : \mathbf{I} \rightarrow  \mathcal{A}$ is a diagram that has a limit, the composite $F \circ  D : \mathbf{I} \rightarrow  \mathcal{B}$ also has a limit, and the canonical map

$$
F\left( {\mathop{\lim }\limits_{{ \leftarrow  \mathbf{I}}}D}\right)  \rightarrow  \mathop{\lim }\limits_{{ \leftarrow  \mathbf{I}}}\left( {F \circ  D}\right)
$$

is an isomorphism. Here the ’canonical map’ has $I$ -component

$$
F\left( {\mathop{\lim }\limits_{{ \leftarrow  \mathbf{I}}}D}\right) \overset{F\left( {p}_{I}\right) }{ \rightarrow  }F\left( {D\left( I\right) }\right) ,
$$

where ${p}_{I}$ is the $I$ th projection of the limit cone on $D$ .

In particular, if $F$ preserves limits then

$$
F\left( {\mathop{\lim }\limits_{{ \leftarrow  \mathbf{I}}}D}\right)  \cong  \mathop{\lim }\limits_{{ \leftarrow  \mathbf{I}}}\left( {F \circ  D}\right) \tag{5.22}
$$

whenever $D$ is a diagram with a limit. Preservation of limits says more than (5.22) does: the left- and right-hand sides are required to be not just isomorphic, but isomorphic in a particular way. Nevertheless, we will sometimes omit this check, acting as if preservation means only that (5.22) holds.

Example 5.3.2 The forgetful functor $U :$ Top $\rightarrow$ Set preserves both limits and colimits. (As we will see, this follows from the fact that $U$ has adjoints on both sides.) It does not reflect all limits or all colimits. For instance, choose any non-discrete spaces $X$ and $Y$ , and let $Z$ be the set $U\left( X\right)  \times  U\left( Y\right)$ equipped with the discrete topology. (All that matters here is that the topology on $Z$ is strictly larger than the product topology.) Then we have a cone

$$
X \leftarrow  Z \rightarrow  Y \tag{5.23}
$$

in Top whose image in Set is the product cone

$$
U\left( X\right)  \leftarrow  U\left( X\right)  \times  U\left( Y\right)  \rightarrow  U\left( Y\right) .
$$

But (5.23) is not a product cone in Top, since the discrete topology on $U\left( X\right)  \times \; U\left( Y\right)$ is not the product topology.

Example 5.3.3 In the first paragraph of this section, we observed that the forgetful functor Grp $\rightarrow$ Set does not preserve initial objects and that the forgetful functor ${\mathbf{{Vect}}}_{k} \rightarrow$ Set does not preserve binary sums. Forgetful functors out of categories of algebras very seldom preserve all colimits.

Example 5.3.4 We also saw that (in the examples mentioned) forgetful functors on categories of algebras do preserve limits. In fact, something stronger is true. Let us examine the case of binary products in Grp, although all of the following can be said for any limits in any of the categories Grp, Ab, Vect ${}_{k}$ , Ring, etc.

Take groups ${X}_{1}$ and ${X}_{2}$ . We can form the product set $U\left( {X}_{1}\right)  \times  U\left( {X}_{2}\right)$ , which comes equipped with projections

$$
U\left( {X}_{1}\right) \overset{{p}_{1}}{ \leftarrow  }U\left( {X}_{1}\right)  \times  U\left( {X}_{2}\right) \overset{{p}_{2}}{ \rightarrow  }U\left( {X}_{2}\right) .
$$

I claim that there is exactly one group structure on the set $U\left( {X}_{1}\right)  \times  U\left( {X}_{2}\right)$ with the property that ${p}_{1}$ and ${p}_{2}$ are homomorphisms. To prove uniqueness, suppose that we have a group structure on $U\left( {X}_{1}\right)  \times  U\left( {X}_{2}\right)$ with this property. Take elements $\left( {{x}_{1},{x}_{2}}\right)$ and $\left( {{x}_{1}^{\prime },{x}_{2}^{\prime }}\right)$ of $U\left( {X}_{1}\right)  \times  U\left( {X}_{2}\right)$ and write $\left( {{x}_{1},{x}_{2}}\right)  \cdot  \left( {{x}_{1}^{\prime },{x}_{2}^{\prime }}\right)  = \; \left( {{y}_{1},{y}_{2}}\right)$ . Since ${p}_{1}$ is a homomorphism,

$$
{y}_{1} = {p}_{1}\left( {{y}_{1},{y}_{2}}\right)  = {p}_{1}\left( {\left( {{x}_{1},{x}_{2}}\right)  \cdot  \left( {{x}_{1}^{\prime },{x}_{2}^{\prime }}\right) }\right)  = {p}_{1}\left( {{x}_{1},{x}_{2}}\right)  \cdot  {p}_{1}\left( {{x}_{1}^{\prime },{x}_{2}^{\prime }}\right)  = {x}_{1} \cdot  {x}_{1}^{\prime },
$$

and similarly ${y}_{2} = {x}_{2} \cdot  {x}_{2}^{\prime }$ . Hence

$$
\left( {{x}_{1},{x}_{2}}\right)  \cdot  \left( {{x}_{1}^{\prime },{x}_{2}^{\prime }}\right)  = \left( {{x}_{1}{x}_{1}^{\prime },{x}_{2}{x}_{2}^{\prime }}\right) .
$$

A similar argument shows that ${\left( {x}_{1},{x}_{2}\right) }^{-1} = \left( {{x}_{1}^{-1},{x}_{2}^{-1}}\right)$ and that the identity element 1 of the group is $\left( {1,1}\right)$ . Now, for existence, define $\cdot  ,{\left( \right) }^{-1}$ and 1 by the formulas just given; it can then be checked that the group axioms are satisfied and that ${p}_{1}$ and ${p}_{2}$ are group homomorphisms. This proves the claim.

Write $L$ for the set $U\left( {X}_{1}\right)  \times  U\left( {X}_{2}\right)$ equipped with this group structure. Then we have a cone

$$
{X}_{1}\overset{{p}_{1}}{ \leftarrow  }L\overset{{p}_{2}}{ \rightarrow  }{X}_{2}
$$

in Grp. It is easy to check that this is, in fact, a product cone in Grp.

We can summarize this in language that is not tied to group theory. Given objects ${X}_{1}$ and ${X}_{2}$ of Grp,

![146_636_356_347_365_0.jpg](images/146_636_356_347_365_0.jpg)

Figure 5.3 Creation of limits.

- for any product cone on $\left( {U\left( {X}_{1}\right) , U\left( {X}_{2}\right) }\right)$ in Set, there is a unique cone on $\left( {{X}_{1},{X}_{2}}\right)$ in Grp whose image under $U$ is the cone we started with;

- this cone on $\left( {{X}_{1},{X}_{2}}\right)$ is a product cone.

This suggests the following definition (Figure 5.3).

Definition 5.3.5 A functor $F : \mathcal{A} \rightarrow  \mathcal{B}$ creates limits (of shape I) if whenever $D : \mathbf{I} \rightarrow  \mathcal{A}$ is a diagram in $\mathcal{A}$ ,

- for any limit cone ${\left( B\overset{{q}_{I}}{ \rightarrow  }FD\left( I\right) \right) }_{I \in  \mathbf{I}}$ on the diagram $F \circ  D$ , there is a unique cone ${\left( A\overset{{p}_{I}}{ \rightarrow  }D\left( I\right) \right) }_{I \in  \mathbf{I}}$ on $D$ such that $F\left( A\right)  = B$ and $F\left( {p}_{I}\right)  = {q}_{I}$ for all $I \in  \mathbf{I}$ ;

- this cone ${\left( A\overset{{p}_{I}}{ \rightarrow  }D\left( I\right) \right) }_{I \in  \mathbf{I}}$ is a limit cone on $D$ .

The forgetful functors from Grp, Ring, ... to Set all create limits (Exercise 5.3.11). The word creates is explained by the following result.

Lemma 5.3.6 Let $F : \mathcal{A} \rightarrow  \mathcal{B}$ be a functor and $\mathbf{I}$ a small category. Suppose that $\mathcal{B}$ has, and $F$ creates, limits of shape $\mathbf{I}$ . Then $\mathcal{A}$ has, and $F$ preserves, limits of shape $\mathbf{I}$ .

Proof Exercise 5.3.12.

Since Set has all limits, it follows that all our categories of algebras have all limits, and that the forgetful functors preserve them.

Remark 5.3.7 There is something suspicious about Definition 5.3.5. It refers to equality of objects of a category, a relation that, as we saw on page 31, is usually too strict to be appropriate. It is almost always better to replace equality by isomorphism. If we replace equality by isomorphism throughout the definition of 'creates limits', we obtain a more healthy and inclusive notion. In the notation of Definition 5.3.5, we ask that if $F \circ  D$ has a limit then there exists a cone on $D$ whose image under $F$ is a limit cone, and that every such cone is itself a limit cone.

In fact, what we are calling creation of limits should really be called strict creation of limits, with 'creation of limits' reserved for the more inclusive notion. That is how 'creates' is used in most of the literature. I have chosen to use the strict version here because it is slightly simpler to state, and because the examples at hand all satisfy the stricter condition.

## Exercises

5.3.8 Taking the limit is a process that receives as its input a diagram in a category $\mathcal{A}$ , and produces as its output a new object of $\mathcal{A}$ . Later, we will see that this process is functorial (Proposition 6.1.4). Here you are asked to prove this in the case of binary products.

Let $\mathcal{A}$ be a category with binary products. Suppose that we have chosen for each pair $\left( {X, Y}\right)$ of objects a product cone

$$
X < \overset{{p}_{1}^{X, Y}}{ < }X \times  Y\overset{{p}_{2}^{X, Y}}{ \rightarrow  }Y
$$

Construct a functor $\mathcal{A} \times  \mathcal{A} \rightarrow  \mathcal{A}$ given on objects by $\left( {X, Y}\right)  \mapsto  X \times  Y$ .

5.3.9 Let $\mathcal{A}$ be a category with binary products. Prove directly that

$$
\mathcal{A}\left( {A, X \times  Y}\right)  \cong  \mathcal{A}\left( {A, X}\right)  \times  \mathcal{A}\left( {A, Y}\right)
$$

naturally in $A, X, Y \in  \mathcal{A}$ . (This presupposes that we have chosen for each $X$ and $Y$ a product cone on $\left( {X, Y}\right)$ . By Exercise 5.3.8, the assignment $\left( {X, Y}\right)  \mapsto  X \times  Y$ is then functorial, which it must be in order for 'naturally' to make sense.)

5.3.10 Prove that if a functor creates limits then it also reflects them.

5.3.11 It was shown in Example 5.3.4 that the forgetful functor $U : \operatorname{Grp} \rightarrow$ Set creates binary products.

(a) Using the formula for limits in Set (Example 5.1.22), prove that, in fact, $U$ creates arbitrary limits.

(b) Satisfy yourself that the same is true if $\mathbf{{Grp}}$ is replaced by any other category of algebras such as Ring, $\mathbf{{Ab}}$ or ${\mathbf{{Vect}}}_{k}$ .

5.3.12 Prove Lemma 5.3.6.

5.3.13 (a) An object $P$ of a category $\mathcal{B}$ is projective if $\mathcal{B}\left( {P, - }\right)  : \mathcal{B} \rightarrow$ Set preserves epics. (This means that if $f$ is epic then so is $\mathcal{B}\left( {P, f}\right)$ .) Let Set $\frac{F}{{\epsilon }_{G}} > \mathcal{B}$ be an adjunction in which $G$ preserves epics. Prove that $F\left( S\right)$ is projective for all sets $S$ .

(b) Find a non-projective object of $\mathbf{{Ab}}$ .

(c) An object $I$ of a category $\mathcal{B}$ is injective if it is projective in ${\mathcal{B}}^{\text{ op }}$ , or equivalently if $\mathcal{B}\left( {-, I}\right)  : {\mathcal{B}}^{\text{ op }} \rightarrow$ Set preserves epics. Show that all objects of ${\mathbf{{Vect}}}_{k}$ are injective, and find a non-injective object of $\mathbf{{Ab}}$ .

## 6 Adjoints, representables and limits

We have approached the idea of universal property from three different angles, producing three different formalisms: adjointness, representability, and limits. In this final chapter, we work out the connections between them.

In principle, anything that can be described in one of the three formalisms can also be described in the others. The situation is similar to that of cartesian and polar coordinates: anything that can be done in polar coordinates can in principle be done in cartesian coordinates, and vice versa, but some things are more gracefully done in one system than the other.

In comparing the three approaches, we will discover many of the fundamental results of category theory. Here are some highlights.

- Limits and colimits in functor categories work in the simplest possible way.

- The embedding of a category $\mathbf{A}$ into its presheaf category $\left\lbrack  {{\mathbf{A}}^{\text{ op }},\mathbf{{Set}}}\right\rbrack$ preserves limits (but not colimits).

- The representables are the prime numbers of presheaves: every presheaf can be expressed canonically as a colimit of representables.

- A functor with a left adjoint preserves limits. Under suitable hypotheses, the converse holds too.

- Categories of presheaves $\left\lbrack  {{\mathbf{A}}^{\text{ op }},\mathbf{{Set}}}\right\rbrack$ behave very much like the category of sets, the beginning of an incredible story that brings together the subjects of logic and geometry.

### 6.1 Limits in terms of representables and adjoints

There is more than one way to present the definition of limit. In Chapter 5, we used an explicit form of the definition that is particularly convenient for examples. But we will soon be developing the theory of limits and colimits, and for that, a rephrased form of the definition is useful. In fact, we rephrase it in two different ways: once in terms of representability, and once in terms of adjoints.

We begin by showing that cones are simply natural transformations of a special kind. To do this, we need some notation. Given categories $\mathbf{I}$ and $\mathcal{A}$ and an object $A \in  \mathcal{A}$ , there is a functor ${\Delta A} : \mathbf{I} \rightarrow  \mathcal{A}$ with constant value $A$ on objects and ${1}_{A}$ on maps. This defines, for each $\mathbf{I}$ and $\mathcal{A}$ , the diagonal functor

$$
\Delta  : \mathcal{A} \rightarrow  \left\lbrack  {\mathbf{I},\mathcal{A}}\right\rbrack
$$

The name can be understood by considering the case in which $\mathbf{I}$ is the discrete category with two objects; then $\left\lbrack  {\mathbf{I},\mathcal{A}}\right\rbrack   = \mathcal{A} \times  \mathcal{A}$ and $\Delta \left( A\right)  = \left( {A, A}\right)$ .

Now, given a diagram $D : \mathbf{I} \rightarrow  \mathcal{A}$ and an object $A \in  \mathcal{A}$ , a cone on $D$ with vertex $A$ is simply a natural transformation

$$
\mathbf{I}\underset{D}{\underbrace{ \Downarrow  }}\omega .
$$

Writing Cone $\left( {A, D}\right)$ for the set of cones on $D$ with vertex $A$ , we therefore have

$$
\operatorname{Cone}\left( {A, D}\right)  = \left\lbrack  {\mathbf{I},\mathcal{A}}\right\rbrack  \left( {{\Delta A}, D}\right) . \tag{6.1}
$$

Thus, $\operatorname{Cone}\left( {A, D}\right)$ is functorial in $A$ (contravariantly) and $D$ (covariantly).

Here is our first rephrasing of the definition of limit.

Proposition 6.1.1 Let $\mathbf{I}$ be a small category, $\mathcal{A}$ a category, and $D : \mathbf{I} \rightarrow  \mathcal{A}$ a diagram. Then there is a one-to-one correspondence between limit cones on D and representations of the functor

$$
\operatorname{Cone}\left( {-, D}\right)  : {\mathcal{A}}^{\mathrm{{op}}} \rightarrow  \text{ Set, }
$$

with the representing objects of $\operatorname{Cone}\left( {-, D}\right)$ being the limit objects (that is, the vertices of the limit cones) of $D$ .

Briefly put: a limit of $D$ is a representation of $\left\lbrack  {\mathbf{I},\mathcal{A}}\right\rbrack  \left( {\Delta -, D}\right)$ .

Proof By Corollary 4.3.2, a representation of $\operatorname{Cone}\left( {-, D}\right)$ consists of a cone on $D$ with a certain universal property. This is exactly the universal property in the definition of limit cone.

The proposition formalizes the thought that cones on a diagram $D$ correspond one-to-one with maps into $\mathop{\lim }\limits_{{ \leftarrow  \mathbf{I}}}D$ . It implies that if $D$ has a limit then

$$
\operatorname{Cone}\left( {A, D}\right)  \cong  \mathcal{A}\left( {A,\mathop{\lim }\limits_{ \leftarrow  }D}\right) \tag{6.2}
$$

naturally in $A$ . The correspondence is given from left to right by

$$
{\left( {f}_{I}\right) }_{I \in  \mathbf{I}} \mapsto  \bar{f}
$$

![151_553_380_443_308_0.jpg](images/151_553_380_443_308_0.jpg)

Figure 6.1 Illustration of Lemma 6.1.3.

(in the notation of Definition 5.1.19), and from right to left by

$$
{\left( {p}_{I} \circ  g\right) }_{I \in  \mathbf{I}} \leftrightarrow  g
$$

where ${p}_{I} : \mathop{\lim }\limits_{ \leftarrow  }D \rightarrow  D\left( I\right)$ are the projections.

From Proposition 6.1.1 and Corollary 4.3.10 we deduce:

Corollary 6.1.2 Limits are unique up to isomorphism.

The characterization (6.1) of cones suggests that we might consider varying the diagram $D$ as well as the vertex $A$ . We are naturally led to ask questions such as: given a map $D \rightarrow  {D}^{\prime }$ between diagrams, is there an induced map between the limits of $D$ and ${D}^{\prime }$ ? The answer is yes (Figure 6.1):

Lemma 6.1.3 Let $\mathbf{I}$ be a small category and $\mathbf{I}\underset{{D}^{\prime }}{\underbrace{ \downarrow  \alpha }}\mathcal{A}$ a natural transformation. Let

$$
{\left( \mathop{\lim }\limits_{{ \leftarrow  \mathbf{I}}}D\overset{{p}_{I}}{ \rightarrow  }D\left( I\right) \right) }_{I \in  \mathbf{I}}\;\text{ and }\;{\left( \mathop{\lim }\limits_{{ \leftarrow  \mathbf{I}}}{D}^{\prime }\overset{{p}_{I}^{\prime }}{ \rightarrow  }{D}^{\prime }\left( I\right) \right) }_{I \in  \mathbf{I}}
$$

be limit cones. Then:

(a) there is a unique map $\mathop{\lim }\limits_{{ \leftarrow  \mathbf{I}}}\alpha  : \mathop{\lim }\limits_{{ \leftarrow  \mathbf{I}}}D \rightarrow  \mathop{\lim }\limits_{{ \leftarrow  \mathbf{I}}}{D}^{\prime }$ such that for all $I \in  \mathbf{I}$ , the

square

![152_714_406_244_192_0.jpg](images/152_714_406_244_192_0.jpg)

commutes;

(b) given cones ${\left( A\overset{{f}_{I}}{ \rightarrow  }D\left( I\right) \right) }_{I \in  \mathbf{I}}$ and ${\left( {A}^{\prime }\overset{{f}_{I}^{\prime }}{ \rightarrow  }{D}^{\prime }\left( I\right) \right) }_{I \in  \mathbf{I}}$ and a map $s : A \rightarrow  {A}^{\prime }$ such that

![152_739_730_191_178_0.jpg](images/152_739_730_191_178_0.jpg)

commutes for all $I \in  \mathbf{I}$ , the square

![152_726_975_216_200_0.jpg](images/152_726_975_216_200_0.jpg)

also commutes.

Proof Part (a) follows immediately from the fact that ${\left( \mathop{\lim }\limits_{{ \leftarrow  \mathbf{I}}}D\overset{{\alpha }_{I}{p}_{I}}{ \rightarrow  }{D}^{\prime }\left( I\right) \right) }_{I \in  \mathbf{I}}$ is a cone on ${D}^{\prime }$ . To prove (b), note that for each $I \in  \mathbf{I}$ , we have

$$
{p}_{I}^{\prime } \circ  \left( {\mathop{\lim }\limits_{{ \leftarrow  \mathbf{I}}}\alpha }\right)  \circ  \bar{f} = {\alpha }_{I} \circ  {p}_{I} \circ  \bar{f} = {\alpha }_{I} \circ  {f}_{I} = {f}_{I}^{\prime } \circ  s = {p}_{I}^{\prime } \circ  \overline{{f}^{\prime }} \circ  s.
$$

So by Exercise 5.1.36(a), $\left( {\mathop{\lim }\limits_{{ \leftarrow  \mathbf{I}}}\alpha }\right)  \circ  \bar{f} = \overline{{f}^{\prime }} \circ  s$ .

We can now give the second rephrasing of the definition of limit. It only applies when the category has all limits of the shape concerned.

Proposition 6.1.4 Let $\mathbf{I}$ be a small category and $\mathcal{A}$ a category with all limits of shape $\mathbf{I}$ . Then $\mathop{\lim }\limits_{ \leftarrow  }$ defines a functor $\left\lbrack  {\mathbf{I},\mathcal{A}}\right\rbrack   \rightarrow  \mathcal{A}$ , and this functor is right adjoint to the diagonal functor.

Proof Choose for each $D \in  \left\lbrack  {\mathbf{I},\mathcal{A}}\right\rbrack$ a limit cone on $D$ , and call its vertex $\mathop{\lim }\limits_{{ \leftarrow  \mathbf{I}}}D$ . For each map $\alpha  : D \rightarrow  {D}^{\prime }$ in $\left\lbrack  {\mathbf{I},\mathcal{A}}\right\rbrack$ , we have a canonical map $\mathop{\lim }\limits_{{ \leftarrow  \mathbf{I}}}\alpha$ :

$\mathop{\lim }\limits_{{ \leftarrow  \mathbf{I}}}D \rightarrow  \mathop{\lim }\limits_{{ \leftarrow  \mathbf{I}}}{D}^{\prime }$ , defined as in Lemma 6.1.3(a). This makes $\mathop{\lim }\limits_{{ \leftarrow  \mathbf{I}}}$ into a functor. Proposition 6.1.1 implies that

$$
\left\lbrack  {\mathbf{I},\mathcal{A}}\right\rbrack  \left( {{\Delta A}, D}\right)  = \operatorname{Cone}\left( {A, D}\right)  \cong  \mathcal{A}\left( {A,\mathop{\lim }\limits_{ \leftarrow  }D}\right)
$$

naturally in $A$ , and taking $s = {1}_{A}$ in Lemma 6.1.3(b) tells us that the isomorphism is also natural in $D$ .

To define the functor $\mathop{\lim }\limits_{{ \leftarrow  1}}$ , we had to choose for each $D$ a limit cone on $D$ . This is a non-canonical choice. Nevertheless, different choices only affect the functor $\mathop{\lim }\limits_{{t \rightarrow  1}}$ up to natural isomorphism, by uniqueness of adjoints.

## Exercises

6.1.5 Interpret all the theory of this section in the special case where $\mathbf{I}$ is the discrete category with two objects.

6.1.6 What is the content of Proposition 6.1.4 when $\mathbf{I}$ is a group and $\mathcal{A} =$ Set? What about the dual of Proposition 6.1.4?

### 6.2 Limits and colimits of presheaves

What do limits and colimits look like in functor categories $\left\lbrack  {\mathcal{A},\mathcal{B}}\right\rbrack$ ? In particular, what do they look like in presheaf categories $\left\lbrack  {{\mathcal{A}}^{\text{ op }},\text{ Set }}\right\rbrack$ ? More particularly still, what about limits and colimits of representables? Are they, too, representable?

We will answer all these questions. In order to do so, we first prove that representables preserve limits.

## Representables preserve limits

Let us begin by recalling that, by definition of product, a map $A \rightarrow  X \times  Y$ amounts to a pair of maps $\left( {A \rightarrow  X, A \rightarrow  Y}\right)$ . Here $A, X$ and $Y$ are objects of a category $\mathcal{A}$ with binary products. There is, therefore, a bijection

$$
\mathcal{A}\left( {A, X \times  Y}\right)  \cong  \mathcal{A}\left( {A, X}\right)  \times  \mathcal{A}\left( {A, Y}\right) \tag{6.3}
$$

natural in $A, X, Y \in  \mathcal{A}$ .

Is this a special feature of products, or does some analogous statement hold for every kind of limit? Let us try equalizers. Suppose that $\mathcal{A}$ has equalizers,

and write $\operatorname{Eq}\left( {X\frac{s}{t} \leq  Y}\right)$ for the equalizer of maps $s$ and $t$ . By definition of equalizer, maps

$$
A \rightarrow  \operatorname{Eq}\left( {X\underset{t}{\overset{s}{ \rightarrow  }}Y}\right) \tag{6.4}
$$

correspond one-to-one with maps $f : A \rightarrow  X$ such that $s \circ  f = t \circ  f$ . Now recall that $s$ induces a map

$$
{s}_{ * } = \mathcal{A}\left( {A, s}\right)  : \mathcal{A}\left( {A, X}\right)  \rightarrow  \mathcal{A}\left( {A, Y}\right) ,
$$

and similarly for $t$ . In this notation, what we have just said is that maps (6.4) correspond one-to-one with elements $f \in  \mathcal{A}\left( {A, X}\right)$ such that

$$
\left( {\mathcal{A}\left( {A, s}\right) }\right) \left( f\right)  = \left( {\mathcal{A}\left( {A, t}\right) }\right) \left( f\right) .
$$

By the explicit formula for equalizers in Set (Example 5.1.12), such an $f$ is exactly an element of the equalizer of $\mathcal{A}\left( {A, s}\right)$ and $\mathcal{A}\left( {A, t}\right)$ . So, we have a canonical bijection

$$
\mathcal{A}\left( {A,\operatorname{Eq}\left( {X\underset{t}{\overset{s}{ \rightarrow  }}Y}\right) }\right)  \cong  \operatorname{Eq}\left( {\mathcal{A}\left( {A, X}\right) \overset{\overset{\mathcal{A}\left( {A, s}\right) }{ \rightarrow  }}{\underset{\mathcal{A}\left( {A, t}\right) }{ \rightarrow  }}\mathcal{A}\left( {A, Y}\right) }\right) . \tag{6.5}
$$

This looks something like our isomorphism (6.3) for products.

The isomorphisms (6.3) and (6.5) suggest that, more generally, we might have

$$
\mathcal{A}\left( {A,\mathop{\lim }\limits_{ \leftarrow  }D}\right)  \cong  \mathop{\lim }\limits_{ \leftarrow  }\mathcal{A}\left( {A, D}\right) \tag{6.6}
$$

naturally in $A \in  \mathcal{A}$ and $D \in  \left\lbrack  {\mathbf{I},\mathcal{A}}\right\rbrack$ , whenever $\mathcal{A}$ is a category with limits of shape $\mathbf{I}$ . Here $\mathcal{A}\left( {A, D}\right)$ is the functor

$$
\mathcal{A}\left( {A, D}\right)  : \;\mathbf{I} \rightarrow  \text{ Set }
$$

$$
I \mapsto  \mathcal{A}\left( {A, D\left( I\right) }\right)
$$

This functor could also be written as $\mathcal{A}\left( {A, D\left( -\right) }\right)$ , and is the composite

$$
\mathbf{I}\xrightarrow[]{D}\mathcal{A}\xrightarrow[]{\mathcal{A}\left( {A, - }\right) }\text{ Set. }
$$

The conjectured isomorphism (6.6) states, essentially, that representables preserve limits. We now set about proving this.

Lemma 6.2.1 Let $\mathbf{I}$ be a small category, $\mathcal{A}$ a locally small category, $D$ : $\mathbf{I} \rightarrow  \mathcal{A}$ a diagram, and $A \in  \mathcal{A}$ . Then

$$
\operatorname{Cone}\left( {A, D}\right)  \cong  \mathop{\lim }\limits_{{ \leftarrow  \mathbf{I}}}\mathcal{A}\left( {A, D}\right)
$$

naturally in $A$ and $D$ .

Proof Like all functors from a small category into Set, the functor $\mathcal{A}\left( {A, D}\right)$ does have a limit, given by the explicit formula (5.16). According to this formula, $\lim \mathcal{A}\left( {A, D}\right)$ is the set of all families ${\left( {f}_{I}\right) }_{I \in  \mathbf{I}}$ such that ${f}_{I} \in  \mathcal{A}\left( {A, D\left( I\right) }\right)$ for all $I \in  \mathbf{I}$ and

$$
\left( {\mathcal{A}\left( {A,{Du}}\right) }\right) \left( {f}_{I}\right)  = {f}_{J} \tag{6.7}
$$

for all $I\overset{u}{ \rightarrow  }J$ in $\mathbf{I}$ . But equation (6.7) just says that $\left( {Du}\right)  \circ  {f}_{I} = {f}_{J}$ , so an element of $\mathop{\lim }\limits_{{ \leftarrow  \mathbf{I}}}\mathcal{A}\left( {A, D}\right)$ is nothing but a cone on $D$ with vertex $A$ .

Proposition 6.2.2 (Representables preserve limits) Let $\mathcal{A}$ be a locally small category and $A \in  \mathcal{A}$ . Then $\mathcal{A}\left( {A, - }\right)  : \mathcal{A} \rightarrow$ Set preserves limits.

Proof Let $\mathbf{I}$ be a small category and let $D : \mathbf{I} \rightarrow  \mathcal{A}$ be a diagram that has a limit. Then

$$
\mathcal{A}\left( {A,\mathop{\lim }\limits_{ \leftarrow  }D}\right)  \cong  \operatorname{Cone}\left( {A, D}\right)  \cong  \mathop{\lim }\limits_{ \leftarrow  }\mathcal{A}\left( {A, D}\right)
$$

naturally in $A$ . Here the first isomorphism is Proposition 6.1.1 (or more particularly, the isomorphism (6.2) that follows it), and the second is Lemma 6.2.1.

Remark 6.2.3 Proposition 6.2.2 tells us that

$$
\mathcal{A}\left( {A,\mathop{\lim }\limits_{ \leftarrow  }D}\right)  \cong  \mathop{\lim }\limits_{{ \leftarrow  \mathbf{I}}}\mathcal{A}\left( {A, D}\right) . \tag{6.8}
$$

To dualize Proposition 6.2.2, we replace $\mathcal{A}$ by ${\mathcal{A}}^{\text{ op }}$ . Thus, $\mathcal{A}\left( {-, A}\right)  : {\mathcal{A}}^{\text{ op }} \rightarrow$ Set preserves limits. A limit in ${\mathcal{A}}^{\text{ op }}$ is a colimit in $\mathcal{A}$ , so $\mathcal{A}\left( {-, A}\right)$ transforms colimits in $\mathcal{A}$ into limits in Set:

$$
\mathcal{A}\left( {\mathop{\lim }\limits_{{ \rightarrow  \mathbf{I}}}D, A}\right)  \cong  \mathop{\lim }\limits_{{ \leftarrow  {\mathbf{I}}^{\text{ op }}}}\mathcal{A}\left( {D, A}\right) . \tag{6.9}
$$

The right-hand side is a limit, not a colimit! So even though (6.8) and (6.9) are dual statements, there are, in total, more limits than colimits involved. Somehow, limits have the upper hand.

For example, let $X, Y$ and $A$ be objects of a category $\mathcal{A}$ , and suppose that the sum $X + Y$ exists. By definition of sum, a map $X + Y \rightarrow  A$ amounts to a pair of maps $\left( {X \rightarrow  A, Y \rightarrow  A}\right)$ . In other words, there is a canonical isomorphism

$$
\mathcal{A}\left( {X + Y, A}\right)  \cong  \mathcal{A}\left( {X, A}\right)  \times  \mathcal{A}\left( {Y, A}\right) .
$$

This is the isomorphism (6.9) in the case where $\mathbf{I}$ is the discrete category with two objects.

## Limits in functor categories

Earlier, we learned that it is sometimes useful to view functors as objects in their own right, rather than as maps of categories. For instance, when $G$ is a group, functors $G \rightarrow$ Set are $G$ -sets (Example 1.2.8), which one would usually regard as 'things' rather than 'maps'. This point of view leads to the concept of functor category.

We now begin an analysis of limits and colimits in functor categories $\left\lbrack  {\mathbf{A},\mathcal{S}}\right\rbrack$ . Here $\mathbf{A}$ is small and $\mathcal{S}$ is locally small; these conditions together guarantee that $\left\lbrack  {\mathbf{A},\mathcal{S}}\right\rbrack$ is locally small. The most important cases for us will be $\mathcal{S} =$ Set and $\mathcal{S} = {\text{ Set }}^{\text{ op }}$ . For that reason, we will assume whenever necessary that $\mathcal{S}$ has all limits and colimits.

We show that limits and colimits in $\left\lbrack  {\mathbf{A},\mathcal{S}}\right\rbrack$ work in the simplest way imaginable. For instance, if $\mathcal{S}$ has binary products then so does $\left\lbrack  {\mathbf{A},\mathcal{S}}\right\rbrack$ , and the product of two functors $X, Y : \mathbf{A} \rightarrow  \mathcal{S}$ is the functor $X \times  Y : \mathbf{A} \rightarrow  \mathcal{S}$ given by

$$
\left( {X \times  Y}\right) \left( A\right)  = X\left( A\right)  \times  Y\left( A\right)
$$

for all $A \in  \mathbf{A}$ .

Notation 6.2.4 Let $\mathbf{A}$ and $\mathcal{S}$ be categories. For each $A \in  \mathbf{A}$ , there is a functor

$$
{\mathrm{{ev}}}_{A} : \;\left\lbrack  {\mathbf{A},\mathcal{S}}\right\rbrack   \rightarrow  \mathcal{S}
$$

$$
X\; \mapsto  \;X\left( A\right)
$$

called evaluation at $A$ . We will be working with diagrams in $\left\lbrack  {\mathbf{A},\mathcal{S}}\right\rbrack$ , and given such a diagram $D : \mathbf{I} \rightarrow  \left\lbrack  {\mathbf{A},\mathcal{S}}\right\rbrack$ , we have for each $A \in  \mathbf{A}$ a functor

$$
{\mathrm{{ev}}}_{A} \circ  D : \;\mathbf{I} \rightarrow  \mathcal{S}
$$

$$
I \mapsto  D\left( I\right) \left( A\right)
$$

We write ${\operatorname{ev}}_{A} \circ  D$ as $D\left( -\right) \left( A\right)$ .

Theorem 6.2.5 (Limits in functor categories) Let $\mathbf{A}$ and $\mathbf{I}$ be small categories and $\mathcal{S}$ a locally small category. Let $D : \mathbf{I} \rightarrow  \left\lbrack  {\mathbf{A},\mathcal{S}}\right\rbrack$ be a diagram, and suppose that for each $A \in  \mathbf{A}$ , the diagram $D\left( -\right) \left( A\right)  : \mathbf{I} \rightarrow  \mathcal{S}$ has a limit. Then there is a cone on $D$ whose image under ${\mathrm{{ev}}}_{A}$ is a limit cone on $D\left( -\right) \left( A\right)$ for each $A \in  \mathbf{A}$ . Moreover, any such cone on $D$ is a limit cone.

Theorem 6.2.5 is often expressed as a slogan:

Limits in a functor category are computed pointwise.

The 'points' in the word 'pointwise' are the objects of $\mathbf{A}$ . The slogan means, for example, that given two functors $X, Y \in  \left\lbrack  {\mathbf{A},\mathcal{S}}\right\rbrack$ , their product can be computed by first taking the product $X\left( A\right)  \times  Y\left( A\right)$ in $\mathcal{S}$ for each ’point’ $A$ , then assembling them to form a functor $X \times  Y$ .

Of course, Theorem 6.2.5 has a dual, stating that colimits in a functor category are also computed pointwise.

Proof of Theorem 6.2.5 Take for each $A \in  \mathbf{A}$ a limit cone

$$
{\left( L\left( A\right) \overset{{p}_{I, A}}{ \rightarrow  }D\left( I\right) \left( A\right) \right) }_{I \in  \mathbf{I}} \tag{6.10}
$$

on the diagram $D\left( -\right) \left( A\right)  : \mathbf{I} \rightarrow  \mathcal{S}$ . We prove two statements:

(a) there is exactly one way of extending $L$ to a functor on $\mathbf{A}$ with the property that ${\left( L\overset{{p}_{I}}{ \rightarrow  }D\left( I\right) \right) }_{I \in  \mathbf{I}}$ is a cone on $D$ ;

(b) this cone ${\left( L\overset{{p}_{I}}{ \rightarrow  }D\left( I\right) \right) }_{I \in  \mathbf{I}}$ is a limit cone.

The theorem will follow immediately.

For (a), take a map $f : A \rightarrow  {A}^{\prime }$ in $\mathbf{A}$ . Lemma 6.1.3(a) applied to the natural transformation

![157_621_944_308_132_0.jpg](images/157_621_944_308_132_0.jpg)

implies that there is a unique map $L\left( f\right)  : L\left( A\right)  \rightarrow  L\left( {A}^{\prime }\right)$ such that for all $I \in  \mathbf{I}$ , the square(6.11)

![157_632_1173_290_170_0.jpg](images/157_632_1173_290_170_0.jpg)

commutes. (This is our definition of $L\left( f\right)$ .) We have now defined $L$ on objects and maps of $\mathbf{A}$ . It is easy to check that $L$ preserves composition and identities, and is therefore a functor $L : \mathbf{A} \rightarrow  \mathcal{S}$ . Moreover, the commutativity of diagram (6.11) says exactly that for each $I \in  \mathbf{I}$ , the family ${\left( L\left( A\right) \overset{{p}_{I, A}}{ \rightarrow  }D\left( I\right) \left( A\right) \right) }_{A \in  \mathbf{A}}$ is a natural transformation

$$
\mathbf{A}\underset{D\left( I\right) }{\underbrace{\parallel p{\parallel }_{1}}}\mathcal{I}\text{ . }
$$

So we have a family ${\left( L\overset{{p}_{I}}{ \rightarrow  }D\left( I\right) \right) }_{I \in  \mathbf{I}}$ of maps in $\left\lbrack  {\mathbf{A},\mathcal{S}}\right\rbrack$ , and from the fact that (6.10) is a cone on $D\left( -\right) \left( A\right)$ for each $A \in  \mathbf{A}$ , it follows immediately that ${\left( L\overset{{p}_{I}}{ \rightarrow  }D\left( I\right) \right) }_{I \in  \mathbf{I}}$ is a cone on $D$ .

For (b), let $X \in  \left\lbrack  {\mathbf{A},\mathcal{S}}\right\rbrack$ and let ${\left( X\overset{{q}_{I}}{ \rightarrow  }D\left( I\right) \right) }_{I \in  \mathbf{I}}$ be a cone on $D$ in $\left\lbrack  {\mathbf{A},\mathcal{S}}\right\rbrack$ . For each $A \in  \mathbf{A}$ , we have a cone

$$
{\left( X\left( A\right) \overset{{q}_{I, A}}{ \rightarrow  }D\left( I\right) \left( A\right) \right) }_{I \in  \mathbf{I}}
$$

on $D\left( -\right) \left( A\right)$ in $\mathcal{S}$ , so there is a unique map ${\bar{q}}_{A} : X\left( A\right)  \rightarrow  L\left( A\right)$ such that ${p}_{I, A} \circ \; {\bar{q}}_{A} = {q}_{I, A}$ for all $I \in  \mathbf{I}$ . It only remains to prove that ${\bar{q}}_{A}$ is natural in $A$ , and that follows from Lemma 6.1.3(b).

Theorem 6.2.5 has many important consequences. We begin by recording a cruder form of the theorem (and its dual), which we will use repeatedly.

Corollary 6.2.6 Let $\mathbf{I}$ and $\mathbf{A}$ be small categories, and $\mathcal{S}$ a locally small category. If $\mathcal{S}$ has all limits (respectively, colimits) of shape $\mathbf{I}$ then so does $\left\lbrack  {\mathbf{A},\mathcal{S}}\right\rbrack$ , and for each $A \in  \mathbf{A}$ , the evaluation functor ${\mathrm{{ev}}}_{A} : \left\lbrack  {\mathbf{A},\mathcal{S}}\right\rbrack   \rightarrow  \mathcal{S}$ preserves them.

Warning 6.2.7 If $\mathcal{S}$ does not have all limits of shape $\mathbf{I}$ then $\left\lbrack  {\mathbf{A},\mathcal{S}}\right\rbrack$ may contain limits of shape $\mathbf{I}$ that are not computed pointwise, that is, are not preserved by all the evaluation functors. Examples can be constructed, as in Section 3.3 of Kelly (1982).

Theorem 6.2.5 will also help us to prove that limits commute with limits, in the following sense. Take categories $\mathbf{I},\mathbf{J}$ and $\mathcal{S}$ . There are isomorphisms of categories

$$
\left\lbrack  {\mathbf{I},\left\lbrack  {\mathbf{J},\mathcal{S}}\right\rbrack  }\right\rbrack   \cong  \left\lbrack  {\mathbf{I} \times  \mathbf{J},\mathcal{S}}\right\rbrack   \cong  \left\lbrack  {\mathbf{J},\left\lbrack  {\mathbf{I},\mathcal{S}}\right\rbrack  }\right\rbrack  .
$$

(See Remark 4.1.23(c) and Exercise 1.2.25.) Under these isomorphisms, a functor $D : \mathbf{I} \times  \mathbf{J} \rightarrow  \mathcal{S}$ corresponds to the functors

$$
{D}^{ \bullet  } : \;\mathbf{I} \rightarrow  \left\lbrack  {\mathbf{J},\mathcal{S}}\right\rbrack  \;\text{ and }\;{D}_{ \bullet  } : \;\mathbf{J} \rightarrow  \left\lbrack  {\mathbf{I},\mathcal{S}}\right\rbrack
$$

$$
I \mapsto  D\left( {I, - }\right) \;J \mapsto  D\left( {-, J}\right) .
$$

Supposing that $\mathcal{S}$ has all limits, so do the various functor categories, by Corollary 6.2.6. In particular, there is an object $\mathop{\lim }\limits_{{ \leftarrow  J}}{D}^{ \bullet  }$ of $\left\lbrack  {\mathbf{J},\mathcal{S}}\right\rbrack$ . This is itself a diagram in $\mathcal{S}$ , so we obtain in turn an object $\mathop{\lim }\limits_{{ \rightarrow   \rightarrow  }}\mathop{\lim }\limits_{{ \leftarrow   \rightarrow  }}{D}^{ \bullet  }$ of $\mathcal{S}$ . Alternatively, we can take limits in the other order, producing an object $\lim \mathop{\lim }\limits_{{ \leftarrow   \rightarrow  }}{D}_{ \bullet  }$ of $\mathcal{S}$ . And there is a third possibility: taking the limit of $D$ itself, we obtain another object $\mathop{\lim }\limits_{{ \leftarrow  \mathbf{I} \times  \mathbf{J}}}D$ of $\mathcal{S}$ . The next result states that these three objects are the same. That is, it makes no difference what order we take limits in.

Proposition 6.2.8 (Limits commute with limits) Let $\mathbf{I}$ and $\mathbf{J}$ be small categories. Let $\mathcal{S}$ be a locally small category with limits of shape $\mathbf{I}$ and of shape

J. Then for all $D : \mathbf{I} \times  \mathbf{J} \rightarrow  \mathcal{S}$ , we have

$$
\mathop{\lim }\limits_{ \leftarrow  }\mathop{\lim }\limits_{{ \leftarrow  \mathbf{I}}}{D}^{ \bullet  } \cong  \mathop{\lim }\limits_{{ \leftarrow  \mathbf{I} \times  \mathbf{J}}}D \cong  \mathop{\lim }\limits_{{ \leftarrow  \mathbf{I}}}\mathop{\lim }\limits_{{ \leftarrow  \mathbf{J}}}{D}_{ \bullet  },
$$

and all these limits exist. In particular, $\mathcal{S}$ has limits of shape $\mathbf{I} \times  \mathbf{J}$ .

This is sometimes half-jokingly called Fubini's theorem, as it is something like changing the order of integration in a double integral. The analogy is more appealing with colimits, since, like integrals, colimits can be thought of as a context-sensitive version of sums.

Proof By symmetry, it is enough to prove the first isomorphism. Since $\mathcal{S}$ has limits of shape $\mathbf{I}$ , so does $\left\lbrack  {\mathbf{J},\mathcal{S}}\right\rbrack$ (by Corollary 6.2.6). So $\lim {D}^{ \bullet  }$ exists; it is an object of $\left\lbrack  {\mathbf{J},\mathcal{S}}\right\rbrack$ . Since $\mathcal{S}$ has limits of shape $\mathbf{J},\mathop{\lim }\limits_{{ \leftarrow  \mathbf{J}}}\mathop{\lim }\limits_{{ \leftarrow  \mathbf{I}}}{D}^{ \bullet  }$ exists; it is an object of $\mathcal{S}$ . Then for $S \in  \mathcal{S}$ ,

$$
\mathcal{S}\left( {S,\mathop{\lim }\limits_{{ \leftarrow  \mathbf{J}}}\mathop{\lim }\limits_{{ \leftarrow  \mathbf{I}}}{D}^{ \bullet  }}\right)  \cong  \left\lbrack  {\mathbf{J},\mathcal{S}}\right\rbrack  \left( {{\Delta S},\mathop{\lim }\limits_{{ \leftarrow  \mathbf{I}}}{D}^{ \bullet  }}\right)
$$

$$
\cong  \left\lbrack  {\mathbf{I},\left\lbrack  {\mathbf{J},\mathcal{S}}\right\rbrack  }\right\rbrack  \left( {\Delta \left( {\Delta S}\right) ,{D}^{ \bullet  }}\right)
$$

$$
\cong  \left\lbrack  {\mathbf{I} \times  \mathbf{J},\mathcal{S}}\right\rbrack  \left( {{\Delta S}, D}\right)
$$

naturally in $S$ . The first two steps each follow from Proposition 6.1.1. The third uses the isomorphism $\left\lbrack  {\mathbf{I},\left\lbrack  {\mathbf{J},\mathcal{S}}\right\rbrack  }\right\rbrack   \cong  \left\lbrack  {\mathbf{I} \times  \mathbf{J},\mathcal{S}}\right\rbrack$ , under which $\Delta \left( {\Delta S}\right)$ corresponds to ${\Delta S}$ and ${D}^{ \bullet  }$ corresponds to $D$ .

Hence $\mathop{\lim }\limits_{{ \leftarrow  \mathbf{I}}}\mathop{\lim }\limits_{{ \leftarrow  \mathbf{I}}}{D}^{ \bullet  }$ is a representing object for the functor $\left\lbrack  {\mathbf{I} \times  \mathbf{J},\mathcal{S}}\right\rbrack  \left( {\Delta -, D}\right)$ . By Proposition 6.1.1 again, this says that $\mathop{\lim }\limits_{{ \leftarrow  \mathbf{I} \times  \mathbf{J}}}D$ exists and is isomorphic to $\mathop{\lim }\limits_{{ \leftarrow  \mathbf{J}}}\mathop{\lim }\limits_{{ \leftarrow  \mathbf{I}}}{D}^{ \bullet  }$

Example 6.2.9 When $\mathbf{I} = \mathbf{J} = \underline{ \bullet  }\; \bullet$ , Proposition 6.2.8 says that binary products commute with binary products: if $\mathcal{S}$ has binary products and ${S}_{11},{S}_{12},{S}_{21},{S}_{22} \in  \mathcal{S}$ then the 4-fold product $\mathop{\prod }\limits_{{i, j \in  \{ 1,2\} }}{S}_{ij}$ exists and satisfies

$$
\left( {{S}_{11} \times  {S}_{21}}\right)  \times  \left( {{S}_{12} \times  {S}_{22}}\right)  \cong  \mathop{\prod }\limits_{{i, j \in  \{ 1,2\} }}{S}_{ij} \cong  \left( {{S}_{11} \times  {S}_{12}}\right)  \times  \left( {{S}_{21} \times  {S}_{22}}\right) .
$$

More generally, it makes no difference what order we write products in or where we put the brackets: there are canonical isomorphisms

$$
S \times  T \cong  T \times  S,
$$

$$
\left( {S \times  T}\right)  \times  U \cong  S \times  \left( {T \times  U}\right)
$$

in any category with binary products. If there is also a terminal object 1, there are further canonical isomorphisms

$$
S \times  1 \cong  S \cong  1 \times  S
$$

Warning 6.2.10 The dual of Proposition 6.2.8 states that colimits commute with colimits. For instance,

$$
\left( {{S}_{11} + {S}_{21}}\right)  + \left( {{S}_{12} + {S}_{22}}\right)  \cong  \left( {{S}_{11} + {S}_{12}}\right)  + \left( {{S}_{21} + {S}_{22}}\right)
$$

in any category $\mathcal{S}$ with binary sums. But limits do not in general commute with colimits. For instance, in general,

$$
\left( {{S}_{11} + {S}_{21}}\right)  \times  \left( {{S}_{12} + {S}_{22}}\right)  \ncong  \left( {{S}_{11} \times  {S}_{12}}\right)  + \left( {{S}_{21} \times  {S}_{22}}\right) .
$$

A counterexample is given by taking $\mathcal{S} =$ Set and each ${S}_{ij}$ to be a one-element set. Then the left-hand side has $\left( {1 + 1}\right)  \times  \left( {1 + 1}\right)  = 4$ elements, whereas the right-hand side has $\left( {1 \times  1}\right)  + \left( {1 \times  1}\right)  = 2$ elements.

Here are two further consequences of Theorem 6.2.5.

Corollary 6.2.11 Let $\mathbf{A}$ be a small category. Then $\left\lbrack  {{\mathbf{A}}^{\mathrm{{op}}},\mathbf{{Set}}}\right\rbrack$ has all limits and colimits, and for each $A \in  \mathbf{A}$ , the evaluation functor ${\operatorname{ev}}_{A} : \left\lbrack  {{\mathbf{A}}^{\mathrm{{op}}},\mathbf{{Set}}}\right\rbrack   \rightarrow$ Set preserves them.

Proof Since Set has all limits and colimits, this is immediate from Corollary 6.2.6.

Corollary 6.2.12 The Yoneda embedding ${H}_{ \bullet  } : \mathbf{A} \rightarrow  \left\lbrack  {{\mathbf{A}}^{\text{ op }},\mathbf{{Set}}}\right\rbrack$ preserves limits, for any small category $\mathbf{A}$ .

Proof Let $D : \mathbf{I} \rightarrow  \mathbf{A}$ be a diagram in $\mathbf{A}$ , and let ${\left( \mathop{\lim }\limits_{{ \leftarrow  \mathbf{I}}}D\overset{{p}_{I}}{ \rightarrow  }D\left( I\right) \right) }_{I \in  \mathbf{I}}$ be a limit cone. For each $A \in  \mathbf{A}$ , the composite functor

$$
\mathbf{A}\overset{{H}_{ \bullet  }}{ \rightarrow  }\left\lbrack  {{\mathbf{A}}^{\mathrm{{op}}},\mathbf{{Set}}}\right\rbrack  \overset{{\mathrm{{ev}}}_{A}}{ \rightarrow  }\mathbf{{Set}}
$$

is ${H}^{A}$ , which preserves limits (Proposition 6.2.2). So for each $A \in  \mathbf{A}$ ,

$$
{\left( {\operatorname{ev}}_{A}{H}_{ \bullet  }\left( \mathop{\lim }\limits_{{ \leftarrow  \mathbf{I}}}D\right) \xrightarrow[]{{\operatorname{ev}}_{A}{H}_{ \bullet  }\left( {p}_{I}\right) }{\operatorname{ev}}_{A}{H}_{ \bullet  }\left( D\left( I\right) \right) \right) }_{I \in  \mathbf{I}}
$$

is a limit cone. But then, by the 'moreover' part of Theorem 6.2.5 applied to the diagram ${H}_{ \bullet  } \circ  D$ in $\left\lbrack  {{\mathbf{A}}^{\text{ op }},\mathbf{{Set}}}\right\rbrack$ , the cone

$$
{\left( {H}_{ \bullet  }\left( \mathop{\lim }\limits_{{ \leftarrow  \mathbf{I}}}D\right) \overset{{H}_{ \bullet  }\left( {p}_{I}\right) }{ \rightarrow  }{H}_{ \bullet  }\left( D\left( I\right) \right) \right) }_{I \in  \mathbf{I}}
$$

is also a limit, as required.

Example 6.2.13 Let $\mathbf{A}$ be a category with binary products. Corollary 6.2.12 implies that for all $X, Y \in  \mathbf{A}$ ,

$$
{H}_{X \times  Y} \cong  {H}_{X} \times  {H}_{Y} \tag{6.12}
$$

in $\left\lbrack  {{\mathbf{A}}^{\text{ op }},\mathbf{{Set}}}\right\rbrack$ . When evaluated at a particular object $A$ , this says that

$$
\mathbf{A}\left( {A, X \times  Y}\right)  \cong  \mathbf{A}\left( {A, X}\right)  \times  \mathbf{A}\left( {A, Y}\right)
$$

(using the fact that products are computed pointwise). This is the isomorphism (6.3) that we met at the beginning of this section.

Suppose that we view $\mathbf{A}$ as a subcategory of $\left\lbrack  {{\mathbf{A}}^{\text{ op }},\mathbf{{Set}}}\right\rbrack$ , identifying $A \in  \mathbf{A}$ with the representable ${H}_{A} \in  \left\lbrack  {{\mathbf{A}}^{\text{ op }},\mathbf{{Set}}}\right\rbrack$ as in Figure 4.1. Then the isomorphism (6.12) means that given two objects of $\mathbf{A}$ whose product we want to form, it makes no difference whether we think of the product as taking place in A or $\left\lbrack  {{\mathbf{A}}^{\mathrm{{op}}},\mathbf{{Set}}}\right\rbrack$ . Similarly, if $\mathbf{A}$ has all limits, taking limits does not help us to escape from $\mathbf{A}$ into the rest of $\left\lbrack  {{\mathbf{A}}^{\mathrm{{op}}},\mathbf{{Set}}}\right\rbrack$ : any limit of representable presheaves is again representable.

Warning 6.2.14 The Yoneda embedding does not preserve colimits. For example, if $\mathbf{A}$ has an initial object 0 then ${H}_{0}$ is not initial, since ${H}_{0}\left( 0\right)  = \mathbf{A}\left( {0,0}\right)$ is a one-element set, whereas the initial object of $\left\lbrack  {{\mathbf{A}}^{\mathrm{{op}}},\mathbf{{Set}}}\right\rbrack$ is the presheaf with constant value ∅. We investigate colimits of representables next.

## Every presheaf is a colimit of representables

We now know that the Yoneda embedding preserves limits but not colimits. In fact, the situation for colimits is at the opposite extreme from the situation for limits: by taking colimits of representable presheaves, we can obtain any presheaf we like! This is the last main result of this section.

Every positive integer can be expressed as a product of primes in an essentially unique way. Somewhat similarly, every presheaf can be expressed as a colimit of representables in a canonical (though not unique) way. The repre-sentables are the building blocks of presheaves.

For a different analogy, recall that any complex function holomorphic in a neighbourhood of 0 has a power series expansion, such as

$$
{e}^{z} = 1 + z + \frac{{z}^{2}}{2!} + \frac{{z}^{3}}{3!} + \cdots .
$$

In this sense, the power functions $z \mapsto  {z}^{n}$ are the building blocks of holomorphic functions. We could even take the analogy further: ${\left( \;\right) }^{n}$ is like a representable $\operatorname{Hom}\left( {n, - }\right)$ , and in the categorical context, quotients and sums are types of colimit.

Before we state and prove the theorem, let us look at an easy special case.

Example 6.2.15 Let $\mathbf{A}$ be the discrete category with two objects, $K$ and $L$ . A

presheaf $X$ on $\mathbf{A}$ is just a pair $\left( {X\left( K\right) , X\left( L\right) }\right)$ of sets, and $\left\lbrack  {{\mathbf{A}}^{\text{ op }},\mathbf{{Set}}}\right\rbrack   \cong  \mathbf{{Set}} \times  \mathbf{{Set}}$ . There are two representables, ${H}_{K}$ and ${H}_{L}$ , given by

$$
{H}_{A}\left( B\right)  = \mathbf{A}\left( {B, A}\right)  \cong  \left\{  \begin{array}{ll} 1 & \text{ if }A = B, \\  \varnothing & \text{ if }A \neq  B \end{array}\right.
$$

$\left( {A, B \in  \{ K, L\} }\right)$ . Identifying $\left\lbrack  {{\mathbf{A}}^{\mathrm{{op}}},\mathbf{{Set}}}\right\rbrack$ with $\mathbf{{Set}} \times  \mathbf{{Set}}$ , we have ${H}_{K} \cong  \left( {1,\varnothing }\right)$ and ${H}_{L} \cong  \left( {\varnothing ,1}\right)$ . Every object of $\mathbf{{Set}} \times  \mathbf{{Set}}$ is a sum of copies of $\left( {1,\varnothing }\right)$ and $\left( {\varnothing ,1}\right)$ . Suppose, for instance, that $X\left( K\right)$ has three elements and $X\left( L\right)$ has two elements. Then

$$
\left( {X\left( K\right) , X\left( L\right) }\right)  \cong  \left( {1,\varnothing }\right)  + \left( {1,\varnothing }\right)  + \left( {1,\varnothing }\right)  + \left( {\varnothing ,1}\right)  + \left( {\varnothing ,1}\right)
$$

in Set $\times$ Set. Equivalently,

$$
X \cong  {H}_{K} + {H}_{K} + {H}_{K} + {H}_{L} + {H}_{L}
$$

in $\left\lbrack  {{\mathbf{A}}^{\mathrm{{op}}},\mathbf{{Set}}}\right\rbrack$ , exhibiting $X$ as a sum of representables.

In this example, $X$ is expressed as a sum of five representables, that is, a sum indexed by the set $X\left( K\right)  + X\left( L\right)$ of ’elements’ of $X$ . A sum is a colimit over a discrete category. In the general case, a presheaf $X$ on a category $\mathbf{A}$ is expressed as a colimit over a category whose objects can be thought of as the ’elements’ of $X$ . This is made precise by the following definition.

Definition 6.2.16 Let $\mathbf{A}$ be a category and $X$ a presheaf on $\mathbf{A}$ . The category of elements $\mathbf{E}\left( X\right)$ of $X$ is the category in which:

- objects are pairs $\left( {A, x}\right)$ with $A \in  \mathbf{A}$ and $x \in  X\left( A\right)$ ;

- maps $\left( {{A}^{\prime },{x}^{\prime }}\right)  \rightarrow  \left( {A, x}\right)$ are maps $f : {A}^{\prime } \rightarrow  A$ in $\mathbf{A}$ such that $\left( {Xf}\right) \left( x\right)  = {x}^{\prime }$ .

There is a projection functor $P : \mathbf{E}\left( X\right)  \rightarrow  \mathbf{A}$ defined by $P\left( {A, x}\right)  = A$ and $P\left( f\right)  = \; f$ .

The following 'density theorem' states that every presheaf is a colimit of representables in a canonical way. It is secretly dual to the Yoneda lemma. This becomes apparent if one expresses both in suitably lofty categorical language (that of ends, or that of bimodules); but that is beyond the scope of this book.

Theorem 6.2.17 (Density) Let $\mathbf{A}$ be a small category and $X$ a presheaf on A. Then $X$ is the colimit of the diagram

$$
\mathbf{E}\left( X\right) \overset{P}{ \rightarrow  }\mathbf{A}\overset{{H}_{ \bullet  }}{ \rightarrow  }\left\lbrack  {{\mathbf{A}}^{\mathrm{{op}}},\mathbf{{Set}}}\right\rbrack
$$

in $\left\lbrack  {{\mathbf{A}}^{\mathrm{{op}}},\mathbf{{Set}}}\right\rbrack$ ; that is, $X \cong  \mathop{\lim }\limits_{{ \rightarrow  \mathbf{E}\left( X\right) }}\left( {{H}_{ \bullet  } \circ  P}\right)$ .

Proof First note that since $\mathbf{A}$ is small, so too is $\mathbf{E}\left( X\right)$ . Hence ${H}_{ \bullet  } \circ  P$ really is a diagram in our customary sense (Definition 5.1.18).

Now let $Y \in  \left\lbrack  {{\mathbf{A}}^{\text{ op }},\mathbf{{Set}}}\right\rbrack$ . A cocone on ${H}_{ \bullet  } \circ  P$ with vertex $Y$ is a family

$$
{\left( {H}_{A}\overset{{\alpha }_{A, x}}{ \rightarrow  }Y\right) }_{A \in  \mathbf{A}, x \in  X\left( A\right) }
$$

of natural transformations with the property that for all maps ${A}^{\prime }\overset{f}{ \rightarrow  }A$ in $\mathbf{A}$ and all $x \in  X\left( A\right)$ , the diagram

![163_690_659_171_141_0.jpg](images/163_690_659_171_141_0.jpg)

commutes.

Equivalently (by the Yoneda lemma), a cocone on ${H}_{ \bullet  } \circ  P$ with vertex $Y$ is a family

$$
{\left( {y}_{A, x}\right) }_{A \in  \mathbf{A}, x \in  X\left( A\right) }\text{ , }
$$

with ${y}_{A, x} \in  Y\left( A\right)$ , such that for all maps ${A}^{\prime }\overset{f}{ \rightarrow  }A$ in $\mathbf{A}$ and all $x \in  X\left( A\right)$ ,

$$
\left( {Yf}\right) \left( {y}_{A, x}\right)  = {y}_{{A}^{\prime },\left( {Xf}\right) \left( x\right) }.
$$

To see this, note that if ${\alpha }_{A, x} \in  \left\lbrack  {{\mathbf{A}}^{\text{ op }},\mathbf{{Set}}}\right\rbrack  \left( {{H}_{A}, Y}\right)$ corresponds to ${y}_{A, x} \in  Y\left( A\right)$ , then ${\alpha }_{A, x} \circ  {H}_{f} \in  \left\lbrack  {{\mathbf{A}}^{\text{ op }},\mathbf{{Set}}}\right\rbrack  \left( {{H}_{{A}^{\prime }}, Y}\right)$ corresponds to $\left( {Yf}\right) \left( {y}_{A, x}\right)  \in  Y\left( {A}^{\prime }\right)$ .

Equivalently (writing ${y}_{A, x}$ as ${\overline{\alpha }}_{A}\left( x\right)$ ), it is a family

$$
{\left( X\left( A\right) \overset{{\overline{\alpha }}_{A}}{ \rightarrow  }Y\left( A\right) \right) }_{A \in  \mathbf{A}}
$$

of functions with the property that for all maps ${A}^{\prime }\overset{f}{ \rightarrow  }A$ in $\mathbf{A}$ and all $x \in  X\left( A\right)$ ,

$$
\left( {Yf}\right) \left( {{\overline{\alpha }}_{A}\left( x\right) }\right)  = {\overline{\alpha }}_{{A}^{\prime }}\left( {\left( {Xf}\right) \left( x\right) }\right) .
$$

But this is simply a natural transformation $\overline{\alpha } : X \rightarrow  Y$ . So we have, for each $Y \in  \left\lbrack  {{\mathbf{A}}^{\text{ op }},\mathbf{{Set}}}\right\rbrack$ , a canonical bijection

$$
\left\lbrack  {\mathbf{E}\left( X\right) ,\left\lbrack  {{\mathbf{A}}^{\mathrm{{op}}},\mathbf{{Set}}}\right\rbrack  }\right\rbrack  \left( {{H}_{ \bullet  } \circ  P,{\Delta Y}}\right)  \cong  \left\lbrack  {{\mathbf{A}}^{\mathrm{{op}}},\mathbf{{Set}}}\right\rbrack  \left( {X, Y}\right) .
$$

Hence $X$ is the colimit of ${H}_{ \bullet  } \circ  P$ .

Example 6.2.18 In Example 6.2.15, we expressed a particular presheaf $X$ as a sum of representables. Let us check that the way we did this is a special case of the general construction in the density theorem.

Since $\mathbf{A}$ is discrete, the category of elements $\mathbf{E}\left( X\right)$ is also discrete; it is the set $X\left( K\right)  + X\left( L\right)$ with five elements. The projection $P : \mathbf{E}\left( X\right)  \rightarrow  \mathbf{A}$ sends three of the elements to $K$ and the other two to $L$ , so the diagram ${H}_{ \bullet  } \circ  P : \mathbf{E}\left( X\right)  \rightarrow  \left\lbrack  {{\mathbf{A}}^{\text{ op }},\mathbf{{Set}}}\right\rbrack$ sends three of the elements to ${H}_{K}$ and two to ${H}_{L}$ . The colimit of ${H}_{ \bullet  } \circ  P$ is the sum of these five representables, which is $X$ , just as in Example 6.2.15.

Remarks 6.2.19 (a) The term 'category of elements' is compatible with the generalized element terminology introduced in Definition 4.1.25. A generalized element of an object $X$ is just a map into $X$ , say $Z \rightarrow  X$ ; but, as explained after that definition, we often focus on certain special shapes $Z$ . Now suppose that we are working in a presheaf category $\left\lbrack  {{\mathbf{A}}^{\mathrm{{op}}},\mathbf{{Set}}}\right\rbrack$ . Among all presheaves, the representables have a special status, so we might be especially interested in generalized elements of representable shape. The Yoneda lemma implies that for a presheaf $X$ , the generalized elements of $X$ of representable shape correspond to pairs $\left( {A, x}\right)$ with $A \in  \mathbf{A}$ and $x \in  X\left( A\right)$ . In other words, they are the objects of the category of elements.

(b) In topology, a subspace $A$ of a space $B$ is called dense if every point in $B$ can be obtained as a limit of points in $A$ . This provides some explanation for the name of Theorem 6.2.17: the category $\mathbf{A}$ is ’dense’ in $\left\lbrack  {{\mathbf{A}}^{\text{ op }},\mathbf{{Set}}}\right\rbrack$ because every object of $\left\lbrack  {{\mathbf{A}}^{\text{ op }},\mathbf{{Set}}}\right\rbrack$ can be obtained as a colimit of objects of $\mathbf{A}$ .

## Exercises

6.2.20 Fix a small category $\mathbf{A}$ .

(a) Let $\mathcal{S}$ be a locally small category with pullbacks. Show that a natural transformation

$$
\mathbf{A}\underset{Y}{\underbrace{\parallel \alpha }}\mathcal{L}
$$

is monic (as a map in $\left\lbrack  {\mathbf{A},\mathcal{S}}\right\rbrack$ ) if and only if ${\alpha }_{A}$ is monic for all $A \in  \mathbf{A}$ . (Hint: use Lemma 5.1.32.)

(b) Describe explicitly the monics and epics in $\left\lbrack  {{\mathbf{A}}^{\mathrm{{op}}},\mathbf{{Set}}}\right\rbrack$ .

(c) Can you do part (b) without relying on the fact that limits and colimits of presheaves are computed pointwise?

6.2.21 (a) Prove that representables have the following connectedness property: given a locally small category $\mathcal{A}$ and $A \in  \mathcal{A}$ , if $X, Y \in  \left\lbrack  {{\mathcal{A}}^{\text{ op }},\mathbf{{Set}}}\right\rbrack$ with ${H}_{A} \cong  X + Y$ , then either $X$ or $Y$ is the constant functor 0 .

(b) Deduce that the sum of two representables is never representable.

6.2.22 Show how a category of elements can be described as a comma category.

6.2.23 Let $X$ be a presheaf on a locally small category. Show that $X$ is representable if and only if its category of elements has a terminal object.

(Since a terminal object is a limit of the empty diagram, this implies that the concept of representability can be derived from the concept of limit. Since a terminal object of a category $\mathcal{E}$ is also a right adjoint to the unique functor $\mathcal{E} \rightarrow  \mathbf{1}$ , the concept of representability can also be derived from the concept of adjoint.)

6.2.24 Prove that every slice of a presheaf category is again a presheaf category. That is, given a small category $\mathbf{A}$ and a presheaf $X$ on $\mathbf{A}$ , prove that $\left\lbrack  {{\mathbf{A}}^{\text{ op }},\mathbf{{Set}}}\right\rbrack  /X$ is equivalent to $\left\lbrack  {{\mathbf{B}}^{\text{ op }},\mathbf{{Set}}}\right\rbrack$ for some small category $\mathbf{B}$ .

6.2.25 Let $F : \mathbf{A} \rightarrow  \mathbf{B}$ be a functor between small categories. For each object $B \in  \mathbf{B}$ , there is a comma category $\left( {F \Rightarrow  B}\right)$ (defined dually to the comma category in Example 2.3.4), and there is a projection functor ${P}_{B} : \left( {F \Rightarrow  B}\right)  \rightarrow  \mathbf{A}$ .

(a) Let $X : \mathbf{A} \rightarrow  \mathcal{S}$ be a functor from $\mathbf{A}$ to a category $\mathcal{S}$ with small colimits. For each $B \in  \mathbf{B}$ , let $\left( {{\operatorname{Lan}}_{F}X}\right) \left( B\right)$ be the colimit of the diagram

$$
\left( {F \Rightarrow  B}\right) \overset{{P}_{B}}{ \rightarrow  }\mathbf{A}\overset{X}{ \rightarrow  }\mathcal{I}
$$

Show that this defines a functor ${\operatorname{Lan}}_{F}X : \mathbf{B} \rightarrow  \mathcal{S}$ , and that for functors $Y : \mathbf{B} \rightarrow  \mathcal{S}$ , there is a canonical bijection between natural transformations ${\operatorname{Lan}}_{F}X \rightarrow  Y$ and natural transformations $X \rightarrow  Y \circ  F$ .

(b) Deduce that for any category $\mathcal{S}$ with small colimits, the functor

$$
-  \circ  F : \left\lbrack  {\mathbf{B},\mathcal{S}}\right\rbrack   \rightarrow  \left\lbrack  {\mathbf{A},\mathcal{S}}\right\rbrack
$$

has a left adjoint. (This left adjoint, ${\operatorname{Lan}}_{F}$ , is called left Kan extension along $F$ .)

(c) Part (b) and its dual imply that when $\mathcal{S}$ has small limits and colimits, the functor $-  \circ  F$ has both left and right adjoints. Revisit Exercise 2.1.16 with this in mind, taking $F$ to be either the unique functor $\mathbf{1} \rightarrow  G$ or the unique functor $G \rightarrow  \mathbf{1}$ .

### 6.3 Interactions between adjoint functors and limits

We saw in Proposition 4.1.11 that any set-valued functor with a left adjoint is representable, and in Proposition 6.2.2 that any representable preserves limits.

Hence, any set-valued functor with a left adjoint preserves limits. In fact, this conclusion holds not only for set-valued functors, but in complete generality.

Theorem 6.3.1 Let $\mathcal{A}\frac{F}{\dot{G}} > \mathcal{B}$ be an adjunction. Then $F$ preserves colimits and $G$ preserves limits.

Proof By duality, it is enough to prove that $G$ preserves limits. Let $D : \mathbf{I} \rightarrow  \mathcal{B}$ be a diagram for which a limit exists. Then

$$
\mathcal{A}\left( {A, G\left( {\mathop{\lim }\limits_{{ \leftarrow  \mathbf{I}}}D}\right) }\right)  \cong  \mathcal{B}\left( {F\left( A\right) ,\mathop{\lim }\limits_{{ \leftarrow  \mathbf{I}}}D}\right) \tag{6.13}
$$

$$
\cong  \mathop{\lim }\limits_{ \leftarrow  }\mathcal{B}\left( {F\left( A\right) , D}\right) \tag{6.14}
$$

$$
\cong  \mathop{\lim }\limits_{{ \leftarrow  \mathbf{I}}}\mathcal{A}\left( {A, G \circ  D}\right) \tag{6.15}
$$

$$
\cong  \operatorname{Cone}\left( {A, G \circ  D}\right) \tag{6.16}
$$

naturally in $A \in  \mathcal{A}$ . Here, the isomorphism (6.13) is by adjointness,(6.14) is because representables preserve limits, (6.15) is by adjointness again, and (6.16) is by Lemma 6.2.1. So $G\left( {\mathop{\lim }\limits_{{ \leftarrow  \mathbf{I}}}D}\right)$ represents $\operatorname{Cone}\left( {-, G \circ  D}\right)$ ; that is, it is a limit of $G \circ  D$ .

Example 6.3.2 Forgetful functors from categories of algebras to Set have left adjoints, but hardly ever right adjoints. Correspondingly, they preserve all limits, but rarely all colimits.

Example 6.3.3 Every set $B$ gives rise to an adjunction $\left( {- \times  B}\right)  \dashv  {\left( -\right) }^{B}$ of functors from Set to Set (Example 2.1.6). So $-  \times  B$ preserves colimits and ${\left( -\right) }^{B}$ preserves limits. In particular, $-  \times  B$ preserves finite sums and ${\left( -\right) }^{B}$ preserves finite products, giving isomorphisms

$$
0 \times  B \cong  0,\;\left( {{A}_{1} + {A}_{2}}\right)  \times  B \cong  \left( {{A}_{1} \times  B}\right)  + \left( {{A}_{2} \times  B}\right) , \tag{6.17}
$$

$$
{1}^{B} \cong  1,\;{\left( {A}_{1} \times  {A}_{2}\right) }^{B} \cong  {A}_{1}^{B} \times  {A}_{2}^{B}. \tag{6.18}
$$

These are the analogues of standard rules of arithmetic. (See also Example 6.2.9 and the 'Digression on arithmetic' on page 69.) Indeed, if we know (6.17) and (6.18) for just finite sets then by taking cardinality on both sides, we obtain exactly these standard rules. The natural numbers are, after all, just the isomorphism classes of finite sets.

Example 6.3.4 Given a category $\mathcal{A}$ with all limits of shape $\mathbf{I}$ , we have the adjunction $\mathcal{A}\underset{ \leftarrow  1}{\underbrace{\overset{\Delta }{ \rightleftharpoons  }}}\left\lbrack  {\mathbf{I},\mathcal{A}}\right\rbrack$ (Proposition 6.1.4). Hence $\mathop{\lim }\limits_{{ \leftarrow  \mathbf{I}}}$ preserves limits, or equivalently, limits of shape I commute with (all) limits. This gives another proof that limits commute with limits (Proposition 6.2.8), at least in the case where the category has all limits of one of the shapes concerned.

Example 6.3.5 Theorem 6.3.1 is often used to prove that a functor does not have an adjoint. For instance, it was claimed in Example 2.1.3(e) that the forgetful functor $U :$ Field $\rightarrow$ Set does not have a left adjoint. We can now prove this. If $U$ had a left adjoint $F$ : Set $\rightarrow$ Field, then $F$ would preserve colim-its, and in particular, initial objects. Hence $F\left( \varnothing \right)$ would be an initial object of Field. But Field has no initial object, since there are no maps between fields of different characteristic. Further examples of nonexistence of adjoints can be found in Exercise 6.3.21.

## Adjoint functor theorems

Every functor with a left adjoint preserves limits, but limit-preservation alone does not guarantee the existence of a left adjoint. For example, let $\mathcal{B}$ be any category. The unique functor $\mathcal{B} \rightarrow  \mathbf{1}$ always preserves limits, but by Example 2.1.9, it only has a left adjoint if $\mathcal{B}$ has an initial object.

On the other hand, if we have a limit-preserving functor $G : \mathcal{B} \rightarrow  \mathcal{A}$ and $\mathcal{B}$ has all limits, then there is an excellent chance that $G$ has a left adjoint. It is still not always true, but counterexamples are harder to find. For instance (taking $\mathcal{A} = \mathbf{1}$ again), can you find a category $\mathcal{B}$ that has all limits but no initial object?

The condition of having all limits is so important that it has its own word:

Definition 6.3.6 A category is complete (or properly, small complete) if it has all limits.

There are various results called adjoint functor theorems, all of the following form:

Let $\mathcal{A}$ be a category, $\mathcal{B}$ a complete category, and $G : \mathcal{B} \rightarrow  \mathcal{A}$ a

functor. Suppose that $\mathcal{A},\mathcal{B}$ and $G$ satisfy certain further conditions.

Then

$G$ has a left adjoint $\Leftrightarrow  G$ preserves limits.

The forwards implication is immediate from Theorem 6.3.1. It is the backwards implication that concerns us here.

Typically, the 'further conditions' involve the distinction between small and large collections. But there is a special case in which these complications disappear, and I will use it to explain the main idea behind the proofs of the adjoint functor theorems. It is the case where the categories $\mathcal{A}$ and $\mathcal{B}$ are ordered sets.

As we saw in Section 5.1, limits in ordered sets are meets. More precisely, if $D : \mathbf{I} \rightarrow  \mathbf{B}$ is a diagram in an ordered set $\mathbf{B}$ , then

$$
\mathop{\lim }\limits_{{ \leftarrow  \mathbf{I}}}D = \mathop{\bigwedge }\limits_{{I \in  \mathbf{I}}}D\left( I\right)
$$

with one side defined if and only if the other is. So an ordered set is complete if and only if every subset has a meet. Similarly, a map $G : \mathbf{B} \rightarrow  \mathbf{A}$ of ordered sets preserves limits if and only if

$$
G\left( {\mathop{\bigwedge }\limits_{{i \in  I}}{B}_{i}}\right)  = \mathop{\bigwedge }\limits_{{i \in  I}}G\left( {B}_{i}\right)
$$

whenever ${\left( {B}_{i}\right) }_{i \in  I}$ is a family of elements of $\mathbf{B}$ for which a meet exists.

We now show that for ordered sets, there is an adjoint functor theorem of the simplest possible kind: there are no 'further conditions' at all.

Proposition 6.3.7 (Adjoint functor theorem for ordered sets) Let $\mathbf{A}$ be an ordered set, $\mathbf{B}$ a complete ordered set, and $G : \mathbf{B} \rightarrow  \mathbf{A}$ an order-preserving map. Then

$G$ has a left adjoint $\Leftrightarrow  G$ preserves meets.

Proof Suppose that $G$ preserves meets. By Corollary 2.3.7, it is enough to show that for each $A \in  \mathbf{A}$ , the comma category $\left( {A \Rightarrow  G}\right)$ has an initial object. Let $A \in  \mathbf{A}$ . Then $\left( {A \Rightarrow  G}\right)$ is an ordered set, namely, $\{ B \in  \mathbf{B} \mid  A \leq  G\left( B\right) \}$ with the order inherited from $\mathbf{B}$ . We have to show that $\left( {A \Rightarrow  G}\right)$ has a least element.

Since $\mathbf{B}$ is complete, the meet $\mathop{\bigwedge }\limits_{{B \in  \mathbf{B} : A \leq  G\left( B\right) }}B$ exists in $\mathbf{B}$ . This is the meet of all the elements of $\left( {A \Rightarrow  G}\right)$ , so it suffices to show that the meet is itself an element of $\left( {A \Rightarrow  G}\right)$ . And indeed, since $G$ preserves meets, we have

$$
G\left( {\mathop{\bigwedge }\limits_{{B \in  \mathbf{B} : A \leq  G\left( B\right) }}B}\right)  = \mathop{\bigwedge }\limits_{{B \in  \mathbf{B} : A \leq  G\left( B\right) }}G\left( B\right)  \geq  A,
$$

as required.

In the general setting of Corollary 2.3.7, the initial object of $\left( {A \Rightarrow  G}\right)$ is the pair $\left( {F\left( A\right) , A\overset{{\eta }_{A}}{ \rightarrow  }{GF}\left( A\right) }\right)$ , where $F$ is the left adjoint and $\eta$ is the unit map. So in Proposition 6.3.7, the left adjoint $F$ is given by

$$
F\left( A\right)  = \mathop{\bigwedge }\limits_{{B \in  \mathbf{B} : A \leq  G\left( B\right) }}B. \tag{6.19}
$$

Example 6.3.8 Consider Proposition 6.3.7 in the case $\mathbf{A} = \mathbf{1}$ . The unique functor $G : \mathbf{B} \rightarrow  \mathbf{1}$ automatically preserves meets, and, as observed above, a left adjoint to $G$ is an initial object of $\mathbf{B}$ . So in the case $\mathbf{A} = \mathbf{1}$ , the proposition states that a complete ordered set has a least element. This is not quite trivial, since completeness means the existence of all meets, whereas a least element is an empty join.

By (6.19), the least element of $\mathbf{B}$ is $\mathop{\bigwedge }\limits_{{B \in  \mathbf{B}}}B$ . Thus, a least element is not only a colimit of the functor $\varnothing  \rightarrow  \mathbf{B}$ ; it is also a limit of the identity functor $\mathbf{B} \rightarrow  \mathbf{B}$ .

The synonym 'least upper bound' for 'join' suggests a theorem: that a poset with all meets also has all joins. Indeed, given a poset $\mathbf{B}$ with all meets, the join of a subset of $\mathbf{B}$ is simply the meet of its upper bounds: quite literally, its least upper bound.

Let us now attempt to extend Proposition 6.3.7 from ordered sets to categories, starting with a limit-preserving functor $G$ from a complete category $\mathcal{B}$ to a category $\mathcal{A}$ . In the case of ordered sets, we had for each $A \in  \mathcal{A}$ an inclusion map ${P}_{A} : \left( {A \Rightarrow  G}\right)  \hookrightarrow  \mathbf{B}$ , and we showed that the left adjoint $F$ was given by

$$
F\left( A\right)  = \mathop{\lim }\limits_{{ \leftarrow  \left( {A \Rightarrow  G}\right) }}{P}_{A}. \tag{6.20}
$$

In the general case, the analogue of the inclusion functor is the projection functor

$$
{P}_{A} : \;\left( {A \Rightarrow  G}\right) \; \rightarrow  \;\mathcal{B}
$$

$$
\left( {B, A\overset{f}{ \rightarrow  }G\left( B\right) }\right) \; \mapsto  \;B. \tag{6.21}
$$

The case of ordered sets suggests that in general, equation (6.20) might define a left adjoint $F$ to $G$ . And indeed, it can be shown that if this limit in $\mathcal{B}$ exists and is preserved by $G$ , then (6.20) really does give a left adjoint (Theorem X.1.2 of Mac Lane (1971)).

This might seem to suggest that our adjoint functor theorem generalizes smoothly from ordered sets to arbitrary categories, with no need for further conditions. But it does not, for reasons that are quite subtle.

Those reasons are more easily explained if we relax our terminology slightly. When we defined limits, we built in the condition that the shape category $\mathbf{I}$ was small. However, the definition of limit makes sense for an arbitrary category $\mathbf{I}$ . In this discussion, we will need to refer to this more inclusive notion of limit, so let us temporarily suspend the convention that the shape categories $\mathbf{I}$ of limits are always small.

Now, in the template for adjoint functor theorems stated above (after Definition 6.3.6), it was only required that $\mathcal{B}$ has, and $G$ preserves, small limits. But if $\mathcal{B}$ is a large category then $\left( {A \Rightarrow  G}\right)$ might also be large, since to specify an object or map in $\left( {A \Rightarrow  G}\right)$ , we have to specify (among other things) an object or map in $\mathcal{B}$ . So, the limit (6.20) defining the left adjoint is not guaranteed to be small. Hence there is no guarantee that this limit exists in $\mathcal{B}$ , nor that it is preserved by $G$ . It follows that the functor $F$ ’defined’ by (6.20) might not be defined at all, let alone a left adjoint.

(The reader experiencing difficulty with reasoning about small and large collections might usefully compare finite and infinite collections. For instance, if $\mathcal{B}$ is a finite category and $\mathcal{A}$ has finite hom-sets then $\left( {A \Rightarrow  G}\right)$ is also finite, but otherwise $\left( {A \Rightarrow  G}\right)$ might be infinite.)

Proposition 6.3.7 still stands, since there we were dealing with ordered sets, which as categories are small. We might hope to extend it from posets to arbitrary small categories, since the problem just described affects only large categories. But this turns out not to be very fruitful, since in fact, complete posets are the only complete small categories (Exercise 6.3.23).

Alternatively, we could try to salvage the argument by assuming that $\mathcal{B}$ has, and $G$ preserves, all (possibly large) limits. But again, this is unhelpful: there are almost no such categories $\mathcal{B}$ .

The situation therefore becomes more complicated. Each of the best-known adjoint functor theorems imposes further conditions implying that the large limit $\mathop{\lim }\limits_{{ \leftarrow  \left( {A \Rightarrow  G}\right) }}{P}_{A}$ can be replaced by a small limit in some clever way. This allows one to proceed with the argument above.

The two most famous adjoint functor theorems are the 'general' and the 'special'. Their exact statements and proofs are perhaps less significant than their consequences.

Definition 6.3.9 Let $\mathcal{C}$ be a category. A weakly initial set in $\mathcal{C}$ is a set $\mathbf{S}$ of objects with the property that for each $C \in  \mathcal{C}$ , there exist an element $S \in  \mathbf{S}$ and a map $S \rightarrow  C$ .

Note that $\mathbf{S}$ must be a set, that is, small. So, the existence of a weakly initial set is some kind of size restriction. Such size restrictions are comparable to finiteness conditions in algebra.

Theorem 6.3.10 (General adjoint functor theorem) Let $\mathcal{A}$ be a category, $\mathcal{B}$ a complete category, and $G : \mathcal{B} \rightarrow  \mathcal{A}$ a functor. Suppose that $\mathcal{B}$ is locally small and that for each $A \in  \mathcal{A}$ , the category $\left( {A \Rightarrow  G}\right)$ has a weakly initial set. Then

$$
G\text{ has a left adjoint } \Leftrightarrow  G\text{ preserves limits. }
$$

Proof See the appendix.

Example 6.3.11 The general adjoint functor theorem (GAFT) implies that for any category $\mathcal{B}$ of algebras (Grp, Vect ${}_{k},\ldots$ ), the forgetful functor $U$ : $\mathcal{B} \rightarrow$ Set has a left adjoint. Indeed, we saw in Example 5.1.23 that $\mathcal{B}$ has all limits, and in Example 5.3.4 that $U$ preserves them. Also, $\mathcal{B}$ is locally small. To apply GAFT, we now just have to check that for each $A \in$ Set, the comma category $\left( {A \Rightarrow  U}\right)$ has a weakly initial set. This requires a little cardinal arithmetic, omitted here; see Exercise 6.3.24.

So GAFT tells us that, for instance, the free group functor exists. In Examples 1.2.4(a) and 2.1.3(b), we began to see the trickiness of explicitly constructing the free group on a generating set $A$ . One has to define the set of ’formal expressions’ (such as ${x}^{-1}y{x}^{2}z{y}^{-3}$ , with $x, y, z \in  A$ ), then say what it means for two such expressions to be equivalent (so that ${x}^{-2}{x}^{5}y$ is equivalent to ${x}^{3}y$ ), then define $F\left( A\right)$ to be the set of all equivalence classes, then define the group structure, then check the group axioms, then prove that the resulting group has the universal property required. But using GAFT, we can avoid these complications entirely.

The price to be paid is that GAFT does not give us an explicit description of free groups (or left adjoints more generally). When people speak of knowing some object 'explicitly', they usually mean knowing its elements. An element of an object is a map into it, and we have no handle on maps into $F\left( A\right)$ : since $F$ is a left adjoint, it is maps out of $F\left( A\right)$ that we know about. This is why explicit descriptions of left adjoints are often hard to come by.

Example 6.3.12 More generally, GAFT guarantees that forgetful functors between categories of algebras, such as

$$
\mathbf{{Ab}} \rightarrow  \mathbf{{Grp}},\;\mathbf{{Grp}} \rightarrow  \mathbf{{Mon}},\;\mathbf{{Ring}} \rightarrow  \mathbf{{Mon}},\;{\mathbf{{Vect}}}_{\mathbb{C}} \rightarrow  {\mathbf{{Vect}}}_{\mathbb{R}},
$$

have left adjoints. (Some of them are described in Examples 2.1.3.) This is 'more generally' because Set can be seen as a degenerate example of a category of algebras, in the sense of Remark 2.1.4: a group, ring, etc., is a set equipped with some operations satisfying some equations, and a set is a set equipped with no operations satisfying no equations.

The special adjoint functor theorem (SAFT) operates under much tighter hypotheses than GAFT, and is much less widely applicable. Its main advantage is that it removes the condition on weakly initial sets. Indeed, it removes all further conditions on the functor $G$ .

Theorem 6.3.13 (Special adjoint functor theorem) Let $\mathcal{A}$ be a category, $\mathcal{B}$ a complete category, and $G : \mathcal{B} \rightarrow  \mathcal{A}$ a functor. Suppose that $\mathcal{A}$ and $\mathcal{B}$

are locally small, and that $\mathcal{B}$ satisfies certain further conditions. Then

$$
G\text{ has a left adjoint } \Leftrightarrow  G\text{ preserves limits. }
$$

A precise statement and proof can be found in Section V. 8 of Mac Lane (1971).

Example 6.3.14 Here is the classic application of SAFT. Let CptHff be the category of compact Hausdorff spaces, and $U :$ CptHff $\rightarrow$ Top the forgetful functor. SAFT tells us that $U$ has a left adjoint $F$ , turning any space into a compact Hausdorff space in a canonical way.

The existence of this left adjoint is far from obvious, and verifying the hypotheses of SAFT (or indeed, constructing $F$ in any other way) requires some deep theorems of topology. Given a space $X$ , the resulting compact Hausdorff space $F\left( X\right)$ is called its Stone-Čech compactification. Provided that $X$ satisfies some mild separation conditions, the unit of the adjunction at $X$ is an embedding, so that ${UF}\left( X\right)$ contains $X$ as a subspace.

Another advantage of SAFT is that one can extract from its proof a fairly explicit formula for the left adjoint. In this case, it tells us that $F\left( X\right)$ is the closure of the image of the canonical map

$$
X \rightarrow  {\left\lbrack  0,1\right\rbrack  }^{\operatorname{Top}\left( {X,\left\lbrack  {0,1}\right\rbrack  }\right) },
$$

where the codomain is a power of $\left\lbrack  {0,1}\right\rbrack$ in Top.

## Cartesian closed categories

We have seen that for every set $B$ , there is an adjunction $\left( {- \times  B}\right)  \dashv  {\left( -\right) }^{B}$ (Example 2.1.6), and that for every category $\mathcal{B}$ , there is an adjunction $\left( {- \times  \mathcal{B}}\right)  \dashv \; \left\lbrack  {\mathcal{B}, - }\right\rbrack$ (Remark 4.1.23(c)).

Definition 6.3.15 A category $\mathcal{A}$ is cartesian closed if it has finite products and for each $B \in  \mathcal{A}$ , the functor $-  \times  B : \mathcal{A} \rightarrow  \mathcal{A}$ has a right adjoint.

We write the right adjoint as ${\left( -\right) }^{B}$ , and, for $C \in  \mathcal{A}$ , call ${C}^{B}$ an exponential. We may think of ${C}^{B}$ as the space of maps from $B$ to $C$ . Adjointness says that for all $A, B, C \in  \mathcal{A}$ ,

$$
\mathcal{A}\left( {A \times  B, C}\right)  \cong  \mathcal{A}\left( {A,{C}^{B}}\right)
$$

naturally in $A$ and $C$ . In fact, the isomorphism is natural in $B$ too; that comes for free.

Example 6.3.16 Set is cartesian closed; ${C}^{B}$ is the function set $\operatorname{Set}\left( {B, C}\right)$ .

Example 6.3.17 CAT is cartesian closed; ${\mathcal{C}}^{\mathcal{B}}$ is the functor category $\left\lbrack  {\mathcal{B},\mathcal{C}}\right\rbrack$ .

In any cartesian closed category with finite sums, the isomorphisms (6.17) and (6.18) of Example 6.3.3 hold, for the same reasons as stated there. The objects of a cartesian closed category therefore possess an arithmetic like that of the natural numbers. This thought can be developed in several interesting directions, but here we just note that these isomorphisms provide a way of proving that a category is not cartesian closed.

Example 6.3.18 Vect ${}_{k}$ is not cartesian closed, for any field $k$ . It does have finite products, as we saw in Example 5.1.5: binary product is direct sum $\oplus$ , and the terminal object is the trivial vector space $\{ 0\}$ , which is also initial. But if ${\mathbf{{Vect}}}_{k}$ were cartesian closed then equations (6.17) would hold, so that $\{ 0\}  \oplus  B \cong  \{ 0\}$ for all vector spaces $B$ . This is plainly false.

Remark 6.3.19 For any vector spaces $V$ and $W$ , the set ${\operatorname{Vect}}_{k}\left( {V, W}\right)$ of linear maps can itself be given the structure of a vector space, as in Example 1.2.12. Let us now call this vector space $\left\lbrack  {V, W}\right\rbrack$ .

Given that exponentials are supposed to be 'spaces of maps', you might expect Vect ${}_{k}$ to be cartesian closed, with $\left\lbrack  {-, - }\right\rbrack$ as its exponential. We have just seen that this cannot be so. But as it turns out, the linear maps $U \rightarrow  \left\lbrack  {V, W}\right\rbrack$ correspond to the bilinear maps $U \times  V \rightarrow  W$ , or equivalently the linear maps $U \otimes  V \rightarrow  W$ . In the jargon, ${\mathbf{{Vect}}}_{k}$ is an example of a ’monoidal closed category’. These are like cartesian closed categories, but with the cartesian (categorical) product replaced by some other operation called 'product', in this case the tensor product of vector spaces.

For any set $I$ , the product category ${\mathbf{{Set}}}^{I}$ is cartesian closed, just because Set is. (Exponentials in ${\mathbf{{Set}}}^{I}$ , as well as products, are computed pointwise.) Put another way, $\left\lbrack  {{\mathbf{A}}^{\text{ op }},\mathbf{{Set}}}\right\rbrack$ is cartesian closed whenever $\mathbf{A}$ is discrete. We now show that, in fact, $\left\lbrack  {{\mathbf{A}}^{\text{ op }},\mathbf{{Set}}}\right\rbrack$ is cartesian closed for any small category $\mathbf{A}$ whatsoever. In preparation for proving this, let us conduct a thought experiment. Write $\widehat{\mathbf{A}} = \left\lbrack  {{\mathbf{A}}^{\mathrm{{op}}},\mathbf{{Set}}}\right\rbrack$ . If $\widehat{\mathbf{A}}$ is cartesian closed, what must exponentials in $\widehat{\mathbf{A}}$ be? In other words, given presheaves $Y$ and $Z$ , what must ${Z}^{Y}$ be in order that

$$
\widehat{\mathbf{A}}\left( {X,{Z}^{Y}}\right)  \cong  \widehat{\mathbf{A}}\left( {X \times  Y, Z}\right) \tag{6.22}
$$

for all presheaves $X$ ? If this is true for all presheaves $X$ , then in particular it is true when $X$ is representable, so

$$
{Z}^{Y}\left( A\right)  \cong  \widehat{\mathbf{A}}\left( {{H}_{A},{Z}^{Y}}\right)  \cong  \widehat{\mathbf{A}}\left( {{H}_{A} \times  Y, Z}\right)
$$

for all $A \in  \mathbf{A}$ , the first step by Yoneda. This tells us what ${Z}^{Y}$ must be. Notice that ${Z}^{Y}\left( A\right)$ is not simply $Z{\left( A\right) }^{Y\left( A\right) }$ , as one might at first guess: exponentials in a presheaf category are not generally computed pointwise.

Theorem 6.3.20 For any small category $\mathbf{A}$ , the presheaf category $\widehat{\mathbf{A}}$ is cartesian closed.

Here is the strategy of the proof. The argument in the thought experiment gives us the isomorphism (6.22) whenever $X$ is representable. A general presheaf $X$ is not representable, but it is a colimit of representables, and this allows us to bootstrap our way up.

Proof We know that $\widehat{\mathbf{A}}$ has all limits, and in particular, finite products. It remains to show that $\widehat{\mathbf{A}}$ has exponentials. Fix $Y \in  \widehat{\mathbf{A}}$ .

First we prove that $-  \times  Y : \widehat{\mathbf{A}} \rightarrow  \widehat{\mathbf{A}}$ preserves colimits. (Eventually we will prove that $-  \times  Y$ has a right adjoint, from which preservation of colimits follows, but our proof that it has a right adjoint will use preservation of colimits.) Indeed, since products and colimits in $\widehat{\mathbf{A}}$ are computed pointwise, it is enough to prove that for any set $S$ , the functor $-  \times  S :$ Set $\rightarrow$ Set preserves colimits, and this follows from the fact that Set is cartesian closed.

For each presheaf $Z$ on $\mathbf{A}$ , let ${Z}^{Y}$ be the presheaf defined by

$$
{Z}^{Y}\left( A\right)  = \widehat{\mathbf{A}}\left( {{H}_{A} \times  Y, Z}\right)
$$

for all $A \in  \mathbf{A}$ . This defines a functor ${\left( -\right) }^{Y} : \widehat{\mathbf{A}} \rightarrow  \widehat{\mathbf{A}}$ .

I claim that $\left( {- \times  Y}\right)  \dashv  {\left( -\right) }^{Y}$ . Let $X, Z \in  \widehat{\mathbf{A}}$ . Write $P : \mathbf{E}\left( X\right)  \rightarrow  \mathbf{A}$ for the projection (as in Definition 6.2.16), and write ${H}_{P} = {H}_{ \bullet  } \circ  P$ . Then

$$
\widehat{\mathbf{A}}\left( {X,{Z}^{Y}}\right)  \cong  \widehat{\mathbf{A}}\left( {\mathop{\lim }\limits_{{ \rightarrow  \mathbf{E}\left( X\right) }}{H}_{P},{Z}^{Y}}\right) \tag{6.23}
$$

$$
\cong  \mathop{\lim }\limits_{{ \leftarrow  \mathbf{E}{\left( X\right) }^{\mathrm{{op}}}}}\widehat{\mathbf{A}}\left( {{H}_{P},{Z}^{Y}}\right) \tag{6.24}
$$

$$
\cong  \mathop{\lim }\limits_{{ \leftarrow  \mathbf{E}{\left( X\right) }^{\mathrm{{op}}}}}{Z}^{Y}\left( P\right) \tag{6.25}
$$

$$
\cong  \mathop{\lim }\limits_{{ \leftarrow  \mathbf{E}{\left( X\right) }^{\mathrm{{op}}}}}\widehat{\mathbf{A}}\left( {{H}_{P} \times  Y, Z}\right) \tag{6.26}
$$

$$
\cong  \widehat{\mathbf{A}}\left( {\mathop{\lim }\limits_{{ \rightarrow  \mathbf{E}\left( X\right) }}\left( {{H}_{P} \times  Y}\right) , Z}\right) \tag{6.27}
$$

$$
\cong  \widehat{\mathbf{A}}\left( {\left( {\mathop{\lim }\limits_{{ \rightarrow  \mathbf{E}\left( X\right) }}{H}_{P}}\right)  \times  Y, Z}\right) \tag{6.28}
$$

$$
\cong  \widehat{\mathbf{A}}\left( {X \times  Y, Z}\right) \tag{6.29}
$$

naturally in $X$ and $Z$ . Here (6.23) and (6.29) follow from Theorem 6.2.17; (6.24) and (6.27) are because representables preserve limits (as rephrased in Remark 6.2.3); (6.25) is by Yoneda; (6.26) is by definition of ${Z}^{Y}$ ; and (6.28) is because $-  \times  Y$ preserves colimits.

This result can be seen as a step along the road to topos theory. A topos is a category with certain special properties. Topos theory unifies, in an extraordinary way, important aspects of logic and geometry.

For instance, a topos can be regarded as a 'universe of sets': Set is the most basic example of a topos, and every topos shares enough features with Set that one can reason with its objects as if they were sets of some exotic kind. On the other hand, a topos can be regarded as a generalized topological space: every space gives rise to a topos (namely, the category of sheaves on it), and topological properties of the space can be reinterpreted in a useful way as categorical properties of its associated topos.

By definition, a topos is a cartesian closed category with finite limits and with one further property: the existence of a so-called subobject classifier. For example, the two-element set 2 is the subobject classifier of Set, which means, informally, that subsets of a set $A$ correspond one-to-one with maps $A \rightarrow  2$ . Exercises 6.3.26 and 6.3.27 give the formal definition of subobject classifier, then guide you through the proof that Set, and, more generally, every presheaf category, is a topos.

## Exercises

6.3.21 (a) Prove that the forgetful functor $U : \operatorname{Grp} \rightarrow  \operatorname{Set}$ has no right adjoint.

(b) Prove that the chain of adjunctions $C \dashv  D \dashv  O \dashv  I$ in Exercise 3.2.16 extends no further in either direction.

(c) Does the chain of adjunctions in Exercise 2.1.17 extend further in either direction?

6.3.22 Let $\mathcal{A}$ be a locally small category. For functors $U : \mathcal{A} \rightarrow$ Set, consider the following three conditions: (A) $U$ has a left adjoint; (R) $U$ is representable; (L) $U$ preserves limits.

(a) Show that (A) $\Rightarrow  \left( \mathrm{R}\right)  \Rightarrow  \left( \mathrm{L}\right)$ .

(b) Show that if $\mathcal{A}$ has sums then $\left( \mathrm{R}\right)  \Rightarrow  \left( \mathrm{A}\right)$ .

(If $\mathcal{A}$ satisfies the hypotheses of the special adjoint functor theorem then also (L) $\Rightarrow$ (A), so the three conditions are equivalent.)

6.3.23 (a) Prove that every preordered set is equivalent (as a category) to an ordered set.

(b) Let $\mathcal{A}$ be a category with all small products. Suppose that $\mathcal{A}$ is not a preorder, so that there exists a parallel pair of maps $A\xrightarrow[g]{f}B$ in $\mathcal{A}$ with $f \neq  g$ . By considering the maps $A \rightarrow  {B}^{I}$ for each set $I$ , prove that $\mathcal{A}$ is not small.

(c) Deduce that every small category with small products is equivalent to a complete ordered set.

(d) Adapt the argument to prove that every finite category with finite products is equivalent to a complete ordered set.

6.3.24 Probably the most important application of the general adjoint functor theorem is to proving that forgetful functors between categories of algebras have left adjoints (Example 6.3.11). Verifying the hypotheses can be done with some cardinal arithmetic. Here is a typical example.

(a) Let $A$ be a set. Prove that for any group $G$ and family ${\left( {g}_{a}\right) }_{a \in  A}$ of elements of $G$ , the subgroup of $G$ generated by $\left\{  {{g}_{a} \mid  a \in  A}\right\}$ has cardinality at most $\max \{ \left| \mathbb{N}\right| ,\left| A\right| \}$ .

(b) Prove that for any set $S$ , the collection of isomorphism classes of groups of cardinality at most $\left| S\right|$ is small.

(c) Let $U : \operatorname{\mathbf{G} \mathbf{r} \mathbf{p} } \rightarrow  \operatorname{\mathbf{S} \mathbf{e} \mathbf{t} }$ be the forgetful functor from groups to sets. Deduce from (a) and (b) that for every set $A$ , the comma category $\left( {A \Rightarrow  U}\right)$ has a weakly initial set.

(d) Use GAFT to conclude that $U$ has a left adjoint.

6.3.25 Let $\mathbf{A}$ be a small cartesian closed category. Prove that the Yoneda embedding $\mathbf{A} \rightarrow  \left\lbrack  {{\mathbf{A}}^{\text{ op }},\mathbf{{Set}}}\right\rbrack$ preserves the whole cartesian closed structure (exponentials as well as products).

6.3.26 Recall from Exercise 5.1.40 the notion of subobject. A category $\mathcal{A}$ is well-powered if for each $A \in  \mathcal{A}$ , the class of subobjects of $A$ is small, that is, a set. (All of our usual examples of categories are well-powered.) Let $\mathcal{A}$ be a well-powered category with pullbacks, and write $\operatorname{Sub}\left( A\right)$ for the set of subobjects of an object $A \in  \mathcal{A}$ .

(a) Deduce from Exercise 5.1.42 that any map ${A}^{\prime }\overset{f}{ \rightarrow  }A$ in $\mathcal{A}$ induces a map $\operatorname{Sub}\left( f\right)  : \operatorname{Sub}\left( A\right)  \rightarrow  \operatorname{Sub}\left( {A}^{\prime }\right)$ .

(b) Show that this determines a functor Sub : ${\mathcal{A}}^{\text{ op }} \rightarrow$ Set. (Hint: use Exercise 5.1.35.)

(c) For some categories $\mathcal{A}$ , the functor Sub is representable. A subobject classifier for $\mathcal{A}$ is an object $\Omega  \in  \mathcal{A}$ such that $\operatorname{Sub} \cong  {H}_{\Omega }$ . Prove that 2 is a subobject classifier for Set.

A topos is a cartesian closed category with finite limits and a subobject classifier. You have just completed the proof that Set is a topos.

6.3.27 This exercise follows on from the last, culminating in the proof that every presheaf category is a topos. Let $\mathbf{A}$ be a small category.

(a) By conducting a thought experiment similar to the one before the statement of Theorem 6.3.20, find out what the subobject classifier $\Omega$ of $\left\lbrack  {{\mathbf{A}}^{\mathrm{{op}}},\mathbf{{Set}}}\right\rbrack$ must be if it exists.

(b) Prove that this $\Omega$ is indeed a subobject classifier.

(c) Conclude that $\left\lbrack  {{\mathbf{A}}^{\text{ op }},\mathbf{{Set}}}\right\rbrack$ is a topos.

## Appendix Proof of the general adjoint functor theorem

Here we prove the general adjoint functor theorem, which for convenience is restated below. The left-to-right implication follows immediately from Theorem 6.3.1; it is the right-to-left implication that we have to prove.

Theorem 6.3.10 (General adjoint functor theorem) Let $\mathcal{A}$ be a category, $\mathcal{B}$ a complete category, and $G : \mathcal{B} \rightarrow  \mathcal{A}$ a functor. Suppose that $\mathcal{B}$ is locally small and that for each $A \in  \mathcal{A}$ , the category $\left( {A \Rightarrow  G}\right)$ has a weakly initial set. Then

$$
G\text{ has a left adjoint } \Leftrightarrow  G\text{ preserves limits. }
$$

The heart of the proof is the case $\mathcal{A} = \mathbf{1}$ , where GAFT asserts that a complete locally small category with a weakly initial set has an initial object. We prove this first.

The proof of this special case is illuminated by considering the even more special case where $\mathcal{A} = \mathbf{1}$ and the category $\mathcal{B}$ is a poset $\mathbf{B}$ . We saw in Example 6.3.8 that the initial object (least element) of a complete poset $\mathbf{B}$ can be constructed as the meet of all its elements. Otherwise put, it is the limit of the identity functor ${1}_{\mathbf{B}} : \mathbf{B} \rightarrow  \mathbf{B}$ .

One might try to extend this result to arbitrary categories $\mathcal{B}$ by proving that the limit of the identity functor ${1}_{\mathcal{B}} : \mathcal{B} \rightarrow  \mathcal{B}$ is (if it exists) an initial object. This is indeed true (Exercise A. 3 below). However, it is unhelpful: for if $\mathcal{B}$ is large then the limit of ${1}_{\mathcal{B}}$ is a large limit, but we are only given that $\mathcal{B}$ has small limits.

We seem to be at an impasse - but this is where the clever idea behind GAFT comes in. In order to construct the least element of a complete poset, it is not necessary to take the meet of all the elements. More economically, we could just take the meet of the elements of some weakly initial subset (Exercise A.4).

In general, for an arbitrary complete category, the limit of any weakly initial set is an initial object. We prove this now.

Lemma A. 1 Let $\mathcal{C}$ be a complete locally small category with a weakly initial set. Then $\mathcal{C}$ has an initial object.

Proof Let $\mathbf{S}$ be a weakly initial set in $\mathcal{C}$ . Regard $\mathbf{S}$ as a full subcategory of $\mathcal{C}$ ; then $\mathbf{S}$ is small, since $\mathcal{C}$ is locally small. We may therefore take a limit cone

$$
{\left( 0\overset{{p}_{S}}{ \rightarrow  }S\right) }_{S \in  \mathbf{S}} \tag{A.1}
$$

of the inclusion $\mathbf{S} \hookrightarrow  \mathcal{C}$ . We prove that 0 is initial.

Let $C \in  \mathcal{C}$ . We have to show that there is exactly one map $0 \rightarrow  C$ . Certainly there is at least one, since we may choose some $S \in  \mathbf{S}$ and map $j : S \rightarrow  C$ , and we then have the composite $j{p}_{S} : 0 \rightarrow  C$ . To prove uniqueness, let $f, g$ : $0 \rightarrow  C$ . Form the equalizer

$$
E\overset{i}{ \rightarrow  }0\overset{f}{\underset{g}{ \rightarrow  }}C.
$$

Since $\mathbf{S}$ is weakly initial, we may choose $S \in  \mathbf{S}$ and $h : S \rightarrow  E$ . We then have maps

$$
0\overset{{p}_{S}}{ \rightarrow  }S\overset{h}{ \rightarrow  }E\overset{i}{ \rightarrow  }0
$$

with the property that for all ${S}^{\prime } \in  \mathbf{S}$ ,

$$
{p}_{{S}^{\prime }}\left( {{ih}{p}_{S}}\right)  = \left( {{p}_{{S}^{\prime }}{ih}}\right) {p}_{S} = {p}_{{S}^{\prime }} = {p}_{{S}^{\prime }}{1}_{0}
$$

(where the second equality follows from (A.1) being a cone). But (A.1) is a limit cone, so ${ih}{p}_{S} = {1}_{0}$ by Exercise 5.1.36(a). Hence

$$
f = {fih}{p}_{S} = {gih}{p}_{S} = g,
$$

as required.

We have now proved GAFT in the special case $\mathcal{A} = \mathbf{1}$ . The rest of the proof is comparatively routine.

Lemma A. 2 Let $\mathcal{A}$ and $\mathcal{B}$ be categories. Let $G : \mathcal{B} \rightarrow  \mathcal{A}$ be a functor that preserves limits. Then the projection functor ${P}_{A} : \left( {A \Rightarrow  G}\right)  \rightarrow  \mathcal{B}$ of (6.21) creates limits, for each $A \in  \mathcal{A}$ . In particular, if $\mathcal{B}$ is complete then so is each comma category $\left( {A \Rightarrow  G}\right)$ .

Proof The first statement is Exercise A.5(b), and the second follows from Lemma 5.3.6.

We now prove GAFT. By Corollary 2.3.7, it is enough to show that $\left( {A \Rightarrow  G}\right)$ has an initial object for each $A \in  \mathcal{A}$ . Let $A \in  \mathcal{A}$ . By Lemma A.2, $\left( {A \Rightarrow  G}\right)$ is complete, and by hypothesis, it has a weakly initial set. It is also locally small, since $\mathcal{B}$ is. Hence by Lemma A.1, it has an initial object, as required.

## Exercises

A.3 In this exercise, we suspend the convention (made implicitly in Definition 5.1.19) that we only speak of the limit of a functor $\mathbf{I} \rightarrow  \mathcal{C}$ when $\mathbf{I}$ is small. Let $\mathcal{B}$ be a category, possibly large. The aim is to prove that a limit of the identity functor on $\mathcal{B}$ is exactly an initial object of $\mathcal{B}$ .

(a) Let 0 be an initial object of $\mathcal{B}$ . Show that the cone ${\left( 0 \rightarrow  B\right) }_{B \in  \mathcal{B}}$ on the identity functor ${1}_{\mathcal{B}}$ is a limit cone.

(b) Now let ${\left( L\overset{{p}_{B}}{ \rightarrow  }B\right) }_{B \in  \mathcal{B}}$ be a limit cone on ${1}_{\mathcal{B}}$ . Prove that ${p}_{L}$ is the identity on $L$ , and deduce that $L$ is initial.

A. 4 Here you will prove the special case of Lemma A. 1 in which the category concerned is a poset. Let $C$ be a poset and $S \subseteq  C$ .

(a) What does it mean, in purely order-theoretic terms, for $S$ to be a weakly initial set in $C$ ?

(b) Prove directly that if $S$ is weakly initial and the meet $\mathop{\bigwedge }\limits_{{s \in  S}}s$ exists then $\mathop{\bigwedge }\limits_{{s \in  S}}s$ is a least element of $C$ .

A.5 Let $G : \mathcal{B} \rightarrow  \mathcal{A}$ be a limit-preserving functor, and let $A \in  \mathcal{A}$ .

(a) Show that for any small category $\mathbf{I}$ , a diagram of shape $\mathbf{I}$ in $\left( {A \Rightarrow  G}\right)$ amounts to a diagram $E$ of shape $\mathbf{I}$ in $\mathcal{B}$ together with a cone on $G \circ  E$ with vertex $A$ .

(b) Prove that the projection functor ${P}_{A} : \left( {A \Rightarrow  G}\right)  \rightarrow  \mathcal{B}$ of (6.21) creates limits.

## Further reading

This book is intentionally short. Even some topics that are included in most introductions to category theory are omitted here. I will indicate some of the topics that lie beyond the scope of this book, and suggest where you might read about them. Since there is far more written on category theory than anyone could read in a lifetime, these recommendations are necessarily subjective.

The towering presence among category theory books is the classic by one of its founders:

Saunders Mac Lane, Categories for the Working Mathematician. Springer, 1971; second edition with two new chapters, 1998.

It is so well-written that more than forty years on, it is still the most popular introduction to the subject. It addresses a more mature readership than this text, and covers many topics omitted here, including monads (one formalization of the idea of algebraic theory), monoidal categories (categories equipped with a tensor product), 2-categories (mentioned at the end of our Chapter 1), abelian categories (categories of modules), ends (an elegant generalization of the notion of limit), and Kan extensions (which provide the tongue-in-cheek title of the book's final section: 'All concepts are Kan extensions').

Another well-liked book, longer than the one you hold in your hands but written for a similar readership, is:

Steve Awodey, Category Theory. Oxford University Press, 2010.

Awodey's book covers less than Mac Lane's, but is particularly strong on connections between category theory and other parts of logic. It has a full chapter on cartesian closed categories, and also covers the theory of monads.

Those who prefer lectures to books might try this library of 75 ten-minute introductory category theory videos:

Eugenia Cheng and Simon Willerton, The Catsters. Available at https://www.youtube.com/user/TheCatsters, 2007-2010.

Other than the topics treated here, they cover monads, enriched categories, internal groups (and other internal algebraic structures), string diagrams (which we touched on in Remark 2.2.9), and several more sophisticated topics.

For inspiration as much as instruction, here are two further recommendations.

Saunders Mac Lane, Mathematics: Form and Function. Springer, 1986.

F. William Lawvere and Stephen H. Schanuel, Conceptual Mathematics: A First Introduction to Categories. Cambridge University Press, 1997.

Mathematics: Form and Function is a tour through much of pure and applied mathematics, written from a categorical perspective. Its declared purpose is to present the author's philosophy of mathematics, but it can also be enjoyed for its many excellent vignettes of exposition. (Beware of the numerous small errors.) Conceptual Mathematics is a thought-provoking text and an intriguing experiment: category theory for high-school students, complete with classroom dialogues.

For categorical topics beyond the scope of this book, two good general references are:

Francis Borceux, Handbook of Categorical Algebra, Volumes 1-3. Cambridge University Press, 1994.

Various authors, The nLab. Available at https://ncatlab.org, 2008- present.

Borceux's encyclopaedic work often takes a different point of view from the present text, but covers many, many more topics. Apart from those just mentioned in connection with other books, some of the more important ones are fibrations, bimodules (also called profunctors or distributors), Lawvere theories, Cauchy completeness, Morita equivalence, absolute colimits, and flatness.

The $n$ Lab is an ever-growing online resource for mathematics, focusing on category theory and operating on similar principles to Wikipedia. Individual entries can be idiosyncratic, but it has become a very useful reference for advanced categorical topics.

Vigorous research in category theory continues to be done. The sources listed above provide ample onward references for anyone wishing to explore.

## Other texts cited

Timothy Gowers, Mathematics: A Very Short Introduction. Oxford University Press, 2002.

G. M. Kelly, Basic Concepts of Enriched Category Theory. Cambridge University Press, 1982. Also Reprints in Theory and Applications of Categories 10 (2005), 1-136, available at http://www.tac.mta.ca/tac/reprints.

F. William Lawvere and Robert Rosebrugh, Sets for Mathematics. Cambridge University Press, 2003.

Tom Leinster, Rethinking set theory. American Mathematical Monthly 121 (2014), no. 5, 403-415. Also available at https://arxiv.org/ abs/1212.6543.

## Index of notation

blank space, 24

${gf},{10}$

${\alpha F},{37}$

${F\alpha },{37}$

${\alpha }_{A},{28}$

$\mathcal{A}\left( {A, B}\right) ,{10}$

$\mathcal{A}\left( {A, - }\right) ,{84}$

$\mathcal{A}\left( {-, A}\right) ,{88}$

$\mathcal{A}\left( {f, - }\right) ,{88}$

$\mathcal{A}\left( {-, f}\right) ,{90}$

$\mathcal{A}\left( {A, D}\right) ,{147}$

$D\left( -\right) \left( A\right) ,{149}$

$\mathcal{{B}^{A}},{30}$

${B}^{A},{69},{112},{165}$

${\left( {f}_{i}\right) }_{i \in  I},{111}$

A, B, ... (typeface), 118 V, 128

-, 24

-, 42, 119, 127

~, 96

^, 96, 166

( ) • , ( ) ., 151

$* ,{37}$

${V}^{ * },{24}$

${f}^{ * },{23},{88}$

${f}_{ * },{84},{90}$

$\circ  ,{10},{18},{30}$

$g \circ   - ,{84},{90}$

$-  \circ  f,{88}$

$\forall ,3$

$\exists !,3$

$\rightarrow  ,{10}$

$\rightarrow  ,{99}$

$\Rightarrow  ,{29},{59},{60}$

-1,41

$\bot  ,\mathrm{\;T},{49}$

$\cong  ,{12},{26},{32}$

$\simeq  ,{34}$

≤, 15, 74

1 |, 74

[ , ], 30

$\otimes  ,6$

×, 16, 68, 109

П, 68, 111

+, 68, 127

$\sum ,{68},{127}$

II, 68

II, 127

$\oplus  ,{110}$

A|A,59

A|A,60

$A/ \sim  ,{70}$

$\land  ,{111}$

$\land  ,{111}$

V, 128

( )-1,12

$\varnothing ,{13}$

0,127

1,1,10,18,30,112

1,13

2, 31, 69

2, 118

Δ, 50, 73, 143

$\varepsilon ,{51}$

$\eta ,{51}$

${\pi }_{1},{21}$

$\chi ,{69}$

Ab, 18

( )ab, 45

Bilin, 86

C, 23

CAT, 18

Cat, 77

Cone, 143

CptHff, 123

CRing, 19

D, 4

E, 118, 155

ev, 149

FDVect, 32

Field, 46

FinSet, 35

Grp, 11

${H}^{A},{84}$

${H}_{A},{88}$

${H}^{f},{88}$

${H}_{f},{90}$

${H}^{ \bullet  },{88}$

${H}_{ \bullet  },{90}$

Hom, 10, 90

Hom, 23

I, 7

lim, 119

lim, 127

Mon, 18

N, 15

0, 24, 89

ob, 10

( )°P, 16

P, 118

P, 55,69,89

${P}_{A},{162}$

Ring, 11

Set, 11

${S}^{1},{85}$

T, 118

Top, 12

Top, 21

Toph, 17

Toph, 85

${\text{ Vect }}_{k},{12}$

$\mathbb{Z}\left\lbrack  x\right\rbrack  ,8$

## Index

abelianization, 45

adjoint functor theorems, 159-164

general, 162, 171-173

special, 163

adjunction, 41

composition of adjunctions, 49

vs. equivalence, 55

fixed points of, 57

free-forgetful, 43-46

via initial objects, 60-63, 100, 101

limits preserved in, 158

naturality axiom for, 42, 50-51, 91, 101

nonexistence of adjoints, 159

uniqueness of adjoints, 43, 106

aerial photography, 87

algebra, 92 for algebraic theory, 46

associative, 42-43

algebraic geometry, 21, 36, 92

algebraic theory, 46

algebraic topology, 20

applied mathematics, 9

arithmetic, 69, 112, 158, 165

cardinal, 163, 168

arity, 46

arrow, 10, see also map

associative algebra, 42-43

associativity, 10, 151

axiom of choice, 71, 135

bicycle inner tube, 133

bilinear, see map, bilinear

black king, 72

Boolean algebra, 36

${C}^{ * }$ -algebra, 36

canonical, 33, 39

Cantor, Georg, 78

Cantor's theorem, 74

Cantor-Bernstein theorem, 74

cardinality, 74, 163, 168

cartesian closed category, 164-167

category, 10

cartesian closed, 164-167

category of categories, 18, 77

adjunctions with Set, 78, 167

comma, see comma category

complete, 159

coslice, 60

discrete, 13, 78, 87

functor out of, 29, 31, 32

drawing of, 13

of elements, 154, 156

equivalence of categories, 34

vs. adjunction, 55

essentially small, 76

finite, 121

isomorphism of categories, 26

large, 75

locally small, 75, 84

monoidal closed, 165

one-object, 14-15, see also monoid and group

opposite, 16

product of categories, 16, 26, 39

slice, see slice category

slimmed-down, 35

small, 75, 118

2-category of categories, 38

well-powered, 168

centre, 26

characteristic function, 69

chess, 72

class, 11, 75

closure, 55

cocone, 126, see also cone

codomain, 11

coequalizer, 128, see also equalizer

cohomology, 24

colimit, 126, see also limit

and integration, 151

map out of, 147

collection, 11

comma category, 59

limits in, 172

commutes, 11

complete, 159

component

of map into product, 111

of natural transformation, 28

composition, 10

horizontal, 37

vertical, 37

computer science, 9, 79, 80

cone, 118

limit, 119

as natural transformation, 142

set of cones as limit, 146

connectedness, 156

contravariant, 22, 90

coproduct, 127, see also sum

coprojection, 126

coreflective, 46

coslice category, 60

counit, see unit and counit

covariant, 22

creation of limits, 138-139, 172

density, 154, 156

determinant, 29

diagonal, see functor, diagonal

diagram, 118

commutative, 11

string, 55

direct limit, 131

discrete, see category, discrete and topological space, discrete

disjoint union, 68, see also set, category of, sums in

domain, 11

duality, 16, 35, 132

algebra-geometry, 23, 35

Gelfand-Naimark, 36

Pontryagin, 36

principle of, 16, 49

Stone, 36

terminology for, 126

for vector spaces, 24, 32

duck, 104

Eilenberg, Samuel, 9

element

category of elements, 154, 156

as function, 67

generalized, 92, 105, 117, 123, 156

least, see least element

of presheaf, 99

universal, 100

embedding, 102

empty family, 111, 127

epic, 133, see also monic

regular, 135

split, 135

epimorphism, 133, see also epic

equalizer, 112, 132

map into, 146

vs. pullback, 124

of sets, 70, 113

equivalence of categories, 34

vs. adjunction, 55

equivalence relation, 70, 135

generated by relation, 128

equivariant, 29

essentially small, 76

essentially surjective on objects, 34

evaluation, 32, 95, 148

explicit description, 44, 163

exponential, 164, see also set of functions preserved by Yoneda embedding, 168

faithful, 25, 27

family, 68

empty, 111, 127

fibred product, 115, see also pullback

field, 46, 83, 159

figure, see element, generalized

fixed point, 57, 77

forgetful, see functor, forgetful

fork, 112

foundations, 71-73, 80

Fourier analysis, 36, 78

free functor, 19

Fubini's theorem, 151

full, see functor, full and subcategory, full

function

characteristic, 69

injective, 123

intuitive description of, 66

number of functions, 67

partial, 64

set of functions, 47, 69, 164

surjective, 133

functor, 17

category, 30, 38, 164

limits in, 148-153

composition of functors, 18

contravariant, 22, 90

covariant, 22

diagonal, 50, 73, 142

essentially surjective on objects, 34

faithful, 25, 27

forgetful, 18

left adjoint to, 43, 87, 163

preserves limits, 158

is representable, 85, 87

free, 19

full, 25

full and faithful, 34, 103

identity, 18

limit of, 171, 173

image of, 25

product of functors, 148

representable, 84, 89

and adjoints, 86, 167

colimit of representables, 153-156

isomorphism of representables, 104-105

limit of representables, 152-153

preserves limits, 145-147

sum of representables, 156

'seeing', 83, 85

set-valued, 84

$G$ -set,22,50,157, see also monoid, action of

general adjoint functor theorem (GAFT), 162, 171-173

generalized element, see element, generalized

generated equivalence relation, 128

greatest common divisor, 110

greatest lower bound, 111

group, 6, 101, 103, see also monoid

abelian

coequalizer of, 130

finite limit of, 123

abelianization of, 45

action of, 50, 157, see also monoid, action of

category of groups, 11

colimits in, 137

epics in, 134

equalizers in, 114

is not essentially small, 77

isomorphisms in, 12

limits in, 121, 137-140

is locally small, 76

monics in, 123

free, 19, 44, 63, 163, 168

free on monoid, 45

fundamental, 7, 21, 85, 131

isomorphism of elements of, 39

non-homomorphisms of groups, 36

normal subgroup of, 135

as one-object category, 14

opposite, 26

order of element of, 85, 105

representation of, see representation

topological, 36

holomorphic function, 153

hom-set, 75, 90

homology, 21

homotopy, 17, 85, see also group, fundamental

identity, 10

as zero-fold composite, 11

image

of functor, 25

of homomorphism, 130

inverse, see inverse image

inclusion, 6

indiscrete space, 7, 47

infimum, 111

∞-category, 38

initial, see object, initial and set, weakly initial

injection, 123

injective object, 140

integers, see $\mathbb{Z}$

interchange law, 38

intersection, 110, 120

as pullback, 116, 130

inverse, 12

image, 57, 89

as pullback, 115

limit, 120

right, 71

isomorphism, 12

of categories, 26

and full and faithful functors, 103

natural, 31

preserved by functors, 26

join, 128

Kan extension, 157

kernel, 6, 8, 114

Kronecker, Leopold, 78

large, 75

least element, 128, 171, 173

as meet, 161

least upper bound, 128

Lie algebra, 42-43

limit, 118

as adjoint, 144

vs. colimit, 132, 147, 161

non-commutativity with colimits, 152

commutativity with limits, 150, 159

computed pointwise, 148

cone, 119

creation of, 138-139, 172

direct, 131

finite, 121

in functor category, 148-153

functoriality of, 139

has limits, 121

of identity, 171, 173

informal usage, 119

inverse, 120

large, 161-162, 171, 173

map between limits, 143

map into, 147

non-pointwise, 150

preservation of, 136

by adjoint, 158

from products and equalizers, 121

from pullbacks and terminal object, 125

reflection of, 136

as representation of cone functor, 142

small, 119, 161-162, 173

uniqueness of, 143, 145

locally small, 75, 84

loop, 92

lower bound, 111

lowest common multiple, 128

Mac Lane, Saunders, 9

manifold, 133

map, 10

bilinear, 4, 86, 105, 165

need not resemble function, 13

order-preserving, 22, 26

matrix, 40

meet, 111

metric space, 91

minimum, 110

model, 46

monic, 123

composition of monics, 135

pullback of, 125, 135

regular, 135

split, 135

monoid, 15

action of, 22, 24, 29, 31, 85, see also group, action of

epics between monoids, 134

free group on, 45

homomorphism of monoids, 21

as one-object category, 15, 29, 35, 77

opposite, 26

Yoneda lemma for monoids, 99

monoidal closed category, 165

monomorphism, 123, see also monic

morphism, 10, see also map

$n$ -category,38

natural isomorphism, see isomorphism, natural

natural numbers, 15, 71, 158, see also arithmetic

natural transformation, 28

composition of, 30, 36-38

identity, 30

naturally, 32

object, 10

initial, 48, 127

as adjoint, 49

as limit of identity, 171, 173

uniqueness of, 48

injective, 140

need not resemble set, 13

probing of, 81

projective, 140

-set of category, 78, 85

terminal, 48, 112, see also object, initial

open subset, 89

order-preserving, 22, 26

ordered set, 15, 31

adjunction between, 54, 56, 160-162

complete small category is, 162, 168

vs. preordered set, 16, 167

product in, 110-111

sum in, 128

totally, 39

partial function, 64

partially ordered set, 15, see also ordered set

permutation, 39

pointwise, 23, 148, 165

polynomial, 21, see also ring, polynomial

poset, 15, see also ordered set

power, 112

series, 153

set, 69, 89, 110, 128

predicate, 57

preimage, see inverse image

preorder, 15, see also ordered set

preservation, see limit, preservation of

presheaf, 24, 50

category of presheaves

is cartesian closed, 166

limits in, 152

monics and epics in, 156

slice of, 157

is topos, 169

as colimit of representables, 153-156

element of, 99

prime numbers, 153

product, 108, 111

associativity of, 151

binary, 111

commutativity of, 151

empty, 111

functoriality of, 139

informal usage, 109

map into, 145, 153

as pullback, 115

uniqueness of, 109

projection, 108, 118

projective object, 140

pullback, 114

vs. equalizer, 124

of monic, 125, 135

pasting of pullbacks, 124

square, 115

pushout, 130, see also pullback

quantifiers as adjoints, 57

quotient, 132, 134

of set, 70, 129

reflection (adjunction), 57

reflection of limits, 136

reflective, 46

relation, 128, see also equivalence relation

representable, see functor, representable

representation

of functor, 84, 89

as universal element, 99-102

of group or monoid

linear, 22, 50, 157

regular, 85, 99

ring, 2

category of rings, 11

epics in, 134

is not essentially small, 77

isomorphisms in, 12

limits in, 121, 137-140

is locally small, 76

monics in, 123

free, 87

of functions, 22, 89

polynomial, 8, 19, 87

SAFT (special adjoint functor theorem), 163

sameness, 33-34

scheme, 21

section, 71

sequence, 71, 92

set axiomatization of sets, 79-82

category of sets, 11, 67

coequalizers in, 129

colimits in, 131

epics in, 133

equalizers in, 70, 113

is not essentially small, 76

isomorphisms in, 12

limits in, 120

is locally small, 75

monics in, 123

products in, 47, 68, 107, 109

pushouts in, 130

sums in, 68, 127

as topos, 82, 167

conflicting meaning in ZFC, 80

definition of, 71-73

empty, 67, 72

finite, 35, 76

of functions, 47, 69, 164

history, 78-82

intuitive description of, 66

one-element, 1, 67, 112

open, 89

quotient of, 70, 129

size of, 74-75

structurelessness of, 66

two-element, 69, 89, 167

-valued functor, 84

weakly initial, 162, 171-173

shape

of diagram, 118

of generalized element, 92

sheaf, 24, 167

Sierpiński space, 93

simultaneous equations, 21, 113, 122

slice category, 59

of presheaf category, 157

small, 75, 118, 119

special adjoint functor theorem, 163

sphere, 132-133

Stone-Čech compactification, 164

string diagram, 55

subcategory

full, 25, 103

reflective, 46

subobject, 125

classifier, 167, 168

subset, 69, 125

sum, 127, see also product

empty, 127

map out of, 147

as pushout, 131

supremum, 128

surface, 132-133

surjection, 133

tensor product, 5-6, 86, 105, 165

terminal, see object, terminal

thought experiment, 120, 165, 169

topological group, 36

topological space, 6, 55, see also homotopy and group, fundamental

category of topological spaces, 12

colimits in, 137

epics in, 134

equalizers in, 113

is not essentially small, 77

isomorphisms in, 12

limits in, 121, 137

is locally small, 76

products in, 109

compact Hausdorff, 122, 164

discrete, 4, 47, 87

functions on, 22, 24, 89

Hausdorff, 134

indiscrete, 7, 47

open subset of, 89

subspace of, 113

as topos, 167

two-point, 89

topos, 82, 167-169

total order, 39

transpose, 42

triangle identities, 52, 56

2-category, 38

type, 79-81

underlying, 18

union, 68, 128

as pushout, 130

uniqueness, 1, 3, 31, 105

of constructions, 10, 17, 28, 42, 94

unit and counit, 51

adjunction in terms of, 52, 53

injectivity of unit, 63

unit as initial object, 60-63, 100

universal

element, 100

enveloping algebra, 43

property, 1-7

determines object uniquely, 2, 5

upper bound, 128

van Kampen's theorem, 7, 131

variety, 36

vector space, 3, 4, 40, see also bilinear map

category of vector spaces, 12

is not cartesian closed, 165

colimits in, 137

epics in, 134

equalizers in, 114

is not essentially small, 76

limits in, 121, 123, 137-140

is locally small, 76

monics in, 123

products in, 110

sums in, 127

direct sum of vector spaces, 110, 128

dual, 24, 32

free, 20, 43, 87

unit of, 51, 58, 100

functions on, 24

of linear maps, 23

vertex, 118, 126

weakly initial, 162, 171-173

well-powered, 168

word, 19

Yoneda embedding, 90, 102-103

does not preserve colimits, 153

preserves exponentials, 168

preserves limits, 152

Yoneda lemma, 94

for monoids, 99

$\mathbb{Z}$ (integers)

as group, 39, 83, 101, 103

as ring, 2, 48

ZFC (Zermelo-Fraenkel with choice), 79-82