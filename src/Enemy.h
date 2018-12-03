#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/System/Vector2.hpp>

#include "IUpdatable.h"
#include "IMovableActor.h"
#include "Player.h"

#include "behaviors/IBehaviorControllable.h"

class IEnemyBehavior;
class IMapInformationProvider;

class Enemy : public IUpdatable, public IMovableActor, public IBehaviorControllable
{
	public:
		Enemy(IEnemyBehavior& behavior, const IMapInformationProvider& m_mapInformationProvider, const Player &player);

		IEnemyBehavior& behavior() const;

		void kill(Direction bulletImpactDirection);
		bool isDead() const;
		void respawn(const sf::Vector2f& position);

		float deathTimer() const;
		float spawnTimer() const;

		void update(float delta) override;

		sf::FloatRect collisionBox() const override;

		sf::Vector2f position() const override;
		void setPosition(sf::Vector2f position) override;

		sf::Vector2f velocity() const override;
		void setVelocity(sf::Vector2f velocity) override;

		float mass() const override;

		void jump(float velocity) override;
		void move(Direction direction, float velocity) override;

	private:
		IEnemyBehavior& m_behavior;
		const IMapInformationProvider& m_mapInformationProvider;
		const Player &m_player;

		float m_deathTimer;
		float m_spawnTimer;

		int m_health;

		Direction m_bulletImpactDirection;

		sf::Vector2f m_position;
		sf::Vector2f m_velocity;
};

#endif // ENEMY_H
