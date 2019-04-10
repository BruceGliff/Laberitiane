#include <SFML/Graphics.hpp>
#include "Player.h"
#include <iostream>

using namespace sf;

int main()
{
	setlocale(LC_ALL, "Russian");

	sf::RenderWindow window(sf::VideoMode(600, 600), "Laberitianin");

	RectangleShape shape(Vector2f(200, 200));
	shape.setFillColor(Color(255, 255, 255));

	shape.setPosition(225, 225);

	Player p(300, 300, 3);

	Clock clock;

	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time /= 1800;
		
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		
		bool event_F = false;

		//EAST
		if ((Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(Keyboard::D)) && !event_F)
		{
			event_F = true;
			p.move(EAST, time);
		}

		//WEST
		if ((Keyboard::isKeyPressed(Keyboard::Left) || Keyboard::isKeyPressed(Keyboard::A)) && !event_F)
		{ 
			event_F = true;
			p.move(WEST, time);
		}

		//NORTH
		if ((Keyboard::isKeyPressed(Keyboard::Up) || Keyboard::isKeyPressed(Keyboard::W)) && !event_F)
		{ 
			event_F = true;
			p.move(NORTH, time);
		}

		//SOUTH
		if ((Keyboard::isKeyPressed(Keyboard::Down) || Keyboard::isKeyPressed(Keyboard::S)) && !event_F)
		{
			event_F = true;
			p.move(SOUTH, time);
		}

		p.setView(&window);
		window.clear();

		window.draw(shape);
		p.draw(&window);

		window.display();
	}

	return 0;
}