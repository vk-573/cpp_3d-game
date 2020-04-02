/*
** EPITECH PROJECT, 2018
** GameApplication
** File description:
** Implementation of GameApplication
*/

#include "GameApplication.hpp"

GameApplication::GameApplication() : _window(NULL)
{
	_eventManager = new EventManager();
}

GameApplication::~GameApplication()
{
	delete _eventManager;
	for (auto s : _Scenes) {
		// delete s;
	}
}

void GameApplication::init(int width, int height)
{
	_window = irr::createDevice(video::EDT_OPENGL, core::dimension2d<u32>(width, height), 16, 0, true, true, _eventManager);

	// IScene *scene = new Scene();
	IScene *menuScene = new MenuScene();
	_Scenes.push_back(menuScene);
	_Scenes.push_back(NULL);
	// _Scenes.push_back(scene);
}

void GameApplication::start()
{

	_isRunning = true;
	_currentScene = _Scenes[0];
	SoundManager::playMusic("title.wav");

	while (isRunning()) {
		_currentScene->init(_window, _eventManager);
		_ACTION action = _currentScene->run();
		switch (action) {
			case START_GAME: 	startGameScene();
						break;

			case OPTIONS:		options();
						break;

			case NEXT_SCENE:	nextScene();
						break;

			case PREV_SCENE:	prevScene();
						break;

			case BACK_MAINMENU:	backMainMenu();
						break;

			case EXIT_APP: 		quit();
						break;
			default: quit();
		}
	}
}

void		GameApplication::startGameScene() {
		IScene *scene = new Scene();
		_Scenes[1] = scene;
		_currentScene = _Scenes[1];
		std::cout << "startin game scene" << std::endl;

}

void		GameApplication::nextScene() {

}

void		GameApplication::prevScene() {

}

void		GameApplication::options() {

}

void		GameApplication::backMainMenu() {
	_currentScene = _Scenes[0];
}

bool		GameApplication::isRunning() const {
	return _isRunning;
}

void		GameApplication::quit() {
	_isRunning = false;
	_window->closeDevice();
}