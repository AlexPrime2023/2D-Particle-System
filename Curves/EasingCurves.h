#pragma once

class EasingCurve
{
public:
    virtual float interpolate(float t) const = 0;
};

class LinearEasing : public EasingCurve {
public:
    float interpolate(float t) const override {
        return t;
    }
};
