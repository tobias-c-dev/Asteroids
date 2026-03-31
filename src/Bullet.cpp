#include "Bullet.hpp"
#include "Constants.hpp"

Bullet::Bullet(const sf::Vector2f& position, const sf::Vector2f& velocity)
    : velocity(velocity), lifetime(Constants::BULLET_LIFETIME)
{
    shape.setRadius(Constants::BULLET_RADIUS);
    shape.setFillColor(sf::Color::White);
    shape.setOrigin(Constants::BULLET_RADIUS, Constants::BULLET_RADIUS);
    shape.setPosition(position);
}


void Bullet::update(float dt) {
    lifetime -= dt;
    shape.move(velocity * dt);

    sf::Vector2f pos = shape.getPosition();
    if (pos.x < 0.f) pos.x = Constants::SCREEN_WIDTH;
    if (pos.x > Constants::SCREEN_WIDTH) pos.x = 0.f;
    if (pos.y < 0.f) pos.y = Constants::SCREEN_HEIGHT;
    if (pos.y > Constants::SCREEN_HEIGHT) pos.y = 0.f;
    shape.setPosition(pos);
}


void Bullet::draw(sf::RenderWindow& window) const {
    window.draw(shape);
}


bool Bullet::isAlive() const {
    return lifetime > 0.f;
}


const sf::CircleShape& Bullet::getShape() const {
    return shape;
}