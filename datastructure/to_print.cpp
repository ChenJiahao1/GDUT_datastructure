#include "B_Tree.h"
#include "Link_List.h"	

/* ������������ϼ�¼�������ܺ� */
int CountKeyNum(BTree tree) {
	// ������Ϊ 0
	if (tree == NULL) return 0;

	// ��������������¼�����ܺ�
	int childTotal = 0;
	for (int i = 0; i <= tree->keyNum; i++) {
		childTotal += CountKeyNum(tree->child[i]);
	}

	// ������������ļ�¼��������Ϊ�ܼ�¼����
	return tree->keyNum + childTotal;
}

/* ��ӡ B �� */
void TraverseBTree(BTree tree) {
	// ��̬����һ�����飬���ڴ�ŵ�ǰ����Ƿ�Ϊ�����ı�ʶ
	int nowNum = 0;
	int* isLast = (int*)malloc(sizeof(int) * (CountKeyNum(tree) + 10));

	// ��ӡ����
	printf("\n");
	PrintBTree(tree, isLast, nowNum);
}

/* �ݹ��ӡ���� */
void PrintBTree(BTree tree, int isLast[], int nowNum) {
	if (tree == NULL) return;

	printf("��\n");
	for (int i = 0; i <= tree->keyNum; i++) {
		if (tree->child[i] != NULL) {
			printBranch(isLast, nowNum);
			printf("�ǩ�����������");
			isLast[nowNum++] = (i == tree->keyNum);
			PrintBTree(tree->child[i], isLast, nowNum);
			nowNum--;
		}
		if (i != tree->keyNum) {
			printBranch(isLast, nowNum);
			printf("�ǩ� %d\n", tree->key[i + 1]);
			/*printf("�ǩ� %d�� %d\n", tree->key[i + 1], tree->rcd[i+1]->data);*/
		}
	}
}

/* ��ӡ��֦ */
void printBranch(int isLast[], int nowNum) {
	for (int i = 0; i < nowNum; i++) {
		if (isLast[i]) printf(" ");
		else printf("��");
		printf("      ");
	}
}


void InorderBTree(BTree T) {	//����������ף��������׺Ŵ�С����˳�����
	if (T == NULL)return;
	int i;
	for (i = 0; i < T->keyNum; i++) {
		InorderBTree(T->child[i]);
		PrintOneBook(T->key[i + 1], T->rcd[i + 1]);
	}
	InorderBTree(T->child[i]);
}


void InorderBTree_author(BTree T, char* author) {	//�����������������������
	if (T == NULL)return;
	int i;
	for (i = 0; i < T->keyNum; i++) {
		InorderBTree_author(T->child[i], author);
		if (strcmp(T->rcd[i + 1]->author, author) == 0) {
			PrintOneBook(T->key[i + 1], T->rcd[i + 1]);
		}
	}
	InorderBTree_author(T->child[i], author);
}


void PrintHead() {//���ͷ����ʽ
	printf("\n");
	printf("|********************************************���׻�����Ϣ*********************************************|\n");
	printf("|���׺�|������                        |����                |�ִ���  |�ܿ����|������֤|�黹����       |\n");
	printf("|------|------------------------------|--------------------|--------|--------|--------|---------------|\n");
}

void PrintOneBook(KeyType key,Record record) { //��ʾBook������Ϣ-
	if (record->information.head == NULL) {
		printf("|%-6d|%-30s|%-20s|%-8d|%-8d|%-8s|%-15s|\n", key, record->bookname, record->author,
			record->now_count, record->all_count,
			"����", "����");
	}
	else {
		printf("|%-6d|%-30s|%-20s|%-8d|%-8d|%-8d|%-15s|\n", key, record->bookname, record->author,
			record->now_count, record->all_count,
			record->information.head->next->IDnumber, record->information.head->next->deadline);
	}
}

void PrintTail() {//���ײ���ʽ
	printf("|------|------------------------------|--------------------|--------|--------|--------|---------------|\n");
}

void PrintALLBook(BTree T) {
	PrintHead();
	InorderBTree(T);
	PrintTail();
}

void PrintAuthorBook(BTree T, char*author) {
	PrintHead();
	InorderBTree_author(T, author);
	PrintTail();
}



