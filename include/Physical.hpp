#ifndef PHYSICAL_HPP
#define PHYSICAL_HPP

#include "SFML/System/Vector2.hpp"
#include <SFML/Graphics.hpp>

extern float G;

struct Physical : public sf::Drawable {
	sf::CircleShape circle;
	float mass, cDrag = 0.1f;

	sf::Vector2f force, pos, posOld, vi;
	int state = 0;

	Physical(float rad, float mass, sf::Color c, sf::Vector2f si, sf::Vector2f vi);
	void step(float dt);
	void setpos(float x, float y);
	void setpos(sf::Vector2f v);
	sf::Vector2f getpos() const;

	void addDrag(float density);

	bool collidesWith(const Physical& p) const;
	void handleCollision(Physical &p, float e, float dt);
private:
	sf::Vector2f calculatePos(float tf, sf::Vector2f si, sf::Vector2f vi, sf::Vector2f a);
	virtual void draw(sf::RenderTarget& t, sf::RenderStates s) const;
};

#endif
