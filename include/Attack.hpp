#ifndef ATTACK_HPP
#define ATTACK_HPP

#include <irrlicht/irrlicht.h>
#include "ASpell.hpp"

class Attack
{
	public:
		
		Attack(irr::IrrlichtDevice *device, AEntity *player, const int &tileSize, IMap *map);
		~Attack();
		const irr::core::vector3df &getPos() const;
		void                    setPos(const irr::core::vector2df &pos);
                void                    setPlayer(AEntity *player);
		_ANGLE                  getAngle() const;
		void                    setAngle(const _ANGLE &angle);
		void                    setSpeed(irr::f32 speed);
                bool                    update();
	protected:
                // irr::core::vector3df	getCorrectAngle();
                void                    setCorrectState();
		void			checkHitEnemy();
		irr::IrrlichtDevice                     *_device;
                AEntity                                 *_player;
		IMap					*_map;
                irr::scene::IParticleSystemSceneNode	*_particleSystem;
	        irr::scene::IParticleEmitter		*_emitter;
                irr::scene::IParticleAffector           *_affector;
		irr::core::vector2df                    _pos;
		_ANGLE                                  _angle;
                int                                     _tileSize;
        	irr::u32	                        _duration;
        	irr::u32	                        _tmp;
        	irr::ITimer	                        *_timer;
		int					_damage;
};


#endif