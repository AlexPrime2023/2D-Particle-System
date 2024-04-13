#pragma once

#include <SFML/Graphics/Color.hpp>
#include <memory>

#include "EasingCurves.h"

struct ParticleSettings {
    float lifeTime;
    float size;
    float speed;
    float angle;
    float rotationSpeed;
    sf::Vector2f force;
    float particleMass;
    sf::Color startColor;
    sf::Color endColor;
    bool isDrawTrail;
    int trailSize;
    std::shared_ptr<EasingCurve> particleSizeCurve;
    std::shared_ptr<EasingCurve> rgbCurve;
    std::shared_ptr<EasingCurve> alphaCurve;
    std::shared_ptr<EasingCurve> forceCurve;

    ParticleSettings(float lifeTime, float size, float speed, float angle, float rotationSpeed, sf::Vector2f force, float particleMass, const sf::Color& startColor, const sf::Color& endColor, bool isDrawTrail, int trailSize, std::shared_ptr<EasingCurve> particleSizeCurve, std::shared_ptr<EasingCurve> rgbCurve, std::shared_ptr<EasingCurve> alphaCurve, std::shared_ptr<EasingCurve> forceCurve)
        : lifeTime(lifeTime),
        size(size),
        speed(speed),
        angle(angle),
        rotationSpeed(rotationSpeed),
        force(force),
        particleMass(particleMass),
        startColor(startColor),
        endColor(endColor),
        isDrawTrail(isDrawTrail),
        trailSize(trailSize),
        particleSizeCurve(particleSizeCurve),
        rgbCurve(rgbCurve),
        alphaCurve(alphaCurve),
        forceCurve(forceCurve)
    {}
};
