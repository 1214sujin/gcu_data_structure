#define _CRT_NO_SECURE_WARNINGS
#include <stdio.h>
#include <stdlib.h>
int isStackEmpty();
void push(int item[2]);
void pop(int item[2]);
void printMaze(int maze[][10]);

typedef struct stackNode { 
	int data[2];	//data를 배열로 선언하여 순서쌍을 받는다
	struct sn* link;
} sn;
sn* top;

int isStackEmpty() {
	if (top == NULL) return 1;
	else return 0;
}
void push(int item[2]) {
	sn* temp = (sn*)malloc(sizeof(sn));

	temp->data[0] = item[0];
	temp->data[1] = item[1];
	temp->link = top;
	top = temp;
}
void pop(int item[2]) {
	sn* temp = top;

	if (isStackEmpty()) { printf("\n\nStack is empty\n\n"); return; }
	else
	{
		item[0] = temp->data[0];
		item[1] = temp->data[1];
		top = temp->link;
		free(temp);
	}
}
void printMaze(int maze[][10]) {
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			if (maze[i][j] == 2) printf("# ");		//2: 지나온 길
			else if (maze[i][j] == 3) printf("X ");	//3: 잘못된 길
			else printf("%d ", maze[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

int main(void) {
	int maze[10][10] = { {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{0, 0, 0, 0, 1, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 1, 0, 0, 0, 0, 1},
	{1, 0, 1, 1, 1, 0, 0, 1, 0, 1},
	{1, 0, 0, 0, 1, 0, 0, 1, 0, 1},
	{1, 0, 1, 0, 1, 0, 0, 1, 0, 1},
	{1, 0, 1, 0, 1, 0, 0, 1, 0, 1},
	{1, 0, 1, 0, 1, 0, 0, 1, 0, 1},
	{1, 0, 1, 0, 0, 0, 0, 1, 0, 0},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1} };
	int m[2] = { 1, 0 }, end[2] = { 8, 9 }, temp[2];
	//쥐(m) 위치를 시작점으로 초기화
	int cnt, i, j;
	  
	printf("미로\n");
	printMaze(maze);	//처음 미로 상태 출력

	while (m[0] != end[0] || m[1] != end[1])
	{
		cnt = 0;

		//벽이나 X가 아니라면 push
		if (maze[m[0]][m[1] - 1] != 1 && maze[m[0]][m[1] - 1] != 3) {		//왼쪽 탐색
			temp[0] = m[0]; temp[1] = m[1] - 1;
			push(temp); cnt++;
		}
		if (maze[m[0] - 1][m[1]] != 1 && maze[m[0] - 1][m[1]] != 3) {		//위 탐색
			temp[0] = m[0] - 1; temp[1] = m[1];
			push(temp); cnt++;
		}
		if (maze[m[0]][m[1] + 1] != 1 && maze[m[0]][m[1] + 1] != 3) {		//오른쪽 탐색
			temp[0] = m[0]; temp[1] = m[1] + 1;
			push(temp); cnt++;
		}
		if (maze[m[0] + 1][m[1]] != 1 && maze[m[0] + 1][m[1]] != 3) {		//아래 탐색
			temp[0] = m[0] + 1; temp[1] = m[1];
			push(temp); cnt++;
		}

		if (cnt == 1)			//길이 하나 뿐일 경우
		{
			temp[0] = m[0];		//이동 전 위치 저장
			temp[1] = m[1];
			pop(m);				//maze값에 상관 없이 pop
		}
		else					//길이 둘 이상일 경우
		{
			temp[0] = m[0];		//이동 전 위치 저장
			temp[1] = m[1];
			pop(m);				//maze값이 0인 길이 나올 때까지 pop
			while (maze[m[0]][m[1]] != 0) pop(m);
		}
		//이동한 위치가 지나온 길이면 이동 전 위치의 maze값을 X(3)로
		if (maze[m[0]][m[1]] == 2) maze[temp[0]][temp[1]] = 3;
		//이동한 위치가 새 길이면 이동 전 위치의 maze값을 #(2)으로 바꾼다
		else if (maze[m[0]][m[1]] == 0) maze[temp[0]][temp[1]] = 2;
		i = m[0] - temp[0];		//현재 이동한 방향을 알기 위해
		j = m[1] - temp[1];		//현재 좌표에서 기존 좌표를 뺀다
		while (maze[m[0] + i][m[1] + j] == 0)	//이동하던 방향에 있는 maze값이 0일 때
		{
			temp[0] = m[0];		//이동 전 위치 저장
			temp[1] = m[1];
			m[0] = m[0] + i;	//이동하던 방향으로 계속 이동
			m[1] = m[1] + j;
			if (maze[m[0]][m[1]] == 2) maze[temp[0]][temp[1]] = 3;
			else if (maze[m[0]][m[1]] == 0) maze[temp[0]][temp[1]] = 2;
		}
	}
	maze[m[0]][m[1]] = 2;		//end지점에 도착하면 현재위치(end)의 maze값도
	printf("탐색 경로\n");									//#(2)으로 바꾼다
	printMaze(maze);			//탐색 결과 출력

	return 0;
}