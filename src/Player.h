#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/System/Vector2.hpp>

#include "Utility.h"

#include "IUpdatable.h"

class IMapInformationProvider;

class Player : public IUpdatable
{
	public:
		Player(const IMapInformationProvider& collisionInformationProvider);

		int x() const;
		void setX(int x);

		int y() const;
		void setY(int y);

		int decay() const;

		float mass() const;

		sf::Vector2f velocity() const;
		sf::Vector2i direction() const;

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

		void update(float delta);

	private:
		sf::Vector2u tilePosition() const;

		const IMapInformationProvider& m_collisionInformationProvider;

		sf::Vector2f m_position;
		sf::Vector2f m_velocity;
		sf::Vector2u m_lastCheckpointTilePosition;
		sf::Vector2i m_direction;

		int m_decay;
};

#endif // PLAYER_H
