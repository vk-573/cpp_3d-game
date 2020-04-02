#ifndef ASPELL_HPP
#define ASPELL_HPP

#include <irrlicht/irrlicht.h>
#include "AEntity.hpp"
#include "IMap.hpp"

enum _ANGLE {
	_ANGLE_UP,
	_ANGLE_RIGHTUP,
	_ANGLE_RIGHT,
	_ANGLE_RIGHTDOWN,
	_ANGLE_DOWN,
	_ANGLE_DOWNLEFT,
	_ANGLE_LEFT,
	_ANGLE_LEFTUP,
};

class ASpell
{
	public:
		
		ASpell(irr::IrrlichtDevice *device, const int &tileSize, const float &speed, IMap *map);
		virtual ~ASpell();
		const irr::core::vector3df &getPos() const;
                void                    setPlayer(AEntity *player);
		void                    setPos(const irr::core::vector2df &pos);
		_ANGLE                  getAngle() const;
		void                    setAngle(const _ANGLE &angle);
		irr::f32                getSpeed() const;
		void                    setSpeed(irr::f32 speed);
                bool                    update();
	protected:
                bool                    updatePosition();
		irr::IrrlichtDevice     *_device;
                AEntity                  *_player;
		IMap			*_map;
                irr::scene::IParticleSystemSceneNode	*_particleSystem;
	        irr::scene::IParticleEmitter		*_emitter;
                irr::scene::IParticleAffector           *_affector;
		irr::core::vector2df    _pos;
		irr::f32                _speed;
		_ANGLE                 _angle;
                int                     _tileSize;
};


#endif
