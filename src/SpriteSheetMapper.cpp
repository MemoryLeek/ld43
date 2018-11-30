#include <unordered_map>

#include "SpriteSheetMapper.h"

SpriteSheetMapper::SpriteSheetMapper()
{
	m_spriteSheet.loadFromFile("resources/spritesheet.png");
}

sf::Sprite SpriteSheetMapper::get(SpriteId spriteId) const
{
	static std::unordered_map<SpriteId, sf::Vector2u> mapping =
	{
		{ SpriteId::Player, sf::Vector2u(0, 0) },
		{ SpriteId::PlayerRunningLeft, sf::Vector2u(1, 0) },
		{ SpriteId::PlayerRunningRight, sf::Vector2u(2, 0) },
	};

	const sf::Vector2u &index = mapping.at(spriteId);
	const sf::IntRect rect(index.x * TILE_SIZE, index.y * TILE_SIZE, TILE_SIZE, TILE_SIZE);

	return sf::Sprite(m_spriteSheet, rect);
}
