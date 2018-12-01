#ifndef INPUTMAPPING_H
#define INPUTMAPPING_H

#include <SFML/Window/Event.hpp>

#include "BinaryStream.h"
#include "KeyMapping.h"

class InputMapping
{
	public:
		KeyMapping &left();
		KeyMapping &right();

		KeyMapping *find(const sf::Event &event);

	private:
		friend BinaryStream &operator >>(BinaryStream &stream, InputMapping &inputMapping);
		friend BinaryStream &operator <<(BinaryStream &stream, const InputMapping &inputMapping);

		KeyMapping m_left;
		KeyMapping m_right;
};

#endif // INPUTMAPPING_H
