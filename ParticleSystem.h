#pragma once

#include <vector>
#include <SFML/Graphics/RenderWindow.hpp>

#include "Particle.h"

#include "Emitter.h"

class ParticleSystem
{
public:
	ParticleSystem(unsigned int maxParticles);
	~ParticleSystem() = default;

	ParticleSystem(const ParticleSystem& particle) = delete;
	ParticleSystem& operator=(const ParticleSystem& particle) = delete;

	ParticleSystem(ParticleSystem&& particle) noexcept = delete;
	ParticleSystem& operator=(ParticleSystem&& particle) noexcept = delete;

public:
	void update(float dt);
	void draw(sf::RenderWindow& window) const;

public:
	inline void setEmitterPosition(const sf::Vector2f& emiterPosition) { m_emitterPosition = emiterPosition; m_emitter->setEmiterPosition(emiterPosition); };
	inline void setEmissionRate(float emissionRate) { m_emissionRate = emissionRate; };
	inline void setEmitterRadius(float emitterRadius) { m_emitterRadius = emitterRadius; m_emitter->setEmiterRadius(emitterRadius); };
	inline void setParticleLifetime(float particleLifetime) { m_particleLifetime = particleLifetime; };
	inline void setParticleSize(float particleSize) { m_particleSize = particleSize; };
	inline void setParticleSpeed(float particleSpeed) { m_particleSpeed = particleSpeed; };
	inline void setParticleRotationSpeed(float particleRotationSpeed) { m_particleRotationSpeed = particleRotationSpeed; };
	inline void setColor(const sf::Color& color) { m_color = color; };

private:
	unsigned int m_maxParticles;

	std::vector<Particle> m_particles;
	sf::Color m_color;

	sf::Vector2f m_emitterPosition;
	float m_emissionRate;
	float m_emitterRadius;

	float m_particleLifetime;
	float m_particleSize;
	float m_particleSpeed;
	float m_particleRotationSpeed;

	std::shared_ptr<Emitter> m_emitter;
};
