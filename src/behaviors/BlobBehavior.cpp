#include <iostream>

#include "Player.h"
#include "IBehaviorControllable.h"
#include "SpriteSheetMapper.h"

#include "BlobBehavior.h"

const sf::FloatRect COLLISION_BOX = sf::FloatRect(6, 23, 20, 9);

BlobBehavior::BlobBehavior(Player& player)
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

	const auto playerBox = sf::FloatRect(m_player.position().x + m_player.collisionBox().left
		, m_player.position().y + m_player.collisionBox().top
		, m_player.collisionBox().width
		, m_player.collisionBox().height);

	const auto actorBox = sf::FloatRect(actor.position().x + COLLISION_BOX.left
		, actor.position().y + COLLISION_BOX.top
		, COLLISION_BOX.width
		, COLLISION_BOX.height);

	if (actorBox.intersects(playerBox))
	{
		m_player.damage(DECAY / 2);
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

	return COLLISION_BOX;
}
