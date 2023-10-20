#include <stdio.h>
#include <Windows.h>
#include <conio.h>

/*
int main(void) {
	int y = 1;
	while (1) {
		printf("%d\n", y);
		y++;
		Sleep(1000); // ms
	}
	return 0;
}
*/

/*
int tick = 0;
int main(void) {
	int y = 1;
	while (1) {
		// 3�ʸ��� �λ�
		if (tick % 3000 == 0) {
			printf("�ȳ��ϼ���\n");
		}
		// 1�ʸ��� �λ�
		if (tick % 1000 == 0) {
			printf("sec: %d\n", y);
			y++;
		}
		Sleep(10);
		tick += 10;
	}
	return 0;
}
*/

/*
int main(void) {
	while (1) {
		printf("%d", _kbhit());
		if (_kbhit()) { // Ű �Է��� loop �� ������ Ȯ��
			int key = _getch();
			// Ű �Է��� �޴� �Լ�(���� Ű�� �Էµ� ������ ��ٸ��� ����)
			// blocking function�̹Ƿ� _kbhit()�� ���� ���� ���
			if(key == 224) {
				// ����Ű�� �ٸ� Ű(��a��, b��, ��1��, ��!��, ��)�� �޸� 2byte�� �Է� �ȴ�.
				// MSB(224) + LSB(72/75/77/80)
				key = _getch();
				switch (key) {
				case 72: printf(" ��"); break;
				case 75: printf(" ��"); break;
				case 77: printf(" ��"); break;
				case 80: printf(" ��"); break;
				}
			}
			else {
				printf(" %c", key);
			}
		}
		printf("\n");
		Sleep(100);
	}
	return 0;
}
*/

/*
void gotoxy(int row, int col);

int tick = 0;

void gotoxy(int row, int col) {
	COORD pos = { col, row }; // ��, �� �ݴ�� ����
	SetConsoleCursorPosition(
		GetStdHandle(STD_OUTPUT_HANDLE),
		pos
	);
}

int main(void) {
	// 4������ ����(��x, ��y)
	int dx[4] = { -1, 1, 0, 0 };
	int dy[4] = { 0, 0, -1, 1 };
	int x = 1, y = 1;
	int dir = 3; // ����(direction). ó������ ������
	while (1) {
		// 'w', 's', 'a', 'd': �̵�, 'q': ����
		if (_kbhit()) {
			int key = _getch();
			switch (key) {
			case 'w': dir = 0; break;
			case 's': dir = 1; break;
			case 'a': dir = 2; break;
			case 'd': dir = 3; break;
			case 'q': return 0;
			}
		}

		// 0.1�ʸ��� '*' �̵�
		if (tick % 100 == 0) {
			// nx, ny: ���� ��ġ
			int nx = x + dx[dir];
			int ny = y + dy[dir];
			// (nx, ny)�� �̵��� �� ������ pass
			if (nx > 0 && nx < 9 && ny > 0 && ny < 19) {
				gotoxy(x, y); // �����
				printf(" ");
				x = nx; // �̵�
				y = ny;
				gotoxy(x, y); // �� ��ġ�� ���
				printf("*");
			}
		}
		Sleep(10);
		tick += 10;
	}
	return 0;
}
*/

/*
void draw(void);

int tick = 0;
char map[10][20];

void draw(void) {
	system("cls");
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 20; j++) {
			printf("%c", map[i][j]);
		}
		printf("\n");
	}
}

int main(void) {
	// �� �ʱ�ȭ
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 20; j++) {
			if (i == 0 || i == 9 || j == 0 || j == 19) {
				map[i][j] = '#';
			}
			else {
				map[i][j] = ' ';
			}
		}
	}
	map[1][1] = '*';

	// 4������ ����(��x, ��y)
	int dx[4] = { -1, 1, 0, 0 };
	int dy[4] = { 0, 0, -1, 1 };
	int x = 1, y = 1;
	int dir = 3; // ����(direction). ó������ ������
	while (1) {
		// 'w', 's', 'a', 'd': �̵�, 'q': ����
		if (_kbhit()) {
			int key = _getch();
			switch (key) {
			case 'w': dir = 0; break;
			case 's': dir = 1; break;
			case 'a': dir = 2; break;
			case 'd': dir = 3; break;
			case 'q': return 0;
			}
		}

		// 0.1�ʸ��� '*' �̵�
		if (tick % 100 == 0) {
			// nx, ny: ���� ��ġ
			int nx = x + dx[dir];
			int ny = y + dy[dir];
			// (nx, ny)�� �̵��� �� ������ pass
			if (nx > 0 && nx < 9 && ny > 0 && ny < 19) {
				map[x][y] = ' '; // �����
				x = nx; // �̵�
				y = ny;
				map[x][y] = '*'; // �� ��ġ�� ���
			}
		}
		draw();
		Sleep(10);
		tick += 10;
	}
	return 0;
}
*/


void gotoxy(int row, int col);
void draw(void);

int tick = 0;
char map[10][20], front[10][20];

void gotoxy(int row, int col) {
	COORD pos = { col, row }; // ��, �� �ݴ�� ����
	SetConsoleCursorPosition(
		GetStdHandle(STD_OUTPUT_HANDLE),
		pos
	);
}

void draw(void) {
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 20; j++) {
			if (front[i][j] != map[i][j]) {
				front[i][j] = map[i][j];
				gotoxy(i, j);
				printf("%c", front[i][j]);
			}
		}
	}
}

void test(char message[]) {

	int length = 0;
	while (1) {
		if (message[length] == 0) {
			break;
		}
		length++;
	}
	printf("���ڿ� ����: %d\n", length);

	for (int i = 0; i < length; i++) {
		printf("%c", message[i]);
	}
	printf("\n");

	for (int i = 0; i < 20; i++) {
		printf("%d\n", message[i]);
	}

	int len = strlen(message);
	printf("���� : %d\n", len);
}

int main(void) {
	char s[] = "��a !";
	printf("%s\n", s);
	printf("start: %p\n", &s);
	int size = sizeof(s) / sizeof(char);
	printf("size: %d\n", size);
	printf("end: %p\n", &s[size - 1]);
	test(s);

	return 0; // �ӽ� �۵� ����

	// �� �ʱ�ȭ
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 20; j++) {
			if (i == 0 || i == 9 || j == 0 || j == 19) {
				map[i][j] = '#';
			}
			else {
				map[i][j] = ' ';
			}
		}
	}
	map[1][1] = '*';

	// 4������ ����(��x, ��y)
	int dx[4] = { -1, 1, 0, 0 };
	int dy[4] = { 0, 0, -1, 1 };
	int x = 1, y = 1;
	int dir = 3; // ����(direction). ó������ ������
	while (1) {
		// 'w', 's', 'a', 'd': �̵�, 'q': ����
		if (_kbhit()) {
			int key = _getch();
			switch (key) {
			case 'w': dir = 0; break;
			case 's': dir = 1; break;
			case 'a': dir = 2; break;
			case 'd': dir = 3; break;
			case 'q': return 0;
			}
		}

		// 0.1�ʸ��� '*' �̵�
		if (tick % 100 == 0) {
			// nx, ny: ���� ��ġ
			int nx = x + dx[dir];
			int ny = y + dy[dir];
			// (nx, ny)�� �̵��� �� ������ pass
			if (nx > 0 && nx < 9 && ny > 0 && ny < 19) {
				map[x][y] = ' '; // �����
				x = nx; // �̵�
				y = ny;
				map[x][y] = '*'; // �� ��ġ�� ���
			}
		}
		draw();
		Sleep(10);
		tick += 10;
	}
	return 0;
}
