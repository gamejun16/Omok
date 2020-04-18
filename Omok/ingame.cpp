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
		// ����¿� ���� �ڵ��� �����ɴϴ�.
		hIn = GetStdHandle(STD_INPUT_HANDLE);
		hOut = GetStdHandle(STD_OUTPUT_HANDLE);

		/***** ��Ʈ�� *****/

		int posX = -1, posY = -1;
		gotoxy(18, 10); cout << "����";
		gotoxy(17, 23); cout << "���� ����";
		gotoxy(17, 26); cout << "���� ����";


		while (1) {
			gotoxy(0, 0); cout << rec.Event.MouseEvent.dwMousePosition.X << ", " << rec.Event.MouseEvent.dwMousePosition.Y;
			// ����ڷκ��� �Է��� �޽��ϴ�.
			PeekConsoleInput(hIn, &rec, 1, &dw);
			// ���콺 ��� �Ͼ �� ��쿡�� ReadConsoleInput()�Լ��� ��ħ.
			if (dw > 0)
				ReadConsoleInput(hIn, &rec, 1, &dw);

			if (rec.Event.MouseEvent.dwButtonState &FROM_LEFT_1ST_BUTTON_PRESSED) { // ��Ŭ���� �����ٸ�
				while (true) {
					ReadConsoleInput(hIn, &rec, 1, &dw);
					if (!rec.Event.MouseEvent.dwButtonState &FROM_LEFT_1ST_BUTTON_PRESSED) // ��Ŭ���� ���ٸ�
						break; // Ż�� -> �� ������ Ŭ���� �̷�� �� ����
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
		/***** �ΰ��� *****/

		/** ���� �غ� **/

		Field gameField; // ���� �ʵ� ����
		gameField.showField();

		/** ���� **/

		while (true) {
			gotoxy(20, 0); cout << rec.Event.MouseEvent.dwMousePosition.X << ", " << rec.Event.MouseEvent.dwMousePosition.Y;

			// ����ڷκ��� �Է��� �޽��ϴ�.
			PeekConsoleInput(hIn, &rec, 1, &dw);
			// ���콺 ��� �Ͼ �� ��쿡�� ReadConsoleInput()�Լ��� ��ħ.
			if (dw > 0)
				ReadConsoleInput(hIn, &rec, 1, &dw);

			if (rec.Event.MouseEvent.dwButtonState &FROM_LEFT_1ST_BUTTON_PRESSED) { // ��Ŭ���� �����ٸ�
				while (true) {
					ReadConsoleInput(hIn, &rec, 1, &dw);
					if (!rec.Event.MouseEvent.dwButtonState &FROM_LEFT_1ST_BUTTON_PRESSED) // ��Ŭ���� ���ٸ�
						break; // Ż�� -> �� ������ Ŭ���� �̷�� �� ����
				}

				if (gameField.putRock(gameField.getTurn(), rec.Event.MouseEvent.dwMousePosition.X, rec.Event.MouseEvent.dwMousePosition.Y)) { // ���� ����
					gameField.turnExchange(); // putRock()�� ��ȯ���� true �� ��(���� �۵��Ǿ��� ��)�� �� ����
				}
			}

			if (gameField.overCheck()) break; // ���� ���� �Ǻ�

		}
		gotoxy(0, HEIGHT + 1); cout << "���� ����";
		cout << endl;
	}
}



void gotoxy(int x, int y) { //gotoxy�Լ� 
	COORD pos = { 2 * x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
