#include "RunLevel.hpp"
#include "MainPage.hpp"

int main()
{
	int hero = startGame();
	if (hero >= 0)
		RunLevel(hero);
	return 0;
}