#ifndef BLOBBEHAVIOR_H
#define BLOBBEHAVIOR_H

#include <map>

#include "IEnemyBehavior.h"

class IBehaviorControllable;
class IMapInformationProvider;
class Player;

class BlobBehavior : public IEnemyBehavior
{
	public:
		BlobBehavior(Player& player, const IMapInformationProvider &mapInformationProvider);

		void update(float delta) override;

		void invokeOnActor(IBehaviorControllable& actor) override;

		sf::Sprite currentSpriteForActor(const SpriteSheetMapper& spriteSheetMapper, const IBehaviorControllable& actor) const override;

		sf::FloatRect currentCollisionBoxForActor(const IBehaviorControllable& actor) const override;

	private:
		Player& m_player;
		const IMapInformationProvider &m_mapInformationProvider;

		std::map<IBehaviorControllable*, float> m_jumpCoolDowns;
		float m_elapsed;

		// IEnemyBehavior interface
	public:
		int health() const override;
};

#endif // BLOBBEHAVIOR_H
