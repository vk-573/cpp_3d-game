#include "Attack.hpp"

Attack::Attack(irr::IrrlichtDevice *device, AEntity *player, const int &tileSize, IMap *map)
{
	_device = device;
        _tileSize = tileSize;
        _player = player;
        _map = map;
        _damage = 20;
        _timer = _device->getTimer();
        _particleSystem = _device->getSceneManager()->addParticleSystemSceneNode(true);
        setPlayer(player);
	_emitter = _particleSystem->createBoxEmitter(
		irr::core::aabbox3d<irr::f32>(0,    0, 0,
		    				20, 5, 5), // coordonnees de la boite
    		irr::core::vector3df(0,0,-0.2f),        // direction de diffusion
    		150,150,                                       // nb particules emises a la sec min / max
    		irr::video::SColor(250,0,50,0),                  // couleur la plus sombre
    		irr::video::SColor(250,250, 0, 0),            // couleur la plus claire
    		10, 11,                                    // duree de vie min / max
    		0,                                          // angle max d'ecart / direction prevue
    		irr::core::dimension2df(40.0f,5.0f),           // taille minimum
    		irr::core::dimension2df(40.0f,5.0f));
        // irr::scene::IParticleRingEmitter *ringEmitter =  _particleSystem->createRingEmitter(
        //         irr::core::vector3df(10, 5, 10.0), //Center;
        //         50, //radius
        //         10, //thickness
        //         irr::core::vector3df(0.0f, 0.03f, 0.0f), // direction
        //         5, // min per second
        //         10, // max per second
        //         irr::video::SColor(255, 0, 0, 0), // min color
        //         irr::video::SColor(255, 255, 255, 255), // max color
        //         2000, // min lifetime
        //         4000, // max lifetime
        //         0, // max angle degress
        //         irr::core::dimension2df(5.0f, 5.0f), // min size
        //         irr::core::dimension2df(5.0f, 5.0f) // max size
        // );
	// _particleSystem->setEmitter(ringEmitter);
	// _affector =    // creation du modificateur

    	// _particleSystem->createFadeOutParticleAffector(
    	// 	irr::video::SColor(0,8,6,30),             // la couleur finale
    	// 200);                                   // temps necessaire a la modification
	// _particleSystem->addAffector(_affector);       // ajout du modificateur au particle system
	// _affector->drop();                           // on attache l'emetteur
	// _emitter->drop();                           
	_particleSystem->setMaterialFlag(irr::video::EMF_LIGHTING, false);
        _particleSystem->setMaterialType(irr::video::EMT_TRANSPARENT_ALPHA_CHANNEL);
	_particleSystem->setVisible(true);
        _particleSystem->setMaterialTexture(0, _device->getVideoDriver()->getTexture("./resources/textures/slash.png"));
        setCorrectState();
        _duration = 200;
        _tmp = _timer->getTime();
}

Attack::~Attack()
{
	_particleSystem->setVisible(false);
        _particleSystem->removeAll();
}

void            Attack::setPlayer(AEntity *player) {
        _player = player;
}

const irr::core::vector3df &Attack::getPos() const
{
	return _particleSystem->getPosition();
}

void Attack::setPos(const irr::core::vector2df &pos)
{
	_particleSystem->setPosition(irr::core::vector3df(pos.X * _tileSize - 10, 0, -pos.Y *_tileSize + 10));
}

_ANGLE          Attack::getAngle() const
{
	return _angle;
}

void            Attack::setAngle(const _ANGLE &angle)
{
        _angle = angle;
}


bool           Attack::update() {
        if(_timer->getTime() - _tmp > _duration) {
                // puts("attack return false;");
                return false;
        }
        return true;
}

void         Attack::setCorrectState() {
        irr::f32 tmp = _player->getAngle();
        _particleSystem->setPosition(irr::core::vector3df(_player->getPos().X * _tileSize, 20, -_player->getPos().Y * _tileSize));

        //RIGHT
        if (tmp == 0) {
                setAngle(_ANGLE_RIGHT);
                _emitter->setDirection(irr::core::vector3df(0.2f,0,0));
                // _particleSystem->setRotation(irr::core::vector3df(90,90, 90));
                _particleSystem->setPosition(irr::core::vector3df(_player->getPos().X * _tileSize -5, 20, -_player->getPos().Y * _tileSize));
                _particleSystem->setMaterialTexture(0, _device->getVideoDriver()->getTexture("./resources/textures/slashRight.png"));
                _emitter->setMinStartSize(irr::core::dimension2df(5,40));
                _emitter->setMaxStartSize(irr::core::dimension2df(5,40));
        }
        //RIGHT DOWN
        else if (tmp == 45) {
                setAngle(_ANGLE_RIGHTDOWN);
                _emitter->setDirection(irr::core::vector3df(0.2f,0,-0.2f));
                _particleSystem->setPosition(irr::core::vector3df(_player->getPos().X * _tileSize - 10, 20, -_player->getPos().Y * _tileSize - 4));
        }
        // DOWN
        else if (tmp == 90) {
                setAngle(_ANGLE_DOWN);
                _particleSystem->setPosition(irr::core::vector3df(_player->getPos().X * _tileSize -14, 20, -_player->getPos().Y * _tileSize - 6));
                _emitter->setDirection(irr::core::vector3df(0,0,-0.2f));
        }
        //DOWN LEFT
        else if (tmp == -225) {
                setAngle(_ANGLE_DOWNLEFT);
                _emitter->setDirection(irr::core::vector3df(-0.2f,0,-0.2f));
                _particleSystem->setPosition(irr::core::vector3df(_player->getPos().X * _tileSize -20, 20, -_player->getPos().Y * _tileSize - 4));
        }
        //LEFT
        else if (tmp == -180) {
                setAngle(_ANGLE_LEFT);
                _emitter->setDirection(irr::core::vector3df(-0.2f,0,0));
                _particleSystem->setMaterialTexture(0, _device->getVideoDriver()->getTexture("./resources/textures/slashLeft.png"));
                _particleSystem->setPosition(irr::core::vector3df(_player->getPos().X * _tileSize -30, 20, -_player->getPos().Y * _tileSize));
                _emitter->setMinStartSize(irr::core::dimension2df(5,40));
                _emitter->setMaxStartSize(irr::core::dimension2df(5,40));
        }
        //LEFT UP
        else if (tmp == -135) {
                setAngle(_ANGLE_LEFTUP);
                _emitter->setDirection(irr::core::vector3df(-0.2f,0,0.2f));
                _particleSystem->setPosition(irr::core::vector3df(_player->getPos().X * _tileSize -20, 20, -_player->getPos().Y * _tileSize));
                _particleSystem->setMaterialTexture(0, _device->getVideoDriver()->getTexture("./resources/textures/slash180.png"));
        }
        //UP
        else if (tmp == -90) {
                setAngle(_ANGLE_UP);
                _particleSystem->setPosition(irr::core::vector3df(_player->getPos().X * _tileSize -20, 20, -_player->getPos().Y * _tileSize + 10));
                _emitter->setDirection(irr::core::vector3df(0,0,0.2f));
                _particleSystem->setMaterialTexture(0, _device->getVideoDriver()->getTexture("./resources/textures/slash180.png"));

        }
        //UP RIGHT
        else if (tmp == -45) {
                setAngle(_ANGLE_RIGHTUP);
                _particleSystem->setPosition(irr::core::vector3df(_player->getPos().X * _tileSize -10, 20, -_player->getPos().Y * _tileSize));
                _particleSystem->setMaterialTexture(0, _device->getVideoDriver()->getTexture("./resources/textures/slash180.png"));
                _emitter->setDirection(irr::core::vector3df(0.2f,0,0.2f));

        }
        _emitter->setMaxAngleDegrees(1);
	_particleSystem->setEmitter(_emitter);
        _emitter->drop();
        checkHitEnemy();
}

void    Attack::checkHitEnemy() {
        irr::core::vector2df tmp = _player->getPos();
        // std::cout << "tmp.X :" << tmp.X << std::endl;
        // std::cout << "tmp.Y :" << tmp.Y << std::endl;
        tmp.X = (int) tmp.X;
        tmp.Y = (int) tmp.Y;
        // std::cout << "tmp.X :" << tmp.X << std::endl;
        // std::cout << "tmp.Y :" << tmp.Y << std::endl;
        for (auto &enemy : _map->getEnnemies()) {
                if (enemy->isDead()) {
                        continue;
                }
                irr::core::vector2df tmpE = enemy->getPos();
                tmpE.X = (int) tmpE.X;
                tmpE.Y = (int) tmpE.Y;
                if (_angle == _ANGLE_UP) {
                        if ((tmp.X - 1 == tmpE.X && tmp.Y - 1 == tmpE.Y) ||
                                (tmp.X == tmpE.X && tmp.Y - 1 == tmpE.Y) || 
                                (tmp.X + 1 == tmpE.X && tmp.Y - 1 == tmpE.Y)) {
                                enemy->gotHit(_damage);
                        }
                }
                else if (_angle == _ANGLE_RIGHTUP) {
                        if ((tmp.X  == tmpE.X && tmp.Y - 1 == tmpE.Y) ||
                                (tmp.X + 1 == tmpE.X && tmp.Y - 1 == tmpE.Y) || 
                                (tmp.X + 2 == tmpE.X && tmp.Y - 1 == tmpE.Y)) {
                                enemy->gotHit(_damage);
                        }
                }
                else if (_angle == _ANGLE_RIGHT) {
                        if ((tmp.X + 1 == tmpE.X && tmp.Y - 1 == tmpE.Y) ||
                                (tmp.X + 1 == tmpE.X && tmp.Y == tmpE.Y) || 
                                (tmp.X + 1 == tmpE.X && tmp.Y + 1 == tmpE.Y)) {
                                enemy->gotHit(_damage);
                        }
                }
                else if (_angle == _ANGLE_RIGHTDOWN) {
                        if ((tmp.X == tmpE.X && tmp.Y + 1 == tmpE.Y) ||
                                (tmp.X + 1 == tmpE.X && tmp.Y + 1 == tmpE.Y) || 
                                (tmp.X + 2 == tmpE.X && tmp.Y + 1 == tmpE.Y)) {
                                enemy->gotHit(_damage);
                        }
                }
                else if (_angle == _ANGLE_DOWN) {
                        if ((tmp.X - 1 == tmpE.X && tmp.Y + 1 == tmpE.Y) ||
                                (tmp.X == tmpE.X && tmp.Y + 1 == tmpE.Y) || 
                                (tmp.X + 1 == tmpE.X && tmp.Y + 1 == tmpE.Y)) {
                                enemy->gotHit(_damage);
                        }
                }
                else if (_angle == _ANGLE_DOWNLEFT) {
                        if ((tmp.X - 2 == tmpE.X && tmp.Y + 1 == tmpE.Y) ||
                                (tmp.X - 1 == tmpE.X && tmp.Y + 1 == tmpE.Y) || 
                                (tmp.X == tmpE.X && tmp.Y + 1 == tmpE.Y)) {
                                enemy->gotHit(_damage);
                        }
                }
                else if (_angle == _ANGLE_LEFT) {
                        if ((tmp.X - 1 == tmpE.X && tmp.Y - 1 == tmpE.Y) ||
                                (tmp.X - 1 == tmpE.X && tmp.Y == tmpE.Y) || 
                                (tmp.X - 1== tmpE.X && tmp.Y + 1 == tmpE.Y)) {
                                enemy->gotHit(_damage);
                        }
                }
                else if (_angle == _ANGLE_LEFTUP) {
                        if ((tmp.X - 2 == tmpE.X && tmp.Y - 1 == tmpE.Y) ||
                                (tmp.X - 1 == tmpE.X && tmp.Y - 1== tmpE.Y) || 
                                (tmp.X == tmpE.X && tmp.Y - 1 == tmpE.Y)) {
                                enemy->gotHit(_damage);
                        }
                }
        }
}