#include "EnemyFactory.h"

EnemyFactory::EnemyFactory(const Player& player, const IMapInformationProvider& mapInformationProvider)
	: m_player(player)
	, m_mapInformationProvider(mapInformationProvider)
	, m_blobBehavior(m_player)
{
}

Enemy EnemyFactory::createInstance(SpawnType type)
{
	switch (type)
	{
		case SpawnType::Blob:
			return Enemy(m_blobBehavior, m_mapInformationProvider);
		case SpawnType::Expandy:
			return Enemy(m_expandyBehavior, m_mapInformationProvider);
		case SpawnType::Turret:
			return Enemy(m_turretBehavior, m_mapInformationProvider);
		default:
			return Enemy(m_dummyBehavior, m_mapInformationProvider);
	}
}

void EnemyFactory::update(float delta)
{
	m_blobBehavior.update(delta);
	m_dummyBehavior.update(delta);
}
