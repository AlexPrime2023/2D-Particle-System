#include "SphereEmitter.h"

sf::Vector2f SphereEmitter::calculatePosition()
{
    return m_emitterPosition;
}

sf::Vector2f SphereEmitter::calculateVelocity()
{
    float theta = MathUtils::degToRad(std::rand() % 360);
    float phi = MathUtils::degToRad(std::rand() % 180);

    float x = m_emitterRadius * std::sin(phi) * std::cos(theta);
    float y = m_emitterRadius * std::sin(phi) * std::sin(theta);

    sf::Vector2f direction = sf::Vector2f(x, y);
    sf::Vector2f normalizedDirection = direction / std::sqrt(direction.x * direction.x + direction.y * direction.y);

    return normalizedDirection;
}

float SphereEmitter::calculateAngle()
{
    return 0.0f;
}
