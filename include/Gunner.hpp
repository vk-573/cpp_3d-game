/*
** EPITECH PROJECT, 2018
** Gunner
** File description:
** Declaration of Gunner
*/

#ifndef DUNGEON_GUNNER_HPP
#define DUNGEON_GUNNER_HPP

#include "AEnemy.hpp"
#include "Missile.hpp"

class Gunner : public AEnemy
{
public:
	Gunner(const irr::core::vector2df &pos, const irr::f32 size);
	~Gunner();
	void move();
	void process(std::vector<AEntity *> &entities) override;
	void attack(std::vector<AEntity *> &entities);
	void targetNew(Player *player);
	void processDeath(const irr::u32 &tmp);
};


#endif //DUNGEON_GUNNER_HPP
