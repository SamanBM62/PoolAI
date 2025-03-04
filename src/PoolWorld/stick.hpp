#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include "ball.hpp"

class Stick{
private:
    std::unique_ptr<sf::RectangleShape> _stick;
    bool _visibility;
    bool _shouldMove;
    sf::Vector2f _velocity;
public:
    Stick();
    const std::unique_ptr<sf::RectangleShape>& getStick() const;
    bool visibilityStatus();
    void makeVisibile(const sf::Vector2f& coordinate);
    void makeInvisible();
    void moveStick(const sf::Vector2f& ballPos, const float& mouseX, const float& mouseY);
    void hitBall(const std::unique_ptr<Ball> & whiteBall);
    void handleWhiteBallCollision(const std::unique_ptr<Ball> & whiteBall);
    void moveToWhiteBall(unsigned int& FPS, const std::unique_ptr<Ball> & whiteBall);
    void setVelocity(sf::Vector2f& newVel);
    bool checkWhiteBallCollision(const std::unique_ptr<Ball> & whiteBall);
    void startMoving();
};