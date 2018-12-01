#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/System/Vector2.hpp>

#include "IUpdatable.h"
#include "IMovableActor.h"

class IEnemyBehavior;
class IMapInformationProvider;

class Enemy : public IUpdatable, public IMovableActor
{
	public:
		Enemy(const IEnemyBehavior& behavior, const IMapInformationProvider& m_mapInformationProvider);

		void update(float delta) override;

		sf::Vector2f position() const override;
		void setPosition(sf::Vector2f position) override;

		sf::Vector2f velocity() const override;
		void setVelocity(sf::Vector2f velocity) override;

		float mass() const override;

	private:
		const IEnemyBehavior& m_behavior;
		const IMapInformationProvider& m_mapInformationProvider;

		sf::Vector2f m_position;
		sf::Vector2f m_velocity;
};

#endif // ENEMY_H
