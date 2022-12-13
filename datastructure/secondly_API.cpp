#include "B_Tree.h"
#include "Link_List.h"	

/* ��p->key����k */
int Search(BTree p, KeyType key) {	// Ѱ�� key �� node ���ڽ���е�λ��
	if (p == NULL) return 1;	// �п�

	int i = 1;
	while (i <= p->keyNum && key > p->key[i]) i++;
	return i;
}

Status newRoot(BTree& t, BTree child0, BTree child1, KeyType key,Record rcd) {	// ����һ���¸�
	InitBtree(t);
	t->rcd[1] = rcd;
	t->key[1] = key;
	t->keyNum++;
	t->child[0] = child0;
	t->child[1] = child1;
	if (child0 != NULL)	child0->parent = t;
	if (child1 != NULL)	child1->parent = t;
	t->parent = NULL;
	return OK;
}

void Insert(BTree& q, int i, KeyType key, Record rcd, BTree newNode) {	// ���¼�¼ rcd ���뵽��� node �ĵ� i ��λ��
	int j, n = q->keyNum;
	for (j = n; j >= i; j--) {
		Move(q, j+1, q, j);
	}
	q->key[i] = key;
	q->child[i] = newNode;
	q->rcd[i] = rcd;
	if (newNode != NULL)	newNode->parent = q;
	q->keyNum++;
}

Status split(BTree& q, BTree& newNode) {		// �� node �����м���ѳ�������
	int i, j, n = q->keyNum;
	InitBtree(newNode);
	//if (newNode == NULL)	return OVERFLOW;
	newNode->child[0] = q->child[MID_KEY];
	for (i = MID_KEY + 1, j = 1; i <= n; i++, j++) {
		Move(newNode, j, q, i);
	}
	for (i = MID_KEY + 1; i <= n; i++) {
		q->key[i] = 0;
		q->child[i] = NULL;
		q->rcd[i] = NULL;
	}
	newNode->keyNum = n - MID_KEY;
	newNode->parent = q->parent;
	for (i = 0; i <= n - MID_KEY; i++)
		if (newNode->child[i] != NULL)
			newNode->child[i]->parent = newNode;
	q->child[MID_KEY] = NULL;
	q->keyNum = MID_KEY - 1;
	return OK;
}





