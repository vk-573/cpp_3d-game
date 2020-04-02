/*
** EPITECH PROJECT, 2018
** Scene
** File description:
** Declaration of Scene
*/

#ifndef DUNGEON_SCENE_HPP
#define DUNGEON_SCENE_HPP

#include <vector>
#include <search.h>
#include <cmath>
#include "Map.hpp"
#include "AEntity.hpp"
#include "Player.hpp"
#include "IScene.hpp"
#include <cstdio>
#include <cstdlib>

class Scene : public IScene
{
	public:
		Scene();
		~Scene();
		void		init(irr::IrrlichtDevice *window, EventManager *eventmanager);
		_ACTION 	run();
		void		quit();
		void		processEvents(_EVENTS events);
		void		processPlayer();
		void		processEnemies();
		void 		changeMap(Door::Direction dir);
		bool		isRunning() const;
		void		movePlayer(std::pair<int, int> direction);
		void 		display();
		void		replaceCamera();
private:
		void		setHUD();
		irr::IrrlichtDevice 		*device;
		EventManager 			*_eventManager;
		irr::gui::IGUIEnvironment	*_env;
		irr::video::IVideoDriver	*_driver;
		std::vector<Map *>		mapGrid;
		Map 				map;
		std::vector<AEntity *> 		entities;
		Player				*_player;
		irr::scene::ICameraSceneNode 	*camera;
		std::vector<irr::scene::ILightSceneNode *> ambientLights;
		bool 				_isRunning;
		bool 				shadows;
		_ACTION				_exit_action;
};


#endif //DUNGEON_SCENE_HPP