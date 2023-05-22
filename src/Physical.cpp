#include <iostream>
#include <cmath>
#include "Physical.hpp"

float G = 100;
void setG(float x) {
	G = x;
}
float getG() {
	return G;
}

Physical::Physical(float rad, float mass, sf::Color c, sf::Vector2f si, sf::Vector2f vi)
	: mass(mass), vi(vi) {
	circle = sf::CircleShape(rad);
	circle.setOrigin(rad, rad);
	circle.setFillColor(c);

	force = {0.f, mass * -G};
	pos = si;
	posOld = {0.f, 0.f};
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

void Physical::step(float dt) {
	// printf("%d\n", state);
	switch (state) {
	case 0:
		// pos = si;
		state++;
		break;
	case 1:
		posOld = pos;
		pos += vi*dt + 0.5f*(force/mass)*dt*dt;
		state++;
		break;
	default:
		sf::Vector2f posNew = 2.f*pos - posOld + (force/mass)*dt*dt;
		posOld = pos;
		pos = posNew;
		break;
	}
	// printf("posOld{%f, %f}, pos{%f, %f}\n", posOld.x, posOld.y, pos.x, pos.y);

	setpos(pos);
	force = {0.f, 0.f};
}

static float dot(sf::Vector2f a, sf::Vector2f b) {
	return a.x*b.x + a.y*b.y;
}

bool Physical::collidesWith(const Physical& p) const {
	sf::Vector2f space = getpos() - p.getpos();
	float minDist = circle.getRadius() + p.circle.getRadius();
	// printf("Distance: %f\n", std::sqrt(space.x*space.x + space.y*space.y));
	return (space.x*space.x + space.y*space.y)
		<= (minDist*minDist);
}
void Physical::handleCollision(Physical &p, float e, float dt) {
	sf::Vector2f v = (pos - posOld) / dt, vp = (p.pos - p.posOld) / dt,
		vboth = v - vp; // TODO there may be a problem with this
	sf::Vector2f normal = pos - p.pos;
	float masses = 1/mass + 1/p.mass;
	float impulse = -((1+e) * dot(vboth, normal))/(dot(normal, normal) * masses);

	sf::Vector2f dv  =  (impulse / mass)   * normal;
	sf::Vector2f dpv = -(impulse / p.mass) * normal;
	force = mass * (dv/dt);
	p.force = p.mass * (dpv/dt);
}

void Physical::addDrag(float density) {
	if (state == 1) return;

	sf::Vector2f v = pos - posOld;
	float speed = sqrt(v.x*v.x + v.y*v.y);
	float rad = circle.getRadius();
	float area = M_PI * rad * rad;
	float mag = 0.5f * density * speed * speed * cDrag * area;
	sf::Vector2f drag = -(v / speed) * mag;
	force += drag;
}

void Physical::draw(sf::RenderTarget& t, sf::RenderStates s) const {
	t.draw(circle, s);
}

