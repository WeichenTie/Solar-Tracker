#pragma once

namespace Helpers
{
    float lerp(float a, float b, float t)
    {
        return (1.0f - t) * a + b * t;
    }
    float invLerp(float a, float b, float v)
    {
        return (v - a) / (b - a);
    }
    float remap(float iMin, float iMax, float oMin, float oMax, float v)
    {
        return lerp(oMin, oMax, invLerp(iMin, iMax, v));
    }
} // namespace Helpers
