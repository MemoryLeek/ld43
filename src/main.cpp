#include <iostream>
#include <cmath>

#include <SFML/Graphics.hpp>

#include <tmxlite/Map.hpp>

#include "Utility.h"
#include "StateHandler.h"
#include "SettingsProvider.h"

#ifdef SHOWFPS
void fpsTimer()
{
	static sf::Clock frameClock;
	static int frameCounter;

	frameCounter++;
	if (frameClock.getElapsedTime().asMilliseconds() > 1000)
	{
		frameClock.restart();
		std::cout << frameCounter << " FPS" << std::endl;
		frameCounter = 0;
	}
}
#else
#define fpsTimer() ((void)0)
#endif // SHOWFPS

const float TICK = 0.005;

int main()
{
	sf::RenderWindow window(sf::VideoMode(1280, 720), "ld43");
	auto view = window.getDefaultView();
	view.setSize(1280 / 4, 720 / 4);
	view.setCenter(view.getCenter() / 4.f);
	window.setView(view);

	sf::RenderTexture fbo;
	const auto fboCreated = fbo.create(1280 / 4, 720 / 4);
	assert(fboCreated);

	sf::Sprite fboSprite(fbo.getTexture());

	sf::Texture spriteSheet;
	spriteSheet.loadFromFile("resources/spritesheet.png");

	SettingsProvider settingsProvider;
	Settings settings = settingsProvider.load();

	StateHandler stateHandler(settings, spriteSheet);

	sf::Clock deltaClock;

	tmx::Map map;

	for (float elapsed = 0; window.isOpen();)
	{
		sf::Event event;

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::KeyPressed)
			{
				stateHandler.keyPressed(event);
			}

			if (event.type == sf::Event::KeyReleased)
			{
				stateHandler.keyReleased(event);
			}

			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}

		const float seconds = deltaClock
			.restart()
			.asSeconds();

		for (elapsed += seconds; elapsed >= TICK; elapsed -= TICK)
		{
			stateHandler.update(TICK);
		}

		fbo.draw(stateHandler);
		fbo.display();

		window.draw(fboSprite);
		window.display();

		fpsTimer();
	}

	return 0;
}
