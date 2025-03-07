#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
class PoolWorld;
#include "../PoolWorld/pool_world.hpp"


class Score {
private:
    sf::Font _font;
    sf::Text _text;
    int _score;

    void updateScreen();
public:
    Score();
    const sf::Text& getText();
    void increaseScore();
    void decreaseScore();
    void resetScore();
};
class Game {
    std::shared_ptr<sf::Vector2u> window_size;
    std::unique_ptr<sf::RenderWindow> window;
    std::optional<sf::Event> event{};
    std::unique_ptr<PoolWorld> pool_world;
    std::unique_ptr<Score> _score;
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
