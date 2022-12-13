#pragma once

#include "Link_List.h"	
#include<stdio.h>
#include<stdlib.h>
#include<math.h>	
#include<string.h>
#include <windows.h>
#include <corecrt.h>
#include<errno.h>

/* B ������ */
#define M 4

#define BOOKFILE "bookinfo.dat"
#define BORROWERFILE "borrowerinfo.dat"
#define DAILYFILE "daily.dat"

/* B ���ؼ������Сֵ�Լ��м�ֵ */
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
/* ��¼���� */
typedef struct Rcd {
	char* bookname;	//������bookname[30]
	char* author;	//����author[20]
	int now_count;		// �ִ���
	int all_count;		//�ܿ����
	LinkList information;	//��������Ϣ
} Rcd, * Record;


/* B ���ṹ�� */
typedef struct BTNode {
	int keyNum;					// ����йؼ��ָ����������Ĵ�С
	KeyType key[M + 1];			// ���׺����飬0 �ŵ�Ԫδ��	4λ���׺�
	Record rcd[M + 1];			// ��¼ָ�����飬0 �ŵ�Ԫδ��, ÿ��key��Ӧһ��rcd��rcd�൱��һ������
	struct BTNode* parent;		// ָ��˫�׽��
	struct BTNode* child[M + 1];// ����ָ�����飬0 ����ʹ��
} BTNode, * BTree;


/* ������� */
typedef struct Result {
	BTree pt;	// �ҵ��Ľ��
	int i;		// �ڽ���еĹؼ���λ��
	int tag;	// �Ƿ��ҵ���
} Result;


/* ͨ�ø����ӿ� */
Record import_Record(void);		//��������rcd
Result getResult(int i, int tag, BTree pt);	// ���һ�����ֵ
void Move(BTree& a, int index_a, BTree& b, int index_b);	//��b���index_b��ֵ��ֵ��a���index_a
Status InitBtree(BTree& root);		// ��ʼ�� B ��

/* B ���ӿ� */
Status MakeBTree(BTree& t, int num);		// ���� B �� 
void SearchBTree(BTree t, KeyType k, Result& result);	// �� B ��ִ�в��Ҳ���
void InsertBTree(BTree& t, KeyType key, Record rcd);	// �� B ��ִ�в������
Status DeleteBTree(BTree& tree, KeyType key);	// �� B ��ִ��ɾ������
Status UpdateBTree(BTree tree, KeyType key, Record rcd);	// �� B ���йؼ���Ϊ key �Ľ���¼�������µļ�¼
void DestroyBTree(BTree& T);	//����B��

/* B �������ӿ� */
int Search(BTree node, KeyType key);	// Ѱ�� key �� node ���ڽ���е�λ��
void Insert(BTree& q, int i, KeyType key, Record rcd, BTree newNode);	// ���¼�¼ rcd ���뵽��� node �ĵ� i ��λ�ã�ͬʱ�����ӽڵ� newNode ��Ϊ��̺���
Status split(BTree& q, BTree& newNode);	// �� node �����м���ѳ������֣�ǰ�벿������ԭλ����벿�ֽ��� newNode ��ָ��ԭ����˫��
Status newRoot(BTree& t, BTree child0, BTree child1, KeyType key, Record rcd);	// ����һ���¸�

void DeleteBTNode(BTree& p, int i, BTree& T);
Status Successor(BTree& p, int i);	// �ҵ�������㣬�������滻
Status Remove(BTree& p, int i);	// ��ָ������е� i ����¼�Ƴ�
Status Restore(BTree& p, BTree& T);		// ���ĳ��������һ�� B ��
Status Combine(BTree& father, int j);	

/*borrow*/
Status Borrow(BTree t);		//��������
Status DeleteBorrower(BTree T, KeyType key, int IDnumber);		//�������׺��Լ�������֤����

/*to_print*/
void TraverseBTree(BTree tree);					// ��ӡ B ��
int CountKeyNum(BTree tree);	// ������������ϼ�¼�������ܺ�
void PrintBTree(BTree tree, int isLast[], int nowNum);	// �ݹ��ӡ����
void printBranch(int isLast[], int nowNum);	// ��ӡ��֦

void InorderBTree(BTree T);	//�������B�����Ա�����ʽ���
void PrintHead();
void PrintOneBook(KeyType key, Record record);
void PrintTail();
void PrintALLBook(BTree T);		

void InorderBTree_author(BTree T, char* author);	//�����������������������
void PrintAuthorBook(BTree T, char* author);

/*����*/
int menu();		//�˵�


/*file_operation*/
void LoadBTree(BTree& T);	//���ļ�������B��
void saveBTree(BTree T);	//��B�����ݱ������ļ�
void InordersaveBNode(BTree T, FILE* fp);
void InordersaveList(BTree T, FILE* fp);
void saveBTNode(BTNode* node, int i, FILE* fp);
void saveList(LinkList L, KeyType key, FILE* fp);

void daily(int choice);		//��¼��������־