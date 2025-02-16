#include "pool_world.hpp"

PoolWorld::PoolWorld(std::shared_ptr<sf::Vector2u> window_size) : main_window_size{window_size} {
	this->setUpPool();
	this->setUpHoles();
	this->setUpWhiteBall();
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
			auto hole{ std::make_unique < sf::CircleShape>(25) };
			hole->setFillColor(sf::Color::Black);
			hole->setPosition(sf::Vector2f(x, y));
			this->holes.push_back(std::move(hole));
		}
}

const std::vector<std::unique_ptr<sf::CircleShape>>& PoolWorld::getHoles() const {
	return this->holes;
}

void PoolWorld::setUpWhiteBall() {
	this->white_ball = std::make_unique < sf::CircleShape>(20);
	this->white_ball->setPosition(
		sf::Vector2f((this->main_window_size->x) / 2.f,
			(this->main_window_size->y ) / 2.f)
	);
}

const std::unique_ptr<sf::CircleShape>& PoolWorld::getWhiteBall() const {
	return this->white_ball;
}

void PoolWorld::moveWhiteBall() {
	// Move the ball according to its velocity
	this->white_ball->move(velocity * (1.f/60.f));

	// Apply friction to gradually slow the ball down
	float friction = 0.98f;  // Adjust for stronger/weaker friction
	velocity *= friction;

	// Stop ball if velocity is very low
	if (std::abs(velocity.x) < 0.1f) velocity.x = 0;
	if (std::abs(velocity.y) < 0.1f) velocity.y = 0;
}

void PoolWorld::handleWallCollision() {
	sf::Vector2f pos = this->white_ball->getPosition();
	float radius = this->white_ball->getRadius();

	// Left & right walls
	if (pos.x < 0) {
		pos.x = 0;
		velocity.x = -velocity.x;
	}
	else if (pos.x + 2 * radius > this->main_window_size->x) {
		pos.x = this->main_window_size->x - 2 * radius;
		velocity.x = -velocity.x;
	}

	// Top & bottom walls
	if (pos.y < 0) {
		pos.y = 0;
		velocity.y = -velocity.y;
	}
	else if (pos.y + 2 * radius > this->main_window_size->y) {
		pos.y = this->main_window_size->y - 2 * radius;
		velocity.y = -velocity.y;
	}

	this->white_ball->setPosition(pos);
}

