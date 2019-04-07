/**
* @file
* Tile.cpp
* @author
* Marco Corsini Baccaro 2019
* @version 1.0
*
* @section DESCRIPTION
* Game Experience Development Course
* Class of 2018-2019 
* Final Project
*
* @section LICENSE
*
* Copyright 2019
* Permission to use, copy, modify, and/or distribute this software for
* any purpose with or without fee is hereby granted, provided that the
* above copyright notice and this permission notice appear in all copies.
*
* THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
* WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
* MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
* ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
* WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
* ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
* OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
*
* @section Academic Integrity
* I certify that this work is solely my own and complies with
* NBCC Academic Integrity Policy (policy 1111)
*/
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