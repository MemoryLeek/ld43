#include "Enemy.h"
#include "SpriteSheetMapper.h"

#include "EnemyDrawable.h"

EnemyDrawable::EnemyDrawable(const Enemy& enemy, const SpriteSheetMapper& spriteSheetMapper)
	: m_enemy(enemy)
	, m_spriteSheetMapper(spriteSheetMapper)
{
}

void EnemyDrawable::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	auto sprite = m_spriteSheetMapper.get(SpriteId::PlayerIdleLeft, 0);
	sprite.setPosition(m_enemy.position());

	target.draw(sprite);
}
