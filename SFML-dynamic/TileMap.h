#pragma once
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/System/Vector2.hpp>
#include "Map.h"
#include <string>

namespace GEX
{
	class TileMap : public sf::Drawable, public sf::Transformable
	{
	public:
		TileMap();
		~TileMap();

		bool load(Map* tiles, unsigned int width, unsigned int height);

		const sf::Vector2u getTileSize() const { return tileSize_; };

	private:
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
		{
			// apply the transform
			states.transform *= getTransform();

			// apply the tileset texture
			states.texture = &tileSet_;

			// draw the vertex array
			target.draw(vertices_, states);
		}

	private:
		std::string				tileSetFile_ = "Media/Textures/atlas_tiles.png";
		sf::VertexArray			vertices_;
		sf::Texture				tileSet_;
		const sf::Vector2u		tileSize_ = sf::Vector2u(16,16);
	};

}