#pragma once
#include <SFML/Graphics.hpp>
#include "Constants.hpp"

class UI {
public:
    UI() = default;
    bool loadFont(const std::string& path);

    void draw(sf::RenderWindow& window,
              int lives, int score, int waveNumber,
              GameState state);

    sf::Text livesText;
    sf::Text scoreText;
    sf::Text wavesText;
    sf::Text gameOverText0;
    sf::Text gameOverText;
    sf::Text levelText;
    sf::Text pausedText;

    void setWaveNumber(int waveNumber);
    
private:
    sf::Font font;
};
