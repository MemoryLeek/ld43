#ifndef BLOBBEHAVIOR_H
#define BLOBBEHAVIOR_H

#include <map>

#include "IEnemyBehavior.h"

class IBehaviorControllable;
class Player;

class BlobBehavior : public IEnemyBehavior
{
	public:
		BlobBehavior(const Player& player);

		void update(float delta) override;

		void invokeOnActor(IBehaviorControllable& actor) override;

	private:
		const Player& m_player;

		std::map<IBehaviorControllable*, float> m_jumpCoolDowns;
};

#endif // BLOBBEHAVIOR_H
