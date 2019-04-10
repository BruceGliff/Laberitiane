#include <SFML/Graphics.hpp>
#include "Player.h"
#include <iostream>

using namespace sf;

#define MOVEMENT(btn1, btn2, dir, h_ind)\
if ((Keyboard::isKeyPressed(Keyboard::##btn1) || Keyboard::isKeyPressed(Keyboard::##btn2)) && !event_F)\
{\
	event_F = true;\
	heros[h_ind]->move(dir, time);\
}

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
		
		{
			bool event_F = false;
			MOVEMENT(Up, Up, NORTH, 0)
			MOVEMENT(Right, Right, EAST, 0)
			MOVEMENT(Down, Down, SOUTH, 0)
			MOVEMENT(Left, Left, WEST, 0)
		}
		
		{
			bool event_F = false;
			MOVEMENT(W, W, NORTH, 1)
			MOVEMENT(D, D, EAST, 1)
			MOVEMENT(S, S, SOUTH, 1)
			MOVEMENT(A, A, WEST, 1)
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