#ifndef PHYSICAL_HPP
#define PHYSICAL_HPP

#include <SFML/Graphics.hpp>

const float G = 100;

struct Physical : public sf::Drawable {
	sf::CircleShape circle;
	sf::Vector2f force, velocity, position;
	float mass;
	float ti = 0.0;
	void reset(float tf);
	Physical(float rad, float mass, sf::Color c);
	void move(float tf);

	void setpos(float x, float y);
	void setpos(sf::Vector2f v);
	sf::Vector2f getpos() const;

	bool collidesWith(const Physical& p) const;
	void handleCollision(const Physical &p, float tf);
private:
	sf::Vector2f calculatePos(float tf, sf::Vector2f si, sf::Vector2f vi, sf::Vector2f a);
	virtual void draw(sf::RenderTarget& t, sf::RenderStates s) const;
};

#endif
