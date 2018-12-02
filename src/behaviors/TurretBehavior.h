#ifndef TURRETBEHAVIOR_H
#define TURRETBEHAVIOR_H

#include "IEnemyBehavior.h"

class TurretBehavior : public IEnemyBehavior
{
	public:
		TurretBehavior();

		void update(float delta) override;
		void invokeOnActor(IBehaviorControllable &actor) override;

		sf::Sprite currentSpriteForActor(const SpriteSheetMapper &spriteSheetMapper, const IBehaviorControllable &actor) const override;
		sf::FloatRect currentCollisionBoxForActor(const IBehaviorControllable &actor) const override;
};

#endif // TURRETBEHAVIOR_H
