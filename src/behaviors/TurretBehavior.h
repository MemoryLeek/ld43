#ifndef TURRETBEHAVIOR_H
#define TURRETBEHAVIOR_H

#include <map>

#include "IEnemyBehavior.h"
#include "SpriteSheetMapper.h"
#include "Bullet.h"

class IMapInformationProvider;
class ProjectileHitDetector;
class Player;

struct TurretState
{
	TurretState()
		: elapsed(rand())
		, shootingTimer(0)
		, direction(0)
	{
	}

	float elapsed;
	float shootingTimer;
	int direction;
};

class TurretBehavior : public IEnemyBehavior
{
	public:
		TurretBehavior(int spawnDirection
			, ProjectileHitDetector &projectileHitDetector
			, const IMapInformationProvider &mapInformationProvider
			, Player &player
			);

		void update(float delta) override;
		void invokeOnActor(IBehaviorControllable &actor) override;

		sf::Sprite currentSpriteForActor(const SpriteSheetMapper &spriteSheetMapper, const IBehaviorControllable &actor) const override;
		sf::FloatRect currentCollisionBoxForActor(const IBehaviorControllable &actor) const override;

		std::vector<Bullet> bullets() const;

	private:
		TurretState getTurretState(const IBehaviorControllable &actor) const;
		SpriteId getSprite(const TurretState &state) const;
		int getSpriteIndex(const TurretState &state) const;

		const IMapInformationProvider& m_mapInformationProvider;

		ProjectileHitDetector &m_projectileHitDetector;
		Player &m_player;

		int m_spawnDirection;

		std::map<const IBehaviorControllable*, TurretState> m_states;
		std::vector<Bullet> m_bullets;
};

#endif // TURRETBEHAVIOR_H
