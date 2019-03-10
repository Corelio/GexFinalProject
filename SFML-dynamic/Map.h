#pragma once
#include <string>
namespace GEX {
	const int MAPX = 100;
	const int MAPY = 50;

	class Map
	{
	public:
		Map();
		Map(std::string path);
		~Map();
		void			setTile(int x, int y, int value);
		int				getTile(int x, int y) const;
		void			reload();
		int				tileMap[MAPX][MAPY];
	private:
		std::string		_texture;
	};
}
