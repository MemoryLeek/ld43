#ifndef IENEMYBEHAVIOR_H
#define IENEMYBEHAVIOR_H

#include "IUpdatable.h"

class IBehaviorControllable;

class IEnemyBehavior : public IUpdatable
{
	public:
		virtual void invokeOnActor(IBehaviorControllable& actor) = 0;
};

#endif // IENEMYBEHAVIOR_H
