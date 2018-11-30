#include "PlayerDrawable.h"
#include "SpriteSheetMapper.h"
#include "Utility.h"
#include "Player.h"

PlayerDrawable::PlayerDrawable(const Player &player, const SpriteSheetMapper &spriteSheetMapper)
	: m_player(player)
	, m_spriteSheetMapper(spriteSheetMapper)
{
}

sf::Sprite PlayerDrawable::spriteForDirection(int direction) const
{
	const int index = (m_player.x() * 10) % 3;

	if (direction == -1)
	{
		return m_spriteSheetMapper.get(SpriteId::PlayerRunningLeft, index);
	}

	if (direction == 1)
	{
		return m_spriteSheetMapper.get(SpriteId::PlayerRunningRight, index);
	}

	return m_spriteSheetMapper.get(SpriteId::PlayerRunningRight, 0);
}

void PlayerDrawable::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	UNUSED(states);

	const int direction = m_player.direction();

	sf::Sprite sprite = spriteForDirection(direction);
	sprite.setPosition(m_player.x(), m_player.y());

	target.draw(sprite);
}
