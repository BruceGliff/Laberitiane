#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Level.h"
#include <vector>
#include <iostream>


#define MOVEMENT(btn, h_ind)\
if (Keyboard::isKeyPressed(Keyboard::##btn) && !event_F)\
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
using namespace sf;


int RunLevel()
{
	setlocale(LC_ALL, "Russian");

	int winX = 1600;
	int winY = 900;

	sf::RenderWindow window(sf::VideoMode(winX, winY), "Laberitianin");

	Map map(5);

	std::vector<ObjectCore *> objects;
	objects.push_back(new Player(true, 10, 0, 0));

	for (int i = 0; i < 5; i++)
	{
		objects.push_back(new Player(false, 34.f * i, 34.f, i + 1));
		objects.push_back(new UWall(i * 34.0f, 0));
	}

	for (int i = 0; i < 5; i++)
	{
		objects.push_back(new LWall(34.f * i, 34.f));
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


		MOVE(0)

		for (int i = 0; i < objects.size() - 1; i++)
		{
			for (int j = i + 1; j < objects.size(); j++)
				objects[i]->interSection(objects[j]);
		}

		QSort<ObjectCore> * q = nullptr;
		for (auto object : objects)
		{
			q = q->insert(q, object);
		}

		objects[0]->setView(&window);
		window.clear(sf::Color(50, 50, 50));
		map.draw(&window);
		q->draw(&window);

		q->free();

		window.display();
	}

	return 0;
}