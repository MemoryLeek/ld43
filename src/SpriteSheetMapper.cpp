#include <unordered_map>

#include "SpriteSheetMapper.h"

SpriteSheetMapper::SpriteSheetMapper(const sf::Texture& spriteSheet)
	: m_spriteSheet(spriteSheet)
{
}

sf::Sprite SpriteSheetMapper::get(SpriteId spriteId, int index) const
{
	static std::unordered_map<SpriteId, sf::Vector2u> mapping =
	{
		{ SpriteId::Player, sf::Vector2u(0, 0) },
		{ SpriteId::PlayerRunningLeft, sf::Vector2u(14, 2) },
		{ SpriteId::PlayerRunningRight, sf::Vector2u(14, 1) },
	};

	const sf::Vector2u &coordinate = mapping.at(spriteId);
	const sf::IntRect rect((coordinate.x + index) * TILE_SIZE, coordinate.y * TILE_SIZE, TILE_SIZE, TILE_SIZE);

	return sf::Sprite(m_spriteSheet, rect);
}
