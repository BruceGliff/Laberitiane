#pragma once
#include <SFML/Graphics.hpp>
#include "ObjectCore.h"

class Wall : public ObjectCore
{
public:
	Wall(float x = 0, float y = 0, int heroNumber = 0, float dx = 0, float dy = 0, float animSpeed = 0, int frames = 1, float scale = 1, int w = 34, int h = 27, const char * fileName = "ref/images/wall.png") :
		ObjectCore(0, x, y, dx, dy, animSpeed, frames, scale, w, h, fileName)
	{
		updateRect(heroNumber);
	}


	void move(int dir, float time) {}
	void setView(sf::RenderWindow * window) {}
	sf::View * getView() { return nullptr; }

	//void setOpacity();
};