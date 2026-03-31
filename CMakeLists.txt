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

# copy assets to the binary dir so runtime can find them
file(COPY ${CMAKE_SOURCE_DIR}/assets DESTINATION ${CMAKE_BINARY_DIR})

target_include_directories(Asteroids PRIVATE ${CMAKE_SOURCE_DIR}/include)

# Try to find SFML using imported targets if available
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

# If SFML provides namespaced targets (sfml::graphics), prefer them. Fallback to plain names if needed.
if(TARGET sfml::graphics)
    target_link_libraries(Asteroids PRIVATE sfml::graphics sfml::window sfml::system)
else()
    target_link_libraries(Asteroids PRIVATE sfml-graphics sfml-window sfml-system)
endif()
