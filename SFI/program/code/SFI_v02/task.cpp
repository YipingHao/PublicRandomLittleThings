#include "task.h"

#include "element_data.h"

#include <atomic>
#include <chrono>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <limits>
#include <string>
#include <thread>
#include <vector>

namespace analyzer
{
namespace sfi_v02
{
namespace
{
    const int kConfigurationError = -2001;
    const int kInputError = -2002;
    const int kFIError = -2003;
    const int kBuildError = -2004;
    const int kEvaluationError = -2005;
    const int kOutputError = -2006;

    bool LookupSingle(const hyperlex::dictionary& dictionary,
                      const char* key,
                      hyperlex::dictionary::Ktype& type,
                      hyperlex::dictionary::element& value,
                      bool& present,
                      std::string& error)
    {
        size_t count = 0;
        hyperlex::dictionary::element* values = dictionary.search(count, type, key);
        present = (values != NULL && count != 0);
        if (!present)
        {
            type = hyperlex::dictionary::null_;
            return true;
        }
        if (count != 1)
        {
            error = std::string("configuration key '") + key + "' must contain exactly one value";
            return false;
        }
        value = values[0];
        return true;
    }

    bool ReadRequiredString(const hyperlex::dictionary& dictionary,
                            const char* key,
                            std::string& result,
                            std::string& error)
    {
        hyperlex::dictionary::Ktype type = hyperlex::dictionary::null_;
        hyperlex::dictionary::element value;
        bool present = false;
        if (!LookupSingle(dictionary, key, type, value, present, error)) return false;
        if (!present)
        {
            error = std::string("missing required string configuration key '") + key + "'";
            return false;
        }
        if (type != hyperlex::dictionary::string_ || value.ss == NULL)
        {
            error = std::string("configuration key '") + key + "' must be a string";
            return false;
        }
        result = value.ss;
        if (result.empty())
        {
            error = std::string("configuration key '") + key + "' must not be empty";
            return false;
        }
        return true;
    }

    bool ReadOptionalString(const hyperlex::dictionary& dictionary,
                            const char* key,
                            const char* defaultValue,
                            std::string& result,
                            std::string& error)
    {
        hyperlex::dictionary::Ktype type = hyperlex::dictionary::null_;
        hyperlex::dictionary::element value;
        bool present = false;
        if (!LookupSingle(dictionary, key, type, value, present, error)) return false;
        if (!present)
        {
            result = defaultValue;
            return true;
        }
        if (type != hyperlex::dictionary::string_ || value.ss == NULL)
        {
            error = std::string("configuration key '") + key + "' must be a string";
            return false;
        }
        result = value.ss;
        if (result.empty())
        {
            error = std::string("configuration key '") + key + "' must not be empty";
            return false;
        }
        return true;
    }

    bool ReadOptionalBool(const hyperlex::dictionary& dictionary,
                          const char* key,
                          bool defaultValue,
                          bool& result,
                          std::string& error)
    {
        hyperlex::dictionary::Ktype type = hyperlex::dictionary::null_;
        hyperlex::dictionary::element value;
        bool present = false;
        if (!LookupSingle(dictionary, key, type, value, present, error)) return false;
        if (!present)
        {
            result = defaultValue;
            return true;
        }
        if (type != hyperlex::dictionary::bool_)
        {
            error = std::string("configuration key '") + key + "' must be boolean";
            return false;
        }
        result = value.bb;
        return true;
    }

    bool ReadOptionalNonnegativeSize(const hyperlex::dictionary& dictionary,
                                     const char* key,
                                     size_t defaultValue,
                                     size_t& result,
                                     std::string& error)
    {
        hyperlex::dictionary::Ktype type = hyperlex::dictionary::null_;
        hyperlex::dictionary::element value;
        bool present = false;
        if (!LookupSingle(dictionary, key, type, value, present, error)) return false;
        if (!present)
        {
            result = defaultValue;
            return true;
        }
        if (type != hyperlex::dictionary::int_ || value.ii < 0)
        {
            error = std::string("configuration key '") + key + "' must be a nonnegative integer";
            return false;
        }
        result = static_cast<size_t>(value.ii);
        return true;
    }

    bool ReadPositiveSize(const hyperlex::dictionary& dictionary,
                          const char* key,
                          size_t defaultValue,
                          bool required,
                          size_t& result,
                          std::string& error)
    {
        hyperlex::dictionary::Ktype type = hyperlex::dictionary::null_;
        hyperlex::dictionary::element value;
        bool present = false;
        if (!LookupSingle(dictionary, key, type, value, present, error)) return false;
        if (!present)
        {
            if (required)
            {
                error = std::string("missing required positive integer configuration key '") + key + "'";
                return false;
            }
            result = defaultValue;
            return true;
        }
        if (type != hyperlex::dictionary::int_ || value.ii <= 0)
        {
            error = std::string("configuration key '") + key + "' must be a positive integer";
            return false;
        }
        result = static_cast<size_t>(value.ii);
        return true;
    }

    bool ReadDegree(const hyperlex::dictionary& dictionary,
                    const char* key,
                    unsigned int& result,
                    std::string& error)
    {
        size_t parsed = 0;
        if (!ReadPositiveSize(dictionary, key, 0, true, parsed, error)) return false;
        if (parsed > static_cast<size_t>(std::numeric_limits<unsigned int>::max()))
        {
            error = std::string("configuration key '") + key + "' exceeds the supported degree range";
            return false;
        }
        result = static_cast<unsigned int>(parsed);
        return true;
    }

    bool ReadFiniteNumber(const hyperlex::dictionary& dictionary,
                          const char* key,
                          double defaultValue,
                          double& result,
                          std::string& error)
    {
        hyperlex::dictionary::Ktype type = hyperlex::dictionary::null_;
        hyperlex::dictionary::element value;
        bool present = false;
        if (!LookupSingle(dictionary, key, type, value, present, error)) return false;
        if (!present)
        {
            result = defaultValue;
        }
        else if (type == hyperlex::dictionary::float_)
        {
            result = value.ff;
        }
        else if (type == hyperlex::dictionary::int_)
        {
            result = static_cast<double>(value.ii);
        }
        else
        {
            error = std::string("configuration key '") + key + "' must be numeric";
            return false;
        }
        if (!std::isfinite(result))
        {
            error = std::string("configuration key '") + key + "' must be finite";
            return false;
        }
        return true;
    }

    bool HasKey(const hyperlex::dictionary& dictionary, const char* key)
    {
        size_t count = 0;
        hyperlex::dictionary::Ktype type = hyperlex::dictionary::null_;
        return dictionary.search(count, type, key) != NULL && count != 0;
    }

    bool ReadSFIConfigGroup(const hyperlex::dictionary& dictionary,
                            const hyperlex::dictionary*& group,
                            std::string& error)
    {
        size_t count = 0;
        hyperlex::dictionary::Ktype type = hyperlex::dictionary::null_;
        hyperlex::dictionary::element* values = dictionary.search(count, type, "SFI_v02");
        if (values == NULL || count == 0)
        {
            error = "missing required SFI_v02 configuration group";
            return false;
        }
        if (count != 1 || type != hyperlex::dictionary::dictionary_ || values[0].dd == NULL)
        {
            error = "SFI_v02 must be exactly one configuration dictionary";
            return false;
        }
        group = values[0].dd;
        return true;
    }

    bool ParseGeometry(const std::string& text, GeometryKind& geometry)
    {
        if (text == "bond") geometry = GeometryKind::Bond;
        else if (text == "angle") geometry = GeometryKind::Angle;
        else if (text == "dihedral") geometry = GeometryKind::Dihedral;
        else return false;
        return true;
    }

    bool ParseRadialMap(const std::string& text, RadialMap& mapping)
    {
        if (text == "rational") mapping = RadialMap::Rational;
        else if (text == "morse") mapping = RadialMap::Morse;
        else if (text == "gaussian") mapping = RadialMap::Gaussian;
        else return false;
        return true;
    }

    bool ParseBasis(const std::string& text, Basis& basis)
    {
        if (text == "chebyshev") basis = Basis::Chebyshev;
        else if (text == "legendre") basis = Basis::Legendre;
        else return false;
        return true;
    }

    bool SameChannel(const ChannelSpec& left, const ChannelSpec& right)
    {
        return left.geometry == right.geometry &&
               left.radialMap == right.radialMap &&
               left.basis == right.basis;
    }

    bool ParseConfig(const hyperlex::dictionary& dictionary, Config& config, std::string& error)
    {
        config = Config();
        const hyperlex::dictionary* group = NULL;
        if (!ReadSFIConfigGroup(dictionary, group, error)) return false;

        size_t channelCount = 0;
        hyperlex::dictionary::Ktype channelType = hyperlex::dictionary::null_;
        hyperlex::dictionary::element* channelValues =
            group->search(channelCount, channelType, "channels");
        if (channelValues == NULL || channelCount == 0)
        {
            error = "SFI_v02.channels is required and must be a nonempty ordered list";
            return false;
        }
        if (channelType != hyperlex::dictionary::dictionary_)
        {
            error = "SFI_v02.channels must be a list of dictionaries";
            return false;
        }

        bool usesBond = false;
        bool usesAngle = false;
        bool usesDihedral = false;
        bool usesGaussian = false;
        bool hasGaussianCompanion = false;

        for (size_t i = 0; i < channelCount; ++i)
        {
            const hyperlex::dictionary* channelDictionary = channelValues[i].dd;
            if (channelDictionary == NULL)
            {
                error = "SFI_v02.channels contains a null channel dictionary";
                return false;
            }

            std::string geometryText;
            std::string basisText;
            std::string mappingText;
            if (!ReadRequiredString(*channelDictionary, "geometry", geometryText, error) ||
                !ReadRequiredString(*channelDictionary, "basis", basisText, error))
            {
                error = "SFI_v02.channels[" + std::to_string(i) + "]: " + error;
                return false;
            }

            GeometryKind geometry = GeometryKind::Bond;
            Basis basis = Basis::Chebyshev;
            RadialMap mapping = RadialMap::NotApplicable;
            if (!ParseGeometry(geometryText, geometry))
            {
                error = "SFI_v02.channels[" + std::to_string(i) +
                        "].geometry must be bond, angle, or dihedral";
                return false;
            }
            if (!ParseBasis(basisText, basis))
            {
                error = "SFI_v02.channels[" + std::to_string(i) +
                        "].basis must be chebyshev or legendre";
                return false;
            }

            if (geometry == GeometryKind::Bond)
            {
                if (!ReadRequiredString(*channelDictionary, "mapping", mappingText, error))
                {
                    error = "SFI_v02.channels[" + std::to_string(i) + "]: " + error;
                    return false;
                }
                if (!ParseRadialMap(mappingText, mapping))
                {
                    error = "SFI_v02.channels[" + std::to_string(i) +
                            "].mapping must be rational, morse, or gaussian";
                    return false;
                }
                usesBond = true;
                usesGaussian = usesGaussian || mapping == RadialMap::Gaussian;
                hasGaussianCompanion = hasGaussianCompanion ||
                    mapping == RadialMap::Rational || mapping == RadialMap::Morse;
            }
            else
            {
                if (HasKey(*channelDictionary, "mapping"))
                {
                    error = "SFI_v02.channels[" + std::to_string(i) +
                            "]: mapping is only valid for bond channels";
                    return false;
                }
                usesAngle = usesAngle || geometry == GeometryKind::Angle;
                usesDihedral = usesDihedral || geometry == GeometryKind::Dihedral;
            }

            ChannelSpec channel(geometry, mapping, basis);
            for (size_t previous = 0; previous < config.channels.size(); ++previous)
            {
                if (SameChannel(config.channels[previous], channel))
                {
                    error = "SFI_v02.channels[" + std::to_string(i) +
                            "] exactly duplicates an earlier channel";
                    return false;
                }
            }
            config.channels.push_back(channel);
        }

        if (usesBond && !ReadDegree(*group, "bond_max_degree", config.bondMaxDegree, error))
            return false;
        if (usesAngle && !ReadDegree(*group, "angle_max_degree", config.angleMaxDegree, error))
            return false;
        if (usesDihedral && !ReadDegree(*group, "dihedral_max_degree", config.dihedralMaxDegree, error))
            return false;

        if (!ReadFiniteNumber(*group, "m", 1.0, config.m, error) ||
            !ReadFiniteNumber(*group, "a", 1.0, config.a, error) ||
            !ReadFiniteNumber(*group, "b", 1.0, config.b, error) ||
            !ReadFiniteNumber(*group, "c", 1.0, config.c, error))
            return false;

        if (!(config.m > 0.0) || !(config.a > 0.0) || !(config.b > 0.0))
        {
            error = "SFI_v02 parameters m, a, and b must all be greater than zero";
            return false;
        }
        if (usesGaussian && config.c > 0.0 && !hasGaussianCompanion)
        {
            error = "when SFI_v02.c > 0, a Gaussian bond channel requires a rational or Morse bond channel";
            return false;
        }
        return true;
    }

    bool GeometryEnabled(const Config& config, GeometryKind geometry)
    {
        for (size_t i = 0; i < config.channels.size(); ++i)
            if (config.channels[i].geometry == geometry) return true;
        return false;
    }

    bool ReadAndValidateXYZ(hyperlex::dictionary& dictionary,
                            xyzFile& frames,
                            std::string& error)
    {
        std::string dataFormat;
        std::string dataFileName;
        if (!ReadRequiredString(dictionary, "DataFormat", dataFormat, error)) return false;
        if (dataFormat != "xyz")
        {
            error = "SFI_v02 supports only DataFormat=\"xyz\"";
            return false;
        }
        if (!ReadRequiredString(dictionary, "DataFileName", dataFileName, error)) return false;

        FILE* input = std::fopen(dataFileName.c_str(), "r");
        if (input == NULL)
        {
            error = "cannot open XYZ data file '" + dataFileName + "'";
            return false;
        }
        const int parseError = frames.build(input);
        std::fclose(input);
        if (parseError != 0)
        {
            error = "cannot parse XYZ data file '" + dataFileName +
                    "' (parser error " + std::to_string(parseError) + ")";
            return false;
        }
        if (frames.count() == 0)
        {
            error = "XYZ data file contains no frames";
            return false;
        }
        const size_t inconsistentFrame = frames.check();
        if (inconsistentFrame != 0)
        {
            error = "XYZ frame " + std::to_string(inconsistentFrame) +
                    " has a different atom layout from frame 0";
            return false;
        }

        const size_t fileAtomCount = frames[0].AtomCount();
        size_t configuredAtomCount = 0;
        if (!ReadOptionalNonnegativeSize(dictionary, "XYZsettings.AtomCount", 0,
                                         configuredAtomCount, error))
            return false;
        if (configuredAtomCount != 0 && configuredAtomCount != fileAtomCount)
        {
            error = "XYZsettings.AtomCount=" + std::to_string(configuredAtomCount) +
                    " does not match the XYZ atom count " + std::to_string(fileAtomCount);
            return false;
        }

        bool needPermutation = false;
        if (!ReadOptionalBool(dictionary, "XYZsettings.NeedPermutation", false,
                              needPermutation, error))
            return false;
        if (!needPermutation) return true;

        size_t permutationCount = 0;
        hyperlex::dictionary::Ktype permutationType = hyperlex::dictionary::null_;
        hyperlex::dictionary::element* permutationValues =
            dictionary.search(permutationCount, permutationType, "XYZsettings.Permutation");
        if (permutationValues == NULL || permutationCount == 0)
        {
            error = "XYZsettings.NeedPermutation=true requires XYZsettings.Permutation";
            return false;
        }
        if (permutationType != hyperlex::dictionary::int_)
        {
            error = "XYZsettings.Permutation must be an integer array";
            return false;
        }
        if (permutationCount != fileAtomCount)
        {
            error = "XYZsettings.Permutation length " + std::to_string(permutationCount) +
                    " does not match the XYZ atom count " + std::to_string(fileAtomCount);
            return false;
        }

        analyzer::vector<size_t> permutation;
        analyzer::vector<bool> used;
        permutation.recount(permutationCount);
        used.recount(fileAtomCount);
        used.value(false);
        for (size_t i = 0; i < permutationCount; ++i)
        {
            if (permutationValues[i].ii <= 0)
            {
                error = "XYZsettings.Permutation is 1-based; entry " + std::to_string(i) +
                        " must be positive";
                return false;
            }
            const size_t source = static_cast<size_t>(permutationValues[i].ii - 1);
            if (source >= fileAtomCount)
            {
                error = "XYZsettings.Permutation entry " + std::to_string(i) +
                        " is out of range";
                return false;
            }
            if (used[source])
            {
                error = "XYZsettings.Permutation contains duplicate source index " +
                        std::to_string(source + 1);
                return false;
            }
            used[source] = true;
            permutation[i] = source;
        }
        const int permutationError = frames.permutation(permutation);
        if (permutationError != 0)
        {
            error = "failed to apply XYZsettings.Permutation (error " +
                    std::to_string(permutationError) + ")";
            return false;
        }
        return true;
    }

    bool BuildBondInverseScales(const xyz& frame,
                                std::vector<double>& inverseScales,
                                std::string& error)
    {
        const size_t atomCount = frame.AtomCount();
        if (atomCount > 1 && atomCount > std::numeric_limits<size_t>::max() / (atomCount - 1))
        {
            error = "atom count is too large to enumerate bond variables";
            return false;
        }
        const size_t pairCount = atomCount * (atomCount - 1) / 2;
        inverseScales.resize(pairCount);
        size_t pair = 0;
        for (size_t i = 0; i < atomCount; ++i)
        {
            for (size_t j = i + 1; j < atomCount; ++j)
            {
                double covalentLength = 0.0;
                const char* left = frame.AtomName(i);
                const char* right = frame.AtomName(j);
                if (!TryGetCovalentBondLengthAngstrom(left, right, covalentLength))
                {
                    error = "unknown or unsupported element in bond (" +
                            std::string(left == NULL ? "<null>" : left) + ", " +
                            std::string(right == NULL ? "<null>" : right) + ")";
                    return false;
                }
                if (!(covalentLength > 0.0) || !std::isfinite(covalentLength))
                {
                    error = "invalid covalent bond length for element pair (" +
                            std::string(left) + ", " + std::string(right) + ")";
                    return false;
                }
                inverseScales[pair++] = 1.0 / covalentLength;
            }
        }
        return true;
    }

    bool ValidateElementSymbols(const xyz& frame, std::string& error)
    {
        for (size_t atom = 0; atom < frame.AtomCount(); ++atom)
        {
            std::string normalized;
            const char* symbol = frame.AtomName(atom);
            if (!NormalizeElementSymbol(symbol, normalized))
            {
                error = "unknown or unsupported element at atom " + std::to_string(atom) +
                        " ('" + std::string(symbol == NULL ? "<null>" : symbol) + "')";
                return false;
            }
        }
        return true;
    }

    bool LoadFIFile(const hyperlex::dictionary& dictionary,
                    const char* key,
                    const char* geometryName,
                    FIexpresses& expressions,
                    std::string& error)
    {
        std::string fileName;
        if (!ReadRequiredString(dictionary, key, fileName, error)) return false;
        FILE* input = std::fopen(fileName.c_str(), "r");
        if (input == NULL)
        {
            error = std::string("cannot open ") + geometryName + " FI file '" + fileName + "'";
            return false;
        }
        const int parseError = expressions.build(input);
        std::fclose(input);
        if (parseError != 0)
        {
            error = std::string("cannot parse ") + geometryName + " FI file '" + fileName +
                    "' (parser error " + std::to_string(parseError) + ")";
            return false;
        }
        return true;
    }

    std::string ReplaceSuffix(const std::string& fileName, const char* suffix)
    {
        const size_t separator = fileName.find_last_of("/\\");
        const size_t nameStart = separator == std::string::npos ? 0 : separator + 1;
        const size_t dot = fileName.find_last_of('.');
        if (dot == std::string::npos || dot < nameStart || dot == nameStart)
            return fileName + suffix;
        return fileName.substr(0, dot) + suffix;
    }

    bool IsAbsolutePath(const std::string& path)
    {
        if (path.empty()) return false;
        if (path[0] == '/' || path[0] == '\\') return true;
        return path.size() >= 2 && path[1] == ':';
    }

    std::string JoinOutputPath(const char* outputPath, const std::string& fileName)
    {
        if (IsAbsolutePath(fileName) || outputPath == NULL || outputPath[0] == '\0') return fileName;
        std::string result(outputPath);
        if (!result.empty() && result[result.size() - 1] != '/' && result[result.size() - 1] != '\\')
            result += '/';
        result += fileName;
        return result;
    }

    bool WriteColumnsFile(FILE* output, const Evaluator& evaluator)
    {
        if (std::fprintf(output,
            "column\tchannel\tgeometry\tfi_ordinal\texpr_index\tbasis\tdegree\tmapping\torbit_size\taggregation\tm\ta\tb\tc\n") < 0)
            return false;

        const std::vector<ColumnInfo>& columns = evaluator.columns();
        const Config& config = evaluator.config();
        for (size_t i = 0; i < columns.size(); ++i)
        {
            const ColumnInfo& column = columns[i];
            if (std::fprintf(output, "%zu\t%zu\t%s\t%zu\t%zu\t%s\t%u\t%s\t%zu\t%s\t%.17g\t%.17g\t%.17g\t%.17g\n",
                    column.column,
                    column.channelIndex,
                    ToString(column.geometry),
                    column.orbitIndex,
                    column.sourceFIIndex,
                    ToString(column.basis),
                    column.degree,
                    ToString(column.radialMap),
                    column.orbitSize,
                    "neumaier_sum",
                    config.m,
                    config.a,
                    config.b,
                    config.c) < 0)
                return false;
        }
        return std::fprintf(output,
                    "%zu\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%.17g\t%.17g\t%.17g\t%.17g\n",
                    evaluator.outputCount(), "", "energy", "", "", "", "", "", "",
                    "not_applicable", config.m, config.a, config.b, config.c) >= 0;
    }
}

int SFI_v02DataMatrixSwitch(hyperlex::dictionary& dictionary,
                            const char* outputPath,
                            const Evaluator& evaluator,
                            const xyzFile& frames)
{
    const std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
    std::string error;

    size_t requestedThreads = 1;
    size_t chunkRows = 64;
    std::string outputBase;
    const hyperlex::dictionary* group = NULL;
    if (!ReadSFIConfigGroup(dictionary, group, error))
    {
        std::fprintf(stderr, "SFI_v02 configuration error: %s\n", error.c_str());
        return kConfigurationError;
    }
    if (!ReadPositiveSize(dictionary, "threadCount", 1, false, requestedThreads, error) ||
        !ReadPositiveSize(*group, "chunk_rows", 64, false, chunkRows, error) ||
        !ReadOptionalString(dictionary, "OutputFileName", "output", outputBase, error))
    {
        std::fprintf(stderr, "SFI_v02 configuration error: %s\n", error.c_str());
        return kConfigurationError;
    }
    if (!evaluator.isBuilt())
    {
        std::fprintf(stderr, "SFI_v02 internal error: evaluator is not built\n");
        return kBuildError;
    }
    if (frames.count() == 0)
    {
        std::fprintf(stderr, "SFI_v02 input error: no XYZ frames to evaluate\n");
        return kInputError;
    }

    const size_t featureCount = evaluator.outputCount();
    if (featureCount == std::numeric_limits<size_t>::max())
    {
        std::fprintf(stderr, "SFI_v02 output column count overflow\n");
        return kOutputError;
    }
    const size_t outputColumns = featureCount + 1;
    size_t workerCount = requestedThreads < frames.count() ? requestedThreads : frames.count();
    if (chunkRows < workerCount) workerCount = chunkRows;

    std::vector<Workspace> workspaces(workerCount);
    std::vector<std::string> workerErrors(workerCount);
    for (size_t worker = 0; worker < workerCount; ++worker)
    {
        if (!evaluator.prepareWorkspace(workspaces[worker], error))
        {
            std::fprintf(stderr, "SFI_v02 workspace error: %s\n", error.c_str());
            return kBuildError;
        }
    }

    const std::string dataName = ReplaceSuffix(outputBase, ".sfi_v02.txt");
    const std::string columnsName = ReplaceSuffix(outputBase, ".sfi_v02.columns.tsv");
    const std::string dataPath = JoinOutputPath(outputPath, dataName);
    const std::string columnsPath = JoinOutputPath(outputPath, columnsName);

    FILE* dataOutput = std::fopen(dataPath.c_str(), "w");
    if (dataOutput == NULL)
    {
        std::fprintf(stderr, "SFI_v02 cannot open output file '%s'\n", dataPath.c_str());
        return kOutputError;
    }
    FILE* columnsOutput = std::fopen(columnsPath.c_str(), "w");
    if (columnsOutput == NULL)
    {
        std::fprintf(stderr, "SFI_v02 cannot open column metadata file '%s'\n", columnsPath.c_str());
        std::fclose(dataOutput);
        return kOutputError;
    }
    const bool columnsWritten = WriteColumnsFile(columnsOutput, evaluator);
    const int columnsCloseError = std::fclose(columnsOutput);
    if (!columnsWritten || columnsCloseError != 0)
    {
        std::fprintf(stderr, "SFI_v02 failed while writing column metadata '%s'\n", columnsPath.c_str());
        std::fclose(dataOutput);
        return kOutputError;
    }

    if (std::fprintf(dataOutput,
            "# SFI_v02 values generated by FIanalyzer\n"
            "# Number of data points: %zu\n"
            "# Number of SFI_v02 feature columns: %zu\n"
            "# Orbit aggregation: Neumaier compensated sum (no division by orbit_size)\n"
            "# Final column: energy\n\n",
            frames.count(), featureCount) < 0)
    {
        std::fclose(dataOutput);
        return kOutputError;
    }

    std::vector<double> chunkOutput;
    if (chunkRows > std::numeric_limits<size_t>::max() / outputColumns)
    {
        std::fprintf(stderr, "SFI_v02.chunk_rows is too large for the output column count\n");
        std::fclose(dataOutput);
        return kConfigurationError;
    }
    chunkOutput.resize(chunkRows * outputColumns);
    std::vector<std::thread> threads;
    threads.reserve(workerCount);

    for (size_t chunkBegin = 0; chunkBegin < frames.count(); chunkBegin += chunkRows)
    {
        const size_t remaining = frames.count() - chunkBegin;
        const size_t rowsNow = remaining < chunkRows ? remaining : chunkRows;
        const size_t activeWorkers = workerCount < rowsNow ? workerCount : rowsNow;
        std::atomic<bool> failed(false);
        for (size_t worker = 0; worker < activeWorkers; ++worker)
        {
            workerErrors[worker].clear();
            const size_t localBegin = worker * rowsNow / activeWorkers;
            const size_t localEnd = (worker + 1) * rowsNow / activeWorkers;
            threads.push_back(std::thread([&, worker, localBegin, localEnd, chunkBegin]()
            {
                for (size_t localRow = localBegin; localRow < localEnd; ++localRow)
                {
                    if (failed.load(std::memory_order_relaxed)) return;
                    const xyz& frame = frames[chunkBegin + localRow];
                    double* rowOutput = &chunkOutput[localRow * outputColumns];
                    if (!evaluator.evaluate(frame, rowOutput, featureCount,
                                            workspaces[worker], workerErrors[worker]))
                    {
                        failed.store(true, std::memory_order_relaxed);
                        return;
                    }
                    rowOutput[featureCount] = workspaces[worker].frameEnergy();
                }
            }));
        }
        for (size_t worker = 0; worker < threads.size(); ++worker) threads[worker].join();
        threads.clear();

        if (failed.load(std::memory_order_relaxed))
        {
            for (size_t worker = 0; worker < activeWorkers; ++worker)
            {
                if (!workerErrors[worker].empty())
                {
                    error = workerErrors[worker];
                    break;
                }
            }
            std::fprintf(stderr, "SFI_v02 evaluation error in chunk beginning at row %zu: %s\n",
                         chunkBegin, error.empty() ? "unknown worker error" : error.c_str());
            std::fclose(dataOutput);
            return kEvaluationError;
        }

        for (size_t row = 0; row < rowsNow; ++row)
        {
            for (size_t column = 0; column < outputColumns; ++column)
            {
                if (std::fprintf(dataOutput, "%25.16E ",
                                 chunkOutput[row * outputColumns + column]) < 0)
                {
                    std::fprintf(stderr, "SFI_v02 failed while writing output row %zu\n", chunkBegin + row);
                    std::fclose(dataOutput);
                    return kOutputError;
                }
            }
            if (std::fputc('\n', dataOutput) == EOF)
            {
                std::fclose(dataOutput);
                return kOutputError;
            }
        }
    }

    if (std::fclose(dataOutput) != 0)
    {
        std::fprintf(stderr, "SFI_v02 failed while closing output file '%s'\n", dataPath.c_str());
        return kOutputError;
    }

    const std::chrono::duration<double> elapsed = std::chrono::steady_clock::now() - start;
    std::printf("SFI_v02 wrote %zu rows x %zu columns using %zu thread(s), chunk_rows=%zu, in %.3f seconds\n",
                frames.count(), outputColumns, workerCount, chunkRows, elapsed.count());
    std::printf("SFI_v02 data output: %s\n", dataPath.c_str());
    std::printf("SFI_v02 column metadata: %s\n", columnsPath.c_str());
    return 0;
}

int SFI_v02(hyperlex::dictionary& dictionary, const char* outputPath)
{
    std::printf("SFI_v02 task started\n");
    Config config;
    std::string error;
    if (!ParseConfig(dictionary, config, error))
    {
        std::fprintf(stderr, "SFI_v02 configuration error: %s\n", error.c_str());
        return kConfigurationError;
    }

    xyzFile frames;
    if (!ReadAndValidateXYZ(dictionary, frames, error))
    {
        std::fprintf(stderr, "SFI_v02 input error: %s\n", error.c_str());
        return kInputError;
    }
    if (!ValidateElementSymbols(frames[0], error))
    {
        std::fprintf(stderr, "SFI_v02 element data error: %s\n", error.c_str());
        return kInputError;
    }

    const bool useBond = GeometryEnabled(config, GeometryKind::Bond);
    const bool useAngle = GeometryEnabled(config, GeometryKind::Angle);
    const bool useDihedral = GeometryEnabled(config, GeometryKind::Dihedral);

    std::vector<double> inverseBondScales;
    if (useBond && !BuildBondInverseScales(frames[0], inverseBondScales, error))
    {
        std::fprintf(stderr, "SFI_v02 element data error: %s\n", error.c_str());
        return kInputError;
    }

    FIexpresses bondFI;
    FIexpresses angleFI;
    FIexpresses dihedralFI;
    if (useBond && !LoadFIFile(dictionary, "PIPFileName", "bond", bondFI, error))
    {
        std::fprintf(stderr, "SFI_v02 FI error: %s\n", error.c_str());
        return kFIError;
    }
    if (useAngle && !LoadFIFile(dictionary, "AngleFileName", "angle", angleFI, error))
    {
        std::fprintf(stderr, "SFI_v02 FI error: %s\n", error.c_str());
        return kFIError;
    }
    if (useDihedral && !LoadFIFile(dictionary, "DihedralFileName", "dihedral", dihedralFI, error))
    {
        std::fprintf(stderr, "SFI_v02 FI error: %s\n", error.c_str());
        return kFIError;
    }

    Evaluator evaluator;
    if (!evaluator.build(frames[0].AtomCount(),
                         useBond ? &bondFI : NULL,
                         useAngle ? &angleFI : NULL,
                         useDihedral ? &dihedralFI : NULL,
                         inverseBondScales.empty() ? NULL : inverseBondScales.data(),
                         inverseBondScales.size(),
                         config,
                         error))
    {
        std::fprintf(stderr, "SFI_v02 build error: %s\n", error.c_str());
        return kBuildError;
    }

    std::printf("SFI_v02 evaluator: %zu atoms, %zu channels, %zu feature columns\n",
                evaluator.atomCount(), config.channels.size(), evaluator.outputCount());
    return SFI_v02DataMatrixSwitch(dictionary, outputPath, evaluator, frames);
}
}
}
