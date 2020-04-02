#ifndef SPELLBLAST_HPP
#define SPELLBLAST_HPP

#include "ASpell.hpp"


class SpellBlast : public ASpell
{
	public:
		SpellBlast(irr::IrrlichtDevice *device, AEntity *player, const int &tileSize, IMap *map);
		virtual ~SpellBlast();
	private:
                // irr::core::vector3df	getCorrectAngle();
		void			setCorrectState();
};


#endif