
// Roberto Villazana
// Van Ta
// Peter Dang
// Eddie Molina
// Project 1
// CSE 4360-001
// October 22, 2018

#include <ev3.h>

//#define MAX_OBSTABLES 25

void Forward(int tiles);
void Stop();
void Right();
void Left();
void getGoal();
void getStart();
void getObstacle(int i);
void startSong();
void endSong();

int num_obstacles = 13;

double obstacle[25][2] =        /*obstacle locations*/
{{0.61, 2.743},{0.915, 2.743},{1.219, 2.743},{1.829, 1.219},
{1.829, 1.524},{ 1.829, 1.829}, {1.829, 2.134},{2.743, 0.305},
{2.743, 0.61},{2.743, 0.915},{2.743, 2.743},{3.048, 2.743},
{3.353, 2.743},
{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},
{-1,-1},{-1,-1},{-1,-1}};

double start[2] = {0.305, 1.219};		/* Start Location */
double goal[2] = {3.658, 1.829};		/* Goal Location  */

int grid[16][11];
int startx;
int starty;
int goalx;
int goaly;

int main(void)
{
	int i;
	int j;
	int position;
	int direction;	//	1 - North, 2 - East, 3 - West, 4 - South
	getStart();
	getGoal();

	for (i = 0; i < num_obstacles; i++)
	{
		getObstacle(i);
	}

	finalizeGrid();

	position = grid[startx][starty];
	direction = 2;						//	Initialize Direction

	grabPath(position,direction);



	InitEV3();

	startSong();
	executePath(position,direction);
	endSong();

	FreeEV3();
	return 0;
}

/*
 * Mario Start Song
 */
void startSong()
{
	double c5 = 523.25;
	double e5 = 659.25;
	double g5 = 783.99;
	double g4 = 392;

	PlayTone(e5,NOTE_QUARTER);
	Wait(MS_400);
	PlayTone(e5,NOTE_EIGHT);
	Wait(MS_200);
	PlayTone(e5,NOTE_QUARTER);
	Wait(MS_400);
	PlayTone(c5,NOTE_EIGHT);
	Wait(MS_200);
	PlayTone(e5,NOTE_QUARTER);
	Wait(MS_400);
	PlayTone(g5,NOTE_HALF);
	Wait(MS_800);
	PlayTone(g4,NOTE_HALF);
	Wait(MS_800);

}

/*
 * Mario End Song
 */
void endSong()
{
	double c5 = 523.25;
	double e5 = 659.25;
	double g5 = 783.99;
	double g4 = 392;
	double c4 = 261.63;
	double e4 = 329.63;
	double ef = 311.13;
	double af = 415.30;
	double ef5 = 622.25;
	double af5 = 830.61;
	double d4 = 293.66;
	double f4 = 349.23;
	double bf = 466.16;
	double d5 = 587.33;
	double f5 = 698.46;
	double bf5 = 932.33;
	double c = 1046.50;

	PlayTone(c4,NOTE_EIGHT);
	Wait(MS_100);
	PlayTone(e4,NOTE_EIGHT);
	Wait(MS_100);
	PlayTone(g4,NOTE_EIGHT);
	Wait(MS_100);
	PlayTone(c5,NOTE_EIGHT);
	Wait(MS_100);
	PlayTone(e5,NOTE_EIGHT);
	Wait(MS_100);
	PlayTone(g5,NOTE_HALF);
	Wait(MS_400);
	PlayTone(e5,NOTE_HALF);
	Wait(MS_400);

	PlayTone(c4,NOTE_EIGHT);
	Wait(MS_100);
	PlayTone(ef,NOTE_EIGHT);
	Wait(MS_100);
	PlayTone(af,NOTE_EIGHT);
	Wait(MS_100);
	PlayTone(c5,NOTE_EIGHT);
	Wait(MS_100);
	PlayTone(ef5,NOTE_EIGHT);
	Wait(MS_100);
	PlayTone(af5,NOTE_HALF);
	Wait(MS_400);
	PlayTone(ef5,NOTE_HALF);
	Wait(MS_400);

	PlayTone(d4,NOTE_EIGHT);
	Wait(MS_100);
	PlayTone(f4,NOTE_EIGHT);
	Wait(MS_100);
	PlayTone(bf,NOTE_EIGHT);
	Wait(MS_100);
	PlayTone(d5,NOTE_EIGHT);
	Wait(MS_100);
	PlayTone(f5,NOTE_EIGHT);
	Wait(MS_100);
	PlayTone(bf5,NOTE_HALF);
	Wait(MS_400);
	PlayTone(bf5,NOTE_QUARTER);
	Wait(MS_150);
	PlayTone(bf5,NOTE_QUARTER);
	Wait(MS_150);
	PlayTone(bf5,NOTE_QUARTER);
	Wait(MS_100);
	PlayTone(c,NOTE_WHOLE);
	Wait(MS_800);
}

/*
 * Given the number of tiles, the EV3 proceeds forward for each tile.
 */
void Forward(int tiles)
{
	int i;
	int x = 1;

	for (i = 0; i < tiles; i++)
	{
		if (x != 3)
		{
			OnFwdReg(OUT_A,26);
			OnFwdReg(OUT_D,26);
			Wait(SEC_2);
			Wait(MS_400);
			Stop();
		}
		else
		{
			OnFwdReg(OUT_A,28);
			OnFwdReg(OUT_D,26);
			Wait(SEC_2);
			Wait(MS_400);
			Stop();
			x= x - 3;
		}

		x = x + 1;
	}
}

/*
 * Stop EV3 for 700Leftms
 */
void Stop()
{
	OnFwdReg(OUT_A,0);
	OnFwdReg(OUT_D,0);
	Wait(MS_700);
}

/*
 * Function to turn Right
 */
void Right()
{
	OnFwdReg(OUT_A,0);
	OnRevReg(OUT_D,46);
	Wait(MS_500);
	OnFwdReg(OUT_A,41);
	OnRevReg(OUT_D,0);
	Wait(MS_400);

}

/*
 * Function to turn Left
 */
void Left()
{
	OnRevReg(OUT_A,46);
	OnFwdReg(OUT_D,0);
	Wait(MS_400);
	OnFwdReg(OUT_D,48);
	OnRevReg(OUT_A,0);
	Wait(MS_500);
}

/*
 * After path has been finalized, EV3 proceeds forward and turns to where there is a -3 in the grid
 * until it reaches it's destination
 */
void executePath(int position, int direction)
{
	int x = startx;
	int y = starty;

	while(1)
	{
		if (direction == 1)		//	Facing North
		{
			while (grid[x][y + 1] == -3 && y < 11)		//	testing the next tile if in path
			{
				Forward(1);
				y++;
			}

			if (x == goalx && y == goaly)				//	Stop when at destination
				break;

			if (grid[x - 1][y] < grid[x + 1][y])		//	Turn to which ever is next in path
			{
				Left();
				direction = 3;
			}
			else
			{
				Right();
				direction = 2;
			}
		}

		if (direction == 2)		//	Facing East
		{
			while (grid[x + 1][y] == -3 && x < 16)		//	testing the next tile if in path
			{
				Forward(1);
				x++;
			}

			if (x == goalx && y == goaly)				//	Stop when at destination
				break;

			if (grid[x][y - 1] < grid[x][y + 1])		//	Turn to which ever is next in path
			{
				Right();
				direction = 4;
			}
			else
			{
				Left();
				direction = 1;
			}
		}

		if (direction == 3)		//	Facing West
		{
			while (grid[x - 1][y] == -3 && x > 0)		//	testing the next tile if in path
			{
				Forward(1);
				x--;
			}

			if (x == goalx && y == goaly)				//	Stop when at destination
				break;

			if (grid[x][y - 1] < grid[x][y + 1])		//	Turn to which ever is next in path
			{
				Left();
				direction = 4;
			}
			else
			{
				Right();
				direction = 1;
			}
		}

		if (direction == 4)		//	Facing South
		{
			while (grid[x][y - 1] == -3 && y > 0)		//	testing the next tile if in path
			{
				Forward(1);
				y--;
			}

			if (x == goalx && y == goaly)				//	Stop when at destination
				break;

			if (grid[x - 1][y] < grid[x + 1][y])		//	Turn to which ever is next in path
			{
				Right();
				direction = 3;
			}
			else
			{
				Left();
				direction = 2;
			}
		}
	}
}

/*
 * Obtain the coordinates for the goal
 */
void getGoal()
{
	double meters_per_tile = 0.61 / 2;

	double tiles = 0;

	//	Get how many tiles it takes in the x-axis for goal
	while (tiles < goal[0])
	{
		tiles = tiles + meters_per_tile;
		goalx = goalx + 1;
	}

	//	Get how many tiles it takes in the y-axis for goal
	tiles = 0;
	while (tiles < goal[1])
	{
		tiles = tiles + meters_per_tile;
		goaly = goaly + 1;
	}

	grid[goalx][goaly] = -3;		//	-3 is the goal
}

/*
 * Obtain coordinates for the start
 */
void getStart()
{
	double meters_per_tile = 0.61 / 2;


	double tiles = 0;

	//	Get how many tiles it takes in the x-axis for start
	while (tiles < start[0])
	{
		tiles = tiles + meters_per_tile;
		startx = startx + 1;
	}

	//	Get how many tiles it takes in the y-axis for start
	tiles = 0;
	while (tiles < start[1])
	{
		tiles = tiles + meters_per_tile;
		starty = starty + 1;
	}

	grid[startx][starty] = -2;		//	-2 is the start
}

/*
 * Coordinates for every obstacle into grid
 */
void getObstacle(int i)
{
	double meters_per_tile = 0.61 / 2;

	int x = 0;
	int y = 0;
	double tiles = 0;

	//	Get how many tiles it takes in the x-axis for start
	while (tiles < obstacle[i][0])
	{
		tiles = tiles + meters_per_tile;
		x = x + 1;
	}

	//	Get how many tiles it takes in the y-axis for start
	tiles = 0;
	while (tiles < obstacle[i][1])
	{
		tiles = tiles + meters_per_tile;
		y = y + 1;
	}

	grid[x][y] = -1;		//	-1 is the Obstacle
	if (x < 16)
		grid[x + 1][y] = -1;
	if ((y + 1) < 11)
		grid[x][y + 1] = -1;
	if ((x + 1) < 16 && (y + 1) < 11)
		grid[x + 1][y + 1] = -1;
}

/*
 * Function for path planning using Manhattan Path Planning
 */
void finalizeGrid()
{
	int i;
	int j;
	int k;

	i = 1;

	//	Put 1's around the Goal
	if (grid[goalx - 1][goaly] == 0)
		grid[goalx - 1][goaly] = i;
	if (grid[goalx][goaly - 1] == 0)
		grid[goalx][goaly - 1] = i;
	if (grid[goalx + 1][goaly] == 0)
		grid[goalx + 1][goaly] = i;
	if (grid[goalx][goaly + 1] == 0)
		grid[goalx][goaly + 1] = i;

	i++;

	//	while the start hasn't been changed
	while (grid[startx][starty] == -2)
	{
		for (j = 9; j > 0; j--)
		{
			for (k = 0; k < 16; k++)
			{
				if (grid[k][j] == (i-1))
				{
					if (grid[k - 1][j] == 0 || grid[k - 1][j] == -2)	//	change everything around with the next number if it is equal to 0
						grid[k - 1][j] = i;
					if (grid[k][j - 1] == 0 || grid[k][j - 1] == -2)
						grid[k][j - 1] = i;
					if (grid[k + 1][j] == 0 || grid[k + 1][j] == -2)
						grid[k + 1][j] = i;
					if (grid[k][j + 1] == 0 || grid[k][j + 1] == -2)
						grid[k][j + 1] = i;
				}
			}
		}

		i++;
	}
}


/*
 * Grab the shortest path from the start to the goal
 */
void grabPath(int position, int direction)
{
	int x = startx;
	int y = starty;
	int exit = 0;

	while (1)
	{
		if (direction == 1)		//	Facing North
		{
			while (grid[x][y + 1] != -1 && y < 10)		//	while next tile is not an obstacle
			{
				if (grid[x][y + 1] == (position - 1))
					grid[x][y + 1] = -3;				//	if tile suppose to be in path, make it equal -3 for the path to the goal
				else if (grid[x][y + 1] == -3)
					exit = 1;
				else
					break;
				position--;
				y++;
			}

			if (grid[x + 1][y] < grid[x - 1][y] && x != 16)		//	Change direction to wherever the next number is.
				direction = 2;
			else
				direction = 3;

			if (grid[x - 1][y] == -1)
				direction = 2;
			else if (grid[x + 1][y] == -1)
				direction = 3;
		}

		if (exit == 1)
			break;


		if (direction == 2)		//	Facing East
		{
			while (grid[x + 1][y] != -1 && x < 16)		//	while next tile is not an obstacle
			{
				if (grid[x + 1][y] == (position - 1))
					grid[x + 1][y] = -3;				//	if tile suppose to be in path, make it equal -3 for the path to the goal
				else if (grid[x + 1][y] == -3)
					exit = 1;
				else
					break;
				position--;
				x++;
			}


			if (grid[x][y + 1] < grid[x][y - 1] && y != 10)		//	change direction to wherever the next tile is
				direction = 1;
			else
				direction = 4;

			if (grid[x][y - 1] == -1)
				direction = 1;
			else if (grid[x][y + 1] == -1)
				direction = 4;
		}

		if (exit == 1)
			break;

		if (direction == 3)		//	Facing East
		{
			while (grid[x - 1][y] != -1 && x > 0)
			{
				if (grid[x - 1][y] == (position - 1))
					grid[x - 1][y] = -3;
				else if (grid[x - 1][y] == -3)
					exit = 1;
				else
					break;
				position--;
				x--;
			}

			if (grid[x][y + 1] < grid[x][y - 1] && y != 10)
				direction = 1;
			else
				direction = 4;

			if (grid[x][y - 1] == -1)
				direction = 1;
			else if (grid[x][y + 1] == -1)
				direction = 4;
		}

		if (exit == 1)
			break;


		if (direction == 4)		//	Facing South
		{
			while (grid[x][y - 1] != -1 && y > 0)
			{
				if (grid[x][y - 1] == (position - 1))
					grid[x][y - 1] = -3;
				else if (grid[x][y - 1] == -3)
					exit = 1;
				else
					break;
				position--;
				y--;
			}

			if (grid[x + 1][y] < grid[x - 1][y] && x != 16)
				direction = 2;
			else
				direction = 3;

			if (grid[x - 1][y] == -1)
				direction = 2;
			else if (grid[x + 1][y] == -1)
				direction = 3;
		}

		if (exit == 1)
			break;
	}
}



