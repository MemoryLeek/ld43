#ifndef IBEHAVIORCONTROLLABLE_H
#define IBEHAVIORCONTROLLABLE_H

#include "Utility.h"

class IBehaviorControllable
{
	public:
		virtual sf::Vector2f position() const = 0;

		virtual void jump(float velocity) = 0;
		virtual void move(Direction direction, float velocity) = 0;
};

#endif // IBEHAVIORCONTROLLABLE_H
