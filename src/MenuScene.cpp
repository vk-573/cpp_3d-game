#include <iostream>
#include "MenuScene.hpp"

MenuScene::MenuScene() :_isRunning(true)
{
}

MenuScene::~MenuScene()
{
	delete _camera;
}

void MenuScene::init(irr::IrrlichtDevice *window, EventManager *eventmanager)
{
	_device = window;
        _driver = _device->getVideoDriver();
	_eventManager = eventmanager;
        _env = _device->getGUIEnvironment();
	_smgr = _device->getSceneManager();
	_camera = _smgr->addCameraSceneNode(nullptr, irr::core::vector3df(0, 30, -40),
        				  irr::core::vector3df(0, 5, 0));
	_camera->setPosition(irr::core::vector3df(10, -20, 20));
	_camera->setTarget(irr::core::vector3df(10, 15, 20));
	_camera->setFarValue(100000.0f);

	auto light1 = _smgr->addLightSceneNode(nullptr, irr::core::vector3df(10, -50, 0), irr::video::SColorf(0.6f, 0.6f, 0.7f, 0.8f));
	auto light2 = _smgr->addLightSceneNode(nullptr, irr::core::vector3df(-500, 400, 100),irr::video::SColorf(1.0f, 1.0f, 1.0f, 1.0f));
	// if (!shadows) {
	//  	light1->enableCastShadow(false);
	//  	light2->enableCastShadow(false);
	// }
	ambientLights.clear();
	ambientLights.push_back(light1);
	ambientLights.push_back(light2);
	_smgr->setShadowColor(irr::video::SColor(100,0,0,0));
	_exit_action = START_GAME;
        setTextures();
        _arrowPos = _arrPLAY;
}

void            MenuScene::setTextures() {
        _env->addImage(_driver->getTexture("./media/maintitle.png"), irr::core::position2d<int>(400,10));
        _env->addImage(_driver->getTexture("./media/play.png"), irr::core::position2d<int>(1300,300));
        _env->addImage(_driver->getTexture("./media/options.png"), irr::core::position2d<int>(1300,400));
        _env->addImage(_driver->getTexture("./media/quit.png"), irr::core::position2d<int>(1300,500));
        _arrow = _env->addImage(_driver->getTexture("./media/sword_arrow.png"), irr::core::position2d<int>(1175,300));
}

_ACTION		MenuScene::run() {
	_isRunning = true;
	while (_isRunning) {
		_device->run();
		_driver->beginScene(true, true, irr::video::SColor(0, 30, 45, 45));
		display();
		_driver->endScene();
		_eventManager->refresh();
                processEvents(_eventManager->getEvents());
	}
	return _exit_action;
}

void MenuScene::display()
{
	_smgr->setActiveCamera(_camera);
	_smgr->drawAll();
        _env->drawAll();
}

bool MenuScene::isRunning() const
{
	return _isRunning;
}

void MenuScene::processEvents(_EVENTS events)
{

	for (auto action : events) {
		//TODO: implementer les events ici
		if (action.first == EventManager::Action::EXIT && action.second == EventManager::InputType::PRESSED)
			quit();
		else if (action.first == EventManager::Action::MOVE_UP && action.second == EventManager::InputType::PRESSED) {
			processUp();
		}
		else if (action.first == EventManager::Action::MOVE_DOWN && action.second == EventManager::InputType::PRESSED) {
			processDown();
		}
		else if (action.first == EventManager::Action::MOVE_LEFT && action.second == EventManager::InputType::PRESSED) {
			processLeft();
		}
		else if (action.first == EventManager::Action::MOVE_RIGHT && action.second == EventManager::InputType::PRESSED) {
			processRight();
		}
                else if (action.first == EventManager::Action::MOVE_RIGHT && action.second == EventManager::InputType::PRESSED) {
			processRight();
		}
                else if (action.first == EventManager::Action::ENTER && action.second == EventManager::InputType::PRESSED) {
			processEnter();
		}

	}
}

void            MenuScene::processUp() {
        if (_arrowPos != _arrPLAY) {
                _arrowPos = (arrowPosition)((int)_arrowPos - 1);
                _arrow->move(irr::core::position2d<int>(0,-100));
        }
}

void            MenuScene::processDown() {
        if (_arrowPos != _arrQUIT) {
                _arrowPos = (arrowPosition)((int)_arrowPos + 1);
                _arrow->move(irr::core::position2d<int>(0,100));
        }
}

void            MenuScene::processLeft() {

}

void            MenuScene::processRight() {

}

void            MenuScene::processEnter() {
        if (_arrowPos == _arrPLAY) {
                startGame();
        }
        else if (_arrowPos == _arrOPTIONS) {
                goToOptions();
        }
        else if (_arrowPos == _arrQUIT) {
                quit();
        }
}

void            MenuScene::startGame() {
        stopScene();
        _exit_action = START_GAME;

}

void            MenuScene::goToOptions() {
}

void		MenuScene::quit() {
	stopScene();
        _exit_action = EXIT_APP;
}

void		MenuScene::stopScene() {
	_env->clear();
	_isRunning = false;
}