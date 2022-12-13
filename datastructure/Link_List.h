#pragma once

#include "B_Tree.h"
#include<stdio.h>
#include<stdlib.h>
#include<math.h>	
#include<string.h>
#include<time.h>

typedef int Status;
typedef int DataType;

#define DEADLINE_SIZE 15

#define ERROR 0
#define OK 1
#define TRUE 1
#define FALSE 0

//�����СӦΪ all_count-now_count
//�������ڴ�Ž�������Ϣ--֤�����黹����
typedef struct LNode {
	int IDnumber;	//4λ֤����
	char* deadline;	//�黹����20xx-xx-xx
	struct LNode* next;
}LNode, *Link;
typedef struct LinkList{
	Link head;	//ָ�������ͷ���
	int len;	//��������
}LinkList;
//��ͷ���ĵ�����
//����������ڴ�С��������



/*�����������*/
Status InitList(LinkList& L);	//��ʼ��
Status ListEmpty(LinkList& L);	//�ж��Ƿ�Ϊ��
Status MakeList(LinkList& L);
Status DestroyList(LinkList& L);	//ɾ��ȫ����������Ϣ
LNode* SearchList_num(LinkList L, int IDnumber);	//���ݽ�����֤����
Status InsertList(LinkList& L, int IDnumber, char* deadline);	//������ӽ�����
Status DeleteList(LinkList& L, int IDnumber);	//����ɾ��������


//to_print
void ListTraverse(LinkList L);		//�Ա����ʽ��������׵����н�����

//cope_time
time_t get_time(int date_num[]);	
time_t convert_time(char* date);	//��char��ʱ��ת��Ϊtime_t
Status examine_time(char* date);	//���ʱ���ʽ20xx-xx-xx
Status compare_time(LNode* node1, LNode* node2, Status& flag);//date1>date2Ϊ1
struct tm* get_localtime(void);		//��ȡ����ʱ��

