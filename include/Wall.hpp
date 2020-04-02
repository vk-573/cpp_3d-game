/*
** EPITECH PROJECT, 2018
** Wall
** File description:
** Declaration of Wall
*/

#ifndef DUNGEON_WALL_HPP
#define DUNGEON_WALL_HPP

#include "Tile.hpp"

class Wall : public Tile
{
	public:
		Wall();
		void draw(irr::IrrlichtDevice *device, irr::s32 x, irr::s32 y, irr::s32 tileSize) override;

};


#endif //DUNGEON_WALL_HPP
