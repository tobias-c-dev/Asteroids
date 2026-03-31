#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Bullet.hpp"

class Ship {
public:
    Ship();

    void handleInput(float dt);
    void update(float dt);
    void draw(sf::RenderWindow& window) const;

    std::vector<Bullet> shoot();

    void resetPosition();

    const sf::Sprite& getSprite() const;
    sf::Vector2f getPosition() const;

private:
    // sprite & texture for pixel-art ship
    sf::Texture texture;
    sf::Sprite sprite;

    sf::Vector2f velocity;

    float thrust;
    float rotationSpeed;
    float damping;

    bool canFire;
    float bulletSpeed;
};
