/*
** EPITECH PROJECT, 2018
** Goblin
** File description:
** Declaration of Goblin
*/

#ifndef DUNGEON_GOBLIN_HPP
#define DUNGEON_GOBLIN_HPP

#include "AEnemy.hpp"

class Goblin : public AEnemy
{
public:
	Goblin(const irr::core::vector2df &pos, const irr::f32 size);
	~Goblin();
	void move();
	void process(std::vector<AEntity *> &entities) override;
	void attack(Player *player);
	void targetNew(Player *player);
	void processDeath(const irr::u32 &tmp);
};


#endif //DUNGEON_GOBLIN_HPP
