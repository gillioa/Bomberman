##
## Makefile for  in /home/remaud_c/Code/TPs/my_script/MyS
##
## Made by remaud_c
## Login   <remaud_c@epitech.net>
##
## Started on  Fri Feb 14 12:01:16 2014 remaud_c
## Last update Wed Jun 11 16:48:41 2014 courtu_r
##

CC	=	g++ -Wall -Wextra -std=gnu++0x -O3

DIR_SRC = ./sources/

CXXFLAGS	+=  -I$(DIR_SRC)GDL/includes
CXXFLAGS	+=  -I$(DIR_SRC)Map
CXXFLAGS	+=  -I$(DIR_SRC)ScopedLock
CXXFLAGS	+=  -I$(DIR_SRC)Mutex
CXXFLAGS	+=  -I$(DIR_SRC)Case
CXXFLAGS	+=  -I$(DIR_SRC)ABomb
CXXFLAGS 	+=  -I$(DIR_SRC)ABonus
CXXFLAGS 	+=  -I$(DIR_SRC)AObject
CXXFLAGS 	+=  -I$(DIR_SRC)BonusFactory
CXXFLAGS 	+=  -I$(DIR_SRC)PlayerBonus
CXXFLAGS	+=  -I$(DIR_SRC)Time
CXXFLAGS	+=  -I$(DIR_SRC)Except
CXXFLAGS	+=  -I$(DIR_SRC)Player
CXXFLAGS	+=  -I$(DIR_SRC)AWall
CXXFLAGS	+=  -I$(DIR_SRC)Core
CXXFLAGS	+=  -I$(DIR_SRC)MapGen
CXXFLAGS	+=  -I$(DIR_SRC)GameEngine
CXXFLAGS	+=  -I$(DIR_SRC)IA
CXXFLAGS	+=  -I$(DIR_SRC)Thread
CXXFLAGS	+=  -I$(DIR_SRC)menu
CXXFLAGS	+=  -I$(DIR_SRC)serialize
CXXFLAGS	+=  -I$(DIR_SRC)loadsave


LDFLAGS =    -g -L./sources/GDL/libs/ -L./sources/JsonCPP/  -lgdl_gl -lGL -lGLEW -lrt -lfbxsdk -lSDL2 -lpthread -ldl -ljson_linux-gcc-4.7_libmt

RM	=	rm -f

NAME	=	bomberman

SRCS	=	$(DIR_SRC)main.cpp			  \
		$(DIR_SRC)AObject/AObject.cpp			\
		$(DIR_SRC)ABonus/ABonus.cpp			\
		$(DIR_SRC)BonusFactory/BonusFactory.cpp		\
		$(DIR_SRC)Time/Timer.cpp			\
		$(DIR_SRC)Player/Player.cpp			\
		$(DIR_SRC)Map/Map.cpp				\
		$(DIR_SRC)Mutex/Mutex.cpp			\
		$(DIR_SRC)MapGen/MapGenerator.cpp		\
		$(DIR_SRC)Case/Case.cpp				\
		$(DIR_SRC)ScopedLock/ScopedLock.cpp		\
		$(DIR_SRC)ABomb/ABomb.cpp			\
		$(DIR_SRC)AWall/AWall.cpp			\
		$(DIR_SRC)Core/Core.cpp				\
		$(DIR_SRC)IA/IABomb.cpp 			\
		$(DIR_SRC)IA/IABonus.cpp 			\
		$(DIR_SRC)IA/IA.cpp 				\
		$(DIR_SRC)IA/IAPlayer.cpp 			\
		$(DIR_SRC)IA/IASafe.cpp 			\
		$(DIR_SRC)Thread/Thread.cpp			\
		$(DIR_SRC)GameEngine/GameEngine.cpp		\
		$(DIR_SRC)GameEngine/Cube.cpp			\
		$(DIR_SRC)GameEngine/Plan.cpp			\
		$(DIR_SRC)GameEngine/myModel.cpp		\
		$(DIR_SRC)GameEngine/Camera.cpp			\
		$(DIR_SRC)GameEngine/PlayerGraph.cpp		\
		$(DIR_SRC)GameEngine/getColor.cpp		\
		$(DIR_SRC)MapGen/RandomMapGenerator.cpp		\
		$(DIR_SRC)menu/image.cpp 			\
		$(DIR_SRC)menu/menu.cpp 			\
		$(DIR_SRC)menu/AMenu.cpp 			\
		$(DIR_SRC)menu/OptionJoueur.cpp 		\
		$(DIR_SRC)menu/OptionPartie.cpp 		\
		$(DIR_SRC)menu/ChargerPartie.cpp 		\
		$(DIR_SRC)menu/Name.cpp 			\
		$(DIR_SRC)menu/text.cpp 			\
		$(DIR_SRC)menu/myInput.cpp 			\
		$(DIR_SRC)menu/menuconstantes.cpp 		\
		$(DIR_SRC)menu/scores.cpp 			\
		$(DIR_SRC)menu/MenuScore.cpp 			\
		$(DIR_SRC)menu/texturemanager.cpp 		\
		$(DIR_SRC)Core/checkValidity.cpp 		\
		$(DIR_SRC)menu/ingame.cpp 			\
		$(DIR_SRC)loadsave/LoadSave.cpp 		\
		$(DIR_SRC)serialize/Serialize.cpp 


OBJS	=	$(SRCS:.cpp=.o)

%.o:		%.cpp
		$(CC) -c $^ -o $@ $(CXXFLAGS)

all:		$(NAME)

$(NAME):	$(OBJS)
		$(CC)  -o $(NAME) $(OBJS) $(LDFLAGS)

clean:
		$(RM) $(OBJS)

fclean:		clean
		$(RM) $(NAME)

re:		fclean all

test:		fclean all
		$(RM) $(OBJS)
