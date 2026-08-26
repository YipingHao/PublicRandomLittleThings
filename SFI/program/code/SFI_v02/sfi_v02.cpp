#include "sfi_v02.h"

#include <algorithm>
#include <cmath>
#include <limits>
#include <sstream>

namespace analyzer
{
namespace sfi_v02
{
namespace
{
    const std::size_t kNoMapSlot = static_cast<std::size_t>(-1);

    bool TryGeometryIndex(GeometryKind geometry, std::size_t& index)
    {
        switch (geometry)
        {
        case GeometryKind::Bond:
            index = 0;
            return true;
        case GeometryKind::Angle:
            index = 1;
            return true;
        case GeometryKind::Dihedral:
            index = 2;
            return true;
        }
        index = 0;
        return false;
    }

    bool IsValidBasis(Basis basis)
    {
        return basis == Basis::Chebyshev || basis == Basis::Legendre;
    }

    bool CheckedAdd(std::size_t left, std::size_t right, std::size_t& result)
    {
        if (right > std::numeric_limits<std::size_t>::max() - left)
        {
            result = 0;
            return false;
        }
        result = left + right;
        return true;
    }

    bool CheckedMultiply(std::size_t left, std::size_t right, std::size_t& result)
    {
        if (left != 0 && right > std::numeric_limits<std::size_t>::max() / left)
        {
            result = 0;
            return false;
        }
        result = left * right;
        return true;
    }

    bool ChooseTwo(std::size_t value, std::size_t& result)
    {
        if (value < 2)
        {
            result = 0;
            return true;
        }

        std::size_t left = value;
        std::size_t right = value - 1;
        if ((left & 1U) == 0U)
        {
            left /= 2;
        }
        else
        {
            right /= 2;
        }
        return CheckedMultiply(left, right, result);
    }

    bool GeometryVariableCounts(std::size_t atomCount,
                                std::size_t& bondCount,
                                std::size_t& angleCount,
                                std::size_t& dihedralCount)
    {
        if (!ChooseTwo(atomCount, bondCount))
        {
            return false;
        }

        std::size_t wingPairs = 0;
        if (!ChooseTwo(atomCount > 0 ? atomCount - 1 : 0, wingPairs) ||
            !CheckedMultiply(atomCount, wingPairs, angleCount))
        {
            return false;
        }

        std::size_t endpointPairs = 0;
        if (!ChooseTwo(atomCount >= 2 ? atomCount - 2 : 0, endpointPairs) ||
            !CheckedMultiply(bondCount, endpointPairs, dihedralCount))
        {
            return false;
        }
        return true;
    }

    unsigned int DegreeForGeometry(const Config& config, GeometryKind geometry)
    {
        switch (geometry)
        {
        case GeometryKind::Bond:
            return config.bondMaxDegree;
        case GeometryKind::Angle:
            return config.angleMaxDegree;
        case GeometryKind::Dihedral:
            return config.dihedralMaxDegree;
        }
        return 0;
    }

    bool SameChannel(const ChannelSpec& left, const ChannelSpec& right)
    {
        return left.geometry == right.geometry &&
               left.radialMap == right.radialMap &&
               left.basis == right.basis;
    }

    bool ValidateConfig(const Config& config, std::string& error)
    {
        if (config.channels.empty())
        {
            error = "SFI_v02 configuration requires at least one channel.";
            return false;
        }
        if (!std::isfinite(config.m) || !std::isfinite(config.a) ||
            !std::isfinite(config.b) || !std::isfinite(config.c))
        {
            error = "SFI_v02 parameters m, a, b, and c must all be finite.";
            return false;
        }
        if (!(config.m > 0.0) || !(config.a > 0.0) || !(config.b > 0.0))
        {
            error = "SFI_v02 parameters m, a, and b must be greater than zero.";
            return false;
        }

        bool hasGaussianBond = false;
        bool hasMonotoneBond = false;
        bool active[3] = { false, false, false };
        for (std::size_t i = 0; i < config.channels.size(); ++i)
        {
            const ChannelSpec& channel = config.channels[i];
            std::size_t geometryIndex = 0;
            if (!TryGeometryIndex(channel.geometry, geometryIndex))
            {
                error = "SFI_v02 channel has an invalid geometry kind.";
                return false;
            }
            if (!IsValidBasis(channel.basis))
            {
                error = "SFI_v02 channel has an invalid polynomial basis.";
                return false;
            }

            if (channel.geometry == GeometryKind::Bond)
            {
                if (channel.radialMap != RadialMap::Rational &&
                    channel.radialMap != RadialMap::Morse &&
                    channel.radialMap != RadialMap::Gaussian)
                {
                    error = "Every SFI_v02 bond channel must select rational, morse, or gaussian mapping.";
                    return false;
                }
                hasGaussianBond = hasGaussianBond || channel.radialMap == RadialMap::Gaussian;
                hasMonotoneBond = hasMonotoneBond ||
                    channel.radialMap == RadialMap::Rational || channel.radialMap == RadialMap::Morse;
            }
            else if (channel.radialMap != RadialMap::NotApplicable)
            {
                error = "SFI_v02 angle and dihedral channels must use the not-applicable radial map.";
                return false;
            }

            for (std::size_t previous = 0; previous < i; ++previous)
            {
                if (SameChannel(config.channels[previous], channel))
                {
                    error = "SFI_v02 channels must not contain an exact duplicate.";
                    return false;
                }
            }
            active[geometryIndex] = true;
        }

        if (active[0] && config.bondMaxDegree == 0)
        {
            error = "SFI_v02 bond_max_degree must be positive when a bond channel is enabled.";
            return false;
        }
        if (active[1] && config.angleMaxDegree == 0)
        {
            error = "SFI_v02 angle_max_degree must be positive when an angle channel is enabled.";
            return false;
        }
        if (active[2] && config.dihedralMaxDegree == 0)
        {
            error = "SFI_v02 dihedral_max_degree must be positive when a dihedral channel is enabled.";
            return false;
        }
        if (config.c > 0.0 && hasGaussianBond && !hasMonotoneBond)
        {
            error = "With c > 0, a gaussian bond channel requires a rational or morse bond channel.";
            return false;
        }
        return true;
    }

    bool BuildOrbitPartition(const FIexpresses& source,
                             GeometryKind geometry,
                             std::size_t expectedVariableCount,
                             std::vector<OrbitInfo>& orbits,
                             std::vector<std::size_t>& variableToOrbit,
                             std::string& error)
    {
        const char* geometryName = ToString(geometry);
        if (source.getXCount() != expectedVariableCount)
        {
            std::ostringstream message;
            message << "SFI_v02 " << geometryName << " FI variable count is "
                    << source.getXCount() << ", but geometry requires "
                    << expectedVariableCount << ".";
            error = message.str();
            return false;
        }

        orbits.clear();
        variableToOrbit.assign(expectedVariableCount, kNoMapSlot);
        const TemplateSelf::vector<FIexpress>& expressions = source.getItems();
        for (std::size_t expressionIndex = 0; expressionIndex < expressions.count(); ++expressionIndex)
        {
            const FIexpress& expression = expressions[expressionIndex];
            if (expression.getOrder() != 1)
            {
                continue;
            }

            const TemplateSelf::vector<std::size_t>& items = expression.getItems();
            if (expression.getItemCount() == 0 || items.count() != expression.getItemCount())
            {
                std::ostringstream message;
                message << "SFI_v02 " << geometryName << " order-1 FI "
                        << expressionIndex << " has malformed monomial storage.";
                error = message.str();
                return false;
            }

            OrbitInfo orbit;
            orbit.sourceFIIndex = expressionIndex;
            orbit.variables.reserve(items.count());
            const std::size_t orbitIndex = orbits.size();
            for (std::size_t itemIndex = 0; itemIndex < items.count(); ++itemIndex)
            {
                const std::size_t variable = items[itemIndex];
                if (variable >= expectedVariableCount)
                {
                    std::ostringstream message;
                    message << "SFI_v02 " << geometryName << " order-1 FI "
                            << expressionIndex << " contains out-of-range variable "
                            << variable << ".";
                    error = message.str();
                    return false;
                }
                if (variableToOrbit[variable] != kNoMapSlot)
                {
                    std::ostringstream message;
                    message << "SFI_v02 " << geometryName << " variable " << variable
                            << " belongs to more than one order-1 FI orbit.";
                    error = message.str();
                    return false;
                }
                variableToOrbit[variable] = orbitIndex;
                orbit.variables.push_back(variable);
            }
            orbits.push_back(orbit);
        }

        if (orbits.empty())
        {
            std::ostringstream message;
            message << "SFI_v02 " << geometryName << " FI data has no order-1 orbit.";
            error = message.str();
            return false;
        }
        if (source.getOrder1Count() != orbits.size())
        {
            std::ostringstream message;
            message << "SFI_v02 " << geometryName << " FI reports "
                    << source.getOrder1Count() << " order-1 expressions, but contains "
                    << orbits.size() << ".";
            error = message.str();
            return false;
        }
        for (std::size_t variable = 0; variable < expectedVariableCount; ++variable)
        {
            if (variableToOrbit[variable] == kNoMapSlot)
            {
                std::ostringstream message;
                message << "SFI_v02 " << geometryName << " variable " << variable
                        << " is missing from the order-1 FI partition.";
                error = message.str();
                return false;
            }
        }
        return true;
    }

    std::size_t PairIndex(std::size_t first, std::size_t second, std::size_t atomCount)
    {
        return first * (2 * atomCount - first - 1) / 2 + (second - first - 1);
    }

    void NeumaierAdd(double value, double& sum, double& correction)
    {
        const double next = sum + value;
        if (std::fabs(sum) >= std::fabs(value))
        {
            correction += (sum - next) + value;
        }
        else
        {
            correction += (value - next) + sum;
        }
        sum = next;
    }

    std::size_t VectorCapacityBytes(const std::vector<double>& values)
    {
        if (values.capacity() > std::numeric_limits<std::size_t>::max() / sizeof(double))
        {
            return std::numeric_limits<std::size_t>::max();
        }
        return values.capacity() * sizeof(double);
    }
}

const char* ToString(GeometryKind value)
{
    switch (value)
    {
    case GeometryKind::Bond:
        return "bond";
    case GeometryKind::Angle:
        return "angle";
    case GeometryKind::Dihedral:
        return "dihedral";
    }
    return "invalid";
}

const char* ToString(RadialMap value)
{
    switch (value)
    {
    case RadialMap::NotApplicable:
        return "not_applicable";
    case RadialMap::Rational:
        return "rational";
    case RadialMap::Morse:
        return "morse";
    case RadialMap::Gaussian:
        return "gaussian";
    }
    return "invalid";
}

const char* ToString(Basis value)
{
    switch (value)
    {
    case Basis::Chebyshev:
        return "chebyshev";
    case Basis::Legendre:
        return "legendre";
    }
    return "invalid";
}

ChannelSpec::ChannelSpec()
    : geometry(GeometryKind::Bond), radialMap(RadialMap::Rational), basis(Basis::Chebyshev)
{
}

ChannelSpec::ChannelSpec(GeometryKind geometryValue, RadialMap radialMapValue, Basis basisValue)
    : geometry(geometryValue), radialMap(radialMapValue), basis(basisValue)
{
}

Config::Config()
    : bondMaxDegree(0), angleMaxDegree(0), dihedralMaxDegree(0),
      m(1.0), a(1.0), b(1.0), c(1.0)
{
}

OrbitInfo::OrbitInfo() : sourceFIIndex(0)
{
}

ColumnInfo::ColumnInfo()
    : column(0), channelIndex(0), geometry(GeometryKind::Bond),
      radialMap(RadialMap::NotApplicable), basis(Basis::Chebyshev), orbitIndex(0),
      sourceFIIndex(0), orbitSize(0), degree(0)
{
}

Workspace::Workspace() : owner(NULL)
{
}

std::size_t Workspace::capacityBytes(void) const
{
    const std::vector<double>* vectors[] =
    {
        &coordinates, &pairDx, &pairDy, &pairDz, &pairDistance, &geometryValues,
        &mappedBondValues, &previous2, &previous1, &orbitSums, &orbitCorrections,
        &normalX, &normalY, &normalZ, &normalLength
    };
    std::size_t total = 0;
    for (std::size_t i = 0; i < sizeof(vectors) / sizeof(vectors[0]); ++i)
    {
        const std::size_t bytes = VectorCapacityBytes(*vectors[i]);
        if (bytes > std::numeric_limits<std::size_t>::max() - total)
        {
            return std::numeric_limits<std::size_t>::max();
        }
        total += bytes;
    }
    return total;
}

bool Workspace::isPrepared(void) const
{
    return owner != NULL;
}

double Workspace::frameEnergy(void) const
{
    return coordinates.empty()
        ? std::numeric_limits<double>::quiet_NaN()
        : coordinates.back();
}

void Evaluator::pairVector(const Workspace& workspace,
                           std::size_t atomCount,
                           std::size_t from,
                           std::size_t to,
                           double& x,
                           double& y,
                           double& z)
{
    if (from < to)
    {
        const std::size_t pair = PairIndex(from, to, atomCount);
        x = workspace.pairDx[pair];
        y = workspace.pairDy[pair];
        z = workspace.pairDz[pair];
    }
    else
    {
        const std::size_t pair = PairIndex(to, from, atomCount);
        x = -workspace.pairDx[pair];
        y = -workspace.pairDy[pair];
        z = -workspace.pairDz[pair];
    }
}

double Evaluator::pairLength(const Workspace& workspace,
                             std::size_t atomCount,
                             std::size_t first,
                             std::size_t second)
{
    if (second < first)
    {
        std::swap(first, second);
    }
    return workspace.pairDistance[PairIndex(first, second, atomCount)];
}

void Evaluator::storeOrbitSums(const double* values,
                               std::size_t variableCount,
                               const std::vector<std::size_t>& variableToOrbit,
                               const std::vector<OrbitInfo>& orbits,
                               unsigned int degree,
                               unsigned int maxDegree,
                               std::size_t outputOffset,
                               double* output,
                               Workspace& workspace)
{
    const std::size_t orbitCount = orbits.size();
    std::fill(workspace.orbitSums.begin(), workspace.orbitSums.begin() + orbitCount, 0.0);
    std::fill(workspace.orbitCorrections.begin(),
              workspace.orbitCorrections.begin() + orbitCount, 0.0);

    for (std::size_t variable = 0; variable < variableCount; ++variable)
    {
        const std::size_t orbit = variableToOrbit[variable];
        NeumaierAdd(values[variable], workspace.orbitSums[orbit],
                    workspace.orbitCorrections[orbit]);
    }

    for (std::size_t orbit = 0; orbit < orbitCount; ++orbit)
    {
        const double total = workspace.orbitSums[orbit] + workspace.orbitCorrections[orbit];
        const std::size_t column = outputOffset + orbit * static_cast<std::size_t>(maxDegree) +
                                   static_cast<std::size_t>(degree - 1);
        output[column] = total;
    }
}

bool Evaluator::evaluateChannel(std::size_t channelIndex,
                                const double* mapped,
                                double* output,
                                Workspace& workspace,
                                std::string& error) const
{
    const ChannelSpec& channel = configValue.channels[channelIndex];
    std::size_t geometryIndex = 0;
    TryGeometryIndex(channel.geometry, geometryIndex);
    const std::size_t count = variableCounts[geometryIndex];

    for (std::size_t variable = 0; variable < count; ++variable)
    {
        if (!std::isfinite(mapped[variable]))
        {
            error = "SFI_v02 channel input contains a non-finite mapped value.";
            return false;
        }
        workspace.previous2[variable] = 1.0;
        workspace.previous1[variable] = mapped[variable];
    }

    const unsigned int maxDegree = DegreeForGeometry(configValue, channel.geometry);
    storeOrbitSums(&workspace.previous1[0], count, variableToOrbit[geometryIndex],
                   orbitLists[geometryIndex], 1, maxDegree,
                   channelOutputOffsets[channelIndex], output, workspace);

    if (maxDegree >= 2)
    {
        for (unsigned int degree = 2; ; ++degree)
        {
            const double degreeValue = static_cast<double>(degree);
            for (std::size_t variable = 0; variable < count; ++variable)
            {
                const double next = channel.basis == Basis::Chebyshev
                    ? 2.0 * mapped[variable] * workspace.previous1[variable] -
                          workspace.previous2[variable]
                    : ((2.0 * degreeValue - 1.0) * mapped[variable] *
                           workspace.previous1[variable] -
                       (degreeValue - 1.0) * workspace.previous2[variable]) /
                          degreeValue;
                if (!std::isfinite(next))
                {
                    error = "SFI_v02 polynomial recurrence produced a non-finite value.";
                    return false;
                }
                workspace.previous2[variable] = workspace.previous1[variable];
                workspace.previous1[variable] = next;
            }
            storeOrbitSums(&workspace.previous1[0], count, variableToOrbit[geometryIndex],
                           orbitLists[geometryIndex], degree, maxDegree,
                           channelOutputOffsets[channelIndex], output, workspace);
            if (degree == maxDegree)
            {
                break;
            }
        }
    }
    return true;
}

Evaluator::Evaluator()
    : built(false), atomCountValue(0), activeVariableCount(0), maximumVariableCount(0),
      maximumOrbitCount(0), pairCount(0), featureCount(0)
{
    for (std::size_t i = 0; i < 3; ++i)
    {
        variableCounts[i] = 0;
        geometryOffsets[i] = 0;
        activeGeometry[i] = false;
    }
}

void Evaluator::clear(void)
{
    built = false;
    atomCountValue = 0;
    configValue = Config();
    activeVariableCount = 0;
    maximumVariableCount = 0;
    maximumOrbitCount = 0;
    pairCount = 0;
    featureCount = 0;
    inverseBondScales.clear();
    uniqueBondMaps.clear();
    channelMapSlots.clear();
    channelOutputOffsets.clear();
    columnList.clear();
    for (std::size_t i = 0; i < 3; ++i)
    {
        variableCounts[i] = 0;
        geometryOffsets[i] = 0;
        activeGeometry[i] = false;
        orbitLists[i].clear();
        variableToOrbit[i].clear();
    }
}

bool Evaluator::build(std::size_t atomCount,
                      const FIexpresses* bondFI,
                      const FIexpresses* angleFI,
                      const FIexpresses* dihedralFI,
                      const double* bondInverseScales,
                      std::size_t scaleCount,
                      const Config& config,
                      std::string& error)
{
    clear();
    error.clear();
    if (atomCount == 0)
    {
        error = "SFI_v02 requires at least one atom.";
        return false;
    }
    if (!ValidateConfig(config, error))
    {
        return false;
    }

    std::size_t bondCount = 0;
    std::size_t angleCount = 0;
    std::size_t dihedralCount = 0;
    if (!GeometryVariableCounts(atomCount, bondCount, angleCount, dihedralCount))
    {
        error = "SFI_v02 geometry variable count overflows size_t.";
        return false;
    }

    const FIexpresses* sources[3] = { bondFI, angleFI, dihedralFI };
    variableCounts[0] = bondCount;
    variableCounts[1] = angleCount;
    variableCounts[2] = dihedralCount;
    pairCount = bondCount;
    atomCountValue = atomCount;
    configValue = config;

    for (std::size_t channelIndex = 0; channelIndex < config.channels.size(); ++channelIndex)
    {
        std::size_t geometryIndex = 0;
        TryGeometryIndex(config.channels[channelIndex].geometry, geometryIndex);
        activeGeometry[geometryIndex] = true;
    }

    for (std::size_t geometryIndex = 0; geometryIndex < 3; ++geometryIndex)
    {
        if (!activeGeometry[geometryIndex])
        {
            continue;
        }
        if (variableCounts[geometryIndex] == 0)
        {
            std::ostringstream message;
            message << "SFI_v02 " << ToString(static_cast<GeometryKind>(geometryIndex))
                    << " channel is enabled, but this atom count produces no such variables.";
            error = message.str();
            clear();
            return false;
        }
        if (sources[geometryIndex] == NULL)
        {
            std::ostringstream message;
            message << "SFI_v02 " << ToString(static_cast<GeometryKind>(geometryIndex))
                    << " channel requires its FI expressions.";
            error = message.str();
            clear();
            return false;
        }
        if (!BuildOrbitPartition(*sources[geometryIndex],
                                 static_cast<GeometryKind>(geometryIndex),
                                 variableCounts[geometryIndex],
                                 orbitLists[geometryIndex],
                                 variableToOrbit[geometryIndex], error))
        {
            clear();
            return false;
        }
        if (variableCounts[geometryIndex] > maximumVariableCount)
        {
            maximumVariableCount = variableCounts[geometryIndex];
        }
        if (orbitLists[geometryIndex].size() > maximumOrbitCount)
        {
            maximumOrbitCount = orbitLists[geometryIndex].size();
        }
        geometryOffsets[geometryIndex] = activeVariableCount;
        if (geometryIndex != 0 &&
            !CheckedAdd(activeVariableCount, variableCounts[geometryIndex], activeVariableCount))
        {
            error = "SFI_v02 active geometry workspace size overflows size_t.";
            clear();
            return false;
        }
    }

    if (activeGeometry[0])
    {
        if (bondInverseScales == NULL || scaleCount != bondCount)
        {
            std::ostringstream message;
            message << "SFI_v02 requires exactly " << bondCount
                    << " inverse covalent bond scales in i<j order.";
            error = message.str();
            clear();
            return false;
        }
        inverseBondScales.assign(bondInverseScales, bondInverseScales + scaleCount);
        for (std::size_t i = 0; i < inverseBondScales.size(); ++i)
        {
            if (!std::isfinite(inverseBondScales[i]) || !(inverseBondScales[i] > 0.0))
            {
                std::ostringstream message;
                message << "SFI_v02 inverse bond scale " << i
                        << " must be finite and greater than zero.";
                error = message.str();
                clear();
                return false;
            }
        }
    }

    channelMapSlots.assign(config.channels.size(), kNoMapSlot);
    channelOutputOffsets.resize(config.channels.size());
    for (std::size_t channelIndex = 0; channelIndex < config.channels.size(); ++channelIndex)
    {
        const ChannelSpec& channel = config.channels[channelIndex];
        std::size_t geometryIndex = 0;
        TryGeometryIndex(channel.geometry, geometryIndex);
        if (channel.geometry == GeometryKind::Bond)
        {
            std::size_t mapSlot = 0;
            for (; mapSlot < uniqueBondMaps.size(); ++mapSlot)
            {
                if (uniqueBondMaps[mapSlot] == channel.radialMap)
                {
                    break;
                }
            }
            if (mapSlot == uniqueBondMaps.size())
            {
                uniqueBondMaps.push_back(channel.radialMap);
            }
            channelMapSlots[channelIndex] = mapSlot;
        }

        channelOutputOffsets[channelIndex] = featureCount;
        const unsigned int maxDegree = DegreeForGeometry(config, channel.geometry);
        std::size_t channelColumns = 0;
        if (!CheckedMultiply(orbitLists[geometryIndex].size(),
                             static_cast<std::size_t>(maxDegree), channelColumns) ||
            !CheckedAdd(featureCount, channelColumns, featureCount))
        {
            error = "SFI_v02 output column count overflows size_t.";
            clear();
            return false;
        }

        for (std::size_t orbitIndex = 0; orbitIndex < orbitLists[geometryIndex].size(); ++orbitIndex)
        {
            const OrbitInfo& orbit = orbitLists[geometryIndex][orbitIndex];
            for (unsigned int degree = 1; ; ++degree)
            {
                ColumnInfo column;
                column.column = columnList.size();
                column.channelIndex = channelIndex;
                column.geometry = channel.geometry;
                column.radialMap = channel.radialMap;
                column.basis = channel.basis;
                column.orbitIndex = orbitIndex;
                column.sourceFIIndex = orbit.sourceFIIndex;
                column.orbitSize = orbit.variables.size();
                column.degree = degree;
                columnList.push_back(column);
                if (degree == maxDegree)
                {
                    break;
                }
            }
        }
    }

    built = true;
    return true;
}

bool Evaluator::prepareWorkspace(Workspace& workspace, std::string& error) const
{
    error.clear();
    if (!built)
    {
        error = "SFI_v02 evaluator must be built before preparing a workspace.";
        return false;
    }

    std::size_t coordinateCount = 0;
    if (!CheckedMultiply(atomCountValue, static_cast<std::size_t>(3), coordinateCount) ||
        !CheckedAdd(coordinateCount, static_cast<std::size_t>(1), coordinateCount))
    {
        error = "SFI_v02 coordinate workspace size overflows size_t.";
        return false;
    }
    const std::size_t mappedCount = activeGeometry[0] ? variableCounts[0] : 0;

    workspace.coordinates.resize(coordinateCount);
    workspace.pairDx.resize(pairCount);
    workspace.pairDy.resize(pairCount);
    workspace.pairDz.resize(pairCount);
    workspace.pairDistance.resize(pairCount);
    workspace.geometryValues.resize(activeVariableCount);
    workspace.mappedBondValues.resize(mappedCount);
    workspace.previous2.resize(maximumVariableCount);
    workspace.previous1.resize(maximumVariableCount);
    workspace.orbitSums.resize(maximumOrbitCount);
    workspace.orbitCorrections.resize(maximumOrbitCount);
    const std::size_t normalCount = activeGeometry[2] ? atomCountValue : 0;
    workspace.normalX.resize(normalCount);
    workspace.normalY.resize(normalCount);
    workspace.normalZ.resize(normalCount);
    workspace.normalLength.resize(normalCount);
    workspace.owner = this;
    return true;
}

bool Evaluator::evaluate(const xyz& frame,
                         double* output,
                         std::size_t outputCountValue,
                         Workspace& workspace,
                         std::string& error) const
{
    error.clear();
    if (!built)
    {
        error = "SFI_v02 evaluator is not built.";
        return false;
    }
    if (frame.AtomCount() != atomCountValue)
    {
        error = "SFI_v02 frame atom count does not match the evaluator.";
        return false;
    }
    if (outputCountValue != featureCount || (featureCount != 0 && output == NULL))
    {
        error = "SFI_v02 output buffer has the wrong column count.";
        return false;
    }

    std::size_t expectedCoordinates = 0;
    const std::size_t expectedMapped = activeGeometry[0] ? variableCounts[0] : 0;
    CheckedMultiply(atomCountValue, static_cast<std::size_t>(3), expectedCoordinates);
    CheckedAdd(expectedCoordinates, static_cast<std::size_t>(1), expectedCoordinates);
    if (workspace.owner != this || workspace.coordinates.size() != expectedCoordinates ||
        workspace.pairDx.size() != pairCount || workspace.pairDy.size() != pairCount ||
        workspace.pairDz.size() != pairCount || workspace.pairDistance.size() != pairCount ||
        workspace.geometryValues.size() != activeVariableCount ||
        workspace.mappedBondValues.size() != expectedMapped ||
        workspace.previous2.size() != maximumVariableCount ||
        workspace.previous1.size() != maximumVariableCount ||
        workspace.orbitSums.size() != maximumOrbitCount ||
        workspace.orbitCorrections.size() != maximumOrbitCount ||
        workspace.normalX.size() != (activeGeometry[2] ? atomCountValue : 0) ||
        workspace.normalY.size() != (activeGeometry[2] ? atomCountValue : 0) ||
        workspace.normalZ.size() != (activeGeometry[2] ? atomCountValue : 0) ||
        workspace.normalLength.size() != (activeGeometry[2] ? atomCountValue : 0))
    {
        error = "SFI_v02 workspace was not prepared for this evaluator.";
        return false;
    }

    frame.Print(&workspace.coordinates[0]);
    for (std::size_t atom = 0; atom < atomCountValue; ++atom)
    {
        const std::size_t coordinate = atom * 3;
        if (!std::isfinite(workspace.coordinates[coordinate]) ||
            !std::isfinite(workspace.coordinates[coordinate + 1]) ||
            !std::isfinite(workspace.coordinates[coordinate + 2]))
        {
            error = "SFI_v02 frame contains a non-finite coordinate.";
            return false;
        }
    }

    std::size_t pairSite = 0;
    for (std::size_t first = 0; first < atomCountValue; ++first)
    {
        const std::size_t firstCoordinate = first * 3;
        for (std::size_t second = first + 1; second < atomCountValue; ++second)
        {
            const std::size_t secondCoordinate = second * 3;
            const double dx = workspace.coordinates[secondCoordinate] -
                              workspace.coordinates[firstCoordinate];
            const double dy = workspace.coordinates[secondCoordinate + 1] -
                              workspace.coordinates[firstCoordinate + 1];
            const double dz = workspace.coordinates[secondCoordinate + 2] -
                              workspace.coordinates[firstCoordinate + 2];
            const double distance = std::sqrt(dx * dx + dy * dy + dz * dz);
            if (!std::isfinite(dx) || !std::isfinite(dy) || !std::isfinite(dz) ||
                !std::isfinite(distance))
            {
                error = "SFI_v02 frame produces a non-finite pair displacement or distance.";
                return false;
            }
            workspace.pairDx[pairSite] = dx;
            workspace.pairDy[pairSite] = dy;
            workspace.pairDz[pairSite] = dz;
            workspace.pairDistance[pairSite] = distance;
            ++pairSite;
        }
    }

    if (activeGeometry[1])
    {
        double* angleValues = &workspace.geometryValues[geometryOffsets[1]];
        std::size_t angleSite = 0;
        for (std::size_t center = 0; center < atomCountValue; ++center)
        {
            for (std::size_t firstWing = 0; firstWing < atomCountValue; ++firstWing)
            {
                if (firstWing == center)
                {
                    continue;
                }
                double firstX = 0.0;
                double firstY = 0.0;
                double firstZ = 0.0;
                pairVector(workspace, atomCountValue, center, firstWing,
                           firstX, firstY, firstZ);
                const double firstLength = pairLength(workspace, atomCountValue,
                                                      center, firstWing);
                for (std::size_t secondWing = firstWing + 1;
                     secondWing < atomCountValue; ++secondWing)
                {
                    if (secondWing == center)
                    {
                        continue;
                    }
                    double secondX = 0.0;
                    double secondY = 0.0;
                    double secondZ = 0.0;
                    pairVector(workspace, atomCountValue, center, secondWing,
                               secondX, secondY, secondZ);
                    const double secondLength = pairLength(workspace, atomCountValue,
                                                           center, secondWing);
                    double cosine = 1.0;
                    if (firstLength > 0.0 && secondLength > 0.0)
                    {
                        cosine = (firstX * secondX + firstY * secondY + firstZ * secondZ) /
                                 (firstLength * secondLength);
                        if (!std::isfinite(cosine))
                        {
                            error = "SFI_v02 angle geometry produced a non-finite cosine.";
                            return false;
                        }
                        if (cosine > 1.0) cosine = 1.0;
                        if (cosine < -1.0) cosine = -1.0;
                    }
                    angleValues[angleSite++] = cosine;
                }
            }
        }
        if (angleSite != variableCounts[1])
        {
            error = "SFI_v02 internal angle enumeration count mismatch.";
            return false;
        }
    }

    if (activeGeometry[2])
    {
        double* dihedralValues = &workspace.geometryValues[geometryOffsets[2]];
        std::size_t dihedralSite = 0;
        for (std::size_t firstCenter = 0; firstCenter < atomCountValue; ++firstCenter)
        {
            for (std::size_t secondCenter = firstCenter + 1;
                 secondCenter < atomCountValue; ++secondCenter)
            {
                double centerX = 0.0;
                double centerY = 0.0;
                double centerZ = 0.0;
                pairVector(workspace, atomCountValue, firstCenter, secondCenter,
                           centerX, centerY, centerZ);
                for (std::size_t endpoint = 0; endpoint < atomCountValue; ++endpoint)
                {
                    if (endpoint == firstCenter || endpoint == secondCenter)
                    {
                        workspace.normalX[endpoint] = 0.0;
                        workspace.normalY[endpoint] = 0.0;
                        workspace.normalZ[endpoint] = 0.0;
                        workspace.normalLength[endpoint] = 0.0;
                        continue;
                    }
                    double endpointX = 0.0;
                    double endpointY = 0.0;
                    double endpointZ = 0.0;
                    pairVector(workspace, atomCountValue, firstCenter, endpoint,
                               endpointX, endpointY, endpointZ);
                    const double normalX = endpointY * centerZ - endpointZ * centerY;
                    const double normalY = endpointZ * centerX - endpointX * centerZ;
                    const double normalZ = endpointX * centerY - endpointY * centerX;
                    const double normalLength =
                        std::sqrt(normalX * normalX + normalY * normalY + normalZ * normalZ);
                    if (!std::isfinite(normalX) || !std::isfinite(normalY) ||
                        !std::isfinite(normalZ) || !std::isfinite(normalLength))
                    {
                        error = "SFI_v02 dihedral geometry produced a non-finite normal.";
                        return false;
                    }
                    workspace.normalX[endpoint] = normalX;
                    workspace.normalY[endpoint] = normalY;
                    workspace.normalZ[endpoint] = normalZ;
                    workspace.normalLength[endpoint] = normalLength;
                }

                for (std::size_t firstEndpoint = 0;
                     firstEndpoint < atomCountValue; ++firstEndpoint)
                {
                    if (firstEndpoint == firstCenter || firstEndpoint == secondCenter)
                    {
                        continue;
                    }
                    for (std::size_t secondEndpoint = firstEndpoint + 1;
                         secondEndpoint < atomCountValue; ++secondEndpoint)
                    {
                        if (secondEndpoint == firstCenter || secondEndpoint == secondCenter)
                        {
                            continue;
                        }
                        double cosine = 1.0;
                        const double firstLength = workspace.normalLength[firstEndpoint];
                        const double secondLength = workspace.normalLength[secondEndpoint];
                        if (firstLength > 0.0 && secondLength > 0.0)
                        {
                            cosine = (workspace.normalX[firstEndpoint] * workspace.normalX[secondEndpoint] +
                                      workspace.normalY[firstEndpoint] * workspace.normalY[secondEndpoint] +
                                      workspace.normalZ[firstEndpoint] * workspace.normalZ[secondEndpoint]) /
                                     (firstLength * secondLength);
                            if (!std::isfinite(cosine))
                            {
                                error = "SFI_v02 dihedral geometry produced a non-finite cosine.";
                                return false;
                            }
                            if (cosine > 1.0) cosine = 1.0;
                            if (cosine < -1.0) cosine = -1.0;
                        }
                        dihedralValues[dihedralSite++] = cosine;
                    }
                }
            }
        }
        if (dihedralSite != variableCounts[2])
        {
            error = "SFI_v02 internal dihedral enumeration count mismatch.";
            return false;
        }
    }

    if (activeGeometry[0])
    {
        double* mapped = &workspace.mappedBondValues[0];
        for (std::size_t mapSlot = 0; mapSlot < uniqueBondMaps.size(); ++mapSlot)
        {
            for (std::size_t variable = 0; variable < variableCounts[0]; ++variable)
            {
                const double rho = workspace.pairDistance[variable] * inverseBondScales[variable];
                double value = 0.0;
                switch (uniqueBondMaps[mapSlot])
                {
                case RadialMap::Rational:
                    value = (rho - configValue.m) / (rho + configValue.m);
                    break;
                case RadialMap::Morse:
                    value = 2.0 * std::exp(-configValue.a * rho) - 1.0;
                    break;
                case RadialMap::Gaussian:
                {
                    const double difference = rho - configValue.c;
                    value = 2.0 * std::exp(-configValue.b * difference * difference) - 1.0;
                    break;
                }
                case RadialMap::NotApplicable:
                    error = "SFI_v02 internal bond mapping plan is invalid.";
                    return false;
                }
                if (!std::isfinite(value))
                {
                    error = "SFI_v02 radial mapping produced a non-finite value.";
                    return false;
                }
                mapped[variable] = value;
            }

            for (std::size_t channelIndex = 0;
                 channelIndex < configValue.channels.size(); ++channelIndex)
            {
                if (configValue.channels[channelIndex].geometry == GeometryKind::Bond &&
                    channelMapSlots[channelIndex] == mapSlot &&
                    !evaluateChannel(channelIndex, mapped, output, workspace, error))
                {
                    return false;
                }
            }
        }
    }

    for (std::size_t channelIndex = 0; channelIndex < configValue.channels.size(); ++channelIndex)
    {
        const ChannelSpec& channel = configValue.channels[channelIndex];
        if (channel.geometry == GeometryKind::Bond)
        {
            continue;
        }
        std::size_t geometryIndex = 0;
        TryGeometryIndex(channel.geometry, geometryIndex);
        const double* mapped = &workspace.geometryValues[geometryOffsets[geometryIndex]];
        if (!evaluateChannel(channelIndex, mapped, output, workspace, error))
        {
            return false;
        }
    }
    return true;
}

std::size_t Evaluator::outputCount(void) const
{
    return featureCount;
}

const std::vector<ColumnInfo>& Evaluator::columns(void) const
{
    return columnList;
}

const Config& Evaluator::config(void) const
{
    return configValue;
}

std::size_t Evaluator::atomCount(void) const
{
    return atomCountValue;
}

std::size_t Evaluator::variableCount(GeometryKind geometry) const
{
    std::size_t index = 0;
    return TryGeometryIndex(geometry, index) ? variableCounts[index] : 0;
}

const std::vector<OrbitInfo>& Evaluator::orbits(GeometryKind geometry) const
{
    static const std::vector<OrbitInfo> empty;
    std::size_t index = 0;
    return TryGeometryIndex(geometry, index) ? orbitLists[index] : empty;
}

bool Evaluator::isBuilt(void) const
{
    return built;
}
}
}
