#ifndef BULLET_H
#define BULLET_H

#include <SFML/Graphics.hpp>

#include "Utility.h"

struct Bullet
{
	sf::Vector2u position;
	Direction direction;
};

#endif // BULLET_H
