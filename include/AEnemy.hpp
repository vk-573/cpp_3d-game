/*
** EPITECH PROJECT, 2018
** AEnemy
** File description:
** Declaration of AEnemy
*/

#ifndef DUNGEON_AENEMY_HPP
#define DUNGEON_AENEMY_HPP

#include "AEntity.hpp"
#include "Player.hpp"

class AEnemy : public AEntity
{
	public:
		AEnemy(const std::string &model, const std::string &texture,
			const irr::core::vector2df &pos, const irr::f32 size);
		~AEnemy();
		virtual void process(std::vector<AEntity *> &entities) = 0;
		void setTimer(irr::ITimer *timer);
	protected:
		irr::core::vector2df target;
		irr::ITimer	*timer;
		irr::u32	targetTimer;
		irr::u32	attackTimer;
		float attackSpeed;
		float range;
		int damage;
};


#endif //DUNGEON_AENEMY_HPP
