#include "analyzer.h"
#include <pthread.h>

using namespace analyzer;

// 线程参数结构体
typedef struct {
    const FIexpresses* fiExpresses;
    const double* input;
    size_t ldi;
    size_t startRow;
    size_t endRow;
    size_t coli;
    double* output;
    size_t ldo;
    size_t colo;
    bool PowerNormalization;
    int error;
} ThreadData;

// 线程函数
void* computeThread(void* arg) {
    ThreadData* data = (ThreadData*)arg;
    const size_t rows = data->endRow - data->startRow;
    const double* currentInput = data->input + data->startRow * data->ldi;
    double* currentOutput = data->output + data->startRow * data->ldo;

    data->error = data->fiExpresses->compute(
        currentInput, data->ldi, rows, data->coli,
        currentOutput, data->ldo, rows, data->colo,
        data->PowerNormalization);
    
    return NULL;
}

int FIexpresses::compute(unsigned int threadCount, const double* input, size_t ldi, size_t rowi, size_t coli, double* output, size_t ldo, size_t rowo, size_t colo) const
{
    return compute(threadCount, input, ldi, rowi, coli, output, ldo, rowo, colo, false);
}

int FIexpresses::compute(unsigned int threadCount, const double* input, size_t ldi, size_t rowi, size_t coli, double* output, size_t ldo, size_t rowo, size_t colo, bool PowerNormalization) const
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
    
    // 如果线程数为0或1，直接使用单线程版本
    if (threadCount == 0 || threadCount == 1) {
        return compute(input, ldi, rowi, coli, output, ldo, rowo, colo, PowerNormalization);
    }
    
    // 计算每个线程处理的行数
    size_t rowsPerThread = rowi / threadCount;
    size_t remainingRows = rowi % threadCount;
    
    // 创建线程和线程数据
    pthread_t* threads = new pthread_t[threadCount];
    ThreadData* threadData = new ThreadData[threadCount];
    
    // 分配任务并创建线程
    size_t currentRow = 0;
    for (unsigned int i = 0; i < threadCount; ++i) {
        // 计算当前线程处理的行数
        size_t threadRows = rowsPerThread + (i < remainingRows ? 1 : 0);
        
        // 设置线程数据
        threadData[i].fiExpresses = this;
        threadData[i].input = input;
        threadData[i].ldi = ldi;
        threadData[i].startRow = currentRow;
        threadData[i].endRow = currentRow + threadRows;
        threadData[i].coli = coli;
        threadData[i].output = output;
        threadData[i].ldo = ldo;
        threadData[i].colo = colo;
        threadData[i].PowerNormalization = PowerNormalization;
        threadData[i].error = 0;
        
        // 创建线程
        pthread_create(&threads[i], NULL, computeThread, &threadData[i]);
        
        // 更新当前行
        currentRow += threadRows;
    }
    
    // 等待所有线程完成
    int error = 0;
    for (unsigned int i = 0; i < threadCount; ++i) {
        pthread_join(threads[i], NULL);
        if (error == 0 && threadData[i].error != 0) {
            error = threadData[i].error;
        }
    }
    
    // 释放资源
    delete[] threads;
    delete[] threadData;
    
    return error;
}

// SFI 线程参数结构体
typedef struct {
    const SFIexpresses* sfiExpresses;
    const double* input;
    size_t ldi;
    size_t startRow;
    size_t endRow;
    size_t coli;
    double* output;
    size_t ldo;
    size_t colo;
    bool powerNormalization;
    int error;
} SFIThreadData;

// SFI 线程函数
void* computeSFIThread(void* arg) {
    SFIThreadData* data = (SFIThreadData*)arg;
    const size_t rows = data->endRow - data->startRow;
    const double* currentInput = data->input + data->startRow * data->ldi;
    double* currentOutput = data->output + data->startRow * data->ldo;

    data->error = data->sfiExpresses->compute(
        currentInput, data->ldi, rows, data->coli,
        currentOutput, data->ldo, rows, data->colo,
        data->powerNormalization);

    return NULL;
}

int SFIexpresses::compute(unsigned int threadCount, const double* input, size_t ldi, size_t rowi, size_t coli,
    double* output, size_t ldo, size_t rowo, size_t colo) const
{
    return compute(threadCount, input, ldi, rowi, coli, output, ldo, rowo, colo, false);
}

int SFIexpresses::compute(unsigned int threadCount, const double* input, size_t ldi, size_t rowi, size_t coli,
    double* output, size_t ldo, size_t rowo, size_t colo, bool PowerNormalization) const
{
    if (rowi != rowo) {
        return -1;
    }

    if (coli != XCount) {
        return -3;
    }

    if (colo != formulas.count()) {
        return -4;
    }

    if (threadCount == 0 || threadCount == 1) {
        return compute(input, ldi, rowi, coli, output, ldo, rowo, colo, PowerNormalization);
    }

    size_t rowsPerThread = rowi / threadCount;
    size_t remainingRows = rowi % threadCount;

    pthread_t* threads = new pthread_t[threadCount];
    SFIThreadData* threadData = new SFIThreadData[threadCount];

    size_t currentRow = 0;
    for (unsigned int i = 0; i < threadCount; ++i) {
        size_t threadRows = rowsPerThread + (i < remainingRows ? 1 : 0);

        threadData[i].sfiExpresses = this;
        threadData[i].input = input;
        threadData[i].ldi = ldi;
        threadData[i].startRow = currentRow;
        threadData[i].endRow = currentRow + threadRows;
        threadData[i].coli = coli;
        threadData[i].output = output;
        threadData[i].ldo = ldo;
        threadData[i].colo = colo;
        threadData[i].powerNormalization = PowerNormalization;
        threadData[i].error = 0;

        pthread_create(&threads[i], NULL, computeSFIThread, &threadData[i]);

        currentRow += threadRows;
    }

    int error = 0;
    for (unsigned int i = 0; i < threadCount; ++i) {
        pthread_join(threads[i], NULL);
        if (error == 0 && threadData[i].error != 0) {
            error = threadData[i].error;
        }
    }

    delete[] threads;
    delete[] threadData;

    return error;
}

// 余弦 FI 变换线程参数结构体（键角与二面角共用）
typedef struct {
    const FIexpresses* fiExpresses;
    const double* cosineInput;
    size_t ldi;
    size_t startRow;
    size_t endRow;
    size_t coli;
    double* output;
    size_t ldo;
    size_t colo;
    const vector<unsigned int>* settings_cos;
    int error;
} CosTransformThreadData;

// 余弦 FI 变换线程函数
void* computeCosTransformThread(void* arg) {
    CosTransformThreadData* data = (CosTransformThreadData*)arg;
    const size_t rows = data->endRow - data->startRow;
    const double* currentInput = data->cosineInput + data->startRow * data->ldi;
    double* currentOutput = data->output + data->startRow * data->ldo;

    data->error = data->fiExpresses->computeCosTransform(
        currentInput, data->ldi, rows, data->coli,
        currentOutput, data->ldo, rows, data->colo,
        *(data->settings_cos));

    return NULL;
}

int FIexpresses::computeCosTransform(unsigned int threadCount, const double* cosineInput, size_t ldi, size_t rowi, size_t coli,
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

    // 计算期望的输出列数
    size_t expectedColo = 0;
    for (size_t fi = 0; fi < items.size(); ++fi) {
        const int order = items[fi].getOrder();
        if (order > 0 && (size_t)order <= settings_cos.count()) {
            const unsigned int harmonicCount = settings_cos[(size_t)order - 1];
            expectedColo += harmonicCount;
        }
    }

    if (colo != expectedColo) {
        return -4;
    }

    // 如果线程数为0或1，直接使用单线程版本
    if (threadCount == 0 || threadCount == 1) {
        return computeCosTransform(cosineInput, ldi, rowi, coli, output, ldo, rowo, colo, settings_cos);
    }

    // 计算每个线程处理的行数
    size_t rowsPerThread = rowi / threadCount;
    size_t remainingRows = rowi % threadCount;

    // 创建线程和线程数据
    pthread_t* threads = new pthread_t[threadCount];
    CosTransformThreadData* threadData = new CosTransformThreadData[threadCount];

    // 分配任务并创建线程
    size_t currentRow = 0;
    for (unsigned int i = 0; i < threadCount; ++i) {
        // 计算当前线程处理的行数
        size_t threadRows = rowsPerThread + (i < remainingRows ? 1 : 0);

        // 设置线程数据
        threadData[i].fiExpresses = this;
        threadData[i].cosineInput = cosineInput;
        threadData[i].ldi = ldi;
        threadData[i].startRow = currentRow;
        threadData[i].endRow = currentRow + threadRows;
        threadData[i].coli = coli;
        threadData[i].output = output;
        threadData[i].ldo = ldo;
        threadData[i].colo = colo;
        threadData[i].settings_cos = &settings_cos;
        threadData[i].error = 0;

        // 创建线程
        pthread_create(&threads[i], NULL, computeCosTransformThread, &threadData[i]);

        currentRow += threadRows;
    }

    // 等待所有线程完成
    int error = 0;
    for (unsigned int i = 0; i < threadCount; ++i) {
        pthread_join(threads[i], NULL);
        if (error == 0 && threadData[i].error != 0) {
            error = threadData[i].error;
        }
    }

    // 释放资源
    delete[] threads;
    delete[] threadData;

    return error;
}

int FIexpresses::computeAngleCosTransform(unsigned int threadCount, const double* angleCosineInput, size_t ldi, size_t rowi, size_t coli,
    double* output, size_t ldo, size_t rowo, size_t colo, const vector<unsigned int>& settingsA_cos) const
{
    return computeCosTransform(threadCount, angleCosineInput, ldi, rowi, coli,
        output, ldo, rowo, colo, settingsA_cos);
}
