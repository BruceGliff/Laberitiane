#include <SFML/Graphics.hpp>
#include "Level.h"
#include "Player.h"
#include "Gun.h"
#include <vector>
#include <iostream>

#define LOSE 0xFF
#define WIN  0x0F

typedef unsigned int uInt;

int Exit(std::vector<ObjectCore *> & objects, sf::RenderWindow * window, int exitID = 0)
{
	for (auto x : objects)
	{
		delete x;
	}
	window->close();
	delete window;

	return exitID;
}

int RunLevel(int heroNumber = 0)
{
	setlocale(LC_ALL, "Russian");
	
	Size<int> windowS(1600, 900);

	sf::RenderWindow * window = new sf::RenderWindow(sf::VideoMode(windowS.x(), windowS.y()), "Laberitianin");

	float globTime = 0;

	Level lvl(10);
	
	std::vector<ObjectCore *> objects;

	Player * player = new Player(objects, true, 10, 10, heroNumber);
	objects.push_back(new Player(objects, false, 40, 10, 2, player->this_is_long_name_of_function_to_get_player_coord_X(), player->this_is_long_name_of_function_to_get_player_coord_Y(), &lvl));
	objects.push_back((ObjectCore*) player);

	lvl.insert(objects);
	
	sf::Clock clock;
	while (window->isOpen())
	{
		float time = float(clock.getElapsedTime().asMicroseconds());

		clock.restart();
		
		globTime += time / 1000000;
		time /= 1800;

		sf::Event event;
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				return Exit(objects, window);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				return Exit(objects, window, LOSE);
		}

		//player->evnt(time, globTime, window);

		bool botsAliveF = false;
		for (uInt i = 0; i < objects.size(); i++)
		{
			if (objects[i]->alive() && !objects[i]->active())
				return Exit(objects, window, LOSE);

			objects[i]->evnt(time, globTime, window);
			objects[i]->keep_move(time);
			

			Player * bot = dynamic_cast<Player *>(objects[i]);
			if (bot && objects[i]->active() && !objects[i]->alive())
				botsAliveF = true;

			for (uInt j = i + 1; j < objects.size(); j++)
				if (objects[i]->active() && objects[j]->active() && (objects[i]->player() || objects[j]->player()))
					objects[i]->interSection(objects[j]);
		}
		if (!botsAliveF) 
			return Exit(objects, window, WIN);

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

	
	return Exit(objects, window);
}