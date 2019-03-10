#include "TileMap.h"

namespace GEX
{

	TileMap::TileMap()
	{
		//Load tileset
		tileSet_.loadFromFile(tileSetFile_);
	}


	TileMap::~TileMap()
	{
	}

	bool TileMap::load(Map* tiles, unsigned int width, unsigned int height)
	{
		// resize the vertex array to fit the level size
		vertices_.setPrimitiveType(sf::Quads);
		vertices_.resize(width * height * 4);

		// populate the vertex array, with one quad per tile
		for (unsigned int i = 0; i < width; ++i)
			for (unsigned int j = 0; j < height; ++j)
			{
				// get the current tile number
				int tileNumber = tiles->getTile(i,j);
				
				// if tile number is less than zero, do not draw
				if (tileNumber < 0) {
					continue; //move to the next tile
				}

				// find its position in the tileset texture
				int tu = tileNumber % (tileSet_.getSize().x / tileSize_.x);
				int tv = tileNumber / (tileSet_.getSize().x / tileSize_.x);

				// get a pointer to the current tile's quad
				sf::Vertex* quad = &vertices_[(i + j * width) * 4];

				// define its 4 corners
				quad[0].position = sf::Vector2f(i * tileSize_.x, j * tileSize_.y);
				quad[1].position = sf::Vector2f((i + 1) * tileSize_.x, j * tileSize_.y);
				quad[2].position = sf::Vector2f((i + 1) * tileSize_.x, (j + 1) * tileSize_.y);
				quad[3].position = sf::Vector2f(i * tileSize_.x, (j + 1) * tileSize_.y);

				// define its 4 texture coordinates
				quad[0].texCoords = sf::Vector2f(tu * tileSize_.x + tu, tv * tileSize_.y + tv);
				quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize_.x + tu, tv * tileSize_.y + tv);
				quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize_.x + tu, (tv + 1) * tileSize_.y + tv);
				quad[3].texCoords = sf::Vector2f(tu * tileSize_.x + tu, (tv + 1) * tileSize_.y + tv);
			}

		return true;
	}

}
