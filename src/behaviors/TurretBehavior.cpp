#include "TurretBehavior.h"
#include "Utility.h"
#include "SpriteSheetMapper.h"
#include "IBehaviorControllable.h"

TurretBehavior::TurretBehavior()
{

}

void TurretBehavior::update(float delta)
{
	UNUSED(delta);
}

void TurretBehavior::invokeOnActor(IBehaviorControllable &actor)
{
	UNUSED(actor);
}

sf::Sprite TurretBehavior::currentSpriteForActor(const SpriteSheetMapper &spriteSheetMapper, const IBehaviorControllable &actor) const
{
	sf::Sprite sprite = spriteSheetMapper.get(SpriteId::TurretLookingLeft, 0);
	sprite.setPosition(actor.position());

	return sprite;
}

sf::FloatRect TurretBehavior::currentCollisionBoxForActor(const IBehaviorControllable &actor) const
{
	UNUSED(actor);

	return sf::FloatRect(8, 21, 15, 11);
}
