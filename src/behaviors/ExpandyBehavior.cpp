#include <iostream>
#include <algorithm>

#include "ExpandyBehavior.h"
#include "Utility.h"
#include "SpriteSheetMapper.h"
#include "IBehaviorControllable.h"
#include "Player.h"

ExpandyBehavior::ExpandyBehavior(const Player &player)
	: m_player(player)
{
}

void ExpandyBehavior::update(float delta)
{
	UNUSED(delta);
}

void ExpandyBehavior::invokeOnActor(IBehaviorControllable &actor)
{
	UNUSED(actor);
}

int ExpandyBehavior::getSpriteIndex(const IBehaviorControllable &actor) const
{
	const sf::Vector2f &position = actor.position();

	return Utility::clamp<int>(17 - abs(position.x - m_player.x()) / 5, 0, 17);
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
