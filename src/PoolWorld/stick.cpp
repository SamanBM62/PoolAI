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

void Stick::moveStick(const sf::Vector2f& ballPos, float mouseX, float mouseY) {

    auto differenceX = ballPos.x - mouseX;
    auto differenceY = ballPos.y - mouseY;

    // Calculate the magnitude (distance) between the ball and the mouse
    float magnitude = std::sqrt(differenceX * differenceX + differenceY * differenceY);
    
    sf::Vector2f direction(mouseX - ballPos.x, mouseY - ballPos.y);

    // If the magnitude is greater than 500, scale the direction vector to 500 pixels
    if (magnitude > 100.f) {
        // Normalize the vector and scale it to 500 pixels
        direction = direction / magnitude * 100.f;
    }

    // Set the position of the stick to be 500 pixels away from the ball, in the direction of the mouse
    sf::Vector2f stickPosition = ballPos + direction;

    // Calculate the angle using the direction vector
    float angleInRadians = std::atan2(direction.y, direction.x);

    // Convert to sf::Angle
    sf::Angle angle = sf::radians(angleInRadians);

    // Set the position and rotation of the stick
    this->_stick->setPosition(sf::Vector2f(stickPosition.x, stickPosition.y + 4.f));
    this->_stick->setRotation(angle);
}