#include "RunLevel.hpp"
#include "MainPage.hpp"
#include "Mult.cpp"
#include  "Win_Lose.cpp"

int main()
{
	int hero = 0;
	
	while (1)
	{
		hero = startGame();
		if (hero == EXIT)
			return 0;
		if (hero == MULT)
		{
			RunVideo();
			continue;
		}
	
		int exitID = 0;
		if (hero >= 0)
			exitID = RunLevel(hero);
		switch (exitID)
		{
		case WIN:
			Win();
			break;
		case LOSE:
			Lose();
			break;
		}
	}

	return 0;
}