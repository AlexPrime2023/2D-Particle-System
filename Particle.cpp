#include "Particle.h"

#include <cmath>
#include <iostream>

Particle::Particle(float x, float y, const ParticleSettings& settings) :
	m_position(x, y),
	m_velocity(settings.speed* std::cos(settings.angle), settings.speed* std::sin(settings.angle)),
	m_lifetime(settings.lifetime),
	m_color(settings.color)
{
}

Particle::Particle(const Particle& particle) :
	m_position(particle.m_position),
	m_velocity(particle.m_velocity),
	m_lifetime(particle.m_lifetime),
	m_color(particle.m_color)
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
	m_lifetime -= dt;
	m_position += m_velocity * dt;
}

void Particle::swap(Particle& particle) noexcept
{
	std::swap(m_position, particle.m_position);
	std::swap(m_velocity, particle.m_velocity);
	std::swap(m_lifetime, particle.m_lifetime);
	std::swap(m_color, particle.m_color);
}
