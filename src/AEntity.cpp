/*
** EPITECH PROJECT, 2018
** AEntity
** File description:
** Implementation of AEntity
*/

#include <AEntity.hpp>

#include "AEntity.hpp"

AEntity::AEntity(irr::IrrlichtDevice *device, const std::string &model, const std::string &texture,
	const irr::core::vector2df &pos, const irr::f32 size)
	: animatedMesh(NULL), animatedMeshSceneNode(NULL), pos(pos), size(size), model(model), texture(texture)
{
	_device = device;
}

AEntity::~AEntity()
{

}

void AEntity::draw(irr::IrrlichtDevice *device)
{
	if (!_device)
		_device = device;
	if (!animatedMesh) {
		animatedMesh = device->getSceneManager()->getMesh(model.c_str());
	}
	animatedMeshSceneNode = device->getSceneManager()->addAnimatedMeshSceneNode(animatedMesh);
	animatedMeshSceneNode->addShadowVolumeSceneNode();
	animatedMeshSceneNode->setMaterialType(irr::video::EMT_SOLID);
	animatedMeshSceneNode->setMaterialFlag(irr::video::EMF_NORMALIZE_NORMALS, true);
	animatedMeshSceneNode->setMD2Animation(irr::scene::EMAT_STAND);
	animatedMeshSceneNode->setMaterialTexture(0, device->getVideoDriver()->getTexture(texture.c_str()));
	setPos(pos);
	setSize(size);
}

AEntity		&AEntity::getThis() {
	return *this;
}

const irr::core::vector2df &AEntity::getPos() const
{
	return pos;
}

const irr::core::vector3df &AEntity::getMeshPos() const
{
	return animatedMeshSceneNode->getPosition();
}

void AEntity::setPos(const irr::core::vector2df &pos, const int tileSize)
{
	if (animatedMeshSceneNode) {
		animatedMeshSceneNode->setPosition(irr::core::vector3df(
			pos.X * tileSize - tileSize / 2,
			tileSize * 0.75,
			pos.Y * -1 * tileSize + tileSize / 2
		));
	}
	AEntity::pos = pos;
}

irr::f32 AEntity::getAngle() const
{
	return angle;
}

void AEntity::setAngle(irr::f32 angle)
{
	animatedMeshSceneNode->setRotation(irr::core::vector3df(0, angle, 0));
	AEntity::angle = angle;
}

irr::f32 AEntity::getSpeed() const
{
	return speed;
}

void AEntity::setSpeed(irr::f32 speed)
{
	AEntity::speed = speed;
}

irr::f32 AEntity::getSize() const
{
	return size;
}

void AEntity::setSize(irr::f32 size)
{
	animatedMeshSceneNode->setScale(irr::core::vector3df(size, size, size));
	AEntity::size = size;
}

AEntity::State AEntity::getState() const
{
	return state;
}

void AEntity::setState(AEntity::State newState)
{
	if (newState == RUNNING && state != RUNNING) {
		animatedMeshSceneNode->setMD2Animation(irr::scene::EMD2_ANIMATION_TYPE::EMAT_RUN);
	}
	else if (newState == IDLE && state != IDLE) {
		animatedMeshSceneNode->setMD2Animation(irr::scene::EMD2_ANIMATION_TYPE::EMAT_STAND);
	}
	else if (newState == ATTACK && state != ATTACK) {
		animatedMeshSceneNode->setMD2Animation(irr::scene::EMD2_ANIMATION_TYPE::EMAT_ATTACK);
	}
	else if (newState == ATTACKSPELL && state != ATTACKSPELL) {
		animatedMeshSceneNode->setMD2Animation(irr::scene::EMD2_ANIMATION_TYPE::EMAT_STAND);		
	}
	else if (newState == DAMAGED && state != DAMAGED) {
		animatedMeshSceneNode->setMD2Animation(irr::scene::EMD2_ANIMATION_TYPE::EMAT_PAIN_A);
	}
	state = newState;
}

void AEntity::clear()
{
	if (animatedMeshSceneNode) {
		animatedMeshSceneNode->getSceneManager()->addToDeletionQueue(animatedMeshSceneNode);
	}
	animatedMeshSceneNode = NULL;
}

const std::string &AEntity::getModelString() const
{
	return model;
}

bool		AEntity::isDead() const {
	return _dead;
}

bool		AEntity::isDying() const {
	return _isDying;
}

void	AEntity::gotHit(const int &damage) {
	if (_isDying) {
		return;
	}
	_hp -= damage;
	animatedMeshSceneNode->setMD2Animation(irr::scene::EMD2_ANIMATION_TYPE::EMAT_PAIN_A);
	if (_hp <= 0) {
		_hp = 0;
		_isDying = true;
		_deathTimer = _device->getTimer()->getTime();
		animatedMeshSceneNode->setMD2Animation(irr::scene::EMAT_DEATH_FALLBACK);
		// puts("Died");
		// animatedMeshSceneNode->setVisible(false);
	}
}
