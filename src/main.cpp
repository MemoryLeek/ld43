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
const float JOY_DEAD = 20.f;

int main()
{
	sf::RenderWindow window(sf::VideoMode(RES_X, RES_Y), "Pixel Rot", sf::Style::Close);
	window.setFramerateLimit(200);

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

			if (event.type == sf::Event::MouseButtonPressed)
			{
				stateHandler.mouseButtonPressed(event);
			}

			if (event.type == sf::Event::MouseButtonReleased)
			{
				stateHandler.mouseButtonReleased(event);
			}

			if (event.type == sf::Event::JoystickButtonPressed)
			{
				stateHandler.joystickButtonPressed(event);
			}

			if (event.type == sf::Event::JoystickButtonReleased)
			{
				stateHandler.joystickButtonReleased(event);
			}

			if (event.type == sf::Event::JoystickMoved)
			{
				if (event.joystickMove.axis == sf::Joystick::X)
				{
					if (fabs(event.joystickMove.position) > JOY_DEAD)
					{
						sf::Event emulatedKeyEvent;
						emulatedKeyEvent.type = sf::Event::KeyPressed;

						if (event.joystickMove.position < 0.0f)
						{
							emulatedKeyEvent.key.code = sf::Keyboard::A;
						}
						else
						{
							emulatedKeyEvent.key.code = sf::Keyboard::D;
						}

						stateHandler.keyPressed(emulatedKeyEvent);
					}
					else
					{
						sf::Event emulatedKeyEvent1;
						emulatedKeyEvent1.type = sf::Event::KeyReleased;
						emulatedKeyEvent1.key.code = sf::Keyboard::A;

						sf::Event emulatedKeyEvent2;
						emulatedKeyEvent2.type = sf::Event::KeyReleased;
						emulatedKeyEvent2.key.code = sf::Keyboard::D;

						stateHandler.keyReleased(emulatedKeyEvent1);
						stateHandler.keyReleased(emulatedKeyEvent2);
					}
				}
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

		window.draw(stateHandler);
		window.display();

		fpsTimer();
	}

	settingsProvider.save(settings);

	return 0;
}
