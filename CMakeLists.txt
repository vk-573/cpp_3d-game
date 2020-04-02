cmake_minimum_required(VERSION 3.0)
set(NAME Dungeon)
project(${NAME})
set(CMAKE_CXX_STANDARD 14)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR})

## Flags
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS_DEBUG}")

## Includes and lib directory
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/)
#include_directories(${NAME} ${CMAKE_CURRENT_SOURCE_DIR}/lib/include)
#link_directories(${NAME} ${CMAKE_CURRENT_SOURCE_DIR}/lib/linux)

## Compilation
set(
	SRC
	src/GameApplication.cpp
	src/EventManager.cpp
	src/MenuScene.cpp
	src/Scene.cpp
	src/Tile.cpp
	src/Wall.cpp
	src/Door.cpp
	src/Map.cpp
	src/AEntity.cpp
	src/AEnemy.cpp
	src/Goblin.cpp
	src/Gunner.cpp
	src/Missile.cpp
	src/Player.cpp
	src/main.cpp
	src/ASpell.cpp
	src/SpellBlast.cpp
	src/Attack.cpp
	src/SoundManager.cpp
)

set(
	INCLUDES
	include/GameApplication.hpp
	include/EventManager.hpp
	include/IScene.hpp
	include/MenuScene.hpp
	include/Scene.hpp
	include/Tile.hpp
	include/Wall.hpp
	include/Door.hpp
	include/IMap.hpp
	include/Map.hpp
	include/AEntity.hpp
	include/AEnemy.hpp
	include/Goblin.hpp
	include/Gunner.hpp
	include/Missile.hpp
	include/Player.hpp
	include/ASpell.hpp
	include/SpellBlast.hpp
	include/Attack.hpp
	include/SoundManager.hpp
)

add_executable(
		${NAME}
		${SRC}
		${INCLUDES}
)

## Lib linking
#execute_process(COMMAND bash -c "sudo cp -r -v ../lib/linux/libIrrKlang.so /usr/lib/")
target_link_libraries(${NAME} Irrlicht GL Xxf86vm Xext X11 Xcursor)
target_link_libraries(${NAME} Irrlicht IrrKlang GL Xxf86vm Xext X11 Xcursor)
