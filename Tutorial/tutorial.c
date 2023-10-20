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
		// 3초마다 인사
		if (tick % 3000 == 0) {
			printf("안녕하세요\n");
		}
		// 1초마다 인사
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
		if (_kbhit()) { // 키 입력은 loop 돌 때마다 확인
			int key = _getch();
			// 키 입력을 받는 함수(엔터 키가 입력될 때까지 기다리지 않음)
			// blocking function이므로 _kbhit()가 참일 때만 사용
			if(key == 224) {
				// 방향키는 다른 키(‘a’, b’, ‘1’, ‘!’, …)와 달리 2byte로 입력 된다.
				// MSB(224) + LSB(72/75/77/80)
				key = _getch();
				switch (key) {
				case 72: printf(" ↑"); break;
				case 75: printf(" ←"); break;
				case 77: printf(" →"); break;
				case 80: printf(" ↓"); break;
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
	COORD pos = { col, row }; // 행, 열 반대로 전달
	SetConsoleCursorPosition(
		GetStdHandle(STD_OUTPUT_HANDLE),
		pos
	);
}

int main(void) {
	// 4방향의 변위(Δx, Δy)
	int dx[4] = { -1, 1, 0, 0 };
	int dy[4] = { 0, 0, -1, 1 };
	int x = 1, y = 1;
	int dir = 3; // 방향(direction). 처음에는 오른쪽
	while (1) {
		// 'w', 's', 'a', 'd': 이동, 'q': 종료
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

		// 0.1초마다 '*' 이동
		if (tick % 100 == 0) {
			// nx, ny: 다음 위치
			int nx = x + dx[dir];
			int ny = y + dy[dir];
			// (nx, ny)로 이동할 수 없으면 pass
			if (nx > 0 && nx < 9 && ny > 0 && ny < 19) {
				gotoxy(x, y); // 지우고
				printf(" ");
				x = nx; // 이동
				y = ny;
				gotoxy(x, y); // 새 위치에 출력
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
	// 맵 초기화
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

	// 4방향의 변위(Δx, Δy)
	int dx[4] = { -1, 1, 0, 0 };
	int dy[4] = { 0, 0, -1, 1 };
	int x = 1, y = 1;
	int dir = 3; // 방향(direction). 처음에는 오른쪽
	while (1) {
		// 'w', 's', 'a', 'd': 이동, 'q': 종료
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

		// 0.1초마다 '*' 이동
		if (tick % 100 == 0) {
			// nx, ny: 다음 위치
			int nx = x + dx[dir];
			int ny = y + dy[dir];
			// (nx, ny)로 이동할 수 없으면 pass
			if (nx > 0 && nx < 9 && ny > 0 && ny < 19) {
				map[x][y] = ' '; // 지우고
				x = nx; // 이동
				y = ny;
				map[x][y] = '*'; // 새 위치에 출력
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
	COORD pos = { col, row }; // 행, 열 반대로 전달
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
	printf("문자열 길이: %d\n", length);

	for (int i = 0; i < length; i++) {
		printf("%c", message[i]);
	}
	printf("\n");

	for (int i = 0; i < 20; i++) {
		printf("%d\n", message[i]);
	}

	int len = strlen(message);
	printf("길이 : %d\n", len);
}

int main(void) {
	char s[] = "가a !";
	printf("%s\n", s);
	printf("start: %p\n", &s);
	int size = sizeof(s) / sizeof(char);
	printf("size: %d\n", size);
	printf("end: %p\n", &s[size - 1]);
	test(s);

	return 0; // 임시 작동 중지

	// 맵 초기화
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

	// 4방향의 변위(Δx, Δy)
	int dx[4] = { -1, 1, 0, 0 };
	int dy[4] = { 0, 0, -1, 1 };
	int x = 1, y = 1;
	int dir = 3; // 방향(direction). 처음에는 오른쪽
	while (1) {
		// 'w', 's', 'a', 'd': 이동, 'q': 종료
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

		// 0.1초마다 '*' 이동
		if (tick % 100 == 0) {
			// nx, ny: 다음 위치
			int nx = x + dx[dir];
			int ny = y + dy[dir];
			// (nx, ny)로 이동할 수 없으면 pass
			if (nx > 0 && nx < 9 && ny > 0 && ny < 19) {
				map[x][y] = ' '; // 지우고
				x = nx; // 이동
				y = ny;
				map[x][y] = '*'; // 새 위치에 출력
			}
		}
		draw();
		Sleep(10);
		tick += 10;
	}
	return 0;
}
