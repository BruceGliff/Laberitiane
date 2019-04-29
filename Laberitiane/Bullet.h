#pragma once
#include "ObjectCore.h"

class Bullet : public ObjectCore
{

	int dir_;
	float speed_;

public:
	Bullet(bool alive = 0, float x = 0, float y = 0, bool active = false, bool visible = true, float dx = 0, float dy = 0, float animSpeed = 0, int frames = 1, int w = 4, int h = 2, const char * fileName = "ref/images/bullet.png", float speed = 0.7f) :
		ObjectCore(alive, x, y, active, visible, dx, dy, animSpeed, frames, w, h, fileName),
		speed_(speed)
	{
	}

	void setView(sf::RenderWindow * window) {}
	sf::View * getView() { return nullptr; }

	void createCol()
	{
		col_.setSize(sf::Vector2f(float(w_), float(h_)));
		col_.setFillColor(sf::Color(255, 0, 0));
		col_.setPosition(x_, y_);
	}

	void spawn(float x, float y, int dir) 
	{
		rotate(0);
		spr_.setOrigin(0, 0);
		x_ = 0; y_ = 0;

		dir %= 4;
		active_ = true;
		dir_ = dir;
		switch (dir)
		{
		case Up:
			rotate(270);
			spr_.setOrigin(-5.f, 0);
			x_ += 6.f + x; y_ += y + 5.f + 4.f;
			spr_.setPosition(x_, y_);
			break;
		case Down:
			rotate(90);
			spr_.setOrigin(8.f, 0);//8
			x_ += 7.f + x; y_ += y + 5.f + 12.f;//+12
			spr_.setPosition(x_, y_);
			break;
		case Left:
			rotate(180);
			spr_.setOrigin(0, -4.f);
			x_ += 6.f + x; y_ += y + 10.f + 4.f;
			spr_.setPosition(x_, y_);
			break;
		case Right:
			rotate(0);
			spr_.setOrigin(0, 4.f);
			x_ += 10.f + x; y_ += y + 10.f + 4.f;
			spr_.setPosition(x_, y_);
			break;
		}
	}

	void move(int dir, float time)
	{
		switch (dir_)
		{
		case Up:
			ObjectCore::move(0, -speed_, time);
			spr_.setPosition(x_, y_);
			break;
		case Right:
			ObjectCore::move(speed_, 0, time);
			spr_.setPosition(x_, y_);
			break;
		case Down:
			ObjectCore::move(0, speed_, time);
			spr_.setPosition(x_, y_);
			break;
		case Left:
			ObjectCore::move(-speed_, 0, time);
			spr_.setPosition(x_, y_);
			break;
		}
	}

	void rotate(float degrees)
	{
		col_.setPosition(x_, y_);
		float curr_deg = col_.getRotation();
		spr_.rotate(-curr_deg + degrees);
		col_.rotate(-curr_deg + degrees);
	}

	bool interSection(ObjectCore * second)
	{
		if ((spr_.getGlobalBounds().intersects(second->getHoriCol().getGlobalBounds()) && (dir_ == Down || dir_ == Up)) 
			|| (spr_.getGlobalBounds().intersects(second->getVertCol().getGlobalBounds()) && (dir_ == Left || dir_ == Right)))
		{
			if (second->player())
			{
				second->setActive(false);
			}

			active_ = false;
			return true;
		}

		return false;
	}
};