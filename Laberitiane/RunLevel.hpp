#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Gun.h"
#include "Level.h"
#include <vector>
#include <iostream>

typedef unsigned int uInt;

int RunLevel()
{
	setlocale(LC_ALL, "Russian");

	int winX = 1600;
	int winY = 900;

	sf::RenderWindow * window = new sf::RenderWindow(sf::VideoMode(winX, winY), "Laberitianin");

	float globTime = 0;

	Level lvl(5);
	
	std::vector<ObjectCore *> objects;
	ObjectCore * player = new Player(objects, true, 10, 20, 0);

	lvl.insert(objects);
	
	sf::Clock clock;
	while (window->isOpen())
	{
				
		float time = float(clock.getElapsedTime().asMicroseconds());
		globTime += time / 1000000;
		clock.restart();
		time /= 1800;

		sf::Event event;
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window->close();
		}

		player->evnt(time, globTime);


		for (uInt i = 0; i < objects.size(); i++)
		{
			if (objects[i]->active())
				for (uInt j = i + 1; j < objects.size(); j++)
					objects[i]->interSection(objects[j]);
		}

		player->setView(window);

		

		QSort<ObjectCore> * q = nullptr;

		for (auto object : objects)
		{
			q = q->insert(q, object);
		}

		window->clear(sf::Color(50, 50, 50));
			
		lvl.draw(window);
		q->draw(window);
		q->free();

		window->display();
	}

	return 0;
}