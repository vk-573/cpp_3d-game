/*
** EPITECH PROJECT, 2018
** Map
** File description:
** Implementation of Map
*/

#include <iostream>
#include "Map.hpp"


Map::Map() : tileSize(20)
{
	int height = 10;
	int width = 10;

	//todo: map creation
	//C'est une map de debug en dur pour l'instant, il faut pouvoir charger des fichers de map
	for (int y = 0; y < height; y++) {
		tiles.emplace_back();
		for (int x = 0; x < width; x++) {
			if (x == 0 || y == 0 || x == width - 1 || y == height - 1) {
				//wall
				tiles[y].push_back(new Wall());
			}
			else {
				//ground
				tiles[y].push_back(new Tile("resources/textures/grass.jpg", Tile::FLOOR));
			}
		}
	}
}

Map::Map(const std::string &name) : adjacentMaps(), tileSize(20)
{
	std::ifstream infile(name);
	pos = irr::core::vector2di(0, 0);
	int y = 0;

	std::string line;
	while (std::getline(infile, line))
	{
		tiles.emplace_back();
		for (unsigned int x = 0; x < line.size(); x++) {
			char c = line[x];

			if (c == ' ' || c == 'E' || c == 'I') {
				tiles[y].push_back(new Tile("resources/textures/grass.jpg", Tile::FLOOR));
			}
			else if (c == '#') {
				tiles[y].push_back(new Wall());
			}
			else if (c == 'U' || c == 'D' || c == 'R' || c == 'L') {
				tiles[y].push_back(new Door(c));
				doors.push_back(((Door *)tiles[y][x])->getDirection());
			}

			//spawn des entités
			if (c == 'E') {
				tiles[y][x]->setSpawn(true);
			}

		}
		y++;
	}

}

Map::Map(const std::string &name, const irr::core::vector2di &parentPosition, const Door::Direction dir) : Map(name)
{
	pos = irr::core::vector2di(parentPosition.X, parentPosition.Y);

	if (dir == Door::Direction::UP) {
		pos.Y++;
	}
	else if (dir == Door::Direction::DOWN) {
		pos.Y--;
	}
	else if (dir == Door::Direction::LEFT) {
		pos.X--;
	}
	else if (dir == Door::Direction::RIGHT) {
		pos.X++;
	}
}

Map::~Map()
{
	for (auto line : tiles) {
		for (auto tile : line) {
			delete tile;
		}
	}
	tiles.clear();
	clear();
	for (auto e : ennemies) {
		delete e;
	}
}

void Map::rotateTiles()
{
	std::vector<std::vector<Tile *>> newMap;

	for (int y = tiles.size() - 1; y >= 0; y--) {
		for (unsigned int x = 0; x < tiles[y].size(); x++) {
			if (newMap.size() <= x) {
				newMap.emplace_back();
			}

			if (tiles[y][x]->getType() == Tile::Type::DOOR) {
				((Door *)tiles[y][x])->rotate();
			}
			newMap[x].push_back(tiles[y][x]);
		}
	}

	for (auto row : tiles) {
		row.clear();
	}
	tiles.clear();
	tiles = newMap;
}

void Map::rotate(int rotateValue)
{
	for (int i = 0; i < rotateValue; i++) {
		rotateTiles();
	}

	for (auto &dir : doors)
		dir = dir + rotateValue;
}

void Map::spawnEnemies()
{
	for (unsigned int y = 0; y < tiles.size(); y++) {
		for (unsigned int x = 0; x < tiles[y].size(); x++) {
			if (tiles[y][x]->isSpawn())
				ennemies.push_back(spawnEnemy(irr::core::vector2di(x, y)));
		}
	};
}

void Map::draw(irr::IrrlichtDevice *device)
{
	for (unsigned int y = 0; y < tiles.size(); y++) {
		for (unsigned int x = 0; x < tiles[y].size(); x++) {
			//le Y est inversé au rendu
			tiles[y][x]->draw(device, x, y * -1, tileSize);
		}
	}

	for (AEntity *enemy : ennemies) {
		if (!enemy->isDead()) {
			enemy->draw(device);
		}
	}
}

void Map::clear()
{
	for (unsigned int y = 0; y < tiles.size(); y++) {
		for (unsigned int x = 0; x < tiles[y].size(); x++) {
			tiles[y][x]->clear();
		}
	}

	for (AEntity *enemy : ennemies) {
		enemy->clear();
	}
	// ennemies.clear();
}

int Map::getWidth(bool worldValue) const
{
	return (int)tiles[0].size() * (worldValue ? tileSize : 1);
}

int Map::getHeight(bool worldValue) const
{
	return (int)tiles.size() * (worldValue ? tileSize : 1);
}

int Map::getTileSize() const
{
	return tileSize;
}

void Map::generateAdjacent(std::vector<Map *> &grid, const int maxDepth)
{
	Map *newMap;
	std::string selectedMap = "1";
	int mapCount = grid.size();

	srand(time(NULL));
	for (auto direction : doors) {
		if (adjacentMaps.count(direction)) {
			continue;
		}

		if (mapCount >= maxDepth) {
			newMap = new Map("resources/maps/1.map", pos, direction);
		}
		else {
			int rand = (int)(random() % 100);
			//TODO: add depth to rand?

			if (rand < 50)
				selectedMap = "2";
			else if (rand < 60)
				selectedMap = "22";
			else if (rand < 75)
				selectedMap = "3";
			else if (rand < 90)
				selectedMap = "33";
			//TODO: check if map exists in adjacent coords
			newMap = new Map("resources/maps/" + selectedMap + ".map", pos, direction);
		}

		newMap->rotate((int)direction + 2);

		newMap->setAdjacent(this, direction + 2);
		adjacentMaps[direction] = newMap;
		grid.push_back(newMap);
	}
}


std::vector<Map *> Map::generate(const int depth)
{
	std::vector<Map *> mapGrid;
	int mapCount = mapGrid.size();

	mapGrid.push_back(new Map("resources/maps/4.map"));
	for (int i = 0; i < depth; i++) {
		mapCount = mapGrid.size();
		for (int j = 0; j < mapCount; j++) {
			Map *map = mapGrid[j];
			map->generateAdjacent(mapGrid, depth);
		}
	}

	return mapGrid;
}

const irr::core::vector2di &Map::getPos() const
{
	return pos;
}

std::map<Door::Direction, Map *> &Map::getAdjacentMaps()
{
	return adjacentMaps;
}

Tile *Map::getTile(const int x, const int y)
{
	return tiles[y][x];
}

void Map::setAdjacent(Map *map, const Door::Direction dir)
{
	adjacentMaps[dir] = map;
}

irr::core::vector2df Map::getSpawnPos(const Door::Direction dir)
{
	irr::core::vector2df spawn(getWidth(false) / 2 + 0.5, getHeight(false) / 2 + 0.5);

	std::cout << "Dir " << (int)dir << std::endl;
	for (unsigned int y = 0; y < tiles.size(); y++) {
		for (unsigned int x = 0; x < tiles[y].size(); x++) {
			if (tiles[y][x]->getType() == Tile::Type::DOOR
				&& ((Door *)tiles[y][x])->getDirection() == dir + 2
				&& (int)dir != -1) {
				spawn.X = x + 0.5;
				spawn.Y = y + 0.5;
				if (dir == Door::Direction::UP) {
					spawn.Y--;
				}
				else if (dir == Door::Direction::DOWN) {
					spawn.Y++;
				}
				else if (dir == Door::Direction::RIGHT) {
					spawn.X++;
				}
				else if (dir == Door::Direction::LEFT) {
					spawn.X--;
				}
				return spawn;
			}
		}
	}

	return spawn;
}

AEntity *Map::spawnEnemy(const irr::core::vector2di &pos)
{
	AEntity *enemy;
	irr::core::vector2df finalPos(pos.X + 0.5, pos.Y + 0.5);
	int rand = random() % 2;

	if (rand == 0) {
		enemy = (AEntity *)new Gunner(finalPos, 1);
	}
	else if (rand == 1) {
		enemy = (AEntity *)new Goblin(finalPos, 1);
	}
	return enemy;
}

std::vector<AEntity *> &Map::getEnnemies()
{
	return ennemies;
}
