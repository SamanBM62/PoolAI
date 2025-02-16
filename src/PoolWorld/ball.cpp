#include "ball.hpp"

Ball::Ball(float radious, sf::Vector2f pos) : _ball{ std::make_unique<sf::CircleShape>(radious) },
	velocity{0.f, 0.f} {
	this->_ball->setPosition(pos);
}

void Ball::move(unsigned int& FPS)
{
	if (!this->velocity.x && !this->velocity.y)
		return;

	// Move the ball according to its velocity
	this->_ball->move(this->velocity * (1.f / FPS));

	// Apply friction to gradually slow the ball down
	float friction = 0.98f;  // Adjust for stronger/weaker friction
	this->velocity *= friction;

	// Stop ball if velocity is very low
	if (std::abs(velocity.x) < 0.1f) velocity.x = 0;
	if (std::abs(velocity.y) < 0.1f) velocity.y = 0;
}

void Ball::setVelocity(sf::Vector2f& newVel)
{
	this->velocity = newVel;
}

const std::unique_ptr<sf::CircleShape>& Ball::getBall() const
{
	return this->_ball;
}

void Ball::handleWallCollision(sf::Vector2f& window_size, sf::Vector2f& board_size)
{
	sf::Vector2f pos = this->_ball->getPosition();
	float radius = this->_ball->getRadius();

	float left_x{(window_size.x - board_size.x)/2.f};
	float right_x{window_size.x - left_x};
	bool collsion{ false };

	// Left & right walls
	if (pos.x < left_x) {
		pos.x = left_x;
		this->velocity.x = -this->velocity.x;
		
		collsion = true;
	} else if (pos.x + 2 * radius > right_x) {
		pos.x = right_x - 2 * radius;
		this->velocity.x = -this->velocity.x;
		collsion = true;
	}

	float top_y{ (window_size.y - board_size.y) / 2.f };
	float bottom_y{ window_size.y - top_y };

	// Top & bottom walls
	if (pos.y < top_y) {
		pos.y = top_y;
		this->velocity.y = -this->velocity.y;
		collsion = true;
	} else if (pos.y + 2 * radius > bottom_y) {
		pos.y = bottom_y - 2 * radius;
		this->velocity.y = -this->velocity.y;
		collsion = true;
	}

	if (collsion) {
		this->_ball->setPosition(pos);
		float friction = 0.85f;
		this->velocity *= friction;
	}
}
