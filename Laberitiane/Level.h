#pragma once
#include "Wall.h"
#include "Map.h"
#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>

enum
{
	NOTHING = 0,
	RIGHT = 1,
	DOWN = 2,
	BOTH = 3

};

#include "creator.cpp"

class Level
{
	Map * map_;

	int size_;
	int * shape_;


	unsigned int rand()
	{
		std::srand(unsigned(std::time(0)));
		return std::rand();
	}

public:
	Level(int size = 5) :
		size_(size)
	{
		map_ = new Map(size, 0);

		maze maz(size, size);
		//maz.print_maze();

		shape_ = maz.convert();
	}
	~Level()
	{
		delete[] shape_;
		delete map_;
	}

	void draw(sf::RenderWindow * window)
	{
		map_->draw(window);
	}


	void insert(std::vector<ObjectCore *> & vec)
	{
		for (int i = 0; i < (size_ + 1) * (size_ + 1); i++)
		{
			switch (shape_[i])
			{
			case NOTHING:
				break;
			case DOWN:
				vec.push_back(new LWall((i % (size_ + 1)) * 34.f, (i / (size_ + 1)) * 34.f - 34.f - 27.f));
				break;
			case RIGHT:
				vec.push_back(new UWall((i % (size_ + 1)) * 34.f, (i / (size_ + 1)) * 34.f - 27.f));
				break;
			case BOTH:
				vec.push_back(new UWall((i % (size_ + 1)) * 34.f, (i / (size_ + 1)) * 34.f - 27.f));
				vec.push_back(new LWall((i % (size_ + 1)) * 34.f, (i / (size_ + 1)) * 34.f - 34.f  -27.f));
				break;

			default:
				break;
			}
		}
	}
};