#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
typedef struct addr_bk ab;	// 주소록 구조체의 별명
int show(ab book[], ab* ptr);	// 주소록을 보여주는 함수
int add(ab book[], ab* ptr);	// 주소록에 주소를 추가하는 함수
int find(ab book[], ab* ptr);	// 주소를 탐색하는 함수
int del(ab book[], ab* ptr);	// 주소를 지우는 함수

struct addr_bk {
	char name[10], call[20], addr[50], bday[10];	// 이름, 전화번호, 주소, 생일
};

int show(ab book[], ab* ptr) {
	printf("\n00 | 이름\t전화번호\t주소\t\t생일\n");
	ab* p_now = book;	// ptr과 비교하여 for문을 중지시키기 위한 포인터 선언
	for (int i = 0; p_now + i < ptr; i++) {
		printf("%02d | %s\t%s\t%s\t%s\n", i + 1, book[i].name, book[i].call, book[i].addr, book[i].bday);
	}
	printf("\n");
	return 1;			// 목록의 개수가 변하지 않았으므로 1 반환
}

int add(ab book[], ab* ptr) {
	if (ptr == book + 50) {	// book이 50짜리 배열이므로, ptr이 50번째 줄 이후를 가리키고 있으면 주소를 추가할 수 없다
		printf("\n주소록이 가득 찼습니다.\n");
		return 1;
	}
	else {
		printf("\n새 주소를 추가합니다.\n이름: ");
		scanf("%s", ptr->name);
		printf("전화번호: ");
		scanf("%s", ptr->call);
		getchar();		// 버퍼에 남아있는 \n을 지운다
		printf("주소: ");
		scanf("%[^\n]s", ptr->addr);	// 주소는 띄어쓰기를 포함하여 받는다
		printf("생일(MMDD): ");
		scanf("%s", ptr->bday);
		printf("\n");
		return 2;		// 목록이 하나 추가되었으므로 2 반환
	}
}

int find(ab book[], ab* ptr) {
	char kw[10] = "\0";
	ab *find_p;			// 배열을 내려가며 탐색에 사용될 포인터 선언
	printf("\n검색어를 입력하세요: ");	// 이름만 입력받는다
	scanf("%s", &kw);
	int chk = 0;		// 탐색에 성공했는지 확인. 0: 실패. 1 : 성공
	for (find_p = book; find_p < ptr; find_p++) {
		if (strcmp(kw, find_p->name) == 0) {	// 검색어와 find_p가 가리키는 줄의 이름이 같은 경우
			printf("    %s\t%s\t%s\t%s\n\n", find_p->name, find_p->call, find_p->addr, find_p->bday);
			chk = 1;	// 탐색 성공
		}
	}
	if (chk == 0)		// 탐색에 실패한 경우
		printf("찾는 주소가 없습니다.\n\n");
	return 1;			// 목록의 개수가 변하지 않았으므로 1 반환
}

int del(ab book[], ab* ptr) {
	int rmv;
	show(book, ptr);	// 목차 번호를 보여주기 위해 show() 호출
	printf("\n삭제하고자 하는 주소의 목차번호를 선택하세요: ");
	scanf("%d", &rmv);
	ab *rmv_p = &book[rmv];	// ptr과 비교하여 for문을 중지시키기 위한 포인터 선언
	int chk = 0;		// 탐색에 성공했는지 확인
	for (rmv; rmv_p++ < ptr; rmv++) {
		book[rmv - 1] = book[rmv];	// 삭제하고자 하는 줄의 아래에 있는 주소들을 한 칸씩 올린다
		chk = 1;		// 탐색 성공
	}
	if (chk == 0) {		// 탐색에 실패한 경우
		printf("찾는 주소가 없습니다.\n");
		return 1;		//목록의 개수가 변하지 않았으므로 1 반환
	}
	else {
		printf("삭제되었습니다.\n\n");
		show(book, ptr - 1);	// 삭제된 결과를 보여주기 위해 show() 호출
		return 0;		// 목록이 하나 삭제되었으므로 0 반환
	}
	
}

int main() {														// choice 값을 통해 바로 함수로 넘어갈 수 있도록
	int choice, (*pf[4])(ab[], ab*) = { show, add, find, del };		// 함수 포인터를 선언
	ab book[50], *ptr;	// 주소록 배열, 주소록의 마지막 줄 이후를 가리키는 포인터
	ptr = book;			// 아직 주소록에 내용이 없으므로 포인터를 첫 번째 줄에 위치시킨다

	while (1) {
		printf("1. 목록보기\n2. 추가하기\n3. 탐색하기\n4. 삭제하기\n5. 종료하기\n");
		scanf("%d", &choice);
		if (choice == 5) {	// 종료하기를 선택하는 경우 return으로 그냥 종료시킴
			printf("\n주소록을 종료합니다\n");
			return 0;
		}
		else ptr += pf[choice - 1](book, ptr) - 1;	// 포인터가 움직이지 않을 때 1, 내려갈 때 2, 올라갈 때 0을 반환받는다
	}
}