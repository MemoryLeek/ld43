#include "Settings.h"

InputMapping &Settings::inputMapping()
{
	return m_inputMapping;
}

BinaryStream &operator >>(BinaryStream &stream, Settings &settings)
{
	stream >> settings.m_inputMapping;

	return stream;
}

BinaryStream &operator <<(BinaryStream &stream, const Settings &settings)
{
	stream << settings.m_inputMapping;

	return stream;
}
