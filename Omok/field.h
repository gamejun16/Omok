#ifndef __FIELD__
#define __FIELD__

#include "ingame.h"


class Field {
private:
	int field[HEIGHT][WIDTH]; // 2�����迭�ν� �ʵ��� ��ǩ���� ����
	int turn; // ��
	int winner; // ����

public:

	Field() { // ������
		for (int i = 0; i < HEIGHT; i++) {
			for (int j = 0; j < WIDTH; j++)
				field[i][j] = 0; // field �迭�� ��� 0���� �ʱ�ȭ
		}
		turn = WHITE; // ���� �� WHITE
	} 
	~Field() {} // �Ҹ���

	bool putRock(int turn, int x, int y); // ���� �۵��� true, ���� �߻��� false ��ȯ
	void showField(); // �ʵ� ���
	int getTurn() { return turn; }
	void turnExchange();
	bool overCheck(); // ���� ���� ���� üũ. ����� true ��ȯ
	int getWinner() { return winner; }
};

#include <iostream>
using namespace std;

#endif