#include <iostream>
#include <time.h>

enum
{
	ERROR = 134,

	WALL = 5,

	NO_WALL = 6,

	RANDOM_NUMBER = 56


};

//FILE* loggg;

class cell
{
	//private:
	public:
		int north_, west_, east_, south_; // много памяти
		int set_;
	//public:
		//int create_wall(char letter);
		int delete_wall(char letter);
		bool check_wall(char letter); 
		int& cset();// вторая функция с аргуметом изменения
};

class maze
{
	//private:
	public:
		cell** cell_;
		int vertical_, horizontal_;
	//public:
		maze(int vert, int horiz);
		~maze();

		int change_array_before_start(cell** array, int number, int range);

		int last_line_processing (cell* array, int range);

		int print_maze();


		int* convert();

		int test();

};



int get_random();

maze:: maze(int vert, int horiz):
vertical_(vert),
horizontal_(horiz)

{
	cell_ = new(std:: nothrow) cell* [vert];

	if (cell_ == nullptr)
		printf("Not enough memmory\nProblem in maze constructor\n");

	for (int i = 0; i < vert; i++)
	{
		cell_[i] = new(std:: nothrow) cell[horiz];
		if (cell_[i] == nullptr)
			printf("Not enough memmory\nProblem in maze constructor\n");

		for (int j = 0; j < horiz; j++)
		{
			cell_[i][j].east_ = NO_WALL;
			cell_[i][j].west_ = NO_WALL;
			cell_[i][j].north_ = NO_WALL;
			cell_[i][j].south_ = NO_WALL;

			if (i == 0)
				cell_[0][j].north_ = WALL;
		}
	}

	for (int j = 0; j < horiz; j++)
		cell_[0][j].cset() = j;


	// begin

	for (int i = 0; i < vert; i++)
	{
		cell_[i][0].west_ = WALL; // optimize (лишнее действие и так произойдет из-за копирования)
		cell_[i][horiz - 1].east_ = WALL;

	

		for (int j = 0; j < horiz - 1; j++)
		{
			if (cell_[i][j].cset() != cell_[i][j + 1].cset())
				if (get_random() % 3 == 1)
				{
					cell_[i][j].east_ = WALL;
					cell_[i][j + 1].west_ = WALL;
				}

				else
					cell_[i][j + 1].cset() = cell_[i][j].cset(); 

			else
			{
				cell_[i][j].east_ = WALL;
				cell_[i][j + 1].west_ = WALL;
			}
		}




		bool was_opened_cell = false;

		for (int j = 0; j < horiz; j++)
			std:: cout << cell_[i][j].cset() << ' ';

		printf("\n");

		for (int j = 0; j < horiz - 1; j++)
		{

			if ((cell_[i][j].cset() != cell_[i][j + 1].cset() && was_opened_cell == true) || (cell_[i][j].cset() == cell_[i][j + 1].cset()))
				if (get_random() % 3 == 1)
				{
					cell_[i][j].south_ = WALL;

					if (i + 1 < vertical_)
						cell_[i + 1][j].north_ = WALL;
				}

				else
					was_opened_cell = true;
			else
				was_opened_cell = true;


			if (cell_[i][j].cset() != cell_[i][j + 1].cset())
				was_opened_cell = false;
		}

		if (was_opened_cell)
			if (get_random() % 3 == 1)
			{
				cell_[i][horiz - 1].south_ = WALL;

				if (i + 1 < vertical_)
					cell_[i + 1][horiz - 1].north_ = WALL;
			}			


		if (i + 1 < vert)
		{

			for (int j = 0; j < horiz; j++)
			{
				//cell_[i + 1][j] = cell_[i][j];
				cell_[i + 1][j].south_ = cell_[i][j].south_;
				cell_[i + 1][j].east_ = cell_[i][j].east_;
				cell_[i + 1][j].west_ = cell_[i][j].west_;
				cell_[i + 1][j].set_ = cell_[i][j].set_;
			}

			int res = change_array_before_start(cell_, i + 1, horiz);
			if (res == ERROR)
				printf("There is a problem with change_array_before_start\n");
		}
	}

	int res = last_line_processing(cell_[vert - 1], horiz);
}

int get_random()
{
	static int a = 0;

	a += time(NULL);

	a -= RANDOM_NUMBER;

	a %= 124;

	return a;
}

int maze:: change_array_before_start(cell** array, int number, int range)
{
	if (array == nullptr)
		return ERROR;

	int* array_of_set_number = (int*) calloc (range, sizeof(int));


	for (int i = 0; i < range; i++)
	{
		if (i > 0)
			array[number][i].delete_wall('w');
		if (i < range - 1)
			array[number][i].delete_wall('e');

		if (array[number][i].check_wall('s'))
		{
			array[number][i].cset() = -1;

			array[number][i].south_ = NO_WALL;

			if (number < vertical_ - 1)
				array[number + 1][i].north_ = NO_WALL;
		}
		else
		{
			array_of_set_number[array[number][i].cset()] = 1;
		}
	}

	int set_number = 0;

	for (int i = 0; i < range; i++)
	{
		if (array[number][i].cset() == -1)
		{
			while (array_of_set_number[set_number] != 0)
				set_number++;

			array[number][i].cset() = set_number;

			array_of_set_number[set_number] = 1;
		}
	}

	return 0;
}


int maze:: last_line_processing(cell* array, int range)
{
	int prev = array[0].cset();

	for (int i = 0; i < range - 1; i++)
	{
		if (prev != array[i + 1].cset())
		{
			prev = array[i + 1].cset();

			array[i + 1].cset() = array[i].cset();

			array[i + 1].delete_wall('w');

			array[i].delete_wall('e');
		}

		array[i].south_ = WALL;
	}

	array[range - 1].south_ = WALL;

	return 0;
}


/*int cell:: create_wall(char letter)
{
	switch (letter)
	{
		case 's':
			south_ = WALL;
			break;
		case 'n':
			north_ = WALL;
			break;
		case 'e':
			east_ = WALL;
			break;
		case 'w':
			west_ = WALL;
			break;
		case 'a':
			south_ = WALL;
			north_ = WALL;
			east_ = WALL;
			west_ = WALL;
			break;
		default:
			printf("Wrong letter in create_wall\n");
	}

	return 0;
}*/



int cell:: delete_wall(char letter)
{
	switch (letter)
	{
		case 's':
			south_ = NO_WALL;
			break;
		case 'n':
			north_ = NO_WALL;
			break;
		case 'e':
			east_ = NO_WALL;
			break;
		case 'w':
			west_ = NO_WALL;
			break;
		case 'a':
			south_ = NO_WALL;
			north_ = NO_WALL;
			east_ = NO_WALL;
			west_ = NO_WALL;
			break;
		default:
			printf("Wrong letter in delete_wall\n");
	}

	return 0;
}
bool cell:: check_wall(char letter)
{
	switch (letter)
	{
		case 's':
			if (south_ == WALL)
				return true;
			break;
		case 'n':
			if (north_ == WALL)
				return true;
			break;
		case 'e':
			if (east_ == WALL)
				return true;
			break;
		case 'w':
			if (west_ == WALL)
				return true;
			break;
		default:
			printf("Wrong letter in check_wall\n");
	}

	return false;
} 


int& cell:: cset()
{
	return set_;
}

int maze:: print_maze()
{

	for (int i = 0; i < horizontal_; i++)
		printf(" __");

	printf("\n");

	for (int i = 0; i < vertical_; i++)
	{
		printf("|");

		for (int j = 0; j < horizontal_; j++ )
		{
			if (cell_[i][j].south_ == WALL)
			{
				if (i < vertical_ - 1)
					if(cell_[i + 1][j].north_ != WALL)
						printf("!!");
					else
						printf("__");
				else
					printf("__");
			}
			else
				printf("  ");

			if (cell_[i][j].check_wall('e'))
				printf("|");
			else
				printf(" ");
		}

		printf("\n");
	}

	return 0;
}


maze:: ~maze()
{
	for (int i = 0; i < vertical_; i++)
		delete[] cell_[i];

	delete[] cell_;

	printf("DESTRUCTOR!!!\n");

}
int* maze:: convert ()
{
	int* res = new int [(vertical_ + 1) * (horizontal_ + 1)];
	for (int i = 0; i < (vertical_ + 1) * (horizontal_ + 1); i++)
		res[i] = 0;

	int k = 0;

	for (int i = 0; i < vertical_; i++)
	{
		for (int j = 0; j < horizontal_; j++)
		{
			if (cell_[i][j].north_ == WALL)
			{

				if (i > 0)
					if(cell_[i - 1][j].south_ != WALL)
						printf("! ");



				k++;
				res[(i) * (horizontal_ + 1) + j] += RIGHT;
			}

			if (cell_[i][j].west_ == WALL)
				res[(i + 1) * (horizontal_ + 1) + j] += DOWN;
		}

		res[(i + 1) * (horizontal_ + 1) + horizontal_] += DOWN;
	}

	for (int j = 0; j < horizontal_; j++)
		res[(vertical_) * (horizontal_ + 1) + j] += RIGHT;

	printf("%d\n", k);
	return res;
}

int maze:: test ()
{
	for (int i = 0; i < vertical_; i++)
		for(int j = 0; j < horizontal_; j++)
		{
			cell_[i][j].north_ = WALL;
			cell_[i][j].west_ = WALL;
			cell_[i][j].east_ = NO_WALL;
			cell_[i][j].south_ = NO_WALL;
		}

}



/*int main()
{
	loggg = fopen("loggg.txt", "w");

	fclose(loggg);



	loggg = fopen("loggg.txt", "a");

	fprintf(loggg, "begin\n");

	fclose(loggg);



	//printf("%d\n", time(NULL));

	maze a(5, 5);

	
	a.print_maze();



	return 0;
}*/