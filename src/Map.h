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

#include "ICollisionInformationProvider.h"

class Map : public sf::Drawable, public ICollisionInformationProvider
{
	public:
		Map(const std::string& path, const sf::Texture& spriteSheet);

		const sf::Vector2f& offset() const;
		void setOffset(const sf::Vector2f& offset);
		void moveOffset(const sf::Vector2f& delta);

		bool isCollidable(const unsigned int tx, const unsigned int ty) const override;

	protected:
		void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	private:
		void loadLayer(const tmx::Layer* layer);
		void loadTileLayer(const tmx::TileLayer* layer);

		static size_t calculateActiveTileCount(const tmx::TileLayer* layer);
		static std::array<sf::Vector2f, 6> calculateTilePosition(const unsigned int tx, const unsigned int ty, const tmx::Vector2u tileSize);
		static std::array<sf::Vector2f, 6> calculateTexturePosition(const unsigned int tid, const tmx::Tileset& tileset);
		static std::array<sf::Vector2f, 6> convertRectToTriangleVertices(const sf::Rect<float>& rect);

		tmx::Map m_map;
		const sf::Texture& m_spriteSheet;
		std::vector<std::unique_ptr<sf::VertexBuffer>> m_vertexBuffers;
		std::vector<uint8_t> m_collidables;

		sf::Vector2f m_offset;
};

#endif // MAP_H
