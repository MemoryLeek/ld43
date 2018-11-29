#ifndef DUMMYSTATE_H
#define DUMMYSTATE_H

#include "IState.h"

class DummyState : public IState
{
	public:
		void keyPressed(const sf::Event::KeyEvent &event) override;
		void keyReleased(const sf::Event::KeyEvent &event) override;

		void update(long delta) override;

	protected:
		void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};

#endif // DUMMYSTATE_H
