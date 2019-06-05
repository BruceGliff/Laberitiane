#include "RunLevel.hpp"
#include "MainPage.hpp"
#include "Mult.cpp"

int main()
{
	int hero = 0;
	while ((hero = startGame()) == MULT)
	{
		RunVideo();
	}
	int exitID = 0;
	if (hero >= 0)
		exitID = RunLevel(hero);
	switch (exitID)
	{
	case WIN:
		std::cout << "WIN";
		break;
	case LOSE:
		std::cout << "LOSE";
		break;
	}
	//system("pause");

	return 0;
}