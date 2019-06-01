#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class MainWindow
{
	int heroNumber = 0;
	float scale = 1.f;
	bool more = true;

	sf::Texture backWall_;
	sf::Sprite backWallSpr_;

	float w_ = 1600.f;
	float h_ = 900.f;


	sf::Texture text_;
	sf::Sprite textSpr_;

	float wT_ = 634.f;
	float hT_ = 192.f;
	

	sf::Texture start_;
	sf::Sprite startSpr_;

	float wS_ = 391.f;
	float hS_ = 119.f;


	sf::Texture skin_;
	sf::Sprite skinSpr_;

	float wSkin_ = 16.f;
	float hSkin_ = 16.f;

public:
	MainWindow()
	{
		
		backWall_.loadFromFile("ref/images/mainTheme.png");
		backWallSpr_.setTexture(backWall_);
		backWallSpr_.setPosition(0.f, 0.f);
		
		text_.loadFromFile("ref/images/Laberetiane.png");
		textSpr_.setTexture(text_);
		textSpr_.setOrigin(367.f, 96.f);
		textSpr_.setPosition(800.f, 120.f);

		start_.loadFromFile("ref/images/StartBtn.png");
		startSpr_.setTexture(start_);
		startSpr_.setPosition(605.f, 391.f);
		
		skin_.loadFromFile("ref/images/skins.png");
		skinSpr_.setTexture(skin_);
		skinSpr_.setTextureRect(sf::IntRect(0, int(hSkin_ * heroNumber * 3), int(wSkin_), int(hSkin_)));
		skinSpr_.setPosition(224.f, 660.f);
		skinSpr_.setScale(9.f, 9.f);
		
	}
	~MainWindow() {};

	void setHero(int number)
	{
		heroNumber = number;
		skinSpr_.setTextureRect(sf::IntRect(0, int(hSkin_ * heroNumber * 3), int(wSkin_), int(hSkin_)));
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
		window->draw(startSpr_);
		window->draw(skinSpr_);
	}
};

