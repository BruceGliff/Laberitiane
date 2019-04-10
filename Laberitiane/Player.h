#pragma once

#include <SFML/Graphics.hpp>
#include "HeroCore.h"

constexpr auto REVERS_TEX = 1;
constexpr auto POS_TEX_N = 3;

enum direction
{
	NORTH = 0,
	EAST,
	SOUTH,
	WEST
};

class Player : public HeroCore
{
	int heroNumber_;
	int dir_;
	float speed_;

	sf::View view_;

public:
	Player(float x = 0, float y = 0, int heroNumber = 0, float dx = 0, float dy = 0, float animSpeed = 0.02f, int frames = 3, int w = 16, int h = 16, const char * fileName = "ref/images/skins.png", float speed = 0.2) :
		HeroCore(x, y, dx, dy, animSpeed, frames, w, h, fileName),
		heroNumber_(heroNumber),
		speed_(speed)
	{
		view_.reset(sf::FloatRect(225, 225, 300, 300)); //зависимость размера окна от размера камеры
		updateRect(POS_TEX_N * heroNumber, 0);
	}

	void move(int dir, float time)
	{
		dir %= 4;
		switch (dir)
		{
		case NORTH:
			HeroCore::move(0, -speed_, time);
			updateRect(POS_TEX_N * heroNumber_ + POS_TEX_N - 1, time);
			break;
		case EAST:
			HeroCore::move(speed_, 0, time);
			updateRect(POS_TEX_N * heroNumber_ + POS_TEX_N - 2, time);
			break;
		case SOUTH:
			HeroCore::move(0, speed_, time);
			updateRect(POS_TEX_N * heroNumber_, time);
			break;
		case WEST:
			HeroCore::move(-speed_, 0, time);
			updateRect(POS_TEX_N * heroNumber_ + POS_TEX_N - 2, time, REVERS_TEX);
			break;
		}

		setViewCoor(getX(), getY());
	}

	void setViewCoor(float x, float y) { view_.setCenter(x + getW() * 1.6,  y + getH() * 1.6); } // Узнать зависисмость координат, от размера

	void setView(sf::RenderWindow * window){ window->setView(view_); }

};

