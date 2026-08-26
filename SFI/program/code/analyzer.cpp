#include "analyzer.h"
#include <cmath>

using namespace analyzer;

static double NormalizeByOrder(double base, bool powerNormalization, int order, double exponent)
{
    if (!powerNormalization || order <= 1 || base < 0.0)
    {
        return base;
    }

    if (order == 2)
    {
        return std::sqrt(base);
    }

    return std::pow(base, exponent);
}

void FIexpress::move(FIexpress& src)
{
    order = src.order;
    ItemCount = src.ItemCount;
    items.move(src.items);
    compactFactors.move(src.compactFactors);
    compactMonomialBegin.move(src.compactMonomialBegin);
    compactMonomialCount.move(src.compactMonomialCount);
    normalizationPower = src.normalizationPower;
    src.order = 0;
    src.ItemCount = 0;
    src.normalizationPower = 1.0;
}

double FIexpress::compute_bare(const vector<double>& values) const
{
    double result = 0.0;
    // 遍历每个单项式
    for (size_t i = 0; i < ItemCount; ++i)
    {
        double term = 1.0;  // 当前单项式的值，系数为1.0
        // 每个单项式占order个元素，每个元素是变量的索引
        for (int j = 0; j < order; ++j)
        {
            size_t varIndex = items[i * order + j];  // 获取变量索引
            term *= 1.0 / values[varIndex];                // 乘以对应变量的值
        }
        result += term;  // 累加单项式到结果
    }
    return result;
}

double FIexpress::compute(const vector<double>& values, bool PowerNormalization) const
{
    const double base = compute_bare(values);
    return NormalizeByOrder(base, PowerNormalization, order, normalizationPower);
}

double FIexpress::compute(const double* values, bool PowerNormalization) const
{
    const double base = compute_bare(values);
    return NormalizeByOrder(base, PowerNormalization, order, normalizationPower);
}

void FIexpress::buildRuntimePlan(void)
{
    compactFactors.recount(0);
    compactMonomialBegin.recount(ItemCount);
    compactMonomialCount.recount(ItemCount);
    normalizationPower = (order > 0) ? (1.0 / static_cast<double>(order)) : 1.0;

    if (order <= 0 || ItemCount == 0)
    {
        return;
    }

    const size_t order_sz = static_cast<size_t>(order);
    for (size_t mono = 0; mono < ItemCount; ++mono)
    {
        const size_t base = mono * order_sz;
        compactMonomialBegin[mono] = compactFactors.count();

        for (size_t k = 0; k < order_sz; ++k)
        {
            const size_t x = items[base + k];
            bool seen = false;
            for (size_t prev = 0; prev < k; ++prev)
            {
                if (items[base + prev] == x)
                {
                    seen = true;
                    break;
                }
            }

            if (seen)
            {
                continue;
            }

            unsigned int power = 1;
            for (size_t next = k + 1; next < order_sz; ++next)
            {
                if (items[base + next] == x)
                {
                    ++power;
                }
            }

            compactFactors.append(FIcompactFactor(x, power));
        }

        compactMonomialCount[mono] = compactFactors.count() - compactMonomialBegin[mono];
    }
}

double FIexpress::compute_compact(const double* reciprocalPowers, const size_t* reciprocalPowerOffset, bool PowerNormalization) const
{
    if (compactMonomialBegin.count() != ItemCount || compactMonomialCount.count() != ItemCount)
    {
        double result = 0.0;
        for (size_t mono = 0; mono < ItemCount; ++mono)
        {
            double term = 1.0;
            const size_t base = mono * static_cast<size_t>(order);
            for (int k = 0; k < order; ++k)
            {
                const size_t x = items[base + static_cast<size_t>(k)];
                term *= reciprocalPowers[reciprocalPowerOffset[x] + 1];
            }
            result += term;
        }
        return NormalizeByOrder(result, PowerNormalization, order, normalizationPower);
    }

    double result = 0.0;
    for (size_t mono = 0; mono < ItemCount; ++mono)
    {
        double term = 1.0;
        const size_t begin = compactMonomialBegin[mono];
        const size_t count = compactMonomialCount[mono];
        for (size_t k = 0; k < count; ++k)
        {
            const FIcompactFactor& f = compactFactors[begin + k];
            term *= reciprocalPowers[reciprocalPowerOffset[f.XIndex] + f.power];
        }
        result += term;
    }

    return NormalizeByOrder(result, PowerNormalization, order, normalizationPower);
}

int FIexpress::AppendMonomial(const vector<size_t>& monomial)
{
    // 如果items数组为空，则设置order为monomial的长度
    if (items.empty())
    {
        order = monomial.size();
    }
    // 如果items数组不为空，且monomial的长度与order不相同，则返回-1
    else if (monomial.size() != static_cast<size_t>(order) || monomial.empty())
    {
        return -1;
    }
    
    // 将单项式的指数信息追加到items数组
    items.append(monomial);
    // 增加ItemCount
    ItemCount++;
    normalizationPower = (order > 0) ? (1.0 / static_cast<double>(order)) : 1.0;
    
    return 0;
}

void FIexpresses::move(FIexpresses& src)
{
    items.move(src.items);
    XCount = src.XCount;
    highestOrder = src.highestOrder;
    OrderCount.move(src.OrderCount);
    Order1Count = src.Order1Count;
    partions.move(src.partions);
    CrossItem.move(src.CrossItem);
    maxReciprocalPower.move(src.maxReciprocalPower);
    reciprocalPowerOffset.move(src.reciprocalPowerOffset);
    reciprocalPowerCacheSize = src.reciprocalPowerCacheSize;
    src.XCount = 0;
    src.highestOrder = 0;
    src.Order1Count = 0;
    src.reciprocalPowerCacheSize = 0;
}

void FIexpresses::BuildRuntimePlans(void)
{
    for (size_t i = 0; i < items.count(); ++i)
    {
        items[i].buildRuntimePlan();
    }

    maxReciprocalPower.recount(XCount);
    maxReciprocalPower.value(0);
    reciprocalPowerOffset.recount(XCount);
    reciprocalPowerOffset.value(0);
    reciprocalPowerCacheSize = 0;

    for (size_t i = 0; i < items.count(); ++i)
    {
        const vector<FIcompactFactor>& factors = items[i].compactFactors;
        for (size_t j = 0; j < factors.count(); ++j)
        {
            const size_t x = factors[j].XIndex;
            if (x < XCount && factors[j].power > maxReciprocalPower[x])
            {
                maxReciprocalPower[x] = factors[j].power;
            }
        }
    }

    for (size_t x = 0; x < XCount; ++x)
    {
        if (maxReciprocalPower[x] > 0)
        {
            reciprocalPowerOffset[x] = reciprocalPowerCacheSize;
            reciprocalPowerCacheSize += static_cast<size_t>(maxReciprocalPower[x]) + 1;
        }
    }
}
size_t FIexpress::getXCount() const
{
    if (items.count() == 0)
    {
        return 0;
    }
    
    size_t maxIndex = 0;
    for (size_t i = 0; i < items.count(); i++)
    {
        if (items[i] > maxIndex)
        {
            maxIndex = items[i];
        }
    }
    
    return maxIndex;
}

int FIexpresses::compute(const double*input, size_t ldi, size_t rowi, size_t coli, double* output, size_t ldo, size_t rowo, size_t colo) const
{
    return compute(input, ldi, rowi, coli, output, ldo, rowo, colo, false);
}

int FIexpresses::compute(const double*input, size_t ldi, size_t rowi, size_t coli, double* output, size_t ldo, size_t rowo, size_t colo, bool PowerNormalization) const
{
    // 检查输入输出的行数是否匹配
    if (rowi != rowo) {
        return -1;
    }
    
    // 检查列数是否与输入数据的维度匹配
    if (coli != XCount) {
        return -3;
    }
    
    // 检查输出数据的维度是否与所有FIexpress的次数总和匹配
    if (colo != items.size()) {
        return -4;
    }

    if (items.size() == 0)
    {
        return 0;
    }

    if (maxReciprocalPower.count() != XCount || reciprocalPowerOffset.count() != XCount)
    {
        for (size_t i = 0; i < rowi; ++i)
        {
            const double* currentInput = input + i * ldi;
            double* currentOutput = output + i * ldo;
            for (size_t j = 0; j < items.size(); ++j)
            {
                currentOutput[j] = items[j].compute(currentInput, PowerNormalization);
            }
        }
        return 0;
    }
    
    vector<double> reciprocalPowerCache;
    reciprocalPowerCache.recount(reciprocalPowerCacheSize);

    // 遍历每条输入数据
    for (size_t i = 0; i < rowi; ++i) {
        // 计算当前输入数据的起始位置
        const double* currentInput = input + i * ldi;
        // 计算当前输出数据的起始位置
        double* currentOutput = output + i * ldo;

        for (size_t x = 0; x < XCount; ++x)
        {
            const unsigned int maxPower = maxReciprocalPower[x];
            if (maxPower == 0)
            {
                continue;
            }

            const size_t offset = reciprocalPowerOffset[x];
            const double base = 1.0 / currentInput[x];
            reciprocalPowerCache[offset] = 1.0;
            reciprocalPowerCache[offset + 1] = base;
            for (unsigned int p = 2; p <= maxPower; ++p)
            {
                reciprocalPowerCache[offset + p] = reciprocalPowerCache[offset + p - 1] * base;
            }
        }
        
        // 对每条数据，计算所有FIexpress对象的值
        for (size_t j = 0; j < items.size(); ++j) {
            // 计算当前FIexpress的值
            double value = items[j].compute_compact(
                reciprocalPowerCache.ptr(), reciprocalPowerOffset.ptr(), PowerNormalization);
            // 将计算结果存储到输出矩阵的对应位置
            currentOutput[j] = value;
        }
    }
    
    return 0;
}

int FIexpresses::computeCosTransform(const double* cosineInput, size_t ldi, size_t rowi, size_t coli,
    double* output, size_t ldo, size_t rowo, size_t colo, const vector<unsigned int>& settings_cos) const
{
    // 检查输入输出的行数是否匹配
    if (rowi != rowo) {
        return -1;
    }

    // 检查列数是否与输入数据的维度匹配
    if (coli != XCount) {
        return -3;
    }

    // 计算期望的输出列数并生成变换计划
    vector<FIcosTransformEntry> plan;
    size_t expectedColo = 0;
    unsigned int maxHarmonic = 0;
    for (size_t fi = 0; fi < items.size(); ++fi) {
        const int order = items[fi].getOrder();
        if (order > 0 && (size_t)order <= settings_cos.count()) {
            const unsigned int harmonicCount = settings_cos[(size_t)order - 1];
            if (harmonicCount > 0)
            {
                FIcosTransformEntry entry;
                entry.exprIndex = fi;
                entry.outputOffset = expectedColo;
                entry.harmonicCount = harmonicCount;
                plan.append(entry);
                if (harmonicCount > maxHarmonic)
                {
                    maxHarmonic = harmonicCount;
                }
            }
            expectedColo += harmonicCount;
        }
    }

    if (colo != expectedColo) {
        return -4;
    }

    vector<double> chebyshevCache;
    const size_t chebyshevStride = static_cast<size_t>(maxHarmonic) + 1;
    if (maxHarmonic > 0)
    {
        chebyshevCache.recount(coli * chebyshevStride);
    }

    // 遍历每条输入数据（每个构型）
    for (size_t r = 0; r < rowi; ++r) {
        const double* cosineRow = cosineInput + r * ldi;
        double* outputRow = output + r * ldo;

        if (maxHarmonic > 0)
        {
            for (size_t x = 0; x < coli; ++x)
            {
                const size_t base = x * chebyshevStride;
                const double cosine = cosineRow[x];
                chebyshevCache[base] = 1.0;
                chebyshevCache[base + 1] = cosine;
                for (unsigned int n = 2; n <= maxHarmonic; ++n)
                {
                    chebyshevCache[base + n] =
                        2.0 * cosine * chebyshevCache[base + n - 1] - chebyshevCache[base + n - 2];
                }
            }
        }

        // 遍历每个使用余弦变量的 FI（键角或二面角）
        for (size_t pi = 0; pi < plan.count(); ++pi) {
            const FIcosTransformEntry& entry = plan[pi];
            const FIexpress& cosineExpr = items[entry.exprIndex];
            const int order = cosineExpr.getOrder();
            const unsigned int harmonicCount = entry.harmonicCount;
            const size_t outBase = entry.outputOffset;

            // 对任意角变量 alpha，T_n(cos(alpha)) = cos(n*alpha)。
            for (unsigned int n = 1; n <= harmonicCount; ++n) {
                double cos_sum = 0.0;
                // 遍历 FI 的每个单项式
                for (size_t mono = 0; mono < cosineExpr.getItemCount(); ++mono) {
                    double term = 1.0;
                    const size_t base = mono * (size_t)order;
                    // 对单项式中的每个余弦变量应用 T_n。
                    for (int k = 0; k < order; ++k) {
                        const size_t cosineIdx = cosineExpr.getItems()[base + (size_t)k];
                        if (cosineIdx >= coli) {
                            return -5; // 索引越界
                        }
                        term *= chebyshevCache[cosineIdx * chebyshevStride + n];
                    }
                    cos_sum += term;
                }
                outputRow[outBase + (size_t)n - 1] = cos_sum;
            }
        }
    }

    return 0;
}

int FIexpresses::computeAngleCosTransform(const double* angleCosineInput, size_t ldi, size_t rowi, size_t coli,
    double* output, size_t ldo, size_t rowo, size_t colo, const vector<unsigned int>& settingsA_cos) const
{
    return computeCosTransform(angleCosineInput, ldi, rowi, coli,
        output, ldo, rowo, colo, settingsA_cos);
}


void FIexpress::demo(FILE*fp) const
{
    fprintf(fp, "FIexpress: order=%d, ItemCount=%zu, polynomial:\n\t", order, ItemCount);
    for (size_t i = 0; i < ItemCount; ++i) 
    {
            for (int j = 0; j < order; ++j) {
                size_t varIndex = items[i * order + j];
                fprintf(fp, "x[%zu]", varIndex);
                if (j + 1 < order) {
                    fprintf(fp, " * ");
                }
            }
            if (i + 1 < ItemCount) {
                fprintf(fp, " + ");
            }
            else
                fprintf(fp, ";\n");
    }
    fflush(fp);
}

void FIexpress::DemoSimple(FILE*fp) const
{
    fprintf(fp, "FIexpress: order=%d, ItemCount=%zu\n", order, ItemCount);
    if (ItemCount > 0) {
        fprintf(fp, "  ");
        for (int j = 0; j < order; ++j) {
            size_t varIndex = items[j];
            fprintf(fp, "x[%zu]", varIndex);
            if (j + 1 < order) {
                fprintf(fp, " * ");
            }
        }
        if (ItemCount > 1) {
            fprintf(fp, " + ...");
        }
        fprintf(fp, "\n");
    }
    fflush(fp);
}

void FIexpresses::demo(FILE*fp) const
{
    fprintf(fp, "FIexpresses: total=%zu, highestOrder=%d, XCount=%zu, Order1Count=%zu\n", items.size(), highestOrder, XCount, Order1Count);
    
    size_t accLength = 0;
    for (size_t i = 0; i < items.size(); ++i) {
        size_t currentLength = items[i].order * items[i].ItemCount;
        accLength += currentLength;
        fprintf(fp, "  FIexpress %zu (length=%zu, acc=%zu):", i, currentLength, accLength);
        if (items[i].order == 1) {
            items[i].demo(fp);
        } else {
            items[i].DemoSimple(fp);
        }
    }
    
    // 无论什么情况都要打印 OrderCount
    fprintf(fp, "  Order distribution:\n");
    for (size_t i = 0; i < OrderCount.size(); ++i) {
        if (OrderCount[i] > 0) {
            fprintf(fp, "    Order %zu: %zu polynomials\n", i, OrderCount[i]);
        }
    }

    if (partions.size() > 0) {
        fprintf(fp, "  Partions:\n");
        for (size_t i = 0; i < partions.size(); ++i) {
            fprintf(fp, "    FIexpress %zu partion: [", i);
            for (size_t j = 0; j < partions[i].size(); ++j) {
                fprintf(fp, "%zu", partions[i][j]);
                if (j + 1 < partions[i].size()) {
                    fprintf(fp, ", ");
                }
            }
            fprintf(fp, "]\n");
        }
    }
    
    fflush(fp);
}

void errorinfo::demo(FILE*fp) const
{
    fprintf(fp, "line %zu, %s, expect %s\n", line, msg, symbol);
    fflush(fp);
}

void FIexpresses::SortByOrder(void)
{
    // 使用简单的冒泡排序对items进行排序，按照order从小到大
    for (size_t i = 0; i < items.count(); ++i) {
        for (size_t j = 0; j < items.count() - 1 - i; ++j) {
            if (items[j].getOrder() > items[j + 1].getOrder()) {
                // 交换items[j]和items[j + 1]
                FIexpress temp;
                temp.move(items[j]);
                items[j].move(items[j + 1]);
                items[j + 1].move(temp);
            }
        }
    }
}

void FIexpresses::cutoffByOrder(int max_order, bool enable_crossitem)
{
    vector<FIexpress> newItems;
    for (size_t i = 0; i < items.count(); ++i) {
        bool keep = true;
        if (items[i].getOrder() > max_order) {
            keep = false;
        }

        // Check crossitem condition
        if (keep && enable_crossitem) {
            if (i < CrossItem.size()) {
                keep = CrossItem[i];
            }
        }
        
        if (keep) {
            newItems.append(items[i]);
        }
    }
    
    // Update items
    items.move(newItems);
    
    // Recalculate highestOrder and OrderCount
    OrderAnalysis();
    
    // Re-analyze partions
    analyze();
    BuildRuntimePlans();
}

void FIexpresses::cutoffByWorkload(size_t max_workload, bool enable_crossitem)
{
    vector<FIexpress> newItems;
    size_t accLength = 0;
    
    for (size_t i = 0; i < items.count(); ++i) {
        bool keep = true;
        size_t currentLength = items[i].getOrder() * items[i].getItemCount();
        
        if (accLength + currentLength > max_workload) {
            keep = false; 
        }

        // Check crossitem condition
        if (keep && enable_crossitem) {
            if (i < CrossItem.size()) {
                keep = CrossItem[i];
            }
        }
        
        if (keep) {
            newItems.append(items[i]);
            accLength += items[i].getOrder() * items[i].getItemCount();
        }
    }
    
    // Update items
    items.move(newItems);
    
    // Recalculate highestOrder and OrderCount
    OrderAnalysis();
    
    // Re-analyze partions
    analyze();
    BuildRuntimePlans();
}

void FIexpresses::CrossItemAnalysis(void)
{
    CrossItem.recount(items.count());
    
    for (size_t i = 0; i < items.count(); ++i) {
        bool hasDuplicate = false;
        if (items[i].getItemCount() > 0) {
            int order = items[i].getOrder();
            const vector<size_t>& exprItems = items[i].getItems();
            
            // Just check the first monomial (first `order` elements in exprItems)
            for (int p = 0; p < order; ++p)
            {
                for (int q = p + 1; q < order; ++q) 
                {
                    if (exprItems[p] == exprItems[q]) {
                        hasDuplicate = true;
                        break;
                    }
                }
                if (hasDuplicate) break;
            }
        }
        
        CrossItem[i] = !hasDuplicate;
    }
}

void FIexpresses::analyze(void)
{
    // 该函数的目的是通过一阶不变量来划分 N 阶多项式。
    // partions[i][k] 记录了第 i 个多项式的某个代表性单项式中，
    // 包含了多少个属于第 k 个一阶多项式的自变量。
    
    SortByOrder();
    Order1Count = 0;
    partions.recount(0); // 清空以前的划分，以免反复追加
    
    for (size_t i = 0; i < items.count(); i++)
    {
        const FIexpress& expre = items[i];
        if(expre.getOrder() == 1)
        {
            Order1Count++;
        }
    }

    for (size_t i = 0; i < items.count(); i++)
    {
        vector<size_t> partion;
        const FIexpress& expre = items[i];
        size_t order = expre.getOrder();
        
        // 利用置换不变性：一阶不变量的 N 阶单项式构成了 N 阶不变量多项式的一个划分。
        // 因此，只需要检查该多项式的任何一个单项式（这里用了第一个单项式，即前 order 个变量），
        // 就可以计算出它属于哪个一阶不变量单项式的划分。
        
        partion.recount(Order1Count);
        partion.value(0);

        for (size_t j = 0; j < order; j++)
        {
            for (size_t k = 0; k < Order1Count; k++)
            {
                const FIexpress& Order1now_ = items[k];
                size_t site = Order1now_.items.search(expre.items[j]);
                if(site != (size_t)(-1))
                {
                    partion[k]++;
                    break;
                }
            }
        }
        partions.append(partion);
    }
  
    CrossItemAnalysis();
}
