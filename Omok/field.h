#ifndef __FIELD__
#define __FIELD__

#include "ingame.h"


class Field {
private:
	int field[HEIGHT][WIDTH]; // 2차원배열로써 필드의 좌푯값을 저장
	int turn; // 턴
	int winner; // 승자

public:

	Field() { // 생성자
		for (int i = 0; i < HEIGHT; i++) {
			for (int j = 0; j < WIDTH; j++)
				field[i][j] = 0; // field 배열을 모두 0으로 초기화
		}
		turn = WHITE; // 시작 턴 WHITE
	} 
	~Field() {} // 소멸자

	bool putRock(int turn, int x, int y); // 정상 작동시 true, 오류 발생시 false 반환
	void showField(); // 필드 출력
	int getTurn() { return turn; }
	void turnExchange();
	bool overCheck(); // 게임 종료 여부 체크. 종료시 true 반환
	int getWinner() { return winner; }
};

#include <iostream>
using namespace std;

#endif