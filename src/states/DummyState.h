#ifndef DUMMYSTATE_H
#define DUMMYSTATE_H

#include "IState.h"
#include "Map.h"
#include "Player.h"
#include "SpriteSheetMapper.h"
#include "InputMapping.h"

class Settings;

class DummyState : public IState
{
	public:
		DummyState(Settings &settings, const sf::Texture& spriteSheet);

		void keyPressed(const sf::Event &event) override;
		void keyReleased(const sf::Event &event) override;

		void update(float delta) override;

	protected:
		void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

	private:
		Settings &m_settings;

		SpriteSheetMapper m_spriteSheetMapper;
		Player m_player;
		Map m_map;
};

#endif // DUMMYSTATE_H
