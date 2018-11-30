#ifndef STATEHANDLER_H
#define STATEHANDLER_H

#include <SFML/Graphics.hpp>

class IState;

class StateHandler : public sf::Drawable
{
	public:
		StateHandler(const sf::Texture& spriteSheet);

		void keyPressed(const sf::Event::KeyEvent &event);
		void keyReleased(const sf::Event::KeyEvent &event);

		void update(float delta);

		void changeState(IState *next, float duration);
		void changeState(IState *next);

	protected:
		void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

	private:
		IState *m_state;
};

#endif // STATEHANDLER_H
