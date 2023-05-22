#include <iostream>

#include <cmath>
#include <SFML/Graphics.hpp>
#include "imgui.h"
#include "imgui-SFML.h"

#include "Physical.hpp"

const int fps = 24;
const float dt = 1.f / fps;
float e = 1.f;
float density = 0.f;

void start(Physical& p, Physical& collide) {
	p = Physical(30.0, 1.0, sf::Color::Green,
		{0.f, -370.f}, {140.0f, 200.0f});
	collide = Physical(20.0, 0.5, sf::Color::Blue,
		{400.f, 200.f}, {0.f, 0.f});
}

template<typename F>
void tree(const char* name, F fn) {
	if (ImGui::TreeNodeEx(name, ImGuiTreeNodeFlags_Framed)) {
		fn();
		ImGui::TreePop();
	}
}

void physical_gui(const char* name, Physical& p) {
	tree(name, [&p]{
		ImGui::InputFloat("Mass", &p.mass);
		ImGui::InputFloat("Drag Coefficient", &p.cDrag);
	});
}

void ui(Physical& p, Physical& collide) {
	ImGui::Begin("Simulation Options" , NULL, ImGuiWindowFlags_None);
	if (ImGui::Button("Restart Simulation"))
		start(p, collide);
	ImGui::InputFloat("Gravitational Constant", &G);
	ImGui::SliderFloat("Coefficient of Restitution", &e, 0.f, 1.f);
	ImGui::InputFloat("Fluid Density", &density);
	physical_gui("Green", p);
	physical_gui("Blue", collide);
	ImGui::End();
}

int main(int argc, char** argv) {
	sf::RenderWindow win(sf::VideoMode(1200, 800), "Physim");
	win.setKeyRepeatEnabled(false);
	win.setFramerateLimit(fps);
	ImGui::SFML::Init(win);

	Physical p(30.0, 1.0, sf::Color::Green,
		{0.f, -370.f}, {140.0f, 200.0f});
 
	Physical collide(20.0, 0.5, sf::Color::Blue,
		{400.f, 200.f}, {0.f, 0.f});
	//collide.force.y = 0; //Stationary Object

	while (win.isOpen()) {
		bool go = false;
		sf::Event ev;
		while (win.pollEvent(ev)) {
			ImGui::SFML::ProcessEvent(ev);
			switch (ev.type) {
			case sf::Event::Closed:
				win.close();
				break;
			case sf::Event::KeyPressed:
				go = true;
				break;
			default: break;
			}
		}
		ImGui::SFML::Update(win, sf::seconds(dt));

		ui(p, collide);

		// if (!go) continue;

		if (collide.pos.y < -1300)
			start(p, collide);

		p.force.y += p.mass * -G;
		collide.force.y += collide.mass * -G;
		p.addDrag(density);
		collide.addDrag(density);
		p.step(dt);
		collide.step(dt);

		if (p.collidesWith(collide)) {
			p.circle.setFillColor(sf::Color::Red);
			p.handleCollision(collide, e, dt);
		} else {
			p.circle.setFillColor(sf::Color::Green);
		}
		win.clear();
		win.draw(p);
		win.draw(collide);

		ImGui::SFML::Render(win);
		win.display();
	}
}


