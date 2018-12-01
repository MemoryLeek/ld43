#include "InputMapping.h"

KeyMapping &InputMapping::left()
{
	return m_left;
}

KeyMapping &InputMapping::right()
{
	return m_right;
}

KeyMapping *InputMapping::find(const sf::Event &event)
{
	static KeyMapping *mappings[]
	{
		&m_left,
		&m_right,
	};

	for (KeyMapping *mapping : mappings)
	{
		const int key = mapping->key();
		const int joystickButton = mapping->joystickButton();

		switch (event.type)
		{
			case sf::Event::JoystickButtonPressed:
			case sf::Event::JoystickButtonReleased:
			{
				if (joystickButton == (int)event.joystickButton.button)
				{
					return mapping;
				}

				break;
			}

			case sf::Event::KeyPressed:
			case sf::Event::KeyReleased:
			{
				if (key == event.key.code)
				{
					return mapping;
				}

				break;
			}

			default:
			{
				break;
			}
		}
	}

	return nullptr;
}

BinaryStream &operator >>(BinaryStream &stream, InputMapping &inputMapping)
{
	stream >> inputMapping.m_left;
	stream >> inputMapping.m_right;

	return stream;
}

BinaryStream &operator <<(BinaryStream &stream, const InputMapping &inputMapping)
{
	stream << inputMapping.m_left;
	stream << inputMapping.m_right;

	return stream;
}
