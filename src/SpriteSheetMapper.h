#ifndef SPRITESHEETMAPPER_H
#define SPRITESHEETMAPPER_H

#include <SFML/Graphics.hpp>

enum class SpriteId
{
	Player,
	PlayerRunningLeft,
	PlayerRunningRight,
};

class SpriteSheetMapper
{
	const int TILE_SIZE = 32;

	public:
		SpriteSheetMapper();

		sf::Sprite get(SpriteId spriteId) const;

	private:
		sf::Texture m_spriteSheet;
};

#endif // SPRITESHEETMAPPER_H
