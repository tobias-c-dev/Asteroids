#include "Game.hpp"
#include <iostream>
#include <cstdlib>
#include <cmath>

Game::Game()
    : window(
          sf::VideoMode::getDesktopMode(),
          "Asteroids Game",
          sf::State::Fullscreen),
      state(GameState::PLAYING),
      score(0),
      lives(Constants::INITIAL_LIVES),
      waveNumber(1),
      isInvincible(false),
      canControlShip(true)
{
    auto desktop = sf::VideoMode::getDesktopMode();

    Constants::SCREEN_WIDTH = desktop.size.x;
    Constants::SCREEN_HEIGHT = desktop.size.y;

    ship.resetPosition();

    ui.loadFont("assets/Creepster-Regular.ttf");

    spawnAsteroids(Constants::ASTEROID_START_COUNT, 1.f);
}

void Game::run()
{
    while (window.isOpen())
    {
        processEvents();

        float dt = clock.restart().asSeconds();

        if (state == GameState::PLAYING ||
            state == GameState::SHOWING_WAVE)
        {
            update(dt);
        }

        render();
    }
}

void Game::processEvents()
{
    while (const std::optional event = window.pollEvent())
    {
        if (event->is<sf::Event::Closed>())
        {
            window.close();
        }

        if (const auto* keyPressed =
                event->getIf<sf::Event::KeyPressed>())
        {
            if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
            {
                if (state == GameState::PLAYING)
                {
                    state = GameState::PAUSED;
                }
                else if (state == GameState::PAUSED)
                {
                    state = GameState::PLAYING;
                }
            }
        }
    }

    if (state == GameState::PAUSED)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R))
        {
            resetGame();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q))
        {
            window.close();
        }
    }
    else if (state == GameState::GAME_OVER &&
             gameOverClock.getElapsedTime().asSeconds() > 1.5f)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R))
        {
            resetGame();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q))
        {
            window.close();
        }
    }
}

void Game::update(float dt)
{
    // Invincibility logic
    if (isInvincible &&
        invincibilityClock.getElapsedTime().asSeconds() >
            Constants::INVINCIBILITY_DURATION)
    {
        isInvincible = false;
    }

    if (!canControlShip &&
        invincibilityClock.getElapsedTime().asSeconds() >
            Constants::CONTROL_DELAY)
    {
        canControlShip = true;
    }

    // Ship
    if (canControlShip)
    {
        ship.handleInput(dt);

        auto newBullets = ship.shoot();

        bullets.insert(
            bullets.end(),
            newBullets.begin(),
            newBullets.end()
        );
    }

    ship.update(dt);

    // Bullets
    for (std::size_t i = 0; i < bullets.size();)
    {
        bullets[i].update(dt);

        if (!bullets[i].isAlive())
        {
            bullets.erase(bullets.begin() + i);
        }
        else
        {
            ++i;
        }
    }

    // Wave Number
    if (asteroids.empty() &&
        state == GameState::PLAYING)
    {
        waveNumber++;

        ui.setWaveNumber(waveNumber);

        waveClock.restart();
        state = GameState::SHOWING_WAVE;

        bullets.clear();
        ship.resetPosition();

        isInvincible = true;
        invincibilityClock.restart();
    }

    if (state == GameState::SHOWING_WAVE &&
        waveClock.getElapsedTime().asSeconds() > 2.0f)
    {
        int count =
            Constants::ASTEROID_START_COUNT +
            (waveNumber - 1) * 2;

        float speedMult =
            1.f + (waveNumber - 1) * 0.2f;

        spawnAsteroids(count, speedMult);

        state = GameState::PLAYING;
    }

    // Asteroids
    for (auto& asteroid : asteroids)
    {
        asteroid.update(dt);
    }

    // Collisions
    handleCollisions();
}

void Game::render()
{
    window.clear(sf::Color::Black);

    if (state == GameState::PLAYING ||
        state == GameState::PAUSED)
    {
        for (auto& asteroid : asteroids)
        {
            asteroid.draw(window);
        }

        for (auto& b : bullets)
        {
            b.draw(window);
        }

        if (!isInvincible ||
            (static_cast<int>(
                 invincibilityClock
                     .getElapsedTime()
                     .asMilliseconds() / 200) %
             2))
        {
            ship.draw(window);
        }
    }

    ui.draw(
        window,
        lives,
        score,
        waveNumber,
        state
    );

    window.display();
}

void Game::handleCollisions()
{
    // Bullets vs Asteroids
    for (std::size_t i = 0; i < bullets.size();)
    {
        bool bulletHit = false;

        for (std::size_t j = 0; j < asteroids.size();)
        {
            sf::Vector2f bulletPos =
                bullets[i].getShape().getPosition();

            sf::Vector2f asteroidPos =
                asteroids[j].getSprite().getPosition();

            float dx = bulletPos.x - asteroidPos.x;
            float dy = bulletPos.y - asteroidPos.y;

            float distance =
                std::sqrt(dx * dx + dy * dy);

            if (distance < asteroids[j].getRadius())
            {
                float oldScale =
                    asteroids[j].getScale();

                if (oldScale > Constants::ASTEROID_MIN_SCALE)
                {
                    // Split into 2 smaller asteroids
                    for (int s = 0; s < 2; ++s)
                    {
                        float newScale =
                            oldScale / 2.f;

                        float angle =
                            static_cast<float>(
                                (std::rand() % 360) *
                                Constants::PI /
                                180.0f
                            );

                        float speed =
                            static_cast<float>(
                                (std::rand() % 50) +
                                50.0f
                            );

                        sf::Vector2f vel(
                            std::cos(angle) * speed,
                            std::sin(angle) * speed
                        );

                        asteroids.emplace_back(
                            newScale,
                            asteroidPos,
                            vel
                        );
                    }

                    score += 100;
                }
                else
                {
                    score += 200;
                }

                asteroids.erase(
                    asteroids.begin() + j
                );

                bullets.erase(
                    bullets.begin() + i
                );

                bulletHit = true;
                break;
            }
            else
            {
                ++j;
            }
        }

        if (!bulletHit)
        {
            ++i;
        }
    }

    // Ship vs Asteroids
    if (!isInvincible)
    {
        for (auto& asteroid : asteroids)
        {
            sf::Vector2f shipPos =
                ship.getPosition();

            sf::Vector2f asteroidPos =
                asteroid.getSprite().getPosition();

            float dx =
                shipPos.x - asteroidPos.x;

            float dy =
                shipPos.y - asteroidPos.y;

            float distance =
                std::sqrt(dx * dx + dy * dy);

            if (distance <
                asteroid.getRadius() +
                Constants::SHIP_COLLISION_RADIUS)
            {
                lives--;

                if (lives < 0)
                {
                    state = GameState::GAME_OVER;
                    gameOverClock.restart();
                }
                else
                {
                    ship.resetPosition();

                    isInvincible = true;
                    invincibilityClock.restart();

                    canControlShip = false;
                }

                break;
            }
        }
    }
}

void Game::resetGame()
{
    score = 0;
    lives = Constants::INITIAL_LIVES;

    bullets.clear();
    asteroids.clear();

    ship.resetPosition();

    isInvincible = true;
    invincibilityClock.restart();

    canControlShip = false;

    spawnAsteroids(
        Constants::ASTEROID_START_COUNT,
        1.f
    );

    state = GameState::PLAYING;
}

void Game::spawnAsteroids(int count, float speedMult)
{
    for (int i = 0; i < count; ++i)
    {
        float scale =
            0.5f +
            (std::rand() % 150) / 100.0f;

        float x =
            static_cast<float>(
                std::rand() %
                static_cast<int>(Constants::SCREEN_WIDTH)
            );

        float y =
            static_cast<float>(
                std::rand() %
                static_cast<int>(Constants::SCREEN_HEIGHT)
            );

        float vx =
            static_cast<float>(
                (std::rand() % 101) - 30
            );

        float vy =
            static_cast<float>(
                (std::rand() % 101) - 30
            );

        asteroids.emplace_back(
            scale,
            sf::Vector2f(x, y),
            sf::Vector2f(vx * speedMult, vy * speedMult)
        );
    }
}