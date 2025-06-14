#include "pool_world.hpp"
#include <cmath>

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
		sf::Vector2f((this->main_window_size->x) / 2.f - 200.f,
					(this->main_window_size->y) / 2.f),
					sf::Color::White
		);
}

void PoolWorld::setUpBalls()
{
	/* this code looks like shit, but it works; mayabe a TODO:later? */
    int radius = 20;

    std::vector<sf::Color> colors = {
        sf::Color::Red, sf::Color::Yellow, sf::Color(235, 106, 14), sf::Color::Blue, sf::Color::Magenta,
        sf::Color(255, 165, 0), sf::Color::Cyan, sf::Color::Red, sf::Color::Yellow, sf::Color(235, 106, 14),
        sf::Color::Blue, sf::Color::Magenta, sf::Color(255, 165, 0), sf::Color::Cyan, sf::Color::Red, sf::Color::Yellow
    };

    float startX = (this->main_window_size->x) / 2.f + 100.f;
    float startY = (this->main_window_size->y) / 2.f;

    float horizontalSpacing = 2 * radius + 10.f;
    float verticalSpacing = 2 * radius + 10.f;

    int ballIndex = 0;

    for (int row = 0; row < 5; ++row) {
        for (int col = 0; col <= row; ++col) {
            float x = startX + col * horizontalSpacing ;
            float y = startY + row * verticalSpacing - (col * horizontalSpacing / 2);

            this->_balls.push_back(std::make_unique<Ball>(radius, sf::Vector2f(x, y), colors[ballIndex]));
            ballIndex++;
        }
    }
	for(auto const& ball: this->_balls)
		ball->getBall()->move(sf::Vector2f(0, -101.f));
}


void PoolWorld::shootBall()
{
	this->_stick->hitBall(this->white_ball);
}

const std::unique_ptr<sf::CircleShape>& PoolWorld::getWhiteBallShape() const {
	return this->white_ball->getBall();
}

const std::unique_ptr<Ball>& PoolWorld::getWhiteBall() const {
	return this->white_ball;
}

const std::vector<std::unique_ptr<Ball>>& PoolWorld::getBalls() const
{
	return this->_balls;
}

void PoolWorld::moveWhiteBall(unsigned int& FPS) {
	// Move the ball according to its velocity
	this->white_ball->move(FPS);
}

void PoolWorld::moveBalls(unsigned int& FPS)
{
	for(auto const& ball: this->_balls) {
		ball->move(FPS);
		if(ball->checkCollision(*this->white_ball))
			ball->handleBallCollision(*this->white_ball);
		for(auto const& ball2: this->_balls)
		{
			if(ball2->checkCollision(*this->white_ball))
				ball2->handleBallCollision(*this->white_ball);
			if(ball->checkCollision(*ball2))
				ball->handleBallCollision(*ball2);
		}
	}
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

	for(auto const& ball: this->_balls) {
		ball->handleWallCollision(temp, temp2);
	}
}

const std::unique_ptr<sf::RectangleShape>& PoolWorld::getStickShape() const {
	return this->_stick->getStick();
}

const std::unique_ptr<Stick>& PoolWorld::getStick() const {
	return this->_stick;
}


void PoolWorld::updateScore(const std::unique_ptr<Score>& scoreTable) {
	for (auto const& hole: this->holes) {
		
		for(auto const& ball: this->_balls) {
			if (this->checkBallCollisonWithHoles(*ball->getBall(), *hole)) {
				scoreTable->increaseScore();
				ball->makeInvisible();
			}
		}

		if (this->checkBallCollisonWithHoles(*this->white_ball->getBall(), *hole)) {
			scoreTable->decreaseScore();
			this->white_ball->makeInvisible();
		}
	}
}

bool PoolWorld::checkBallCollisonWithHoles(const sf::CircleShape& ball, const sf::CircleShape& hole) {
	// Get the center positions of both the ball and the hole
    sf::Vector2f ballCenter = ball.getPosition() + sf::Vector2f(ball.getRadius(), ball.getRadius());
    sf::Vector2f holeCenter = hole.getPosition() + sf::Vector2f(hole.getRadius(), hole.getRadius());

    // Calculate the difference between the centers
    sf::Vector2f diff = ballCenter - holeCenter;

    // Calculate the distance between the centers
    float distance = std::sqrt(diff.x * diff.x + diff.y * diff.y);

    // Calculate the sum of the radii
    float radiusSum = ball.getRadius() + hole.getRadius();

    // Return true if the distance is less than or equal to the sum of the radii
    return distance <= radiusSum;
}
