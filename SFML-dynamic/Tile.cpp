#include "Tile.h"

namespace GEX
{
	Tile::Tile() :
		texture_(new sf::Texture()),
		sprites_(),
		filePath_("Media/Textures/atlas_tiles.png"),
		tileSize_(16),
		x_(37),
		y_(28)
	{
		loadSprite();
	}


	Tile::~Tile()
	{
	}

	sf::Sprite* Tile::getSprite(int p) const
	{
		return sprites_[p].get();
	}

	void Tile::loadSprite()
	{
		texture_->loadFromFile(filePath_);
		sf::Vector2f position = sf::Vector2f();
		for (int i = 0; i < x_; i++) {
			for (int j = 0; j < y_; j++) {
				position.x = i*tileSize_ + i * 1;
				position.y = j*tileSize_ + j * 1;
				std::unique_ptr<sf::Sprite> tile(new sf::Sprite());
				tile->setTexture(*texture_);
				tile->setPosition(position);
				sprites_.push_back(std::move(tile));
			}
		}
	}

}