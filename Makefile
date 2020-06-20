CC = g++
CFLAGS = -g -Wall -Werror -pedantic -pedantic-errors

CFILES = client.cpp MainWindow.cpp MainMap.cpp jsoncpp.cpp SDLError.cpp MapImage.cpp Player.cpp Image.cpp SpriteClipCreator.cpp FilteredImage.cpp Texture.cpp EntityManager.cpp Spyder.cpp Skeleton.cpp Goblin.cpp Zombie.cpp Banker.cpp Merchant.cpp Healer.cpp Entity.cpp Camera.cpp Item.cpp ClientProtocol.cpp NPC.cpp
LINKLIBS = -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer
EXEC_S = main

build: $(CFILES)
	$(CC) -o $(EXEC_S) $(CFILES) $(LINKLIBS)

run: build
	./$(EXEC_S)
