#include <iostream>
#include <vector>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Vertex.hpp>

#include <tmxlite/Map.hpp>
#include <tmxlite/TileLayer.hpp>

#include "Map.h"

Map::Map(const std::string& path, const sf::Texture& spriteSheet)
	: m_spriteSheet(spriteSheet)
{
	tmx::Map map;
	const auto mapSuccessfullyLoaded = map.load(path);
	assert(mapSuccessfullyLoaded);

	std::cout << "Loading map: " << path << std::endl;

	for (const auto& layer : map.getLayers())
	{
		loadLayer(layer.get(), map);
	}
}

const sf::Vector2f& Map::offset() const
{
	return m_offset;
}

void Map::setOffset(const sf::Vector2f& offset)
{
	m_offset = offset;
}

void Map::moveOffset(const sf::Vector2f& delta)
{
	m_offset += delta;
}

void Map::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.texture = &m_spriteSheet;
	states.transform.translate(m_offset.x, m_offset.y);

	for (const auto& vertexBuffer : m_vertexBuffers)
	{
		target.draw(*vertexBuffer, states);
	}
}

void Map::loadLayer(const tmx::Layer* layer, const tmx::Map& map)
{
	std::cout << "Loading map layer: " << layer->getName() << std::endl;

	const auto layerType = layer->getType();
	switch (layerType)
	{
		case tmx::Layer::Type::Tile:
		{
			const auto tileLayer = static_cast<const tmx::TileLayer*>(layer);
			loadTileLayer(tileLayer, map);
			break;
		}
		default:
			std::cout << "Unhandled layer type: " << static_cast<int>(layerType) << std::endl;
	}
}

void Map::loadTileLayer(const tmx::TileLayer* layer, const tmx::Map& map)
{
	m_vertexBuffers.push_back(std::make_unique<sf::VertexBuffer>(sf::PrimitiveType::Triangles, sf::VertexBuffer::Usage::Static));

	const auto vertexCount = calculateActiveTileCount(layer) * 6; // 2 triangles == 6 vertices per tile
	const auto vertexBufferSuccessfullyAllocated = m_vertexBuffers.back()->create(vertexCount);
	assert(vertexBufferSuccessfullyAllocated);
	std::cout << "Allocated layer vertex buffer with " << vertexCount << " points" << std::endl;

	std::vector<sf::Vertex> vertices(vertexCount);
	size_t vertexIndex = 0;

	const auto& tiles = layer->getTiles();
	const auto tileCount = map.getTileCount();

	for (unsigned int y = 0; y < tileCount.y; y++)
	{
		for (unsigned int x = 0; x < tileCount.x; x++)
		{
			const auto& tile = tiles[x + tileCount.x * y];
			if (tile.ID == 0)
			{
				continue;
			}

			const auto& tileVertices = calculateTilePosition(x, y, map.getTileSize());
			const auto& textureVertices = calculateTexturePosition(tile.ID, map.getTilesets().at(0));

			for (size_t i = 0; i < 6; i++)
			{
				vertices[vertexIndex].position = tileVertices[i];
				vertices[vertexIndex].texCoords = textureVertices[i];
				vertexIndex++;
			}
		}
	}

	m_vertexBuffers.back()->update(vertices.data());
}

size_t Map::calculateActiveTileCount(const tmx::TileLayer* layer)
{
	size_t count = 0;

	for (const auto& tile : layer->getTiles())
	{
		if (tile.ID == 0)
		{
			continue;
		}

		count++;
	}

	return count;
}

std::array<sf::Vector2f, 6> Map::calculateTilePosition(const unsigned int tx, const unsigned int ty, const tmx::Vector2u tileSize)
{
	const auto px = tx * tileSize.x;
	const auto py = ty * tileSize.y;

	return convertRectToTriangleVertices(sf::Rect<float>(px, py, tileSize.x, tileSize.y));
}

std::array<sf::Vector2f, 6> Map::calculateTexturePosition(const unsigned int tid, const tmx::Tileset& tileset)
{
	const auto tile = tileset.getTile(tid);
	const auto& pos = tile->imagePosition;
	const auto& size = tile->imageSize;

	return convertRectToTriangleVertices(sf::Rect<float>(pos.x, pos.y, size.x, size.y));
}

std::array<sf::Vector2f, 6> Map::convertRectToTriangleVertices(const sf::Rect<float>& rect)
{
	std::array<sf::Vector2f, 6> vertices;

	// Top left
	vertices[0].x = rect.left;
	vertices[0].y = rect.top;
	// Bottom left
	vertices[1].x = rect.left;
	vertices[1].y = rect.top + rect.height;
	// Top right
	vertices[2].x = rect.left + rect.width;
	vertices[2].y = rect.top;

	// Top right
	vertices[3].x = rect.left + rect.width;
	vertices[3].y = rect.top;
	// Bottom left
	vertices[4].x = rect.left;
	vertices[4].y = rect.top + rect.height;
	// Bottom right
	vertices[5].x = rect.left + rect.width;
	vertices[5].y = rect.top + rect.height;

	return vertices;
}
