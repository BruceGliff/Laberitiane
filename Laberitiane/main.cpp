#include <SFML/Graphics.hpp>
#include "Player.h"
#include <iostream>

using namespace sf;

int main()
{
	setlocale(LC_ALL, "Russian");

	sf::RenderWindow window(sf::VideoMode(200, 200), "Laberitianin");

	RectangleShape shape(Vector2f(200, 200));
	shape.setFillColor(Color(255, 255, 255));

	shape.setPosition(0, 0);

	Player p(50, 50, 7);

	Clock clock;

	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time /= 1800;
		std::cout << time << "\n";
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		//EAST
		if (Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(Keyboard::D))
		{
			p.updateRect(EAST, 0.1, time);
		}

		//WEST
		if (Keyboard::isKeyPressed(Keyboard::Left) || Keyboard::isKeyPressed(Keyboard::A))
		{ 
			p.updateRect(WEST, 0.1, time);
		}

		//NORTH
		if (Keyboard::isKeyPressed(Keyboard::Up) || Keyboard::isKeyPressed(Keyboard::W)) 
		{ 
			p.updateRect(NORTH, 0.1, time);
		}

		//SOUTH
		if (Keyboard::isKeyPressed(Keyboard::Down) || Keyboard::isKeyPressed(Keyboard::S))
		{
			p.updateRect(SOUTH, 0.1, time);
		}
		p.upload(time);

		window.clear();

		window.draw(shape);
		window.draw(p.spr_);

		window.display();
	}

	return 0;
}