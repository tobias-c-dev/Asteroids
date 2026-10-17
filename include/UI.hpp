#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include "Constants.hpp"

class UI
{
public:
    UI();

    bool loadFont(const std::string& path);

    void draw(
        sf::RenderWindow& window,
        int lives,
        int score,
        int waveNumber,
        GameState state
    );

    void setWaveNumber(int waveNumber);

private:
    sf::Font font;

    sf::Text livesText;
    sf::Text scoreText;
    sf::Text wavesText;
    sf::Text gameOverText0;
    sf::Text gameOverText;
    sf::Text levelText;
    sf::Text pausedText;
};