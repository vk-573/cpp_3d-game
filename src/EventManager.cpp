/*
** EPITECH PROJECT, 2018
** EventManager
** File description:
** Implementation of EventManager
*/

#include <GameApplication.hpp>
#include "EventManager.hpp"


std::vector<std::pair<EventManager::Action, EventManager::InputType>> EventManager::events;


EventManager::EventManager()
{
	for (irr::u32 i = 0; i < irr::KEY_KEY_CODES_COUNT; ++i) {
		keyIsDown[i] = false;
		keyIsReleased[i] = false;
	}
}

static std::map<irr::EKEY_CODE, EventManager::Action> actions = {
	{ irr::KEY_KEY_Z, EventManager::Action::MOVE_UP },
	{ irr::KEY_KEY_Q, EventManager::Action::MOVE_LEFT },
	{ irr::KEY_KEY_S, EventManager::Action::MOVE_DOWN },
	{ irr::KEY_KEY_D, EventManager::Action::MOVE_RIGHT },
	{ irr::KEY_UP, EventManager::Action::CAMERA_ZUP },
	{ irr::KEY_DOWN, EventManager::Action::CAMERA_ZDOWN },
	{ irr::KEY_LEFT, EventManager::Action::CAMERA_XDOWN },
	{ irr::KEY_RIGHT, EventManager::Action::CAMERA_XUP },
	{ irr::KEY_PRIOR, EventManager::Action::CAMERA_YDOWN },
	{ irr::KEY_NEXT, EventManager::Action::CAMERA_YUP },
	{ irr::KEY_SPACE, EventManager::Action::ATTACK },
	{ irr::KEY_RETURN, EventManager::Action::ENTER },
	{ irr::KEY_ESCAPE, EventManager::Action::EXIT }
};

void EventManager::refresh()
{
	events.clear();
	for (auto &line : actions) {
		if (isKeyDown(line.first))
			events.push_back({line.second, PRESSED});
		else if (isKeyReleased(line.first))
			events.push_back({line.second, RELEASED});
	}
}

std::vector<std::pair<EventManager::Action, EventManager::InputType>>
EventManager::getEvents()
{
	return events;
}

bool EventManager::OnEvent(const irr::SEvent &event)
{
	if (event.EventType == irr::EET_KEY_INPUT_EVENT) {
		keyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
		keyIsReleased[event.KeyInput.Key] = !event.KeyInput.PressedDown;
		return true;
	}
//	else if (event.EventType == irr::EET_GUI_EVENT) {
//		guiEvents[(Event::MenuItem)event.GUIEvent.Caller->getID()]
//			= event.GUIEvent.EventType;
//	}
	return false;
}

bool EventManager::isKeyDown(irr::EKEY_CODE keyCode) const
{
	return keyIsDown[keyCode];
}

bool EventManager::isKeyReleased(irr::EKEY_CODE keyCode)
{
	if (keyIsReleased[keyCode]) {
		keyIsReleased[keyCode] = false;
		return true;
	}
	return false;
}