#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

class Stick{
private:
    std::unique_ptr<sf::RectangleShape> _stick;
    bool _visibility;

public:
    Stick();
    const std::unique_ptr<sf::RectangleShape>& getStick() const;
    bool visibilityStatus();
    void makeVisibile();
    void makeInvisible();
};