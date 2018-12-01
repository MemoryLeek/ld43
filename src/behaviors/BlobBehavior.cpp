#include <iostream>

#include "Player.h"
#include "IBehaviorControllable.h"

#include "BlobBehavior.h"

BlobBehavior::BlobBehavior(const Player& player)
	: m_player(player)
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
