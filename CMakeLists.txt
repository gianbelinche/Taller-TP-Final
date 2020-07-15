cmake_minimum_required(VERSION 2.8)

project(argentum)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Werror -pedantic -g -Wno-deprecated-declarations")

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
  client_src/assets/BlockingMsgQueue.cpp
  client_src/assets/ProtMsgQueue.cpp
  client_src/ClientConnector.cpp
  client_src/assets/Socket.cpp
  client_src/entity/Entity.cpp
  client_src/entity/EntityManager.cpp
  client_src/entity/Item.cpp
  client_src/entity/NPC.cpp
  client_src/Mob.cpp
  client_src/entity/Player.cpp
  client_src/wrap_sdl/FilteredImage.cpp
  client_src/wrap_sdl/Image.cpp
  client_src/MapImage.cpp
  client_src/wrap_sdl/Text.cpp
  client_src/wrap_sdl/Texture.cpp
  client_src/Camera.cpp
  client_src/MainMap.cpp
  client_src/MainWindow.cpp
  client_src/SpriteClipCreator.cpp
  client_src/layout/ExpBar.cpp
  client_src/layout/GraphicInventory.cpp
  client_src/layout/Layout.cpp
  client_src/layout/MiniChat.cpp
  client_src/errors/QueueClosedException.cpp
  client_src/errors/OSError.cpp
  client_src/errors/QuitException.cpp
  client_src/errors/SDLError.cpp
  client_src/errors/SocketException.cpp
  client_src/client_controller/EventManager.cpp
  client_src/ModelController.cpp
  client_src/client_controller/Receiver.cpp
  client_src/client_controller/Renderer.cpp
  client_src/client_controller/Sender.cpp
  client_src/assets/Thread.cpp
  client_src/Equippable.cpp
  client_src/layout/LayoutManager.cpp
  client_src/wrap_sdl/Music.cpp
  client_src/wrap_sdl/MusicPlayer.cpp
  client_src/wrap_sdl/SoundEffect.cpp
  client_src/wrap_sdl/SoundEffectPlayer.cpp
)

add_library(server_lib
  server_src/Server.cpp
  server_src/Game.cpp
  server_src/Communication/ClosedQueueException.cpp
  server_src/Communication/MessageDispatcher.cpp
  server_src/Communication/ServerReceiver.cpp
  server_src/Communication/ServerSender.cpp
  server_src/Communication/Socket.cpp
  server_src/Communication/SocketException.cpp
  server_src/config/Equations.cpp
  server_src/Entities/Bank.cpp
  server_src/Entities/Banker.cpp
  server_src/Entities/BankLocker.cpp
  server_src/Entities/ImmobilizedState.cpp
  server_src/Entities/Merchant.cpp
  server_src/Entities/NPC.cpp
  server_src/Entities/Priest.cpp
  server_src/Entities/Class.cpp
  server_src/Entities/Entity.cpp
  server_src/Entities/GhostState.cpp
  server_src/Entities/MeditationState.cpp
  server_src/Entities/Monster.cpp 
  server_src/Entities/MonsterType.cpp 
  server_src/Entities/NormalState.cpp 
  server_src/Entities/PlayerNet.cpp 
  server_src/Entities/PlayerState.cpp 
  server_src/Entities/Race.cpp 
  server_src/Events/EntityClick.cpp
  server_src/Events/Event.cpp 
  server_src/Events/InventoryClick.cpp 
  server_src/Events/MessageSent.cpp 
  server_src/Events/ServerEventHandler.cpp 
  server_src/Events/PlayerConnection.cpp
  server_src/Events/ServerEventListener.cpp 
  server_src/Events/UserMoved.cpp 
  server_src/Items/Armor.cpp 
  server_src/Items/Helmet.cpp 
  server_src/Items/Item.cpp 
  server_src/Items/Shield.cpp 
  server_src/Items/Weapon.cpp 
  server_src/Items/Wearable.cpp
  server_src/Items/Inventory.cpp 
  server_src/Items/HpPotion.cpp 
  server_src/Items/ManaPotion.cpp 
  server_src/Items/GoldDrop.cpp
  server_src/resources/Acceptor.cpp 
  server_src/resources/ClientHandler.cpp 
  server_src/resources/Condition.cpp 
  server_src/resources/GameState.cpp 
  server_src/resources/IsAlive.cpp 
  server_src/jsoncpp.cpp 
  server_src/resources/Map.cpp 
  server_src/resources/MasterFactory.cpp
  server_src/resources/Persistor.cpp 
  server_src/resources/ServerProtocol.cpp 
  server_src/resources/Thread.cpp
  server_src/Utils/sha256.cpp
  server_src/Utils/Configuration.cpp
  server_src/Utils/ChatMessageParser.cpp
  )

# Agrego la carpeta con los headers autogenerados a los includes
message("Agregando '${PROJECT_BINARY_DIR}' como directorio de includes")
include_directories(${PROJECT_BINARY_DIR})
include_directories(headers json)

add_executable (client
  client_src/login/LogIn.cpp
  client_src/login/LogInController.cpp
  client_src/ClientInitializer.cpp
  client_src/client.cpp
)

add_executable(server server_src/server_main.cpp)

#target_link_libraries(testgian errors sounds textures layout SDL2 SDL2_image SDL2_mixer SDL2_ttf)
#target_link_libraries(prueba controllers connection entities textures images layout errors threads SDL2 SDL2_image SDL2_mixer SDL2_ttf pthread)
target_link_libraries(client clientLib SDL2 SDL2_image SDL2_mixer SDL2_ttf pthread Qt5::Widgets)
target_link_libraries(server server_lib pthread)
