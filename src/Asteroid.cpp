#include "Asteroid.hpp"
#include "Constants.hpp"
#include <iostream>

sf::Texture Asteroid::texture;

Asteroid::Asteroid(float scale,
                   const sf::Vector2f& position,
                   const sf::Vector2f& velocity)
    : sprite(texture),
      velocity(velocity),
      radius(0.f),
      scale(scale)
{
    if (texture.getSize().x == 0)
    {
        if (!texture.loadFromFile("assets/asteroid_asteroids.png"))
        {
            std::cerr << "Failed to load assets/asteroid_asteroids.png\n";
        }
    }

    sprite.setTextureRect(sf::IntRect(
        {0, 0},
        {
            static_cast<int>(texture.getSize().x),
            static_cast<int>(texture.getSize().y)
        }
    ));

    sprite.setOrigin({
        static_cast<float>(texture.getSize().x) / 2.f,
        static_cast<float>(texture.getSize().y) / 2.f
    });

    sprite.setPosition(position);

    sprite.setScale({
        scale * 2.f,
        scale * 2.f
    });

    radius =
        (static_cast<float>(texture.getSize().x) / 2.f) * scale;
}

void Asteroid::update(float dt)
{
    sprite.move(velocity * dt);

    sf::Vector2f pos = sprite.getPosition();

    if (pos.x < 0.f)
        pos.x += Constants::SCREEN_WIDTH;

    if (pos.x > Constants::SCREEN_WIDTH)
        pos.x -= Constants::SCREEN_WIDTH;

    if (pos.y < 0.f)
        pos.y += Constants::SCREEN_HEIGHT;

    if (pos.y > Constants::SCREEN_HEIGHT)
        pos.y -= Constants::SCREEN_HEIGHT;

    sprite.setPosition(pos);
}

void Asteroid::draw(sf::RenderWindow& window) const
{
    window.draw(sprite);
}

const sf::Sprite& Asteroid::getSprite() const
{
    return sprite;
}

float Asteroid::getRadius() const
{
    return radius;
}

float Asteroid::getScale() const
{
    return scale;
}