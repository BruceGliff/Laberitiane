#pragma once
#include "Wall.h"
#include "Map.h"
#include "Qsort.h"
#include <iostream>
#include <vector>

class Level
{
	Map * map_;
	std::vector<ObjectCore *> vec;

	int u_count_;
	int l_count_;

	int size_;
	char * shape_;

	char * gnrShape(int size)
	{
		int sz = (size + 1) * (size + 1);
		
		char * shape = new char(sz + 1);
		for (int i = 0; i < sz; i++)
		{
			shape[i] = '0';
		}
		shape[sz] = '\0';
		int u_count_ = size * 2;
		int l_count_ = size * 2;

		

		//ÑÎÇÄÀÍÈÅ SHAPE

	

		for (int i = 0; i < sz; i++)
		{

		}


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
		static unsigned int seed = 4541;
		seed = (8253729 * seed + 2396403);
		return seed % 32768;
	}

public:
	Level(int size = 5) :
		size_(size)
	{
		map_ = new Map(size, 0);
		shape_ = gnrShape(size);
		
	}

	void draw(sf::RenderWindow * window, QSort<ObjectCore> * q)
	{
		map_->draw(window);
		/*/
		for (int i = 0; i < (size_ + 1) * (size_ + 1); i++)
		{
			switch (shape_[i])
			{
			case '0':
				break;
			case '1':
				vec.push_back(new LWall((i % (size_ + 1)) * 34.f, (i / (size_ + 1)) * 34.f));
				break;
			case '2':
				vec.push_back(new UWall((i % (size_ + 1)) * 34.f, (i / (size_ + 1)) * 34.f + 34.f));
				break;
			case '3':
				vec.push_back(new LWall((i % (size_ + 1)) * 34.f, (i / (size_ + 1)) * 34.f));
				vec.push_back(new UWall((i % (size_ + 1)) * 34.f, (i / (size_ + 1)) * 34.f + 34.f));
				break;

			default:
				break;
			}
		}

		for (auto x : vec)
		{
			x->draw(window);
		}*/
	}
};








