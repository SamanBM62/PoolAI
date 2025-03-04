#include "stick.hpp"
#include <iostream>
#include <cmath>

Stick::Stick(): _stick {std::make_unique<sf::RectangleShape>(sf::Vector2f{500.f, 30.f})}, _visibility{false}, _shouldMove{false}{

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
    whiteBall->setVelocity(this->_velocity);
}

void Stick::handleWhiteBallCollision(const std::unique_ptr<Ball> & whiteBall) {
    this->hitBall(whiteBall);
    this->_velocity = sf::Vector2f(0.f, 0.f);
    this->makeInvisible();
    this->_shouldMove = false;
}

bool Stick::checkWhiteBallCollision(const std::unique_ptr<Ball> & whiteBall) {
    sf::Vector2f circleCenter = whiteBall->getBall()->getPosition();
    sf::FloatRect rectangleBounds = this->_stick->getGlobalBounds(); // Rectangle bounds
    float circleRadius = whiteBall->getBall()->getRadius();

    // Find the closest point on the rectangle to the circle's center
    float closestX = std::max(rectangleBounds.position.x, std::min(circleCenter.x, rectangleBounds.position.x + rectangleBounds.size.x));
    float closestY = std::max(rectangleBounds.position.y, std::min(circleCenter.y, rectangleBounds.position.y + rectangleBounds.size.y));

    // Calculate the distance from the circle’s center to the closest point
    sf::Vector2f diff = circleCenter - sf::Vector2f(closestX, closestY);
    float distance = std::sqrt(diff.x * diff.x + diff.y * diff.y);

    // Check for collision
    return distance <= circleRadius;
}

void Stick::moveToWhiteBall(unsigned int& FPS, const std::unique_ptr<Ball> & whiteBall) {
    if (!this->_shouldMove)
        return;

    this->_stick->move(this->_velocity * (1.f / FPS));
    if(this->checkWhiteBallCollision(whiteBall))
        this->handleWhiteBallCollision(whiteBall);
}

void Stick::setVelocity(sf::Vector2f& newVel) {
    this->_velocity = newVel;
}

void Stick::startMoving() {
    this->_shouldMove = true;
}