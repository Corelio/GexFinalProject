#pragma once
#include <SFML/System/Vector2.hpp>
#include "Animation.h"

namespace sf
{
	class Sprite;
	class Text;
}

void centerOrigin(sf::Sprite& sprite);
void centerOrigin(sf::Text& text);
void centerOrigin(GEX::Animation& animation);

// Degree/radian conversion
float			toDegree(float radian);
float			toRadian(float degree);

// Random number generation
int				randomInt(int exclusiveMax);

// Vector operations
float			length(sf::Vector2f vector);
sf::Vector2f	unitVector(sf::Vector2f vector);

//Rectangle flip left right
sf::IntRect flip(const sf::IntRect& rec);



