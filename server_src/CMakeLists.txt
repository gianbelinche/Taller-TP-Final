cmake_minimum_required(VERSION 2.8)

project(argentum)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -pedantic -Wno-deprecated-declarations -g")

add_library(server_lib
  Server.cpp
  Game.cpp
  Communication/ClosedQueueException.cpp
  Communication/MessageDispatcher.cpp
  Communication/ServerReceiver.cpp
  Communication/ServerSender.cpp
  Communication/Socket.cpp
  Communication/SocketException.cpp
  config/Equations.cpp
  Entities/Bank.cpp
  Entities/Banker.cpp
  Entities/BankLocker.cpp
  Entities/ImmobilizedState.cpp
  Entities/Merchant.cpp
  Entities/NPC.cpp
  Entities/Priest.cpp
  Entities/Class.cpp
  Entities/Entity.cpp
  Entities/GhostState.cpp
  Entities/MeditationState.cpp
  Entities/Monster.cpp 
  Entities/MonsterType.cpp 
  Entities/NormalState.cpp 
  Entities/PlayerNet.cpp 
  Entities/PlayerState.cpp 
  Entities/Race.cpp 
  Events/EntityClick.cpp
  Events/Event.cpp 
  Events/InventoryClick.cpp 
  Events/MessageSent.cpp 
  Events/ServerEventHandler.cpp 
  Events/PlayerConnection.cpp
  Events/ServerEventListener.cpp 
  Events/UserMoved.cpp 
  Items/Armor.cpp 
  Items/Helmet.cpp 
  Items/Item.cpp 
  Items/Shield.cpp 
  Items/Weapon.cpp 
  Items/Wearable.cpp
  Items/Inventory.cpp 
  Items/HpPotion.cpp 
  Items/ManaPotion.cpp 
  resources/Acceptor.cpp 
  resources/ClientHandler.cpp 
  resources/Condition.cpp 
  resources/GameState.cpp 
  resources/IsAlive.cpp 
  jsoncpp.cpp 
  resources/JsonError.cpp 
  resources/Map.cpp 
  resources/MasterFactory.cpp
  resources/Persistor.cpp 
  resources/ServerProtocol.cpp 
  resources/Thread.cpp
  Utils/sha256.cpp
  Utils/Configuration.cpp
  Utils/ChatMessageParser.cpp
  )

  include_directories(headers json)

  add_executable(server server_main.cpp)

  target_link_libraries(server server_lib pthread)

