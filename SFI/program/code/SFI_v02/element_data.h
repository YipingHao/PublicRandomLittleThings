#ifndef FIANALYZER_SFI_V02_ELEMENT_DATA_H
#define FIANALYZER_SFI_V02_ELEMENT_DATA_H

#include <cstddef>
#include <string>

namespace analyzer
{
namespace sfi_v02
{
    struct ElementData
    {
        unsigned int atomicNumber;
        const char* symbol;
        double singleBondCovalentRadiusAngstrom;
    };

    bool NormalizeElementSymbol(const char* input, std::string& normalized);
    const ElementData* FindElement(const char* input);
    const ElementData* FindElementByAtomicNumber(unsigned int atomicNumber);
    bool TryGetCovalentRadiusAngstrom(const char* input, double& radius);
    bool TryGetCovalentBondLengthAngstrom(const char* left, const char* right, double& length);
    const char* CovalentRadiusSource(void);
    std::size_t CovalentRadiusElementCount(void);
}
}

#endif
