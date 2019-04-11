#include "QSort.h"
#include "Player.h"

int main()
{
	//*
	QSort<HeroCore> * t = nullptr;

	HeroCore *heroes[1000];

	for (int i = 1000; i >= 0; i--)
	{
		heroes[i] = new Player(i * 20.0f, float(i) / 7);
	}

	system("pause");

	for (int i = 0; i < 1000; i++)
	{
		t = t->insert(t, heroes[i]);
	}

	t->print();
	
	t->free();

	system("pause");

	return 0;
	//*/

	/*
	Node<float> * t = nullptr;

	for (int i = 10000; i > 1000; i--)
	{
		t = t->insert(t, float(i) / 3);
	}

	t->print();


	system("pause");
	//*/
}