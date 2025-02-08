#pragma once

#include <SFML/Graphics.hpp>

class Game {
    sf::RenderWindow* window;
    std::optional<sf::Event> event{};
    void pollEvent();
public:
    Game();
    ~Game();
    const bool running() const;
    void update();
    void render();
};
