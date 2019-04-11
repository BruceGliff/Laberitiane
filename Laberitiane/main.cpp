#include <SFML/Graphics.hpp>
#include "Player.h"
#include <iostream>

using namespace sf;

#define MOVEMENT(btn, h_ind)\
if (Keyboard::isKeyPressed(Keyboard::##btn) && !event_F)\
{\
	event_F = true;\
	heroes[h_ind]->move(btn, time);\
}

int main()
{
	setlocale(LC_ALL, "Russian");

	sf::RenderWindow window(sf::VideoMode(900, 900), "Laberitianin");

	RectangleShape shape(Vector2f(800, 800));
	shape.setFillColor(Color(255, 255, 255));
	shape.scale(3, 3);

	shape.setPosition(0, 0);

	HeroCore *heroes[8];
	HeroCore *h_draw[8];

	for (int i = 0; i < 8; i++)
	{
		heroes[i] = new Player(i * 50.0f, 0, i);
		h_draw[i] = heroes[i];
	}


	Clock clock;

	while (window.isOpen())
	{
		float time = float(clock.getElapsedTime().asMicroseconds());
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
			MOVEMENT(Up, 0);
			MOVEMENT(Right, 0);
			MOVEMENT(Down, 0);
			MOVEMENT(Left, 0);
		}
		
		
		for (int i = 0; i < 7; i++)
		{
			for (int j = i + 1; j < 8; j++)
				heroes[i]->interSection(heroes[j]);
		}

		heroes[0]->setView(&window);

		window.clear();

		QSort<HeroCore> * q = nullptr;
		for (int i = 0; i < 8; i++)
		{
			q = q->insert(q, h_draw[i]);
		}

		window.draw(shape);

		q->draw(&window);
		
		window.display();
		q->free();
	}

	return 0;
}