#include "ingame.h"
#include "rock.h"
#include "field.h"

HANDLE hIn, hOut;
INPUT_RECORD rec;
DWORD dw;

void Ingame::introPlay() {

}



void Ingame::gamePlay(int sceneNumber) {
	gotoxy(WIDTH*2,0); cout << version;

	if (sceneNumber == 1) {
		// 입출력에 사용될 핸들을 가져옵니다.
		hIn = GetStdHandle(STD_INPUT_HANDLE);
		hOut = GetStdHandle(STD_OUTPUT_HANDLE);

		/***** 인트로 *****/

		int posX = -1, posY = -1;
		gotoxy(18, 10); cout << "오목";
		gotoxy(17, 23); cout << "게임 시작";
		gotoxy(17, 26); cout << "게임 종료";


		while (1) {
			gotoxy(0, 0); cout << rec.Event.MouseEvent.dwMousePosition.X << ", " << rec.Event.MouseEvent.dwMousePosition.Y;
			// 사용자로부터 입력을 받습니다.
			PeekConsoleInput(hIn, &rec, 1, &dw);
			// 마우스 제어가 일어났 을 경우에만 ReadConsoleInput()함수를 거침.
			if (dw > 0)
				ReadConsoleInput(hIn, &rec, 1, &dw);

			if (rec.Event.MouseEvent.dwButtonState &FROM_LEFT_1ST_BUTTON_PRESSED) { // 좌클릭을 눌렀다면
				while (true) {
					ReadConsoleInput(hIn, &rec, 1, &dw);
					if (!rec.Event.MouseEvent.dwButtonState &FROM_LEFT_1ST_BUTTON_PRESSED) // 좌클릭을 땠다면
						break; // 탈출 -> 한 차례의 클릭이 이루어 진 상태
				}
				posX = rec.Event.MouseEvent.dwMousePosition.X;
				posY = rec.Event.MouseEvent.dwMousePosition.Y;

				if ((posX >= 34 && posX <= 42) && posY == 23) {
					setSceneNumber(2); // 0: exit , 1: intro , 2: ingame
					break;
				}
				else if ((posX >= 34 && posX <= 42) && posY == 26) {
					setSceneNumber(0);
					break;
				}
			}
		}

	}

	else if (sceneNumber == 2) {
		/***** 인게임 *****/

		/** 시작 준비 **/

		Field gameField; // 게임 필드 생성
		gameField.showField();

		/** 시작 **/

		while (true) {
			gotoxy(20, 0); cout << rec.Event.MouseEvent.dwMousePosition.X << ", " << rec.Event.MouseEvent.dwMousePosition.Y;

			// 사용자로부터 입력을 받습니다.
			PeekConsoleInput(hIn, &rec, 1, &dw);
			// 마우스 제어가 일어났 을 경우에만 ReadConsoleInput()함수를 거침.
			if (dw > 0)
				ReadConsoleInput(hIn, &rec, 1, &dw);

			if (rec.Event.MouseEvent.dwButtonState &FROM_LEFT_1ST_BUTTON_PRESSED) { // 좌클릭을 눌렀다면
				while (true) {
					ReadConsoleInput(hIn, &rec, 1, &dw);
					if (!rec.Event.MouseEvent.dwButtonState &FROM_LEFT_1ST_BUTTON_PRESSED) // 좌클릭을 땠다면
						break; // 탈출 -> 한 차례의 클릭이 이루어 진 상태
				}

				if (gameField.putRock(gameField.getTurn(), rec.Event.MouseEvent.dwMousePosition.X, rec.Event.MouseEvent.dwMousePosition.Y)) { // 돌을 놓음
					gameField.turnExchange(); // putRock()의 반환값이 true 일 때(정상 작동되었을 때)만 턴 변경
				}
			}

			if (gameField.overCheck()) break; // 게임 종료 판별

		}
		gotoxy(0, HEIGHT + 1); cout << "게임 종료";
		cout << endl;
	}
}



void gotoxy(int x, int y) { //gotoxy함수 
	COORD pos = { 2 * x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
