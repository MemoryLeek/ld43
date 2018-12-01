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

		std::vector<Enemy> enemies() const;

		void update(float delta) override;

	private:
		const IMapInformationProvider& m_mapInformationProvider;

		std::vector<Enemy> m_enemies;
};

#endif // ENEMYPOOL_H
