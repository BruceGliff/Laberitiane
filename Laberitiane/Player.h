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

class Player : public heroCore
{
	int heroNumber_;
	int dir_;
	float speed_;

public:
	Player(float x = 0, float y = 0, int heroNumber = 0, float dx = 0, float dy = 0, float animSpeed = 0.02f, int frames = 3, int w = 16, int h = 16, const char * fileName = "ref/images/skins.png", float speed = 0.2) :
		heroCore(x, y, dx, dy, animSpeed, frames, w, h, fileName),
		heroNumber_(heroNumber),
		speed_(speed)
	{
		updateRect(POS_TEX_N * heroNumber, 0);
	}

	void move(int dir, float time)
	{
		//std::cout << speed_;
		dir %= 4;
		switch (dir)
		{
		case NORTH:
			heroCore::move(0, -speed_, time);
			updateRect(POS_TEX_N * heroNumber_ + POS_TEX_N - 1, time);
			break;
		case EAST:
			heroCore::move(speed_, 0, time);
			updateRect(POS_TEX_N * heroNumber_ + POS_TEX_N - 2, time);
			break;
		case SOUTH:
			heroCore::move(0, speed_, time);
			updateRect(POS_TEX_N * heroNumber_, time);
			break;
		case WEST:
			heroCore::move(-speed_, 0, time);
			updateRect(POS_TEX_N * heroNumber_ + POS_TEX_N - 2, time, REVERS_TEX);
			break;
		}

	}

};

