#include <SFML/Graphics.hpp>
#include "ParticleSystem.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "Test SFML");

	ParticleSystem particleSystem(1000);

	particleSystem.setEmitterPosition(sf::Vector2f(window.getSize().x / 2.0f, window.getSize().y / 2.0f));
	particleSystem.setEmissionRate(100.0f);
	particleSystem.setEmitterRadius(100.0f);
	particleSystem.setParticleLifetime(5.0f);
	particleSystem.setParticleSize(5.0f);
	particleSystem.setParticleSpeed(50.0f);
	particleSystem.setParticleRotationSpeed(0.0f);

	particleSystem.setDrawTrail(true);
	particleSystem.setTrailSize(20);

	particleSystem.setColor(sf::Color::Red);

	sf::Clock clock;
	const int maxFPS = 60;
	const float fixedTimeStep = 1.0f / (maxFPS ? static_cast<double>(maxFPS) : 1.0f);
	float accumulatedTime = 0.0f;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		float deltaTime = clock.restart().asSeconds();
		accumulatedTime += deltaTime;

		while (accumulatedTime >= fixedTimeStep) {
			// Update game
			particleSystem.update(fixedTimeStep);
			accumulatedTime -= fixedTimeStep;
		}

		window.clear();
		particleSystem.draw(window);
		window.display();
	}

	return 0;
}
