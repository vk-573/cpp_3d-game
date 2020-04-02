/*
** EPITECH PROJECT, 2018
** Missile
** File description:
** Implementation of Missile
*/

#include <Missile.hpp>

#include "Missile.hpp"

Missile::Missile(irr::IrrlichtDevice *device, irr::core::vector2df pos,
	float angle, float size)
	: AEntity(device, "resources/models/missile.obj", "resources/textures/missile.png", pos, size)
{
	_isOver = false;
	speed = 0.06;
	timer = device->getTimer();
	spawnTime = timer->getTime();
	draw(device);
	setAngle(angle);
}

void Missile::draw(irr::IrrlichtDevice *device)
{
	AEntity::draw(device);
}

void Missile::move()
{
	irr::core::vector2df newPos(pos);
	float angle = getAngle();

	newPos.X = pos.X + speed * cos(angle * M_PI / 180);
	newPos.Y = pos.Y + speed * sin(angle * M_PI / 180);

	setPos(newPos);
}

void Missile::process(std::vector<AEntity *> &entities)
{
	entities = entities;
	if (timer->getTime() > spawnTime + 10 * 1000) {
		_isOver = true;
		return;
	}
	move();
}

void Missile::setAngle(irr::f32 angle)
{
	animatedMeshSceneNode->setRotation(irr::core::vector3df(0, angle + 90, 0));
	AEntity::angle = angle;
}

bool Missile::isOver()
{
	return _isOver;
}
