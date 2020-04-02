/*
** EPITECH PROJECT, 2018
** Door
** File description:
** Implementation of Door
*/

#include "Door.hpp"

Door::Door(const char d) : Tile("resources/textures/grass.jpg", DOOR)
{
	if (d == 'U') {
		direction = UP;
	}
	else if (d == 'D') {
		direction = DOWN;
	}
	else if (d == 'L') {
		direction = LEFT;
	}
	else if (d == 'R') {
		direction = RIGHT;
	}
}

void Door::draw(irr::IrrlichtDevice *device, irr::s32 x, irr::s32 y, irr::s32 tileSize)
{
	Tile::draw(device, x, y, tileSize);
	irr::scene::IAnimatedMesh *cube = device->getSceneManager()->getMesh("resources/models/door.obj");
	mesh = (irr::scene::IMeshSceneNode *)device->getSceneManager()->addAnimatedMeshSceneNode(cube);
	mesh->addShadowVolumeSceneNode();
	mesh->setScale(irr::core::vector3df((irr::f32)tileSize * 0.2, (irr::f32)tileSize * 0.2, (irr::f32)tileSize * 0.4));
	mesh->setPosition(irr::core::vector3df((irr::f32)x * tileSize, tileSize * 0.5, (irr::f32)y * tileSize));
	mesh->setRotation(irr::core::vector3df(0, 90 * (int)direction, 0));
	mesh->setMaterialType(irr::video::EMT_SOLID);
	mesh->setMaterialFlag(irr::video::EMF_NORMALIZE_NORMALS, true);
}

void Door::rotate()
{
	direction = direction + 1;
}

Door::Direction Door::getDirection() const
{
	return direction;
}

Door::Direction operator +(Door::Direction dir, int value) {
	return (Door::Direction)(((int)dir + value) % 4);
}
