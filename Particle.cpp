#include "Particle.h"

#include <cmath>
#include <iostream>

Particle::Particle(float x, float y, const ParticleSettings& settings) :
	m_position(x, y),
	m_velocity(settings.speed* std::cos(settings.angle), settings.speed* std::sin(settings.angle)),
	m_lifetime(settings.lifetime),
	m_color(settings.color),
	m_rotationSpeed(settings.rotationSpeed),
	m_isDrawTrail(settings.isDrawTrail),
	m_trailSize(settings.trailSize)
{
}

Particle::Particle(const Particle& particle) :
	m_position(particle.m_position),
	m_velocity(particle.m_velocity),
	m_lifetime(particle.m_lifetime),
	m_color(particle.m_color),
	m_rotationSpeed(particle.m_rotationSpeed),
	m_isDrawTrail(particle.m_isDrawTrail),
	m_trailSize(particle.m_trailSize)
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

	m_position += m_velocity * dt;
}

void Particle::swap(Particle& particle) noexcept
{
	std::swap(m_position, particle.m_position);
	std::swap(m_velocity, particle.m_velocity);
	std::swap(m_lifetime, particle.m_lifetime);
	std::swap(m_color, particle.m_color);
	std::swap(m_rotationSpeed, particle.m_rotationSpeed);
	std::swap(m_isDrawTrail, particle.m_isDrawTrail);
	std::swap(m_trailSize, particle.m_trailSize);
}
