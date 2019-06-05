#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "Size.h"

class Video
{
	int count_ = 86;
	sf::Texture * tex_;
	sf::Sprite * framesSpr_;

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

	std::string shape = "p (00).png\0";
	std::string path = "ref/images/ANIM/";
	tex_ = new sf::Texture[count_ + 1];
	framesSpr_ = new sf::Sprite[count_ + 1];

	for (int i = 1; i <= count_; i++)
	{
		if (i < 10)
		{
			shape[4] = '0' + i;
		}
		else
		{
			shape[3] = '0' + i / 10;
			shape[4] = '0' + i % 10;
		}

		std::string tmp = path + shape;
		//std::cout << tmp<<'\n';
		tex_[i].loadFromFile(tmp);
		framesSpr_[i].setTexture(tex_[i]);
		framesSpr_[i].setScale(1.25, 1.25);
	}

	Size<int> windowS(1600, 900);
	window = new sf::RenderWindow(sf::VideoMode(windowS.x(), windowS.y()), "Laberitianin");
}

int Video::play()
{
	float frame = 0;
	sf::Clock clock;
	while (window->isOpen())
	{
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
		window->clear();
		window->draw(framesSpr_[int(frame)]);
		exit->draw(window);
		window->display();
		if (int(frame) == 35 || int(frame) == 53 || int(frame) == 22)
		{
			frame += time / 500;
		} else  if (frame < 86.f)
		{
			frame += time / 70;
		}
		//std::cout << int(frame) << '\n';
	}
	return 0;
}

Video::~Video()
{
	delete[] framesSpr_;
	delete[] tex_;
	delete exit;
}


int RunVideo()
{
	Video anim;
	anim.play();
	return 0;
}