#ifndef EXPANDYBEHAVIOR_H
#define EXPANDYBEHAVIOR_H

#include "IEnemyBehavior.h"

class Player;

class ExpandyBehavior : public IEnemyBehavior
{
	public:
		ExpandyBehavior(Player& player);

		void update(float delta) override;
		void invokeOnActor(IBehaviorControllable &actor) override;

		sf::Sprite currentSpriteForActor(const SpriteSheetMapper &spriteSheetMapper, const IBehaviorControllable &actor) const override;
		sf::FloatRect currentCollisionBoxForActor(const IBehaviorControllable &actor) const override;

	private:
		int getSpriteIndex(const IBehaviorControllable &actor) const;

		Player& m_player;

		// IEnemyBehavior interface
	public:
		int health() const override;
};

#endif // EXPANDYBEHAVIOR_H
