#include "analyzer.h"
#include <cmath>


namespace analyzer
{
    // 辅助函数：统计向量中非零元素的数量
    size_t CountNonZero(const vector<size_t>& v)
    {
        size_t n = 0;
        for (size_t i = 0; i < v.count(); ++i)
        {
            if (v[i] != 0)
            {
                ++n;
            }
        }
        return n;
    }

    // 辅助函数：混合基数计数器的下一个组合
    bool NextMixedRadix(vector<size_t>& digits, size_t base)
    {
        if (digits.count() == 0)
        {
            return false;
        }

        for (size_t i = 0; i < digits.count(); ++i)
        {
            ++digits[i];
            if (digits[i] < base)
            {
                return true;
            }
            digits[i] = 0;
        }

        return false;
    }

    // 辅助函数：根据函数类型返回对应的字符串表示
    const char* FuncName(func f)
    {
        switch (f)
        {
        case analyzer::poly: return "poly";
        case analyzer::reciprocal: return "reciprocal";
        case analyzer::exp: return "exp";
        case analyzer::gaussian: return "gaussian";
        case analyzer::cos: return "cos";
        case analyzer::sin: return "sin";
        default: return "unknown";
        }
    }

    // 辅助函数：打印单项式表达式
    void PrintSFIItemExpr(FILE* fp, const SFIitem& item)
    {
        const int displayPower = item.power + 1;
        switch (item.function)
        {
        case analyzer::poly:
            fprintf(fp, "x[%zu]^%d", item.XIndex, displayPower);
            break;
        case analyzer::reciprocal:
            fprintf(fp, "x[%zu]^(-%d)", item.XIndex, displayPower);
            break;
        case analyzer::exp:
            fprintf(fp, "exp(-%d*x[%zu])", displayPower, item.XIndex);
            break;
        case analyzer::gaussian:
            fprintf(fp, "exp(-%d*x[%zu]^2)", displayPower, item.XIndex);
            break;
        case analyzer::cos:
            fprintf(fp, "cos(%d*x[%zu])", displayPower, item.XIndex);
            break;
        case analyzer::sin:
            fprintf(fp, "sin(%d*x[%zu])", displayPower, item.XIndex);
            break;
        default:
            fprintf(fp, "unknown(x[%zu],%d)", item.XIndex, displayPower);
            break;
        }

        if (item.factor != 1.0)
        {
            fprintf(fp, "*%g", item.factor);
        }
    }

    double PowIntNonNegative(double x, int n)
    {
        if (n <= 0)
        {
            return 1.0;
        }

        double v = 1.0;
        for (int i = 0; i < n; ++i)
        {
            v *= x;
        }
        return v;
    }

    int EvalSFIItem(const SFIitem& item, double x, double& out)
    {
        const int effectivePower = item.power + 1;
        switch (item.function)
        {
        case analyzer::poly:
            out = item.factor * PowIntNonNegative(x, effectivePower);
            return 0;
        case analyzer::reciprocal:
            if (x == 0.0)
            {
                return -5;
            }
            out = item.factor / PowIntNonNegative(x, effectivePower);
            return 0;
        case analyzer::exp:
            out = item.factor * std::exp(-(double)effectivePower * x);
            return 0;
        case analyzer::gaussian:
            out = item.factor * std::exp(-(double)effectivePower * x * x);
            return 0;
        case analyzer::cos:
            out = item.factor * std::cos((double)effectivePower * x);
            return 0;
        case analyzer::sin:
            out = item.factor * std::sin((double)effectivePower * x);
            return 0;
        default:
            return -2;
        }
    }

    size_t FuncIndex(func f)
    {
        switch (f)
        {
        case analyzer::poly: return 0;
        case analyzer::reciprocal: return 1;
        case analyzer::exp: return 2;
        case analyzer::gaussian: return 3;
        case analyzer::cos: return 4;
        case analyzer::sin: return 5;
        default: return 0;
        }
    }

}

using namespace analyzer;

static bool SameSFIItemKey(const SFIitemKey& left, const SFIitemKey& right)
{
    return left.XIndex == right.XIndex
        && left.effectivePower == right.effectivePower
        && left.factor == right.factor
        && left.function == right.function;
}

static double NormalizeSFIValue(double base, bool powerNormalization, bool positiveDefinite, size_t sumItemOrder, double normalizationPower)
{
    if (!powerNormalization)
    {
        return base;
    }

    if (!positiveDefinite)
    {
        return base;
    }

    if (sumItemOrder <= 1)
    {
        return base;
    }

    if (base < 0.0)
    {
        return base;
    }

    if (sumItemOrder == 2)
    {
        return std::sqrt(base);
    }

    return std::pow(base, normalizationPower);
}

static void FillPowerCache(vector<double>& cache, const SFIpowerPlan& plan, const double* input, func f, size_t xCount)
{
    for (size_t x = 0; x < xCount; ++x)
    {
        const unsigned int maxPower = plan.maxPower[x];
        if (maxPower == 0)
        {
            continue;
        }

        const size_t offset = plan.offset[x];
        double base = 1.0;
        switch (f)
        {
        case analyzer::poly:
            base = input[x];
            cache[offset] = 1.0;
            cache[offset + 1] = base;
            break;
        case analyzer::reciprocal:
            cache[offset] = 1.0;
            if (input[x] == 0.0)
            {
                for (unsigned int p = 1; p <= maxPower; ++p)
                {
                    cache[offset + p] = 0.0;
                }
                continue;
            }
            base = 1.0 / input[x];
            cache[offset + 1] = base;
            break;
        case analyzer::exp:
            base = std::exp(-input[x]);
            cache[offset] = 1.0;
            cache[offset + 1] = base;
            break;
        case analyzer::gaussian:
            base = std::exp(-input[x] * input[x]);
            cache[offset] = 1.0;
            cache[offset + 1] = base;
            break;
        default:
            continue;
        }

        for (unsigned int p = 2; p <= maxPower; ++p)
        {
            cache[offset + p] = cache[offset + p - 1] * base;
        }
    }
}

static void FillTrigCaches(vector<double>& cosCache, const SFIpowerPlan& cosPlan,
    vector<double>& sinCache, const SFIpowerPlan& sinPlan, const double* input, size_t xCount)
{
    for (size_t x = 0; x < xCount; ++x)
    {
        const unsigned int maxCos = cosPlan.maxPower[x];
        const unsigned int maxSin = sinPlan.maxPower[x];
        const unsigned int maxTrig = (maxCos > maxSin) ? maxCos : maxSin;
        if (maxTrig == 0)
        {
            continue;
        }

        const double sin1 = std::sin(input[x]);
        const double cos1 = std::cos(input[x]);
        if (maxCos > 0)
        {
            const size_t off = cosPlan.offset[x];
            cosCache[off] = 1.0;
            cosCache[off + 1] = cos1;
        }
        if (maxSin > 0)
        {
            const size_t off = sinPlan.offset[x];
            sinCache[off] = 0.0;
            sinCache[off + 1] = sin1;
        }

        double prevSin = sin1;
        double prevCos = cos1;
        for (unsigned int p = 2; p <= maxTrig; ++p)
        {
            const double nextSin = prevSin * cos1 + prevCos * sin1;
            const double nextCos = prevCos * cos1 - prevSin * sin1;
            if (p <= maxCos)
            {
                cosCache[cosPlan.offset[x] + p] = nextCos;
            }
            if (p <= maxSin)
            {
                sinCache[sinPlan.offset[x] + p] = nextSin;
            }
            prevSin = nextSin;
            prevCos = nextCos;
        }
    }
}

static double CachedSFIItemValue(const SFIitemKey& key, vector<double> caches[6], const SFIpowerPlan plans[6])
{
    const size_t idx = FuncIndex(key.function);
    const double base = caches[idx][plans[idx].offset[key.XIndex] + static_cast<size_t>(key.effectivePower)];
    return key.factor * base;
}

double SFIitem::compute(double x) const
{
    double out = 0.0;
    EvalSFIItem(*this, x, out);
    return out;
}

double SFIitem::compute(const double* x) const
{
    return compute(x[XIndex]);
}

double SFIformula::compute(const double* x) const
{
    if (order <= 0 || ItemCount == 0 || items.count() == 0)
    {
        return 0.0;
    }
    
    double acc = 0.0;
    const size_t order_sz = (size_t)order;
    for (size_t m = 0; m < ItemCount; ++m)
    {
        double term = 1.0;
        const size_t base = m * order_sz;
        for (size_t k = 0; k < order_sz; ++k)
        {
            term *= items[base + k].compute(x);
        }
        acc += term;
    }
    return acc;
}

double SFIformula::compute(const double* x, bool PowerNormalization) const
{
    const double base = compute(x);
    const size_t realOrder = (sumItemOrderCached > 0) ? sumItemOrderCached : GetSumofItemsOrder();
    const bool positive = (sumItemOrderCached > 0) ? positiveDefiniteCached : PositiveDefinite();
    const double exponent = (realOrder > 0) ? (1.0 / static_cast<double>(realOrder)) : 1.0;
    return NormalizeSFIValue(base, PowerNormalization, positive, realOrder, exponent);
}

bool SFIformula::PositiveDefinite(void) const
{
    if (order <= 0 || ItemCount == 0 || items.count() == 0)
    {
        return false;
    }

    const size_t order_sz = static_cast<size_t>(order);
    if (items.count() < order_sz)
    {
        return false;
    }

    bool positive = true;
    for (size_t i = 0; i < order_sz; ++i)
    {
        const func f = items[i].function;
        positive = positive && (f != analyzer::sin) && (f != analyzer::cos);
        if (!positive)
        {
            break;
        }
    }

    return positive;
}

size_t SFIformula::GetSumofItemsOrder(void) const
{
    if (order <= 0 || ItemCount == 0 || items.count() == 0)
    {
        return 0;
    }

    const size_t order_sz = static_cast<size_t>(order);
    const size_t limit = (items.count() < order_sz) ? items.count() : order_sz;
    size_t sum = 0;
    for (size_t i = 0; i < limit; ++i)
    {
        sum += static_cast<size_t>(items[i].power + 1);
    }

    return sum;
}

void SFIformula::move(SFIformula& src)
{
    items.move(src.items);
    partion.move(src.partion);
    order = src.order;
    ItemCount = src.ItemCount;
    SourceCount = src.SourceCount;
    positiveDefiniteCached = src.positiveDefiniteCached;
    sumItemOrderCached = src.sumItemOrderCached;
    normalizationPower = src.normalizationPower;
    src.order = 0;
    src.ItemCount = 0;
    src.SourceCount = 0;
    src.positiveDefiniteCached = false;
    src.sumItemOrderCached = 0;
    src.normalizationPower = 1.0;
}

void SFIexpresses::move(SFIexpresses& src)
{
    formulas.move(src.formulas);
    highestOrder = src.highestOrder;
    HighestSource = src.HighestSource;
    XCount = src.XCount;
    SourceOrder1Count = src.SourceOrder1Count;
    Order1.move(src.Order1);
    settings.move(src.settings);
    XindexToPartition.move(src.XindexToPartition);
    itemCacheKeys.move(src.itemCacheKeys);
    for (size_t i = 0; i < 6; ++i)
    {
        powerPlans[i].move(src.powerPlans[i]);
    }
    src.highestOrder = 0;
    src.HighestSource = 0;
    src.XCount = 0;
    src.SourceOrder1Count = 0;
}

void SFIexpresses::BuildItemCachePlan(void)
{
    itemCacheKeys.recount(0);
    for (size_t f = 0; f < 6; ++f)
    {
        powerPlans[f].maxPower.recount(XCount);
        powerPlans[f].maxPower.value(0);
        powerPlans[f].offset.recount(XCount);
        powerPlans[f].offset.value(0);
        powerPlans[f].cacheSize = 0;
    }

    for (size_t fi = 0; fi < formulas.count(); ++fi)
    {
        SFIformula& formula = formulas[fi];
        formula.positiveDefiniteCached = formula.PositiveDefinite();
        formula.sumItemOrderCached = formula.GetSumofItemsOrder();
        formula.normalizationPower = (formula.sumItemOrderCached > 0)
            ? (1.0 / static_cast<double>(formula.sumItemOrderCached))
            : 1.0;

        for (size_t itemIndex = 0; itemIndex < formula.items.count(); ++itemIndex)
        {
            SFIitem& item = formula.items[itemIndex];
            SFIitemKey key;
            key.XIndex = item.XIndex;
            key.effectivePower = item.power + 1;
            key.factor = item.factor;
            key.function = item.function;

            size_t cacheIndex = (size_t)(-1);
            for (size_t k = 0; k < itemCacheKeys.count(); ++k)
            {
                if (SameSFIItemKey(itemCacheKeys[k], key))
                {
                    cacheIndex = k;
                    break;
                }
            }

            if (cacheIndex == (size_t)(-1))
            {
                cacheIndex = itemCacheKeys.count();
                itemCacheKeys.append(key);
            }

            item.cacheIndex = cacheIndex;
            const size_t funcIndex = FuncIndex(item.function);
            if (item.XIndex < XCount && key.effectivePower > (int)powerPlans[funcIndex].maxPower[item.XIndex])
            {
                powerPlans[funcIndex].maxPower[item.XIndex] = static_cast<unsigned int>(key.effectivePower);
            }
        }
    }

    for (size_t f = 0; f < 6; ++f)
    {
        size_t cacheSize = 0;
        for (size_t x = 0; x < XCount; ++x)
        {
            if (powerPlans[f].maxPower[x] > 0)
            {
                powerPlans[f].offset[x] = cacheSize;
                cacheSize += static_cast<size_t>(powerPlans[f].maxPower[x]) + 1;
            }
        }
        powerPlans[f].cacheSize = cacheSize;
    }
}

void SFIexpresses::build(const FIexpresses& source, int max_order, const vector<Setting>& Settings)
{
    // 构建流程：先对来源FI做按阶+CrossItem过滤，再按每个FI的划分信息进行“虚拟阶”函数组合枚举。
    FIexpresses here(source);
    here.cutoffByOrder(max_order, true);

    formulas.recount(0);
    Order1.recount(0);
    settings = Settings;
    highestOrder = 0;
    HighestSource = 0;
    XCount = here.getXCount(); // SFI的输入变量数量与来源FI一致
    SourceOrder1Count = here.getOrder1Count(); 

    const vector<FIexpress>& hereItems = here.getItems();
    const vector<vector<size_t> >& herePartions = here.getPartions();
    
    // 检查划分向量数量与FI数量是否匹配
    if (herePartions.count() != hereItems.count())
    {
        throw std::runtime_error("SFI build failed: partion count does not match FI count.");
    }

    for (size_t i = 0; i < hereItems.count(); ++i)
    {
        if (hereItems[i].order == 1)
        {
            Order1.append(hereItems[i]);
        }
    }

    // 检查一阶不变量数量与来源FI中一阶单项式数量是否匹配
    if (Order1.count() != SourceOrder1Count)
    {
        throw std::runtime_error("SFI build failed: Order1 count mismatch.");
    }

    // 构建输入变量到一阶单项式划分的映射
    XindexToPartition.recount(XCount);
    XindexToPartition.value((size_t)(-1));

    // 根据一阶不变量构建划分映射，并检查每个输入变量是否唯一地属于一个划分
    for (size_t p = 0; p < Order1.count(); ++p)
    {
        const FIexpress& one = Order1[p];
        if (one.order != 1)
        {
            continue;
        }

        if (one.items.count() < one.ItemCount)
        {
            throw std::runtime_error("SFI build failed: malformed order-1 FI items.");
        }

        for (size_t t = 0; t < one.ItemCount; ++t)
        {
            const size_t x = one.items[t];
            if (x >= XCount)
            {
                throw std::runtime_error("SFI build failed: XIndex out of range while building partition map.");
            }

            if (XindexToPartition[x] != (size_t)(-1) && XindexToPartition[x] != p)
            {
                throw std::runtime_error("SFI build failed: one XIndex belongs to multiple order-1 partitions.");
            }

            XindexToPartition[x] = p;
        }
    }

    // 枚举每个FI的函数组合
    for (size_t i = 0; i < hereItems.count(); ++i)
    {
        const FIexpress& srcExpr = hereItems[i];
        const int order = srcExpr.order;
        if (order <= 0)
        {
            continue;
        }

        // 检查当前阶数是否在提供的设置范围内
        if ((size_t)order > settings.count())
        {
            continue;
        }

        const Setting& setting = settings[(size_t)order - 1];
        const size_t funcCount = setting.sum();
        const vector<size_t>& srcPartion = herePartions[i];

        if (srcPartion.count() != SourceOrder1Count)
        {
            throw std::runtime_error("SFI build failed: partion width does not match SourceOrder1Count.");
        }

        // 统计当前FI的来源划分数量（即涉及多少个不同的一阶单项式划分）
        const size_t sourceCount = CountNonZero(srcPartion);
        if (sourceCount == 0 || funcCount == 0)
        {
            continue;
        }

        // 构建来源划分到函数组合槽位的映射
        vector<size_t> partitionToSlot;
        partitionToSlot.recount(SourceOrder1Count);
        partitionToSlot.value((size_t)(-1));
        size_t slotCount = 0;
        for (size_t p = 0; p < srcPartion.count(); ++p)
        {
            if (srcPartion[p] > 0)
            {
                partitionToSlot[p] = slotCount;
                ++slotCount;
            }
        }

        if (slotCount != sourceCount)
        {
            throw std::runtime_error("SFI build failed: source partition slot mapping mismatch.");
        }

        const size_t expectedItems = (size_t)order * srcExpr.ItemCount;
        if (srcExpr.items.count() < expectedItems)
        {
            throw std::runtime_error("SFI build failed: malformed FI monomial storage.");
        }

        vector<size_t> funcIDs;
        funcIDs.recount(sourceCount);
        funcIDs.value(0);

        while (true)
        {
            SFIformula formula;
            formula.order = order;
            formula.ItemCount = srcExpr.ItemCount;
            formula.partion = srcPartion;
            formula.SourceCount = (int)sourceCount;
            formula.items.recount(0);

            for (size_t mono = 0; mono < srcExpr.ItemCount; ++mono)
            {
                const size_t base = mono * (size_t)order;
                for (int k = 0; k < order; ++k)
                {
                    const size_t x = srcExpr.items[base + (size_t)k];
                    if (x >= XCount)
                    {
                        throw std::runtime_error("SFI build failed: XIndex out of range in FI monomial.");
                    }

                    const size_t partition = XindexToPartition[x];
                    if (partition == (size_t)(-1))
                    {
                        throw std::runtime_error("SFI build failed: XIndex not found in order-1 partition map.");
                    }

                    if (partition >= partitionToSlot.count())
                    {
                        throw std::runtime_error("SFI build failed: partition index out of range.");
                    }

                    const size_t slot = partitionToSlot[partition];
                    if (slot == (size_t)(-1) || slot >= funcIDs.count())
                    {
                        throw std::runtime_error("SFI build failed: partition slot not active for current FI.");
                    }

                    const size_t id = funcIDs[slot];
                    SFIitem item;
                    item.XIndex = x;
                    item.function = setting.GetFunc(id);
                    item.power = (int)setting.GetIndex(id);
                    item.factor = 1.0;
                    formula.items.append(item);
                }
            }

            formulas.append(formula);
            if (formula.order > highestOrder)
            {
                highestOrder = formula.order;
            }
            if (formula.SourceCount > HighestSource)
            {
                HighestSource = formula.SourceCount;
            }

            if (!NextMixedRadix(funcIDs, funcCount))
            {
                break;
            }
        }
    }

    BuildItemCachePlan();
}

void SFIexpresses::demo(FILE* fp) const
{
    fprintf(fp,
        "SFIexpresses: total=%zu, highestOrder=%d, HighestSource=%d, XCount=%zu, SourceOrder1Count=%zu\n",
        formulas.count(), highestOrder, HighestSource, XCount, SourceOrder1Count);
    fprintf(fp, "  Power semantics: stored as 0-based index, effective value in demo/compute/codegen is (power + 1).\n");

    fprintf(fp, "  Settings by order:\n");
    if (settings.count() == 0)
    {
        fprintf(fp, "    (none)\n");
    }
    for (size_t i = 0; i < settings.count(); ++i)
    {
        const Setting& s = settings[i];
        fprintf(fp,
            "    Order %zu: poly=%u reciprocal=%u exp=%u gaussian=%u cos=%u sin=%u sum=%zu\n",
            i + 1, s.poly, s.reciprocal, s.exp, s.gaussian, s.cos, s.sin, s.sum());
    }

    fprintf(fp, "  XindexToPartition map (x -> p):\n    ");
    if (XindexToPartition.count() == 0)
    {
        fprintf(fp, "(empty)\n");
    }
    else
    {
        for (size_t x = 0; x < XindexToPartition.count(); ++x)
        {
            fprintf(fp, "%zu->", x);
            if (XindexToPartition[x] == (size_t)(-1))
            {
                fprintf(fp, "NA");
            }
            else
            {
                fprintf(fp, "%zu", XindexToPartition[x]);
            }
            if (x + 1 < XindexToPartition.count())
            {
                fprintf(fp, ", ");
            }
        }
        fprintf(fp, "\n");
    }

    size_t accLength = 0;
    for (size_t i = 0; i < formulas.count(); ++i)
    {
        const SFIformula& f = formulas[i];
        const size_t currentLength = f.items.count();
        accLength += currentLength;

        fprintf(fp,
            "  SFIformula %zu (length=%zu, acc=%zu): order=%d, ItemCount=%zu, SourceCount=%d\n",
            i, currentLength, accLength, f.order, f.ItemCount, f.SourceCount);

        fprintf(fp, "    partion: [");
        for (size_t p = 0; p < f.partion.count(); ++p)
        {
            fprintf(fp, "%zu", f.partion[p]);
            if (p + 1 < f.partion.count())
            {
                fprintf(fp, ", ");
            }
        }
        fprintf(fp, "]\n");

        if (f.ItemCount == 0 || f.order <= 0 || f.items.count() == 0)
        {
            fprintf(fp, "    expr: (empty)\n");
            continue;
        }

        fprintf(fp, "    expr: ");
        const size_t monomialCount = f.ItemCount;
        const size_t order = (size_t)f.order;
        if (f.order == 1)
        {
            for (size_t mono = 0; mono < monomialCount; ++mono)
            {
                const size_t base = mono * order;
                for (size_t k = 0; k < order; ++k)
                {
                    if (base + k >= f.items.count())
                    {
                        fprintf(fp, "[malformed]");
                        break;
                    }
                    PrintSFIItemExpr(fp, f.items[base + k]);
                    if (k + 1 < order)
                    {
                        fprintf(fp, " * ");
                    }
                }
                if (mono + 1 < monomialCount)
                {
                    fprintf(fp, " + ");
                }
            }
        }
        else
        {
            const size_t base = 0;
            for (size_t k = 0; k < order; ++k)
            {
                if (base + k >= f.items.count())
                {
                    fprintf(fp, "[malformed]");
                    break;
                }
                PrintSFIItemExpr(fp, f.items[base + k]);
                if (k + 1 < order)
                {
                    fprintf(fp, " * ");
                }
            }
            if (monomialCount > 1)
            {
                fprintf(fp, " + ...");
            }
        }
        fprintf(fp, "\n");

        // 附加每个组合槽位最常见函数类型提示（便于快速排查构造结果）
        if (f.items.count() > 0)
        {
            const int displayPower = f.items[0].power + 1;
            fprintf(fp, "    first-item: func=%s, XIndex=%zu, power=%d, factor=%g\n",
                FuncName(f.items[0].function), f.items[0].XIndex, displayPower, f.items[0].factor);
        }
    }

    fflush(fp);
}

int SFIexpresses::compute(const double* input, size_t ldi, size_t rowi, size_t coli,
    double* output, size_t ldo, size_t rowo, size_t colo) const
{
    return compute(input, ldi, rowi, coli, output, ldo, rowo, colo, false);
}

int SFIexpresses::compute(const double* input, size_t ldi, size_t rowi, size_t coli,
    double* output, size_t ldo, size_t rowo, size_t colo, bool PowerNormalization) const
{
    if (rowi != rowo)
    {
        return -1;
    }

    if (coli != XCount)
    {
        return -3;
    }

    if (colo != formulas.count())
    {
        return -4;
    }

    if (formulas.count() == 0)
    {
        return 0;
    }

    if (formulas.count() > 0 && itemCacheKeys.count() == 0)
    {
        for (size_t r = 0; r < rowi; ++r)
        {
            const double* inRow = input + r * ldi;
            double* outRow = output + r * ldo;
            for (size_t fi = 0; fi < formulas.count(); ++fi)
            {
                outRow[fi] = formulas[fi].compute(inRow, PowerNormalization);
            }
        }
        return 0;
    }

    vector<double> caches[6];
    for (size_t f = 0; f < 6; ++f)
    {
        caches[f].recount(powerPlans[f].cacheSize);
    }

    vector<double> itemValues;
    itemValues.recount(itemCacheKeys.count());

    for (size_t r = 0; r < rowi; ++r)
    {
        const double* inRow = input + r * ldi;
        double* outRow = output + r * ldo;

        FillPowerCache(caches[FuncIndex(analyzer::poly)], powerPlans[FuncIndex(analyzer::poly)], inRow, analyzer::poly, XCount);
        FillPowerCache(caches[FuncIndex(analyzer::reciprocal)], powerPlans[FuncIndex(analyzer::reciprocal)], inRow, analyzer::reciprocal, XCount);
        FillPowerCache(caches[FuncIndex(analyzer::exp)], powerPlans[FuncIndex(analyzer::exp)], inRow, analyzer::exp, XCount);
        FillPowerCache(caches[FuncIndex(analyzer::gaussian)], powerPlans[FuncIndex(analyzer::gaussian)], inRow, analyzer::gaussian, XCount);
        FillTrigCaches(
            caches[FuncIndex(analyzer::cos)], powerPlans[FuncIndex(analyzer::cos)],
            caches[FuncIndex(analyzer::sin)], powerPlans[FuncIndex(analyzer::sin)],
            inRow, XCount);

        for (size_t keyIndex = 0; keyIndex < itemCacheKeys.count(); ++keyIndex)
        {
            itemValues[keyIndex] = CachedSFIItemValue(itemCacheKeys[keyIndex], caches, powerPlans);
        }

        for (size_t fi = 0; fi < formulas.count(); ++fi)
        {
            const SFIformula& f = formulas[fi];
            if (f.order <= 0)
            {
                outRow[fi] = 0.0;
                continue;
            }

            const size_t order_sz = (size_t)f.order;
            const size_t expected = f.ItemCount * order_sz;
            if (f.items.count() < expected)
            {
                return -2;
            }

            double acc = 0.0;
            for (size_t mono = 0; mono < f.ItemCount; ++mono)
            {
                double term = 1.0;
                const size_t base = mono * order_sz;
                for (size_t k = 0; k < order_sz; ++k)
                {
                    const size_t itemIndex = base + k;
                    const size_t cacheIndex = f.items[itemIndex].cacheIndex;
                    if (cacheIndex >= itemValues.count())
                    {
                        return -2;
                    }
                    term *= itemValues[cacheIndex];
                }
                acc += term;
            }

            outRow[fi] = NormalizeSFIValue(
                acc, PowerNormalization, f.positiveDefiniteCached,
                f.sumItemOrderCached, f.normalizationPower);
        }
    }

    return 0;
}
