#include "Particle.h"

#include "MathUtils.h"
#include <iostream>

Particle::Particle(float x, float y, const ParticleSettings& settings) :
	m_position(x, y),
	m_velocity(settings.speed* std::cos(settings.angle), settings.speed* std::sin(settings.angle)),
	m_lifetime(settings.lifetime),
	m_particleSize(settings.size),
	m_startColor(settings.startColor),
	m_endColor(settings.endColor),
	m_easedColor(settings.startColor),
	m_startLifeTime(settings.lifetime),
	m_startParticleSize(settings.size),
	m_startForce(settings.force),
	m_force(settings.force),
	m_particleMass(settings.particleMass),
	m_rotationSpeed(settings.rotationSpeed),
	m_isDrawTrail(settings.isDrawTrail),
	m_trailSize(settings.trailSize),
	m_particleSizeCurve(settings.particleSizeCurve),
	m_rgbCurve(settings.rgbCurve),
	m_alphaCurve(settings.alphaCurve),
	m_forceCurve(settings.forceCurve)
{
}

Particle::Particle(const Particle& particle) :
	m_position(particle.m_position),
	m_velocity(particle.m_velocity),
	m_lifetime(particle.m_lifetime),
	m_particleSize(particle.m_particleSize),
	m_startColor(particle.m_startColor),
	m_endColor(particle.m_endColor),
	m_easedColor(particle.m_startColor),
	m_startLifeTime(particle.m_startLifeTime),
	m_startParticleSize(particle.m_startParticleSize),
	m_startForce(particle.m_startForce),
	m_force(particle.m_force),
	m_particleMass(particle.m_particleMass),
	m_rotationSpeed(particle.m_rotationSpeed),
	m_isDrawTrail(particle.m_isDrawTrail),
	m_trailSize(particle.m_trailSize),
	m_particleSizeCurve(particle.m_particleSizeCurve),
	m_rgbCurve(particle.m_rgbCurve),
	m_alphaCurve(particle.m_alphaCurve),
	m_forceCurve(particle.m_forceCurve)
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
	if (m_isDrawTrail)
	{
		m_trail.push_back(m_position);

		// Limit the trail size
		if (m_trail.size() > m_trailSize) {
			m_trail.erase(m_trail.begin());
		}
	}

	m_lifetime -= dt;

	// Update the particle rotation angle
	float angle = std::atan2(m_velocity.y, m_velocity.x) + m_rotationSpeed * dt;
	m_velocity = sf::Vector2f(std::cos(angle), std::sin(angle)) * std::sqrt(m_velocity.x * m_velocity.x + m_velocity.y * m_velocity.y);

	if (m_particleSizeCurve)
	{
		// Updating the Particle's Direction Using a Curve
		// Time progression from 0 to 1
		float t = 1.0f - (m_lifetime / m_startLifeTime);
		float easingFactor = m_particleSizeCurve->interpolate(t);
		m_particleSize = m_startParticleSize * easingFactor;
	}

	if (m_rgbCurve)
	{
		float t = 1.0f - (m_lifetime / m_startLifeTime);
		float easingFactor = m_rgbCurve->interpolate(t);

		m_easedColor.r = static_cast<sf::Uint8>((1.0f - easingFactor) * m_startColor.r + easingFactor * m_endColor.r);
		m_easedColor.g = static_cast<sf::Uint8>((1.0f - easingFactor) * m_startColor.g + easingFactor * m_endColor.g);
		m_easedColor.b = static_cast<sf::Uint8>((1.0f - easingFactor) * m_startColor.b + easingFactor * m_endColor.b);
	}

	if (m_alphaCurve)
	{
		float t = 1.0f - (m_lifetime / m_startLifeTime);
		float easingFactor = m_alphaCurve->interpolate(t);
		m_easedColor.a = static_cast<sf::Uint8>((1.0f - easingFactor) * m_startColor.a + easingFactor * m_endColor.a);
	}

	if (m_forceCurve)
	{
		float t = 1.0f - (m_lifetime / m_startLifeTime);
		float easingFactor = m_forceCurve->interpolate(t);
		m_force = m_startForce * easingFactor;
	}

	// Update velocity with force proportional to particle mass
	if (MathUtils::isNumbersAreSameFuzzyCompare(m_force.x, 0.0f) || MathUtils::isNumbersAreSameFuzzyCompare(m_force.y, 0.0f))
		m_velocity += m_force / (m_particleMass > 0.0f ? m_particleMass : 1.0f);

	m_position += m_velocity * dt;
}

void Particle::swap(Particle& particle) noexcept
{
	std::swap(m_position, particle.m_position);
	std::swap(m_velocity, particle.m_velocity);
	std::swap(m_lifetime, particle.m_lifetime);
	std::swap(m_particleSize, particle.m_particleSize);
	std::swap(m_startColor, particle.m_startColor);
	std::swap(m_endColor, particle.m_endColor);
	std::swap(m_easedColor, particle.m_easedColor);
	std::swap(m_startLifeTime, particle.m_startLifeTime);
	std::swap(m_startParticleSize, particle.m_startParticleSize);
	std::swap(m_startForce, particle.m_startForce);
	std::swap(m_force, particle.m_force);
	std::swap(m_particleMass, particle.m_particleMass);
	std::swap(m_rotationSpeed, particle.m_rotationSpeed);
	std::swap(m_isDrawTrail, particle.m_isDrawTrail);
	std::swap(m_trailSize, particle.m_trailSize);
	std::swap(m_particleSizeCurve, particle.m_particleSizeCurve);
	std::swap(m_rgbCurve, particle.m_rgbCurve);
	std::swap(m_alphaCurve, particle.m_alphaCurve);
	std::swap(m_forceCurve, particle.m_forceCurve);
}
