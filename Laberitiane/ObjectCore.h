#pragma once
#include <SFML/Graphics.hpp>

#include <iostream>

enum direction
{
	Up = 0,
	Right,
	Down,
	Left
};

class ObjectCore
{
protected:
	bool alive_;

	bool active_;
	bool visible_;

	float x_;
	float y_;
	float dx_;
	float dy_;

	float animSpeed_;
	int frames_;
	float currFrame_;

	sf::Texture tex_;
	sf::Sprite spr_;
	sf::RectangleShape col_;
	sf::RectangleShape bullCol_;

	int w_;
	int h_;

	const char * fileName_;

public:
	int delY_ = 0;

	ObjectCore(bool alive = 0, float x = 0, float y = 0, bool active = true, bool visible = true, float dx = 0, float dy = 0, float animSpeed = 0.02f, int frames = 3, int w = 16, int h = 16, const char * fileName = "ref/images/skins.png", float degree = 0.f) :
		alive_(alive),
		active_(active),
		visible_(visible),
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
		spr_.setPosition(x_, y_);
		spr_.setRotation(degree);
	}

	~ObjectCore() {}

	void setActive(bool f) { active_ = f; }
	void setVisible(bool f) { visible_ = f; }

	void move(float dx, float dy, float time)
	{
		dx_ = dx;
		dy_ = dy;

		x_ += dx_ * time;
		y_ += dy_ * time;
		spr_.setPosition(x_, y_);
		col_.setPosition(x_ + 2, y_ + h_ - 2);
		bullCol_.setPosition(x_ + 3, y_ + h_ / 2 - 3.f);
	}

	virtual void move(int dir, float time) = 0;
	virtual void setView(sf::RenderWindow * window) = 0;
	virtual sf::View * getView() = 0;
	virtual void spawn(float x, float y, int dir) {}


	virtual void updateRect(int delY = 0, float time = 0.f, int reverse = 0)
	{
		currFrame_ += animSpeed_ * time;
		if (currFrame_ >= frames_) currFrame_ -= frames_;

		if (!reverse)
		{
			spr_.setTextureRect(sf::IntRect(w_ * int(currFrame_), h_ * delY, w_, h_));
		}
		else
			spr_.setTextureRect(sf::IntRect(w_ * int(currFrame_ + 1), h_ * delY, -w_, h_));
	}

	bool alive() { return alive_; }
	bool active() { return active_; }


	virtual void draw(sf::RenderWindow * window)
	{
		if (active_)
		{
			
			window->draw(col_);
			window->draw(spr_);
			window->draw(bullCol_);
		}		
	}

	float getX() { return x_; }
	float getY() { return y_; }
	int getH() { return h_; }
	int getW() { return w_; }

	sf::Sprite & getSpr() { return spr_; }

	
	virtual bool interSection(ObjectCore * second)
	{
		if (col_.getGlobalBounds().intersects(second->col_.getGlobalBounds()))
		{
			//std::cout << "INTERSECT" << '\n';
			return true;
		}

		return false;
	}

};


#include "QSort.h"
#include "Sort.h"