#pragma once

#include <SFML/System/Vector2.hpp>

#include "ParticleSettings.h"

#include <vector>

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
    inline bool isDrawTail() const { return m_isDrawTrail; };

public:
    inline sf::Vector2f velocity() const { return m_velocity; };
    inline void setVelocity(const sf::Vector2f& velocity) { m_velocity = velocity; }

    inline sf::Vector2f position() const { return m_position; };

    inline float size() const { return m_particleSize; };

    inline sf::Color color() const { return m_easedColor; };

    inline int trailSize() const { return m_trail.size(); };
    inline sf::Vector2f trailIndex(int index) const { return m_trail[index]; };

private:
    // Copy-swap idiom
    void swap(Particle& particle) noexcept;

private:
    sf::Vector2f m_position;
    sf::Vector2f m_velocity;
    float m_lifetime;
    float m_particleSize;

    sf::Color m_startColor;
    sf::Color m_endColor;
    sf::Color m_easedColor;

    sf::Vector2f m_force;
    float m_particleMass;

    float m_startLifeTime;
    float m_startParticleSize;

    float m_rotationSpeed;

    bool m_isDrawTrail;
    int m_trailSize;

    std::vector<sf::Vector2f> m_trail;

    std::shared_ptr<EasingCurve> m_particleSizeCurve;
    std::shared_ptr<EasingCurve> m_rgbCurve;
    std::shared_ptr<EasingCurve> m_alphaCurve;
};
