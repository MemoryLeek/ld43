#ifndef MAP_H
#define MAP_H

#include <string>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/VertexBuffer.hpp>

#include <tmxlite/Map.hpp>
#include <tmxlite/Tileset.hpp>
#include <tmxlite/TileLayer.hpp>

#include "IMapInformationProvider.h"
#include "SpawnPoint.h"

class Map : public sf::Drawable, public IMapInformationProvider
{
	public:
		Map(const std::string& path, const sf::Texture& spriteSheet);

		bool isCollidable(const unsigned int tx, const unsigned int ty) const override;
		bool isCheckpoint(const unsigned int tx, const unsigned int ty) const override;
		bool intersectsKillzone(const sf::FloatRect& collisionBox) const override;

		std::vector<SpawnPoint> spawnPoints() const override;

	protected:
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	private:
		void loadLayer(const tmx::Layer* layer);
		void loadTileLayer(const tmx::TileLayer* layer);
		void loadObjectLayer(const tmx::ObjectGroup* layer);

		static size_t calculateActiveTileCount(const tmx::TileLayer* layer);
		static std::array<sf::Vector2f, 6> calculateTilePosition(const unsigned int tx, const unsigned int ty, const tmx::Vector2u tileSize);
		static std::array<sf::Vector2f, 6> calculateTexturePosition(const unsigned int tid, const tmx::Tileset& tileset);
		static std::array<sf::Vector2f, 6> convertRectToTriangleVertices(const sf::Rect<float>& rect);

		tmx::Map m_map;
		const sf::Texture& m_spriteSheet;
		std::vector<std::unique_ptr<sf::VertexBuffer>> m_vertexBuffers;
		std::vector<uint8_t> m_collidables;
		std::vector<sf::Vector2u> m_checkpoints;
		std::vector<SpawnPoint> m_spawnPoints;
		std::vector<sf::FloatRect> m_killZones;
};

#endif // MAP_H
