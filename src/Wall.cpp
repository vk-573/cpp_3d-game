/*
** EPITECH PROJECT, 2018
** Wall
** File description:
** Implementation of Wall
*/

#include <Wall.hpp>

#include "Wall.hpp"


Wall::Wall() : Tile("resources/textures/wall.jpg", WALL)
{

}

void Wall::draw(irr::IrrlichtDevice *device, irr::s32 x, irr::s32 y, irr::s32 tileSize)
{
	Tile::draw(device, x, y, tileSize);
	irr::scene::IAnimatedMesh *cube = device->getSceneManager()->getMesh("resources/models/cube.obj");
	mesh = (irr::scene::IMeshSceneNode *)device->getSceneManager()->addAnimatedMeshSceneNode(cube);
	mesh->addShadowVolumeSceneNode();
	mesh->setScale(irr::core::vector3df((irr::f32)tileSize, (irr::f32)tileSize, (irr::f32)tileSize));
	mesh->setPosition(irr::core::vector3df((irr::f32)x * tileSize, 0, (irr::f32)y * tileSize));
	mesh->setMaterialType(irr::video::EMT_SOLID);
	mesh->setMaterialFlag(irr::video::EMF_NORMALIZE_NORMALS, true);
	mesh->setMaterialTexture(0, device->getVideoDriver()->getTexture(texture.c_str()));
}
