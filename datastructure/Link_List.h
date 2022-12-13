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

//链表大小应为 all_count-now_count
//链表用于存放借阅者信息--证件，归还期限
typedef struct LNode {
	int IDnumber;	//4位证件号
	char* deadline;	//归还期限20xx-xx-xx
	struct LNode* next;
}LNode, *Link;
typedef struct LinkList{
	Link head;	//指向链表的头结点
	int len;	//借阅人数
}LinkList;
//带头结点的单链表
//链表根据日期从小到大排序



/*链表基础操作*/
Status InitList(LinkList& L);	//初始化
Status ListEmpty(LinkList& L);	//判断是否为空
Status MakeList(LinkList& L);
Status DestroyList(LinkList& L);	//删除全部借阅者信息
LNode* SearchList_num(LinkList L, int IDnumber);	//根据借阅者证搜索
Status InsertList(LinkList& L, int IDnumber, char* deadline);	//用于添加借阅者
Status DeleteList(LinkList& L, int IDnumber);	//用于删除借阅者


//to_print
void ListTraverse(LinkList L);		//以表格形式输出该文献的所有借阅者

//cope_time
time_t get_time(int date_num[]);	
time_t convert_time(char* date);	//将char型时间转化为time_t
Status examine_time(char* date);	//检查时间格式20xx-xx-xx
Status compare_time(LNode* node1, LNode* node2, Status& flag);//date1>date2为1
struct tm* get_localtime(void);		//获取本地时间

