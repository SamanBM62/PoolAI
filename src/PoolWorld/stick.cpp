#include "stick.hpp"

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
    this->_visibility = true;
}

void Stick::makeInvisible() {
    this->_visibility = false;
}