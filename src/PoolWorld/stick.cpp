#include "stick.hpp"
#include <iostream>
#include <cmath>

Stick::Stick(): _stick {std::make_unique<sf::RectangleShape>(sf::Vector2f{500.f, 30.f})}, _visibility{false}{

    this->_stick->setPosition(sf::Vector2f{500.f, 500.f});
    this->_stick->setFillColor(sf::Color(139, 69, 19));

};

const std::unique_ptr<sf::RectangleShape>& Stick::getStick() const {
    return this->_stick;
}

bool Stick::visibilityStatus() {
    return this->_visibility;
}

void Stick::makeVisibile(sf::Vector2f const& coordinate) {
    // TODO: Remove magic numbers
    this->_stick->setPosition(sf::Vector2f(coordinate.x - 500.f - 5.f, coordinate.y + 4.f));
    sf::Angle angle = sf::radians(0);
    this->_stick->setRotation(angle);
    this->_visibility = true;
}

void Stick::makeInvisible() {
    this->_visibility = false;
}

void Stick::moveStick(const sf::Vector2f& ballPos, const float& mouseX, const float& mouseY) {

    auto differenceX = ballPos.x - mouseX;
    auto differenceY = ballPos.y - mouseY;

    float magnitude = std::sqrt(differenceX * differenceX + differenceY * differenceY);
    
    sf::Vector2f direction(mouseX - ballPos.x, mouseY - ballPos.y);

    float maxDistancePixel = 200.f;

    if (magnitude > maxDistancePixel) {
        direction = direction / magnitude * maxDistancePixel;
    }

    sf::Vector2f stickPosition = ballPos + direction;

    float angleInRadians = std::atan2(direction.y, direction.x);

    sf::Angle angle = sf::radians(angleInRadians);

    // Set the position and rotation of the stick
    this->_stick->setPosition(sf::Vector2f(stickPosition.x, stickPosition.y + 4.f));
    this->_stick->setRotation(angle);
}

void Stick::hitBall(const std::unique_ptr<Ball> & whiteBall) {
    auto vel = this->_stick->getPosition() - whiteBall->getBall()->getPosition();
    vel.x *= -6.5; /*I've just tested different numbers*/
    vel.y *= -6.5;
    whiteBall->setVelocity(vel);
}