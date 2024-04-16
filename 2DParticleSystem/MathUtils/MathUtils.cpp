#include "MathUtils.h"

#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif

float MathUtils::radToDeg(float angle)
{
    return angle * 180.0f / M_PI;
}

float MathUtils::degToRad(float angle)
{
    return angle * M_PI / 180.0f;
}

bool MathUtils::isNumbersAreSameFuzzyCompare(float a, float b)
{
    constexpr float epsilon = std::numeric_limits<float>::epsilon();
    return std::abs(a - b) < epsilon;
}
