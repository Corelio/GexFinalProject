#pragma once
#include <vector>
#include <memory>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

namespace GEX
{
	class Tile
	{
	public:
		Tile();
		~Tile();
		sf::Sprite* getSprite(int p) const;
		int getTileSize() const { return tileSize_; }
	private:
		void loadSprite();
	private:
		std::vector<std::unique_ptr<sf::Sprite>> sprites_;
		std::unique_ptr<sf::Texture> texture_;
		std::string	filePath_;
		int tileSize_;
		int x_;
		int y_;
	};
}
