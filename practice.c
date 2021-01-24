//struct14_2
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<Windows.h>
/*
���� : �輼��
���� : double linked list �� �̿��� �������� ���α׷�
���۱Ⱓ : 2020�� 06�� 01��~04��
����� : Visual Studio 2017
�ֿ� ��� : ����ü, ���Ḯ��Ʈ, �Լ�, ������ ��
�ҽ���� : ������ �޴�ȭ��
�޴�
 ���ο� ���� �߰�
 �뿩���� �ݳ�
 �н� ���� ����
 ���� �뿩
 ���� ���
 ������
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
void gotoxy(int x, int y) // frame�� �׸��� ���� ����ü
{
	COORD CORD;
	CORD.X = x;
	CORD.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), CORD);
}


//Basic input
Node* basicInformationInput(int *); // �⺻ �Ҵ� ����
void InputData(Node *, int *); // user input
//print
int printList(Node *);
void printCollectionList(Node *, Node *);

// list control
void addNewNode(Node **, int *); // �߰�
void deleteNode(Node **, int *, Node *); // ����
Node *rentNode(Node **, int *, Node *); // �뿩
Node *unLinkAndReturnNode(Node **, int *, Node *); // ����, ���Կ� ���� return
void InsertRemovedNode(Node **, int *, Node **); // ����

// menu
void menu(Node *); // �޴�
int pressKeyForMenuSelecting(); // �޴� ȭ�� Ű ����

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


// �⺻ ����
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

	strcpy_s(temp->Book.title, 50, "����̼���"); // input
	strcpy_s(temp->Book.author, 50, "������Ʈ.H.���긮ġ");
	temp->Book.page = 688;

	strcpy_s(temp->next->Book.title, 50, "�� �������ǽ�");
	strcpy_s(temp->next->Book.author, 50, "�� ��Ų");
	temp->next->Book.page = 248;

	strcpy_s(temp->next->next->Book.title, 50, "������ ���Ͽ�");
	strcpy_s(temp->next->next->Book.author, 50, "���� ����");
	temp->next->next->Book.page = 312;

	for (int i = 0; i < 3; i++) { // book index �ο�
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
	printf("���� : "); scanf_s("%[^\n]", inputTitle, 50);
	getchar(); //enter
	gotoxy(3, 7);
	printf("���� : "); scanf_s("%[^\n]", inputAuthor, 50);
	getchar(); //enter
	gotoxy(3, 9);
	printf("������ : "); scanf_s("%d", &inputPage);
	getchar(); //enter

	strcpy_s(p->Book.title, 50, inputTitle); // input data �ֱ�
	strcpy_s(p->Book.author, 50, inputAuthor);
	p->Book.page = inputPage;
	p->Book.index = ++(*cnt);

	pressAnyKeyToContinue();
}

int printList(Node *pN) { // ��� sub function
	int loopCnt = 0;
	Node *search = pN;

	for (int i = 0; i < loopCnt; i++) {
		gotoxy(0, i); printf("��");
	}
	// ���� ���� ���� �����̴� ���� �����ϱ� ���� ��ǥ ����
	gotoxy(0, 0);
	int x = 0; int y = 0;
	printf("��������������������������������������������������������������������������������������������������������������������������������\n");
	puts("��     Title                    Author                   page   ��");
	while (search) {
		gotoxy(x, y + 2); printf("��");
		gotoxy(x, y + 3); printf("��");
		gotoxy(x + 3, y + 3); printf("%d", search->Book.index);
		gotoxy(x + 6, y + 3); printf("%s", search->Book.title);
		gotoxy(x + 31, y + 3); printf("%s", search->Book.author);
		gotoxy(x + 56, y + 3); printf("%dp", search->Book.page);
		gotoxy(x + 63, y + 3); printf("��");
		gotoxy(x + 63, y + 2); printf("��");

		search = search->next; // ������ ���
		y += 2; // �� ����
	}
	gotoxy(x, y + 2);
	puts("��                                                              ��");
	printf("��������������������������������������������������������������������������������������������������������������������������������\n");

	search = NULL;
	return y; // press enter ���� ��ġ�� ���ؼ� y�� return
}
void printCollectionList(Node *pN, Node *pR) { // ������
	x = 0;
	y = printList(pN);
	y = FrameDrawing(x, y + 4, 3);
	if (pR == NULL) {
		gotoxy(11, y + 2);
		printf("�뿩 ����");
	}
	else {
		gotoxy(4, y + 2);
		printf("�뿩�� : %s", pR->Book.title);
	}

	pressAnyKeyToContinue();
}
// list control
void addNewNode(Node **ppN, int *cnt) {	// ���� �߰�					
	Node *pNewNode = (Node *)malloc(sizeof(Node));
	Node *temp = *ppN; // �ӽ�����
	pNewNode->prev = NULL;
	pNewNode->next = NULL;

	InputData(pNewNode, cnt);

	if (temp == NULL) { // ù��° å�� ���
		*ppN = pNewNode;
		return;
	}
	while (temp->next != NULL) { // �ƴ� ��� ������ ��ȣ ã��
		temp = temp->next;
	}
	temp->next = pNewNode;
	pNewNode->prev = temp;
}
void deleteNode(Node **ppN, int *cnt, Node *pR) { // ���� ����
	Node *f = unLinkAndReturnNode(ppN, cnt, pR);
	free(f);
	f = NULL;
	(*cnt)--;

	pressAnyKeyToContinue();
}
Node *rentNode(Node **ppN, int *cnt, Node *pR) { // �뿩 ���� ����Ʈ���� ���� �� ����
	x = 0; y = 0;
	if (pR != NULL) { // �̹� �뿩���� ���
		y = FrameDrawing(0, 1, 3);
		gotoxy(3, y + 2);
		printf("�뿩 ���� ������ �ѱ��Դϴ�");

		pressAnyKeyToContinue();
		return pR;
	}
	else {
		Node *temp = unLinkAndReturnNode(ppN, cnt, pR);
		pressAnyKeyToContinue();
		return temp;
	}
}
Node *unLinkAndReturnNode(Node **ppN, int *cnt, Node *pR) { // ���� ����
	int index = 0;
	Node *temp = *ppN; //�ӽ�����
	x = 0; y = 0;

	y = printList(*ppN);
	y = FrameDrawing(0, y + 5, 3);
	gotoxy(x + 6, y + 2);
	printf("���� ��ȣ (1~%d) : ", *cnt);
	scanf_s("%d", &index);
	getchar(); //enter

	for (int i = 0; i < index - 1; i++) {
		temp = temp->next;
	} // ���ù�ȣ ���� �ҷ�����

	if (temp->Book.index == 1) { // ù��°�� ���
		*ppN = (*ppN)->next;
		(*ppN)->prev = NULL;
		temp->next = NULL;
	}
	else if ((temp->Book.index == *cnt)) { // �������� ���
		(temp->prev)->next = NULL;
		temp->prev = NULL;
	}
	else {
		(temp->prev)->next = temp->next;
		(temp->next)->prev = temp->prev;
	}
	return temp;
}
void InsertRemovedNode(Node **ppN, int *cnt, Node **pR) { // ���� �ݳ�
	x = 0; y = 0;
	if ((*pR) == NULL) {
		y = FrameDrawing(x, y, 3);
		gotoxy(x + 5, y + 2);
		printf("�ݳ��� ������ �����ϴ�\n");
	}
	else {
		int index = (*pR)->Book.index;
		y = FrameDrawing(x, y, 3);
		gotoxy(x + 3, y + 2);
		printf("�뿩���� : %s\n", (*pR)->Book.title);

		Node *pInsertNode = *pR; // �뿩���� �ӽ�����
		Node *temp = *ppN; //�ӽ�����

		for (int i = 0; i < index - 2; i++) {
			temp = temp->next;
		}
		if (index == 1) { // ù��°�� ���
			pInsertNode->next = *ppN;
			(*ppN)->prev = pInsertNode;
			(*ppN) = (*ppN)->prev;
		}
		else if (index != *cnt) { // �������� ���
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
		printf("�ݳ��Ϸ�\n");
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

		choice = pressKeyForMenuSelecting(); // return y�� 6~14(2�� ����)
		if (choice == 16) break; //����
		else {
			Sleep(350); // ���� �� ȭ����ȯ ������
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
	printf("����\n");

	Node *temp = NULL; // free �����ִ� �� üũ
	for (int i = 0; i < nodeCnt - 2; i++) {
		temp = temp->next;
	}
	for (int i = nodeCnt - 2; i > 0; i--) {
		free(temp->prev);
		temp->prev = NULL;
		temp = temp->prev;
	}
}
int pressKeyForMenuSelecting() { //����Ű ����
	int key = 0;
	x = 9; y = 6;

	while (1) {
		menuSelectFrameDrawing(x, y);
		gotoxy(x, y); printf("��");
		key = getch();
		if (key == 13) { //enter������ selecting Ż��
			break;
		}
		if (key == 224) { //Ư��Ƽ �Ǻ�
			key = getch();

			switch (key) {
			case 72: // ��
				menuSelectFrameErase(x, y);
				y -= 2;
				gotoxy(x, y + 2); printf(" ");

				if (y < 6) y = 16; // y 6~16 ����
				break;
			case 80: // ��
				menuSelectFrameErase(x, y);
				y += 2;
				gotoxy(x, y - 2); printf(" ");

				if (y > 16) y = 6;
			}
		}
	}
	return y; // y�� ��ġ�� ���� �޴��� ������ ���̹Ƿ� return
}

// frame
void menuSelectFrameDrawing(int x, int y) {
	gotoxy(x + 3, y - 1); printf("������������������������������������������");
	gotoxy(x + 3, y); printf("��");
	gotoxy(x + 23, y); printf("��");
	gotoxy(x + 3, y + 1); printf("������������������������������������������");
}
void menuSelectFrameErase(int x, int y) {
	gotoxy(x + 3, y - 1); printf("                     ");
	gotoxy(x + 3, y); printf(" ");
	gotoxy(x + 23, y); printf(" ");
	gotoxy(x + 3, y + 1); printf("                     ");
}
void menuFrameDrawing() {
	char *menu = "\t        ���ο� ���� �߰�\n\n\t        �뿩���� �ݳ�\n\n\t        �н� ���� ����\n\n\t        ���� �뿩\n\n\t        ���� ���\n\n\t        ������";
	printf("\n  ������������������������������������������������������������������������������\n");
	printf("  ��                                     ��\n");
	printf("  ��                                     ��\n");
	printf("  �� ���������������������������������������������������������������������� ��\n");
	for (int i = 0; i < 13; i++) {
		printf("  �� ��                                 �� ��\n");
	}
	printf("  �� ���������������������������������������������������������������������� ��\n");
	printf("  ������������������������������������������������������������������������������\n");

	gotoxy(17, 2);
	printf(" ������");
	gotoxy(0, 6);
	printf("%s", menu);
}
int FrameDrawing(int x, int y, int height) {
	int i;
	gotoxy(x, y); printf("����������������������������������������������������������������\n");
	for (i = 1; i <= height; i++) {
		gotoxy(x, y + i); printf("��"); gotoxy(x + 31, y + i); printf("��");
	}
	gotoxy(x, y + i); printf("����������������������������������������������������������������\n");
	return y;
}

void pressAnyKeyToContinue() { // for delay
	gotoxy(0, 23);
	printf("\n������������������������������������������������������������������������������\n");
	printf("��  ����Ͻ÷��� ���� Ű�� �����ּ���  ��\n");
	printf("������������������������������������������������������������������������������\n");
	getchar();
}
