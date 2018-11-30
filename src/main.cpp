#include <iostream>
#include <cmath>

#include <SFML/Graphics.hpp>

#include <tmxlite/Map.hpp>

#include "Utility.h"
#include "StateHandler.h"

const float TICK = 0.005;

int main()
{
	sf::RenderWindow window(sf::VideoMode(1280, 720), "ld43");

	sf::Texture spriteSheet;
	spriteSheet.loadFromFile("resources/spritesheet.png");

	StateHandler stateHandler(spriteSheet);

	sf::Clock deltaClock;

	for (float elapsed = 0; window.isOpen();)
	{
		sf::Event event;

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::KeyPressed)
			{
				stateHandler.keyPressed(event.key);
			}

			if (event.type == sf::Event::KeyReleased)
			{
				stateHandler.keyReleased(event.key);
			}

			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}

		const float seconds = deltaClock
			.restart()
			.asSeconds();

		for (elapsed += seconds; elapsed > TICK; elapsed -= TICK)
		{
			stateHandler.update(TICK);
		}

		window.clear(sf::Color::Black);
		window.draw(stateHandler);
		window.display();
	}

	return 0;
}
