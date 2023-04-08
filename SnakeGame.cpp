#include <iostream>
#include <conio.h>

#include <windows.h> //For sleep

using namespace std;

bool gameOver;

const int width = 40;
const int height = 20;

int x, y, fruitX, fruitY , score, tailNumber;
int tailX[100], tailY[100];

enum eDirection { STOP = 0 , LEFT , RIGHT, UP, DOWN};
eDirection dir;

void randomizeFruit()
{
	fruitX = rand() % (width - 3) + 1;
	fruitY = rand() % (height - 3) + 1;
}

void setup()
{
	gameOver = false;

	dir = STOP;

	x = width / 2;
	y = height / 2;

	randomizeFruit();

	score = 0;

}



void draw()
{

	system("cls"); //Clean up windows

	for (int h = 0; h < height; h++)
	{
		for (int w = 0; w < width; w++)
		{

			if (h == 0 || h == height - 1)
			{
				cout << "#";
			}
			else
			{
				if (w == 0 || w == width - 1)
				{
					cout << "#";
				}
				else
				{

					if (w == x && h == y)
					{
						cout << "O";
					}
					else if (w == fruitX && h == fruitY)
					{
						cout << "F";
					}
					else
					{

						bool printed = false;

						for (int i = 0; i < tailNumber; i++)
						{

							if (tailX[i] == w && tailY[i] == h)
							{
								cout << "o";
								printed = true;
							}

						}

						if (!printed)
						{
							cout << " ";
						}

					}

				}

			}


		}

		cout << endl;

	}

	cout << "Score:" << score << endl;

}

void input()
{

	if (_kbhit()) //Any key pressed
	{

		switch (_getch())
		{
			case 'a':
				dir = LEFT;
				break;

			case 'd':
				dir = RIGHT;
				break;

			case 'w':
				dir = UP;
				break;

			case 's':
				dir = DOWN;
				break;

			case 27: //Esc
				gameOver = true;
				break;
			
		}

	}

}

void logic()
{

	int previusX = tailX[0];
	int previusY = tailY[0];

	int previus2X, previus2Y;

	tailX[0] = x;
	tailY[0] = y;

	for (int i = 1; i < tailNumber; i++)
	{

		previus2X = tailX[i];
		previus2Y = tailY[i];

		tailX[i] = previusX;
		tailY[i] = previusY;

		previusX = previus2X;
		previusY = previus2Y;
	}


	switch (dir)
	{
	case LEFT:
		x--;
		break;

	case RIGHT:
		x++;
		break;

	case UP:
		y--;
		break;

	case DOWN:
		y++;
		break;
	}

	//Wall
	if (x >= width - 1)
	{
		x = 0;
	}
	else if (x < 0)
	{
		x = width - 1;
	}

	if (y >= height - 1)
	{
		y = 0;
	}
	else if (y < 0)
	{
		y = height - 1;
	}

	//Self eat
	for (int i = 0; i < tailNumber; i++)
	{

		if (x == tailX[i] && y == tailY[i])
		{
			gameOver = true;
		}
		
	}

	//Fruit
	if (x == fruitX && y == fruitY)
	{

		score += 10;

		randomizeFruit();

		tailNumber++;

	}

}


int main()
{

	setup();

	while (!gameOver)
	{
		draw();
		input();
		logic();
		Sleep(30);
	}

	return 0;
}