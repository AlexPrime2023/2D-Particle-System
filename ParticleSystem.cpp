#include "ParticleSystem.h"
#include <SFML/Graphics/CircleShape.hpp>

// TODO To another file
#include "SphereEmitter.h"
#include "ConeEmitter.h"
#include "PlaneEmitter.h"

ParticleSystem::ParticleSystem(unsigned int maxParticles) :
    m_maxParticles(maxParticles),
    m_color(sf::Color::White),
    m_emitterPosition(0.0f, 0.0f),
    m_emissionRate(0.0f),
    m_emitterRadius(0.0f),
    m_particleLifetime(0.0f),
    m_particleSize(0.0f),
    m_particleSpeed(0.0f),
    m_particleRotationSpeed(0.0f),
    m_isDrawTrail(false),
    m_trailSize(0)
{
    // Default sphere emitter
    m_emitter = std::make_shared<SphereEmitter>(SphereEmitter());
}

void ParticleSystem::update(float dt)
{
    float particlesToCreate = m_emissionRate * dt;

    for (int i = 0; i < particlesToCreate; ++i)
    {
        if (m_particles.size() < m_maxParticles)
        {
            if (m_emitter)
            {
                const sf::Vector2f position = m_emitter->calculatePosition();
                const sf::Vector2f velocity = m_emitter->calculateVelocity();
                const float angle = m_emitter->calculateAngle();

                ParticleSettings settings{ m_particleLifetime, m_particleSize, m_particleSpeed, angle, m_particleRotationSpeed, m_color, m_isDrawTrail, m_trailSize };
                m_particles.push_back({ position.x, position.y, settings });
                m_particles.back().setVelocity(velocity * m_particleSpeed);
            }
        }
    }

    for (auto&& particle : m_particles)
        particle.update(dt);

    m_particles.erase(std::remove_if(m_particles.begin(), m_particles.end(),
        [](const Particle& p) { return !p.isAlive(); }),
        m_particles.end());
}

void ParticleSystem::draw(sf::RenderWindow& window) const
{
    for (const auto& particle : m_particles)
    {
        if (particle.isDrawTail() && particle.trailSize() > 1) {
            for (size_t i = 1; i < particle.trailSize(); ++i) {
                sf::Vertex line[] = {
                    sf::Vertex(particle.trailIndex(i - 1), particle.color()),
                    sf::Vertex(particle.trailIndex(i), particle.color())
                };
                window.draw(line, 2, sf::Lines);
            }
        }

        sf::CircleShape shape(m_particleSize);
        shape.setFillColor(particle.color());
        shape.setPosition(particle.position());
        window.draw(shape);
    }
}
