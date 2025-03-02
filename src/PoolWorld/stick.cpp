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
    this->_stick->setPosition(sf::Vector2f(coordinate.x - 30.f, coordinate.y + 5.f));
    float angleInRadians = std::atan2(0, -1);
    sf::Angle angle = sf::radians(angleInRadians);
    this->_stick->setRotation(angle);
    this->_visibility = true;
}

void Stick::makeInvisible() {
    this->_visibility = false;
}

void Stick::moveStick(const sf::Vector2f &ballPos, const float& mouseX, const float& mouseY) {

    // ballPos.x = -ballPos.x;
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
    auto ballPosition = whiteBall->getBall()->getPosition();
    auto radius = whiteBall->getBall()->getRadius();

    auto vel = this->_stick->getPosition() - sf::Vector2f(ballPosition + sf::Vector2f(radius, radius));
    std::cout << "stick position " << this->_stick->getPosition().x << " " << this->_stick->getPosition().y << std::endl;
    std::cout << "ball position " << whiteBall->getBall()->getPosition().x << " " << whiteBall->getBall()->getPosition().y << std::endl;
    std::cout << "vel position " << vel.x << " " << vel.y << std::endl;
    vel.x *= -6.5; /*I've just tested different numbers*/
    vel.y *= -6.5;
    whiteBall->setVelocity(vel);
}