#ifndef ISTATE_H
#define ISTATE_H

#include <SFML/Graphics.hpp>

class IState : public sf::Drawable
{
	public:
		virtual void update(long delta) = 0;
};

#endif // ISTATE_H
