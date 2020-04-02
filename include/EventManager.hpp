/*
** EPITECH PROJECT, 2018
** EventManager
** File description:
** Declaration of EventManager
*/

#ifndef DUNGEON_EVENTMANAGER_HPP
#define DUNGEON_EVENTMANAGER_HPP

#include <irrlicht/irrlicht.h>
#include <vector>
#include <map>

class EventManager : public irr::IEventReceiver
{
	public:
		enum Action {
			MOVE_UP,
			MOVE_DOWN,
			MOVE_RIGHT,
			MOVE_LEFT,
			ATTACK,
			ENTER,
			EXIT,
			CAMERA_XUP,
			CAMERA_XDOWN,
			CAMERA_YUP,
			CAMERA_YDOWN,
			CAMERA_ZUP,
			CAMERA_ZDOWN,
		};
		enum InputType {
			PRESSED,
			RELEASED
		};
		EventManager();
		void refresh();
		static std::vector<std::pair<Action, InputType>> getEvents();
		bool OnEvent(const irr::SEvent &event) override;
		bool isKeyDown(irr::EKEY_CODE keyCode) const;
		bool isKeyReleased(irr::EKEY_CODE keyCode);
	private:
		static std::vector<std::pair<Action, InputType>> events;
		bool keyIsDown[irr::KEY_KEY_CODES_COUNT];
		bool keyIsReleased[irr::KEY_KEY_CODES_COUNT];
};

typedef std::vector<std::pair<EventManager::Action, EventManager::InputType>> _EVENTS;

#endif //DUNGEON_EVENTMANAGER_HPP
