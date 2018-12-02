#include "EnemyFactory.h"

EnemyFactory::EnemyFactory(const Player& player, const IMapInformationProvider& mapInformationProvider)
	: m_player(player)
	, m_mapInformationProvider(mapInformationProvider)
	, m_blobBehavior(m_player)
	, m_expandyBehavior(m_player)
{
}

Enemy* EnemyFactory::createInstance(SpawnType type)
{
	switch (type)
	{
		case SpawnType::Blob:
			return new Enemy(m_blobBehavior, m_mapInformationProvider);
		case SpawnType::Expandy:
			return new Enemy(m_expandyBehavior, m_mapInformationProvider);
		case SpawnType::Turret:
			return new Enemy(m_turretBehavior, m_mapInformationProvider);
		default:
			return new Enemy(m_dummyBehavior, m_mapInformationProvider);
	}
}

void EnemyFactory::update(float delta)
{
	m_blobBehavior.update(delta);
	m_dummyBehavior.update(delta);
	m_expandyBehavior.update(delta);
	m_turretBehavior.update(delta);
}
