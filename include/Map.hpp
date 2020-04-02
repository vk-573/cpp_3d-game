/*
** EPITECH PROJECT, 2018
** Map
** File description:
** Declaration of Map
*/

#ifndef DUNGEON_MAP_HPP
#define DUNGEON_MAP_HPP

#include <vector>
#include <fstream>
#include <map>
#include "IMap.hpp"
#include <string>
// #include "Tile.hpp"
#include "Wall.hpp"
#include "Door.hpp"
// #include "AEntity.hpp"
#include "Goblin.hpp"
#include "Gunner.hpp"

class Map : public IMap
{
public:
	Map();
	Map(const std::string &name);
	Map(const std::string &name, const irr::core::vector2di &pos, const Door::Direction dir);
	~Map();
	void draw(irr::IrrlichtDevice *device);
	void clear();
	int getWidth(bool worldValues) const;
	int getHeight(bool worldValues) const;
	int getTileSize() const;
	void rotateTiles();
	void rotate(const int rotateValue);
	static std::vector<Map *> generate(const int depth);
	void generateAdjacent(std::vector<Map *> &grid, const int depth);
	const irr::core::vector2di &getPos() const;
	Tile *getTile(const int x, const int y);
	std::map<Door::Direction, Map *> &getAdjacentMaps();
	void setAdjacent(Map *map, const Door::Direction dir);
	irr::core::vector2df getSpawnPos(const Door::Direction dir);
	AEntity *spawnEnemy(const irr::core::vector2di &pos);
	void spawnEnemies();
	std::vector<AEntity *> &getEnnemies();

private:
	std::vector<std::vector<Tile *>> tiles;
	std::map<Door::Direction, Map *> adjacentMaps;
	std::vector<Door::Direction> doors;
	std::vector<AEntity *> ennemies;
	irr::core::vector2di pos;
	int tileSize;
};


#endif //DUNGEON_MAP_HPP
