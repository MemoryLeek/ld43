#include <iostream>

#include "Player.h"
#include "IBehaviorControllable.h"
#include "SpriteSheetMapper.h"

#include "BlobBehavior.h"

BlobBehavior::BlobBehavior(const Player& player)
	: m_player(player)
	, m_elapsed(0)
{
}

void BlobBehavior::update(float delta)
{
	for (auto& cooldown : m_jumpCoolDowns)
	{
		if (cooldown.second > 0)
		{
			cooldown.second -= delta;
		}
	}

	m_elapsed += delta;
}

void BlobBehavior::invokeOnActor(IBehaviorControllable& actor)
{
	if (m_player.position().x < actor.position().x)
	{
		actor.move(Direction::Left, 0.15f);
	}
	else
	{
		actor.move(Direction::Right, 0.15f);
	}

	// Blob likey jumpey
	if (m_jumpCoolDowns[&actor] <= 0)
	{
		actor.jump(1.f);
		m_jumpCoolDowns[&actor] = .8f;
	}
}

sf::Sprite BlobBehavior::currentSpriteForActor(const SpriteSheetMapper& spriteSheetMapper, const IBehaviorControllable& actor) const
{
	auto sprite = spriteSheetMapper.get(SpriteId::Blob, 0);
	sprite.setPosition(actor.position());
	return sprite;
}

sf::FloatRect BlobBehavior::currentCollisionBoxForActor(const IBehaviorControllable& actor) const
{
	UNUSED(actor);

	return sf::FloatRect(6, 23, 20, 9);
}
