#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
typedef struct Sparse_Matrix sm;
int smAdd(sm a[], sm b[]);
int readSm(FILE* fp, sm arr[]);
int printSm(sm arr[]);

struct Sparse_Matrix {
	int row;
	int col;
	int value;
}C[13] = { 0 };

int smAdd(sm a[], sm b[]) {
	int k = 1, i = 1, j = 1;
	C[0].row = a[0].row;
	C[0].col = a[0].col;
	while(i <= a[0].value || j <= b[0].value)
	{
		if (i > a[0].value)
		{
			C[k].row = b[j].row;
			C[k].col = b[j].col;
			C[k].value = b[j].value;
			j++;
		}
		else if (j > b[0].value)
		{
			C[k].row = a[i].row;
			C[k].col = a[i].col;
			C[k].value = a[i].value;
			i++;
		}
		else if (a[i].row == b[j].row && a[i].col == b[j].col)
		{
			C[k].row = a[i].row;
			C[k].col = a[i].col;
			C[k].value = a[i].value + b[j].value;
			i++; j++;
		}
		else if (a[i].row < b[j].row || a[i].row == b[j].row && a[i].col < b[j].col)
		{ 
			C[k].row = a[i].row;
			C[k].col = a[i].col;
			C[k].value = a[i].value;
			i++;
		}
		else if (a[i].row > b[j].row || a[i].row == b[j].row && a[i].col > b[j].col)
		{
			C[k].row = b[j].row;
			C[k].col = b[j].col;
			C[k].value = b[j].value;
			j++;
		}
		else k--;
		k++;
	}
	return 0;
}

int readSm(FILE *fp, sm arr[]) {
	char f = fgetc(fp);
	while (f != EOF)
	{
		if (f == ' ')
		{
			arr[0].col++;
		}
		else if (f == '\n')
		{
			arr[0].row++;
			arr[0].col = 0;
		}
		else if (f == '0');
		else
		{
			arr[0].value++;
			arr[arr[0].value].row = arr[0].row;
			arr[arr[0].value].col = arr[0].col;
			arr[arr[0].value].value = f - '0';
		}
		f = fgetc(fp);
	}
	arr[0].row++; arr[0].col++;
	return 0;
}

int printSm(sm arr[]) {
	int i = arr[0].row, j = arr[0].col, m = 1;
	for (int k = 0; k < i; k++)
	{
		for (int l = 0; l < j; l++)
		{
			if (arr[m].row == k && arr[m].col == l)
			{
				printf("%2d", arr[m].value);
				m++;
			}
			else printf(" 0");
			printf(" ");
		}
		printf("\n");
	}
	return 0;
}

int main() {
	sm A[13] = { 0 }, B[13] = { 0 };
	FILE* fp = fopen("C:\\test\\A.txt", "r");
	readSm(fp, A); fclose(fp);
	fp = fopen("C:\\test\\B.txt", "r");
	readSm(fp, B); fclose(fp);

	smAdd(A, B);
	printf(" A\n"); printSm(A);
	printf("\n B\n"); printSm(B);
	printf("\n A + B\n"); printSm(C);

	return 0;
}