#include <iostream>
#include <conio.h>
#include <windows.h>

using namespace std;

bool gameOver;
const int width = 20;
const int height = 10;
int x, y, frX, frY, score;
int tailX[100], tailY[100];
enum eDir { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDir dir;
int command;

void Setup() {
	gameOver = false;
	dir = STOP;
	x = width / 2 - 1;
	y = height / 2 - 1;
	frX = rand() % width;
	frY = rand() % height;
	score = 0;
}

void Menu() {
		cout << "1)Start the game\n" "2)Quit the game\n" "Enter action:";
		cin >> command;
		if (command == 1) {
			Setup();
		}
		else if (command == 2) {
			gameOver = true;
		}
		else {
			system("cls");
			cout << "Not valid command\n" << endl;
			Menu();
	}
}

void Map() {
	system("cls");
	for (int i = 0; i < width + 1; i++)
		cout << "#";

	cout << endl;

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (j == 0 || j == width - 1)
				cout << "#";
			if (i == y && j == x) {
				cout << "O";
			}
			else if (i == frY && j == frX) {
				cout << "*";
			}
			else {
				bool print = false;
				for (int k = 0; k < score; k++) {
					if (tailX[k] == j && tailY[k] == i) {
						print = true;
						cout << "o";
					}
				}
				if (!print)
					cout << ' ';
			}
		}
		cout << endl;
	}
	for (int i = 0; i < width + 1; i++) {
		cout << "#";
	}
	cout << "\nYour score:" << score << endl;
}

void Input() {
	if (_kbhit()) {
		switch(_getch()){
		case 'a':
			if (dir != RIGHT)
				dir = LEFT;
			break;
		case 'd':
			if (dir != LEFT)
			dir = RIGHT;
			break;
		case 'w':
			if (dir != DOWN)
			dir = UP;
			break;
		case 's':
			if (dir != UP)
			dir = DOWN;
			break;
		}
	}
}

void Logic() {
	int PrX = tailX[0];
	int PrY = tailY[0];
	int Pr2X, Pr2Y;
	tailX[0] = x;
	tailY[0] = y;
	for (int i = 1; i < score; i++) {
		Pr2X = tailX[i];
		Pr2Y = tailY[i];
		tailX[i] = PrX;
		tailY[i] = PrY;
		PrX = Pr2X;
		PrY = Pr2Y;
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
	if (x > width - 2 || x < 0  || y > height - 1 || y < 0)
		gameOver = true;
	for (int i = 0; i < score; i++) {
		if (tailX[i] == x && tailY[i] == y)
			gameOver = true;
	}

	if (x == frX && y == frY) {
		score++;
		frX = rand() % width;
		frY = rand() % height;
	}
}

int main()
{
	Menu();
	while (!gameOver) {
		Map();
		Input();
		Logic();
		Sleep(220);
		if (gameOver == true) {
			system("cls");
			cout << "Game over!\n" << endl;
			Menu();
		}
	}
}