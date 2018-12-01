#include "Enemy.h"
#include "SpriteSheetMapper.h"

#include "EnemyDrawable.h"

EnemyDrawable::EnemyDrawable(const Enemy& enemy, const SpriteSheetMapper& spriteSheetMapper)
	: m_enemy(enemy)
	, m_spriteSheetMapper(spriteSheetMapper)
	, m_elapsed(0)
{
}

void EnemyDrawable::update(float delta)
{
	m_elapsed += delta;
}

void EnemyDrawable::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	const int spriteIndex = (int)(m_elapsed * 5) % 3;
	auto sprite = m_spriteSheetMapper.get(SpriteId::Blob, spriteIndex);
	sprite.setPosition(m_enemy.position());

	target.draw(sprite);
}
