#pragma once

#include <SFML/System/Vector2.hpp>
#include <cmath>
#include "MathUtils.h"

class Emitter
{
public:
    virtual sf::Vector2f calculatePosition() = 0;
    virtual sf::Vector2f calculateVelocity() = 0;
    virtual float calculateAngle() = 0;

    inline void setEmiterPosition(const sf::Vector2f& emiterPosition) { m_emitterPosition = emiterPosition; };
    inline void setEmiterRadius(const float& emiterRadius) { m_emitterRadius = emiterRadius; };

    virtual ~Emitter() {}

protected:
    sf::Vector2f m_emitterPosition;
    float m_emitterRadius;
};
