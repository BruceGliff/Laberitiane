#pragma once
#include <SFML/Graphics.hpp>
#include "Size.h"

class  Button
{
	float posX_;
	float posY_;

	sf::Texture tex_;
	sf::Sprite spr_;

	Size<float> size_;


public:
	Button() {}
	Button(float posX, float posY, float w, float h, const char * path, float scale = 1.f)
	{
		posX_ = posX;
		posY_ = posY;

		size_ = Size<float>(w * scale, h * scale);

		tex_.loadFromFile(path);
		spr_.setTexture(tex_);
		spr_.setPosition(posX_, posY_);
	}
	Button(float posX, float posY, Size<float> size, const char * path, float scale = 1.f)
	{
		posX_ = posX;
		posY_ = posY;

		size_ = size;
		size_.x(size.x() * scale);
		size_.y(size.y() * scale);

		tex_.loadFromFile(path);
		spr_.setTexture(tex_);
		spr_.setScale(scale, scale);
		spr_.setPosition(posX_, posY_);
	}
	~Button() {}


	bool click(int x, int y)
	{
		if ((x > posX_ && x < (posX_ + size_.x())) && (y > posY_ && y < (posY_ + size_.y())))
			return true;
		return false;
	}

	void draw(sf::RenderWindow * window)
	{
		window->draw(spr_);
	}

};