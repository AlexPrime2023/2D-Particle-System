#pragma once

#include <SFML/System/Vector2.hpp>

#include "ParticleSettings.h"


class Particle
{
public:
    Particle(float x, float y, const ParticleSettings& settings);
    ~Particle() = default;

    Particle(const Particle& particle);
    Particle& operator=(const Particle& particle);

    // Doesn't make sense since primitive types
    Particle(Particle&& particle) noexcept = default;
    Particle& operator=(Particle&& particle) noexcept = default;

public:
    void update(float dt);

public:
    inline bool isAlive() const { return m_lifetime > 0.0f; };

public:
    inline sf::Vector2f velocity() const { return m_velocity; };
    inline void setVelocity(const sf::Vector2f& velocity) { m_velocity = velocity; }

    inline sf::Vector2f position() const { return m_position; };

    inline sf::Color color() const { return m_color; };

private:
    // Copy-swap idiom
    void swap(Particle& particle) noexcept;

private:
    sf::Vector2f m_position;
    sf::Vector2f m_velocity;
    float m_lifetime;
    sf::Color m_color;

    float m_rotationSpeed;
};
