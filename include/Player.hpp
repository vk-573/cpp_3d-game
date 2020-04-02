/*
** EPITECH PROJECT, 2018
** Player
** File description:
** Declaration of Player
*/

#ifndef DUNGEON_PLAYER_HPP
#define DUNGEON_PLAYER_HPP

#include <irrlicht/irrlicht.h>
#include "IMap.hpp"
// #include "AEntity.hpp"
#include "SpellBlast.hpp"
#include "Attack.hpp"
#include <vector>


class Player : public AEntity
{
public:
	Player(irr::IrrlichtDevice *device, const irr::core::vector2df &pos, irr::ITimer *timer, const int &tilesize);
	~Player();
	void		attack();
	void		attackSpell();
	void		process(std::vector<AEntity *> &entities) override;
	int		getHP() const;
	int		getHPmax() const;
	int		getMP() const;
	int		getMPmax() const;
	float		getSpellspeed() const;
	float		getSpellCD() const;
	int		getSpellDamage() const;
	float		getAttackSpeed() const;
	float		getAttackCD() const;
	int		getAttackDamage() const;
	void		setHUD();
	void 		damage(int damage);
	void		setMap(IMap *map);
	bool		isDying() const;

private:
	void		manaRegen(irr::u32 tmp);
	void		useMana(const int &mp);
	void		checkState();
	void		updateSpell();
	void		updateAttack();
	void		castAttack();
	void		processDeath(const irr::u32 &tmp);
	void		die();
	IMap 		*_map;
	std::vector<ASpell*> _Spells;
	float		_spellCD;
	float		_spellSpeed;
	float		_spellAnimationSpeed;
	int		_spellDamage;
	Attack		*_attack;
	bool		_attacking = false;
	float		_attackCD;
	float		_attackSpeed;
	float		_attackAnimationSpeed;
	int		_attackDamage;
	int		_hpMax;
	int		_hp;
	int		_mpMax;
	int		_mp;
	float		_hpRegen;
	float		_mpRegen;
	irr::ITimer	*_timer;
	irr::u32	_mpRegenTimer;
	irr::u32	_attackCDTimer;
	irr::u32	_attackAnimationTimer;
	irr::u32	_spellCDTimer;
	irr::u32	_spellAnimationTimer;
	bool		_manaFull;
	int		_tileSize;
	ASpell		*_spell;
	//HUD
	void		changeStaticText(irr::gui::IGUIStaticText *text, const std::string &str);
	void		updateHUD();
	void		updateMPHUD();
	void		updateHPHUD();
	void		updateCastHUD();
	void		showCast();
	void		hideCast();
	irr::gui::IGUIEnvironment	*_env;
	irr::gui::IGUIStaticText	*_pHpText;
	irr::gui::IGUIStaticText	*_pMpText;
	irr::gui::IGUIStaticText	*_attCDText;
	irr::gui::IGUIStaticText	*_splCDText;
	irr::gui::IGUIStaticText	*_mpRegenText;
	irr::gui::IGUIStaticText	*_castText;
	irr::gui::IGUIImage		*_hpBar;
	irr::gui::IGUIImage		*_mpBar;
	irr::gui::IGUIImage		*_castBar;
	irr::gui::IGUIImage		*_castEnergy;

	//Paritcules
	irr::scene::IParticleSystemSceneNode	*_particleSystem;
	irr::scene::IParticleEmitter		*_emitter;
};


#endif //DUNGEON_PLAYER_HPP
