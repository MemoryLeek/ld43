#ifndef ENEMYPOOL_H
#define ENEMYPOOL_H

#include <vector>

#include "Enemy.h"
#include "IUpdatable.h"

class EnemyFactory;
class IMapInformationProvider;

class EnemyPool : public IUpdatable
{
	public:
		EnemyPool(EnemyFactory& enemyFactory, const IMapInformationProvider& mapInformationProvider);

		std::vector<Enemy*> enemies() const;

		void update(float delta) override;

		bool canRespawn(size_t index) const;
		void setRespawnCooldown(size_t index, float cooldown);

	private:
		const IMapInformationProvider& m_mapInformationProvider;

		std::vector<Enemy*> m_enemies;
		std::vector<float> m_respawnTimers;
};

#endif // ENEMYPOOL_H
