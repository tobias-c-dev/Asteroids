#pragma once

namespace Constants
{
    // Window
    inline float SCREEN_WIDTH = 800.0f;
    inline float SCREEN_HEIGHT = 600.0f;

    // Math
    constexpr float PI = 3.14159265358979323846f;

    constexpr inline float degToRad(float degrees)
    {
        return degrees * PI / 180.0f;
    }

    // Ship
    constexpr float SHIP_SIZE = 60.f;
    constexpr float SHIP_COLLISION_RADIUS = 55.0f;
    constexpr float SHIP_THRUST = 200.0f;
    constexpr float SHIP_ROT_SPEED = 100.0f;
    constexpr float SHIP_FRICTION = 0.9998f;

    // Bullets
    constexpr float BULLET_SPEED = 400.0f;
    constexpr float BULLET_LIFETIME = 1.5f;
    constexpr float BULLET_RADIUS = 2.0f;

    // Asteroids
    constexpr float ASTEROID_MIN_RADIUS = 40.0f;
    constexpr int ASTEROID_START_COUNT = 3;
    constexpr float ASTEROID_MIN_SCALE = 0.5f;

    // Game Rules
    constexpr int INITIAL_LIVES = 3;
    constexpr float INVINCIBILITY_DURATION = 3.0f;
    constexpr float CONTROL_DELAY = 1.0f;
}

enum class GameState
{
    PLAYING,
    PAUSED,
    GAME_OVER,
    SHOWING_WAVE
};