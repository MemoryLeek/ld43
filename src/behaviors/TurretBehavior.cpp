#include "TurretBehavior.h"
#include "Utility.h"
#include "SpriteSheetMapper.h"
#include "IBehaviorControllable.h"

TurretBehavior::TurretBehavior(int spawnDirection)
	: m_spawnDirection(spawnDirection)
{
}

void TurretBehavior::update(float delta)
{
	for (auto &state : m_states)
	{
		if ((state.second.elapsed += delta) > 3)
		{
			state.second.direction = !state.second.direction;
			state.second.elapsed = 0;
		}
	}
}

void TurretBehavior::invokeOnActor(IBehaviorControllable &actor)
{
	const auto &iterator = m_states.find(&actor);

	if (iterator == m_states.end())
	{
		m_states[&actor].direction = m_spawnDirection;
	}
}

sf::Sprite TurretBehavior::currentSpriteForActor(const SpriteSheetMapper &spriteSheetMapper, const IBehaviorControllable &actor) const
{
	const auto &state = getTurretState(actor);
	const auto spriteId = getSprite(state);
	const auto index = getSpriteIndex(state);

	sf::Sprite sprite = spriteSheetMapper.get(spriteId, index);
	sprite.setPosition(actor.position());

	return sprite;
}

sf::FloatRect TurretBehavior::currentCollisionBoxForActor(const IBehaviorControllable &actor) const
{
	const auto &state = getTurretState(actor);
	const auto index = getSpriteIndex(state);

	return sf::FloatRect(8, 21 - index, 15, 11 + index);
}

TurretState TurretBehavior::getTurretState(const IBehaviorControllable &actor) const
{
	static TurretState invalid;

	const auto &iterator = m_states.find(&actor);

	if (iterator == m_states.end())
	{
		return invalid;
	}

	return (*iterator).second;
}

SpriteId TurretBehavior::getSprite(const TurretState &state) const
{
	if (state.direction == 0)
	{
		return SpriteId::TurretLookingLeft;
	}

	return SpriteId::TurretLookingRight;
}

int TurretBehavior::getSpriteIndex(const TurretState &state) const
{
	const float start = std::max(0.0f, (0.5f - state.elapsed) / 0.5f);
	const float end = std::max(0.0f, (state.elapsed - 2.5f) / 0.5f);

	return (start + end) * 6;
}
