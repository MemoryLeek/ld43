#include "ExpandyBehavior.h"
#include "Utility.h"
#include "SpriteSheetMapper.h"
#include "IBehaviorControllable.h"

ExpandyBehavior::ExpandyBehavior()
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

sf::Sprite ExpandyBehavior::currentSpriteForActor(const SpriteSheetMapper &spriteSheetMapper, const IBehaviorControllable &actor) const
{
	sf::Sprite sprite = spriteSheetMapper.get(SpriteId::Expandy, 0);
	sprite.setPosition(actor.position());

	return sprite;
}

sf::FloatRect ExpandyBehavior::currentCollisionBoxForActor(const IBehaviorControllable &actor) const
{
	UNUSED(actor);

	return sf::FloatRect(9, 20, 14, 9);
}
