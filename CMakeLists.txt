cmake_minimum_required(VERSION 2.8)

project(argentum)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
#[[
add_library(controllers
  ClientController.cpp
  ClientProtocol.cpp
  jsoncpp.cpp
  MessageQueue.cpp
)

add_library(connection
  ClientConnector.cpp
  Socket.cpp
)

add_library(entities
  Banker.cpp
  Entity.cpp
  EntityManager.cpp
  Goblin.cpp
  Healer.cpp
  Item.cpp
  Merchant.cpp
  NPC.cpp
  Player.cpp
  Skeleton.cpp
  Spyder.cpp
  Zombie.cpp
)

add_library(textures
  FilteredImage.cpp
  Image.cpp
  MapImage.cpp
  Text.cpp
  Texture.cpp
)

add_library(images
  Camera.cpp
  MainMap.cpp
  MainWindow.cpp
  SpriteClipCreator.cpp
)

add_library(layout
  ExpBar.cpp
  GraphicInventory.cpp
  Layout.cpp
  MiniChat.cpp
)

add_library(errors
  EmptyException.cpp
  JsonError.cpp
  OSError.cpp
  QuitException.cpp
  SDLError.cpp
  SocketException.cpp
)

add_library(threads
  EventManager.cpp
  ModelController.cpp
  Receiver.cpp
  Renderer.cpp
  Sender.cpp
  Thread.cpp
)
]]
add_library(pruebasss
  ClientController.cpp
  ClientProtocol.cpp
  jsoncpp.cpp
  MessageQueue.cpp
  ClientConnector.cpp
  Socket.cpp
  Banker.cpp
  Entity.cpp
  EntityManager.cpp
  Goblin.cpp
  Healer.cpp
  Item.cpp
  Merchant.cpp
  NPC.cpp
  Player.cpp
  Skeleton.cpp
  Spyder.cpp
  Zombie.cpp
  FilteredImage.cpp
  Image.cpp
  MapImage.cpp
  Text.cpp
  Texture.cpp
  Camera.cpp
  MainMap.cpp
  MainWindow.cpp
  SpriteClipCreator.cpp
  ExpBar.cpp
  GraphicInventory.cpp
  Layout.cpp
  MiniChat.cpp
<<<<<<< HEAD
  EmptyException.cpp
  JsonError.cpp
  OSError.cpp
  QuitException.cpp
  SDLError.cpp
  SocketException.cpp
  EventManager.cpp
  ModelController.cpp
  Receiver.cpp
  Renderer.cpp
  Sender.cpp
  Thread.cpp
=======
  LoginScreen.cpp
  Camera.cpp
>>>>>>> d7ac03a4c5e3842114c92dec75b8056384766d0f
)

# Agrego la carpeta con los headers autogenerados a los includes
message("Agregando '${PROJECT_BINARY_DIR}' como directorio de includes")
include_directories(${PROJECT_BINARY_DIR})


add_executable (prueba
  client.cpp
)

#target_link_libraries(testgian errors sounds textures layout SDL2 SDL2_image SDL2_mixer SDL2_ttf)
#target_link_libraries(prueba controllers connection entities textures images layout errors threads SDL2 SDL2_image SDL2_mixer SDL2_ttf pthread)
target_link_libraries(prueba pruebasss SDL2 SDL2_image SDL2_mixer SDL2_ttf pthread)