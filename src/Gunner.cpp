/*
** EPITECH PROJECT, 2018
** Gunner
** File description:
** Implementation of Gunner
*/

#include "Gunner.hpp"

Gunner::Gunner(const irr::core::vector2df &pos, const irr::f32 size)
	: AEnemy("resources/models/rhino.md2", "resources/textures/rhino.jpg", pos, size * 0.5)
{
	attackTimer = 0;
	targetTimer = 0;
	attackSpeed = 6;
	speed = 0.75;
	range = 0.8;
	damage = 10;
	_hp = 50;
}

Gunner::~Gunner()
{
}

void Gunner::move()
{
	setState(IDLE);
}

void Gunner::attack(std::vector<AEntity *> &entities)
{
	int rand = random() % 30 - 15;
	float direction = angle + rand;

	if (getState() != ATTACK) {
		SoundManager::playSound("gunfire.wav");
		attackTimer = timer->getTime();
		entities.push_back(new Missile(_device, pos, direction, 2));
	}
	setState(ATTACK);
}

void Gunner::targetNew(Player *player)
{
	irr::core::vector2df newPos;
	target = player->getPos();
	double direction = atan2(target.Y - pos.Y, target.X - pos.X) * 180 / M_PI;

	setAngle(direction);
}

void Gunner::process(std::vector<AEntity *> &entities)
{
	Player *player = (Player *)entities[0];
	if (_isDying) {
		processDeath(_device->getTimer()->getTime());
		return;
	}
	if (timer->getTime() + random() % 200 - random() % 200 > targetTimer + 0.1 * 1000) {
		targetTimer = timer->getTime();
		targetNew((Player *)player);
	}

	if (timer->getTime() > attackTimer + attackSpeed * 1000) {
		attack(entities);
	}
	else if (timer->getTime() > attackTimer + 1000) {
		move();
	}
}

void		Gunner::processDeath(const irr::u32 &tmp) {
	if (tmp - _deathTimer > 800) {
		_dead = true;
		animatedMeshSceneNode->setVisible(false);
	}
}