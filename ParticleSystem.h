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

	inline void setColor(const sf::Color& color) { m_startColor = color; m_endColor = color; };
	inline void setStartColor(const sf::Color& startColor) { m_startColor = startColor; };
	inline void setEndColor(const sf::Color& endColor) { m_endColor = endColor; };

	inline void setDrawTrail(bool isDrawTrail) { m_isDrawTrail = isDrawTrail; }
	inline void setTrailSize(int trailSize) { m_trailSize = trailSize; }

	inline void setEasingCurveParticleSize(std::shared_ptr<EasingCurve> particleSizeCurve) { m_particleSizeCurve = std::move(particleSizeCurve); };
	inline void setEasingCurveRGB(std::shared_ptr<EasingCurve> rgbCurve) { m_rgbCurve = std::move(rgbCurve); };
	inline void setEasingCurveAplha(std::shared_ptr<EasingCurve> alphaCurve) { m_alphaCurve = std::move(alphaCurve); };

private:
	unsigned int m_maxParticles;

	std::vector<Particle> m_particles;
	sf::Color m_startColor;
	sf::Color m_endColor;

	sf::Vector2f m_emitterPosition;
	float m_emissionRate;
	float m_emitterRadius;

	float m_particleLifetime;
	float m_particleSize;
	float m_particleSpeed;
	float m_particleRotationSpeed;

	bool m_isDrawTrail;
	int m_trailSize;

	std::shared_ptr<Emitter> m_emitter;

	std::shared_ptr<EasingCurve> m_particleSizeCurve;
	std::shared_ptr<EasingCurve> m_rgbCurve;
	std::shared_ptr<EasingCurve> m_alphaCurve;
};
