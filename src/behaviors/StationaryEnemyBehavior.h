#ifndef STATIONARYENEMYBEHAVIOR_H
#define STATIONARYENEMYBEHAVIOR_H

#include "IEnemyBehavior.h"

class StationaryEnemyBehavior : public IEnemyBehavior
{
	public:
		void update(float delta) override;

		void invokeOnActor(Enemy& enemy) const override;
};

#endif // STATIONARYENEMYBEHAVIOR_H
