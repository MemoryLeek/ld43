#ifndef PLAYER_H
#define PLAYER_H

#include "IUpdatable.h"

class Player : public IUpdatable
{
	public:
		Player();

		int x() const;
		void setX(int x);

		int y() const;
		void setY(int y);

		int direction() const;

		void setVelocity(int velocity);
		void update(float delta);

	private:
		int m_x;
		int m_y;
		int m_velocity;
		int m_direction;
};

#endif // PLAYER_H
