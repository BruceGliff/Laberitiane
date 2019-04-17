#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Level.h"
#include <vector>
#include <iostream>

#define MOVEMENT(btn, h_ind)\
if (sf::Keyboard::isKeyPressed(sf::Keyboard::##btn) && !event_F)\
{\
	event_F = true;\
	objects[h_ind]->move(btn, time);\
}

#define MOVE(id)\
{\
bool event_F = false;\
MOVEMENT(Up, id);\
MOVEMENT(Right, id);\
MOVEMENT(Down, id);\
MOVEMENT(Left, id);\
}

typedef unsigned int uInt;

int RunLevel()
{
	setlocale(LC_ALL, "Russian");

	int winX = 1000;
	int winY = 460;

	sf::RenderWindow window(sf::VideoMode(winX, winY), "Laberitianin");

	Level lvl(5);

	

	std::vector<ObjectCore *> objects;
	objects.push_back(new Player(true, 10, 0, 0));
	lvl.insert(objects);

	sf::Clock clock;
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


		MOVE(0)

		for (uInt i = 0; i < objects.size(); i++)
		{
			for (uInt j = i + 1; j < objects.size(); j++)
				objects[i]->interSection(objects[j]);
		}

		objects[0]->setView(&window);

		

		QSort<ObjectCore> * q = nullptr;

		for (auto object : objects)
		{
			q = q->insert(q, object);
		}

		window.clear(sf::Color(50, 50, 50));
			
		lvl.draw(&window);
		q->draw(&window);
		q->free();

		window.display();
	}

	return 0;
}