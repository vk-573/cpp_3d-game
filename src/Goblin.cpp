/*
** EPITECH PROJECT, 2018
** Goblin
** File description:
** Implementation of Goblin
*/

#include <Goblin.hpp>

#include "Goblin.hpp"

Goblin::Goblin(const irr::core::vector2df &pos, const irr::f32 size)
	: AEnemy("resources/models/knight.md2", "resources/textures/knight.jpg", pos, size * 0.5)
{
	attackTimer = 0;
	targetTimer = 0;
	attackSpeed = 0.8;
	speed = 0.025;
	range = 0.8;
	damage = 1;
	_hp = 40;
}

Goblin::~Goblin()
{

}

void Goblin::move()
{
	irr::core::vector2df newPos;
	double direction = atan2(target.Y - pos.Y, target.X - pos.X) * 180 / M_PI;

	newPos.X = pos.X + speed * cos(direction * M_PI / 180);
	newPos.Y = pos.Y + speed * sin(direction * M_PI / 180);

	setAngle(direction);

	//COLLISIONS
	if (true) {
		setState(RUNNING);
		setPos(newPos);
	}
	else {
		setState(IDLE);
	}

	//Basic collision with walls
//	if (newPos.X < 0 || newPos.X >= map.getWidth(false)
//	    || newPos.Y < 0 || newPos.Y >= map.getHeight(false)
//	    || map.getTile(newPos.X, newPos.Y)->getType() == Tile::Type::WALL) {
//		return;
//	}
}

void Goblin::attack(Player *player)
{

	//damage only if player is still here at this point of animation
	if (state != ATTACK || timer->getTime() > attackTimer + attackSpeed * 1000) {
		attackTimer = timer->getTime();
		player->damage(damage);
	}
	setState(ATTACK);
}

void Goblin::targetNew(Player *player)
{
	irr::core::vector2df newPos;
	int rand = random() % 100;
	target = player->getPos();
	double direction = atan2(target.Y - pos.Y, target.X - pos.X) * 180 / M_PI;

	if (rand < 15)
		direction += 90;
	else if (rand < 30)
		direction -= 90;
	else
		return;

	newPos.X = pos.X + 2 * cos(direction * M_PI / 180);
	newPos.Y = pos.Y + 2 * sin(direction * M_PI / 180);
	target = newPos;
}

void Goblin::process(std::vector<AEntity *> &entities)
{
	if (_isDying) {
		processDeath(_device->getTimer()->getTime());
		return;
	}
	Player *player = (Player *)entities[0];

	if (timer->getTime() + random() % 200 - random() % 200 > targetTimer + 1 * 1000) {
		targetTimer = timer->getTime();
		targetNew((Player *)player);
	}
	float distance = sqrt(pow(pos.X - target.X, 2) + pow(pos.Y - target.Y, 2));

	if (distance <= range) {
		attack((Player *)player);
	}
	else if (timer->getTime() > attackTimer + attackSpeed * 1000) {
		move();
	}
}

void		Goblin::processDeath(const irr::u32 &tmp) {
	if (tmp - _deathTimer > 800) {
		_dead = true;
		animatedMeshSceneNode->setVisible(false);
	}
}