#include "FIgenerator.h"
#include <cstdio>
#include <cstdlib>

using namespace FIgenerator;

template <typename T>
using VectorT = TemplateSelf::vector<T>;

// 把 setL[offsetL] 与 setR[offsetR] 两个已排序单项式做归并乘法，
// 结果（仍然有序）写入长度为 orderL + orderR 的复用暂存区 out。
template <typename T>
static void MononialProduct(
    T* out,
    const VectorT<T>& setL,
    size_t orderL,
    size_t offsetL,
    const VectorT<T>& setR,
    size_t orderR,
    size_t offsetR)
{
    const T* L = setL.ptr(offsetL * orderL);
    const T* R = setR.ptr(offsetR * orderR);

    size_t i = 0, j = 0, k = 0;
    while (i < orderL && j < orderR)
    {
        if (L[i] <= R[j]) out[k++] = L[i++];
        else              out[k++] = R[j++];
    }
    while (i < orderL) out[k++] = L[i++];
    while (j < orderR) out[k++] = R[j++];
}


// ============================================================================
// MononialSet<T>
// ============================================================================
template <typename T>
MononialSet<T>::MononialSet()
    : order(0), length(0)
{}

// 构造函数：生成包含所有一阶变元 [0, 1, ..., range-1] 的单项式集合
template <typename T>
MononialSet<T>::MononialSet(size_t range, bool /*order1_all_constructor_tag*/)
    : order(1), length(range)
{
    monomials.recount(range);
    for (size_t i = 0; i < range; i++)
    {
        monomials[i] = static_cast<T>(i);
    }
    // Already sorted: [0], [1], [2], ...
}

// 子集构造函数：从 src 中提取所有能整除 target_mono 的单项式（sub-multiset 关系）
// src 和 target_mono 均已按升序排列
template <typename T>
MononialSet<T>::MononialSet(const MononialSet<T>& src, const T* target_mono, size_t target_order)
    : order(src.order), length(0)
{
    if (src.length == 0 || src.order == 0) return;
    monomials.recapacity(src.order * src.length); // 最坏情况：src 中所有单项式都能整除 target_mono
    for (size_t i = 0; i < src.length; i++)
    {
        const T* m = src.monomials.ptr(i * src.order);

        // 双指针检查 m 是否为 target_mono 的 sub-multiset（两者均已排序）
        size_t mi = 0, ti = 0;
        bool isSub = true;
        while (mi < src.order && ti < target_order)
        {
            if (m[mi] == target_mono[ti])      { mi++; ti++; }
            else if (m[mi] < target_mono[ti])  { isSub = false; break; }
            else                               { ti++; }
        }
        if (mi < src.order) isSub = false;  // src 中还有未匹配的元素

        if (isSub)
        {
            for (size_t k = 0; k < src.order; k++) monomials.append(m[k]);
            length++;
        }
    }
}

template <typename T>
void MononialSet<T>::move(MononialSet& src)
{
    if (&src == this) return;
    monomials.move(src.monomials);
    order = src.order;
    length = src.length;
    src.order = 0;
    src.length = 0;
}

template <typename T>
void MononialSet<T>::clear()
{
    monomials.clear();
    order = 0;
    length = 0;
}

template <typename T>
void MononialSet<T>::setShape(size_t o, size_t l)
{
    order = o;
    length = l;
    monomials.recount(order * length);
}

template <typename T>
int MononialSet<T>::compareMonomial(size_t leftIdx, size_t rightIdx) const
{
    const T* L = monomials.ptr(leftIdx * order);
    const T* R = monomials.ptr(rightIdx * order);
    for (size_t i = 0; i < order; i++)
    {
        if (L[i] < R[i]) return -1;
        if (L[i] > R[i]) return 1;
    }
    return 0;
}

template <typename T>
void MononialSet<T>::swapMonomial(size_t leftIdx, size_t rightIdx)
{
    if (leftIdx == rightIdx) return;
    T* L = monomials.ptr(leftIdx * order);
    T* R = monomials.ptr(rightIdx * order);
    for (size_t i = 0; i < order; i++)
    {
        T t = L[i];
        L[i] = R[i];
        R[i] = t;
    }
}

// Insertion sort for small subarrays (more efficient for small n due to low constant factor)
template <typename T>
void MononialSet<T>::insertionSort(long left, long right)
{
    for (long i = left + 1; i <= right; i++)
    {
        long j = i;
        while (j > left && compareMonomial((size_t)j, (size_t)(j - 1)) < 0)
        {
            swapMonomial((size_t)j, (size_t)(j - 1));
            j--;
        }
    }
}

// Median-of-three pivot selection to avoid worst-case O(n²) on sorted/reverse-sorted data
template <typename T>
long MononialSet<T>::medianOfThree(long left, long right)
{
    long mid = left + (right - left) / 2;
    
    // Sort left, mid, right so that left <= mid <= right
    if (compareMonomial((size_t)mid, (size_t)left) < 0)
        swapMonomial((size_t)left, (size_t)mid);
    if (compareMonomial((size_t)right, (size_t)left) < 0)
        swapMonomial((size_t)left, (size_t)right);
    if (compareMonomial((size_t)right, (size_t)mid) < 0)
        swapMonomial((size_t)mid, (size_t)right);
    
    // Return median (which is now at mid position)
    return mid;
}

template <typename T>
void MononialSet<T>::quickSort(long left, long right)
{
    // Use insertion sort for small subarrays (typically faster due to lower constant)
    const long INSERTION_SORT_THRESHOLD = 16;
    
    if (right - left < INSERTION_SORT_THRESHOLD)
    {
        if (left < right)
            insertionSort(left, right);
        return;
    }
    
    // Median-of-three pivot selection to handle sorted/reverse-sorted data
    long pivot = medianOfThree(left, right);
    long i = left;
    long j = right;

    while (i <= j)
    {
        while (compareMonomial((size_t)i, (size_t)pivot) < 0) i++;
        while (compareMonomial((size_t)j, (size_t)pivot) > 0) j--;
        if (i <= j)
        {
            swapMonomial((size_t)i, (size_t)j);
            if (pivot == i) pivot = j;
            else if (pivot == j) pivot = i;
            i++;
            j--;
        }
    }

    if (left < j) quickSort(left, j);
    if (i < right) quickSort(i, right);
}

template <typename T>
void MononialSet<T>::sort(void)
{
    if (length <= 1 || order == 0) return;
    quickSort(0, (long)length - 1);
}

// 静态工厂方法：生成包含所有一阶变元 [0], [1], ..., [range-1] 的单项式集合
template <typename T>
MononialSet<T> MononialSet<T>::order1all(size_t range)
{
    return MononialSet<T>(range, true);
}

// 快速排序单个单项式（in-place）：使用插入排序，适用于小规模数组
template <typename T>
static void sortMonomial(T* mono, size_t order)
{
    // Insertion sort for small arrays (order typically <= 10)
    for (size_t i = 1; i < order; i++)
    {
        T key = mono[i];
        long j = (long)i - 1;
        while (j >= 0 && mono[j] > key)
        {            mono[j + 1] = mono[j];
            j--;
        }
        mono[j + 1] = key;
    }
}

template <typename T>
void MononialSet<T>::append(TemplateSelf::vector<T>& s, size_t offset)
{
    if (order == 0) return;
    if ((offset + 1) * order > s.count()) return;

    const T* src = s.ptr(offset * order);
    for (size_t i = 0; i < order; i++) monomials.append(src[i]);
    length++;
}

// 直接追加一个已排序的原始单项式（长度为 order 的裸指针）
template <typename T>
void MononialSet<T>::appendRaw(const T* mono)
{
    if (order == 0) return;
    for (size_t i = 0; i < order; i++) monomials.append(mono[i]);
    length++;
}

template <typename T>
int MononialSet<T>::compare(const MononialSet& other) const
{
    if (order < other.order) return -1;
    if (order > other.order) return 1;

    const size_t minLen = (length < other.length) ? length : other.length;
    for (size_t m = 0; m < minLen; m++)
    {
        const T* L = monomials.ptr(m * order);
        const T* R = other.monomials.ptr(m * order);
        for (size_t k = 0; k < order; k++)
        {
            if (L[k] < R[k]) return -1;
            if (L[k] > R[k]) return 1;
        }
    }

    if (length < other.length) return -1;
    if (length > other.length) return 1;
    return 0;
}

template <typename T>
bool MononialSet<T>::operator==(const MononialSet& other) const { return compare(other) == 0; }
template <typename T>
bool MononialSet<T>::operator<(const MononialSet& other) const { return compare(other) < 0; }
template <typename T>
bool MononialSet<T>::operator>(const MononialSet& other) const { return compare(other) > 0; }
template <typename T>
bool MononialSet<T>::operator<=(const MononialSet& other) const { return compare(other) <= 0; }
template <typename T>
bool MononialSet<T>::operator>=(const MononialSet& other) const { return compare(other) >= 0; }

template <typename T>
void MononialSet<T>::demo(FILE* fp) const
{
    if (!fp) return;
    fprintf(fp, "MononialSet(order=%zu, length=%zu)\n", order, length);
    for (size_t m = 0; m < length; m++)
    {
        fprintf(fp, "  [%zu]:", m);
        const T* row = monomials.ptr(m * order);
        for (size_t i = 0; i < order; i++)
            fprintf(fp, " %u", (unsigned int)row[i]);
        fprintf(fp, "\n");
    }
}


// ============================================================================
// HomogeneousPolynomial<T>
// ============================================================================
template <typename T>
HomogeneousPolynomial<T>::HomogeneousPolynomial()
    : order(0),
      length(0),
      occupied(0),
      threshold(0),
      logCap(3),
      limitFactor(0.25)
{}

template <typename T>
void HomogeneousPolynomial<T>::move(HomogeneousPolynomial& src)
{
    if (&src == this) return;
    Set.move(src.Set);
    Coefficients.move(src.Coefficients);
    buck.move(src.buck);

    order = src.order;
    length = src.length;
    occupied = src.occupied;
    threshold = src.threshold;
    logCap = src.logCap;
    limitFactor = src.limitFactor;

    src.order = 0;
    src.length = 0;
    src.occupied = 0;
    src.threshold = 0;
    src.logCap = 3;
    src.limitFactor = 0.25;
}

template <typename T>
void HomogeneousPolynomial<T>::clear()
{
    Set.clear();
    Coefficients.clear();
    buck.Free();
    order = 0;
    length = 0;
    occupied = 0;
    threshold = 0;
    logCap = 3;
}

template <typename T>
double HomogeneousPolynomial<T>::loadFactor() const
{
    if (buck.count() == 0) return 0.0;
    return occupied / (double)buck.count();
}

template <typename T>
size_t HomogeneousPolynomial<T>::hashMonomial(const T* mono) const
{
    size_t h = (size_t)1469598103934665603ULL;
    for (size_t i = 0; i < order; i++)
    {
        h ^= (size_t)mono[i] + (size_t)0x9e3779b97f4a7c15ULL + (h << 6) + (h >> 2);
    }

    // buck uses a power-of-two capacity, so its index depends only on the low
    // bits of the hash.  The structured, sorted monomial keys leave those bits
    // strongly correlated after the combine loop above and can create enormous
    // primary clusters under linear probing.  Apply a SplitMix64 finalizer so
    // changes in every input bit avalanche into the low bucket-index bits.
    unsigned long long z = (unsigned long long)h;
    z ^= z >> 30;
    z *= 0xbf58476d1ce4e5b9ULL;
    z ^= z >> 27;
    z *= 0x94d049bb133111ebULL;
    z ^= z >> 31;
    return (size_t)z;
}

template <typename T>
int HomogeneousPolynomial<T>::compareMonomial(const T* monoA, const T* monoB) const
{
    for (size_t i = 0; i < order; i++)
    {
        if (monoA[i] < monoB[i]) return -1;
        if (monoA[i] > monoB[i]) return 1;
    }
    return 0;
}

template <typename T>
void HomogeneousPolynomial<T>::resetHash(size_t logCap_)
{
    logCap = logCap_;
    const size_t cap = ((size_t)1) << logCap;
    buck.Malloc(cap);
    buck.value(0);

    occupied = 0;
    threshold = (size_t)(cap * limitFactor);
    if (threshold == 0) threshold = 1;

    // 只重建 bucket 映射，不改变 Set/Coefficients。
    for (size_t m = 0; m < length; m++)
    {
        const T* mono = Set.ptr(m * order);
        size_t pos = hashMonomial(mono) & (cap - 1);
        for (;;)
        {
            if (buck[pos] == 0)
            {
                buck[pos] = m + 1; // 存 monomial index + 1
                occupied++;
                break;
            }
            pos = (pos + 1) & (cap - 1);
        }
    }
}

template <typename T>
void HomogeneousPolynomial<T>::ensureCapacity()
{
    if (buck.count() == 0)
    {
        resetHash(logCap);
        return;
    }

    if (occupied + 1 > threshold)
        resetHash(logCap + 1);
}

template <typename T>
size_t HomogeneousPolynomial<T>::searchRaw(const T* mono) const
{
    if (buck.count() == 0 || length == 0 || order == 0) return 0;

    const size_t cap = buck.count();
    size_t pos = hashMonomial(mono) & (cap - 1);
    for (;;)
    {
        const size_t cell = buck[pos];
        if (cell == 0) return 0; // not found

        const size_t monoIdx = cell - 1;
        const T* candidate = Set.ptr(monoIdx * order);
        if (compareMonomial(mono, candidate) == 0)
            return monoIdx + 1; // 单项式 index + 1（0 表示未找到）

        pos = (pos + 1) & (cap - 1);
    }
}

template <typename T>
size_t HomogeneousPolynomial<T>::appendRaw(const T* mono, size_t coeffDelta)
{
    if (order == 0) return 0;

    ensureCapacity();

    const size_t cap = buck.count();
    size_t pos = hashMonomial(mono) & (cap - 1);
    for (;;)
    {
        const size_t cell = buck[pos];
        if (cell == 0)
        {
            for (size_t i = 0; i < order; i++) Set.append(mono[i]);

            Coefficients.append(coeffDelta);
            length++;

            buck[pos] = length; // monomial index + 1
            occupied++;
            return pos + 1;
        }

        const size_t monoIdx = cell - 1;
        const T* candidate = Set.ptr(monoIdx * order);
        if (compareMonomial(mono, candidate) == 0)
        {
            Coefficients[monoIdx] += coeffDelta;
            return monoIdx + 1;
        }

        pos = (pos + 1) & (cap - 1);
    }
}

template <typename T>
void HomogeneousPolynomial<T>::set(const MononialSet<T>& s)
{
    clear();
    order = s.order;
    if (order == 0 || s.length == 0)
    {
        resetHash(3);
        return;
    }

    resetHash(3);
    for (size_t i = 0; i < s.length; i++)
    {
        appendRaw(s.monomials.ptr(i * order), 1);
    }
}

template <typename T>
void HomogeneousPolynomial<T>::operator*=(const MononialSet<T>& s)
{
    if (order == 0 || length == 0 || s.order == 0 || s.length == 0)
    {
        clear();
        return;
    }

    HomogeneousPolynomial<T> result;
    result.order = order + s.order;
    result.length = 0;
    result.limitFactor = limitFactor;
    result.logCap = 3;
    result.resetHash(result.logCap);

    VectorT<T> product;
    product.recount(result.order);

    for (size_t i = 0; i < length; i++)
    {
        const size_t coeff = Coefficients[i];
        for (size_t j = 0; j < s.length; j++)
        {
            MononialProduct(product.ptr(), Set, order, i, s.monomials, s.order, j);
            result.appendRaw(product.ptr(), coeff);
        }
    }

    move(result);
}

template <typename T>
size_t HomogeneousPolynomial<T>::search(const TemplateSelf::vector<T>& monomialSet, size_t offset) const
{
    if (order == 0) return 0;
    if ((offset + 1) * order > monomialSet.count()) return 0;
    return searchRaw(monomialSet.ptr(offset * order));
}

template <typename T>
size_t HomogeneousPolynomial<T>::append(const TemplateSelf::vector<T>& monomial)
{
    if (monomial.count() == 0) return 0;

    if (order == 0)
    {
        order = monomial.count();
        length = 0;
        Set.clear();
        Coefficients.clear();
        resetHash(3);
    }

    if (monomial.count() != order)
        return 0;

    return appendRaw(monomial.ptr(), 1);
}

template <typename T>
void HomogeneousPolynomial<T>::demo(FILE* fp) const
{
    if (!fp) return;
    fprintf(fp, "HomogeneousPolynomial(order=%zu, length=%zu, occupied=%zu, cap=%zu)\n",
            order, length, occupied, buck.count());

    for (size_t m = 0; m < length; m++)
    {
        fprintf(fp, "  c=%zu :", Coefficients[m]);
        const T* mono = Set.ptr(m * order);
        for (size_t i = 0; i < order; i++)
            fprintf(fp, " %u", (unsigned int)mono[i]);
        fprintf(fp, "\n");
    }
}


// 显式模板实例化（本项目当前需要的三种键下标类型）
template class MononialSet<unsigned char>;
template class MononialSet<unsigned short>;
template class MononialSet<unsigned int>;
template class HomogeneousPolynomial<unsigned char>;
template class HomogeneousPolynomial<unsigned short>;
template class HomogeneousPolynomial<unsigned int>;
