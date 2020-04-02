#include "ASpell.hpp"

ASpell::ASpell(irr::IrrlichtDevice *device, const int &tileSize, const float &speed, IMap *map)
{
	_device = device;
        _tileSize = tileSize;
        _speed = speed;
        _map = map;
}

ASpell::~ASpell()
{

}

void            ASpell::setPlayer(AEntity *player) {
        _player = player;
}

const irr::core::vector3df &ASpell::getPos() const
{
	return _particleSystem->getPosition();
}

void ASpell::setPos(const irr::core::vector2df &pos)
{
	_particleSystem->setPosition(irr::core::vector3df(pos.X * _tileSize - 10, 0, -pos.Y *_tileSize + 10));
}

_ANGLE          ASpell::getAngle() const
{
	return _angle;
}

void            ASpell::setAngle(const _ANGLE &angle)
{
        _angle = angle;
}

irr::f32        ASpell::getSpeed() const
{
	return _speed;
}

void            ASpell::setSpeed(irr::f32 speed)
{
	 _speed = speed;
}

bool            ASpell::update() {
        return updatePosition();
}

bool            ASpell::updatePosition() {
        irr::core::vector3df tmp = _particleSystem->getPosition();
        if (_map->getTile(tmp.X / _tileSize, -tmp.Z / _tileSize)->getType() != Tile::FLOOR) {
                return false;
        }
        //Diag = 4/Pi where x && y = V2/2 = 0.701
        if (_angle == _ANGLE_UP) {
	        _particleSystem->setPosition(irr::core::vector3df(tmp.X, 20, tmp.Z + (_tileSize * _speed)));
        }
        else if (_angle == _ANGLE_RIGHTUP) {
	        _particleSystem->setPosition(irr::core::vector3df(tmp.X + (_tileSize * _speed * 0.70), 20, tmp.Z + (_tileSize * _speed * 0.70)));
        }
        else if (_angle == _ANGLE_RIGHT) {
	        _particleSystem->setPosition(irr::core::vector3df(tmp.X + (_tileSize * _speed), 20, tmp.Z));
        }
        else if (_angle == _ANGLE_RIGHTDOWN) {
	        _particleSystem->setPosition(irr::core::vector3df(tmp.X + (_tileSize * _speed * 0.70), 20, tmp.Z - (_tileSize * _speed * 0.70)));
        }
        else if (_angle == _ANGLE_DOWN) {
	        _particleSystem->setPosition(irr::core::vector3df(tmp.X, 20, tmp.Z - (_tileSize * _speed)));
        }
        else if (_angle == _ANGLE_DOWNLEFT) {
	        _particleSystem->setPosition(irr::core::vector3df(tmp.X - (_tileSize * _speed * 0.70), 20, tmp.Z - (_tileSize * _speed * 0.70)));
        }
        else if (_angle == _ANGLE_LEFT) {
	        _particleSystem->setPosition(irr::core::vector3df(tmp.X - (_tileSize * _speed), 20, tmp.Z));
        }
        else if (_angle == _ANGLE_LEFTUP) {
	        _particleSystem->setPosition(irr::core::vector3df(tmp.X - (_tileSize * _speed * 0.70), 20, tmp.Z + (_tileSize * _speed * 0.70)));
        }
        tmp = _particleSystem->getPosition();
        tmp.X = (int) tmp.X / _tileSize;
        tmp.Z = (int) tmp.Z / _tileSize;
        for (auto &enemy : _map->getEnnemies()) {
                if (!enemy->isDead()) {
                        irr::core::vector2df tmpE = enemy->getPos();
                        tmpE.X = (int) tmpE.X;
                        tmpE.Y = (int) tmpE.Y;
                        if (tmp.X + 1== tmpE.X && tmp.Z == -tmpE.Y) {
                                enemy->gotHit(40);
                                return false;
                        }
                }
        }
        return true;
}