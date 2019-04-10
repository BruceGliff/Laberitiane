#pragma once

#include <SFML/Graphics.hpp>

sf::View  camera;

void setCameraCoor(float x, float y)
{
	camera.setCenter(x, y);
}