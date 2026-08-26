#ifndef FIANALYZER_SFI_V02_SFI_V02_H
#define FIANALYZER_SFI_V02_SFI_V02_H

#include "../analyzer.h"

#include <cstddef>
#include <string>
#include <vector>

namespace analyzer
{
namespace sfi_v02
{
    enum class GeometryKind
    {
        Bond,
        Angle,
        Dihedral
    };

    enum class RadialMap
    {
        NotApplicable,
        Rational,
        Morse,
        Gaussian
    };

    enum class Basis
    {
        Chebyshev,
        Legendre
    };

    const char* ToString(GeometryKind value);
    const char* ToString(RadialMap value);
    const char* ToString(Basis value);

    struct ChannelSpec
    {
        ChannelSpec();
        ChannelSpec(GeometryKind geometryValue, RadialMap radialMapValue, Basis basisValue);

        GeometryKind geometry;
        RadialMap radialMap;
        Basis basis;
    };

    struct Config
    {
        Config();

        std::vector<ChannelSpec> channels;
        unsigned int bondMaxDegree;
        unsigned int angleMaxDegree;
        unsigned int dihedralMaxDegree;
        double m;
        double a;
        double b;
        double c;
    };

    struct OrbitInfo
    {
        OrbitInfo();

        std::size_t sourceFIIndex;
        std::vector<std::size_t> variables;
    };

    struct ColumnInfo
    {
        ColumnInfo();

        std::size_t column;
        std::size_t channelIndex;
        GeometryKind geometry;
        RadialMap radialMap;
        Basis basis;
        std::size_t orbitIndex;
        std::size_t sourceFIIndex;
        std::size_t orbitSize;
        unsigned int degree;
    };

    class Evaluator;

    class Workspace
    {
    public:
        Workspace();

        std::size_t capacityBytes(void) const;
        bool isPrepared(void) const;
        double frameEnergy(void) const;

    private:
        friend class Evaluator;

        const Evaluator* owner;
        std::vector<double> coordinates;
        std::vector<double> pairDx;
        std::vector<double> pairDy;
        std::vector<double> pairDz;
        std::vector<double> pairDistance;
        std::vector<double> geometryValues;
        std::vector<double> mappedBondValues;
        std::vector<double> previous2;
        std::vector<double> previous1;
        std::vector<double> orbitSums;
        std::vector<double> orbitCorrections;
        std::vector<double> normalX;
        std::vector<double> normalY;
        std::vector<double> normalZ;
        std::vector<double> normalLength;
    };

    class Evaluator
    {
    public:
        Evaluator();

        bool build(std::size_t atomCount,
                   const FIexpresses* bondFI,
                   const FIexpresses* angleFI,
                   const FIexpresses* dihedralFI,
                   const double* bondInverseScales,
                   std::size_t scaleCount,
                   const Config& config,
                   std::string& error);

        bool prepareWorkspace(Workspace& workspace, std::string& error) const;
        bool evaluate(const xyz& frame,
                      double* output,
                      std::size_t outputCount,
                      Workspace& workspace,
                      std::string& error) const;

        std::size_t outputCount(void) const;
        const std::vector<ColumnInfo>& columns(void) const;
        const Config& config(void) const;
        std::size_t atomCount(void) const;
        std::size_t variableCount(GeometryKind geometry) const;
        const std::vector<OrbitInfo>& orbits(GeometryKind geometry) const;
        bool isBuilt(void) const;

    private:
        void clear(void);
        static void pairVector(const Workspace& workspace,
                               std::size_t atomCount,
                               std::size_t from,
                               std::size_t to,
                               double& x,
                               double& y,
                               double& z);
        static double pairLength(const Workspace& workspace,
                                 std::size_t atomCount,
                                 std::size_t first,
                                 std::size_t second);
        static void storeOrbitSums(const double* values,
                                   std::size_t variableCount,
                                   const std::vector<std::size_t>& variableToOrbit,
                                   const std::vector<OrbitInfo>& orbits,
                                   unsigned int degree,
                                   unsigned int maxDegree,
                                   std::size_t outputOffset,
                                   double* output,
                                   Workspace& workspace);
        bool evaluateChannel(std::size_t channelIndex,
                             const double* mapped,
                             double* output,
                             Workspace& workspace,
                             std::string& error) const;

        bool built;
        std::size_t atomCountValue;
        Config configValue;
        std::size_t variableCounts[3];
        std::size_t geometryOffsets[3];
        bool activeGeometry[3];
        std::size_t activeVariableCount;
        std::size_t maximumVariableCount;
        std::size_t maximumOrbitCount;
        std::size_t pairCount;
        std::size_t featureCount;

        std::vector<double> inverseBondScales;
        std::vector<OrbitInfo> orbitLists[3];
        std::vector<std::size_t> variableToOrbit[3];
        std::vector<RadialMap> uniqueBondMaps;
        std::vector<std::size_t> channelMapSlots;
        std::vector<std::size_t> channelOutputOffsets;
        std::vector<ColumnInfo> columnList;
    };
}
}

#endif
