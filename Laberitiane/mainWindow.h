#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Size.h"
#include "Button.h"

class MainWindow
{
	int heroNumber = 0;
	float scale = 1.f;
	bool more = true;

	sf::Texture backWall_;
	sf::Sprite backWallSpr_;

	sf::Texture text_;
	sf::Sprite textSpr_;

	Size<float> start_s;


	sf::Texture skin_;
	sf::Sprite skinSpr_;

	Size<int> skin_s;

public:
	Button * start;

	MainWindow()
	{
		
		backWall_.loadFromFile("ref/images/mainTheme.png");
		backWallSpr_.setTexture(backWall_);
		backWallSpr_.setPosition(0.f, 0.f);
		
		text_.loadFromFile("ref/images/Laberetiane.png");
		textSpr_.setTexture(text_);
		textSpr_.setOrigin(367.f, 96.f);
		textSpr_.setPosition(800.f, 120.f);

		start_s = Size<float>(391.f, 119.f);
		start = new Button(605.f, 358.f, start_s, "ref/images/StartBtn.png");
		
		skin_s = Size<int>(16, 16);
		skin_.loadFromFile("ref/images/skins.png");
		skinSpr_.setTexture(skin_);
		skinSpr_.setTextureRect(sf::IntRect(0, skin_s.y() * heroNumber * 3, skin_s.x() , skin_s.y()));
		skinSpr_.setPosition(224.f, 660.f);
		skinSpr_.setScale(9.f, 9.f);
		
	}
	~MainWindow() 
	{
		delete start;
	};

	void setHero(int number)
	{
		heroNumber = number;
		skinSpr_.setTextureRect(sf::IntRect(0, skin_s.y() * heroNumber * 3, skin_s.x(), skin_s.y()));
	}

	void anim(float time)
	{
		int speed = 5000;
		if (scale > 1.2)
			more = false;
		if (scale < 1.0)
			more = true;
		if (more)
			scale += time / speed;
		else
			scale -= time / speed;
		textSpr_.setScale(scale, scale);
	}

	void draw(sf::RenderWindow * window, float time)
	{
		anim(time);
		window->draw(backWallSpr_);
		window->draw(textSpr_);
		start->draw(window);
		window->draw(skinSpr_);
	}
};

