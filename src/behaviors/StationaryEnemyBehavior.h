#ifndef STATIONARYENEMYBEHAVIOR_H
#define STATIONARYENEMYBEHAVIOR_H

#include "IEnemyBehavior.h"

class StationaryEnemyBehavior : public IEnemyBehavior
{
	public:
		void update(float delta) override;

		void invokeOnActor(IBehaviorControllable& actor) override;

		sf::Sprite currentSpriteForActor(const SpriteSheetMapper& spriteSheetMapper, const IBehaviorControllable& actor) const override;
};

#endif // STATIONARYENEMYBEHAVIOR_H
