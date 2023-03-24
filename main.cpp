#include "pch.h"
#include <conio.h>
#include <stdio.h>
#include <windows.h>

#define SCREEN_ROWS_NUM 25
#define SCREEN_COLS_NUM 80

int main()
{
    SetConsoleTitle(L"Simple Console Game");

    //Set Physical Console Window Size
    HANDLE hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SMALL_RECT rectWindow = {0, 0, SCREEN_COLS_NUM - 1, SCREEN_ROWS_NUM - 1};
    SetConsoleWindowInfo(hConsole, TRUE, &rectWindow);
    //Set the size of the screen buffer
    COORD coord = {SCREEN_COLS_NUM, SCREEN_ROWS_NUM};
    SetConsoleScreenBufferSize(hConsole, coord);

    char screen[SCREEN_ROWS_NUM][SCREEN_COLS_NUM + 1]; //we'll paint everything in this matrix, then flush it onto the creen

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
		if (snakePos_Row == SCREEN_ROWS_NUM)
		{
			snakePos_Row = SCREEN_ROWS_NUM - 2;
			snakeMove_DRow = -1;
		}
		else
		if (snakePos_Col == -1)
		{
			snakePos_Col = 1;
			snakeMove_DCol = +1;
		}
		else
		if (snakePos_Col == SCREEN_COLS_NUM)
		{
			snakePos_Col = SCREEN_COLS_NUM - 2;
			snakeMove_DCol = -1;
		}

		//paint the screen in a matrix
		memset(screen, 32, sizeof(screen)); //clear it, with spaces
		//paint the snake
		screen[snakePos_Row][snakePos_Col] = '*';
		//set the string terminator for each row as it will be flushed onto the real screen: each screen row comming from a null terminated string
		for (int row = 0; row < SCREEN_ROWS_NUM; row++)
			screen[row][SCREEN_COLS_NUM] = 0;

		system("cls"); //clear the (real) screen

		//flush the screen matrix onto the real screen
		for (int row = 0; row < SCREEN_ROWS_NUM; row++)
		{
			if (row == SCREEN_ROWS_NUM - 1)
				screen[row][SCREEN_COLS_NUM - 1] = 0; //avoid scrolling one row up when the screen is full
			printf("%s", screen[row]);
		}

		Sleep(50);
	}

	return 0;
}
