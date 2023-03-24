#include "pch.h"
#include <conio.h>
#include <stdio.h>
#include <windows.h>

const int screenW = 80, screenH = 25;

int main()
{
    SetConsoleTitleA("Simple Console Game");

    //Set Physical Console Window Size
    HANDLE hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SMALL_RECT rectWindow = {0, 0, screenW - 1, screenH - 1};
    SetConsoleWindowInfo(hConsole, TRUE, &rectWindow);
    //Set the size of the screen buffer
    COORD coord = {screenW, screenH};
    SetConsoleScreenBufferSize(hConsole, coord);

    char screen[screenH][screenW + 1]; //we'll paint everything in this matrix, then flush it onto the creen

	int snakePos_Row = 10;
	int snakePos_Col = 10;
	int snakeMove_DRow = 0;
	int snakeMove_DCol = +1; //start moving to the right

	while (1) //we'll stop it with a break statement
	{
		if (_kbhit()) //check user's input
		{
			unsigned char ch = _getch();
			//printf("%d ", ch);
			if (ch == 27) //ASCII code for the Esc key
				break; //end the game
			if (ch == 224) //it's a key that generates two bytes when being pressed, the first one being 224
			{
				ch = _getch();
				if (ch == 75) //the left arrow key
				{
					snakeMove_DRow = 0;
					snakeMove_DCol = -1;
				}
				else
				if (ch == 77) //the right arrow key
				{
					snakeMove_DRow = 0;
					snakeMove_DCol = +1;
				}
				else
				if (ch == 72) //the up arrow key
				{
					snakeMove_DRow = -1;
					snakeMove_DCol = 0;
				}
				else
				if (ch == 80) //the down arrow key
				{
					snakeMove_DRow = +1;
					snakeMove_DCol = 0;
				}
			}
			else
			if (ch == 0) //it's a key that generates two bytes when being pressed, the first one being 0
			{
				ch = _getch();
			}
		}

		//do animation
		snakePos_Row += snakeMove_DRow;
		snakePos_Col += snakeMove_DCol;

		//check against the screen boundaries, and bounce
		if (snakePos_Row == -1)
		{
			snakePos_Row = 1;
			snakeMove_DRow = +1;
		}
		else
		if (snakePos_Row == screenH)
		{
			snakePos_Row = screenH - 2;
			snakeMove_DRow = -1;
		}
		else
		if (snakePos_Col == -1)
		{
			snakePos_Col = 1;
			snakeMove_DCol = +1;
		}
		else
		if (snakePos_Col == screenW)
		{
			snakePos_Col = screenW - 2;
			snakeMove_DCol = -1;
		}

		//paint the screen in a matrix
		memset(screen, 32, sizeof(screen)); //clear it, with spaces
		//paint the snake
		screen[snakePos_Row][snakePos_Col] = '*';
		//set the string terminator for each row as it will be flushed onto the real screen: each screen row comming from a null terminated string
		for (int row = 0; row < screenH; row++)
			screen[row][screenW] = 0;

		system("cls"); //clear the (real) screen

		//flush the screen matrix onto the real screen
		for (int row = 0; row < screenH; row++)
		{
			if (row == screenH - 1)
				screen[row][screenW - 1] = 0; //avoid scrolling one row up when the screen is full
			printf("%s", screen[row]);
		}

		Sleep(50);
	}

	return 0;
}
