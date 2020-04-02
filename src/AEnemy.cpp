/*
** EPITECH PROJECT, 2018
** AEnemy
** File description:
** Implementation of AEnemy
*/

#include <AEnemy.hpp>

#include "AEnemy.hpp"

AEnemy::AEnemy(const std::string &model, const std::string &texture,
	const irr::core::vector2df &pos, const irr::f32 size)
	: AEntity(NULL, model, texture, pos, size), target()
{
	;
}

AEnemy::~AEnemy()
{

}

void AEnemy::setTimer(irr::ITimer *timer)
{
	AEnemy::timer = timer;
}