#include <SFML/Graphics.hpp>
#include "Player.h"
#include <iostream>

using namespace sf;

int main()
{
	setlocale(LC_ALL, "Russian");

	sf::RenderWindow window(sf::VideoMode(200, 200), "Laberitianin");

	RectangleShape shape(Vector2f(60, 60));
	shape.setFillColor(Color(255, 255, 255));

	shape.setPosition(0, 0);

	HeroCore *heros[8];

	for (int i = 0; i < 8; i++)
	{
		heros[i] = new Player(i * 20, 0, i);
	}


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
			(dynamic_cast<Player *>(heros[0]))->move(EAST, time);
		}

		//WEST
		if ((Keyboard::isKeyPressed(Keyboard::Left) || Keyboard::isKeyPressed(Keyboard::A)) && !event_F)
		{ 
			event_F = true;
			(dynamic_cast<Player *>(heros[0]))->move(WEST, time);
		}

		//NORTH
		if ((Keyboard::isKeyPressed(Keyboard::Up) || Keyboard::isKeyPressed(Keyboard::W)) && !event_F)
		{ 
			event_F = true;
			(dynamic_cast<Player *>(heros[0]))->move(NORTH, time);
		}

		//SOUTH
		if ((Keyboard::isKeyPressed(Keyboard::Down) || Keyboard::isKeyPressed(Keyboard::S)) && !event_F)
		{
			event_F = true;
			(dynamic_cast<Player *>(heros[0]))->move(SOUTH, time);
		}

		(dynamic_cast<Player *>(heros[0]))->setView(&window);
		window.clear();

		window.draw(shape);

		for (int i = 0; i < 8; i++)
			heros[i]->draw(&window);
		
		window.display();
	}

	return 0;
}