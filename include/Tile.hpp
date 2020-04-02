/*
** EPITECH PROJECT, 2018
** Tile
** File description:
** Declaration of Tile
*/

#ifndef DUNGEON_TILE_HPP
#define DUNGEON_TILE_HPP

#include <irrlicht/irrlicht.h>
#include <string>

class Tile
{
	public:
		enum Type {
			FLOOR,
			WALL,
			DOOR
		};
		Tile(std::string texture, Type type);
		virtual ~Tile();
		virtual void draw(irr::IrrlichtDevice *device, irr::s32 x, irr::s32 y, irr::s32 tileSize);
		virtual void clear();
		Type getType() const;
	protected:
		std::string texture;
		irr::scene::IMeshSceneNode *floorMesh;
		irr::scene::IMeshSceneNode *mesh;
		Type type;
		bool spawn;
public:
	bool isSpawn() const;
	void setSpawn(bool spawn);
};


#endif //DUNGEON_TILE_HPP
