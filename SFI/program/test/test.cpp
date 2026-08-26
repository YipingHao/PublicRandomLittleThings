#include "../code/dictionary.h"
#include "../code/analyzer.h"
#include <cmath>
#include <cstdio>
#include <cstring>

int TestSFIv02(void);

static bool NearlyEqual(double left, double right, double tolerance)
{
    return std::fabs(left - right) <= tolerance;
}

static int TestAngleCosineInterfaces(void)
{
    analyzer::vector<const char*> names;
    names.append("X");
    names.append("X");
    names.append("X");

    analyzer::vector<double> coordinates;
    coordinates.append(-1.0); coordinates.append(0.0); coordinates.append(0.0);
    coordinates.append( 0.0); coordinates.append(0.0); coordinates.append(0.0);
    coordinates.append( 1.0); coordinates.append(0.0); coordinates.append(0.0);

    analyzer::xyz one;
    const double energy = 2.5;
    if (one.build(energy, names, coordinates) != 0)
    {
        printf("TestAngleCosineInterfaces: xyz build failed.\n");
        return -101;
    }

    double radians[4];
    double cosines[4];
    one.PrintAngle(radians);
    one.PrintAngleCosines(cosines);
    for (size_t i = 0; i < 3; ++i)
    {
        if (!NearlyEqual(std::cos(radians[i]), cosines[i], 1.0e-14))
        {
            printf("TestAngleCosineInterfaces: direct interface mismatch at %zu.\n", i);
            return -102;
        }
    }
    if (!NearlyEqual(radians[3], energy, 0.0) || !NearlyEqual(cosines[3], energy, 0.0))
    {
        printf("TestAngleCosineInterfaces: energy mismatch.\n");
        return -103;
    }

    analyzer::xyzFile file;
    if (file.append(one) != 0)
    {
        printf("TestAngleCosineInterfaces: xyzFile append failed.\n");
        return -104;
    }

    analyzer::vector<double> angleMatrix;
    analyzer::vector<double> angleCosineMatrix;
    analyzer::vector<double> bondMatrix;
    analyzer::vector<double> combinedAngleCosineMatrix;
    file.PrintAngles(angleMatrix);
    file.PrintAngleCosines(angleCosineMatrix);
    file.PrintRAndAngleCosines(bondMatrix, combinedAngleCosineMatrix);

    if (angleMatrix.count() != 4 || angleCosineMatrix.count() != 4 || combinedAngleCosineMatrix.count() != 4)
    {
        printf("TestAngleCosineInterfaces: unexpected matrix dimensions.\n");
        return -105;
    }
    for (size_t i = 0; i < 3; ++i)
    {
        if (!NearlyEqual(std::cos(angleMatrix[i]), angleCosineMatrix[i], 1.0e-14) ||
            !NearlyEqual(angleCosineMatrix[i], combinedAngleCosineMatrix[i], 1.0e-14))
        {
            printf("TestAngleCosineInterfaces: xyzFile interface mismatch at %zu.\n", i);
            return -106;
        }
    }

    return 0;
}

static int TestDihedralCosineInterfaces(void)
{
    analyzer::vector<const char*> names;
    names.append("X"); names.append("X"); names.append("X"); names.append("X");

    // 直角四面体；按中心边 (0,1),(0,2),(0,3),(1,2),(1,3),(2,3) 排列。
    analyzer::vector<double> coordinates;
    coordinates.append(0.0); coordinates.append(0.0); coordinates.append(0.0);
    coordinates.append(1.0); coordinates.append(0.0); coordinates.append(0.0);
    coordinates.append(0.0); coordinates.append(1.0); coordinates.append(0.0);
    coordinates.append(0.0); coordinates.append(0.0); coordinates.append(1.0);

    analyzer::xyz one;
    const double energy = -1.25;
    if (one.build(energy, names, coordinates) != 0)
    {
        printf("TestDihedralCosineInterfaces: xyz build failed.\n");
        return -301;
    }

    double direct[7];
    one.PrintDihedralCosines(direct);
    const double invSqrt3 = 1.0 / std::sqrt(3.0);
    const double expected[6] = { 0.0, 0.0, 0.0, invSqrt3, invSqrt3, invSqrt3 };
    for (size_t i = 0; i < 6; ++i)
    {
        if (!NearlyEqual(direct[i], expected[i], 1.0e-14))
        {
            printf("TestDihedralCosineInterfaces: ordering/value mismatch at %zu.\n", i);
            return -302;
        }
    }
    if (!NearlyEqual(direct[6], energy, 0.0))
    {
        printf("TestDihedralCosineInterfaces: energy mismatch.\n");
        return -303;
    }

    // 交换原子 0/1 后，按同一置换映射中心边与端点对，二面角值应保持一致。
    analyzer::vector<double> swappedCoordinates;
    const size_t atomPermutation[4] = { 1, 0, 2, 3 };
    for (size_t i = 0; i < 4; ++i)
    {
        const size_t source = atomPermutation[i];
        swappedCoordinates.append(coordinates[source * 3 + 0]);
        swappedCoordinates.append(coordinates[source * 3 + 1]);
        swappedCoordinates.append(coordinates[source * 3 + 2]);
    }
    analyzer::xyz swapped;
    if (swapped.build(energy, names, swappedCoordinates) != 0)
    {
        return -309;
    }
    double swappedValues[7];
    swapped.PrintDihedralCosines(swappedValues);
    const size_t centerL[6] = { 0, 0, 0, 1, 1, 2 };
    const size_t centerR[6] = { 1, 2, 3, 2, 3, 3 };
    const size_t endL[6] = { 2, 1, 1, 0, 0, 0 };
    const size_t endR[6] = { 3, 3, 2, 3, 2, 1 };
    for (size_t oldIndex = 0; oldIndex < 6; ++oldIndex)
    {
        size_t mappedB = atomPermutation[centerL[oldIndex]];
        size_t mappedC = atomPermutation[centerR[oldIndex]];
        size_t mappedA = atomPermutation[endL[oldIndex]];
        size_t mappedD = atomPermutation[endR[oldIndex]];
        if (mappedC < mappedB) { size_t t = mappedB; mappedB = mappedC; mappedC = t; }
        if (mappedD < mappedA) { size_t t = mappedA; mappedA = mappedD; mappedD = t; }

        size_t mappedIndex = (size_t)(-1);
        size_t site = 0;
        for (size_t B = 0; B < 4; ++B)
        {
            for (size_t C = B + 1; C < 4; ++C)
            {
                for (size_t A = 0; A < 4; ++A)
                {
                    if (A == B || A == C) continue;
                    for (size_t D = A + 1; D < 4; ++D)
                    {
                        if (D == B || D == C) continue;
                        if (B == mappedB && C == mappedC && A == mappedA && D == mappedD)
                        {
                            mappedIndex = site;
                        }
                        ++site;
                    }
                }
            }
        }
        if (mappedIndex == (size_t)(-1) || !NearlyEqual(direct[oldIndex], swappedValues[mappedIndex], 1.0e-14))
        {
            printf("TestDihedralCosineInterfaces: permutation mismatch at %zu.\n", oldIndex);
            return -310;
        }
    }

    analyzer::xyzFile file;
    if (file.append(one) != 0)
    {
        printf("TestDihedralCosineInterfaces: xyzFile append failed.\n");
        return -304;
    }
    analyzer::vector<double> standalone;
    analyzer::vector<double> combined;
    analyzer::vector<double> bonds;
    file.PrintDihedralCosines(standalone);
    file.PrintRAndGeometricCosines(bonds, NULL, &combined);
    if (standalone.count() != 7 || combined.count() != 7)
    {
        printf("TestDihedralCosineInterfaces: unexpected matrix dimensions.\n");
        return -305;
    }
    for (size_t i = 0; i < 7; ++i)
    {
        if (!NearlyEqual(standalone[i], combined[i], 1.0e-14))
        {
            printf("TestDihedralCosineInterfaces: combined interface mismatch at %zu.\n", i);
            return -306;
        }
    }

    // 共线构型的全部法向量退化，约定 cos(phi)=1。
    coordinates.clear();
    for (size_t i = 0; i < 4; ++i)
    {
        coordinates.append((double)i); coordinates.append(0.0); coordinates.append(0.0);
    }
    analyzer::xyz degenerate;
    if (degenerate.build(energy, names, coordinates) != 0)
    {
        return -307;
    }
    double degenerateValues[7];
    degenerate.PrintDihedralCosines(degenerateValues);
    for (size_t i = 0; i < 6; ++i)
    {
        if (!NearlyEqual(degenerateValues[i], 1.0, 0.0))
        {
            printf("TestDihedralCosineInterfaces: degenerate policy mismatch at %zu.\n", i);
            return -308;
        }
    }

    return 0;
}

static int TestChebyshevAngleTransform(void)
{
    FILE* fp = tmpfile();
    if (fp == NULL)
    {
        printf("TestChebyshevAngleTransform: tmpfile failed.\n");
        return -201;
    }
    fprintf(fp, "p[0] = r[0] + r[1];\n");
    fprintf(fp, "p[1] = r[0] * r[1];\n");
    rewind(fp);

    analyzer::FIexpresses expressions;
    const int buildError = expressions.build(fp);
    fclose(fp);
    if (buildError != 0)
    {
        printf("TestChebyshevAngleTransform: FI build failed: %d.\n", buildError);
        return -202;
    }

    analyzer::vector<unsigned int> settingsA_cos;
    settingsA_cos.append(4); // 一阶 FI: n=1...4
    settingsA_cos.append(3); // 二阶 FI: n=1...3

    const size_t rowCount = 5;
    const size_t inputColumns = 2;
    const size_t outputColumns = 7;
    const double endpointStep = 1.0e-8;
    const double input[rowCount * inputColumns] = {
        -1.0, 1.0,
        -1.0 + endpointStep, 1.0,
         0.0, -0.5,
         0.5, 0.75,
         1.0, -1.0
    };
    double singleOutput[rowCount * outputColumns];
    double threadedOutput[rowCount * outputColumns];
    double genericOutput[rowCount * outputColumns];

    int error = expressions.computeAngleCosTransform(
        input, inputColumns, rowCount, inputColumns,
        singleOutput, outputColumns, rowCount, outputColumns, settingsA_cos);
    if (error != 0)
    {
        printf("TestChebyshevAngleTransform: single-thread compute failed: %d.\n", error);
        return -203;
    }

    error = expressions.computeAngleCosTransform(
        3, input, inputColumns, rowCount, inputColumns,
        threadedOutput, outputColumns, rowCount, outputColumns, settingsA_cos);
    if (error != 0)
    {
        printf("TestChebyshevAngleTransform: threaded compute failed: %d.\n", error);
        return -204;
    }

    error = expressions.computeCosTransform(
        input, inputColumns, rowCount, inputColumns,
        genericOutput, outputColumns, rowCount, outputColumns, settingsA_cos);
    if (error != 0)
    {
        printf("TestChebyshevAngleTransform: generic compute failed: %d.\n", error);
        return -209;
    }

    for (size_t row = 0; row < rowCount; ++row)
    {
        const double x0 = input[row * inputColumns];
        const double x1 = input[row * inputColumns + 1];
        const double theta0 = std::acos(x0);
        const double theta1 = std::acos(x1);

        for (unsigned int n = 1; n <= 4; ++n)
        {
            const double expected = std::cos(n * theta0) + std::cos(n * theta1);
            const size_t site = row * outputColumns + (size_t)n - 1;
            if (!NearlyEqual(singleOutput[site], expected, 2.0e-11))
            {
                printf("TestChebyshevAngleTransform: order-1 mismatch at row=%zu n=%u.\n", row, n);
                return -205;
            }
        }
        for (unsigned int n = 1; n <= 3; ++n)
        {
            const double expected = std::cos(n * theta0) * std::cos(n * theta1);
            const size_t site = row * outputColumns + 4 + (size_t)n - 1;
            if (!NearlyEqual(singleOutput[site], expected, 2.0e-11))
            {
                printf("TestChebyshevAngleTransform: order-2 mismatch at row=%zu n=%u.\n", row, n);
                return -206;
            }
        }

        for (size_t column = 0; column < outputColumns; ++column)
        {
            const size_t site = row * outputColumns + column;
            if (!NearlyEqual(singleOutput[site], threadedOutput[site], 1.0e-14))
            {
                printf("TestChebyshevAngleTransform: threading mismatch at row=%zu column=%zu.\n", row, column);
                return -207;
            }
            if (!NearlyEqual(singleOutput[site], genericOutput[site], 1.0e-14))
            {
                printf("TestChebyshevAngleTransform: generic mismatch at row=%zu column=%zu.\n", row, column);
                return -210;
            }
        }
    }

    // T_n'(x) 在 x=-1 处的极限是 (-1)^(n-1)*n^2，不应出现旧 sin(acos(x)) 的奇异导数。
    for (unsigned int n = 1; n <= 4; ++n)
    {
        const size_t endpointSite = (size_t)n - 1;
        const size_t nearbySite = outputColumns + (size_t)n - 1;
        const double finiteDifference = (singleOutput[nearbySite] - singleOutput[endpointSite]) / endpointStep;
        const double sign = ((n % 2) == 1) ? 1.0 : -1.0;
        const double expectedDerivative = sign * (double)(n * n);
        if (!NearlyEqual(finiteDifference, expectedDerivative, 2.0e-5))
        {
            printf("TestChebyshevAngleTransform: endpoint derivative mismatch at n=%u.\n", n);
            return -208;
        }
    }

    return 0;
}

int TestEntrance(hyperlex::dictionary&dict, const char* outputPath)
{
    (void)dict;
    (void)outputPath;

    int error = TestAngleCosineInterfaces();
    if (error != 0)
    {
        return error;
    }

    error = TestChebyshevAngleTransform();
    if (error != 0)
    {
        return error;
    }

    error = TestDihedralCosineInterfaces();
    if (error != 0)
    {
        return error;
    }

    error = TestSFIv02();
    if (error != 0)
    {
        return error;
    }

    printf("Angle/dihedral cosine, Chebyshev, and SFI_v02 regression tests passed.\n");
    return 0;
}
