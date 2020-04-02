/*
** EPITECH PROJECT, 2018
** SoundManager
** File description:
** Implementation of SoundManager
*/

#include "SoundManager.hpp"
#include <iostream>

irrklang::ISoundEngine *SoundManager::engine = irrklang::createIrrKlangDevice();
irrklang::ISound *SoundManager::currentMusic = NULL;

void SoundManager::playSound(const std::string &soundName)
{
	std::string string = "resources/sounds/sfx/" + soundName;
	engine->play2D(string.c_str(), false, false);
}

void SoundManager::playMusic(const std::string &musicName)
{
	std::string string = "resources/sounds/themes/" + musicName;

	if (SoundManager::currentMusic) {
		SoundManager::currentMusic->stop();
		SoundManager::currentMusic->drop();
	}
	SoundManager::currentMusic = engine->play2D(string.c_str(), true, false, true);
}
