#ifndef SETTINGS_H
#define SETTINGS_H

#include "InputMapping.h"
#include "BinaryStream.h"

class Settings
{
	public:
		InputMapping &inputMapping();

	private:
		friend BinaryStream &operator >>(BinaryStream &stream, Settings &settings);
		friend BinaryStream &operator <<(BinaryStream &stream, const Settings &settings);

		InputMapping m_inputMapping;
};

#endif // SETTINGS_H
