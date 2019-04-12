#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Map.h"
#include "Wall.h"
#include <vector>
#include <iostream>

using namespace sf;

#define MOVEMENT(btn, h_ind)\
if (Keyboard::isKeyPressed(Keyboard::##btn) && !event_F)\
{\
	event_F = true;\
	objects[h_ind]->move(btn, time);\
}

int main()
{
	setlocale(LC_ALL, "Russian");

	int winX = 1600;
	int winY = 900;

	sf::RenderWindow window(sf::VideoMode(winX, winY), "Laberitianin");

	Map map(5, 1);


	std::vector<ObjectCore *> objects;

	ObjectCore * h_draw[8];
	ObjectCore * w_draw[10];

	h_draw[0] = new Player(true, 0, 0, 0);
	objects.push_back(h_draw[0]);
	for (int i = 1; i < 8; i++)
	{
		h_draw[i] = new Player(false, i * 50.0f, 0, i);
		objects.push_back(h_draw[i]);
	}

	for (int i = 0; i < 10; i++)
	{
		w_draw[i] = new Wall(34 * i, 0);
		objects.push_back(w_draw[i]);
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
		
		
		for (int i = 0; i < objects.size() - 1; i++)
		{
			for (int j = i + 1; j < objects.size(); j++)
				objects[i]->interSection(objects[j]);
		}
		
		objects[0]->setView(&window);

		window.clear(sf::Color(50, 50, 50));

		QSort<ObjectCore> * q = nullptr;
		for (int i = 0; i < 8; i++)
		{
			q = q->insert(q, h_draw[i]);
		}

		for (int i = 0; i < 10; i++)
		{
			q = q->insert(q, w_draw[i]);
		}

		map.draw(&window);

		q->draw(&window);

		q->free();

		window.display();
		
	}

	return 0;
}