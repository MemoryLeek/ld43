#ifndef SHAKEYBEHAVIOR_H
#define SHAKEYBEHAVIOR_H

#include <array>
#include <map>

#include "IEnemyBehavior.h"
#include "SpriteSheetMapper.h"

struct ShakeyState
{
	ShakeyState()
		: direction(0)
		, state(0)
		, elapsed(0)
	{
	}

	int direction;
	int state;

	float elapsed;
};

class IMapInformationProvider;
class ProjectileHitDetector;

class ShakeyBehavior : public IEnemyBehavior
{
	public:
		ShakeyBehavior(const IMapInformationProvider &mapInformationProvider
			, const ProjectileHitDetector &projectileHitDetector
			);

		void update(float delta) override;
		void invokeOnActor(IBehaviorControllable &actor) override;

		sf::Sprite currentSpriteForActor(const SpriteSheetMapper &spriteSheetMapper, const IBehaviorControllable &actor) const override;
		sf::FloatRect currentCollisionBoxForActor(const IBehaviorControllable &actor) const override;

	private:
		std::array<sf::Vector2u, 2> getTilesToCheck(int direction, const sf::Vector2f &position) const;
		bool shouldChangeDirection(int direction, IBehaviorControllable &actor) const;
		ShakeyState getShakeyState(const IBehaviorControllable &actor) const;
		SpriteId getSpriteId(const ShakeyState &state) const;
		int getSpriteIndex(const ShakeyState &state) const;

		const IMapInformationProvider &m_mapInformationProvider;
		const ProjectileHitDetector &m_projectileHitDetector;

		std::map<const IBehaviorControllable*, ShakeyState> m_states;
};

#endif // SHAKEYBEHAVIOR_H
