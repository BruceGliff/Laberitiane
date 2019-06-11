#include "mainWindow.h"
#define MULT 0x5F
#define EXIT -1

int startGame()
{
	Size<int> window_s(1600, 900);
	sf::RenderWindow * window = new sf::RenderWindow(sf::VideoMode(window_s.x(), window_s.y()), "Laberitianin");

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
			{
				window->close();
				delete window;
				return -1;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
				heroNumber--;

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
				heroNumber++;
			heroNumber %= 8;
			Window.setHero(int(heroNumber));

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				{
					window->close();
					delete window;
					return EXIT;
				}
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				sf::Vector2i globalPosition = sf::Mouse::getPosition(*window);
				int x = globalPosition.x;
				int y = globalPosition.y;

				if (Window.start->click(x, y))
				{
					window->close();
					delete window;
					return heroNumber;
				}

				
				if (Window.exit->click(x, y))
				{
					window->close();
					delete window;
					return EXIT;
				}
				if (Window.video->click(x, y))
				{
					window->close();
					delete window;
					return MULT;
				}
			}

		}
		window->clear(sf::Color(50, 50, 50));
		Window.draw(window, time);
		window->display();
	}

	delete window;
	return 0;
}