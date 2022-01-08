#include <iostream>
#include <conio.h>
#include <windows.h>

using namespace std;

#define width 50
#define height 25
#define esc 27

// Initialize Variables
bool gameRunning;

// User Variables
int x, y, speed = 1;
int tailX[100], tailY[100], tailLength;

// Tail Coordinates
int fposX, fposY, sposX, sposY;

// Target Variables
int targetX, targetY;

// Game Variables
int score;

enum directions { STOP = 0, UP, DOWN, LEFT, RIGHT };
directions dir;

void SetupUser() {
	x = rand() % width;
	y = rand() % height;
}

void SetupTarget() {
	targetX = rand() % width;
	targetY = rand() % height;
}

void SetupCoords() {
	SetupUser();
	SetupTarget();
}

void GameSetup() {
	gameRunning = true;
	dir = STOP;
	SetupCoords();

	// Trigger when target and player are on top of each other
	while (x == targetX && y == targetY) SetupCoords();
	score = 0;
}

void TopBottom() {
	for (int i = 0; i < width; i++) {
		cout << "#";
	}
	cout << endl;
}

void Body() {
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (j == 0 || j == width - 1) cout << '#';
			else if (i == y && j == x) cout << "@";
			else if (i == targetY && j == targetX) cout << "O";
			else {
				bool tail = false;
				for (int k = 0; k < tailLength; k++) {
					if (j == tailX[k] && i == tailY[k]) {
						cout << "@";
						tail = true;
					}
				}
				if (!tail) {
					cout << " ";
				}
			}
		}
		cout << endl;
	}
}

void GameWindow() {
	system("cls");
	TopBottom();
	Body();
	TopBottom();
	cout << "Score: " << score;
}

void GameInput() {
	if (_kbhit()) {
		switch (_getch()) {
			case 'w':
				if (dir != DOWN) dir = UP;
				break;
			case 'a':
				if (dir != RIGHT) dir = LEFT;
				break;
			case 's':
				if (dir != UP) dir = DOWN;
				break;
			case 'd':
				if (dir != LEFT) dir = RIGHT;
				break;
			case esc:
				gameRunning = false;
				break;
		}
	}
}

void Game() {

	//Tail 
	fposX = tailX[0];
	fposY = tailY[0];
	tailX[0] = x;
	tailY[0] = y;

	for (int i = 1; i < tailLength; i++) {
		sposX = tailX[i];
		sposY = tailY[i];
		tailX[i] = fposX;
		tailY[i] = fposY;
		fposX = sposX;
		fposY = sposY;
	}

	// Directions
	switch (dir) {
	case LEFT:
		x -= speed;
		break;
	case RIGHT:
		x += speed;
		break;
	case UP:
		y -= speed;
		break;
	case DOWN:
		y += speed;
		break;
	}

	// Snake hits the border
	if(( x <= 0 || x >= width - 1) || (y < 0 || y >= height)) gameRunning = false;

	// Snake hits the tail
	for (int i = 0; i < tailLength; i++) {
		if (x == tailX[i] && y == tailY[i]) {
			gameRunning = false;
		}
	}

	// Snake hits the target
	if (x == targetX && y == targetY) {
		SetupTarget();
		score++;
		tailLength++;
	}
}

int main() {
	GameSetup();
	while (gameRunning) {
		GameWindow();
		GameInput();
		Game();
		Sleep(30);
	}
}