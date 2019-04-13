#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>
#include <cstring>
#include <iostream>


class Map
{
	sf::Texture tex_;
	sf::Sprite spr_;
	sf::RenderTexture map_;

	int num_;

	int size_;
	int width_;
	int scale_;

	const char * fileName_;
public:
	Map(int size = 5, int num = 5, int width = 34, int scale = 1, const char * fileName = "ref/images/flour.png") :
		num_(num),
		size_(size),
		width_(width),
		scale_(scale),
		fileName_(fileName)
	{
		tex_.loadFromFile(fileName);
		spr_.setTexture(tex_);
		spr_.scale(scale, scale);
		spr_.setPosition(0, 0);
		spr_.setTextureRect(sf::IntRect(width_ * num_, 0, width_, width_));

		map_.create(width_ * size_ * scale_, width_ * size_ * scale_);
		map_.clear();
		for(int k = 0; k < size_ * size_;  k++)
		{
			spr_.setPosition(sf::Vector2f((k % size_) * width_ * scale_, (k / size_) * width_ * scale_));
			map_.draw(spr_);
		}
	}

	void draw(sf::RenderWindow * window) 
	{
		map_.display();
		sf::Sprite sprite(map_.getTexture());
		window->draw(sprite);
	}
	
	
};