#include <iostream>
#include "Physical.hpp"

Physical::Physical(float rad, float mass, sf::Color c) : mass(mass) {
	circle = sf::CircleShape(rad);
	circle.setOrigin(rad, rad);
	force = sf::Vector2f(0.0, mass * -G);
	velocity = sf::Vector2f(0.0, 0.0);
	position = sf::Vector2f(0.0, 0.0);

	circle.setFillColor(c);
}

void Physical::setpos(float x, float y) {
	setpos(sf::Vector2f(x, y));
}
void Physical::setpos(sf::Vector2f v) {
	circle.setPosition(v.x, -v.y);
}
sf::Vector2f Physical::getpos() const {
	auto pos = circle.getPosition();
	return sf::Vector2f(pos.x, -pos.y);
}

// void Physical::move(float dt) {
// 	sf::Vector2f accel = force * (dt / mass);
// 	velocity += accel;
// 	std::printf("(%f, %f)\n", velocity.x, velocity.y);
// 	setpos(getpos() + velocity * dt);
// }

void Physical::reset(float tf) {
	ti = tf;
}

sf::Vector2f Physical::calculatePos(float tf, sf::Vector2f si, sf::Vector2f vi, sf::Vector2f a) {
	float t = tf - ti;
	return si + vi*t + (a/2.0f)*(t*t); 
}

void Physical::move(float tf) {
	// velocity = velocity initial
	setpos(calculatePos(tf, position, velocity, force / mass));
}

bool Physical::collidesWith(const Physical& p) const {
	sf::Vector2f space = getpos() - p.getpos();
	float minDist = circle.getRadius() + p.circle.getRadius();
	return (space.x*space.x + space.y*space.y)
		<= (minDist*minDist);
}
void Physical::handleCollision(const Physical &p, float tf) {
	reset(tf);
	position = getpos();
	velocity = (getpos() - p.getpos());
}

void Physical::draw(sf::RenderTarget& t, sf::RenderStates s) const {
	t.draw(circle, s);
}

