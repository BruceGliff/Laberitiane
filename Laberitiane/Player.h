#pragma once

#include <SFML/Graphics.hpp>

enum direction
{
	NORTH = 0,
	EAST,
	SOUTH,
	WEST
};

class Player
{
public:
	float x_;
	float y_;

	float dx_ = 0 ;
	float dy_ = 0;

	int h_;
	int w_;

	float speed_ = 0;
	float animSpeed_ = 0.02;
	int dir_;
	float frame_ =  0;
	int heroNumber_;

	sf::Image img_;
	sf::Texture tex_;
	sf::Sprite spr_;

	const char * fileName_ = "ref/images/skins.png";

	Player(float x, float y, int heroNumber = 0, int h = 16, int w = 16)
	{
		img_.loadFromFile(fileName_);
		tex_.loadFromImage(img_);
		spr_.setTexture(tex_);
		spr_.scale(sf::Vector2f(5, 5));

		heroNumber_ = heroNumber;
		h_ = h;
		w_ = w;
		x_ = x;
		y_ = y;

		spr_.setTextureRect(sf::IntRect(0, heroNumber_ * 3 * h_, w, h));
	}

	void updateRect(int dir, float speed, float time)
	{
		dir_ = dir;
		speed_ = speed;

		frame_ += animSpeed_ * time;
		if (frame_ >= 3) frame_ -= 3;

		switch (dir_)
		{
		case NORTH:
			spr_.setTextureRect(sf::IntRect(16 * int(frame_), heroNumber_ * 3 * h_ + 2 * h_, h_, h_));
			break;
		case EAST:
			spr_.setTextureRect(sf::IntRect(16 * int(frame_), heroNumber_ * 3 * h_ + 1 * h_, h_, h_));
			break;
		case SOUTH:
			spr_.setTextureRect(sf::IntRect(16 * int(frame_), heroNumber_ * 3 * h_, h_, h_));
			break;
		case WEST:
			spr_.setTextureRect(sf::IntRect(16 * (int(frame_) + 1), heroNumber_ * 3 * h_ + 1 * h_, -h_, h_));
			break;
		}
		
	}

	~Player() {};

	void upload(float time)
	{
		switch (dir_)
		{
		case NORTH:
			dx_ = 0;
			dy_ = -speed_;
			break;
		case EAST:
			dx_ = speed_;
			dy_ = 0;
			break;
		case SOUTH:
			dx_ = 0;
			dy_ = speed_;
			break;
		case WEST:
			dx_ = -speed_;
			dy_ = 0;
			break;
		}

		x_ += dx_ * time;
		y_ += dy_ * time;

		speed_ = 0;
		spr_.setPosition(x_, y_);
	}	
};

