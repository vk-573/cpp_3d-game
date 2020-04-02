/*
** EPITECH PROJECT, 2018
** GameApplication
** File description:
** Declaration of GameApplication
*/

#ifndef DUNGEON_GAMEAPPLICATION_HPP
#define DUNGEON_GAMEAPPLICATION_HPP


#include <irrlicht/irrlicht.h>
#include <irrlicht/IrrlichtDevice.h>
#include <string>
#include <iostream>
#include "Scene.hpp"
#include "MenuScene.hpp"

using namespace irr;

class GameApplication
{
	public:
		GameApplication();
		~GameApplication();
		void		init(int width, int height);
		void		start();
		bool		isRunning() const;
		void		quit();
	private:
		void            runScene();
		void		startGameScene();
		void            nextScene();
		void		prevScene();
		void		backMainMenu();
		void		options();
		irr::IrrlichtDevice	*_window;
		bool			_isRunning;
		EventManager 		*_eventManager;
		std::vector<IScene *>   _Scenes;
                IScene                  *_currentScene;
};


#endif //DUNGEON_GAMEAPPLICATION_HPP
