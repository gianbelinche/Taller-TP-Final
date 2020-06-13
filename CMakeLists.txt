cmake_minimum_required(VERSION 2.8)

project(argentum)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_library(sounds
  SoundEffect.cpp
  SoundEffectPlayer.cpp
  Music.cpp
  MusicPlayer.cpp
)

add_library(textures
  Texture.cpp
  Image.cpp
  Text.cpp
  FilteredImage.cpp
)

add_library(layout
  Layout.cpp
  GraphicInventory.cpp
  Test_gian.cpp 
)

add_library(errors
  SDLError.cpp
)

# Agrego la carpeta con los headers autogenerados a los includes
message("Agregando '${PROJECT_BINARY_DIR}' como directorio de includes")
include_directories(${PROJECT_BINARY_DIR})

add_executable (testgian
  prueba_de_sonido.cpp
)



target_link_libraries(testgian errors sounds textures layout SDL2 SDL2_image SDL2_mixer SDL2_ttf)