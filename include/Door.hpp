/*
** EPITECH PROJECT, 2018
** Door
** File description:
** Declaration of Door
*/

#ifndef DUNGEON_DOOR_HPP
#define DUNGEON_DOOR_HPP

#include "Tile.hpp"

class Door : public Tile
{
public:
	enum Direction {
		UP = 0,
		RIGHT,
		DOWN,
		LEFT
	};
	Door(const char d);
	void draw(irr::IrrlichtDevice *device, irr::s32 x, irr::s32 y, irr::s32 tileSize) override;
	void rotate();
	Direction getDirection() const;
protected:
	Direction direction;
};

Door::Direction operator +(Door::Direction dir, int value);

#endif //DUNGEON_DOOR_HPP
