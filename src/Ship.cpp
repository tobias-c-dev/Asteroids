#include "Ship.hpp"
#include "Constants.hpp"
#include <iostream>
#include <cmath>

Ship::Ship()
    : texture(),
      sprite(texture),
      velocity(0.f, 0.f),
      thrust(Constants::SHIP_THRUST),
      rotationSpeed(Constants::SHIP_ROT_SPEED),
      damping(Constants::SHIP_FRICTION),
      canFire(true),
      bulletSpeed(Constants::BULLET_SPEED)
{
    if (!texture.loadFromFile("assets/ship_asteroids.png"))
    {
        std::cerr << "Failed to load ship texture\n";
    }

    sprite.setTexture(texture);

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

    float scale =
        Constants::SHIP_SIZE /
        static_cast<float>(texture.getSize().y);

    sprite.setScale({
        1.5f * scale,
        1.5f * scale
    });

    sprite.setPosition({
        Constants::SCREEN_WIDTH / 2.f,
        Constants::SCREEN_HEIGHT / 2.f
    });

    sprite.setRotation(sf::degrees(0.f));
}


void Ship::handleInput(float dt)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
        sprite.rotate(sf::degrees(-rotationSpeed * dt));

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
        sprite.rotate(sf::degrees(rotationSpeed * dt));

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
    {
        float angleRad =
            Constants::degToRad(sprite.getRotation().asDegrees());

        sf::Vector2f direction(
            std::sin(angleRad),
            -std::cos(angleRad)
        );

        velocity += direction * thrust * dt;
    }
}

void Ship::update(float dt)
{
    sprite.move(velocity * dt);
    velocity *= damping;

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

void Ship::draw(sf::RenderWindow& window) const
{
    window.draw(sprite);
}

std::vector<Bullet> Ship::shoot()
{
    std::vector<Bullet> newBullets;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
    {
        if (canFire)
        {
            float angleRad =
                Constants::degToRad(sprite.getRotation().asDegrees());

            sf::Vector2f direction(
                std::sin(angleRad),
                -std::cos(angleRad)
            );

            sf::Vector2f bulletVelocity =
                direction * bulletSpeed + velocity;

            sf::FloatRect bounds = sprite.getLocalBounds();

            sf::Vector2f noseLocal(
                bounds.position.x + bounds.size.x / 2.f,
                bounds.position.y
            );

            sf::Vector2f noseWorld =
                sprite.getTransform().transformPoint(noseLocal);

            newBullets.emplace_back(noseWorld, bulletVelocity);

            canFire = false;
        }
    }
    else
    {
        canFire = true;
    }

    return newBullets;
}

void Ship::resetPosition()
{
    sprite.setPosition({
        Constants::SCREEN_WIDTH / 2.f,
        Constants::SCREEN_HEIGHT / 2.f
    });

    sprite.setRotation(sf::degrees(0.f));
    velocity = {0.f, 0.f};
}

const sf::Sprite& Ship::getSprite() const
{
    return sprite;
}

sf::Vector2f Ship::getPosition() const
{
    return sprite.getPosition();
}