#include "B_Tree.h"
#include "Link_List.h"	

/* 计算出整棵树上记录条数的总和 */
int CountKeyNum(BTree tree) {
	// 空树则为 0
	if (tree == NULL) return 0;

	// 计算所有子树记录条数总和
	int childTotal = 0;
	for (int i = 0; i <= tree->keyNum; i++) {
		childTotal += CountKeyNum(tree->child[i]);
	}

	// 子树加上自身的记录条数，即为总记录条数
	return tree->keyNum + childTotal;
}

/* 打印 B 树 */
void TraverseBTree(BTree tree) {
	// 动态创建一个数组，用于存放当前结点是否为最后结点的标识
	int nowNum = 0;
	int* isLast = (int*)malloc(sizeof(int) * (CountKeyNum(tree) + 10));

	// 打印树形
	printf("\n");
	PrintBTree(tree, isLast, nowNum);
}

/* 递归打印树形 */
void PrintBTree(BTree tree, int isLast[], int nowNum) {
	if (tree == NULL) return;

	printf("┓\n");
	for (int i = 0; i <= tree->keyNum; i++) {
		if (tree->child[i] != NULL) {
			printBranch(isLast, nowNum);
			printf("┣━━━━━━");
			isLast[nowNum++] = (i == tree->keyNum);
			PrintBTree(tree->child[i], isLast, nowNum);
			nowNum--;
		}
		if (i != tree->keyNum) {
			printBranch(isLast, nowNum);
			printf("┣━ %d\n", tree->key[i + 1]);
			/*printf("┣━ %d━ %d\n", tree->key[i + 1], tree->rcd[i+1]->data);*/
		}
	}
}

/* 打印树枝 */
void printBranch(int isLast[], int nowNum) {
	for (int i = 0; i < nowNum; i++) {
		if (isLast[i]) printf(" ");
		else printf("┃");
		printf("      ");
	}
}


void InorderBTree(BTree T) {	//中序遍历文献，即按文献号从小到大顺序遍历
	if (T == NULL)return;
	int i;
	for (i = 0; i < T->keyNum; i++) {
		InorderBTree(T->child[i]);
		PrintOneBook(T->key[i + 1], T->rcd[i + 1]);
	}
	InorderBTree(T->child[i]);
}


void InorderBTree_author(BTree T, char* author) {	//根据著者输出所有他的文献
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


void PrintHead() {//表格头部格式
	printf("\n");
	printf("|********************************************文献基本信息*********************************************|\n");
	printf("|文献号|文献名                        |著者                |现存量  |总库存量|借阅者证|归还期限       |\n");
	printf("|------|------------------------------|--------------------|--------|--------|--------|---------------|\n");
}

void PrintOneBook(KeyType key,Record record) { //显示Book基本信息-
	if (record->information.head == NULL) {
		printf("|%-6d|%-30s|%-20s|%-8d|%-8d|%-8s|%-15s|\n", key, record->bookname, record->author,
			record->now_count, record->all_count,
			"暂无", "暂无");
	}
	else {
		printf("|%-6d|%-30s|%-20s|%-8d|%-8d|%-8d|%-15s|\n", key, record->bookname, record->author,
			record->now_count, record->all_count,
			record->information.head->next->IDnumber, record->information.head->next->deadline);
	}
}

void PrintTail() {//表格底部格式
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



