#include "field.h"

bool Field::putRock(int turn, int y, int x) {
	if ((x >= HEIGHT || x < 0) || (y >= WIDTH*2 || y < 0)) // x,y�� ������ �߸��Ǿ��ٸ�?
		return false; //false�� ��ȯ�Ѵ�

	y /= 2; // ��ǩ���� 2���� �迭 ������ ��ȯ�ϱ� ����

	if (field[x][y] != 0) // �ش� field�� ������� �ʴٸ�
		return false; // false�� ��ȯ�Ѵ�
	

	field[x][y] = turn; // ���� ���� �����̹Ƿ� ���� ���´�

	showField(); // �ʵ� ����
	return true; // ���� �۵����� �˸���
}

void Field::showField() {
	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			gotoxy(j, i);
			switch (field[i][j]) {
			case 0: // blank
				if (i == 0) { // �ʵ� �ֻ�� ����
					if (j == 0) { cout << "��"; break; }
					else if (j == WIDTH - 1) { cout << "��"; break; }
					else { cout << "��"; break; }
				}

				else if (i == HEIGHT - 1) { // �ʵ� ���ϴ� ����
					if (j == 0) { cout << "��"; break; }
					else if (j == WIDTH - 1) { cout << "��"; break; }
					else { cout << "��"; break; }
				}

				else {
					if (j == 0) { cout << "��"; break; }
					else if (j == WIDTH - 1) { cout << "��"; break; }
				}

				cout << "��";
				break;
			case WHITE: // WHITE
				cout << "��";
				break;
			case BLACK: // BLACK
				cout << "��";
				break;
			}
		}
	}
}

void Field::turnExchange() {
	if (turn == WHITE)
		turn = BLACK;
	else if (turn == BLACK)
		turn = WHITE;
}

bool Field::overCheck() {
	int target = 0; // �˻����� ���� ���� �ǹ�. WHITE = 1 , BLACK = 2
	int count = 1; // 5���� �Ǿ����� ī��Ʈ. 1���� �����ϸ�, 5�� �� �� ���� ����.
	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			if (field[i][j] != 0) { // �� �߰�. �˻� ����
				target = field[i][j]; // Ÿ�� ����

				// �� 5ĭ �˻�
				for (int z = j + 1; z < WIDTH; z++) {
					if (field[i][z] == target) {
						count++;
						if (count == 5) {
							return true; // ���� ����
						}
					}
					else { count = 1; break; }
				}
				// �� 5ĭ �˻�
				for (int z = i + 1; z < HEIGHT; z++) {
					if (field[z][j] == target) {
						count++;
						if (count == 5) {
							return true; // ���� ����
						}
					}
					else { count = 1; break; }
				}
				// �� 5ĭ �˻�
				for (int x = i + 1, z = j + 1; x < HEIGHT && z < WIDTH; x++, z++) {
					if (field[x][z] == target) {
						count++;
						if (count == 5) {
							return true; // ���� ����
						}
					}
					else { count = 1; break; }
				}
				// �� 5ĭ �˻�
				for (int x = i - 1, z = j + 1; x < HEIGHT && z < WIDTH; x--, z++) {
					if (field[x][z] == target) {
						count++;
						if (count == 5) {
							return true; // ���� ����
						}
					}
					else { count = 1; break; }
				}
			}
		}
	}
	
	return false; // ���� ������ ������ ����
}