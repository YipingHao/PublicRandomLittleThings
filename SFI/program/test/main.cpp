#include "../code/dictionary.h"
#include "../code/analyzer.h"
#include "../code/SFI_v02/task.h"
#include <cstring>
#include <exception>
#include <string>
#include <ctime>

int TestEntrance(hyperlex::dictionary&dict, const char* outputPath);

int static TaskEntrance(hyperlex::dictionary&dict, const char* outputPath, const char* task);
std::string static ChangeSuffix(const std::string& file, const char* new_one);
// 生成代码文件的通用函数
template <class ExprT>
int static EmitCodeFile(const char* outputPath, const std::string& baseName, const char* suffix,
    const char* languageName, const ExprT& expr, int (ExprT::*printer)(FILE*) const);

int main(int argc, char* argv[])
{
    hyperlex::dictionary dict;

    const char* parameterPath = "./parameter/input.txt";
    const char* outputPath = "./output/";

    if (argc > 1) {
        parameterPath = argv[1];
    }
    if (argc > 2) {
        outputPath = argv[2];
    }

    FILE*fp = fopen(parameterPath, "r");
    if (fp == NULL) {
        printf("Error when opening parameter file: %s\n", parameterPath);
        return 1123123;
    }

    // 构建参数字典并打印参数信息
    int error = dict.build(fp);
    fclose(fp);
    dict.print(stdout);
    if (error != 0) {
        printf("Error when reading parameter file: %s, error: %d\n", parameterPath, error);
        return error;
    }
    
    const char * task = dict.search("test","item");
    printf("task: %s\n", task);
    

    if (strcmp(task, "test") == 0) {
        return TestEntrance(dict, outputPath);
    }
    else {
        return TaskEntrance(dict, outputPath, task);
    }
    return 0;
}

void static CodeGeneration(hyperlex::dictionary&dict, const char* outputPath, analyzer::FIexpresses & expressions)
{
    bool CcodePrint = dict.search(false,"CodeGenSetting.CcodePrint");
    bool FortranCodePrint = dict.search(false,"CodeGenSetting.FortranCodePrint");
    const char * OutputFileName = dict.search("output","OutputFileName");
    std::string fileName = OutputFileName;

    // 生成C代码
    if (CcodePrint) {
        EmitCodeFile(outputPath, fileName, ".c", "C", expressions, &analyzer::FIexpresses::printCcode);
    }

    // 生成Fortran代码
    if (FortranCodePrint) {
        EmitCodeFile(outputPath, fileName, ".f90", "Fortran", expressions, &analyzer::FIexpresses::printFortrancode);
    }
}


int static DataMatrixSwitch(hyperlex::dictionary&dict, const char* outputPath, analyzer::FIexpresses & expressions);
int static SFIDataMatrixSwitch(hyperlex::dictionary&dict, const char* outputPath, const analyzer::SFIexpresses & expressions,
    const analyzer::FIexpresses* angleExpressions, int maxOrderA, const analyzer::vector<unsigned int>& settingsA_cos,
    const analyzer::FIexpresses* dihedralExpressions, int maxOrderD, const analyzer::vector<unsigned int>& settingsD_cos);
int static Cutoff(hyperlex::dictionary&dict, const char* outputPath, analyzer::FIexpresses & expressions);
int static SFI(hyperlex::dictionary&dict, const char* outputPath, analyzer::FIexpresses & expressions);
int static XYZonly(hyperlex::dictionary&dict, const char* outputPath);

int static TaskEntrance(hyperlex::dictionary&dict, const char* outputPath, const char* task)
{
    if (strcmp(task, "XYZonly") == 0)
    {
        return XYZonly(dict, outputPath);
    }
    if (strcmp(task, "SFI_v02") == 0)
    {
        return analyzer::sfi_v02::SFI_v02(dict, outputPath);
    }

    const char * PIPFileName = dict.search("./data/origin.txt","PIPFileName");
    printf("PIPFileName: %s\n", PIPFileName);
    FILE*fp = fopen(PIPFileName, "r");
    if (fp == NULL) {
        printf("Error when opening PIP file: %s\n", PIPFileName);
        return 1123;
    }
    // 构建FIexpresses对象
    analyzer::FIexpresses expressions;
    int error = expressions.build(fp);
    fclose(fp);
    if (error != 0) {
        printf("Error when reading PIP file: %s, error: %d\n", PIPFileName, error);
        return error;
    }
    else {
        printf("read PIP file end:\n");
    }

    // 输出表达式信息供用户查看
    expressions.demo(stdout);

    if (strcmp(task, "dataswitch") == 0) 
    {
        return DataMatrixSwitch(dict, outputPath, expressions);
    }
    else if (strcmp(task, "CodeGeneration") == 0)
    {
        CodeGeneration(dict, outputPath, expressions);
        return 0;
    }
    else if (strcmp(task, "cutoff") == 0) 
    {
        return Cutoff(dict, outputPath, expressions);
    }
    else if (strcmp(task, "SFI") == 0) 
    {
        return SFI(dict, outputPath, expressions);
    }
    else
    {
        printf("Unknown task: %s\n", task);
        return -156489;
    }
}

class XYZsetting
{
protected:
    bool ThisMode;//if item == "XYZonly";
    const char* format;
	bool OutToFile;
	analyzer::StringConst OutFileName;//Prefix is only needed
	bool NeedPermutation;
	analyzer::vector<size_t> Permutation;
	size_t AtomCount;
    analyzer::xyzFile XYZFile;

    FILE*DataFILE;
    analyzer::vector<double> dataMatrix;// bondlength, energy
    size_t row;
    size_t col;
public:
    XYZsetting(/* args */);
    ~XYZsetting();
    int build(hyperlex::dictionary&dict, const char* outputPath, analyzer::vector<double>* angleCosineMatrix = NULL,
        analyzer::vector<double>* dihedralCosineMatrix = NULL);

    bool IFneededPermutation(void) const { return NeedPermutation; }
    const analyzer::vector<double> & GetMat(void) const { return dataMatrix; }
    size_t GetRow(void) const { return row; }
    size_t GetCol(void) const { return col; }
    const analyzer::xyzFile & GetXYZFile(void) const { return XYZFile; }
    analyzer::xyzFile & GetXYZFile(void) { return XYZFile; }
};

int static XYZonly(hyperlex::dictionary&dict, const char* outputPath)
{
    XYZsetting xyzSetting;
    int error = xyzSetting.build(dict, outputPath);
    if (error != 0) {
        printf("XYZonly failed: error %d\n", error);
        return error;
    }

    printf("XYZonly: row: %zu, col: %zu\n", xyzSetting.GetRow(), xyzSetting.GetCol());
    return 0;
}

int static DataMatrixSwitch(hyperlex::dictionary&dict, const char* outputPath, analyzer::FIexpresses & expressions)
{
    clock_t startTotal = clock();

    long int threadCount = dict.search((long int)1, "threadCount");
    printf("threadCount: %ld\n", threadCount);

    const char * DataFileName = dict.search("./data/origin.txt","DataFileName");
    printf("DataFileName: %s\n", DataFileName);

    const bool PowerNormalization = dict.search(false, "FI.PowerNormalization");
    printf("  FI.PowerNormalization: %s\n", PowerNormalization ? "true" : "false");

    const char* dataFormat = dict.search("mat", "DataFormat");
    const bool ifDataXYZ = dict.search(false, "IfDataXYZ");
    bool useXYZ = false;
    if (strcmp(dataFormat, "xyz") == 0) {
        useXYZ = true;
    } else if (strcmp(dataFormat, "mat") == 0) {
        useXYZ = false;
    } else {
        useXYZ = ifDataXYZ;
    }

    size_t row = 0;
    size_t col = 0;
    analyzer::vector<double> matrixStorage;
    const analyzer::vector<double>* matrix = NULL;

    clock_t startDataLoad = clock();
    XYZsetting xyzSetting;
    if (useXYZ) {
        int error = xyzSetting.build(dict, outputPath);
        if (error != 0) {
            return error;
        }
        matrix = &xyzSetting.GetMat();
        row = xyzSetting.GetRow();
        col = xyzSetting.GetCol();
    } else {
        FILE* inputMat = fopen(DataFileName, "r");
        if (inputMat == NULL) {
            printf("Error when opening data file: %s\n", DataFileName);
            return 1234234;
        }
        int error = analyzer::ParserDataMatrix(inputMat, matrixStorage, row, col);
        fclose(inputMat);
        if (error != 0) {
            printf("Error when parsing data file: %s, error: %d\n", DataFileName, error);
            return error;
        }
        matrix = &matrixStorage;
    }

    clock_t endDataLoad = clock();
    double dataLoadTime = (double)(endDataLoad - startDataLoad) / CLOCKS_PER_SEC;
    printf("Data loading time: %.3f seconds\n", dataLoadTime);

    printf("row: %zu, col: %zu\n", row, col);

    bool hasEnergy;
    size_t xCount = expressions.getXCount();
    if(xCount + 1 == col)
    {
        hasEnergy = true;
     
    }
    else if(xCount == col)
    {
        hasEnergy = false;
    }
    else
    {
        printf("Error: XCount != col && XCount + 1 != col\n");
        return -1;
    }
    // 计算输出矩阵的列数：PIP多项式数量 + (如果有能量则加1)
    size_t outputCols = expressions.getItems().size();
    size_t ldi = col; // 输入矩阵的领先维度
    size_t coli = hasEnergy ? (col - 1) : col; // 输入数据的列数（不包括能量列）
    size_t ldo = hasEnergy ? (outputCols + 1) : outputCols; // 输出矩阵的领先维度

    // 分配输出矩阵
    analyzer::vector<double> outputMatrix;
    outputMatrix.resize(row * ldo);
    // 准备输入和输出参数
    const double* inputData = matrix->ptr();
    double* outputData = outputMatrix.ptr();

    // 计算PIP值
    clock_t startCompute = clock();
    int computeError;
    if (threadCount > 1) {
        // 使用多线程计算
        computeError = expressions.compute(static_cast<unsigned int>(threadCount), 
                                         inputData, ldi, row, coli, 
                                         outputData, ldo, row, outputCols, PowerNormalization);
    } else {
        // 使用单线程计算
        computeError = expressions.compute(inputData, ldi, row, coli, 
                                         outputData, ldo, row, outputCols, PowerNormalization);
    }

    if (computeError != 0) {
        printf("Error when computing PIP values: %d\n", computeError);
        return computeError;
    }

    clock_t endCompute = clock();
    double computeTime = (double)(endCompute - startCompute) / CLOCKS_PER_SEC;
    printf("PIP computation time: %.3f seconds\n", computeTime);

    // 如果有能量列，将能量值复制到输出矩阵的最后一列
    if (hasEnergy) {
        for (size_t i = 0; i < row; ++i) {
            // 输入矩阵的最后一列是能量值
            double energy = (*matrix)[i * ldi + coli];
            // 输出矩阵的最后一列存储能量值
            outputMatrix[i * ldo + outputCols] = energy;
        }
    }

    // 保存结果到输出文件
    clock_t startFileSave = clock();
    const char * OutputFileName = dict.search("output","OutputFileName");
    std::string fileName = OutputFileName;
    std::string outputFilePath = ChangeSuffix(fileName, ".txt");
    hyperlex::FilePath filetemp;
    hyperlex::FilePath OutputFilePath;
    OutputFilePath.build(outputPath);
    filetemp.build(outputFilePath.c_str());
    OutputFilePath += filetemp;

    FILE* outputFile = fopen(OutputFilePath.path(), "w");
    if (outputFile != NULL) {
        // 写入表头信息
        fprintf(outputFile, "# PIP values generated by FIanalyzer\n");
        fprintf(outputFile, "# Number of data points: %zu\n", row);
        fprintf(outputFile, "# Number of PIP polynomials: %zu\n", expressions.getItems().size());
        if (hasEnergy) {
            fprintf(outputFile, "# Including energy values\n");
        }
        fprintf(outputFile, "\n");

        // 写入数据
        for (size_t i = 0; i < row; ++i) {
            for (size_t j = 0; j < ldo; ++j) {
                fprintf(outputFile, "%25.16E ", outputMatrix[i * ldo + j]);
            }
            fprintf(outputFile, "\n");
        }

        fclose(outputFile);
        printf("Output file generated: %s\n", OutputFilePath.path());
    } else {
        printf("Error opening output file for writing: %s\n", OutputFilePath.path());
        return 1234;
    }

    clock_t endFileSave = clock();
    double fileSaveTime = (double)(endFileSave - startFileSave) / CLOCKS_PER_SEC;
    printf("File saving time: %.3f seconds\n", fileSaveTime);

    clock_t endTotal = clock();
    double totalTime = (double)(endTotal - startTotal) / CLOCKS_PER_SEC;
    printf("DataMatrixSwitch total time: %.3f seconds\n", totalTime);

    return 0;
}


XYZsetting::XYZsetting(/* args */)
{
    ThisMode = false;
    format = NULL;
    OutToFile = false;
    NeedPermutation = false;
    AtomCount = 0;
    DataFILE = NULL;
    row = 0;
    col = 0;
}

XYZsetting::~XYZsetting()
{
}

int XYZsetting::build(hyperlex::dictionary&dict, const char* outputPath, analyzer::vector<double>* angleCosineMatrix,
    analyzer::vector<double>* dihedralCosineMatrix)
{
    dataMatrix.clear();
    row = 0;
    col = 0;

    const char* dataFormat = dict.search("mat", "DataFormat");
    const bool ifDataXYZ = dict.search(false, "IfDataXYZ");
    ThisMode = (strcmp(dataFormat, "xyz") == 0) || ifDataXYZ;
    format = dataFormat;

    const char* dataFileName = dict.search("./data/origin.txt", "DataFileName");
    OutToFile = dict.search(false, "XYZsettings.OutToFile");

    const char* outFileName = dict.search("bondlength", "XYZsettings.OutFileName");
    OutFileName = outFileName;

    NeedPermutation = dict.search(false, "XYZsettings.NeedPermutation");
    AtomCount = (size_t)dict.search((long int)0, "XYZsettings.AtomCount");

    Permutation.clear();
    if (NeedPermutation) {
        size_t permCount = 0;
        hyperlex::dictionary::Ktype permType = hyperlex::dictionary::null_;
        hyperlex::dictionary::element* permArray = dict.search(permCount, permType, "XYZsettings.Permutation");
        if (permArray != NULL && permCount > 0) {
            if (permType != hyperlex::dictionary::int_) {
                printf("Error: XYZsettings.Permutation must be integer array.\n");
                return -301;
            }
            Permutation.recount(permCount);
            for (size_t i = 0; i < permCount; ++i) {
                Permutation[i] = (size_t)permArray[i].ii;
            }
        }
    }

    FILE* fp = fopen(dataFileName, "r");
    if (fp == NULL) {
        printf("Error when opening xyz data file: %s\n", dataFileName);
        return 1234234;
    }

    XYZFile.clear();
    int error = XYZFile.build(fp);
    fclose(fp);
    if (error != 0) {
        printf("Error when parsing xyz data file: %s, error: %d\n", dataFileName, error);
        return error;
    }

    if (XYZFile.count() == 0) {
        printf("Error: xyz data file has no frames.\n");
        return -302;
    }

    const size_t fileAtomCount = XYZFile[0].AtomCount();
    if (AtomCount != 0 && AtomCount != fileAtomCount) {
        printf("Error: AtomCount mismatch. input=%zu file=%zu\n", AtomCount, fileAtomCount);
        return -303;
    }

    const size_t bad = XYZFile.check();
    if (bad != 0) {
        printf("Error: xyz frames mismatch at index %zu\n", bad);
        return -304;
    }

    if (NeedPermutation) {
        if (Permutation.count() == 0) {
            printf("Error: NeedPermutation is true but Permutation is empty.\n");
            return -305;
        }
        if (Permutation.count() != fileAtomCount) {
            printf("Error: Permutation size mismatch. perm=%zu atom=%zu\n", Permutation.count(), fileAtomCount);
            return -306;
        }

        analyzer::vector<bool> used;
        used.recount(fileAtomCount);
        used.value(false);
        for (size_t i = 0; i < Permutation.count(); ++i) {
            if (Permutation[i] == 0) {
                printf("Error: Permutation is 1-based; index 0 is invalid at %zu.\n", i);
                return -307;
            }
            const size_t idx = Permutation[i] - 1;
            if (idx >= fileAtomCount) {
                printf("Error: Permutation index out of range at %zu: %zu\n", i, Permutation[i]);
                return -308;
            }
            if (used[idx]) {
                printf("Error: Permutation has duplicates at index %zu.\n", i);
                return -309;
            }
            used[idx] = true;
            Permutation[i] = idx;
        }

        error = XYZFile.permutation(Permutation);
        if (error != 0) {
            printf("Error when applying permutation: %d\n", error);
            return error;
        }
    }

    if (angleCosineMatrix != NULL || dihedralCosineMatrix != NULL) {
        XYZFile.PrintRAndGeometricCosines(dataMatrix, angleCosineMatrix, dihedralCosineMatrix);
    } else {
        XYZFile.PrintR(dataMatrix);
    }
    row = XYZFile.count();
    col = fileAtomCount * (fileAtomCount - 1) / 2 + 1;

    if (OutToFile) {
        std::string outFilePath = ChangeSuffix(OutFileName.ptr(), ".txt");
        hyperlex::FilePath filetemp;
        hyperlex::FilePath outputFilePath;
        outputFilePath.build(outputPath);
        filetemp.build(outFilePath.c_str());
        outputFilePath += filetemp;

        FILE* out = fopen(outputFilePath.path(), "w");
        if (out == NULL) {
            printf("Error opening xyz output file for writing: %s\n", outputFilePath.path());
            return -310;
        }

        for (size_t i = 0; i < row; ++i) {
            for (size_t j = 0; j < col; ++j) {
                fprintf(out, "%25.16E ", dataMatrix[i * col + j]);
            }
            fprintf(out, "\n");
        }

        fclose(out);
        printf("XYZ bondlength matrix output: %s\n", outputFilePath.path());
    }

    return 0;
}



std::string static ChangeSuffix(const std::string& file, const char* new_one)
{
    size_t i, j;
    std::string name;
    name = "";
    for (i = file.length(); i != 0; i--)
        if (file[i - 1] == '.') break;
    if (i == 0)
    {
        name = file;
        name += '.';
    }
    else
    {
        for (j = 0; j < i; j++)
            name += file[j];
    }
    if (new_one[0] == '.') name += (new_one + 1);
    else name += new_one;
    return name;
}

// 生成代码文件的通用函数
template <class ExprT>
int static EmitCodeFile(const char* outputPath, const std::string& baseName, const char* suffix,
    const char* languageName, const ExprT& expr, int (ExprT::*printer)(FILE*) const)
{
    std::string filePath = ChangeSuffix(baseName, suffix);
    hyperlex::FilePath filetemp;
    hyperlex::FilePath outputFilePath;
    outputFilePath.build(outputPath);
    filetemp.build(filePath.c_str());
    outputFilePath += filetemp;

    FILE* fp = fopen(outputFilePath.path(), "w");
    if (fp == NULL) {
        printf("Error opening %s code file for writing: %s\n", languageName, outputFilePath.path());
        return -1;
    }

    int ec = (expr.*printer)(fp);
    fclose(fp);
    if (ec != 0) {
        printf("Error generating %s code: %d\n", languageName, ec);
        return ec;
    }

    printf("%s code generated: %s\n", languageName, outputFilePath.path());
    return 0;
}

int static Cutoff(hyperlex::dictionary&dict, const char* outputPath, analyzer::FIexpresses & expressions)
{
    const char* threshold = dict.search("order", "CutoffSetting.threshold");
    int order = (int)dict.search((long int)-1, "CutoffSetting.order");
    long int workload = dict.search((long int)-1, "CutoffSetting.workload");
    bool crossItem = dict.search(false, "CutoffSetting.CrossItem");

    printf("Cutoff task started:\n");
    printf("  threshold: %s\n", threshold);
    if (strcmp(threshold, "order") == 0) {
        printf("  order: %d\n", order);
        expressions.cutoffByOrder(order, crossItem);
    } else if (strcmp(threshold, "workload") == 0) {
        printf("  workload: %ld\n", workload);
        expressions.cutoffByWorkload((size_t)workload, crossItem);
    } else {
        printf("  Unknown threshold: %s\n", threshold);
    }
    printf("  CrossItem: %s\n", crossItem ? "true" : "false");

    printf("\nCutoff applied successfully.\n");
    expressions.demo(stdout);

    // 输出截断后的原始格式文本
    const char * OutputFileName = dict.search("output", "OutputFileName");
    std::string fileName = OutputFileName;
    std::string printFilePath = ChangeSuffix(fileName, ".txt");
    
    hyperlex::FilePath filetemp;
    hyperlex::FilePath PrintFilePathPath;
    PrintFilePathPath.build(outputPath);
    filetemp.build(printFilePath.c_str());
    PrintFilePathPath += filetemp;

    FILE* pFile = fopen(PrintFilePathPath.path(), "w");
    if (pFile != NULL) {
        expressions.print(pFile);
        fclose(pFile);
        printf("\nPolynomials printed to file: %s\n", PrintFilePathPath.path());
    } else {
        printf("\nError opening file for printing polynomials: %s\n", PrintFilePathPath.path());
    }

    // 生成代码保存截断后的特征
    // CodeGeneration(dict, outputPath, expressions);
    
    return 0;
}

int static SFIDataMatrixSwitch(hyperlex::dictionary&dict, const char* outputPath, const analyzer::SFIexpresses & expressions,
    const analyzer::FIexpresses* angleExpressions, int maxOrderA, const analyzer::vector<unsigned int>& settingsA_cos,
    const analyzer::FIexpresses* dihedralExpressions, int maxOrderD, const analyzer::vector<unsigned int>& settingsD_cos)
{
    clock_t startTotal = clock();

    long int threadCount = dict.search((long int)1, "threadCount");
    printf("threadCount: %ld\n", threadCount);

    const char * DataFileName = dict.search("./data/origin.txt","DataFileName");
    printf("SFI DataSwitch started, DataFileName: %s\n", DataFileName);

    const bool PowerNormalization = dict.search(false, "SFI.PowerNormalization");
    printf("  SFI.PowerNormalization: %s\n", PowerNormalization ? "true" : "false");

    const bool useAngles = (angleExpressions != NULL && maxOrderA > 0 && settingsA_cos.count() == (size_t)maxOrderA);
    if (useAngles) {
        printf("  Using cos-only angle FI with orderA = %d, settingsA count = %zu\n", maxOrderA, settingsA_cos.count());
    }
    const bool useDihedrals = (dihedralExpressions != NULL && maxOrderD > 0 && settingsD_cos.count() == (size_t)maxOrderD);
    if (useDihedrals) {
        printf("  Using cos-only dihedral FI with orderD = %d, settingsD count = %zu\n", maxOrderD, settingsD_cos.count());
    }

    const char* dataFormat = dict.search("mat", "DataFormat");
    const bool ifDataXYZ = dict.search(false, "IfDataXYZ");
    bool useXYZ = false;
    if (strcmp(dataFormat, "xyz") == 0) {
        useXYZ = true;
    } else if (strcmp(dataFormat, "mat") == 0) {
        useXYZ = false;
    } else {
        useXYZ = ifDataXYZ;
    }

    size_t row = 0;
    size_t col = 0;
    analyzer::vector<double> matrixStorage;
    analyzer::vector<double> angleCosineMatrixStorage;
    analyzer::vector<double> dihedralCosineMatrixStorage;
    const analyzer::vector<double>* matrix = NULL;
    const analyzer::vector<double>* angleCosineMatrix = NULL;
    const analyzer::vector<double>* dihedralCosineMatrix = NULL;

    clock_t startDataLoad = clock();
    XYZsetting xyzSetting;
    if (useXYZ) {
        int error = xyzSetting.build(dict, outputPath,
            useAngles ? &angleCosineMatrixStorage : NULL,
            useDihedrals ? &dihedralCosineMatrixStorage : NULL);
        if (error != 0) {
            return error;
        }
        matrix = &xyzSetting.GetMat();
        row = xyzSetting.GetRow();
        col = xyzSetting.GetCol();

        // 如果需要键角，从 XYZ 文件直接计算键角余弦矩阵。
        if (useAngles) {
            angleCosineMatrix = &angleCosineMatrixStorage;
        }
        if (useDihedrals) {
            dihedralCosineMatrix = &dihedralCosineMatrixStorage;
        }
    } else {
        FILE* inputMat = fopen(DataFileName, "r");
        if (inputMat == NULL) {
            printf("Error when opening data file: %s\n", DataFileName);
            return 1234234;
        }
        int error = analyzer::ParserDataMatrix(inputMat, matrixStorage, row, col);
        fclose(inputMat);
        if (error != 0) {
            printf("Error when parsing data file: %s, error: %d\n", DataFileName, error);
            return error;
        }
        matrix = &matrixStorage;

        // mat 格式不支持键角和二面角
        if (useAngles || useDihedrals) {
            printf("Error: Angle and dihedral support requires XYZ format, not mat format.\n");
            return -1;
        }
    }

    clock_t endDataLoad = clock();
    double dataLoadTime = (double)(endDataLoad - startDataLoad) / CLOCKS_PER_SEC;
    printf("Data loading time: %.3f seconds\n", dataLoadTime);

    printf("row: %zu, col: %zu\n", row, col);

    bool hasEnergy;
    const size_t xCount = expressions.getXCount();
    if (xCount + 1 == col) {
        hasEnergy = true;
    } else if (xCount == col) {
        hasEnergy = false;
    } else {
        printf("Error: SFI XCount != col && XCount + 1 != col\n");
        return -1;
    }

    const size_t bondSFICount = expressions.getFormulaCount();
    size_t angleSFICount = 0;
    size_t dihedralSFICount = 0;

    if (useAngles) {
        // 计算键角 SFI 的总列数
        // 对每个键角 FI，根据其阶数应用相应的 settingsA
        for (size_t fi = 0; fi < angleExpressions->getItems().count(); ++fi) {
            const int order = angleExpressions->getItems()[fi].getOrder();
            if (order > 0 && order <= maxOrderA && (size_t)order <= settingsA_cos.count()) {
                const unsigned int harmonicCount = settingsA_cos[(size_t)order - 1];
                // 每个 FI 生成 harmonicCount 个 cos(n*theta) 特征，n=1...harmonicCount。
                angleSFICount += harmonicCount;
            }
        }
        if (angleSFICount == 0) {
            printf("Error: angle FI configuration produces zero output columns for SFI.orderA=%d.\n", maxOrderA);
            return -13;
        }
        printf("  Total angle SFI columns: %zu\n", angleSFICount);
    }

    if (useDihedrals) {
        for (size_t fi = 0; fi < dihedralExpressions->getItems().count(); ++fi) {
            const int order = dihedralExpressions->getItems()[fi].getOrder();
            if (order > 0 && order <= maxOrderD && (size_t)order <= settingsD_cos.count()) {
                dihedralSFICount += settingsD_cos[(size_t)order - 1];
            }
        }
        if (dihedralSFICount == 0) {
            printf("Error: dihedral FI configuration produces zero output columns for SFI.orderD=%d.\n", maxOrderD);
            return -21;
        }
        printf("  Total dihedral SFI columns: %zu\n", dihedralSFICount);
    }

    const size_t totalOutputCols = bondSFICount + angleSFICount + dihedralSFICount;
    const size_t ldi = col;
    const size_t coli = hasEnergy ? (col - 1) : col;
    const size_t ldo = hasEnergy ? (totalOutputCols + 1) : totalOutputCols;

    analyzer::vector<double> outputMatrix;
    outputMatrix.resize(row * ldo);

    // 计算键长 SFI 值
    clock_t startBondCompute = clock();
    int computeError;
    if (threadCount > 1) {
        computeError = expressions.compute(
            static_cast<unsigned int>(threadCount),
            matrix->ptr(), ldi, row, coli,
            outputMatrix.ptr(), ldo, row, bondSFICount, PowerNormalization);
    } else {
        computeError = expressions.compute(
            matrix->ptr(), ldi, row, coli,
            outputMatrix.ptr(), ldo, row, bondSFICount, PowerNormalization);
    }

    if (computeError != 0) {
        printf("Error when computing SFI values: %d\n", computeError);
        return computeError;
    }

    clock_t endBondCompute = clock();
    double bondComputeTime = (double)(endBondCompute - startBondCompute) / CLOCKS_PER_SEC;
    printf("Bond SFI computation time: %.3f seconds\n", bondComputeTime);

    // 计算键角 SFI 值
    if (useAngles && angleCosineMatrix != NULL) {
        clock_t startAngleCompute = clock();
        const size_t angleLdi = angleCosineMatrix->count() / row;
        const size_t angleColi = hasEnergy ? (angleLdi - 1) : angleLdi;

        printf("Computing cos-only angle SFI transformations with Chebyshev recurrence...\n");

        // 输入已经是 cos(theta)，使用 T_n(cos(theta)) = cos(n*theta) 计算键角变换。
        int angleComputeError;
        if (threadCount > 1) {
            angleComputeError = angleExpressions->computeAngleCosTransform(
                static_cast<unsigned int>(threadCount),
                angleCosineMatrix->ptr(), angleLdi, row, angleColi,
                outputMatrix.ptr() + bondSFICount, ldo, row, angleSFICount,
                settingsA_cos);
        } else {
            angleComputeError = angleExpressions->computeAngleCosTransform(
                angleCosineMatrix->ptr(), angleLdi, row, angleColi,
                outputMatrix.ptr() + bondSFICount, ldo, row, angleSFICount,
                settingsA_cos);
        }

        if (angleComputeError != 0) {
            printf("Error when computing angle transformations: %d\n", angleComputeError);
            return angleComputeError;
        }

        clock_t endAngleCompute = clock();
        double angleComputeTime = (double)(endAngleCompute - startAngleCompute) / CLOCKS_PER_SEC;
        printf("Angle SFI computation time: %.3f seconds\n", angleComputeTime);
    }

    // 计算二面角 SFI 值
    if (useDihedrals && dihedralCosineMatrix != NULL) {
        clock_t startDihedralCompute = clock();
        const size_t dihedralLdi = dihedralCosineMatrix->count() / row;
        const size_t dihedralColi = hasEnergy ? (dihedralLdi - 1) : dihedralLdi;

        printf("Computing cos-only dihedral SFI transformations with Chebyshev recurrence...\n");

        int dihedralComputeError;
        double* dihedralOutput = outputMatrix.ptr() + bondSFICount + angleSFICount;
        if (threadCount > 1) {
            dihedralComputeError = dihedralExpressions->computeCosTransform(
                static_cast<unsigned int>(threadCount),
                dihedralCosineMatrix->ptr(), dihedralLdi, row, dihedralColi,
                dihedralOutput, ldo, row, dihedralSFICount, settingsD_cos);
        } else {
            dihedralComputeError = dihedralExpressions->computeCosTransform(
                dihedralCosineMatrix->ptr(), dihedralLdi, row, dihedralColi,
                dihedralOutput, ldo, row, dihedralSFICount, settingsD_cos);
        }

        if (dihedralComputeError != 0) {
            printf("Error when computing dihedral transformations: %d\n", dihedralComputeError);
            return dihedralComputeError;
        }

        clock_t endDihedralCompute = clock();
        double dihedralComputeTime = (double)(endDihedralCompute - startDihedralCompute) / CLOCKS_PER_SEC;
        printf("Dihedral SFI computation time: %.3f seconds\n", dihedralComputeTime);
    }

    // 复制能量值到最后一列
    if (hasEnergy) {
        for (size_t i = 0; i < row; ++i) {
            outputMatrix[i * ldo + totalOutputCols] = (*matrix)[i * ldi + coli];
        }
    }

    clock_t startFileSave = clock();
    const char * OutputFileName = dict.search("output","OutputFileName");
    std::string fileName = OutputFileName;
    std::string outputFilePath = ChangeSuffix(fileName, ".sfi.txt");
    hyperlex::FilePath filetemp;
    hyperlex::FilePath OutputFilePath;
    OutputFilePath.build(outputPath);
    filetemp.build(outputFilePath.c_str());
    OutputFilePath += filetemp;

    FILE* outputFile = fopen(OutputFilePath.path(), "w");
    if (outputFile == NULL) {
        printf("Error opening output file for writing: %s\n", OutputFilePath.path());
        return 1234;
    }

    fprintf(outputFile, "# SFI values generated by FIanalyzer\n");
    fprintf(outputFile, "# Number of data points: %zu\n", row);
    fprintf(outputFile, "# Number of bond SFI formulas: %zu\n", bondSFICount);
    if (useAngles) {
        fprintf(outputFile, "# Number of angle FI expressions: %zu\n", angleExpressions->getItems().count());
        fprintf(outputFile, "# Total angle SFI columns: %zu\n", angleSFICount);
        fprintf(outputFile, "# Angle basis: cos(n*theta) = T_n(cos(theta)), n starts at 1\n");
    }
    if (useDihedrals) {
        fprintf(outputFile, "# Number of dihedral FI expressions: %zu\n", dihedralExpressions->getItems().count());
        fprintf(outputFile, "# Total dihedral SFI columns: %zu\n", dihedralSFICount);
        fprintf(outputFile, "# Dihedral key: (B,C,A,D), B<C and A<D; center-edge and endpoint-pair slots are distinct\n");
        fprintf(outputFile, "# Dihedral basis: cos(n*phi) = T_n(cos(phi)), n starts at 1\n");
    }
    if (hasEnergy) {
        fprintf(outputFile, "# Including energy values\n");
    }
    fprintf(outputFile, "\n");

    for (size_t i = 0; i < row; ++i) {
        for (size_t j = 0; j < ldo; ++j) {
            fprintf(outputFile, "%25.16E ", outputMatrix[i * ldo + j]);
        }
        fprintf(outputFile, "\n");
    }

    fclose(outputFile);
    printf("SFI DataSwitch output file generated: %s\n", OutputFilePath.path());

    clock_t endFileSave = clock();
    double fileSaveTime = (double)(endFileSave - startFileSave) / CLOCKS_PER_SEC;
    printf("File saving time: %.3f seconds\n", fileSaveTime);

    clock_t endTotal = clock();
    double totalTime = (double)(endTotal - startTotal) / CLOCKS_PER_SEC;
    printf("SFIDataMatrixSwitch total time: %.3f seconds\n", totalTime);

    return 0;
}

int static SFI(hyperlex::dictionary&dict, const char* outputPath, analyzer::FIexpresses & expressions)
{
    printf("SFI task started:\n");

    const int maxOrder = (int)dict.search((long int)-1, "SFI.order");
    const bool CcodePrint = dict.search(false, "SFI.CcodePrint");
    const bool FortranCodePrint = dict.search(false, "SFI.FortranCodePrint");
    const bool DataSwitch = dict.search(false, "SFI.DataSwitch");
    const bool PowerNormalization = dict.search(false, "SFI.PowerNormalization");

    // 读取键角相关参数
    const char* AngleFileName = dict.search("", "AngleFileName");
    const bool UsingAngle = dict.search(false, "UsingAngle");
    const char* DihedralFileName = dict.search("", "DihedralFileName");
    const bool UsingDihedral = dict.search(false, "UsingDihedral");

    // 读取 orderA 和 settingsA 参数
    const int maxOrderA = (int)dict.search((long int)-1, "SFI.orderA");
    const int maxOrderD = (int)dict.search((long int)-1, "SFI.orderD");

    analyzer::vector<unsigned int> settingsA_cos;
    size_t settingsACount = 0;
    hyperlex::dictionary::Ktype settingsAType = hyperlex::dictionary::null_;
    hyperlex::dictionary::element* settingsAArray = dict.search(settingsACount, settingsAType, "SFI.settingsA");

    analyzer::vector<unsigned int> settingsD_cos;
    size_t settingsDCount = 0;
    hyperlex::dictionary::Ktype settingsDType = hyperlex::dictionary::null_;
    hyperlex::dictionary::element* settingsDArray = dict.search(settingsDCount, settingsDType, "SFI.settingsD");

    if (UsingAngle) {
        if (maxOrderA <= 0) {
            printf("Error: UsingAngle=true requires SFI.orderA > 0, got %d.\n", maxOrderA);
            return -6;
        }
        if (strlen(AngleFileName) == 0) {
            printf("Error: UsingAngle=true requires AngleFileName.\n");
            return -7;
        }
        if (settingsAArray == NULL || settingsAType != hyperlex::dictionary::dictionary_ || settingsACount == 0) {
            printf("Error: UsingAngle=true requires SFI.settingsA as a non-empty dictionary array.\n");
            return -8;
        }
        if (settingsACount != (size_t)maxOrderA) {
            printf("Error: SFI.settingsA count (%zu) must equal SFI.orderA (%d).\n", settingsACount, maxOrderA);
            return -9;
        }

        bool hasAngleHarmonic = false;
        for (size_t i = 0; i < settingsACount; ++i) {
            hyperlex::dictionary* one = settingsAArray[i].dd;
            if (one == NULL) {
                printf("Error: SFI.settingsA[%zu] is null.\n", i);
                return -2;
            }

            hyperlex::dictionary::Ktype cosType = hyperlex::dictionary::null_;
            const hyperlex::dictionary::element cosElement = one->search(cosType, "cos");
            if (cosType == hyperlex::dictionary::null_) {
                hyperlex::dictionary::Ktype legacyType = hyperlex::dictionary::null_;
                one->search(legacyType, "sincos");
                if (legacyType != hyperlex::dictionary::null_) {
                    printf("Error: SFI.settingsA[%zu].sincos is no longer supported; use .cos.\n", i);
                } else {
                    printf("Error: SFI.settingsA[%zu].cos is required.\n", i);
                }
                return -10;
            }
            if (cosType != hyperlex::dictionary::int_ || cosElement.ii < 0) {
                printf("Error: SFI.settingsA[%zu].cos must be a non-negative integer.\n", i);
                return -11;
            }

            const unsigned int harmonicCount = (unsigned int)cosElement.ii;
            settingsA_cos.append(harmonicCount);
            hasAngleHarmonic = hasAngleHarmonic || (harmonicCount > 0);
            printf("  settingsA[%zu]: cos=%u\n", i, harmonicCount);
        }

        if (!hasAngleHarmonic) {
            printf("Error: UsingAngle=true requires at least one positive SFI.settingsA[].cos value.\n");
            return -12;
        }
    }

    if (UsingDihedral) {
        if (maxOrderD <= 0) {
            printf("Error: UsingDihedral=true requires SFI.orderD > 0, got %d.\n", maxOrderD);
            return -14;
        }
        if (strlen(DihedralFileName) == 0) {
            printf("Error: UsingDihedral=true requires DihedralFileName.\n");
            return -15;
        }
        if (settingsDArray == NULL || settingsDType != hyperlex::dictionary::dictionary_ || settingsDCount == 0) {
            printf("Error: UsingDihedral=true requires SFI.settingsD as a non-empty dictionary array.\n");
            return -16;
        }
        if (settingsDCount != (size_t)maxOrderD) {
            printf("Error: SFI.settingsD count (%zu) must equal SFI.orderD (%d).\n", settingsDCount, maxOrderD);
            return -17;
        }

        bool hasDihedralHarmonic = false;
        for (size_t i = 0; i < settingsDCount; ++i) {
            hyperlex::dictionary* one = settingsDArray[i].dd;
            if (one == NULL) {
                printf("Error: SFI.settingsD[%zu] is null.\n", i);
                return -18;
            }

            hyperlex::dictionary::Ktype cosType = hyperlex::dictionary::null_;
            const hyperlex::dictionary::element cosElement = one->search(cosType, "cos");
            if (cosType == hyperlex::dictionary::null_) {
                hyperlex::dictionary::Ktype legacyType = hyperlex::dictionary::null_;
                one->search(legacyType, "sincos");
                if (legacyType != hyperlex::dictionary::null_) {
                    printf("Error: SFI.settingsD[%zu].sincos is not supported; use .cos.\n", i);
                } else {
                    printf("Error: SFI.settingsD[%zu].cos is required.\n", i);
                }
                return -19;
            }
            if (cosType != hyperlex::dictionary::int_ || cosElement.ii < 0) {
                printf("Error: SFI.settingsD[%zu].cos must be a non-negative integer.\n", i);
                return -20;
            }

            const unsigned int harmonicCount = (unsigned int)cosElement.ii;
            settingsD_cos.append(harmonicCount);
            hasDihedralHarmonic = hasDihedralHarmonic || (harmonicCount > 0);
            printf("  settingsD[%zu]: cos=%u\n", i, harmonicCount);
        }

        if (!hasDihedralHarmonic) {
            printf("Error: UsingDihedral=true requires at least one positive SFI.settingsD[].cos value.\n");
            return -22;
        }
    }

    if (maxOrder <= 0) {
        printf("Error: invalid SFI.order = %d\n", maxOrder);
        return -1;
    }

    printf("  SFI.order: %d\n", maxOrder);
    printf("  SFI.CcodePrint: %s\n", CcodePrint ? "true" : "false");
    printf("  SFI.FortranCodePrint: %s\n", FortranCodePrint ? "true" : "false");
    printf("  SFI.DataSwitch: %s\n", DataSwitch ? "true" : "false");
    printf("  SFI.PowerNormalization: %s\n", PowerNormalization ? "true" : "false");
    printf("  AngleFileName: %s\n", AngleFileName);
    printf("  UsingAngle: %s\n", UsingAngle ? "true" : "false");
    printf("  DihedralFileName: %s\n", DihedralFileName);
    printf("  UsingDihedral: %s\n", UsingDihedral ? "true" : "false");
    if (maxOrderA > 0) {
        printf("  SFI.orderA: %d\n", maxOrderA);
    }
    if (maxOrderD > 0) {
        printf("  SFI.orderD: %d\n", maxOrderD);
    }

    analyzer::vector<analyzer::Setting> settings;
    size_t settingCount = 0;
    hyperlex::dictionary::Ktype settingType = hyperlex::dictionary::null_;
    hyperlex::dictionary::element* settingArray = dict.search(settingCount, settingType, "SFI.settings");

    if (settingArray != NULL && settingType == hyperlex::dictionary::dictionary_ && settingCount > 0) {
        for (size_t i = 0; i < settingCount; ++i) {
            analyzer::Setting s;
            hyperlex::dictionary* one = settingArray[i].dd;
            if (one == NULL) {
                printf("Error: SFI.settings[%zu] is null.\n", i);
                return -2;
            }

            s.poly = (unsigned int)one->search((long int)0, "poly");
            s.reciprocal = (unsigned int)one->search((long int)0, "reciprocal");
            s.exp = (unsigned int)one->search((long int)0, "exp");
            s.gaussian = (unsigned int)one->search((long int)0, "gaussian");
            s.cos = (unsigned int)one->search((long int)0, "cos");
            s.sin = (unsigned int)one->search((long int)0, "sin");
            settings.append(s);

            printf("  settings[%zu]: poly=%u reciprocal=%u exp=%u gaussian=%u cos=%u sin=%u sum=%zu\n",
                i, s.poly, s.reciprocal, s.exp, s.gaussian, s.cos, s.sin, s.sum());
        }
    } else {
        analyzer::Setting s;
        s.poly = (unsigned int)dict.search((long int)0, "SFI.poly");
        s.reciprocal = (unsigned int)dict.search((long int)0, "SFI.reciprocal");
        s.exp = (unsigned int)dict.search((long int)0, "SFI.exp");
        s.gaussian = (unsigned int)dict.search((long int)0, "SFI.gaussian");
        s.cos = (unsigned int)dict.search((long int)0, "SFI.cos");
        s.sin = (unsigned int)dict.search((long int)0, "SFI.sin");
        settings.append(s);

        printf("  SFI.settings not found as array; fallback to single SFI.* setting.\n");
        printf("  settings[0]: poly=%u reciprocal=%u exp=%u gaussian=%u cos=%u sin=%u sum=%zu\n",
            s.poly, s.reciprocal, s.exp, s.gaussian, s.cos, s.sin, s.sum());
    }

    if (settings.count() < (size_t)maxOrder) {
        printf("  Warning: settings count (%zu) < SFI.order (%d). ", settings.count(), maxOrder);
        printf("build() will skip source FI orders that have no corresponding setting.\n");
    }

    // 读取键角 FI 表达式（如果启用）
    analyzer::FIexpresses angleExpressions;
    if (UsingAngle) {
        printf("\nLoading angle FI file: %s\n", AngleFileName);
        FILE* angleFp = fopen(AngleFileName, "r");
        if (angleFp == NULL) {
            printf("Error when opening angle FI file: %s\n", AngleFileName);
            return -5;
        }
        int error = angleExpressions.build(angleFp);
        fclose(angleFp);
        if (error != 0) {
            printf("Error when reading angle FI file: %s, error: %d\n", AngleFileName, error);
            return error;
        }
        printf("Angle FI file loaded successfully.\n");
        angleExpressions.demo(stdout);
    }

    analyzer::FIexpresses dihedralExpressions;
    if (UsingDihedral) {
        printf("\nLoading dihedral FI file: %s\n", DihedralFileName);
        FILE* dihedralFp = fopen(DihedralFileName, "r");
        if (dihedralFp == NULL) {
            printf("Error when opening dihedral FI file: %s\n", DihedralFileName);
            return -23;
        }
        int error = dihedralExpressions.build(dihedralFp);
        fclose(dihedralFp);
        if (error != 0) {
            printf("Error when reading dihedral FI file: %s, error: %d\n", DihedralFileName, error);
            return error;
        }
        printf("Dihedral FI file loaded successfully.\n");
        dihedralExpressions.demo(stdout);
    }

    analyzer::SFIexpresses sfi;
    try {
        sfi.build(expressions, maxOrder, settings);
    }
    catch (const std::exception& ex) {
        printf("Error when building SFIexpresses: %s\n", ex.what());
        return -3;
    }
    catch (...) {
        printf("Error when building SFIexpresses: unknown exception.\n");
        return -4;
    }

    printf("SFI build test finished successfully.\n");
    printf("SFI demo output:\n");
    sfi.demo(stdout);

    if (DataSwitch) {
        int sw = SFIDataMatrixSwitch(dict, outputPath, sfi,
            (UsingAngle && angleExpressions.getItems().count() > 0) ? &angleExpressions : NULL,
            maxOrderA, settingsA_cos,
            (UsingDihedral && dihedralExpressions.getItems().count() > 0) ? &dihedralExpressions : NULL,
            maxOrderD, settingsD_cos);
        if (sw != 0) {
            return sw;
        }
    }

    const char * OutputFileName = dict.search("output","OutputFileName");
    std::string fileName = OutputFileName;

    if (CcodePrint) {
        int ec = EmitCodeFile(outputPath, fileName, ".sfi.c", "SFI C", sfi, &analyzer::SFIexpresses::printCcode);
        if (ec != 0) {
            return ec;
        }
    }
    if (FortranCodePrint) {
        int ec = EmitCodeFile(outputPath, fileName, ".sfi.f90", "SFI Fortran", sfi, &analyzer::SFIexpresses::printFortrancode);
        if (ec != 0) {
            return ec;
        }
    }

    printf("SFI task finished: build + demo + optional DataSwitch/codegen completed.\n");
    return 0;
}
