#ifndef INPUTMAPPING_H
#define INPUTMAPPING_H

#include <SFML/Window/Event.hpp>

#include "BinaryStream.h"
#include "KeyMapping.h"

class InputMapping
{
	public:
		KeyMapping &up();
		KeyMapping &down();
		KeyMapping &left();
		KeyMapping &right();
		KeyMapping &jump();
		KeyMapping &shoot();

		KeyMapping *find(const sf::Event &event);

	private:
		friend BinaryStream &operator >>(BinaryStream &stream, InputMapping &inputMapping);
		friend BinaryStream &operator <<(BinaryStream &stream, const InputMapping &inputMapping);

		KeyMapping m_up;
		KeyMapping m_down;
		KeyMapping m_left;
		KeyMapping m_right;
		KeyMapping m_jump;
		KeyMapping m_shoot;
};

#endif // INPUTMAPPING_H
