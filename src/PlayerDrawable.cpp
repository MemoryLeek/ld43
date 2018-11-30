#include "PlayerDrawable.h"
#include "SpriteSheetMapper.h"
#include "Utility.h"
#include "Player.h"

PlayerDrawable::PlayerDrawable(const Player &player, const SpriteSheetMapper &spriteSheetMapper)
	: m_player(player)
	, m_spriteSheetMapper(spriteSheetMapper)
{
}

SpriteId spriteForDirection(int direction)
{
	if (direction == -1)
	{
		return SpriteId::PlayerRunningLeft;
	}

	if (direction == 1)
	{
		return SpriteId::PlayerRunningRight;
	}

	return SpriteId::Player;
}

void PlayerDrawable::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	UNUSED(states);

	const int direction = m_player.direction();

	const SpriteId spriteId = spriteForDirection(direction);

	sf::Sprite sprite = m_spriteSheetMapper.get(spriteId);
	sprite.setPosition(m_player.x(), m_player.y());

	target.draw(sprite);
}
