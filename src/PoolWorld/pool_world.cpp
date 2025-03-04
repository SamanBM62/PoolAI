#include "pool_world.hpp"

PoolWorld::PoolWorld(std::shared_ptr<sf::Vector2u> window_size) : main_window_size{window_size}, _stick{std::make_unique < Stick>()} {
	this->setUpPool();
	this->setUpHoles();
	this->setUpWhiteBall();
	this->setUpBalls();
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
	this->white_ball = std::make_unique <Ball>(20, 
		sf::Vector2f((this->main_window_size->x) / 2.f,
					(this->main_window_size->y) / 2.f)
		);
}

void PoolWorld::setUpBalls()
{
	this->_balls = std::make_unique <Ball>(20,
		sf::Vector2f((this->main_window_size->x) / 2.f + 200.f,
			(this->main_window_size->y) / 2.f)
		);
	this->_balls->getBall()->setFillColor(sf::Color::Red);
}

void PoolWorld::shootBall()
{
	this->_stick->hitBall(this->white_ball);
}

const std::unique_ptr<sf::CircleShape>& PoolWorld::getWhiteBall() const {
	return this->white_ball->getBall();
}

const std::unique_ptr<sf::CircleShape>& PoolWorld::getBalls() const
{
	return this->_balls->getBall();
}

void PoolWorld::moveWhiteBall(unsigned int& FPS) {
	// Move the ball according to its velocity
	this->white_ball->move(FPS);
}

void PoolWorld::moveBalls(unsigned int& FPS)
{
	this->_balls->move(FPS);
	if(this->_balls->checkCollision(*this->white_ball))
		this->_balls->handleBallCollision(*this->white_ball);
}

void PoolWorld::moveStik(unsigned int& FPS) {
	this->_stick->moveToWhiteBall(FPS, this->white_ball);
}

void PoolWorld::handleWallCollision() {
	// TODO: remove this temp
	sf::Vector2f temp(this->main_window_size->x, this->main_window_size->y);
	sf::Vector2f temp2 = this->pool.getSize();

	this->white_ball->handleWallCollision(temp, 
			temp2);

	this->_balls->handleWallCollision(temp,
		temp2);
}

const std::unique_ptr<sf::RectangleShape>& PoolWorld::getStickShape() const {
	return this->_stick->getStick();
}

const std::unique_ptr<Stick>& PoolWorld::getStick() const {
	return this->_stick;
}
