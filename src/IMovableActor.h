#ifndef IMOVABLEACTOR_H
#define IMOVABLEACTOR_H

#include <SFML/System/Vector2.hpp>

class IMovableActor
{
	public:
		virtual sf::Vector2f position() const = 0;
		virtual void setPosition(sf::Vector2f position) = 0;

		virtual sf::Vector2f velocity() const = 0;
		virtual void setVelocity(sf::Vector2f velocity) = 0;

		virtual float mass() const = 0;
};

#endif // IMOVABLEACTOR_H
