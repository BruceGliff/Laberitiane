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
		//maz.test();
		maz.print_maze();

		shape_ = maz.convert();
	}

	void draw(sf::RenderWindow * window)
	{
		map_->draw(window);
	}


	void insert(std::vector<ObjectCore *> & vec)
	{
		for (int i = 0; i < (size_ + 1) * (size_ + 1); i++)
		{
			/*maze maz(size, size);
			maz.print_maze();*/

			switch (shape_[i])
			{
			case NOTHING:
				break;
			case DOWN:
				//printf("2\n");
				vec.push_back(new LWall((i % (size_ + 1)) * 34.f, (i / (size_ + 1)) * 34.f - 34.f));
				break;
			case RIGHT:
				//printf("1\n");
				vec.push_back(new UWall((i % (size_ + 1)) * 34.f, (i / (size_ + 1)) * 34.f - 27.f));
				break;
			case BOTH:
				//printf("3\n");
				vec.push_back(new UWall((i % (size_ + 1)) * 34.f, (i / (size_ + 1)) * 34.f - 27.f));
				vec.push_back(new LWall((i % (size_ + 1)) * 34.f, (i / (size_ + 1)) * 34.f - 34.f));
				break;

			default:
				std:: cout << "Alert!!!" << shape_[i] << "\n";
				break;
			}

			/*for (int i = 0; i < maz.vertical_; i++)
			{
				for (int j = 0; j < maz.horizontal_; j++)
					if (maz.cell_[i][j].north_ == WALL)
			}*/

		}
	}
};








