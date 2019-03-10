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