#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
typedef struct addr_bk ab;	// �ּҷ� ����ü�� ����
int show(ab book[], ab* ptr);	// �ּҷ��� �����ִ� �Լ�
int add(ab book[], ab* ptr);	// �ּҷϿ� �ּҸ� �߰��ϴ� �Լ�
int find(ab book[], ab* ptr);	// �ּҸ� Ž���ϴ� �Լ�
int del(ab book[], ab* ptr);	// �ּҸ� ����� �Լ�

struct addr_bk {
	char name[10], call[20], addr[50], bday[10];	// �̸�, ��ȭ��ȣ, �ּ�, ����
};

int show(ab book[], ab* ptr) {
	printf("\n00 | �̸�\t��ȭ��ȣ\t�ּ�\t\t����\n");
	ab* p_now = book;	// ptr�� ���Ͽ� for���� ������Ű�� ���� ������ ����
	for (int i = 0; p_now + i < ptr; i++) {
		printf("%02d | %s\t%s\t%s\t%s\n", i + 1, book[i].name, book[i].call, book[i].addr, book[i].bday);
	}
	printf("\n");
	return 1;			// ����� ������ ������ �ʾ����Ƿ� 1 ��ȯ
}

int add(ab book[], ab* ptr) {
	if (ptr == book + 50) {	// book�� 50¥�� �迭�̹Ƿ�, ptr�� 50��° �� ���ĸ� ����Ű�� ������ �ּҸ� �߰��� �� ����
		printf("\n�ּҷ��� ���� á���ϴ�.\n");
		return 1;
	}
	else {
		printf("\n�� �ּҸ� �߰��մϴ�.\n�̸�: ");
		scanf("%s", ptr->name);
		printf("��ȭ��ȣ: ");
		scanf("%s", ptr->call);
		getchar();		// ���ۿ� �����ִ� \n�� �����
		printf("�ּ�: ");
		scanf("%[^\n]s", ptr->addr);	// �ּҴ� ���⸦ �����Ͽ� �޴´�
		printf("����(MMDD): ");
		scanf("%s", ptr->bday);
		printf("\n");
		return 2;		// ����� �ϳ� �߰��Ǿ����Ƿ� 2 ��ȯ
	}
}

int find(ab book[], ab* ptr) {
	char kw[10] = "\0";
	ab *find_p;			// �迭�� �������� Ž���� ���� ������ ����
	printf("\n�˻�� �Է��ϼ���: ");	// �̸��� �Է¹޴´�
	scanf("%s", &kw);
	int chk = 0;		// Ž���� �����ߴ��� Ȯ��. 0: ����. 1 : ����
	for (find_p = book; find_p < ptr; find_p++) {
		if (strcmp(kw, find_p->name) == 0) {	// �˻���� find_p�� ����Ű�� ���� �̸��� ���� ���
			printf("    %s\t%s\t%s\t%s\n\n", find_p->name, find_p->call, find_p->addr, find_p->bday);
			chk = 1;	// Ž�� ����
		}
	}
	if (chk == 0)		// Ž���� ������ ���
		printf("ã�� �ּҰ� �����ϴ�.\n\n");
	return 1;			// ����� ������ ������ �ʾ����Ƿ� 1 ��ȯ
}

int del(ab book[], ab* ptr) {
	int rmv;
	show(book, ptr);	// ���� ��ȣ�� �����ֱ� ���� show() ȣ��
	printf("\n�����ϰ��� �ϴ� �ּ��� ������ȣ�� �����ϼ���: ");
	scanf("%d", &rmv);
	ab *rmv_p = &book[rmv];	// ptr�� ���Ͽ� for���� ������Ű�� ���� ������ ����
	int chk = 0;		// Ž���� �����ߴ��� Ȯ��
	for (rmv; rmv_p++ < ptr; rmv++) {
		book[rmv - 1] = book[rmv];	// �����ϰ��� �ϴ� ���� �Ʒ��� �ִ� �ּҵ��� �� ĭ�� �ø���
		chk = 1;		// Ž�� ����
	}
	if (chk == 0) {		// Ž���� ������ ���
		printf("ã�� �ּҰ� �����ϴ�.\n");
		return 1;		//����� ������ ������ �ʾ����Ƿ� 1 ��ȯ
	}
	else {
		printf("�����Ǿ����ϴ�.\n\n");
		show(book, ptr - 1);	// ������ ����� �����ֱ� ���� show() ȣ��
		return 0;		// ����� �ϳ� �����Ǿ����Ƿ� 0 ��ȯ
	}
	
}

int main() {														// choice ���� ���� �ٷ� �Լ��� �Ѿ �� �ֵ���
	int choice, (*pf[4])(ab[], ab*) = { show, add, find, del };		// �Լ� �����͸� ����
	ab book[50], *ptr;	// �ּҷ� �迭, �ּҷ��� ������ �� ���ĸ� ����Ű�� ������
	ptr = book;			// ���� �ּҷϿ� ������ �����Ƿ� �����͸� ù ��° �ٿ� ��ġ��Ų��

	while (1) {
		printf("1. ��Ϻ���\n2. �߰��ϱ�\n3. Ž���ϱ�\n4. �����ϱ�\n5. �����ϱ�\n");
		scanf("%d", &choice);
		if (choice == 5) {	// �����ϱ⸦ �����ϴ� ��� return���� �׳� �����Ŵ
			printf("\n�ּҷ��� �����մϴ�\n");
			return 0;
		}
		else ptr += pf[choice - 1](book, ptr) - 1;	// �����Ͱ� �������� ���� �� 1, ������ �� 2, �ö� �� 0�� ��ȯ�޴´�
	}
}