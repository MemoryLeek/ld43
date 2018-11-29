#ifndef ISTATE_H
#define ISTATE_H

#include <SFML/Graphics.hpp>

class IState : public sf::Drawable
{
	public:
		virtual void keyPressed(const sf::Event::KeyEvent &event) = 0;
		virtual void keyReleased(const sf::Event::KeyEvent &event) = 0;

		virtual void update(long delta) = 0;
};

#endif // ISTATE_H
