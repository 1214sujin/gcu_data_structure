#define _CRT_NO_SECURE_WARNINGS
#include <stdio.h>
#include <stdlib.h>
int isStackEmpty();
void push(int item[2]);
void pop(int item[2]);
void printMaze(int maze[][10]);

typedef struct stackNode { 
	int data[2];	//data�� �迭�� �����Ͽ� �������� �޴´�
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
			if (maze[i][j] == 2) printf("# ");		//2: ������ ��
			else if (maze[i][j] == 3) printf("X ");	//3: �߸��� ��
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
	//��(m) ��ġ�� ���������� �ʱ�ȭ
	int cnt, i, j;
	  
	printf("�̷�\n");
	printMaze(maze);	//ó�� �̷� ���� ���

	while (m[0] != end[0] || m[1] != end[1])
	{
		cnt = 0;

		//���̳� X�� �ƴ϶�� push
		if (maze[m[0]][m[1] - 1] != 1 && maze[m[0]][m[1] - 1] != 3) {		//���� Ž��
			temp[0] = m[0]; temp[1] = m[1] - 1;
			push(temp); cnt++;
		}
		if (maze[m[0] - 1][m[1]] != 1 && maze[m[0] - 1][m[1]] != 3) {		//�� Ž��
			temp[0] = m[0] - 1; temp[1] = m[1];
			push(temp); cnt++;
		}
		if (maze[m[0]][m[1] + 1] != 1 && maze[m[0]][m[1] + 1] != 3) {		//������ Ž��
			temp[0] = m[0]; temp[1] = m[1] + 1;
			push(temp); cnt++;
		}
		if (maze[m[0] + 1][m[1]] != 1 && maze[m[0] + 1][m[1]] != 3) {		//�Ʒ� Ž��
			temp[0] = m[0] + 1; temp[1] = m[1];
			push(temp); cnt++;
		}

		if (cnt == 1)			//���� �ϳ� ���� ���
		{
			temp[0] = m[0];		//�̵� �� ��ġ ����
			temp[1] = m[1];
			pop(m);				//maze���� ��� ���� pop
		}
		else					//���� �� �̻��� ���
		{
			temp[0] = m[0];		//�̵� �� ��ġ ����
			temp[1] = m[1];
			pop(m);				//maze���� 0�� ���� ���� ������ pop
			while (maze[m[0]][m[1]] != 0) pop(m);
		}
		//�̵��� ��ġ�� ������ ���̸� �̵� �� ��ġ�� maze���� X(3)��
		if (maze[m[0]][m[1]] == 2) maze[temp[0]][temp[1]] = 3;
		//�̵��� ��ġ�� �� ���̸� �̵� �� ��ġ�� maze���� #(2)���� �ٲ۴�
		else if (maze[m[0]][m[1]] == 0) maze[temp[0]][temp[1]] = 2;
		i = m[0] - temp[0];		//���� �̵��� ������ �˱� ����
		j = m[1] - temp[1];		//���� ��ǥ���� ���� ��ǥ�� ����
		while (maze[m[0] + i][m[1] + j] == 0)	//�̵��ϴ� ���⿡ �ִ� maze���� 0�� ��
		{
			temp[0] = m[0];		//�̵� �� ��ġ ����
			temp[1] = m[1];
			m[0] = m[0] + i;	//�̵��ϴ� �������� ��� �̵�
			m[1] = m[1] + j;
			if (maze[m[0]][m[1]] == 2) maze[temp[0]][temp[1]] = 3;
			else if (maze[m[0]][m[1]] == 0) maze[temp[0]][temp[1]] = 2;
		}
	}
	maze[m[0]][m[1]] = 2;		//end������ �����ϸ� ������ġ(end)�� maze����
	printf("Ž�� ���\n");									//#(2)���� �ٲ۴�
	printMaze(maze);			//Ž�� ��� ���

	return 0;
}