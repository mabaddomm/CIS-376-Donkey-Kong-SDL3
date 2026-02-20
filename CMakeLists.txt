cmake_minimum_required(VERSION 3.16)
project(DonkeyKong)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")

# Build SDL from vendored folder
add_subdirectory(vendored/SDL EXCLUDE_FROM_ALL)

# This assumes the SDL_image source is available in vendored/SDL_image
add_subdirectory(vendored/SDL_image EXCLUDE_FROM_ALL)



# Create your executable
add_executable(DonkeyKong
    game.cpp
    gameEngine.cpp
    gameObjects.cpp
    components.cpp
    scene.cpp
    player.cpp
)

# Link SDL3
target_link_libraries(DonkeyKong PRIVATE SDL3::SDL3 SDL3_image::SDL3_image)

