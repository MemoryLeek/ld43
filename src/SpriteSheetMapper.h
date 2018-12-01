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
		SpriteSheetMapper(const sf::Texture& spriteSheet);

		sf::Sprite get(SpriteId spriteId, int index) const;

	private:
		const sf::Texture& m_spriteSheet;
};

#endif // SPRITESHEETMAPPER_H