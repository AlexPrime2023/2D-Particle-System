#pragma once

#include "Emitter.h"

class SphereEmitter : public Emitter
{
public:
	sf::Vector2f calculatePosition() override;
	sf::Vector2f calculateVelocity() override;
	float calculateAngle() override;
};

