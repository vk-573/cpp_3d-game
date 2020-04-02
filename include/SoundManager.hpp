/*
** EPITECH PROJECT, 2018
** SoundManager
** File description:
** Declaration of SoundManager
*/

#ifndef DUNGEON_SOUNDMANAGER_HPP
#define DUNGEON_SOUNDMANAGER_HPP

#include <irrklang/irrKlang.h>
#include <string>

using namespace irrklang;

class SoundManager
{
	static ISoundEngine *engine;
	static irrklang::ISound *currentMusic;

	public:
		static void playSound(const std::string &soundName);
		static void playMusic(const std::string &musicName);
};



#endif //DUNGEON_SOUNDMANAGER_HPP
