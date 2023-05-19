#include <iostream>
#include <cmath>
#include <SFML/Graphics.hpp>

#include "Physical.hpp"

int main(int argc, char** argv) {
	sf::RenderWindow win(sf::VideoMode(600, 400), "Physim");
	win.setKeyRepeatEnabled(false);

	Physical p(30.0, 1.0, sf::Color::Green);
	p.position.y = -370.0;
	p.velocity.x = 140.0;
	p.velocity.y = 200.0;
 
	Physical collide(20.0, 1.0, sf::Color::Blue);
	collide.position.x = 400.0;
	collide.position.y = -200.0;
	collide.force.y = 0; //Stationary Object

	//sf::Clock clock;
	sf::Clock timer;

	while (win.isOpen()) {
		//float dt = clock.restart().asSeconds();
		float t = timer.getElapsedTime().asSeconds();

		sf::Event ev;
		while (win.pollEvent(ev)) {
			switch (ev.type) {
			case sf::Event::Closed:
				win.close();
				break;
			// case sf::Event::KeyPressed: {
			// 	t += 0.01;
			// 	std::printf("t = %f\n", t);
			// 	sf::Vector2f dist = p.getpos() - collide.getpos();
			// 	std::printf("dist = %f\n", std::sqrt(dist.x*dist.x + dist.y*dist.y));
			// 	std::putchar('\n');
			// 	break;
			// }
			default: break;
			}
		}

		p.move(t);
		collide.move(t);

		if (p.collidesWith(collide)) {
			p.circle.setFillColor(sf::Color::Red);
			p.handleCollision(collide, t);
		} else {
			p.circle.setFillColor(sf::Color::Green);
		}
// 
		win.clear();
		win.draw(p);
		win.draw(collide);
		win.display();
	}
}


