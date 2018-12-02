#ifndef TURRETBEHAVIOR_H
#define TURRETBEHAVIOR_H

#include <map>

#include "IEnemyBehavior.h"
#include "SpriteSheetMapper.h"

class ProjectileHitDetector;

struct TurretState
{
	TurretState()
		: elapsed(rand())
		, direction(0)
	{
	}

	float elapsed;
	int direction;
};

class TurretBehavior : public IEnemyBehavior
{
	public:
		TurretBehavior(int spawnDirection, ProjectileHitDetector& projectileHitDetector);

		void update(float delta) override;
		void invokeOnActor(IBehaviorControllable &actor) override;

		sf::Sprite currentSpriteForActor(const SpriteSheetMapper &spriteSheetMapper, const IBehaviorControllable &actor) const override;
		sf::FloatRect currentCollisionBoxForActor(const IBehaviorControllable &actor) const override;

	private:
		TurretState getTurretState(const IBehaviorControllable &actor) const;
		SpriteId getSprite(const TurretState &state) const;
		int getSpriteIndex(const TurretState &state) const;

		ProjectileHitDetector& m_projectileHitDetector;
		int m_spawnDirection;

		std::map<const IBehaviorControllable*, TurretState> m_states;
};

#endif // TURRETBEHAVIOR_H
