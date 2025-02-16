#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>

class PoolWorld{
private:
	sf::RectangleShape pool;
	std::shared_ptr<sf::Vector2u> main_window_size;
	std::vector<std::unique_ptr<sf::CircleShape>> holes;
	std::unique_ptr<sf::CircleShape> white_ball;
	sf::Vector2f velocity{500.f, 500.f};

	void setUpPool();
	void setUpHoles();
	void setUpWhiteBall();

public:
	PoolWorld(std::shared_ptr<sf::Vector2u>);
	sf::RectangleShape getPool();
	const std::vector<std::unique_ptr<sf::CircleShape>>& getHoles() const;
	const std::unique_ptr<sf::CircleShape>& getWhiteBall() const;
	void moveWhiteBall();
	void handleWallCollision();
};