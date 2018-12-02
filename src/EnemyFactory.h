#ifndef ENEMYFACTORY_H
#define ENEMYFACTORY_H

#include "Enemy.h"
#include "SpawnPoint.h"
#include "IUpdatable.h"

#include "behaviors/BlobBehavior.h"
#include "behaviors/StationaryEnemyBehavior.h"
#include "behaviors/ExpandyBehavior.h"
#include "behaviors/TurretBehavior.h"

class EnemyFactory : public IUpdatable
{
	public:
		EnemyFactory(Player& player, const IMapInformationProvider& mapInformationProvider);

		Enemy* createInstance(SpawnType type);

		void update(float delta) override;

	private:
		Player& m_player;
		const IMapInformationProvider& m_mapInformationProvider;

		BlobBehavior m_blobBehavior;
		StationaryEnemyBehavior m_dummyBehavior;
		ExpandyBehavior m_expandyBehavior;
		TurretBehavior m_turretLeftBehavior;
		TurretBehavior m_turretRightBehavior;
};

#endif // ENEMYFACTORY_H
