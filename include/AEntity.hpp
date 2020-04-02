/*
** EPITECH PROJECT, 2018
** AEntity
** File description:
** Declaration of AEntity
*/

#ifndef DUNGEON_AENTITY_HPP
#define DUNGEON_AENTITY_HPP

#include <irrlicht/irrlicht.h>
#include <string>
#include <vector>
#include <iostream>
#include "SoundManager.hpp"

class AEntity
{
	public:
		enum State {
			IDLE,
			RUNNING,
			INTERACTION,
			ATTACK,
			ATTACKSPELL,
			DAMAGED
		};
		AEntity(irr::IrrlichtDevice *device, const std::string &model, const std::string &texture,
			const irr::core::vector2df &pos, const irr::f32 size);
		virtual ~AEntity();
		virtual void process(std::vector<AEntity *> &entities) = 0;
		const irr::core::vector2df &getPos() const;
		const irr::core::vector3df &getMeshPos() const;
		void setPos(const irr::core::vector2df &pos, const int tileSize = 20);
		irr::f32 getAngle() const;
		void setAngle(irr::f32 angle);
		irr::f32 getSpeed() const;
		void setSpeed(irr::f32 speed);
		irr::f32 getSize() const;
		void setSize(irr::f32 size);
		State getState() const;
		void setState(State status);
		AEntity	&getThis();
		virtual void draw(irr::IrrlichtDevice *device);
		void clear();
		const std::string &getModelString() const;
		bool		isDead() const;
		bool		isDying() const;
		void	gotHit(const int &damage);
protected:
		irr::IrrlichtDevice 		*_device;
		irr::scene::IAnimatedMesh *animatedMesh;
		irr::scene::IAnimatedMeshSceneNode *animatedMeshSceneNode;
		irr::core::vector2df pos;
		irr::f32 angle;
		irr::f32 speed;
		irr::f32 size;
		std::string model;
		std::string texture;
		State state;
		bool		_dead = false;
		bool		_isDying = false;
		int	_hp;
		irr::u32	_deathTimer;
};


#endif //DUNGEON_AENTITY_HPP
