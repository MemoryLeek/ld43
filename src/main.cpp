#include <iostream>
#include <cmath>

#include <SFML/Graphics.hpp>

#include <tmxlite/Map.hpp>

#include "Utility.h"
#include "StateHandler.h"

class Player
{
	public:
		Player()
			: m_x(0)
			, m_y(0)
		{
		}

		int x() const
		{
			return m_x;
		}

		void setX(int x)
		{
			m_x = x;
		}

		int y()
		{
			return m_y;
		}

		void setY(int y)
		{
			m_y = y;
		}

	private:
		int m_x;
		int m_y;
};

class PlayerDrawable : public sf::Drawable
{
	public:
		PlayerDrawable(Player &player)
			: m_player(player)
		{
			m_texture.loadFromFile("resources/player.png");
		}

	protected:
		void draw(sf::RenderTarget &target, sf::RenderStates states) const override
		{
			UNUSED(states);

			sf::Sprite sprite(m_texture);
			sprite.setPosition(m_player.x(), m_player.y());

			target.draw(sprite);
		}

	private:
		sf::Texture m_texture;

		Player &m_player;
};


int main()
{
	sf::RenderWindow window(sf::VideoMode(1280, 720), "ld43");

	StateHandler stateHandler;

	sf::Clock deltaClock;

	tmx::Map map;

	while (window.isOpen())
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

		const float delta = deltaClock
			.restart()
			.asSeconds();

		stateHandler.update(delta);

		window.clear(sf::Color::Black);
		window.draw(stateHandler);
		window.display();
	}

	return 0;
}
