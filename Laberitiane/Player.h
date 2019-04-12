#pragma once

#include <SFML/Graphics.hpp>
#include "Wall.h"

constexpr auto REVERS_TEX = 1;
constexpr auto POS_TEX_N = 3;

enum direction
{
	Up = 0,
	Right,
	Down,
	Left
};

class Player : public ObjectCore
{
	int heroNumber_;
	int revDir_;
	float speed_;
	float speedF_;
	float lastMoveT_;

	int winX_ = 320;
	int winY_ = 180;
	sf::View view_;

public:
	Player(bool playerF = 0, float x = 0, float y = 0, int heroNumber = 0, float dx = 0, float dy = 0, float animSpeed = 0.02f, int frames = 3, float scale = 1, int w = 16, int h = 16, const char * fileName = "ref/images/skins.png", float speed = 0.2) :
		ObjectCore(playerF, x, y, dx, dy, animSpeed, frames, scale, w, h, fileName),
		heroNumber_(heroNumber),
		speed_(speed),
		speedF_(speed)
	{
		view_.reset(sf::FloatRect(0, 0, winX_, winY_));
		view_.setCenter(x + w /2, y + h / 2);
		updateRect(POS_TEX_N * heroNumber);
	}

	void move(int dir, float time)
	{
		lastMoveT_ = time;
		dir %= 4;
		switch (dir)
		{
		case Up:
			revDir_ = Down;
			ObjectCore::move(0, -speed_, time);
			updateRect(POS_TEX_N * heroNumber_ + POS_TEX_N - 1, time);
			break;
		case Right:
			revDir_ = Left;
			ObjectCore::move(speed_, 0, time);
			updateRect(POS_TEX_N * heroNumber_ + POS_TEX_N - 2, time);
			break;
		case Down:
			revDir_ = Up;
			ObjectCore::move(0, speed_, time);
			updateRect(POS_TEX_N * heroNumber_, time);
			break;
		case Left:
			revDir_ = Right;
			ObjectCore::move(-speed_, 0, time);
			updateRect(POS_TEX_N * heroNumber_ + POS_TEX_N - 2, time, REVERS_TEX);
			break;
		}

		setViewCoor(getX(), getY());
	}

	void setViewCoor(float x, float y) { view_.setCenter(x + getW() / 2,  y + getH() / 2); }

	void setView(sf::RenderWindow * window){ window->setView(view_); }

	sf::View * getView() { return &view_; }

	
	bool interSection(ObjectCore * second)
	{
		if (alive()) 
			interSectionPos(second);

		if (ObjectCore::interSection(second))
		{
			if (Wall * p = dynamic_cast<Wall *>(second))
			{
				teleport(revDir_, lastMoveT_);
				speed_ = 0;
				return true;
			}
		}
		speed_ = speedF_;
		return false;
	}

	bool interSectionPos(ObjectCore * second)
	{
		Wall * p;
		if (p = dynamic_cast<Wall *>(second))
		{
			if (getSpr().getGlobalBounds().intersects(second->getSpr().getGlobalBounds()) && (second->getY() < (getY() + getH())) && ((second->getY() + second->getH()) > (getY() + getH())))
			{			
				second->updateRect(1);
				return true;
			}
			second->updateRect(0);
			return false;
		}		
		return false;
	}


	void teleport(int dir, float time)
	{
		lastMoveT_ = time;
		dir %= 4;
		switch (dir)
		{
		case Up:
			ObjectCore::move(0, -speed_, time);
			break;
		case Right:
			ObjectCore::move(speed_, 0, time);
			break;
		case Down:
			ObjectCore::move(0, speed_, time);
			break;
		case Left:
			ObjectCore::move(-speed_, 0, time);
			break;
		}

		setViewCoor(getX(), getY());
	}
	

};

