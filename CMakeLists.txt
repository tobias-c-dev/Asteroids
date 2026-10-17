cmake_minimum_required(VERSION 3.16)
project(AsteroidsGame)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Asteroids
    src/main.cpp
    src/Game.cpp
    src/Ship.cpp
    src/Bullet.cpp
    src/Asteroid.cpp
    src/UI.cpp
)

target_include_directories(Asteroids PRIVATE
    ${CMAKE_SOURCE_DIR}/include
)

# Copy assets next to the executable
file(COPY
    ${CMAKE_SOURCE_DIR}/assets
    DESTINATION ${CMAKE_BINARY_DIR}
)

# SFML 3
find_package(SFML 3 REQUIRED COMPONENTS Graphics Window System)

target_link_libraries(Asteroids PRIVATE
    SFML::Graphics
    SFML::Window
    SFML::System
)