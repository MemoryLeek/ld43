#ifndef IENEMYBEHAVIOR_H
#define IENEMYBEHAVIOR_H

#include "IUpdatable.h"

class Enemy;

class IEnemyBehavior : public IUpdatable
{
	public:
		virtual void invokeOnActor(Enemy& enemy) const = 0;
};

#endif // IENEMYBEHAVIOR_H
