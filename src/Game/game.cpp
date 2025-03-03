#include "game.hpp"
#include <iostream>

Game::Game() : window_size{std::make_shared<sf::Vector2u>(1500u, 700u)},
               window{std::make_unique<sf::RenderWindow>(sf::VideoMode(*this->window_size), "Not sure what to put?",
                sf::Style::Titlebar | sf::Style::Close)} {

    this->_FPS = 60;
    this->window->setFramerateLimit(this->_FPS);
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
                case sf::Keyboard::Scancode::V:
                    this->pool_world->getStick()->makeVisibile(this->pool_world->getWhiteBall()->getPosition());
                    break;
                case sf::Keyboard::Scancode::S:
                    this->pool_world->shootBall();
                    break;
                case sf::Keyboard::Scancode::I:
                    this->pool_world->getStick()->makeInvisible();
                    break;
                default:
                    break;
                }
            }

            if (const auto* mouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>())
            {
                if (mouseButtonPressed->button == sf::Mouse::Button::Left)
                {
                    if (this->pool_world->getWhiteBall()->getGlobalBounds().contains(sf::Vector2f(mouseButtonPressed->position.x, mouseButtonPressed->position.y))
                        && !this->pool_world->getStick()->visibilityStatus()) {

                        auto ballPosition = this->pool_world->getWhiteBall()->getPosition();
                        auto radius = this->pool_world->getWhiteBall()->getRadius();
                        this->pool_world->getStick()->makeVisibile(sf::Vector2f(ballPosition + sf::Vector2f(radius, radius)));
                    }
                }
            }

            if (const auto* mouseButtonReleased = event->getIf<sf::Event::MouseButtonReleased>())
            {
                if (mouseButtonReleased->button == sf::Mouse::Button::Left && this->pool_world->getStick()->visibilityStatus())
                {
                    // this->pool_world->getStick()->makeInvisible();
                    // this->pool_world->shootBall();
                    this->pool_world->getStick()->m
                }
            }

            if (const auto* mouseMoved = event->getIf<sf::Event::MouseMoved>())
            {
                if(this->pool_world->getStick()->visibilityStatus()) {
                    auto ballPosition = this->pool_world->getWhiteBall()->getPosition();
                    auto radius = this->pool_world->getWhiteBall()->getRadius();

                    this->pool_world->getStick()->moveStick(sf::Vector2f(ballPosition + sf::Vector2f(radius, radius)), mouseMoved->position.x, mouseMoved->position.y);
                }
            }

            sf::Vector2i mousePos = sf::Mouse::getPosition(*this->window);
        }
}

void Game::update() {
    this->pollEvent();
    this->pool_world->moveWhiteBall(this->_FPS);
    this->pool_world->moveBalls(this->_FPS);
    this->pool_world->handleWallCollision();
    
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

    this->window->draw(*this->pool_world->getWhiteBall());
    this->window->draw(*this->pool_world->getBalls());
    if(this->pool_world->getStick()->visibilityStatus())
        this->window->draw(*this->pool_world->getStickShape());
}