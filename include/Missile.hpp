/*
** EPITECH PROJECT, 2018
** Missile
** File description:
** Declaration of Missile
*/

#ifndef DUNGEON_MISSILE_HPP
#define DUNGEON_MISSILE_HPP

#include "AEntity.hpp"

class Missile : public AEntity
{
public:
	Missile(irr::IrrlichtDevice *device, irr::core::vector2df pos,
		float angle, float size);
	void move();
	void process(std::vector<AEntity *> &entities);
	void setAngle(irr::f32 angle);
	void draw(irr::IrrlichtDevice *device) override;
	bool isOver();
private:
	irr::ITimer *timer;
	irr::u32 spawnTime;
	irr::scene::IParticleSystemSceneNode	*_particleSystem;
	irr::scene::IParticleEmitter		*_emitter;
	irr::scene::IParticleAffector           *_affector;
	bool _isOver;
};


#endif //DUNGEON_MISSILE_HPP
