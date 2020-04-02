/*
** EPITECH PROJECT, 2018
** Player
** File description:
** Implementation of Player
*/

#include "Player.hpp"

Player::Player(irr::IrrlichtDevice *device, const irr::core::vector2df &pos, irr::ITimer *timer, const int &tileSize)
: AEntity(device, "resources/model.md2", "resources/skin.png", pos, 0.6)
{
	_env = device->getGUIEnvironment();
	_timer = timer;
	setSpeed(0.05);
	_hp = 100;
	_hpMax = 100;
	_mp = 90;
	_mpMax = 100;
	_spellCD = 4;
	_attackCD = 1.4;
	_mpRegen = 1;
	_attackCDTimer = 0;
	_attackAnimationSpeed = 0.2;
	_attackAnimationTimer = 0;
	_spellCDTimer = 0;
	_spellAnimationSpeed = 1;
	_spellAnimationTimer = _timer->getTime() - _spellAnimationSpeed * 1000;
	_mpRegenTimer = 0;
	_manaFull = false;
	state = IDLE;
	_tileSize = tileSize;
	_spell = NULL;
}

Player::~Player()
{
	// puts("EHHEHEEH");
	for (auto &spell : _Spells) {
		if (spell) {
			delete spell;
		}
	}
}

void		Player::showCast() {
	_castBar->setVisible(true);
	_castText->setVisible(true);
	_castEnergy->setVisible(true);
}

void		Player::hideCast() {
	_castBar->setVisible(false);
	_castEnergy->setVisible(false);
	_castText->setVisible(false);
}

void		Player::setHUD() {
	_env->addImage(_device->getVideoDriver()->getTexture("./media/lifeBar.png"), irr::core::position2d<int>(0,0));
	_hpBar = _env->addImage(_device->getVideoDriver()->getTexture("./media/hpBar.png"), irr::core::position2d<int>(12,7));
	_mpBar = _env->addImage(_device->getVideoDriver()->getTexture("./media/mpBar.png"), irr::core::position2d<int>(12,39));
	_castBar = _env->addImage(_device->getVideoDriver()->getTexture("./media/castBar.png"), irr::core::position2d<int>(642,820));
	_castEnergy = _env->addImage(_device->getVideoDriver()->getTexture("./media/energyCast.png"), irr::core::position2d<int>(645,823));
	_pHpText = _env->addStaticText(L"100 / 1zer00", irr::core::rect<irr::s32>(230,14,280,32), false, false);
	_pHpText->setOverrideColor(irr::video::SColor(255, 255, 255,255));
	_pMpText = _env->addStaticText(L"100 / 100", irr::core::rect<irr::s32>(230,46,280,80), false, false);
	_pMpText->setOverrideColor(irr::video::SColor(255, 255, 255,255));
	_mpRegenText = _env->addStaticText(L"regen: 1 / sec", irr::core::rect<irr::s32>(550,46,680,60), false, false);
	_mpRegenText->setOverrideColor(irr::video::SColor(255, 255, 255,255));
	_attCDText = _env->addStaticText(L"ATTACK CD: READY", irr::core::rect<irr::s32>(30,100,280,180), false, false);
	_attCDText->setOverrideColor(irr::video::SColor(255, 255, 255,255));
	_splCDText = _env->addStaticText(L"SPELL CD: READY", irr::core::rect<irr::s32>(30,120,280,280), false, false);
	_splCDText->setOverrideColor(irr::video::SColor(255, 255, 255,255));
	_castText = _env->addStaticText(L"Attack", irr::core::rect<irr::s32>(780,824,900,880), false, false);
	_castText->setOverrideColor(irr::video::SColor(255, 200, 200,220));
	std::string str;
	str = std::to_string(_hp) + " / " + std::to_string(_hpMax);
	changeStaticText(_pHpText, str);
	str = std::to_string(_mp) + " / " + std::to_string(_mpMax);
	changeStaticText(_pMpText, str);
	_mpBar->setMaxSize(irr::core::dimension2du((float)_mp / (float)_mpMax * 479, 26));
	_hpBar->setMaxSize(irr::core::dimension2du((float)_hp / (float)_hpMax * 479, 26));
	hideCast();
}

void		Player::changeStaticText(irr::gui::IGUIStaticText *text, const std::string &str) {
	std::wstring tmp(L"                                                     ");
	for (unsigned int i = 0; i < tmp.size(); i++) {
		tmp[i] = str[i];
	}
	text->setText(tmp.c_str());
}

void		Player::updateHUD() {
	irr::u32 tmp = _timer->getTime();
	if (state == ATTACK) {
		std::string str("ATTACK CAST");
		changeStaticText(_castText, str);
		irr::u32	currentTime = (_timer->getTime() - _attackAnimationTimer);
		_castEnergy->setMaxSize(irr::core::dimension2du(((currentTime / (_attackAnimationSpeed * 1000)) * 309) , 10));
	}
	if (state == ATTACKSPELL) {
		std::string str("SPELL CAST");
		changeStaticText(_castText, str);
		irr::u32	currentTime = (_timer->getTime() - _spellAnimationTimer);
		_castEnergy->setMaxSize(irr::core::dimension2du(((currentTime / (_spellAnimationSpeed * 1000)) * 309) , 10));
	}
	if(tmp - _attackCDTimer > (_attackCD * 1000)) {
		changeStaticText(_attCDText, "ATTACK CD: READY");
	}
	else {
		changeStaticText(_attCDText, "ATTACK CD: " + std::to_string((int) (_attackCD - (tmp - _attackCDTimer) / 1000 )) + "sec");
	}
	if(tmp - _spellCDTimer > (_spellCD * 1000)) {
		changeStaticText(_splCDText, "SPELL_ CD: READY");
	}
	else {
		changeStaticText(_splCDText, "SPELL_ CD: " + std::to_string((int) (_spellCD - (tmp - _spellCDTimer) / 1000 )) + "sec");
	}
}

void		Player::updateHPHUD() {
	std::string str;
	// std::cout << "hp: " << _hp << std::endl;
	str = std::to_string(_hp) + " / " + std::to_string(_hpMax);
	changeStaticText(_pHpText, str);
	if (_hp) {
		_hpBar->setMaxSize(irr::core::dimension2du((float)_hp / (float)_hpMax * 479, 26));
	}
	else {
		_hpBar->setMaxSize(irr::core::dimension2du(1, 26));
	}

}

void		Player::updateMPHUD() {
	std::string str;
	str = std::to_string(_mp) + " / " + std::to_string(_mpMax);
	changeStaticText(_pMpText, str);
	if (_mp) {
		_mpBar->setMaxSize(irr::core::dimension2du((float)_mp / (float)_mpMax * 479, 26));
	}
	else {
		_mpBar->setMaxSize(irr::core::dimension2du(1, 26));
	}

}

void		Player::updateCastHUD() {

}

void		Player::useMana(const int &mp) {
	_mp -= mp;
	_manaFull = false;
	if (_mp <= 0) {
		_mp = 0;
	}
	updateMPHUD();
}

void		Player::attack() {
	if (state == ATTACK || state == ATTACKSPELL) {
		return;
	}
	irr::u32 tim = _timer->getTime();
	if (tim - _attackCDTimer > (_attackCD * 1000)) {
		std::cout << "ATTACK" << std::endl;
		_attackCDTimer = tim;
		_attackAnimationTimer = tim;
		useMana(1);
		setState(ATTACK);
		showCast();
		SoundManager::playSound("attack.wav");
	}
}

void		Player::attackSpell() {
	if (state == ATTACK || state == ATTACKSPELL) {
		return;
	}
	if (_mp < 8) {
		return;
	}
	irr::u32 tim = _timer->getTime();
	if (tim - _spellCDTimer > (_spellCD * 1000)) {
		std::cout << "SPELL ATTACK" << std::endl;
		_spellCDTimer = tim;
		_spellAnimationTimer = tim;
		useMana(8);
		setState(ATTACKSPELL);
		showCast();
		SoundManager::playSound("attack.wav");
	}
}

void		Player::checkState() {
	irr::u32 tm = _timer->getTime();
	if (state == ATTACK) {
		if (tm - _attackAnimationTimer > (_attackAnimationSpeed * 1000)) {
			_attackAnimationTimer = tm;
			setState(IDLE);
			// puts("ATTACK Launch");
			hideCast();
			updateCastHUD();
			castAttack();
		}
	}
	if (state == ATTACKSPELL) {
		// puts("spell casting");
		if (tm - _spellAnimationTimer > (_spellAnimationSpeed * 1000)) {
			_spellAnimationTimer = tm;
			setState(IDLE);
			// puts("SPELL Launch");
			hideCast();
			updateCastHUD();
			_Spells.push_back(new SpellBlast(_device, &getThis(), _tileSize, _map));
		}
	}
}

void		Player::process(std::vector<AEntity *> &entities) {
	entities = entities;
	irr::u32 tmp = _timer->getTime();
	if (_isDying) {
		processDeath(tmp);
		return;
	}
	//std::cout << "time:" << tmp << std::endl;
	checkState();
	updateHUD();
	updateSpell();
	if (_attacking) {
		updateAttack();
	}
	//_particleSystem->setPosition(irr::core::vector3df(getPos().X *_tileSize - 10, 0, -getPos().Y *_tileSize + 10));
	if (!_manaFull) {
		manaRegen(tmp);
	}
}

void		Player::castAttack() {
	_attacking = true;
	_attack = new Attack(_device, &getThis(), _tileSize, _map);
}

void		Player::updateAttack() {
	if(!_attack) {
		return;
	}
	if(!_attack->update()) {
		_attacking = false;
		delete _attack;
		_attack = NULL;
	}
}

void		Player::updateSpell() {

	// delete spell when touches or done;
	int i = 0;
	for (auto &spell : _Spells) {
		if(spell) {
			if (!spell->update()) {
				delete spell;
				_Spells.erase(_Spells.begin()+i);
				break;
			}
		}
		i++;
	}
}

void		Player::manaRegen(irr::u32 tmp) {
	if (tmp - _mpRegenTimer > (_mpRegen * 1000)) {
		_mpRegenTimer = tmp;
		_mp += 1;
		updateMPHUD();
		if (_mp > _mpMax) {
			_mp = _mpMax;
			_manaFull = true;
		}
	}
}

void		Player::setMap(IMap *map) {
	_map = map;
}

int		Player::getHP() const {
	return _hp;
}

int		Player::getHPmax() const {
	return _hpMax;
}

int		Player::getMP() const {
	return _mp;
}

int		Player::getMPmax() const {
	return _mpMax;
}

float		Player::getSpellspeed() const {
	return _spellSpeed;
}

float		Player::getSpellCD() const {
	return _spellCD;
}

int		Player::getSpellDamage() const {
	return _spellDamage;
}

float		Player::getAttackSpeed() const {
	return _attackSpeed;
}

float		Player::getAttackCD() const {
	return _attackCD;
}

int		Player::getAttackDamage() const {
	return _attackDamage;
}

void		Player::damage(int damage)
{
	if(_isDying) {
		return;
	}
	_hp -= damage;
	if (_hp <= 0) {
		_hp = 0;
		_isDying = true;
		_deathTimer = _timer->getTime();
		animatedMeshSceneNode->setMD2Animation(irr::scene::EMAT_DEATH_FALLBACK);
	}
	setState(DAMAGED);
	updateHPHUD();
	hideCast();
}

void		Player::processDeath(const irr::u32 &tmp) {
	if (tmp - _deathTimer > 1000) {
		die();
	}
}

void		Player::die() {
	_dead = true;
	animatedMeshSceneNode->setVisible(false);
}

bool		Player::isDying() const{
	return _isDying;
}