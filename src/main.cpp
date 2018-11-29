#include <SFML/Graphics.hpp>

template<typename T>
void UNUSED(T &)
{
}

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

class IState
{
};

class StateTransition
{

};

class StateHandler : public sf::Drawable
{
	public:
		StateHandler()
			: m_current(nullptr)
			, m_next(nullptr)
		{
		}

		void keyPressed(const sf::Event::KeyEvent &event)
		{
			UNUSED(event);
		}

		void keyReleased(const sf::Event::KeyEvent &event)
		{
			UNUSED(event);
		}

		void update(long delta)
		{
			UNUSED(delta);
		}

//		void

		// Drawable interface
	protected:
		void draw(sf::RenderTarget &target, sf::RenderStates states) const override
		{
			UNUSED(target);
			UNUSED(states);
		}

	private:
		StateTransition m_transition;

		IState *m_current;
		IState *m_next;
};

int main()
{
	sf::RenderWindow window(sf::VideoMode(1280, 720), "ld43");

	Player player;
	PlayerDrawable playerDrawable(player);

	while (window.isOpen())
	{
		sf::Event event;

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::KeyPressed)
			{
				switch (event.key.code)
				{
					case sf::Keyboard::W:
						player.setY(player.y() - 32);
						break;
					case sf::Keyboard::A:
						player.setX(player.x() - 32);
						break;
					case sf::Keyboard::S:
						player.setY(player.y() + 32);
						break;
					case sf::Keyboard::D:
						player.setX(player.x() + 32);
						break;
					default:
						break;
				}
			}

			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}

		window.clear(sf::Color::Black);
		window.draw(playerDrawable);
		window.display();
	}

	return 0;
}
