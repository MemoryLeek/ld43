#ifndef ISTATE_H
#define ISTATE_H

#include <SFML/Graphics.hpp>

#include "IUpdatable.h"

class IState : public sf::Drawable, public IUpdatable
{
	public:
		virtual void keyPressed(const sf::Event::KeyEvent &event) = 0;
		virtual void keyReleased(const sf::Event::KeyEvent &event) = 0;
};

#endif // ISTATE_H
