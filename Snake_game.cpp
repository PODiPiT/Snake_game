#include <iostream>
#include <chrono>
#include <thread> 
#include <conio.h>
using namespace std;

bool gameOver;

const int width = 30; // that's a game fiels
const int height = 20;
int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100];  //these two arrays are for tail of the snake
int nTail;  //number of elements in the tail
enum eDirection{STOP=0, LEFT, RIGHT, UP, DOWN};
eDirection dir;

void Setup() //we initialize start positions for fruit and head of the snake
{
	gameOver = false;
	dir = STOP;
	x = width / 2;
	y = height / 2;
	fruitX = rand() % width;
	fruitY = rand() % height;
	score = 0;
}

void Draw()
{
	system("cls");
	for (int i = 0; i < width+2; i++)  //there is a top line of the field
	{
		cout << "#";
	}
	cout << endl;
	
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (j == 0)  //there is a left line of the field
				cout << "#";
			
			if (i == y && j == x)  //we show a head of the snake
				cout << "O";

			else if (i == fruitY && j == fruitX)  //we show a fruit
				cout << "@";

			else
			{
				bool print = false; 
				for (int k = 0; k < nTail; k++)
				{

					if (tailX[k] == j && tailY[k] == i)
					{
						cout << "o";
						print = true;
					}
				}
				if (!print)
					cout << " ";
			}

			if (j==width-1)  //there is a right line of the field
				cout << "#";
		}
		cout << endl;
	}

	for (int i = 0; i < width+2; i++)  //there is a bottom line of the field
	{
		cout << "#";
	}
	cout << endl;
	cout << "Score:" << score << endl;  //we show our score
}

void Input()
{
	if (_kbhit())  //_kbhit - returns positive number if a key on keybord is pressed, if nothing is pressed it will return zero
	{
		switch (_getch())  //_getch - returns ASCII value of a character that was pressed
		{
		case 'a':  //we asign keys W A D S for controlling direction of snake
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
		case 'x':  //key x will be for exiting game
			gameOver = true;
			break;

		}
	}
}

void Logic()
{
	int prevX = tailX[0];  //we need to remember where snake's head were
	int prevY = tailY[0];
	int prev2X, prev2Y;
	tailX[0] = x;
	tailY[0] = y;

	for (int i = 1; i < nTail; i++)
	{
		prev2X = tailX[i];
		prev2Y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	} 
	switch (dir)  //we move our snake's head
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
	//if (x > width || x < 0|| y > height || y < 0)  //if snake meet the boundary game is over
	//	gameOver = true;

	if (x >= width) x = 0; else if (x < 0) x = width - 1; // these two lines will allow us to go through boundaries
	if (y >= height) y = 0; else if (y < 0) y = height - 1;

	for (int i = 0; i < nTail; i++)
		if (tailX[i] == x && tailY[i] == y)
			gameOver = true;

	if (x == fruitX && y == fruitY)  //if snake meet the fruit we increase our score and put fruit to another position
	{
		score += 10;
		fruitX = rand() % width;
		fruitY = rand() % width;
		nTail++;
	}
}

int main()
{
	Setup();
	while (!gameOver)
	{
		Draw();
		Input();
		Logic();
		this_thread::sleep_for(chrono::milliseconds(100));
	}
	
	return 0;
}