#include "Map.h"
#include <sstream>
#include <fstream>
#include <string>

namespace GEX
{
	Map::Map()
	{
		_texture = "Media/Textures/tileMap.csv";
		reload();
	}

	Map::Map(std::string path)
	{
		_texture = path;
		reload();
	}

	Map::~Map()
	{
	}

	void Map::setTile(int x, int y, int value)
	{
		tileMap[x][y] = value;
	}

	int Map::getTile(int x, int y) const
	{
		return tileMap[x][y];
	}

	/*
		Method to load the tile map from a CSV file
	*/
	void Map::reload()
	{
		std::ifstream file;
		file.open(_texture);
		std::string fullLine;
		int x = 0;
		int y = 0;
		while (std::getline(file, fullLine, '\n'))  
		{
			std::istringstream line(fullLine);
			std::string data;
			while (std::getline(line, data, ',')) 
			{
				tileMap[x++][y] = std::stoi(data);
			}
			x = 0;
			y++;
		}
		file.close();
	}

}