#include <iostream>

#include "EnemyFactory.h"
#include "IMapInformationProvider.h"

#include "EnemyPool.h"

constexpr float RESPAWN_DELAY = 5.f;

EnemyPool::EnemyPool(EnemyFactory& enemyFactory, const IMapInformationProvider& mapInformationProvider)
	: m_mapInformationProvider(mapInformationProvider)
{
	m_enemies.reserve(m_mapInformationProvider.spawnPoints().size());

	for (const auto& spawn : m_mapInformationProvider.spawnPoints())
	{
		m_enemies.emplace_back(enemyFactory.createInstance(spawn.type()));
	}

	m_respawnTimers.assign(m_enemies.size(), 0);
}

std::vector<Enemy*> EnemyPool::enemies() const
{
	return m_enemies;
}

void EnemyPool::update(float delta)
{
	for (size_t i = 0; i < m_enemies.size(); i++)
	{
		auto& enemy = m_enemies[i];

		if (enemy->isDead())
		{
			if (canRespawn(i))
			{
				enemy->respawn(m_mapInformationProvider.spawnPoints()[i].position());
				setRespawnCooldown(i, RESPAWN_DELAY);
			}
			else
			{
				m_respawnTimers[i] -= delta;
			}
		}

		enemy->update(delta);
	}
}

bool EnemyPool::canRespawn(size_t index) const
{
	return m_respawnTimers[index] <= 0;
}

void EnemyPool::setRespawnCooldown(size_t index, float cooldown)
{
	m_respawnTimers[index] = cooldown;
}

void EnemyPool::respawnAll()
{
	for (size_t i = 0; i < m_enemies.size(); i++)
	{
		m_enemies[i]->respawn(m_mapInformationProvider.spawnPoints()[i].position());
		setRespawnCooldown(i, RESPAWN_DELAY);
	}
}
