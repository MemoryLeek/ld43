#ifndef LOGOSTATE_H
#define LOGOSTATE_H

#include "IState.h"

class StateHandler;

class LogoState : public IState
{
	public:
		LogoState(StateHandler &stateHandler);

		void keyPressed(const sf::Event::KeyEvent &event) override;
		void keyReleased(const sf::Event::KeyEvent &event) override;

		void update(long delta) override;

	protected:
		void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

	private:
		sf::Texture m_logo;

		StateHandler &m_stateHandler;

		long m_duration;
};


#endif // LOGOSTATE_H
