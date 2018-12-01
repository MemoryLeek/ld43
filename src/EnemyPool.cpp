#include "EnemyFactory.h"
#include "IMapInformationProvider.h"

#include "EnemyPool.h"

EnemyPool::EnemyPool(EnemyFactory& enemyFactory, const IMapInformationProvider& mapInformationProvider)
	: m_mapInformationProvider(mapInformationProvider)
{
	m_enemies.reserve(m_mapInformationProvider.spawnPoints().size());

	for (const auto& spawn : m_mapInformationProvider.spawnPoints())
	{
		m_enemies.emplace_back(enemyFactory.createInstance(spawn.type()));
		m_enemies.back().respawn(spawn.position());
	}
}

std::vector<Enemy> EnemyPool::enemies() const
{
	return m_enemies;
}

void EnemyPool::update(float delta)
{
	for (size_t i = 0; i < m_enemies.size(); i++)
	{
		auto& enemy = m_enemies[i];

		if (enemy.isDead())
		{
			enemy.respawn(m_mapInformationProvider.spawnPoints()[i].position());
		}

		enemy.update(delta);
	}
}
