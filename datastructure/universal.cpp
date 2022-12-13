#include "B_Tree.h"
#include "Link_List.h"

Status InitBtree(BTree& root) {	// ��ʼ�� B ��
	root = (BTree)malloc(sizeof(BTNode));
	if (root == NULL)	return OVERFLOW;
	root->parent = NULL;
	for (int i = 0; i <= M; i++)
	{
		root->key[i] = 0;
		root->child[i] = NULL;
		root->rcd[i] = NULL;
	}
	root->keyNum = 0;
	return TRUE;
}

/* ���һ��������� */
Result getResult(int i, int tag, BTree pt) {
	Result result;
	result.pt = pt;
	result.i = i;
	result.tag = tag;
	
	return result;
}
                                                                                                         
Record import_Record(void) {	//���ڲ�������
	Record rcd = (Record)malloc(sizeof(Rcd));
	char* bookname = (char*)malloc(sizeof(char) * BOOKNAME_SIZE);
	char* author = (char*)malloc(sizeof(char) * AUTHOR_SIZE);
	if(rcd == NULL||bookname==NULL||author==NULL)	return NULL;
	rcd->information.head = NULL;
	rcd->information.len = 0;
	printf("��������������\n");
	fflush(stdin);
	gets_s(bookname, BOOKNAME_SIZE);
	printf("����������������\n");
	fflush(stdin);
	gets_s(author, AUTHOR_SIZE);
	printf("�������������\n");
	fflush(stdin);
	scanf_s("%d", &rcd->now_count);
	rcd->bookname = bookname;
	rcd->author = author;
	rcd->all_count = rcd->now_count;
	return rcd;
}


void Move(BTree& a, int index_a, BTree& b, int index_b) {	//��b���index_b��ֵ��ֵ��a���index_a
	a->key[index_a] = b->key[index_b];
	a->child[index_a] = b->child[index_b];
	a->rcd[index_a] = b->rcd[index_b];
}

