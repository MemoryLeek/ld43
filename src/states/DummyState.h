#ifndef DUMMYSTATE_H
#define DUMMYSTATE_H

#include "IState.h"
#include "Player.h"
#include "SpriteSheetMapper.h"

class DummyState : public IState
{
	public:
		void keyPressed(const sf::Event::KeyEvent &event) override;
		void keyReleased(const sf::Event::KeyEvent &event) override;

		void update(float delta) override;

	protected:
		void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

	private:
		SpriteSheetMapper m_spriteSheetMapper;
		Player m_player;
};

#endif // DUMMYSTATE_H
