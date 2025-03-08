#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>

class Ball {
private:
	std::unique_ptr<sf::CircleShape> _ball;
	sf::Vector2f velocity;
	bool _visibilty;
	sf::Vector2f _originalPos;
public:
	Ball(float radious, sf::Vector2f pos);
	void move(unsigned int& FPS);
	void setVelocity(sf::Vector2f& newVel);
	void handleWallCollision(sf::Vector2f& window_size, sf::Vector2f& board_size);
	const std::unique_ptr<sf::CircleShape>& getBall() const;
	bool checkCollision(const Ball& other) const;
	void handleBallCollision(Ball& other);
	bool visibilityStatus();
    void makeVisibile();
    void makeInvisible();
};