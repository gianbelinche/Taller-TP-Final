cmake_minimum_required(VERSION 2.8)

project(argentum)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Werror -pedantic -g")

# Find the QtWidgets library
find_package(Qt5Widgets)

include_directories(.)

# Esta macro toma cada uno los parámetros y ejecuta *uic* sobre ellos
# La aplicacion uic genera headers con la definición de los widgets
# a partir de un archivo .ui
# Los nombres de los headers generados se guardan en la variable pasada
# como primer parámetro.
# No, no los genera con la carpeta como prefijo.
#qt5_wrap_ui(UIS_HEADERS
#        login.ui
#)

add_library(clientLib
  client_src/ClientController.cpp
  client_src/ClientProtocol.cpp
  client_src/BlockingMsgQueue.cpp
  client_src/ProtMsgQueue.cpp
  client_src/ClientConnector.cpp
  client_src/Socket.cpp
  client_src/Banker.cpp
  client_src/Entity.cpp
  client_src/EntityManager.cpp
  client_src/Goblin.cpp
  client_src/Healer.cpp
  client_src/Item.cpp
  client_src/Merchant.cpp
  client_src/NPC.cpp
  client_src/Player.cpp
  client_src/Skeleton.cpp
  client_src/Spyder.cpp
  client_src/Zombie.cpp
  client_src/FilteredImage.cpp
  client_src/Image.cpp
  client_src/MapImage.cpp
  client_src/Text.cpp
  client_src/Texture.cpp
  client_src/Camera.cpp
  client_src/MainMap.cpp
  client_src/MainWindow.cpp
  client_src/SpriteClipCreator.cpp
  client_src/ExpBar.cpp
  client_src/GraphicInventory.cpp
  client_src/Layout.cpp
  client_src/MiniChat.cpp
  client_src/QueueClosedException.cpp
  client_src/OSError.cpp
  client_src/QuitException.cpp
  client_src/SDLError.cpp
  client_src/SocketException.cpp
  client_src/EventManager.cpp
  client_src/ModelController.cpp
  client_src/Receiver.cpp
  client_src/Renderer.cpp
  client_src/Sender.cpp
  client_src/Thread.cpp
  client_src/Equippable.cpp
  client_src/LayoutManager.cpp
  client_src/Music.cpp
  client_src/MusicPlayer.cpp
  client_src/SoundEffect.cpp
  client_src/SoundEffectPlayer.cpp
)

# Agrego la carpeta con los headers autogenerados a los includes
message("Agregando '${PROJECT_BINARY_DIR}' como directorio de includes")
include_directories(${PROJECT_BINARY_DIR})


add_executable (client
  client_src/LogIn.cpp
  client_src/LogInController.cpp
  client_src/client.cpp
)

#target_link_libraries(testgian errors sounds textures layout SDL2 SDL2_image SDL2_mixer SDL2_ttf)
#target_link_libraries(prueba controllers connection entities textures images layout errors threads SDL2 SDL2_image SDL2_mixer SDL2_ttf pthread)
target_link_libraries(client clientLib SDL2 SDL2_image SDL2_mixer SDL2_ttf pthread Qt5::Widgets)