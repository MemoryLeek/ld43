#ifndef CAMERA_H
#define CAMERA_H

#include <SFML/System/Vector2.hpp>

class Camera
{
	public:
		Camera();

		const sf::Vector2f& position() const;
		void setTarget(const sf::Vector2f& target);

		void update(float delta);

	private:
		sf::Vector2f m_position;
		sf::Vector2f m_target;
};

#endif // CAMERA_H
