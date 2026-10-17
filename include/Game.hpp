#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "Asteroid.hpp"
#include "Bullet.hpp"
#include "Constants.hpp"
#include "Ship.hpp"
#include "UI.hpp"

class Game
{
public:
    Game();

    void run();

private:
    void processEvents();
    void update(float dt);
    void render();

    void handleCollisions();
    void resetGame();
    void spawnAsteroids(int count, float speedMult);

    sf::RenderWindow window;

    GameState state;

    Ship ship;
    std::vector<Asteroid> asteroids;
    std::vector<Bullet> bullets;

    int score;
    int lives;
    int waveNumber;

    UI ui;

    // Timers
    sf::Clock clock;
    sf::Clock invincibilityClock;
    sf::Clock gameOverClock;
    sf::Clock waveClock;

    // Flags
    bool isInvincible;
    bool canControlShip;
};