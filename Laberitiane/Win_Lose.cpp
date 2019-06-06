#include <SFML/Graphics.hpp>
#include <iostream>
#include "Button.h"
#include "Size.h"

int Win()
{
	Size<int> window_s(1600, 900);
	sf::RenderWindow * window = new sf::RenderWindow(sf::VideoMode(window_s.x(), window_s.y()), "Laberitianin");
	Size<float> exit_s(1172.f, 504.f);
	Button * exit = new Button(1400.f, 800.f, exit_s, "ref/images/exitBtn.png", 0.1f);

	sf::Texture tex;
	tex.loadFromFile("ref/images/WIN.png");
	sf::Sprite spr;
	spr.setTexture(tex);
	spr.scale(1.25, 1.25);

	while (window->isOpen())
	{
		sf::Event event;
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window->close();
				return -1;
			}
		
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				sf::Vector2i globalPosition = sf::Mouse::getPosition(*window);
				int x = globalPosition.x;
				int y = globalPosition.y;

				
				if (exit->click(x, y))
				{
					window->close();
					delete exit;
					delete window;										
					return 0;
				}
				
			}

		}
		window->clear(sf::Color(50, 50, 50));
		window->draw(spr);
		exit->draw(window);
		window->display();
	}
}

int Lose()
{
	Size<int> window_s(1600, 900);
	sf::RenderWindow * window = new sf::RenderWindow(sf::VideoMode(window_s.x(), window_s.y()), "Laberitianin");
	Size<float> exit_s(1172.f, 504.f);
	Button * exit = new Button(1400.f, 800.f, exit_s, "ref/images/exitBtn.png", 0.1f);

	sf::Texture tex;
	tex.loadFromFile("ref/images/LOSE.png");
	sf::Sprite spr;
	spr.setTexture(tex);
	spr.scale(1.25, 1.25);

	while (window->isOpen())
	{
		sf::Event event;
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window->close();
				return -1;
			}

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				sf::Vector2i globalPosition = sf::Mouse::getPosition(*window);
				int x = globalPosition.x;
				int y = globalPosition.y;


				if (exit->click(x, y))
				{
					window->close();
					delete exit;
					delete window;
					return 0;
				}

			}

		}
		window->clear(sf::Color(50, 50, 50));
		window->draw(spr);
		exit->draw(window);
		window->display();
	}
}