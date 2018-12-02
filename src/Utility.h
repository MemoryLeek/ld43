#ifndef UTILITY_H
#define UTILITY_H

#include <SFML/System/Vector2.hpp>

constexpr int RES_X = 1280;
constexpr int RES_Y = 720;
constexpr int TILE_SIZE = 32;

constexpr float RENDERSCALE = 2;
constexpr float GRAVITY = 10;
constexpr float DECAY = 2000.0f;
constexpr float DAMAGE = 2000.0f;

template<typename T>
void UNUSED(T &)
{
}

namespace Utility
{
	template<typename T>
	T lerp(T start, T end, float value)
	{
		return start + (end - start) * value;
	}

	inline sf::Vector2u tilePosition(unsigned int px, unsigned int py)
	{
		return sf::Vector2u((px + TILE_SIZE / 2) / TILE_SIZE, (py + TILE_SIZE - 1) / TILE_SIZE);
	}

	inline sf::Vector2u correctTilePosition(unsigned int px, unsigned int py)
	{
		return sf::Vector2u(px / TILE_SIZE, py/ TILE_SIZE);
	}
}

enum class Direction
{
	Left,
	Right,
	Up,
	Down,
};

#endif // UTILITY_H
