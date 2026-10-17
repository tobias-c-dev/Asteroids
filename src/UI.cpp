#include "UI.hpp"
#include "Constants.hpp"
#include <iostream>

UI::UI()
    : livesText(font),
      scoreText(font),
      wavesText(font),
      gameOverText0(font),
      gameOverText(font),
      levelText(font),
      pausedText(font)
{
}

bool UI::loadFont(const std::string& path)
{
    if (!font.openFromFile(path))
    {
        std::cerr << "Font not found in current working directory"
                  << std::endl;
        return false;
    }

    livesText.setFillColor(sf::Color::Red);
    livesText.setCharacterSize(50);
    livesText.setPosition({10.f, 10.f});

    scoreText.setFillColor(sf::Color::Green);
    scoreText.setCharacterSize(50);
    scoreText.setPosition({10.f, 70.f});

    wavesText.setFillColor(sf::Color::Cyan);
    wavesText.setCharacterSize(50);
    wavesText.setPosition({
        static_cast<float>(Constants::SCREEN_WIDTH - 180),
        static_cast<float>(Constants::SCREEN_HEIGHT - 1050)
    });

    levelText.setFillColor(sf::Color::Red);
    levelText.setCharacterSize(100);
    levelText.setPosition({
        static_cast<float>(Constants::SCREEN_WIDTH) / 2.f,
        static_cast<float>(Constants::SCREEN_HEIGHT) / 2.f
    });

    gameOverText0.setFillColor(sf::Color::Red);
    gameOverText0.setCharacterSize(200);
    gameOverText0.setString("GAME OVER!");

    auto textRect0 = gameOverText0.getLocalBounds();

    gameOverText0.setOrigin({
        textRect0.position.x + textRect0.size.x / 2.f,
        textRect0.position.y + textRect0.size.y / 2.f
    });

    gameOverText0.setPosition({
        static_cast<float>(Constants::SCREEN_WIDTH) / 2.f,
        static_cast<float>(Constants::SCREEN_HEIGHT) / 2.f - 30.f
    });

    gameOverText.setFillColor(sf::Color::Magenta);
    gameOverText.setCharacterSize(70);
    gameOverText.setString("PRESS R TO RESTART\nPRESS Q TO QUIT");

    auto textRect = gameOverText.getLocalBounds();

    gameOverText.setOrigin({
        textRect.position.x + textRect.size.x / 2.f,
        textRect.position.y + textRect.size.y / 2.f
    });

    gameOverText.setPosition({
        static_cast<float>(Constants::SCREEN_WIDTH) / 2.f,
        static_cast<float>(Constants::SCREEN_HEIGHT) / 2.f + 350.f
    });

    pausedText.setCharacterSize(80);
    pausedText.setFillColor(sf::Color::Magenta);
    pausedText.setString("PAUSED");

    auto textRectPaused = pausedText.getLocalBounds();

    pausedText.setOrigin({
        textRectPaused.position.x + textRectPaused.size.x / 2.f,
        textRectPaused.position.y + textRectPaused.size.y / 2.f
    });

    pausedText.setPosition({
        static_cast<float>(Constants::SCREEN_WIDTH) / 2.f,
        static_cast<float>(Constants::SCREEN_HEIGHT) / 2.f - 30.f
    });

    return true;
}

void UI::draw(sf::RenderWindow& window,
              int lives,
              int score,
              int waveNumber,
              GameState state)
{
    livesText.setString("Lives:   " + std::to_string(lives));
    scoreText.setString("Score:   " + std::to_string(score));
    wavesText.setString("Wave:    " + std::to_string(waveNumber));

    if (state == GameState::PLAYING)
    {
        window.draw(livesText);
        window.draw(scoreText);
        window.draw(wavesText);
    }
    else if (state == GameState::PAUSED)
    {
        window.draw(livesText);
        window.draw(scoreText);
        window.draw(wavesText);
        window.draw(pausedText);
        window.draw(gameOverText);
    }
    else if (state == GameState::SHOWING_WAVE)
    {
        window.draw(levelText);
    }
    else if (state == GameState::GAME_OVER)
    {
        window.draw(gameOverText0);
        window.draw(gameOverText);
    }
}

void UI::setWaveNumber(int waveNumber)
{
    levelText.setString("Wave:   " + std::to_string(waveNumber));

    auto bounds = levelText.getLocalBounds();

    levelText.setOrigin({
        bounds.position.x + bounds.size.x / 2.f,
        bounds.position.y + bounds.size.y / 2.f
    });

    levelText.setPosition({
        static_cast<float>(Constants::SCREEN_WIDTH) / 2.f,
        static_cast<float>(Constants::SCREEN_HEIGHT) / 2.f
    });
}