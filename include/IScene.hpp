#ifndef ISCENE_HPP_
#define ISCENE_HPP_

#include <irrlicht/irrlicht.h>
#include <EventManager.hpp>
#include <unistd.h>

enum _ACTION {
	START_GAME,
        NEXT_SCENE,
        PREV_SCENE,
	BACK_MAINMENU,
	OPTIONS,
	EXIT_APP,
};

class IScene {
	public:
		virtual			~IScene() = default;
		virtual void		init(irr::IrrlichtDevice *window, EventManager *eventmanager) = 0;
		virtual _ACTION		run() = 0;
		virtual void		processEvents(_EVENTS events) = 0;
		virtual bool		isRunning() const = 0;
		virtual void		quit() = 0;
};

#endif