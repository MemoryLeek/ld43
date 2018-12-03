#include <iostream>

#include "Player.h"
#include "IBehaviorControllable.h"
#include "SpriteSheetMapper.h"
#include "ActorMovementHandler.h"
#include "BlobBehavior.h"
#include "Enemy.h"

const sf::FloatRect COLLISION_BOX = sf::FloatRect(6, 23, 20, 9);
const sf::FloatRect COLLISION_BOX_AIR = sf::FloatRect(6, 16, 20, 16);

BlobBehavior::BlobBehavior(Player& player, const IMapInformationProvider &mapInformationProvider)
	: m_player(player)
	, m_mapInformationProvider(mapInformationProvider)
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
	const auto playerPosition = m_player.position();
	const auto actorPosition = actor.position();

	if (ActorMovementHandler::isOnGround((Enemy &)actor, m_mapInformationProvider))
	{
		actor.move(Direction::Left, 0.0f);
	}

	// Blob likey jumpey
	if (m_jumpCoolDowns[&actor] <= 0)
	{
		if (abs(playerPosition.x - actorPosition.x) > 200 ||
			abs(playerPosition.y - actorPosition.y) > 200)
		{
			return;
		}

		if (playerPosition.x < actorPosition.x)
		{
			actor.move(Direction::Left, 0.25f);
		}
		else
		{
			actor.move(Direction::Right, 0.25f);
		}

		actor.jump(2.f);

		m_jumpCoolDowns[&actor] = 1.0f;
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
	if (actor.velocity().y >= 0)
	{
		return COLLISION_BOX;
	}

	return COLLISION_BOX_AIR;
}

int BlobBehavior::health() const
{
	return 1;
}
