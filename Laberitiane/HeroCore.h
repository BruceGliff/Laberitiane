#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class HeroCore
{
	float x_;
	float y_;
	float dx_;
	float dy_;

	float animSpeed_;
	int frames_;
	float currFrame_;

	sf::Texture tex_;
	sf::Sprite spr_;

	int w_;
	int h_;

	const char * fileName_;

public:
	int delY_ = 0;

	HeroCore(float x  = 0, float y = 0, float dx = 0, float dy = 0, float animSpeed = 0.02f, int frames = 3, int w = 16, int h = 16, const char * fileName = "ref/images/skins.png"):
		x_(x),
		y_(y),
		dx_(dx),
		dy_(dy),
		animSpeed_(animSpeed),
		frames_(frames),
		currFrame_(0),
		w_(w),
		h_(h),
		fileName_(fileName)
	{
		tex_.loadFromFile(fileName);
		spr_.setTexture(tex_);
		spr_.scale(3, 3);
		spr_.setPosition(x_, y_);
	}

	~HeroCore() {}

	virtual void move(float dx, float dy, float time)
	{
		dx_ = dx;
		dy_ = dy;

		x_ += dx_ * time;
		y_ += dy_ * time;
		spr_.setPosition(x_, y_);
	}

	virtual void updateRect(int delY, float time, int reverse = 0)
	{
		currFrame_ += animSpeed_ * time;
		if (currFrame_ >= frames_) currFrame_ -= frames_;

		if (!reverse)
			spr_.setTextureRect(sf::IntRect(w_ * int(currFrame_), h_ * delY, w_, h_));
		else
			spr_.setTextureRect(sf::IntRect(w_ * int(currFrame_ + 1), h_ * delY, -w_, h_));
	}


	virtual void draw(sf::RenderWindow * window)
	{
		window->draw(spr_);
	}

	float getX() { return x_; }
	float getY() { return y_; }
	int getH() { return h_; }
	int getW() { return w_; }
};