#include <iostream>
#include <fstream>
#include <conio.h>

#include <windows.h> //For sleep
#include <string>
#include <stack>
#include <queue>

using namespace std;

int sizeX = 60, sizeY = 20;
char wall = '#';

bool pause = false;

const int size = 5;
int appSpeed = 6000;

//POSITION CLASS
class Position
{

public:
	int x,y;
	int horizontalDir,verticalDir;

	Position()
	{
		x = rand() % sizeX + 0;
		y = rand() % sizeY + 0;

		horizontalDir = 1;
		verticalDir = 1;
	}

	Position operator + (Position pos)
	{
		Position new_pos;
		new_pos.x = x + pos.x;
		new_pos.y = y + pos.y;
		return new_pos;
	}

	Position operator - (Position pos)
	{
		Position new_pos;
		new_pos.x = x - pos.x;
		new_pos.y = y - pos.y;
		return new_pos;
	}

	void Update()
	{
		if(x >= sizeX - 1 || x <= 1)
		{
			horizontalDir *= -1;
		}
		if(y >= sizeY - 1 || y <= 1)
		{
			verticalDir *= -1;
		}

		x += horizontalDir;
		y += verticalDir;

	}

	void Print()
	{
		cout << "(" << x << "," << y << ")\t" << (x + y);
	}

	void Ispis()
	{
		cout << "(" << x << "," << y << ")";
	}

	void Pair()
	{
		pair <string, int> xPair("x:", x);
		pair <string, int> yPair("y:", y);

		swap(xPair, yPair);

		cout << xPair.first << xPair.second << " " << yPair.first << yPair.second;
	}

};

//CIRCLE CLASS
class Circle: public Position
{

private:
	static int counter;

public:
	char sing;

	Circle()
	{
		sing = 'o';
		counter ++;
	}

};

int Circle::counter = 0;

Circle cir[size];


//STAR CLASS
class Star: public Position
{

private:
	static int counter;

public:
	char sing;

	Star()
	{
		sing = '*';
		counter ++;

		horizontalDir = -1;
		verticalDir = -1;
	}
};

int Star::counter = 0;

Star str[size];


void Render()
{

	system("cls"); //Clean up windows

	for(int y = 0; y <= sizeY; y++)
	{
		for(int x = 0; x <= sizeX; x++)
		{

			if(x == 0 || x == sizeX)
			{
				cout << wall;
			}
			else if(y == 0 || y == sizeY)
			{
				cout << wall;
			}
			else
			{

				char sign = ' ';

				for(int i = 0; i < size; i++)
				{
					if(x == cir[i].x && y == cir[i].y)
					{
						sign = cir[i].sing;
						break;
					}
				}

				for(int i = 0; i < size; i++)
				{
					if(x == str[i].x && y == str[i].y)
					{
						sign = str[i].sing;
						break;
					}
				}

				cout << sign;

			}
		}

		cout << endl;

	}

}

void Update()
{
	for(int i = 0; i < size; i++)
	{
		cir[i].Update();
		str[i].Update();
	}
}

template<class T>
void print(T arr[size])
{
	for(int i = 0; i < size; i++)
	{
		arr[i].Print();
		cout << endl;
	}
}

template<class T>
void sort(T arr[size])
{

	int toSort[size] = {};

	//fill
	for(int i = 0; i < size; i++)
	{
		toSort[i] = arr[i].x + arr[i].y;
	}

	//sort
	for(int k = 0; k < size; k++)
	{
		for(int i = 1; i < size; i++)
		{
			if(toSort[i - 1] > toSort[i])
			{
				int temp = toSort[i - 1];
				toSort[i - 1] =  toSort[i];
				toSort[i] = temp;
			}
		}
	}

	//print
	for(int i = 0; i < size; i++)
	{
		cout << toSort[i] << " ";
	}

}

void printStack(stack<int> stc)
{
	while(!stc.empty())
	{
		cout << stc.top() << " ";
		stc.pop();
	}
}

void printQueue(queue<int> que)
{
	while(!que.empty())
	{
		cout << que.front() << " ";
		que.pop();
	}
}

void writeFile()
{

	fstream file;
	file.open("ss.txt", ios::out);

	if(!file.is_open())
	{
		return;
	}

	for(int y = 0; y <= sizeY; y++)
	{
		for(int x = 0; x <= sizeX; x++)
		{

			if(x == 0 || x == sizeX)
			{
				file << wall;
			}
			else if(y == 0 || y == sizeY)
			{
				file << wall;
			}
			else
			{

				char sign = ' ';

				for(int i = 0; i < size; i++)
				{
					if(x == cir[i].x && y == cir[i].y)
					{
						sign = cir[i].sing;
						break;
					}
				}

				for(int i = 0; i < size; i++)
				{
					if(x == str[i].x && y == str[i].y)
					{
						sign = str[i].sing;
						break;
					}
				}

				file << sign;

			}
		}

		file << endl;

	}

	file.close();

}

void Input()
{

	if (_kbhit()) //Any key pressed
	{

		switch (_getch())
		{
			case 's':
				writeFile();
				break;

			case 27: //Esc
				exit(1);
				break;
			
		}

	}

}

int main()
{

	pause = true;

	cout << endl << "Stars:" << endl;
	print<Star>(str);

	cout << endl << "Circles:" << endl;
	print<Circle>(cir);

	cout << endl << "Sort Stars: ";
	sort<Star>(str);

	cout << endl << "Sort Circles: ";
	sort<Circle>(cir);

	cout << endl << endl;
	Position pos1 = str[0] + str[1];
	str[0].Ispis(); cout << "+"; str[1].Ispis(); cout << "="; pos1.Ispis(); 

	cout << endl << endl;
	Position pos2 = str[4] - str[3];
	str[4].Ispis(); cout << "-"; str[3].Ispis(); cout << "="; pos2.Ispis(); 

	cout << endl << endl;
	str[1].Pair();

	cout << endl << endl;

	stack<int> count;
	for(int i = 0; i < size; i++)
	{
		count.push(str[i].x + str[i].y);
	}
	printStack(count);


	cout << endl << endl;

	queue<int> qCount;
	for(int i = 0; i < size; i++)
	{
		qCount.push(cir[i].x + cir[i].y);
	}
	printQueue(qCount);

	char p;
	cin >> p;
	if(p == 'p')
	{
		pause = false;
	}

	while(!pause)
	{
		Input();
		Render();
		Update();
		Sleep(300);
	}

}
