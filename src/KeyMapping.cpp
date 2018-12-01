#include "KeyMapping.h"

KeyMapping::KeyMapping()
	: m_key(0)
	, m_joystickButton(0)
{
}

int KeyMapping::key() const
{
	return m_key;
}

void KeyMapping::setKey(int key)
{
	m_key = key;
}

int KeyMapping::joystickButton() const
{
	return m_joystickButton;
}

void KeyMapping::setJoystickButton(int joystickButton)
{
	m_joystickButton = joystickButton;
}

void KeyMapping::keyPressed() const
{
	m_onPress();
}

void KeyMapping::keyReleased() const
{
	m_onRelease();
}

BinaryStream &operator >>(BinaryStream &stream, KeyMapping &keyMapping)
{
	stream >> keyMapping.m_key;
	stream >> keyMapping.m_joystickButton;

	return stream;
}

BinaryStream &operator <<(BinaryStream &stream, const KeyMapping &keyMapping)
{
	stream << keyMapping.m_key;
	stream << keyMapping.m_joystickButton;

	return stream;
}
