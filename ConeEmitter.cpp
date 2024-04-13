#include "ConeEmitter.h"

ConeEmitter::ConeEmitter(float startAngle, float endAngle) :
	m_startAngle(startAngle * 3.14159f / 180.0f),
	m_endAngle(endAngle * 3.14159f / 180.0f),
	m_coneAngle(0.0f)
{
}

sf::Vector2f ConeEmitter::calculatePosition()
{
	return m_emitterPosition;
}

sf::Vector2f ConeEmitter::calculateVelocity()
{
	m_coneAngle = (std::rand() % (static_cast<int>((m_startAngle - m_endAngle) * 100))) / 100.0f + sin(90);
	return sf::Vector2f(std::cos(m_coneAngle), std::sin(m_coneAngle));
}

float ConeEmitter::calculateAngle()
{
	return m_coneAngle;
}
