#pragma once

#include "Link_List.h"	
#include<stdio.h>
#include<stdlib.h>
#include<math.h>	
#include<string.h>
#include <windows.h>
#include <corecrt.h>
#include<errno.h>

/* B 树阶数 */
#define M 4

#define BOOKFILE "bookinfo.dat"
#define BORROWERFILE "borrowerinfo.dat"
#define DAILYFILE "daily.dat"

/* B 树关键最大最小值以及中间值 */
#define MAX_KEY (M-1)
#define MIN_KEY ((M+1)/2-1)
#define MID_KEY ((M+1)/2)

typedef int Status;
typedef int KeyType;


#define ERROR 0
#define OK 1
#define TRUE 1
#define FALSE 0


#define BOOKNAME_SIZE 30
#define AUTHOR_SIZE 20
/* 记录类型 */
typedef struct Rcd {
	char* bookname;	//文献名bookname[30]
	char* author;	//著者author[20]
	int now_count;		// 现存量
	int all_count;		//总库存量
	LinkList information;	//借阅者信息
} Rcd, * Record;


/* B 树结构体 */
typedef struct BTNode {
	int keyNum;					// 结点中关键字个数，即结点的大小
	KeyType key[M + 1];			// 文献号数组，0 号单元未用	4位文献号
	Record rcd[M + 1];			// 记录指针数组，0 号单元未用, 每个key对应一个rcd，rcd相当于一个数组
	struct BTNode* parent;		// 指向双亲结点
	struct BTNode* child[M + 1];// 子树指针数组，0 号有使用
} BTNode, * BTree;


/* 结果类型 */
typedef struct Result {
	BTree pt;	// 找到的结点
	int i;		// 在结点中的关键字位序
	int tag;	// 是否找到了
} Result;


/* 通用辅助接口 */
Record import_Record(void);		//方便输入rcd
Result getResult(int i, int tag, BTree pt);	// 获得一个结果值
void Move(BTree& a, int index_a, BTree& b, int index_b);	//把b结点index_b的值赋值给a结点index_a
Status InitBtree(BTree& root);		// 初始化 B 树

/* B 树接口 */
Status MakeBTree(BTree& t, int num);		// 构建 B 树 
void SearchBTree(BTree t, KeyType k, Result& result);	// 对 B 树执行查找操作
void InsertBTree(BTree& t, KeyType key, Record rcd);	// 对 B 树执行插入操作
Status DeleteBTree(BTree& tree, KeyType key);	// 对 B 树执行删除操作
Status UpdateBTree(BTree tree, KeyType key, Record rcd);	// 将 B 树中关键字为 key 的结点记录更换成新的记录
void DestroyBTree(BTree& T);	//销毁B树

/* B 树辅助接口 */
int Search(BTree node, KeyType key);	// 寻找 key 在 node 所在结点中的位置
void Insert(BTree& q, int i, KeyType key, Record rcd, BTree newNode);	// 将新记录 rcd 插入到结点 node 的第 i 个位置，同时将新子节点 newNode 作为后继孩子
Status split(BTree& q, BTree& newNode);	// 将 node 结点从中间分裂成两部分，前半部分留在原位，后半部分进入 newNode 并指向原结点的双亲
Status newRoot(BTree& t, BTree child0, BTree child1, KeyType key, Record rcd);	// 生成一个新根

void DeleteBTNode(BTree& p, int i, BTree& T);
Status Successor(BTree& p, int i);	// 找到后驱结点，并进行替换
Status Remove(BTree& p, int i);	// 将指定结点中第 i 个记录移除
Status Restore(BTree& p, BTree& T);		// 针对某个结点调整一颗 B 树
Status Combine(BTree& father, int j);	

/*borrow*/
Status Borrow(BTree t);		//借阅文献
Status DeleteBorrower(BTree T, KeyType key, int IDnumber);		//根据文献号以及借阅者证还书

/*to_print*/
void TraverseBTree(BTree tree);					// 打印 B 树
int CountKeyNum(BTree tree);	// 计算出整棵树上记录条数的总和
void PrintBTree(BTree tree, int isLast[], int nowNum);	// 递归打印树形
void printBranch(int isLast[], int nowNum);	// 打印树枝

void InorderBTree(BTree T);	//中序遍历B树，以表格的形式输出
void PrintHead();
void PrintOneBook(KeyType key, Record record);
void PrintTail();
void PrintALLBook(BTree T);		

void InorderBTree_author(BTree T, char* author);	//根据著者输出所有他的文献
void PrintAuthorBook(BTree T, char* author);

/*界面*/
int menu();		//菜单


/*file_operation*/
void LoadBTree(BTree& T);	//从文件中载入B树
void saveBTree(BTree T);	//将B树数据保存至文件
void InordersaveBNode(BTree T, FILE* fp);
void InordersaveList(BTree T, FILE* fp);
void saveBTNode(BTNode* node, int i, FILE* fp);
void saveList(LinkList L, KeyType key, FILE* fp);

void daily(int choice);		//记录操作的日志