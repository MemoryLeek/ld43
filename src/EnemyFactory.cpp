#include "EnemyFactory.h"

EnemyFactory::EnemyFactory(Player& player, const IMapInformationProvider& mapInformationProvider, ProjectileHitDetector& projectileHitDetector)
	: m_player(player)
	, m_mapInformationProvider(mapInformationProvider)
	, m_blobBehavior(m_player, mapInformationProvider)
	, m_expandyBehavior(m_player)
	, m_turretLeftBehavior(0, projectileHitDetector, m_mapInformationProvider, m_player)
	, m_turretRightBehavior(1, projectileHitDetector, m_mapInformationProvider, m_player)
	, m_shakeyBehavior(mapInformationProvider, projectileHitDetector, m_player)
{
}

Enemy* EnemyFactory::createInstance(SpawnType type)
{
	switch (type)
	{
		case SpawnType::Blob:
			return new Enemy(m_blobBehavior, m_mapInformationProvider, m_player);
		case SpawnType::Expandy:
			return new Enemy(m_expandyBehavior, m_mapInformationProvider, m_player);
		case SpawnType::TurretLeft:
			return new Enemy(m_turretLeftBehavior, m_mapInformationProvider, m_player);
		case SpawnType::TurretRight:
			return new Enemy(m_turretRightBehavior, m_mapInformationProvider, m_player);
		case SpawnType::Shakey:
			return new Enemy(m_shakeyBehavior, m_mapInformationProvider, m_player);
		default:
			return new Enemy(m_dummyBehavior, m_mapInformationProvider, m_player);
	}
}

void EnemyFactory::update(float delta)
{
	m_blobBehavior.update(delta);
	m_dummyBehavior.update(delta);
	m_expandyBehavior.update(delta);
	m_turretLeftBehavior.update(delta);
	m_turretRightBehavior.update(delta);
	m_shakeyBehavior.update(delta);
}
