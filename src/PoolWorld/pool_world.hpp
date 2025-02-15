#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>

class PoolWorld{
private:
	sf::RectangleShape pool;
	std::shared_ptr<sf::Vector2u> main_window_size;
	std::vector<std::unique_ptr<sf::CircleShape>> holes;

	void setUpPool();
	void setUpHoles();

public:
	PoolWorld(std::shared_ptr<sf::Vector2u>);
	sf::RectangleShape getPool();
	const std::vector<std::unique_ptr<sf::CircleShape>>& getHoles() const;
};