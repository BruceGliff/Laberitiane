#pragma once
#include "Wall.h"
#include "Map.h"
#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>



#include "creator.cpp"

class Level
{
	Map * map_;

	int size_;
	int * shape_;

	Maze* maze;


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
		maze = new Maze(size, size);
		maze->print_Maze();

		shape_ = maze->convert();
	}
	~Level()
	{
		delete[] shape_;
		delete map_;
		maze->~Maze();
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

	int GetSize()
	{
		return size_;
	}



	int* getCommands(int* arr, int x1, int y1, int x2, int y2)
	{
		assert(arr);

		coord *track = (coord*) calloc(size_ * size_ + 10, sizeof(coord));

		maze->find_path(arr, x1, y1, x2, y2, 0, track, size_ * size_ + 10);
		int i = 0;
		while (arr[i] != 0)
		{	
			printf("%d ", arr[i++]);
		}
		printf("\n");
		
		return arr;
	}
};