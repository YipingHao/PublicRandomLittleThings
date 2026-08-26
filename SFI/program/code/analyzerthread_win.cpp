#include "analyzer.h"

using namespace analyzer;

int FIexpresses::compute(unsigned int threadCount, const double*input, size_t ldi, size_t rowi, size_t coli, double* output, size_t ldo, size_t rowo, size_t colo) const
{
    // Keep behavior deterministic when no threading backend is enabled.
    // This overload is required by callers that pass a thread count.
    (void)threadCount;
    return compute(input, ldi, rowi, coli, output, ldo, rowo, colo);
}

int FIexpresses::compute(unsigned int threadCount, const double*input, size_t ldi, size_t rowi, size_t coli, double* output, size_t ldo, size_t rowo, size_t colo, bool PowerNormalization) const
{
    (void)threadCount;
    return compute(input, ldi, rowi, coli, output, ldo, rowo, colo, PowerNormalization);
}

int SFIexpresses::compute(unsigned int threadCount, const double*input, size_t ldi, size_t rowi, size_t coli,
    double* output, size_t ldo, size_t rowo, size_t colo) const
{
    (void)threadCount;
    return compute(input, ldi, rowi, coli, output, ldo, rowo, colo);
}

int SFIexpresses::compute(unsigned int threadCount, const double*input, size_t ldi, size_t rowi, size_t coli,
    double* output, size_t ldo, size_t rowo, size_t colo, bool PowerNormalization) const
{
    (void)threadCount;
    return compute(input, ldi, rowi, coli, output, ldo, rowo, colo, PowerNormalization);
}

int FIexpresses::computeCosTransform(unsigned int threadCount, const double* cosineInput, size_t ldi, size_t rowi, size_t coli,
    double* output, size_t ldo, size_t rowo, size_t colo, const vector<unsigned int>& settings_cos) const
{
    (void)threadCount;
    return computeCosTransform(cosineInput, ldi, rowi, coli, output, ldo, rowo, colo, settings_cos);
}

int FIexpresses::computeAngleCosTransform(unsigned int threadCount, const double* angleCosineInput, size_t ldi, size_t rowi, size_t coli,
    double* output, size_t ldo, size_t rowo, size_t colo, const vector<unsigned int>& settingsA_cos) const
{
    return computeCosTransform(threadCount, angleCosineInput, ldi, rowi, coli,
        output, ldo, rowo, colo, settingsA_cos);
}
