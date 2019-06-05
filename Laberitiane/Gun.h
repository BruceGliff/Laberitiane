#pragma once
#include "Bullet.h"

class Gun
{
	std::vector <Bullet *> store_;
	int capacity_;
	int top_;

	float lastShot_;
	float cDown_;
	float fireTime_;

public:
	Gun(std::vector<ObjectCore *> & vec, int capacity = 10, float cDown = 0.2f) :
		capacity_(capacity),
		top_(0),
		cDown_(cDown),
		lastShot_(0.f),
		fireTime_(0.3f)
	{
		for (int i = 0; i <= capacity; i++)
		{
			store_.push_back(new Bullet());
			vec.push_back(store_[i]);
		}
	}

	void shot(ObjectCore * player, float time, float globTime, sf::RenderWindow * window)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !store_[top_]->active() && globTime - lastShot_ > cDown_ && top_ < capacity_)
		{
			float x = player->getX();
			float y = player->getY();
			store_[top_]->spawn(x, y, player->getDir());
			lastShot_ = globTime;
			top_++;
		}

		for (auto bullet : store_)
		{
			if (bullet->active())
			{
				bullet->move(0, time);
			}
		}
	}

	void reload()
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
		{
			top_ = 0;
		}
	}

	~Gun()
	{}

};

