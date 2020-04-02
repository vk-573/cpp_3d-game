/*
** EPITECH PROJECT, 2018
** Tile
** File description:
** Implementation of Tile
*/

#include "Tile.hpp"

Tile::Tile(std::string texture, Type type) : texture(texture), mesh(nullptr), type(type), spawn(false)
{
}

Tile::~Tile()
{
	if (mesh)
		mesh->remove();
}

void Tile::draw(irr::IrrlichtDevice *device, irr::s32 x, irr::s32 y, irr::s32 tileSize)
{
	const irr::scene::IGeometryCreator *g = device->getSceneManager()->getGeometryCreator();
	irr::scene::IMesh *plane = g->createPlaneMesh(
		irr::core::dimension2d<irr::f32>((irr::f32)tileSize, (irr::f32)tileSize));
	floorMesh = device->getSceneManager()->addMeshSceneNode(plane);
	floorMesh->setPosition(irr::core::vector3df((irr::f32)x * tileSize, 0, (irr::f32)y * tileSize));
	floorMesh->setMaterialType(irr::video::EMT_SOLID);
	floorMesh->setMaterialFlag(irr::video::EMF_NORMALIZE_NORMALS, true);
	floorMesh->setMaterialTexture(0, device->getVideoDriver()->getTexture(texture.c_str()));
}

void Tile::clear()
{
	floorMesh->getSceneManager()->addToDeletionQueue(floorMesh);
	if (mesh)
		mesh->getSceneManager()->addToDeletionQueue(mesh);
	floorMesh = nullptr;
	mesh = nullptr;
}

Tile::Type Tile::getType() const
{
	return type;
}

bool Tile::isSpawn() const
{
	return spawn;
}
void Tile::setSpawn(bool spawn)
{
	Tile::spawn = spawn;
}

