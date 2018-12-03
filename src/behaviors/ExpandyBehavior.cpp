#include <iostream>
#include <algorithm>

#include "ExpandyBehavior.h"
#include "Utility.h"
#include "SpriteSheetMapper.h"
#include "IBehaviorControllable.h"
#include "Player.h"

ExpandyBehavior::ExpandyBehavior(Player &player)
	: m_player(player)
{
}

void ExpandyBehavior::update(float delta)
{
	UNUSED(delta);
}

void ExpandyBehavior::invokeOnActor(IBehaviorControllable &actor)
{
	const auto playerBox = sf::FloatRect(m_player.position().x + m_player.collisionBox().left
		, m_player.position().y + m_player.collisionBox().top
		, m_player.collisionBox().width
		, m_player.collisionBox().height);

	const auto collisionBox = currentCollisionBoxForActor(actor);
	const auto actorBox = sf::FloatRect(actor.position().x + collisionBox.left
		, actor.position().y + collisionBox.top
		, collisionBox.width
		, collisionBox.height);

	if (actorBox.intersects(playerBox))
	{
		m_player.damage(DECAY / 2);
	}
}

int ExpandyBehavior::getSpriteIndex(const IBehaviorControllable &actor) const
{
	const sf::Vector2f &position = actor.position();

	return Utility::clamp<int>(17 - abs(position.x - m_player.x()) / 5, 0, 17);
}

int ExpandyBehavior::health() const
{
	return 1;
}

sf::Sprite ExpandyBehavior::currentSpriteForActor(const SpriteSheetMapper &spriteSheetMapper, const IBehaviorControllable &actor) const
{
	sf::Sprite sprite = spriteSheetMapper.get(SpriteId::Expandy, getSpriteIndex(actor));
	sprite.setPosition(actor.position());

	return sprite;
}

sf::FloatRect ExpandyBehavior::currentCollisionBoxForActor(const IBehaviorControllable &actor) const
{
	const int index = getSpriteIndex(actor);

	return sf::FloatRect(9, 20 - index, 14, 9 + index);
}
