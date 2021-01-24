//struct14_2
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<Windows.h>
/*
제작 : 김세현
주제 : double linked list 를 이용한 도서관리 프로그램
제작기간 : 2020년 06월 01일~04일
사용툴 : Visual Studio 2017
주요 기능 : 구조체, 연결리스트, 함수, 포인터 등
소스결과 : 도서관 메뉴화면
메뉴
 새로운 도서 추가
 대여도서 반납
 분실 도서 제외
 도서 대여
 소장 목록
 나가기
*/

//structure
typedef struct Infomation {
	char title[50];
	char author[50];
	int page;
	int index;
}Info;
typedef struct Node {
	struct Node *prev;
	struct Node *next;
	Info Book;
}Node;
void gotoxy(int x, int y) // frame을 그리기 위한 구조체
{
	COORD CORD;
	CORD.X = x;
	CORD.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), CORD);
}


//Basic input
Node* basicInformationInput(int *); // 기본 할당 정보
void InputData(Node *, int *); // user input
//print
int printList(Node *);
void printCollectionList(Node *, Node *);

// list control
void addNewNode(Node **, int *); // 추가
void deleteNode(Node **, int *, Node *); // 삭제
Node *rentNode(Node **, int *, Node *); // 대여
Node *unLinkAndReturnNode(Node **, int *, Node *); // 삭제, 삽입용 정보 return
void InsertRemovedNode(Node **, int *, Node **); // 삽입

// menu
void menu(Node *); // 메뉴
int pressKeyForMenuSelecting(); // 메뉴 화면 키 조작

// decoration
void menuSelectFrameDrawing(int, int);
void menuSelectFrameErase(int, int);
void menuFrameDrawing();
int FrameDrawing(int, int, int);
//other
void pressAnyKeyToContinue();


int x; int y;
// main()
void main() {
	// Head
	Node *pHead = (Node*)malloc(sizeof(Node));
	pHead = NULL;
	menu(pHead);
}


// 기본 정보
Node* basicInformationInput(int *cnt) {
	Node *pNewNode1 = (Node *)malloc(sizeof(Node));
	Node *pNewNode2 = (Node *)malloc(sizeof(Node));
	Node *pNewNode3 = (Node *)malloc(sizeof(Node));  // create head->next->next
	Node *temp = pNewNode1;

	pNewNode1->prev = NULL; // link
	pNewNode1->next = pNewNode2;
	pNewNode2->prev = pNewNode1;
	pNewNode2->next = pNewNode3;
	pNewNode3->prev = pNewNode2;
	pNewNode3->next = NULL;

	strcpy_s(temp->Book.title, 50, "서양미술사"); // input
	strcpy_s(temp->Book.author, 50, "에른스트.H.곰브리치");
	temp->Book.page = 688;

	strcpy_s(temp->next->Book.title, 50, "모마 마스터피스");
	strcpy_s(temp->next->Book.author, 50, "앤 템킨");
	temp->next->Book.page = 248;

	strcpy_s(temp->next->next->Book.title, 50, "사진에 관하여");
	strcpy_s(temp->next->next->Book.author, 50, "수잔 손택");
	temp->next->next->Book.page = 312;

	for (int i = 0; i < 3; i++) { // book index 부여
		temp->Book.index = ++(*cnt);
		temp = temp->next;
	}
	return pNewNode1;
}
void InputData(Node *p, int *cnt) {
	int inputPage;
	char inputTitle[50] = { 0 };
	char inputAuthor[50] = { 0 };
	FrameDrawing(0, 3, 7);

	gotoxy(3, 5);
	printf("제목 : "); scanf_s("%[^\n]", inputTitle, 50);
	getchar(); //enter
	gotoxy(3, 7);
	printf("저자 : "); scanf_s("%[^\n]", inputAuthor, 50);
	getchar(); //enter
	gotoxy(3, 9);
	printf("페이지 : "); scanf_s("%d", &inputPage);
	getchar(); //enter

	strcpy_s(p->Book.title, 50, inputTitle); // input data 넣기
	strcpy_s(p->Book.author, 50, inputAuthor);
	p->Book.page = inputPage;
	p->Book.index = ++(*cnt);

	pressAnyKeyToContinue();
}

int printList(Node *pN) { // 출력 sub function
	int loopCnt = 0;
	Node *search = pN;

	for (int i = 0; i < loopCnt; i++) {
		gotoxy(0, i); printf("┃");
	}
	// 글자 수에 따라 움직이는 것을 방지하기 위해 좌표 고정
	gotoxy(0, 0);
	int x = 0; int y = 0;
	printf("┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n");
	puts("┃     Title                    Author                   page   ┃");
	while (search) {
		gotoxy(x, y + 2); printf("┃");
		gotoxy(x, y + 3); printf("┃");
		gotoxy(x + 3, y + 3); printf("%d", search->Book.index);
		gotoxy(x + 6, y + 3); printf("%s", search->Book.title);
		gotoxy(x + 31, y + 3); printf("%s", search->Book.author);
		gotoxy(x + 56, y + 3); printf("%dp", search->Book.page);
		gotoxy(x + 63, y + 3); printf("┃");
		gotoxy(x + 63, y + 2); printf("┃");

		search = search->next; // 끝까지 출력
		y += 2; // 줄 간격
	}
	gotoxy(x, y + 2);
	puts("┃                                                              ┃");
	printf("┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n");

	search = NULL;
	return y; // press enter 문구 위치를 위해서 y값 return
}
void printCollectionList(Node *pN, Node *pR) { // 소장목록
	x = 0;
	y = printList(pN);
	y = FrameDrawing(x, y + 4, 3);
	if (pR == NULL) {
		gotoxy(11, y + 2);
		printf("대여 가능");
	}
	else {
		gotoxy(4, y + 2);
		printf("대여중 : %s", pR->Book.title);
	}

	pressAnyKeyToContinue();
}
// list control
void addNewNode(Node **ppN, int *cnt) {	// 도서 추가					
	Node *pNewNode = (Node *)malloc(sizeof(Node));
	Node *temp = *ppN; // 임시저장
	pNewNode->prev = NULL;
	pNewNode->next = NULL;

	InputData(pNewNode, cnt);

	if (temp == NULL) { // 첫번째 책일 경우
		*ppN = pNewNode;
		return;
	}
	while (temp->next != NULL) { // 아닐 경우 마지막 번호 찾기
		temp = temp->next;
	}
	temp->next = pNewNode;
	pNewNode->prev = temp;
}
void deleteNode(Node **ppN, int *cnt, Node *pR) { // 도서 삭제
	Node *f = unLinkAndReturnNode(ppN, cnt, pR);
	free(f);
	f = NULL;
	(*cnt)--;

	pressAnyKeyToContinue();
}
Node *rentNode(Node **ppN, int *cnt, Node *pR) { // 대여 도서 리스트에서 제거 후 저장
	x = 0; y = 0;
	if (pR != NULL) { // 이미 대여중인 경우
		y = FrameDrawing(0, 1, 3);
		gotoxy(3, y + 2);
		printf("대여 가능 도서는 한권입니다");

		pressAnyKeyToContinue();
		return pR;
	}
	else {
		Node *temp = unLinkAndReturnNode(ppN, cnt, pR);
		pressAnyKeyToContinue();
		return temp;
	}
}
Node *unLinkAndReturnNode(Node **ppN, int *cnt, Node *pR) { // 도서 추출
	int index = 0;
	Node *temp = *ppN; //임시저장
	x = 0; y = 0;

	y = printList(*ppN);
	y = FrameDrawing(0, y + 5, 3);
	gotoxy(x + 6, y + 2);
	printf("도서 번호 (1~%d) : ", *cnt);
	scanf_s("%d", &index);
	getchar(); //enter

	for (int i = 0; i < index - 1; i++) {
		temp = temp->next;
	} // 선택번호 도서 불러오기

	if (temp->Book.index == 1) { // 첫번째인 경우
		*ppN = (*ppN)->next;
		(*ppN)->prev = NULL;
		temp->next = NULL;
	}
	else if ((temp->Book.index == *cnt)) { // 마지막인 경우
		(temp->prev)->next = NULL;
		temp->prev = NULL;
	}
	else {
		(temp->prev)->next = temp->next;
		(temp->next)->prev = temp->prev;
	}
	return temp;
}
void InsertRemovedNode(Node **ppN, int *cnt, Node **pR) { // 도서 반납
	x = 0; y = 0;
	if ((*pR) == NULL) {
		y = FrameDrawing(x, y, 3);
		gotoxy(x + 5, y + 2);
		printf("반납할 도서가 없습니다\n");
	}
	else {
		int index = (*pR)->Book.index;
		y = FrameDrawing(x, y, 3);
		gotoxy(x + 3, y + 2);
		printf("대여도서 : %s\n", (*pR)->Book.title);

		Node *pInsertNode = *pR; // 대여도서 임시저장
		Node *temp = *ppN; //임시저장

		for (int i = 0; i < index - 2; i++) {
			temp = temp->next;
		}
		if (index == 1) { // 첫번째인 경우
			pInsertNode->next = *ppN;
			(*ppN)->prev = pInsertNode;
			(*ppN) = (*ppN)->prev;
		}
		else if (index != *cnt) { // 마지막인 경우
			Node *temp2 = temp->next;
			pInsertNode->prev = temp;
			pInsertNode->next = temp2;
			temp->next = pInsertNode;
			temp2->prev = pInsertNode;
		}
		else {
			temp->next = pInsertNode;
			pInsertNode->prev = temp;
			pInsertNode->next = NULL;
		}
		y = 5;
		y = FrameDrawing(x, y, 3);
		gotoxy(x + 12, y + 2);
		printf("반납완료\n");
		*pR = NULL;
	}
	pressAnyKeyToContinue();
}
// main menu control
void menu(Node *pN) {
	int nodeCnt = 0;
	pN = basicInformationInput(&nodeCnt);
	Node *tempForRent = NULL;
	int choice = 0; int exit = 0;

	while (1) {
		system("cls");
		menuFrameDrawing();

		choice = pressKeyForMenuSelecting(); // return y값 6~14(2씩 증가)
		if (choice == 16) break; //종료
		else {
			Sleep(350); // 선택 후 화면전환 딜레이
			system("cls");
			switch (choice) {
			case 6: addNewNode(&pN, &nodeCnt); break; //6
			case 8: InsertRemovedNode(&pN, &nodeCnt, &tempForRent); break;
			case 10: deleteNode(&pN, &nodeCnt, tempForRent); break;
			case 12: tempForRent = rentNode(&pN, &nodeCnt, tempForRent); break;
			case 14: printCollectionList(pN, tempForRent); break; //14
			}
		}
	}

	system("cls");
	printf("종료\n");

	Node *temp = NULL; // free 문제있는 듯 체크
	for (int i = 0; i < nodeCnt - 2; i++) {
		temp = temp->next;
	}
	for (int i = nodeCnt - 2; i > 0; i--) {
		free(temp->prev);
		temp->prev = NULL;
		temp = temp->prev;
	}
}
int pressKeyForMenuSelecting() { //방향키 조작
	int key = 0;
	x = 9; y = 6;

	while (1) {
		menuSelectFrameDrawing(x, y);
		gotoxy(x, y); printf("▶");
		key = getch();
		if (key == 13) { //enter누르면 selecting 탈출
			break;
		}
		if (key == 224) { //특수티 판별
			key = getch();

			switch (key) {
			case 72: // ↑
				menuSelectFrameErase(x, y);
				y -= 2;
				gotoxy(x, y + 2); printf(" ");

				if (y < 6) y = 16; // y 6~16 고정
				break;
			case 80: // ↓
				menuSelectFrameErase(x, y);
				y += 2;
				gotoxy(x, y - 2); printf(" ");

				if (y > 16) y = 6;
			}
		}
	}
	return y; // y의 위치에 따라 메뉴를 선택할 것이므로 return
}

// frame
void menuSelectFrameDrawing(int x, int y) {
	gotoxy(x + 3, y - 1); printf("┌───────────────────┐");
	gotoxy(x + 3, y); printf("│");
	gotoxy(x + 23, y); printf("│");
	gotoxy(x + 3, y + 1); printf("└───────────────────┘");
}
void menuSelectFrameErase(int x, int y) {
	gotoxy(x + 3, y - 1); printf("                     ");
	gotoxy(x + 3, y); printf(" ");
	gotoxy(x + 23, y); printf(" ");
	gotoxy(x + 3, y + 1); printf("                     ");
}
void menuFrameDrawing() {
	char *menu = "\t        새로운 도서 추가\n\n\t        대여도서 반납\n\n\t        분실 도서 제외\n\n\t        도서 대여\n\n\t        소장 목록\n\n\t        나가기";
	printf("\n  ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n");
	printf("  ┃                                     ┃\n");
	printf("  ┃                                     ┃\n");
	printf("  ┃ ┌─────────────────────────────────┐ ┃\n");
	for (int i = 0; i < 13; i++) {
		printf("  ┃ │                                 │ ┃\n");
	}
	printf("  ┃ └─────────────────────────────────┘ ┃\n");
	printf("  ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n");

	gotoxy(17, 2);
	printf(" 도서관");
	gotoxy(0, 6);
	printf("%s", menu);
}
int FrameDrawing(int x, int y, int height) {
	int i;
	gotoxy(x, y); printf("┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n");
	for (i = 1; i <= height; i++) {
		gotoxy(x, y + i); printf("┃"); gotoxy(x + 31, y + i); printf("┃");
	}
	gotoxy(x, y + i); printf("┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n");
	return y;
}

void pressAnyKeyToContinue() { // for delay
	gotoxy(0, 23);
	printf("\n┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n");
	printf("┃  계속하시려면 엔터 키를 눌러주세요  ┃\n");
	printf("┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n");
	getchar();
}
