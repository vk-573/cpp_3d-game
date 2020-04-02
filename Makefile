SRC         =   src/main.cpp				\
				src/GameApplication.cpp		\
				src/EventManager.cpp		\
				src/Scene.cpp				\
				src/AEntity.cpp				\
				src/AEnemy.cpp				\
				src/Goblin.cpp				\
				src/Gunner.cpp				\
				src/Missile.cpp				\
				src/Player.cpp				\
				src/Attack.cpp				\
				src/Map.cpp					\
				src/Tile.cpp				\
				src/Wall.cpp				\
				src/Door.cpp				\
				src/MenuScene.cpp			\
				src/ASpell.cpp				\
				src/SpellBlast.cpp			\
				src/SoundManager.cpp			\

OBJ         =   $(SRC:.cpp=.o)

NAME        =   dungeon

CC          =   g++

CXXFLAGS    +=  -Wall -Werror -Wextra -g

CXXFLAGS    +=  -Iinclude

CXXFLAGS    +=  -lIrrlicht -lIrrKlang

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME) $(CXXFLAGS)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all
