#ifndef _analyzer_h_hgary8re9yhgi8hygreuihgriurhei
#define _analyzer_h_hgary8re9yhgi8hygreuihgriurhei
#include "template.h"
#include <stdio.h>
#include <stdexcept>
//C++03 语法
namespace analyzer
{
    using namespace TemplateSelf;
    struct FIcompactFactor
    {
        typedef void _hx_trivial_destruct_tag;
        typedef void _hx_bitwise_relocatable_tag;
        FIcompactFactor() : XIndex(0), power(0) {}
        FIcompactFactor(size_t x, unsigned int p) : XIndex(x), power(p) {}
        size_t XIndex;
        unsigned int power;
    };

    struct FIcosTransformEntry
    {
        typedef void _hx_trivial_destruct_tag;
        typedef void _hx_bitwise_relocatable_tag;
        FIcosTransformEntry() : exprIndex(0), outputOffset(0), harmonicCount(0) {}
        size_t exprIndex;
        size_t outputOffset;
        unsigned int harmonicCount;
    };

    class FIexpress
    {
        public:
            typedef void _hx_need_explicit_move_tag;
            FIexpress() : order(0), ItemCount(0), normalizationPower(1.0) {}
            ~FIexpress() {}
            FIexpress(const FIexpress& other)
                : order(other.order), ItemCount(other.ItemCount), items(other.items),
                  compactFactors(other.compactFactors), compactMonomialBegin(other.compactMonomialBegin),
                  compactMonomialCount(other.compactMonomialCount), normalizationPower(other.normalizationPower) {}
            FIexpress& operator=(const FIexpress& other)
            {
                if (this != &other)
                {
                    order = other.order;
                    ItemCount = other.ItemCount;
                    items = other.items;
                    compactFactors = other.compactFactors;
                    compactMonomialBegin = other.compactMonomialBegin;
                    compactMonomialCount = other.compactMonomialCount;
                    normalizationPower = other.normalizationPower;
                }
                return *this;
            }
            void move(FIexpress& src);
            friend class FIexpresses;
            friend class SFIexpresses;
        protected:
            int order;//齐次多项式的次数
            size_t ItemCount;//单项式项数
            vector<size_t> items;//大小为ItemCount * order
            vector<FIcompactFactor> compactFactors;
            vector<size_t> compactMonomialBegin;
            vector<size_t> compactMonomialCount;
            double normalizationPower;
            /*
            齐次多项式的存储格式:
            1. 放弃存储常数项，所有项的系数都设为1.0
               - FI(基本不变量)是多元多项式
            2. items数组存储单项式的指数信息
               - 大小为 ItemCount * order
               - 每个单项式必定占 order 个元素，代表order个自变元
               - 例如: order=3 时，items[i*3], items[i*3+1], items[i*3+2] 中存储的三个整数
                 表示第i个单项式 的每一个自变元是对应哪一个变量的索引（名称）
            3. compute_bare()方法计算齐次多项式的值
               - 输入: FI的值向量(values)
               - 输出: 多项式计算结果(系数为1.0的各单项式之和)
            */
        public:
            int getOrder() const { return order; }
            size_t getItemCount() const { return ItemCount; }
            const vector<size_t>& getItems() const { return items; }
            void setOrder(int order) { this->order = order; normalizationPower = (order > 0) ? (1.0 / static_cast<double>(order)) : 1.0; }
            void setItemCount(size_t itemCount) { this->ItemCount = itemCount; }
            void setItems(const vector<size_t>& items) { this->items = items; }
            size_t getXCount() const;
            //返回齐次自变元下标索引中最大的一个，即items存储的最大的变量索引
            
            double compute_bare(const vector<double>& values) const;
            inline double compute_bare(const double* values) const
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
            double compute(const vector<double>& values, bool PowerNormalization) const;
            double compute(const double* values, bool PowerNormalization) const;
            void buildRuntimePlan(void);
            double compute_compact(const double* reciprocalPowers, const size_t* reciprocalPowerOffset, bool PowerNormalization) const;
            inline double compute(const vector<double>& values) const
            {
                return compute(values, false);
            }
            inline double compute(const double* values) const
            {
                return compute(values, false);
            }
            //不做任何检查，直接计算
            int AppendMonomial(const vector<size_t>& monomial);   
            /*
            追加单项式到多项式
            - 输入: monomial 单项式的向量，如果目前items数组为空，则设置order为monomial的长度
            - 如果目前items数组为不空，且monomial的长度与order不相同，则返回-1
            - 输出: 错误码: 0 成功，-1 失败（如指数向量长度错误）
            */
            void demo(FILE*fp = stdout) const;
            void DemoSimple(FILE*fp = stdout) const;
    };
    class FIexpresses
    {
        public:
        typedef void _hx_need_explicit_move_tag;
            FIexpresses() : highestOrder(0), XCount(0), Order1Count(0), reciprocalPowerCacheSize(0) {}
            ~FIexpresses() {}
            FIexpresses(const FIexpresses& other) : items(other.items), highestOrder(other.highestOrder), OrderCount(other.OrderCount), XCount(other.XCount), \
                        Order1Count(other.Order1Count), partions(other.partions), CrossItem(other.CrossItem),
                        maxReciprocalPower(other.maxReciprocalPower), reciprocalPowerOffset(other.reciprocalPowerOffset),
                        reciprocalPowerCacheSize(other.reciprocalPowerCacheSize) {}
            FIexpresses& operator=(const FIexpresses& other)
            {
                if (this != &other)
                {
                    items = other.items;
                    highestOrder = other.highestOrder;
                    OrderCount = other.OrderCount;
                    XCount = other.XCount;
                    Order1Count = other.Order1Count;
                    partions = other.partions;
                    CrossItem = other.CrossItem;
                    maxReciprocalPower = other.maxReciprocalPower;
                    reciprocalPowerOffset = other.reciprocalPowerOffset;
                    reciprocalPowerCacheSize = other.reciprocalPowerCacheSize;
                }
                return *this;
            }
            void move(FIexpresses& src);
        protected:
            vector<FIexpress> items;
            int highestOrder;//最高次数
            vector<size_t> OrderCount;//次数i的多项式数量
            size_t XCount;//变量数量
            size_t Order1Count;//次数为1的多项式数量，
            /*
            一阶不变量构成了对全体键长的划分。
            */
            /*
            partions数组存储了按照一阶不变量对所有多项式进行的划分。
            由于置换不变性，一阶不变量的N阶单项式构成了N阶不变量多项式的一个划分。
            - partions.size() == items.size()，对应于每个不变量多项式。
            - partions[i] 的大小为 Order1Count（一阶多项式的个数）。
            - partions[i][k] 表示第 i 个多项式的代表单项式（如第一个单项式）中，
              包含第 k 个一阶多项式的自变量的次数（个数）。
            */
            vector<vector<size_t> > partions;

            vector<bool> CrossItem;
            vector<unsigned int> maxReciprocalPower;
            vector<size_t> reciprocalPowerOffset;
            size_t reciprocalPowerCacheSize;
            /*
            什么是CrossItem（跨项）：
            首先根据partions，如果有一个划分指标k,满足两个条件，
            首先partions[i][k] > 1，说明第i个多项式的代表单项式中包含了第k个一阶不变量的自变量。
            其次，它的代表单项式（第一个单项式）中属于k的自变量中有重复指标。
            即 类似于 r[0] * r[0] * r[1] 这种单项式中，r[0] 出现了两次。
            在做判断时可以忽略partions,直接检查代表单项式（第一个单项式）中是否有重复的自变量索引。
            如果有这样的指标重复，那么就是false,否则就是true。
            */
        public:
            const vector<FIexpress>& getItems() const { return items; }
            void setItems(const vector<FIexpress>& items) { this->items = items; }
            int getHighestOrder() const { return highestOrder; }
            const vector<size_t>& getOrderCount() const { return OrderCount; }
            size_t NoneZeroPartionCount(size_t i) const 
            { 
                return partions.count(); 
            }
            const vector<vector<size_t> >& getPartions() const { return partions; }
            const vector<bool>& getCrossItem() const { return CrossItem; }
            size_t getOrder1Count() const { return Order1Count; }
            size_t getXCount() const { return XCount; }
        protected:
            void SortByOrder(void);
            void OrderAnalysis(void);
            void CrossItemAnalysis(void);
            void analyze(void);
            void BuildRuntimePlans(void);
        public:
            int compute(const double*input, size_t ldi, size_t rowi, size_t coli, double* output, size_t ldo, size_t rowo, size_t colo) const;
            int compute(const double*input, size_t ldi, size_t rowi, size_t coli, double* output, size_t ldo, size_t rowo, size_t colo, bool PowerNormalization) const;
            int compute(unsigned int threadCount, const double*input, size_t ldi, size_t rowi, size_t coli, double* output, size_t ldo, size_t rowo, size_t colo) const;
            int compute(unsigned int threadCount, const double*input, size_t ldi, size_t rowi, size_t coli, double* output, size_t ldo, size_t rowo, size_t colo, bool PowerNormalization) const;
            int computeAngleCosTransform(const double* angleCosineInput, size_t ldi, size_t rowi, size_t coli,
                double* output, size_t ldo, size_t rowo, size_t colo, const vector<unsigned int>& settingsA_cos) const;
            int computeAngleCosTransform(unsigned int threadCount, const double* angleCosineInput, size_t ldi, size_t rowi, size_t coli,
                double* output, size_t ldo, size_t rowo, size_t colo, const vector<unsigned int>& settingsA_cos) const;
            int computeCosTransform(const double* cosineInput, size_t ldi, size_t rowi, size_t coli,
                double* output, size_t ldo, size_t rowo, size_t colo, const vector<unsigned int>& settings_cos) const;
            int computeCosTransform(unsigned int threadCount, const double* cosineInput, size_t ldi, size_t rowi, size_t coli,
                double* output, size_t ldo, size_t rowo, size_t colo, const vector<unsigned int>& settings_cos) const;
            void cutoffByOrder(int max_order, bool enable_crossitem);
            void cutoffByWorkload(size_t max_workload, bool enable_crossitem);
            /*
            数据转换函数，将多元多项式的输入转为输出，并且一次转换多条数据，每条数据占据矩阵的一行的开头位置。
            数据矩阵的存储方式说明：坚定的使用行主元存储，即每个元素的索引为 row * ld + col
            
            参数说明：
            - input: 输入矩阵指针，存储原始数据（如键长坐标）
            - ldi: 输入矩阵的领先维度（每行的元素个数）
            - rowi: 输入数据的行数（要处理的数据条数）
            - coli: 输入数据的列数（每条数据的维度）
            - output: 输出矩阵指针，存储转换后的数据（PIP多项式值）
            - ldo: 输出矩阵的领先维度（每行的元素个数）
            - rowo: 输出数据的行数（应与rowi相同）
            - colo: 输出数据的列数（PIP多项式的个数）
            - threadCount: 线程数量（默认1）
            工作原理：
            1. 遍历每条输入数据
            2. 对每条数据，计算所有FIexpress对象的值
            3. 将计算结果存储到输出矩阵的对应位置
            
            检查：
            - 输入输出的行数应匹配（rowi == rowo） 违反则返回-1
            - 输入数据的维度应满足所有FIexpress的计算需求 违反则返回-2
            - 列数应与输入数据的维度匹配（coli == XCount） 违反则返回-3
            - 输出数据的维度应与所有FIexpress的次数总和匹配（colo == items.size()) 违反则返回-4
            
            返回值：
            - 处理的成功状态或错误码（如果有）
            */
            int build(FILE*fp);
            /*
            从文件中读取FIexpress对象的表达式，构建FIexpresses对象。
            参数说明：
            - fp: 输入文件指针，用于读取表达式
            - 处理的成功状态或错误码（如果有）
            文件的文法记录在data/FIlex.txt中，文法分析使用LR解析，解析动作表格和词法分析器表格在
            code/sheet.cpp中
            */
            int printCcode(FILE*fp) const;
            /*
            将这个FIexpresses对象转换为C语言代码，用于计算PIP多项式的值。
            参数说明：
            - fp: 输出文件指针，用于存储生成的C语言代码
            输出的行数的声明是
                void compute(const double* inpput, double* output)
                {
                }
            逐一计算每个多项式的值并写入output数组
            */
            int printFortrancode(FILE*fp) const;
            /*
            将这个FIexpresses对象转换为Fortran语言代码，用于计算PIP多项式的值。
            参数说明：
            - fp: 输出文件指针，用于存储生成的Fortran语言代码
            生成的代码布局：
                subroutine compute(input, output)
                    implicit none
                    real*8, intent(in) :: input(:)
                    real*8, intent(out) :: output(:)
                    real*8 :: temp
                    integer :: i
                    
                    ! 计算第0个多项式
                    temp = 0.0d0
                    temp = temp + input(1) * input(2)
                    temp = temp + input(3) * input(4)
                    output(1) = temp
                    
                    ! 计算第1个多项式
                    temp = 0.0d0
                    temp = temp + input(1) * input(3)
                    output(2) = temp
                    
                    ...
                end subroutine compute
            每个多项式占一个独立的计算块，使用临时变量temp累加所有单项式的值，
            最后将结果写入output数组的对应位置。
            */
            void demo(FILE*fp = stdout) const;

            void print(FILE*fp) const;
            /*
            demo 等成员是输出多项式的有关信息在屏幕上给使用者看的。
            print C code 和 Fortran code 则是输出代码文件的形式给使用者的。
            生成的代码文件是用户真正用来调用的，demo只是给用户看的。

            print则不生成代码，也不给用户看，而是生成和输入文件格式一致的文本，把此处储存的多项式
            按照原格式保存到一个新文件中的接口。不输出任何额外的附加信息。

            输出的格式示例如下

            ```
            P[0] = r[0] + r[1] + r[2] + r[3];
            P[1] = r[4] + r[5] + r[6] + r[7] + r[8] + r[9];
            P[2] = r[0] * r[1] + r[0] * r[2] + r[0] * r[3] + r[1] * r[2] + r[1] * r[3] + r[2] * r[3];
            P[3] = r[0] * r[7] + r[0] * r[8] + r[0] * r[9] + r[1] * r[5] + r[1] * r[6] + r[1] * r[9] + r[2] * r[4] + r[2] * r[6] + r[2] * r[8] + r[3] * r[4] + r[3] * r[5] + r[3] * r[7];
            P[4] = r[4] * r[5] + r[4] * r[6] + r[4] * r[7] + r[4] * r[8] + r[5] * r[6] + r[5] * r[7] + r[5] * r[9] + r[6] * r[8] + r[6] * r[9] + r[7] * r[8] + r[7] * r[9] + r[8] * r[9];
            P[5] = r[4] * r[9] + r[5] * r[8] + r[6] * r[7];
            ```

            */
    };
}
//=================================SFI=============================
namespace analyzer
{
    using namespace TemplateSelf;
    enum func
    {
        poly,
		reciprocal,
		exp,
		gaussian,
		cos,
		sin,
    };

    struct SFIitemKey
    {
        typedef void _hx_trivial_destruct_tag;
        typedef void _hx_bitwise_relocatable_tag;
        SFIitemKey() : XIndex(0), effectivePower(0), factor(1.0), function(poly) {}
        size_t XIndex;
        int effectivePower;
        double factor;
        func function;
    };

    struct SFIpowerPlan
    {
        typedef void _hx_need_explicit_move_tag;
        SFIpowerPlan() : cacheSize(0) {}
        SFIpowerPlan(const SFIpowerPlan& other)
            : maxPower(other.maxPower), offset(other.offset), cacheSize(other.cacheSize) {}
        SFIpowerPlan& operator=(const SFIpowerPlan& other)
        {
            if (this != &other)
            {
                maxPower = other.maxPower;
                offset = other.offset;
                cacheSize = other.cacheSize;
            }
            return *this;
        }
        void move(SFIpowerPlan& src)
        {
            maxPower.move(src.maxPower);
            offset.move(src.offset);
            cacheSize = src.cacheSize;
            src.cacheSize = 0;
        }
        vector<unsigned int> maxPower;
        vector<size_t> offset;
        size_t cacheSize;
    };

    //四个类的构造，copy constructor, copy assignment operator,  析构，move(if needed), 
    struct SFIitem
    {
        typedef void _hx_trivial_destruct_tag;
        typedef void _hx_bitwise_relocatable_tag;
        SFIitem() : XIndex(0), power(0), factor(1.0), function(poly), cacheIndex((size_t)(-1)) {}
        SFIitem(const SFIitem& other)
            : XIndex(other.XIndex), power(other.power), factor(other.factor), function(other.function), cacheIndex(other.cacheIndex) {}
        SFIitem& operator=(const SFIitem& other)
        {
            if (this != &other)
            {
                XIndex = other.XIndex;
                power = other.power;
                factor = other.factor;
                function = other.function;
                cacheIndex = other.cacheIndex;
            }
            return *this;
        }
        size_t XIndex;//变量索引，表示这个单项式中的自变量是输入数据的第几个维度
        int power;//int parameter named as power
        //for polynomial, power is the exponent of the variable Xindex^Power
        //for reciprocal, power is the exponent of the variable 1/Xindex, and the value is Xindex^(-power)
        //for exp, power is the exponent of the variable exp(Xindex), and the value is exp(-power * Xindex)
        //for gaussian, power is the exponent of the variable exp(-Xindex^2), and the value is exp(-power * Xindex^2)
        //for cos, power is the exponent of the variable cos(Xindex), and the value is cos(power * Xindex)
        //for sin, power is the exponent of the variable sin(Xindex), and the value is sin(power * Xindex)
        double factor;
        func function;
        size_t cacheIndex;
        double compute(double x) const;
        double compute(const double* x) const;
    };
    struct Setting
    {
        typedef void _hx_trivial_destruct_tag;
        typedef void _hx_bitwise_relocatable_tag;
        Setting() : poly(0), reciprocal(0), exp(0), gaussian(0), cos(0), sin(0) {}
        Setting(const Setting& other)
            : poly(other.poly), reciprocal(other.reciprocal), exp(other.exp), gaussian(other.gaussian), cos(other.cos), sin(other.sin) {}
        Setting& operator=(const Setting& other)
        {
            if (this != &other)
            {
                poly = other.poly;
                reciprocal = other.reciprocal;
                exp = other.exp;
                gaussian = other.gaussian;
                cos = other.cos;
                sin = other.sin;
            }
            return *this;
        }

        unsigned int poly;
		unsigned int reciprocal;
		unsigned int exp;
		unsigned int gaussian;
		unsigned int cos;
		unsigned int sin;

        size_t sum(void) const  //返回所有函数数量之和
        {
            return poly + reciprocal + exp + gaussian + cos + sin;
        };
        func GetFunc(size_t index) const  //根据index返回对应的函数类型，例如index=0返回poly，index=1返回reciprocal，以此类推
        {
            size_t cumulative = 0;
            if (index < cumulative + poly) return analyzer::poly;
            cumulative += poly;
            if (index < cumulative + reciprocal) return analyzer::reciprocal;
            cumulative += reciprocal;
            if (index < cumulative + exp) return analyzer::exp;
            cumulative += exp;
            if (index < cumulative + gaussian) return analyzer::gaussian;
            cumulative += gaussian;
            if (index < cumulative + cos) return analyzer::cos;
            cumulative += cos;
            if (index < cumulative + sin) return analyzer::sin;
            // 如果 index 超出范围，可以抛出异常或返回一个默认值
            throw std::out_of_range("Index out of range in GetFunc");
        };
        unsigned int GetIndex(size_t index) const  //根据小端序的index返回对应函数的数量，例如index=0返回poly的数量，index=1返回reciprocal的数量，以此类推
        {
            size_t cumulative = 0;
            if (index < cumulative + poly) return index - cumulative;
            cumulative += poly;
            if (index < cumulative + reciprocal) return index - cumulative;
            cumulative += reciprocal;
            if (index < cumulative + exp) return index - cumulative;
            cumulative += exp;
            if (index < cumulative + gaussian) return index - cumulative;
            cumulative += gaussian;
            if (index < cumulative + cos) return index - cumulative;
            cumulative += cos;
            if (index < cumulative + sin) return index - cumulative;
            // 如果 index 超出范围，可以抛出异常或返回一个默认值
            throw std::out_of_range("Index out of range in GetIndex");
        };
    };
    class SFIformula
    {
        public:
            typedef void _hx_need_explicit_move_tag;
            SFIformula() : order(0), ItemCount(0), SourceCount(0), positiveDefiniteCached(false), sumItemOrderCached(0), normalizationPower(1.0) {}
            ~SFIformula() {}
            SFIformula(const SFIformula& other)
                : items(other.items), partion(other.partion), order(other.order), ItemCount(other.ItemCount), SourceCount(other.SourceCount),
                  positiveDefiniteCached(other.positiveDefiniteCached), sumItemOrderCached(other.sumItemOrderCached),
                  normalizationPower(other.normalizationPower) {}
            SFIformula& operator=(const SFIformula& other)
            {
                if (this != &other)
                {
                    items = other.items;
                    partion = other.partion;
                    order = other.order;
                    ItemCount = other.ItemCount;
                    SourceCount = other.SourceCount;
                    positiveDefiniteCached = other.positiveDefiniteCached;
                    sumItemOrderCached = other.sumItemOrderCached;
                    normalizationPower = other.normalizationPower;
                }
                return *this;
            }
            void move(SFIformula& src);
            friend class SFIexpresses;
            double compute(const double* x) const;
            double compute(const double* x, bool PowerNormalization) const;
            bool PositiveDefinite(void) const;
            size_t GetSumofItemsOrder(void) const;
        protected:
            vector<SFIitem> items;
            vector<size_t> partion;
            int order;//齐次多项式的次数，“物理”阶数
            size_t ItemCount;//单项式项数
            int SourceCount;//来自多少个不同的单项式划分，“虚拟”阶数， “等效”阶数
            bool positiveDefiniteCached;
            size_t sumItemOrderCached;
            double normalizationPower;

    };
    class SFIexpresses
    {
        public:
            typedef void _hx_need_explicit_move_tag;
            SFIexpresses() : highestOrder(0), HighestSource(0), XCount(0), SourceOrder1Count(0) {}
            ~SFIexpresses() {}
            SFIexpresses(const SFIexpresses& other)
                : formulas(other.formulas), highestOrder(other.highestOrder), HighestSource(other.HighestSource), XCount(other.XCount), SourceOrder1Count(other.SourceOrder1Count), Order1(other.Order1), settings(other.settings), XindexToPartition(other.XindexToPartition), itemCacheKeys(other.itemCacheKeys)
            {
                for (size_t i = 0; i < 6; ++i)
                {
                    powerPlans[i] = other.powerPlans[i];
                }
            }
            SFIexpresses& operator=(const SFIexpresses& other)
            {
                if (this != &other)
                {
                    formulas = other.formulas;
                    highestOrder = other.highestOrder;
                    HighestSource = other.HighestSource;
                    XCount = other.XCount;
                    SourceOrder1Count = other.SourceOrder1Count;
                    Order1 = other.Order1;
                    settings = other.settings;
                    XindexToPartition = other.XindexToPartition;
                    itemCacheKeys = other.itemCacheKeys;
                    for (size_t i = 0; i < 6; ++i)
                    {
                        powerPlans[i] = other.powerPlans[i];
                    }
                }
                return *this;
            }
            void move(SFIexpresses& src);

        protected:
            vector<SFIformula> formulas;
            int highestOrder;//最高次数
            int HighestSource;//最高来源次数
            size_t XCount;//变量数量
            size_t SourceOrder1Count;//次数为1的多项式数量，记录源自于来源FI中有多少个一阶单项式
            vector<FIexpress> Order1;
            vector<Setting> settings;
            vector<size_t> XindexToPartition;//XCount长，记录每个输入变量所属的一阶单项式划分的索引，值为0到SourceOrder1Count-1之间的整数
            vector<SFIitemKey> itemCacheKeys;
            SFIpowerPlan powerPlans[6];//0:poly, 1:reciprocal, 2:exp, 3:gaussian, 4:cos, 5:sin
            void BuildItemCachePlan(void);
        public:
            void build(const FIexpresses& source, int max_order, const vector<Setting> & Settings);
            void demo(FILE*fp = stdout) const;//输出这个SFIexpresses对象的内容，供用户查看
            size_t getXCount() const { return XCount; }//返回这个SFIexpresses对象中输入变量的数量
            size_t getFormulaCount() const { return formulas.count(); }//返回这个SFIexpresses对象中SFIformula的数量
            int compute(const double*input, size_t ldi, size_t rowi, size_t coli, double* output, size_t ldo, size_t rowo, size_t colo) const;
            int compute(const double*input, size_t ldi, size_t rowi, size_t coli, double* output, size_t ldo, size_t rowo, size_t colo, bool PowerNormalization) const;
            int compute(unsigned int threadCount, const double*input, size_t ldi, size_t rowi, size_t coli, double* output, size_t ldo, size_t rowo, size_t colo) const;
            int compute(unsigned int threadCount, const double*input, size_t ldi, size_t rowi, size_t coli, double* output, size_t ldo, size_t rowo, size_t colo, bool PowerNormalization) const;

            int printCcode(FILE*fp) const;//printer.cpp
            int printFortrancode(FILE*fp) const;//printer.cpp
            
            

    };

    struct errorinfo
    {
        size_t line;
        const char* msg;
        const char* symbol;
        void demo(FILE*fp = stderr) const;
    };
    
    int ParserDataMatrix(FILE*inputMat, vector<double> & matrix, size_t &row, size_t &col);

        /*
        SFI build() 伪代码草案（已保留用于溯源，不参与编译）：
        1) 复制 source 到临时对象 here，并执行 cutoffByOrder(max_order, true)。
        2) 初始化 highestOrder/HighestSource/XCount/SourceOrder1Count/Order1/settings/XindexToPartition。
        3) 遍历不同物理阶，并按对应 Setting 枚举函数组合。
        4) 对每个来源 FI 的每个单项式、每个变量位置构建 SFIitem。
        5) 组合完成后形成 SFIformula，加入 SFIexpresses。
        */
} 

//=================================xyz=============================
namespace analyzer
{
    using namespace TemplateSelf;
    class xyz
	{
	public:
        typedef void _hx_need_explicit_move_tag;
		friend class xyzFile;
		xyz();
		~xyz();
        void move(xyz& src);
        xyz(const xyz& other);
        xyz& operator=(const xyz& other);
        void clear(void);
		
		void Print(double* mat) const;
		void PrintBondlength(double* mat) const;
		// PrintAngle 输出弧度；PrintAngleCosines 输出对应的 cos(theta)。
		void PrintAngle(double* mat) const;
		void PrintAngleCosines(double* mat) const;
		// 二面角 key=(B,C,A,D)：B<C、A<D；输出无向二面角的 cos(phi)。
		void PrintDihedralCosines(double* mat) const;
		void demo(FILE* fp) const;
		bool operator==(const xyz& right) const;
		bool operator!=(const xyz& right) const;
		int build(double Energy, const vector<StringConst>& Name, const vector<double>& xyzSource);
		int build(double Energy, const vector<const char*>& Name, const vector<double>& xyzSource);
        int build(const xyz& source);
		void permutation(const vector<size_t>& group);
		size_t AtomCount(void)const;
		const char* AtomName(size_t index) const;
		//permutation: name[i] = name_old[group[i]];
	protected:
		double E;
		size_t count;
		vector<StringConst> name;
		vector<double> XYZ;
		bool Force;
		bool compare(const xyz& right) const;
		void permutation(const vector<size_t>& group, vector<StringConst>& tempN, vector<double> &tempXYZ);
	};
	class xyzFile 
	{
	public:
		typedef void _hx_need_explicit_move_tag;
		xyzFile();
		~xyzFile();
        xyzFile(const xyzFile& other);
        xyzFile& operator=(const xyzFile& other);
		int build(FILE*fp);
        void clear(void);
        void move(xyzFile& src);
		size_t check(void) const;
		size_t count(void) const;
		int append(const xyz& element);
		double* Print(void) const;
		void demo(FILE* fp) const;
		void tail(FILE* fp, size_t N) const;
		void demo(FILE* fp, size_t lower, size_t upper) const;
		void PrintR(vector<double> & output) const;
		// PrintAngles 输出弧度矩阵；余弦接口不计算 acos。
		void PrintAngles(vector<double> & output) const;
		void PrintAngleCosines(vector<double> & output) const;
		void PrintDihedralCosines(vector<double> & output) const;
        void PrintRAndAngleCosines(vector<double>& bondOutput, vector<double>& angleCosineOutput) const;
        void PrintRAndGeometricCosines(vector<double>& bondOutput, vector<double>* angleCosineOutput,
            vector<double>* dihedralCosineOutput) const;
		int permutation(const vector<size_t>& group);
		xyz& operator[](size_t target) { return content[target]; }
		const xyz& operator[](size_t target) const { return content[target]; }

		double EnergyUpper(void) const;
		double EnerguLower(void) const;
		void OutputErange(vector<double>&output) const;
	private:
		size_t atom;
		vector<xyz> content;
	};
}




#endif
