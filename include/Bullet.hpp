#pragma once
#include <SFML/Graphics.hpp>

class Bullet {
    public:
        Bullet(const sf::Vector2f& position, const sf::Vector2f& velocity);

        void update(float dt);
        void draw(sf::RenderWindow& window) const;
        bool isAlive() const;

        const sf::CircleShape& getShape() const;

    private:
        sf::CircleShape shape;
        sf::Vector2f velocity;
        float lifetime;
};