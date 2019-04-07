/**
* @file
* Map.cpp
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