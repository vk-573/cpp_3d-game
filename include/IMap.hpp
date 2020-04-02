/*
** EPITECH PROJECT, 2019
** Map interface
** File description:
** Declaration of Map
*/

#ifndef IMAP_HPP
#define IMAP_HPP

#include "Tile.hpp"
#include "AEntity.hpp"
#include <vector>

class IMap
{
public:
	virtual Tile *getTile(const int x, const int y) = 0;
	virtual std::vector<AEntity *> &getEnnemies() = 0;
};


#endif //IMAP_HPP
