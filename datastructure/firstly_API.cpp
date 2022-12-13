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
	int finished = 0, needNewRoot = 0;	//待修改  Status
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
				key = q->key[MID_KEY];	//将key，rcd的值改变为待插入父结点的值
				rcd = q->rcd[MID_KEY];
				q->key[MID_KEY] = 0;
				q->rcd[MID_KEY] = NULL;
				if (q->parent != NULL) {	//将q指针指向父结点
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
	if (p->child[0] != NULL) {	//判断是否为最下层非终端结点
		Successor(p, i);
		DeleteBTNode(p, 1, T);
	}
	else {
		Remove(p, i);
		if (p->keyNum < MIN_KEY)	//若只有一个结点则直接返回
		{
			Restore(p, T);
		}
	}
}


/* 根据key对 B 树执行删除操作 */
Status DeleteBTree(BTree &tree, KeyType key) {	//避免主函数里繁琐故将删除与查找合并
	Result result;
	SearchBTree(tree, key, result);
	if (result.tag == 0)	return ERROR;	//未找到
	DeleteBTNode(result.pt, result.i, tree);
	return OK;
}


Status UpdateBTree(BTree tree, KeyType key, Record rcd) {	//传rcd还是data？
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



//当成 key 与 data都为整型
Status MakeBTree(BTree& t, int num) {	// 构建 B 树 
	KeyType key;

	for (int i = 1; i <= num; i++) {
		printf("请输入文献号:");
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
		printf("未查找到该书籍！\n");
		return ERROR;
	}
	if (result.pt->rcd[result.i]->now_count <= 0) {
		printf("库存不足，借阅失败！\n");
		return ERROR;
	}
	Status flag = 0;
	int IDnumber;
	char* deadline = (char*)malloc(sizeof(char) * 15);
	if (deadline == NULL)  return OVERFLOW;
	while (flag == 0) {		//当失败时重新输入
		printf("请输入借阅证号码:");
		scanf_s("%d", &IDnumber);
		printf("请输入归还日期:");
		scanf_s("%s", deadline, 15);
		deadline[4] = '-';
		deadline[7] = '-';
		flag = InsertList(result.pt->rcd[result.i]->information, IDnumber, deadline);
	}
	//改变现存量
	result.pt->rcd[result.i]->now_count--;
	return OK;
}

Status DeleteBorrower(BTree T, KeyType key, int IDnumber) {		//根据文献号以及借阅者证还书
	Result result;
	SearchBTree(T, key, result);
	if (result.tag == 0) {
		printf("未找到该文献!\n");
		return ERROR;
	}
	if (DeleteList(result.pt->rcd[result.i]->information, IDnumber) == 0) {
		printf("还书失败，系统没有您借阅该文献记录!\n");
		return ERROR;
	}
	result.pt->rcd[result.i]->now_count++;
	return OK;
}