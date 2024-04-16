#pragma once

#include "Emitter.h"

class ConeEmitter : public Emitter
{
public:
	ConeEmitter(float startAngle, float endAngle);
	sf::Vector2f calculatePosition() override;
	sf::Vector2f calculateVelocity() override;
	float calculateAngle() override;

private:
	float m_startAngle;
	float m_endAngle;

	float m_coneAngle;
};
