#include "game.hpp"
#include <iostream>

Game::Game(): window {new sf::RenderWindow{sf::VideoMode({1000u, 500u}), "Not sure what to put?", 
         sf::Style::Titlebar | sf::Style::Close}} {

}

Game::~Game() {
    delete this->window;
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
                case sf::Keyboard::Scancode::B:
                    std::cout << "hellllllooooooooo\n";
                    break;
                case sf::Keyboard::Scancode::N:
                    std::cout << "coffeeeeeeeeee\n";
                    break;
                default:
                    break;
                }
            }
        }
}

void Game::update() {
    this->pollEvent();
}

void Game::render() {
    this->window->clear(sf::Color(255, 0, 0));
    this->window->display();
}