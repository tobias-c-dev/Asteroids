#pragma once

#include <SFML/Graphics.hpp>

class Asteroid
{
public:
    Asteroid(float scale,
             const sf::Vector2f& position,
             const sf::Vector2f& velocity);

    void update(float dt);
    void draw(sf::RenderWindow& window) const;

    const sf::Sprite& getSprite() const;
    float getRadius() const;
    float getScale() const;

private:
    static sf::Texture texture;
    sf::Sprite sprite;
    sf::Vector2f velocity;
    float radius;
    float scale;
};