#include "SettingsProvider.h"
#include "BinaryStream.h"

SettingsProvider::SettingsProvider()
{

}

Settings SettingsProvider::load() const
{
	std::fstream file(FILENAME, std::ios::in | std::ios::binary);

	if (file.is_open())
	{
		Settings settings;
		BinaryStream stream(file);
		stream >> settings;

		return settings;
	}
	else
	{
		return m_fallbackProvider.load();
	}
}

void SettingsProvider::save(const Settings &settings)
{
	std::fstream file(FILENAME, std::ios::out | std::ios::binary);

	BinaryStream stream(file);
	stream << settings;
}
