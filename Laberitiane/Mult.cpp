#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "Size.h"

class Video
{
	int count_ = 169;
	float animSpeed_ = 30.f;

	sf::RenderWindow * window;

	Size<float> exit_s;
	Button * exit;

public:
	Video();
	~Video();
	int play();
};

Video::Video()
{

	exit_s = Size<float>(1172.f, 504.f);
	exit = new Button(1400.f, 700.f, exit_s, "ref/images/exitBtn.png", 0.1f);

	Size<int> windowS(1600, 900);
	window = new sf::RenderWindow(sf::VideoMode(windowS.x(), windowS.y()), "Laberitianin");
}

int Video::play()
{
	float frame = 1.f;
	sf::Clock clock;

	std::string shape = "p ().png\0";
	std::string path = "ref/images/ANIM/";
	std::string tmp;
	
	sf::Sprite spr;
	sf::Texture tex;

	float lastFrame = 0;

	while (window->isOpen())
	{
		shape = "p ().png\0";
		path = "ref/images/ANIM/";

		//////////////////////////////
		float time = float(clock.getElapsedTime().asMicroseconds());
		clock.restart();
		time /= 1800;

		sf::Event event;
		while (window->pollEvent(event))
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				sf::Vector2i globalPosition = sf::Mouse::getPosition(*window);
				int x = globalPosition.x;
				int y = globalPosition.y;
				if (exit->click(x, y))
				{
					window->close();
					return 0;
				}
			}
			if (event.type == sf::Event::Closed)
			{
				window->close();
				return 0;
			}
		}
		//////////////////////////////

		if (frame - lastFrame >= 1.f)
		{
			int tmpI = int(frame);
			while (tmpI > 0)
			{
				std::string x;
				x.push_back(char(tmpI % 10 + '0'));
				shape.insert(3, x);
				tmpI /= 10;
			}
			tmp = path + shape;
			//std::cout << tmp<< '\n';
			tex.loadFromFile(tmp);
			spr.setTexture(tex);
			spr.setScale(1.25, 1.25);

			lastFrame = frame;
		}

		window->clear();
		window->draw(spr);
		exit->draw(window);
		window->display();

		if (frame <= count_)
		{
			frame += time / animSpeed_;
		}
	}
	return 0;
}

Video::~Video()
{
	delete exit;
	delete window;
}


int RunVideo()
{
	Video anim;
	anim.play();
	return 0;
}