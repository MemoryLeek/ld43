#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/System/Vector2.hpp>

#include "Utility.h"

#include "IUpdatable.h"
#include "IMovableActor.h"

class IMapInformationProvider;
class ProjectileHitDetector;
class EnemyPool;

class Player : public IUpdatable, public IMovableActor
{
	public:
		Player(const IMapInformationProvider& collisionInformationProvider, const ProjectileHitDetector& projectileHitDetector, EnemyPool& enemyPool);

		int x() const;
		void setX(int x);

		int y() const;
		void setY(int y);

		int decay() const;
		void damage(float decay);

		bool isInvulnerable() const;
		bool isShooting() const;

		float mass() const override;

		sf::Vector2i direction() const;
		Direction shootDirection() const;

		sf::FloatRect collisionBox() const override;

		sf::Vector2f position() const override;
		void setPosition(sf::Vector2f position) override;

		sf::Vector2f velocity() const override;
		void setVelocity(sf::Vector2f velocity) override;

		void moveLeft();
		void moveRight();
		void stopMoving();

		void lookUp();
		void lookDown();
		void resetLook();

		void jump();
		void stopJumping();

		void shoot();
		void stopShooting();

		void update(float delta) override;

	private:
		void respawn();

		const IMapInformationProvider& m_collisionInformationProvider;
		const ProjectileHitDetector& m_projectileHitDetector;
		EnemyPool& m_enemyPool;

		sf::Vector2f m_position;
		sf::Vector2f m_velocity;
		sf::Vector2u m_lastCheckpointTilePosition;
		sf::Vector2i m_direction;

		int m_decay;

		float m_safeTimer;
		float m_shootTimer;
};

#endif // PLAYER_H
