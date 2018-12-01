#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/System/Vector2.hpp>

#include "Utility.h"

#include "IUpdatable.h"

class ICollisionInformationProvider;

class Player : public IUpdatable
{
	public:
		Player(const ICollisionInformationProvider& collisionInformationProvider);

		int x() const;
		void setX(int x);

		int y() const;
		void setY(int y);

		int direction() const;
		const sf::Vector2f& velocity() const;

		void moveLeft();
		void moveRight();
		void stopMoving();

		void jump();
		void stopJumping();

		void update(float delta);

	private:
		sf::Vector2i tilePosition() const;

		const ICollisionInformationProvider& m_collisionInformationProvider;

		sf::Vector2f m_position;
		sf::Vector2f m_velocity;
		float m_mass;
		int m_direction;
};

#endif // PLAYER_H
