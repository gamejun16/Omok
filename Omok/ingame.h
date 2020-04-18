#ifndef __INGAME__
#define __INGAME__

const int WHITE = 1;
const int BLACK = 2;

// HEIGHT * WIDTH ÀÇ field
const int HEIGHT = 15;
const int WIDTH = 15;

const char version[20] = "_test_version";


class Ingame {
	int sceneNumber;
public:
	Ingame() { sceneNumber = 1; }
	int getSceneNumber() { return sceneNumber; }
	void setSceneNumber(int s) { sceneNumber = s; }
	void introPlay();
	void gamePlay(int sceneNumber);
};


void gotoxy(int x, int y);

#include <Windows.h>
#include <conio.h>


#endif