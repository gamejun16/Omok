#include "field.h"

bool Field::putRock(int turn, int y, int x) {
	if ((x >= HEIGHT || x < 0) || (y >= WIDTH*2 || y < 0)) // x,y의 범위가 잘못되었다면?
		return false; //false를 반환한다

	y /= 2; // 좌푯값을 2차원 배열 값으로 변환하기 위함

	if (field[x][y] != 0) // 해당 field가 비어있지 않다면
		return false; // false를 반환한다
	

	field[x][y] = turn; // 알이 없는 상태이므로 알을 놓는다

	showField(); // 필드 갱신
	return true; // 정상 작동됨을 알린다
}

void Field::showField() {
	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			gotoxy(j, i);
			switch (field[i][j]) {
			case 0: // blank
				if (i == 0) { // 필드 최상단 라인
					if (j == 0) { cout << "┏"; break; }
					else if (j == WIDTH - 1) { cout << "┓"; break; }
					else { cout << "┳"; break; }
				}

				else if (i == HEIGHT - 1) { // 필드 최하단 라인
					if (j == 0) { cout << "┗"; break; }
					else if (j == WIDTH - 1) { cout << "┛"; break; }
					else { cout << "┻"; break; }
				}

				else {
					if (j == 0) { cout << "┣"; break; }
					else if (j == WIDTH - 1) { cout << "┫"; break; }
				}

				cout << "╋";
				break;
			case WHITE: // WHITE
				cout << "●";
				break;
			case BLACK: // BLACK
				cout << "○";
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
	int target = 0; // 검사중인 알의 색을 의미. WHITE = 1 , BLACK = 2
	int count = 1; // 5목이 되었음을 카운트. 1부터 시작하며, 5가 될 시 게임 종료.
	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			if (field[i][j] != 0) { // 알 발견. 검사 시작
				target = field[i][j]; // 타겟 설정

				// → 5칸 검사
				for (int z = j + 1; z < WIDTH; z++) {
					if (field[i][z] == target) {
						count++;
						if (count == 5) {
							return true; // 게임 종료
						}
					}
					else { count = 1; break; }
				}
				// ↓ 5칸 검사
				for (int z = i + 1; z < HEIGHT; z++) {
					if (field[z][j] == target) {
						count++;
						if (count == 5) {
							return true; // 게임 종료
						}
					}
					else { count = 1; break; }
				}
				// ↘ 5칸 검사
				for (int x = i + 1, z = j + 1; x < HEIGHT && z < WIDTH; x++, z++) {
					if (field[x][z] == target) {
						count++;
						if (count == 5) {
							return true; // 게임 종료
						}
					}
					else { count = 1; break; }
				}
				// ↗ 5칸 검사
				for (int x = i - 1, z = j + 1; x < HEIGHT && z < WIDTH; x--, z++) {
					if (field[x][z] == target) {
						count++;
						if (count == 5) {
							return true; // 게임 종료
						}
					}
					else { count = 1; break; }
				}
			}
		}
	}
	
	return false; // 아직 게임이 끝나지 않음
}