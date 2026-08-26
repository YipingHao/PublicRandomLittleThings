#ifndef FIANALYZER_SFI_V02_TASK_H
#define FIANALYZER_SFI_V02_TASK_H

#include "../dictionary.h"
#include "sfi_v02.h"

namespace analyzer
{
namespace sfi_v02
{
    int SFI_v02(hyperlex::dictionary& dict, const char* outputPath);
    int SFI_v02DataMatrixSwitch(hyperlex::dictionary& dict,
                                const char* outputPath,
                                const Evaluator& evaluator,
                                const xyzFile& frames);
}
}

#endif
