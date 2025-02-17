#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include "ball.hpp"

class PoolWorld{
private:
	sf::RectangleShape pool;
	std::shared_ptr<sf::Vector2u> main_window_size;
	std::vector<std::unique_ptr<sf::CircleShape>> holes;
	std::unique_ptr<Ball> white_ball;
	//TODO: make this vector
	std::unique_ptr<Ball> _balls;

	void setUpPool();
	void setUpHoles();
	void setUpWhiteBall();
	//TODO: make this vector
	void setUpBalls();

public:
	PoolWorld(std::shared_ptr<sf::Vector2u>);
	sf::RectangleShape getPool();
	const std::vector<std::unique_ptr<sf::CircleShape>>& getHoles() const;
	const std::unique_ptr<sf::CircleShape>& getWhiteBall() const;
	//TODO: make this vector
	const std::unique_ptr<sf::CircleShape>& getBalls() const;
	void moveWhiteBall(unsigned int& FPS);
	//TODO: make this vector
	void moveBalls(unsigned int& FPS);
	void handleWallCollision();
	void shootBall();
};