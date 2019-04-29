#pragma once

#include <SFML/Graphics.hpp>
#include "Wall.h"
#include "Gun.h"

constexpr auto REVERS_TEX = 1;
constexpr auto POS_TEX_N = 3;

#define MOVEMENT(btn, player)\
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::##btn) && !event_F)\
		{\
		event_F = true;\
		player->move(btn, time);\
		}

#define MOVE(player)\
		{\
		bool event_F = false;\
		MOVEMENT(Up, player);\
		MOVEMENT(Right, player);\
		MOVEMENT(Down, player);\
		MOVEMENT(Left, player);\
		}


class Player : public ObjectCore
{
	int heroNumber_;
	int revDir_;
	int dir_;
	float speed_;
	float speedF_;
	float lastMoveT_;

	float winX_ = 300;
	float winY_ = 240;
	sf::View view_;

	Gun * pistol_;

public:
	Player(std::vector<ObjectCore *> & vec, bool alive = 0, float x = 0, float y = 0, int heroNumber = 0, bool active = true, bool visible = true, float dx = 0, float dy = 0, float animSpeed = 0.02f, int frames = 3, int w = 16, int h = 16, const char * fileName = "ref/images/skins.png", float speed = 0.2) :
		ObjectCore(alive, x, y, active, visible, dx, dy, animSpeed, frames, w, h, fileName, 0, true),
		heroNumber_(heroNumber),
		speed_(speed),
		speedF_(speed)
	{
		view_.reset(sf::FloatRect(0.f, 0.f, winX_, winY_));
		view_.setCenter(x + w / 2, y + h / 2);
		updateRect(POS_TEX_N * heroNumber);
		createCol();
		dir_ = Down;
		pistol_ = new Gun(vec, 7);
		vec.push_back(this);
	}

	void move(int dir, float time)
	{
		lastMoveT_ = time;
		dir %= 4;
		dir_ = dir;
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

	void createCol(float degree = 0)
	{
		col_.setSize(sf::Vector2f(w_ - 4.f, 3.f));
		col_.setFillColor(sf::Color(255, 0, 0));
		col_.setRotation(degree);
		col_.setPosition(x_ + 2, y_ + h_ - 2);

		horiCol_.setSize(sf::Vector2f(w_ - 6.f, 1.f));
		horiCol_.setFillColor(sf::Color(0, 0, 255));
		horiCol_.setRotation(degree);
		horiCol_.setPosition(x_ + 3, y_ + h_ / 2 - 3.f);

		vertCol_.setSize(sf::Vector2f(1.f, h_ - 0.f));
		vertCol_.setFillColor(sf::Color(0, 255, 0));
		vertCol_.setRotation(degree);
		vertCol_.setPosition(x_ + w_ / 2, y_);
	}


	void setViewCoor(float x, float y) { view_.setCenter(x + getW() / 2, y + getH() / 2); }

	void setView(sf::RenderWindow * window) { window->setView(view_); }

	sf::View * getView() { return &view_; }
	int getDir() { return dir_; }


	bool interSection(ObjectCore * second)
	{

		UWall * u = dynamic_cast<UWall *>(second);
		LWall * l = dynamic_cast<LWall *>(second);
		if ((u || l) && alive())
		{
			if (alive() && u)
				interSectionPos(second);
			if (ObjectCore::interSection(second))
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
		if ((getX() + getW() - 4 > second->getX()) && (getSpr().getGlobalBounds().intersects(second->getSpr().getGlobalBounds())) && (second->getY() < (getY() + getH())) && ((second->getY() + second->getH()) > (getY() + getH())))
		{
			second->updateRect(1);
			return true;
		}
		second->updateRect(0);
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

	void evnt(float time, float globTime, sf::RenderWindow * window)
	{
		MOVE(this);
		pistol_->shot(this, time, globTime, window);
		pistol_->reload();
	}


};
