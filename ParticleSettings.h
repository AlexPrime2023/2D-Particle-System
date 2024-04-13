#pragma once

#include <SFML/Graphics/Color.hpp>

struct ParticleSettings {
    float lifetime;
    float size;
    float speed;
    float angle;
    float rotationSpeed;
    sf::Color color;
    bool isDrawTrail;
    int trailSize;

    ParticleSettings(float lifetime, float size, float speed, float angle, float rotationSpeed, const sf::Color& color, bool isDrawTrail, int trailSize)
        : lifetime(lifetime),
        size(size),
        speed(speed),
        angle(angle),
        rotationSpeed(rotationSpeed),
        color(color),
        isDrawTrail(isDrawTrail),
        trailSize(trailSize)
    {}
};
