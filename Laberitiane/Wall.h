#pragma once
#include <SFML/Graphics.hpp>
#include "ObjectCore.h"

class UWall : public ObjectCore
{
public:
	UWall(float x = 0, float y = 0, int WallNumber = 0, bool active = true, bool visible = true, float dx = 0, float dy = 0, float animSpeed = 0, int frames = 1, int w = 34, int h = 27, const char * fileName = "ref/images/uwall1.png") :
		ObjectCore(false, x, y, active, visible, dx, dy, animSpeed, frames, w, h, fileName)
	{
		updateRect(WallNumber);
		createCol();
	}
	~UWall()
	{
		//std::cout << "Uw\n";
	}


	void move(int dir, float time) {}
	void setView(sf::RenderWindow * window) {}
	sf::View * getView() { return nullptr; }

	void createCol(float degree = 0)
	{
		col_.setSize(sf::Vector2f(w_ - 2.f, 3.f));
		col_.setFillColor(sf::Color(255, 0, 0));
		col_.setRotation(degree);
		col_.setPosition(x_ + 2.f, y_ + h_ - 2.f);

		horiCol_.setSize(sf::Vector2f(w_ - 0.f, 12.f));
		horiCol_.setFillColor(sf::Color(0, 0, 255));
		horiCol_.setRotation(degree);
		horiCol_.setPosition(x_, y_ + h_ / 2 - 3.f);
	}

};

class LWall : public ObjectCore
{
public:
	LWall(float x = 0, float y = 0, int WallNumber = 0, bool active = true, bool visible = true, float dx = 0, float dy = 0, float animSpeed = 0, int frames = 1, int w = 4, int h = 61, const char * fileName = "ref/images/lwall_v1.png", float degree = 0) :
		ObjectCore(false, x, y, active, visible, dx, dy, animSpeed, frames, w, h, fileName, degree)
	{
		updateRect(WallNumber);
		createCol(degree);

	}

	~LWall()
	{
		//std::cout << "Lw\n";
	}


	void move(int dir, float time) {}
	void setView(sf::RenderWindow * window) {}
	sf::View * getView() { return nullptr; }

	virtual void createCol(float degree = 0)
	{
		col_.setSize(sf::Vector2f(w_, h_ - 27.f));
		col_.setFillColor(sf::Color(255, 0, 0));
		col_.setPosition(x_, y_ + 27.f);

		vertCol_.setSize(sf::Vector2f(w_ - 0.f, h_ - 22.f));
		vertCol_.setFillColor(sf::Color(0, 255, 0));
		vertCol_.setRotation(degree);
		vertCol_.setPosition(x_, y_ + 22.f);

		horiCol_.setSize(sf::Vector2f(w_ - 0.f, h_ - 27.f));
		horiCol_.setFillColor(sf::Color(0, 0, 255));
		horiCol_.setRotation(degree);
		horiCol_.setPosition(x_, y_ + 27.f);
	}
};