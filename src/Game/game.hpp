#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include "../PoolWorld/pool_world.hpp"

class Game {
    std::shared_ptr<sf::Vector2u> window_size;
    std::unique_ptr<sf::RenderWindow> window;
    std::optional<sf::Event> event{};
    std::unique_ptr<PoolWorld> pool_world;
    unsigned int _FPS;

    void pollEvent();
    void drawObjects() const;
public:
    Game();
    ~Game();
    const bool running() const;
    void update();
    void render();
};
