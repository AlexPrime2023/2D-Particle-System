#pragma once

#include <SFML/Graphics/Color.hpp>
#include <memory>

#include "EasingCurves.h"

struct ParticleSettings {
    float lifetime;
    float size;
    float speed;
    float angle;
    float rotationSpeed;
    sf::Color color;
    bool isDrawTrail;
    int trailSize;
    std::shared_ptr<EasingCurve> particleSizeCurve;

    ParticleSettings(float lifetime, float size, float speed, float angle, float rotationSpeed, const sf::Color& color, bool isDrawTrail, int trailSize, std::shared_ptr<EasingCurve> particleSizeCurve)
        : lifetime(lifetime),
        size(size),
        speed(speed),
        angle(angle),
        rotationSpeed(rotationSpeed),
        color(color),
        isDrawTrail(isDrawTrail),
        trailSize(trailSize),
        particleSizeCurve(particleSizeCurve)
    {}
};
