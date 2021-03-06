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
		{ SpriteId::PlayerIdleLeft, sf::Vector2u(0, 4) },
		{ SpriteId::PlayerIdleLeftShooting, sf::Vector2u(1, 4) },
		{ SpriteId::PlayerIdleRight, sf::Vector2u(0, 1) },
		{ SpriteId::PlayerIdleRightShooting, sf::Vector2u(1, 1) },
		{ SpriteId::PlayerRunningLeft, sf::Vector2u(0, 5) },
		{ SpriteId::PlayerRunningLeftShooting, sf::Vector2u(4, 5) },
		{ SpriteId::PlayerRunningRight, sf::Vector2u(0, 2) },
		{ SpriteId::PlayerRunningRightShooting, sf::Vector2u(4, 2) },
		{ SpriteId::PlayerJumpingLeft, sf::Vector2u(0, 6) },
		{ SpriteId::PlayerJumpingRight, sf::Vector2u(0, 3) },
		{ SpriteId::PlayerLookingUp, sf::Vector2u(6, 1) },
		{ SpriteId::PlayerLookingDown, sf::Vector2u(7, 1) },
		{ SpriteId::Blob, sf::Vector2u(10, 4) },
		{ SpriteId::Expandy, sf::Vector2u(10, 7) },
		{ SpriteId::TurretLookingLeft, sf::Vector2u(10, 5) },
		{ SpriteId::TurretShootingLeft, sf::Vector2u(17, 5) },
		{ SpriteId::TurretLookingRight, sf::Vector2u(10, 6) },
		{ SpriteId::TurretShootingRight, sf::Vector2u(17, 6) },
		{ SpriteId::ShakeyWalkingLeft, sf::Vector2u(10, 11) },
		{ SpriteId::ShakeyPreparingLeft, sf::Vector2u(10, 12) },
		{ SpriteId::ShakeyChargingLeft, sf::Vector2u(10, 13) },
		{ SpriteId::ShakeyWalkingRight, sf::Vector2u(10, 8) },
		{ SpriteId::ShakeyPreparingRight, sf::Vector2u(10, 9) },
		{ SpriteId::ShakeyChargingRight, sf::Vector2u(10, 10) },
	};

	const sf::Vector2u &coordinate = mapping.at(spriteId);
	const sf::IntRect rect((coordinate.x + index) * TILE_SIZE, coordinate.y * TILE_SIZE, TILE_SIZE, TILE_SIZE);

	return sf::Sprite(m_spriteSheet, rect);
}
