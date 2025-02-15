#include "game.hpp"
#include <iostream>

Game::Game() : window_size{std::make_shared<sf::Vector2u>(1500u, 700u)},
               window{std::make_unique<sf::RenderWindow>(sf::VideoMode(*this->window_size), "Not sure what to put?",
                sf::Style::Titlebar | sf::Style::Close)} {

    this->window->setFramerateLimit(60);
    this->pool_world = std::make_unique<PoolWorld>(this->window_size);
}

Game::~Game() {
}

const bool Game::running() const {
    return this->window->isOpen();
}

void Game::pollEvent() {
    while (this->event = window->pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                this->window->close();
            }
            else if(const auto* keyPressed = this->event->getIf<sf::Event::KeyPressed>()) {
                switch (keyPressed->scancode)
                {
                case sf::Keyboard::Scancode::Escape:
                    this->window->close();
                    break;
                case sf::Keyboard::Scancode::A:
                    std::cout << "yooooooo\n";
                    break;
                default:
                    break;
                }
            }

            sf::Vector2i mousePos = sf::Mouse::getPosition(*this->window);
        }
}

void Game::update() {
    this->pollEvent();
}

void Game::render() {
    this->window->clear();

    this->drawObjects();

    this->window->display();
}

void Game::drawObjects() const {
    this->window->draw(this->pool_world->getPool());
    const std::vector<std::unique_ptr<sf::CircleShape>>& holes = this->pool_world->getHoles();
    for (auto const& hole : holes) {
        this->window->draw(*hole);
    }
}