#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include "ball.hpp"

class Stick{
private:
    std::unique_ptr<sf::RectangleShape> _stick;
    bool _visibility;

public:
    Stick();
    const std::unique_ptr<sf::RectangleShape>& getStick() const;
    bool visibilityStatus();
    void makeVisibile(const sf::Vector2f& coordinate);
    void makeInvisible();
    void moveStick(const sf::Vector2f& ballPos, const float& mouseX, const float& mouseY);
    void hitBall(const std::unique_ptr<Ball> & whiteBall);
};