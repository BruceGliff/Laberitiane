#pragma once
#include "Wall.h"
#include "Map.h"
#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>

class Level
{
	Map * map_;

	int size_;
	char * shape_;

	char * gnrShape(int size)
	{
		int sz = (size + 1) * (size + 1);
		
		char * shape = new char[sz + 1];
		for (int i = 0; i < sz; i++)
		{
			shape[i] = '0';
		}
		shape[sz] = '\0';

		for (int i = 0; i < sz; i++)
		{
			shape[i] =  '0';
		}

		/* ÒÎËÜÊÎ ÝÒÓ ×ÀÑÒÜ */
		shape[2] = '1';
		shape[3] = '2';
		shape[4] = '3';
		shape[5] = '1';
		shape[6] = '1';
		shape[7] = '1';
		shape[8] = '2';
		shape[9] = '3';
		shape[10] = '0';
		shape[11] = '1';
		shape[12] = '3';
		shape[13] = '2';
		shape[14] = '2';
		shape[15] = '1';
		shape[16] = '2';
		shape[17] = '1';
		shape[18] = '3';
		shape[19] = '2';
		shape[21] = '2';
		shape[22] = '1';
		shape[23] = '3';
		shape[24] = '2';
		shape[25] = '3';
		shape[26] = '2';
		/*  END  */


		for (int i = 1; i <= size - 1; i++)
		{
			//set L
			shape[(size + 1) * i] = '1';
			shape[(size + 1) * (i + 1) - 1] = '1';

			//set U
			shape[i + size * (size + 1)] = '2';
			shape[i] = '2';
		}

		shape[size] = '1';
		shape[sz - 1] = '1';
		shape[0] = '3';
		shape[(size + 1) * size] = '3';
		
		return shape;
	}

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
		shape_ = gnrShape(size);
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
			case '0':
				break;
			case '1':
				vec.push_back(new LWall((i % (size_ + 1)) * 34.f, (i / (size_ + 1)) * 34.f - 34.f));
				break;
			case '2':
				vec.push_back(new UWall((i % (size_ + 1)) * 34.f, (i / (size_ + 1)) * 34.f - 27.f));
				break;
			case '3':
				vec.push_back(new UWall((i % (size_ + 1)) * 34.f, (i / (size_ + 1)) * 34.f - 27.f));
				vec.push_back(new LWall((i % (size_ + 1)) * 34.f, (i / (size_ + 1)) * 34.f - 34.f));
				break;

			default:
				break;
			}
		}
	}
};








