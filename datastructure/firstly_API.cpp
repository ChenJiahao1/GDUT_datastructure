#include "B_Tree.h"
#include "Link_List.h"	

void SearchBTree(BTree t, KeyType k, Result& result) {
	int i=1, found = 0;
	BTree p = t, q = NULL;
	while (p != NULL && 0 == found) {
		i = Search(p, k);
		if (i <= p->keyNum && p->key[i] == k)	found = 1;
		else {
			q = p;
			p = p->child[i - 1];
		}
	}
	if (found == 1)		result = getResult(i, 1, p);
	else
	{
		result = getResult(i, 0, q);
	}
}


void InsertBTree(BTree& t, KeyType key, Record rcd) {
	int finished = 0, needNewRoot = 0;	//���޸�  Status
	Result result;
	SearchBTree(t, key, result);
	int i = result.i;
	BTree q=result.pt, newNode = NULL;
	if (NULL == q)	newRoot(t, NULL, NULL, key, rcd);
	else {
		while (0 == needNewRoot && 0 == finished) {
			Insert(q, i, key, rcd, newNode);
			if (q->keyNum <= MAX_KEY)	finished = 1;
			else {
				split(q, newNode);
				key = q->key[MID_KEY];	//��key��rcd��ֵ�ı�Ϊ�����븸����ֵ
				rcd = q->rcd[MID_KEY];
				q->key[MID_KEY] = 0;
				q->rcd[MID_KEY] = NULL;
				if (q->parent != NULL) {	//��qָ��ָ�򸸽��
					q = q->parent;
					i = Search(q, key);
				}
				else needNewRoot = 1;
			}
		}
		if (1 == needNewRoot)
		{
			newRoot(t, q, newNode, key, rcd);
		}
	}
}



void DeleteBTNode(BTree& p, int i, BTree &T) {
	if (p->child[0] != NULL) {	//�ж��Ƿ�Ϊ���²���ն˽��
		Successor(p, i);
		DeleteBTNode(p, 1, T);
	}
	else {
		Remove(p, i);
		if (p->keyNum < MIN_KEY)	//��ֻ��һ�������ֱ�ӷ���
		{
			Restore(p, T);
		}
	}
}


/* ����key�� B ��ִ��ɾ������ */
Status DeleteBTree(BTree &tree, KeyType key) {	//�����������ﷱ���ʽ�ɾ������Һϲ�
	Result result;
	SearchBTree(tree, key, result);
	if (result.tag == 0)	return ERROR;	//δ�ҵ�
	DeleteBTNode(result.pt, result.i, tree);
	return OK;
}


Status UpdateBTree(BTree tree, KeyType key, Record rcd) {	//��rcd����data��
	Result result;
	SearchBTree(tree, key, result);
	if (result.tag == 1) {
		result.pt->rcd[result.i] = rcd;
		return OK;
	}
	else
	{
		return ERROR;
	}
}


void DestroyBTree(BTree& T) {
	if (T == NULL)return;
	int i;
	BTNode* p = T;
	if (p != NULL) {
		for (i = 0; i <= p->keyNum; i++) {
			BTNode* q = p->child[i];
			DestroyBTree(q);
		}
		free(p);
	}

	T = NULL;
}



//���� key �� data��Ϊ����
Status MakeBTree(BTree& t, int num) {	// ���� B �� 
	KeyType key;

	for (int i = 1; i <= num; i++) {
		printf("���������׺�:");
		scanf_s("%d", &key);
		Record rcd = import_Record();
		if (rcd == NULL)	return ERROR;
		InsertBTree(t, key, rcd);
	}
	return OK;
}


Status Borrow(BTree t) {
	KeyType key;
	scanf_s("%d", &key);
	Result result;
	SearchBTree(t, key, result);
	if (result.tag == 0) {
		printf("δ���ҵ����鼮��\n");
		return ERROR;
	}
	if (result.pt->rcd[result.i]->now_count <= 0) {
		printf("��治�㣬����ʧ�ܣ�\n");
		return ERROR;
	}
	Status flag = 0;
	int IDnumber;
	char* deadline = (char*)malloc(sizeof(char) * 15);
	if (deadline == NULL)  return OVERFLOW;
	while (flag == 0) {		//��ʧ��ʱ��������
		printf("���������֤����:");
		scanf_s("%d", &IDnumber);
		printf("������黹����:");
		scanf_s("%s", deadline, 15);
		deadline[4] = '-';
		deadline[7] = '-';
		flag = InsertList(result.pt->rcd[result.i]->information, IDnumber, deadline);
	}
	//�ı��ִ���
	result.pt->rcd[result.i]->now_count--;
	return OK;
}

Status DeleteBorrower(BTree T, KeyType key, int IDnumber) {		//�������׺��Լ�������֤����
	Result result;
	SearchBTree(T, key, result);
	if (result.tag == 0) {
		printf("δ�ҵ�������!\n");
		return ERROR;
	}
	if (DeleteList(result.pt->rcd[result.i]->information, IDnumber) == 0) {
		printf("����ʧ�ܣ�ϵͳû�������ĸ����׼�¼!\n");
		return ERROR;
	}
	result.pt->rcd[result.i]->now_count++;
	return OK;
}