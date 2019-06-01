#include "mainWindow.h"

int startGame()
{
	int winX = 1600;
	int winY = 900;
	sf::RenderWindow * window = new sf::RenderWindow(sf::VideoMode(winX, winY), "Laberitianin");

	MainWindow Window;

	unsigned int heroNumber = 0;

	sf::Clock clock;
	while (window->isOpen())
	{
		float time = float(clock.getElapsedTime().asMicroseconds());
		clock.restart();
		time /= 1800;

		sf::Event event;
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window->close();
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
				heroNumber--;
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
				heroNumber++;
			heroNumber %= 8;
			Window.setHero(int(heroNumber));


			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				sf::Vector2i globalPosition = sf::Mouse::getPosition(*window);
				float x = globalPosition.x;
				float y = globalPosition.y;

				if ((x > 605 && x < (605 + 391)) && (y > 390 && y < 505))
				{
					delete window;

					return heroNumber;
				}
			}

		}
		window->clear(sf::Color(50, 50, 50));
		Window.draw(window, time);
		window->display();
	}

	return 0;
}