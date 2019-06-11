#include <iostream>
#include <time.h>
#include <assert.h>

#define SUCCESS 135
#define DEAD_END 134

enum
{
	NOTHING = 0,
	RIGHT = 1,
	DOWN = 2,
	BOTH = 3

};

enum step_direction
{
	S_END = 0,
	S_UP = 1,
	S_DOWN = 2,
	S_LEFT = 3,
	S_RIGHT = 4
};

enum 
{
	ERROR = 134,

	WALL = 5,

	NO_WALL = 6,

	RANDOM_NUMBER = 56


};


struct coord
{
	int x, y;
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

class Maze
{
	//private:
public:
	cell** cell_;
	int vertical_, horizontal_;
	//public:
	Maze(int vert, int horiz);
	~Maze();

	int change_array_before_start(cell** array, int number, int range);

	int last_line_processing(cell* array, int range);

	int print_Maze();


	int* convert();

	int test();

	int find_path(int* arr, int x1, int y1, int x2, int y2, int step, coord* track, int size);

	int vertical()
	{
		return vertical_;
	}

	int horizontal()
	{
		return horizontal_;
	}

};



int get_random();

Maze::Maze(int vert, int horiz) :
	vertical_(vert),
	horizontal_(horiz)

{
	cell_ = new(std::nothrow) cell*[vert];

	if (cell_ == nullptr)
		printf("Not enough memmory\nProblem in Maze constructor\n");

	for (int i = 0; i < vert; i++)
	{
		cell_[i] = new(std::nothrow) cell[horiz];
		if (cell_[i] == nullptr)
			printf("Not enough memmory\nProblem in Maze constructor\n");

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

		//for (int j = 0; j < horiz; j++)
			//std::cout << cell_[i][j].cset() << ' ';

		//printf("\n");

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

	a += int(time(NULL));

	a -= RANDOM_NUMBER;

	a %= 124;

	//a = 0;

	return a;
}

int Maze::change_array_before_start(cell** array, int number, int range)
{
	if (array == nullptr)
		return ERROR;

	int* array_of_set_number = (int*)calloc(range, sizeof(int));


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


int Maze::last_line_processing(cell* array, int range)
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



int cell::delete_wall(char letter)
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
bool cell::check_wall(char letter)
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


int& cell::cset()
{
	return set_;
}

int Maze::print_Maze()
{

	for (int i = 0; i < horizontal_; i++)
		printf(" __");

	printf("\n");

	for (int i = 0; i < vertical_; i++)
	{
		printf("|");

		for (int j = 0; j < horizontal_; j++)
		{
			if (cell_[i][j].south_ == WALL)
			{
				if (i < vertical_ - 1)
					if (cell_[i + 1][j].north_ != WALL)
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


Maze:: ~Maze()
{
	for (int i = 0; i < vertical_; i++)
		delete[] cell_[i];

	delete[] cell_;

	//printf("DESTRUCTOR!!!\n");

}
int* Maze::convert()
{
	int* res = new int[(vertical_ + 1) * (horizontal_ + 1)];
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
					if (cell_[i - 1][j].south_ != WALL)
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

	//printf("%d\n", k);
	return res;
}

int Maze::test()
{
	for (int i = 0; i < vertical_; i++)
		for (int j = 0; j < horizontal_; j++)
		{
			cell_[i][j].north_ = WALL;
			cell_[i][j].west_ = WALL;
			cell_[i][j].east_ = NO_WALL;
			cell_[i][j].south_ = NO_WALL;
		}

}


bool checkTrack(coord* track, int size, int x, int y)
{
	for(int i = 0; i < size; i++)
	{
		if(x == track[i].x && y == track[i].y)
			return false;
	}

	return true;
}

int Maze:: find_path(int* arr, int x1, int y1, int x2, int y2, int step, coord* track, int size)
{
	//printf("**");
	assert(arr);
	if ((horizontal_ * vertical_ + 5) / 5  - step <= abs(x1 - x2) + abs(y1 - y2))
	{
		*arr = S_END;
		//printf("****\n");
		return 0;
	}

	if (x1 == x2 && y1 == y2)
	{
		*arr = S_END;
		//printf("**%d**\n", step);
		return step;
	}

	int path1 = 0;
	int path2 = 0;
	int path3 = 0;
	int path4 = 0;

	if (cell_[x1][y1].north_ == NO_WALL && checkTrack(track, step, x1 - 1, y1))
	{
		*arr = S_UP;
		track[step].x = x1;
		track[step].y = y1; 
		path1 = find_path(arr + 1, x1 - 1, y1, x2, y2, step + 1, track, size);
		if (path1 <= (abs(x1 - x2) + abs(y1 - y2)) * 3 / 2 && path1 != 0)
			return path1;
	}

	if (cell_[x1][y1].east_ == NO_WALL && checkTrack(track, step, x1, y1 + 1))
	{
		*arr = S_RIGHT;
		track[step].x = x1;
		track[step].y = y1;
		path2 = find_path(arr + 1, x1, y1 + 1, x2, y2, step + 1, track, size);
		if (path2 <= (abs(x1 - x2) + abs(y1 - y2)) * 3 / 2 && path2 != 0)
			return path2;
	}

	if (cell_[x1][y1].south_ == NO_WALL && checkTrack(track, step, x1 + 1, y1))
	{
		*arr = S_DOWN;
		track[step].x = x1;
		track[step].y = y1;
		path3 = find_path(arr + 1, x1 + 1, y1, x2, y2, step + 1, track, size);
		if (path3 <= (abs(x1 - x2) + abs(y1 - y2)) * 3 / 2 && path3 != 0)
			return path3;
	}

	if (cell_[x1][y1].west_ == NO_WALL && checkTrack(track, step, x1, y1 - 1))
	{
		*arr = S_LEFT;
		track[step].x = x1;
		track[step].y = y1;
		path4 = find_path(arr + 1, x1, y1 - 1, x2, y2, step + 1, track, size);
		if (path4 <= (abs(x1 - x2) + abs(y1 - y2)) * 3 / 2 && path4 != 0)
			return path4;
	}


	if (path1 == 0)
		path1 = horizontal_ * vertical_ + 5;
	if (path2 == 0)
		path2 = horizontal_ * vertical_ + 5;
	if (path3 == 0)
		path3 = horizontal_ * vertical_ + 5;
	if (path4 == 0)
		path4 = horizontal_ * vertical_ + 5;

	int deadEndNumber = horizontal_ * vertical_ + 5;

	if (path1 != deadEndNumber && (path1 <= path2) && (path1 <= path3) && (path1 <= path4))
	{
		*arr = S_UP;
		return find_path(arr + 1, x1 - 1, y1, x2, y2, step + 1, track, size);
	}
	else if (path2 != deadEndNumber && (path2 <= path1) && (path2 <= path3) && (path2 <= path4))
	{
		*arr = S_RIGHT;
		return find_path(arr + 1, x1, y1 + 1, x2, y2, step + 1, track, size);
	}
	else if (path3 != deadEndNumber && (path3 <= path1) && (path3 <= path2) && (path3 <= path4))
	{
		*arr = S_DOWN;
		return find_path(arr + 1, x1 + 1, y1, x2, y2, step + 1, track, size);
	}
	else if (path4 != deadEndNumber && (path4 <= path1) && (path4 <= path2) && (path4 <= path3))
	{
		*arr = S_LEFT;
		return find_path(arr + 1, x1, y1 - 1, x2, y2, step + 1, track, size);
	}

	return 0;
}



/*int main()
{
	//printf("%d\n", time(NULL));
	Maze a(10, 10);

	//a.test();
	a.print_Maze();
	int* arr = (int*) calloc(a.horizontal() * a.vertical() + 10, sizeof(int));


	coord *track = (coord*) calloc(a.horizontal() * a.vertical() + 10, sizeof(coord));
	for(int i = 0; i < a.horizontal() * a.vertical() + 10; ++i)
	{
		track[i].x = -1;
		track[i].y = -1;
	}
	int i = 0;
	int res = a.find_path(arr, 0, 0, 1, 1, 0, track, a.horizontal() * a.vertical() + 10);
	while (arr[i] != 0)
	{
		printf("%d\n", arr[i++]);
	}
	printf("%d\n", res);
	return 0;
}*/

/*int Maze:: find_path(int* arr, int x1, int y1, int x2, int y2, int step, coord* track, int size)
{
	//printf("**");
	assert(arr);
	if ((horizontal_ * vertical_ - step + 5) / 5 <= abs(x1 - x2) + abs(y1 - y2))
	{
		*arr = S_END;
		return DEAD_END;
	}

	if (x1 == x2 && y1 == y2)
	{
		*arr = S_END;
		return SUCCESS;
	}

	if (cell_[x1][y1].north_ == NO_WALL && checkTrack(track, size, x1 - 1, y1))
	{
		*arr = S_UP;
		track[step].x = x1;
		track[step].y = y1; 
		if(find_path(arr + 1, x1 - 1, y1, x2, y2, step + 1, track, size) == SUCCESS)
		{
			return SUCCESS;
		}
	}

	if (cell_[x1][y1].east_ == NO_WALL && checkTrack(track, size, x1, y1 + 1))
	{
		*arr = S_RIGHT;
		track[step].x = x1;
		track[step].y = y1;
		if(find_path(arr + 1, x1, y1 + 1, x2, y2, step + 1, track, size) == SUCCESS)
		{
			return SUCCESS;
		}
	}

	if (cell_[x1][y1].south_ == NO_WALL   && checkTrack(track, size, x1 + 1, y1))
	{
		*arr = S_DOWN;
		track[step].x = x1;
		track[step].y = y1;
		if(find_path(arr + 1, x1 + 1, y1, x2, y2, step + 1, track, size) == SUCCESS)
		{
			return SUCCESS;
		}
	}

	if (cell_[x1][y1].west_ == NO_WALL && checkTrack(track, size, x1, y1 - 1))
	{
		*arr = S_LEFT;
		track[step].x = x1;
		track[step].y = y1;
		if(find_path(arr + 1, x1, y1 - 1, x2, y2, step + 1, track, size) == SUCCESS)
		{
			return SUCCESS;
		}
	}

	return DEAD_END;
}*/