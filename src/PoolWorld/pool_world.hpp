#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include "ball.hpp"
#include "stick.hpp"
class Score;
#include "../Game/game.hpp"

class PoolWorld{
private:
	sf::RectangleShape pool;
	std::shared_ptr<sf::Vector2u> main_window_size;
	std::vector<std::unique_ptr<sf::CircleShape>> holes;
	std::unique_ptr<Ball> white_ball;
	//TODO: make this vector
	std::unique_ptr<Ball> _balls;

	std::unique_ptr<Stick> _stick;

	void setUpPool();
	void setUpHoles();
	void setUpWhiteBall();
	//TODO: make this vector
	void setUpBalls();
	//TODO: needs refactoring using the same code on two different functions!
	bool checkBallCollisonWithHoles(const sf::CircleShape&, const sf::CircleShape&);

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
	void moveStik(unsigned int& FPS);

	const std::unique_ptr<sf::RectangleShape>& getStickShape() const;
	const std::unique_ptr<Stick>& getStick() const;


	void updateScore(const std::unique_ptr<Score>&);
};