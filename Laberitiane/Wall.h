#pragma once
#include <SFML/Graphics.hpp>
#include "ObjectCore.h"

class UWall : public ObjectCore
{
public:
	UWall(float x = 0, float y = 0, int WallNumber = 0, bool active = true, bool visible = true, float dx = 0, float dy = 0, float animSpeed = 0, int frames = 1, float scale = 1, int w = 34, int h = 27, const char * fileName = "ref/images/uwall.png") :
		ObjectCore(false, x, y, active, visible, dx, dy, animSpeed, frames, scale, w, h, fileName)
	{
		updateRect(WallNumber);
		createCol();
	}


	void move(int dir, float time) {}
	void setView(sf::RenderWindow * window) {}
	sf::View * getView() { return nullptr; }

	void createCol(float degree = 0)
	{
		col_.setSize(sf::Vector2f(w_ - 2, 1.f));
		col_.setFillColor(sf::Color(255, 0, 0));
		col_.setRotation(degree);
		col_.setPosition(x_ + 2, y_ + h_ * scale_);
	}

};

class LWall : public ObjectCore
{
public:
	LWall(float x = 0, float y = 0, int WallNumber = 0, bool active = true, bool visible = true, float dx = 0, float dy = 0, float animSpeed = 0, int frames = 1, float scale = 1, int w = 34, int h = 4, const char * fileName = "ref/images/lwall.png", float degree = -90.f) :
		ObjectCore(false, x, y, active, visible, dx, dy, animSpeed, frames, scale, w, h, fileName, degree)
	{
		updateRect(WallNumber);
		createCol(degree);
	}


	void move(int dir, float time) {}
	void setView(sf::RenderWindow * window) {}
	sf::View * getView() { return nullptr; }

	virtual void createCol(float degree = 0)
	{
		col_.setSize(sf::Vector2f(w_, h_));
		col_.setFillColor(sf::Color(255, 0, 0));
		col_.setRotation(degree);
		col_.setPosition(x_, y_ );
	}


};