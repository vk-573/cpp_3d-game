/*
** EPITECH PROJECT, 2018
** Scene
** File description:
** Implementation of Scene
*/

#include <iostream>
#include "Scene.hpp"

Scene::Scene() : mapGrid(Map::generate(8)), map(*mapGrid[0]), _isRunning(true)
{
	shadows = true;
	for (Map *map : mapGrid)
		map->spawnEnemies();
}

Scene::~Scene()
{
}

void Scene::init(irr::IrrlichtDevice *window, EventManager *eventmanager)
{
	device = window;
	_eventManager = eventmanager;
	_env = device->getGUIEnvironment();
	irr::scene::ISceneManager *smgr = device->getSceneManager();
        _driver = device->getVideoDriver();
        map.draw(device);

	entities.push_back(new Player(device, map.getSpawnPos((Door::Direction)-1), device->getTimer(), map.getTileSize()));
	Player *player = (Player *)entities[0];
	player->draw(device);
	_player = player;
	_player->setMap(&map);
	camera = smgr->addCameraSceneNode(nullptr, irr::core::vector3df(0, 30, -40),
					  irr::core::vector3df(0, 5, 0));
	camera->setPosition(irr::core::vector3df((irr::f32)(map.getWidth(true) - map.getTileSize()) / 2,
						 static_cast<irr::f32>((irr::f32)map.getHeight(true) * 0.8),
						 (irr::f32)(map.getHeight(true) * 0.8) * -1));
	camera->setTarget(irr::core::vector3df((irr::f32)(map.getWidth(true) - map.getTileSize()) / 2,
					       0, (irr::f32)map.getHeight(true) / 2 * -1));
	camera->setFarValue(100000.0f);
	smgr->setActiveCamera(camera);
	replaceCamera();


	auto light1 = smgr->addLightSceneNode(nullptr, irr::core::vector3df((irr::f32)map.getWidth(true) / 2,
									    (irr::f32)500, (irr::f32)map.getHeight(true) / 2 * -1),
					      irr::video::SColorf(0.6f, 0.6f, 0.7f, 0.8f),
					      static_cast<irr::f32>(300 + map.getHeight(true) * 0.4));
	auto light2 = smgr->addLightSceneNode(nullptr, irr::core::vector3df(-500, 400, 100),
					      irr::video::SColorf(1.0f, 1.0f, 1.0f, 1.0f),
					      static_cast<irr::f32>(400 + map.getHeight(true) * 0.7));
	if (!shadows) {
		light1->enableCastShadow(false);
		light2->enableCastShadow(false);
	}
	ambientLights.clear();
	ambientLights.push_back(light1);
	ambientLights.push_back(light2);
	smgr->setShadowColor(irr::video::SColor(100,0,0,0));
	setHUD();
	_exit_action = EXIT_APP;
	SoundManager::playMusic("maintheme.wav");
}


void	Scene::setHUD() {
	_player->setHUD();
}

void 	Scene::processPlayer()
{
	_player->process(entities);
	if (_player->isDead()) {
		_exit_action = BACK_MAINMENU;
		quit();
		return;
	}
	if (_player->isDying()) {
		return;
	}
	irr::core::vector2df pos = _player->getPos();
	Tile *currentTile = map.getTile(pos.X, pos.Y);

	if (currentTile->getType() == Tile::Type::DOOR) {
		changeMap(((Door *)currentTile)->getDirection());
	}

	//process projectiles
	for (unsigned i = 1; i < entities.size(); i++) {
		if (entities[i]->getModelString() == "resources/models/missile.obj") {
			float distance = sqrt(pow(pos.X - entities[i]->getPos().X, 2)
				+ pow(pos.Y - entities[i]->getPos().Y, 2));
			if (distance < 0.5 || ((Missile *)entities[i])->isOver()) {
				if (distance < 0.5) {
					_player->damage(10);
				}
				entities[i]->clear();
				entities.erase(entities.begin() + i);
				i--;
			}
		}
	}
}


void Scene::processEnemies()
{
	for (unsigned int i = 1; i < entities.size(); i++) {
		if (!entities[i]->isDead()) {
			entities[i]->process(entities);
		}
		// else {
		// }
	}
}

_ACTION		Scene::run() {
	_isRunning = true;
	while (_isRunning) {
		device->run();
		device->getVideoDriver()->beginScene(true, true, irr::video::SColor(255, 0, 0, 0));
		processEvents(_eventManager->getEvents());
		processPlayer();
		if (!_isRunning) {
			break;
		}
		processEnemies();
		display();
		_env->drawAll();
		device->getVideoDriver()->endScene();
		_eventManager->refresh();
	}
	return _exit_action;
}

void Scene::display()
{
	irr::scene::ISceneManager *smgr = device->getSceneManager();

	smgr->drawAll();
}

bool Scene::isRunning() const
{
	return _isRunning;
}

void Scene::processEvents(_EVENTS events)
{
	if(_player->isDying()) {
		return;
	}
	irr::core::vector3d<float> pos = camera->getPosition();
	std::pair<int, int> playerMovement(0, 0);

	for (auto action : events) {
		//TODO: implementer les events ici
		if (action.first == EventManager::Action::EXIT && action.second == EventManager::InputType::PRESSED)
			_isRunning = false;
		else if (action.first == EventManager::Action::MOVE_UP && action.second == EventManager::InputType::PRESSED) {
			playerMovement.second++;
		}
		else if (action.first == EventManager::Action::MOVE_DOWN && action.second == EventManager::InputType::PRESSED) {
			playerMovement.second--;
		}
		else if (action.first == EventManager::Action::MOVE_LEFT && action.second == EventManager::InputType::PRESSED) {
			playerMovement.first--;
		}
		else if (action.first == EventManager::Action::MOVE_RIGHT && action.second == EventManager::InputType::PRESSED) {
			playerMovement.first++;
		}
		else if (action.first == EventManager::Action::ATTACK && action.second == EventManager::InputType::RELEASED) {
			_player->attackSpell();
		}
		else if (action.first == EventManager::Action::CAMERA_XUP && action.second == EventManager::InputType::PRESSED) {
			pos.X++;
		}
		else if (action.first == EventManager::Action::CAMERA_XDOWN && action.second == EventManager::InputType::PRESSED) {
			pos.X--;
		}
		else if (action.first == EventManager::Action::CAMERA_YUP && action.second == EventManager::InputType::PRESSED) {
			pos.Y++;
		}
		else if (action.first == EventManager::Action::CAMERA_YDOWN && action.second == EventManager::InputType::PRESSED) {
			pos.Y--;
		}
		else if (action.first == EventManager::Action::CAMERA_ZUP && action.second == EventManager::InputType::PRESSED) {
			_player->attack();
		}
		else if (action.first == EventManager::Action::CAMERA_ZDOWN && action.second == EventManager::InputType::PRESSED) {
			pos.Z--;
		}

	}

	camera->setPosition(pos);
	if (playerMovement.first != 0 || playerMovement.second != 0) {
		movePlayer(playerMovement);
	}
	else if (_player->getState() != AEntity::State::ATTACK
		&& _player->getState() != AEntity::State::ATTACKSPELL
		&& _player->getState() != AEntity::State::DAMAGED ){
		entities[0]->setState(AEntity::State::IDLE);
	}
}

void Scene::movePlayer(std::pair<int, int> direction)
{
	if (_player->getState() == AEntity::ATTACK || _player->getState() == AEntity::ATTACKSPELL) {
		return;
	}
	irr::core::vector2df pos = _player->getPos();
	irr::core::vector2df newPos(pos);
	float angle = atan2(direction.first, direction.second) * 180 / M_PI - 90;
	float speed = _player->getSpeed();

	newPos.X = pos.X + speed * cos(angle * M_PI / 180);
	newPos.Y = pos.Y + speed * sin(angle * M_PI / 180);

	//TODO: faire un truc plus clean pour les animations
	_player->setState(AEntity::State::RUNNING);
	_player->setAngle(angle);

	//Basic collision with walls
	if (newPos.X < 0 || newPos.X >= map.getWidth(false)
		|| newPos.Y < 0 || newPos.Y >= map.getHeight(false)
		|| map.getTile(newPos.X, newPos.Y)->getType() == Tile::Type::WALL) {
		return;
	}

	_player->setPos(newPos);
	replaceCamera();
}

void Scene::changeMap(Door::Direction dir)
{
	Player *player = (Player *)entities[0];
	Map *newMap = map.getAdjacentMaps()[dir];
	irr::core::vector2df spawnPos = newMap->getSpawnPos(dir);

	// puts("lol");
	map.clear();
	// puts("lol0.1");
	newMap->draw(device);
	// puts("lol0.2");
	player->setPos(irr::core::vector2df(spawnPos.X, spawnPos.Y));
	replaceCamera();
	map = *newMap;
	// puts("lol1");
	//todo: très sale
	for (unsigned int i = 1; i < entities.size(); i++) {
		if (entities[i]->getModelString() == "resources/models/missile.obj") {
			entities[i]->clear();
			entities.erase(entities.begin() + i);
			i--;
		}
	}
	player->setMap(&map);

	// puts("lol2");
	std::vector<AEntity *> newEntities;
	newEntities.push_back(entities[0]);
	for (AEntity *enemy : map.getEnnemies()) {
		if (!enemy->isDead()) {
			((AEnemy *)enemy)->setTimer(device->getTimer());
			newEntities.push_back(enemy);
		}
	}
	// puts("lol3");
	entities = newEntities;
	SoundManager::playSound("door.wav");
}

void		Scene::quit() {
	_env->clear();
	delete _player;
	// delete camera;
	for (unsigned int i = 1; i < entities.size(); i++) {
		if (entities[i]->getModelString() == "resources/models/missile.obj") {
			entities[i]->clear();
			entities.erase(entities.begin() + i);
			i--;
		}
	}
	for (auto &map: mapGrid) {
		delete map;
	}
	_isRunning = false;
}

void Scene::replaceCamera()
{
	irr::core::vector3df playerPos = entities[0]->getMeshPos();
	irr::core::vector3df newPos = irr::core::vector3df(playerPos);

	newPos.Y += map.getTileSize() * 5;
	newPos.Z -= map.getTileSize() * 3;
	camera->setPosition(newPos);
	camera->setTarget(playerPos);
}
