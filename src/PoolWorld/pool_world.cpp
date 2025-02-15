#include "pool_world.hpp"

PoolWorld::PoolWorld(std::shared_ptr<sf::Vector2u> window_size) : main_window_size{window_size} {
	this->setUpPool();
	this->setUpHoles();
}

sf::RectangleShape PoolWorld::getPool() {
	return this->pool;
}

void PoolWorld::setUpPool() {
	this->pool.setSize(sf::Vector2f(this->main_window_size->x - 100,
		this->main_window_size->y - 50));
	this->pool.setFillColor(sf::Color::Green);
	this->pool.setOutlineColor(sf::Color::Black);
	this->pool.setOutlineThickness(10.f);
	this->pool.setPosition(
		sf::Vector2f((this->main_window_size->x - this->pool.getSize().x) / 2.f,
			(this->main_window_size->y - this->pool.getSize().y) / 2.f));
	//this->pool.setScale();
}

void PoolWorld::setUpHoles() {
	float xPoss[3] = { (this->main_window_size->x - this->pool.getSize().x) / 2.f,
					this->pool.getSize().x ,
					(this->main_window_size->x) / 2.f };
	float yPoss[2] = { (this->main_window_size->y - this->pool.getSize().y) / 2.f, 0 };
	yPoss[1] = this->pool.getSize().y - yPoss[0];

	for(auto& x: xPoss)
		for (auto& y : yPoss) {
			sf::CircleShape hole{ 25 };
			hole.setFillColor(sf::Color::Black);
			hole.setPosition(sf::Vector2f(x, y));
			this->holes.push_back(std::make_unique<sf::CircleShape>(hole));
		}
}

const std::vector<std::unique_ptr<sf::CircleShape>>& PoolWorld::getHoles() const {
	return this->holes;
}