/**
* @file
* SpriteNode.cpp
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
#include "SpriteNode.h"

namespace GEX
{

	SpriteNode::SpriteNode(const sf::Texture& texture) :
		sprite_(texture)
	{

	}

	SpriteNode::SpriteNode(const sf::Texture & texture, const sf::IntRect & textureRect) :
		sprite_(texture, textureRect)
	{
	}

	void SpriteNode::setSprite(const sf::Texture & texture, const sf::IntRect & textureRect)
	{
		sprite_.setTexture(texture);
		sprite_.setTextureRect(textureRect);
	}

	void SpriteNode::drawCurrent(sf::RenderTarget & target, sf::RenderStates states) const
	{
		target.draw(sprite_, states);
	}

}