#ifndef MENU_SCENE_HPP
#define MENU_SCENE_HPP

#include <vector>
#include "IScene.hpp"

enum	arrowPosition {
	_arrPLAY = 0,
	_arrOPTIONS = 1,
	_arrQUIT = 2,
};

class MenuScene : public IScene
{
	public:
		MenuScene();
		~MenuScene();
		void		init(irr::IrrlichtDevice *window, EventManager *eventmanager);
		_ACTION 	run();
		void		quit();
		void		processEvents(_EVENTS events);
		bool		isRunning() const;
private:
		void            display();
		void		startGame();
		void		goToOptions();
                void            processUp();
                void            processDown();
                void            processLeft();
                void            processRight();
                void            processEnter();
		void		setTextures();
		void		stopScene();
		irr::IrrlichtDevice 		*_device;
		irr::video::IVideoDriver	*_driver;
		EventManager 			*_eventManager;
		irr::scene::ISceneManager	*_smgr;
		irr::gui::IGUIEnvironment	*_env;
		irr::gui::IGUIImage		*_arrow;
		arrowPosition			_arrowPos;
		irr::scene::ICameraSceneNode 	*_camera;
		std::vector<irr::scene::ILightSceneNode *> ambientLights;
		bool 				_isRunning;
		_ACTION				_exit_action;
};


#endif