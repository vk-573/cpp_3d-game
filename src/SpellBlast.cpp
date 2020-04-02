#include "SpellBlast.hpp"

SpellBlast::SpellBlast(irr::IrrlichtDevice *device, AEntity *player, const int &tileSize, IMap *map) : ASpell(device, tileSize, 0.20, map)
{
        _particleSystem = _device->getSceneManager()->addParticleSystemSceneNode(true);
        setPlayer(player);
	_emitter = _particleSystem->createBoxEmitter(
		irr::core::aabbox3d<irr::f32>(0,    0, 0,
		    				5, 5, 5), // coordonnees de la boite
    		irr::core::vector3df(-0.2f,0,0),        // direction de diffusion
    		160,240,                                       // nb particules emises a la sec min / max
    		irr::video::SColor(0,20,30,200),                  // couleur la plus sombre
    		irr::video::SColor(0,40,40,250),            // couleur la plus claire
    		60, 80,                                    // duree de vie min / max
    		0,                                          // angle max d'ecart / direction prevue
    		irr::core::dimension2df(1.0f,3.0f),           // taille minimum
    		irr::core::dimension2df(4.0f,4.0f));
	_affector =    // creation du modificateur
    		_particleSystem->createFadeOutParticleAffector(
    		irr::video::SColor(0,8,6,30),             // la couleur finale
    		200);                                   // temps necessaire a la modification
		_particleSystem->addAffector(_affector);       // ajout du modificateur au particle system
	_affector->drop();                           // on attache l'emetteur
	// _particleSystem->setEmitter(_emitter);
	_particleSystem->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	_particleSystem->setVisible(true);
	_particleSystem->setPosition(irr::core::vector3df(_player->getPos().X * _tileSize, 20, -_player->getPos().Y * _tileSize));
        setCorrectState();
}

SpellBlast::~SpellBlast()
{
	_particleSystem->setVisible(false);
        _particleSystem->removeAll();
        // _particleSystem->drop();
}

void         SpellBlast::setCorrectState() {
        irr::f32 tmp = _player->getAngle();
        _particleSystem->setPosition(irr::core::vector3df(_player->getPos().X * _tileSize, 20, -_player->getPos().Y * _tileSize));

        //RIGHT
        if (tmp == 0) {
                setAngle(_ANGLE_RIGHT);
                _emitter->setDirection(irr::core::vector3df(-0.2f,0,0));
                _particleSystem->setPosition(irr::core::vector3df(_player->getPos().X * _tileSize -2, 20, -_player->getPos().Y * _tileSize + 6));
        }
        //RIGHT DOWN
        else if (tmp == 45) {
                setAngle(_ANGLE_RIGHTDOWN);
                _emitter->setDirection(irr::core::vector3df(-0.2f,0,0.2f));
                _particleSystem->setPosition(irr::core::vector3df(_player->getPos().X * _tileSize -5, 20, -_player->getPos().Y * _tileSize));
        }
        // DOWN
        else if (tmp == 90) {
                setAngle(_ANGLE_DOWN);
                _emitter->setDirection(irr::core::vector3df(0,0,0.2f));
                _particleSystem->setPosition(irr::core::vector3df(_player->getPos().X * _tileSize -12, 20, -_player->getPos().Y * _tileSize - 4));
        }
        //DOWN LEFT
        else if (tmp == -225) {
                setAngle(_ANGLE_DOWNLEFT);
                _emitter->setDirection(irr::core::vector3df(0.2f,0,0.2f));
                _particleSystem->setPosition(irr::core::vector3df(_player->getPos().X * _tileSize -20, 20, -_player->getPos().Y * _tileSize) - 4);
        }
        //LEFT
        else if (tmp == -180) {
                setAngle(_ANGLE_LEFT);
                _emitter->setDirection(irr::core::vector3df(0.2f,0,0));
                _particleSystem->setPosition(irr::core::vector3df(_player->getPos().X * _tileSize -12, 20, -_player->getPos().Y * _tileSize + 6));

        }
        //LEFT UP
        else if (tmp == -135) {
                setAngle(_ANGLE_LEFTUP);
                _emitter->setDirection(irr::core::vector3df(0.2f,0,-0.2f));
                _particleSystem->setPosition(irr::core::vector3df(_player->getPos().X * _tileSize -15, 20, -_player->getPos().Y * _tileSize + 12));
        }
        //UP
        else if (tmp == -90) {
                setAngle(_ANGLE_UP);
               _emitter->setDirection(irr::core::vector3df(0,0,-0.2f));
                _particleSystem->setPosition(irr::core::vector3df(_player->getPos().X * _tileSize -12, 20, -_player->getPos().Y * _tileSize + 15));

        }
        //UP RIGHT
        else if (tmp == -45) {
                setAngle(_ANGLE_RIGHTUP);
                _emitter->setDirection(irr::core::vector3df(-0.2f,0,-0.2f));
                _particleSystem->setPosition(irr::core::vector3df(_player->getPos().X * _tileSize -5, 20, -_player->getPos().Y * _tileSize + 15));

        }
        _emitter->setMaxAngleDegrees(1);
	_particleSystem->setEmitter(_emitter);
        _emitter->drop();
}
