#include "PlaneEmitter.h"

sf::Vector2f PlaneEmitter::calculatePosition()
{
    float x = static_cast<float>(std::rand() % static_cast<int>(2.0f * m_emitterRadius) - m_emitterRadius);
    float y = static_cast<float>(std::rand() % static_cast<int>(2.0f * m_emitterRadius) - m_emitterRadius);
    return m_emitterPosition + sf::Vector2f(x, y);
}

sf::Vector2f PlaneEmitter::calculateVelocity()
{
    m_angle = (std::rand() % 360) * 3.14159f / 180.0f;
    return sf::Vector2f(std::cos(m_angle), std::sin(m_angle));
}

float PlaneEmitter::calculateAngle()
{
    return m_angle;
}
