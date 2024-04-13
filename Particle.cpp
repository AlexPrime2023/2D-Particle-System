#include "Particle.h"

#include "MathUtils/MathUtils.h"
#include <iostream>

Particle::Particle(float x, float y, const ParticleSettings& settings) :
	m_position(x, y),
	m_velocity(settings.speed * std::cos(settings.angle), settings.speed * std::sin(settings.angle)),
	m_startLifeTime(settings.lifeTime),
	m_startParticleSize(settings.size),
	m_startForce(settings.force),
	m_curveTime(0.0f),
	m_easedColor(settings.startColor),
	m_particleSettings(settings)
{
}

Particle::Particle(const Particle& particle) :
	m_position(particle.m_position),
	m_velocity(particle.m_velocity),
	m_startLifeTime(particle.m_startLifeTime),
	m_startParticleSize(particle.m_startParticleSize),
	m_startForce(particle.m_startForce),
	m_curveTime(particle.m_curveTime),
	m_easedColor(particle.m_easedColor),
	m_particleSettings(particle.m_particleSettings)
{
}

Particle& Particle::operator=(const Particle& particle)
{
	if (this != &particle)
	{
		Particle copyParticle(particle);
		swap(copyParticle);
	}

	return *this;
}

void Particle::update(float dt)
{
	if (m_particleSettings.isDrawTrail)
	{
		m_trail.push_back(m_position);

		// Limit the trail size
		if (m_trail.size() > m_particleSettings.trailSize) {
			m_trail.erase(m_trail.begin());
		}
	}

	m_particleSettings.lifeTime -= dt;

	// Update the particle rotation angle
	float angle = std::atan2(m_velocity.y, m_velocity.x) + m_particleSettings.rotationSpeed * dt;
	m_velocity = sf::Vector2f(std::cos(angle), std::sin(angle)) * std::sqrt(m_velocity.x * m_velocity.x + m_velocity.y * m_velocity.y);

	if (m_particleSettings.particleSizeCurve || m_particleSettings.rgbCurve || m_particleSettings.alphaCurve || m_particleSettings.forceCurve)
		// Time progression from 0 to 1
		m_curveTime = 1.0f - (m_particleSettings.lifeTime / m_startLifeTime);

	if (m_particleSettings.particleSizeCurve)
	{
		float easingFactor = m_particleSettings.particleSizeCurve->interpolate(m_curveTime);
		m_particleSettings.size = m_startParticleSize * easingFactor;
	}

	if (m_particleSettings.rgbCurve)
	{
		float easingFactor = m_particleSettings.rgbCurve->interpolate(m_curveTime);

		m_easedColor.r = static_cast<sf::Uint8>((1.0f - easingFactor) * m_particleSettings.startColor.r + easingFactor * m_particleSettings.endColor.r);
		m_easedColor.g = static_cast<sf::Uint8>((1.0f - easingFactor) * m_particleSettings.startColor.g + easingFactor * m_particleSettings.endColor.g);
		m_easedColor.b = static_cast<sf::Uint8>((1.0f - easingFactor) * m_particleSettings.startColor.b + easingFactor * m_particleSettings.endColor.b);
	}

	if (m_particleSettings.alphaCurve)
	{
		float easingFactor = m_particleSettings.alphaCurve->interpolate(m_curveTime);
		m_easedColor.a = static_cast<sf::Uint8>((1.0f - easingFactor) * m_particleSettings.startColor.a + easingFactor * m_particleSettings.endColor.a);
	}

	if (m_particleSettings.forceCurve)
	{
		float easingFactor = m_particleSettings.forceCurve->interpolate(m_curveTime);
		m_particleSettings.force = m_startForce * easingFactor;
	}

	// Update velocity with force proportional to particle mass
	if (MathUtils::isNumbersAreSameFuzzyCompare(m_particleSettings.force.x, 0.0f) || MathUtils::isNumbersAreSameFuzzyCompare(m_particleSettings.force.y, 0.0f))
		m_velocity += m_particleSettings.force / (m_particleSettings.particleMass > 0.0f ? m_particleSettings.particleMass : 1.0f);

	m_position += m_velocity * dt;
}

void Particle::swap(Particle& particle) noexcept
{
	std::swap(m_position, particle.m_position);
	std::swap(m_velocity, particle.m_velocity);
	std::swap(m_startLifeTime, particle.m_startLifeTime);
	std::swap(m_startParticleSize, particle.m_startParticleSize);
	std::swap(m_startForce, particle.m_startForce);
	std::swap(m_curveTime, particle.m_curveTime);
	std::swap(m_easedColor, particle.m_easedColor);
	std::swap(m_trail, particle.m_trail);
	std::swap(m_particleSettings, particle.m_particleSettings);
}
