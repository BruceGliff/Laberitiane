#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;

int main()
{
	setlocale(LC_ALL, "Russian");

	sf::RenderWindow window(sf::VideoMode(100, 100), "Laberitianin");

	RectangleShape shape(Vector2f(200, 100));
	shape.setFillColor(Color(255, 255, 255));

	shape.setPosition(0, 0);

	Image img;
	img.loadFromFile("ref/images/skins.png");

	Texture texture;
	texture.loadFromImage(img);

	Sprite sprite;
	sprite.setTexture(texture);
	sprite.setTextureRect(IntRect(0, 64, 16, 16));
	sprite.setPosition(50, 25);

	Clock clock;

	float CurrFrame = 0;

	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time /= 1800;
		std::cout << time << "\n";
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		if (Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(Keyboard::D))
		{
			CurrFrame += 0.035 * time;
			if (CurrFrame > 3) CurrFrame -= 3;

			sprite.setTextureRect(IntRect(16 * int(CurrFrame), 80, 16, 16));
			sprite.move(0.1 * time, 0);
		}
		if (Keyboard::isKeyPressed(Keyboard::Left) || Keyboard::isKeyPressed(Keyboard::A))
		{ 
			CurrFrame += 0.035 * time;
			if (CurrFrame > 3) CurrFrame -= 3;
			
			sprite.setTextureRect(IntRect(16 * (int(CurrFrame) + 1), 80, -16, 16));
			sprite.move(-0.1 * time, 0);
		}
		if (Keyboard::isKeyPressed(Keyboard::Up) || Keyboard::isKeyPressed(Keyboard::W)) 
		{ 
			CurrFrame += 0.035 * time;
			if (CurrFrame > 3) CurrFrame -= 3;

			sprite.setTextureRect(IntRect(16 * int(CurrFrame), 96, 16, 16));
			sprite.move(0, -0.1 * time);
		}
		if (Keyboard::isKeyPressed(Keyboard::Down) || Keyboard::isKeyPressed(Keyboard::S))
		{
			CurrFrame += 0.035 * time;
			if (CurrFrame > 3) CurrFrame -= 3;

			sprite.setTextureRect(IntRect(16 * int(CurrFrame), 64, 16, 16));
			sprite.move(0, 0.1 * time);
		}

		window.clear();
		window.draw(shape);
		window.draw(sprite);

		window.display();
	}

	return 0;
}