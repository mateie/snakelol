#include <iostream>
#include <conio.h>
using namespace std;

#define width 50
#define height 25

// Initialize Variables
bool gameRunning;

// User Variables
int x, y, speed = 1;

// Target Variables
int targetX, targetY;

// Game Variables
int score;

enum directions { STOP = 0, UP, DOWN, LEFT, RIGHT };
directions dir;

void SetupCoords() {
	x = rand() % width;
	y = rand() % height;
	targetX = rand() % width;
	targetY = rand() % height;
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
			else if (i == y && j == x) cout << "*";
			else cout << ' ';
		}
		cout << endl;
	}
}

void GameWindow() {
	system("cls");
	TopBottom();
	Body();
	TopBottom();
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
			case '0':
				gameRunning = false;
				break;
		}
	}
}

void Game() {
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

	if(( x <= 0 || x >= width - 1) || (y < 0 || y >= height)) gameRunning = false;
}

int main() {
	GameSetup();
	while (gameRunning) {
		GameWindow();
		GameInput();
		Game();
	}
}