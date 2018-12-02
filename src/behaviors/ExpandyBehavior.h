#ifndef EXPANDYBEHAVIOR_H
#define EXPANDYBEHAVIOR_H

#include "IEnemyBehavior.h"

class ExpandyBehavior : public IEnemyBehavior
{
	public:
		ExpandyBehavior();

		void update(float delta) override;
		void invokeOnActor(IBehaviorControllable &actor) override;

		sf::Sprite currentSpriteForActor(const SpriteSheetMapper &spriteSheetMapper, const IBehaviorControllable &actor) const override;
		sf::FloatRect currentCollisionBoxForActor(const IBehaviorControllable &actor) const override;
};

#endif // EXPANDYBEHAVIOR_H
