#include "B_Tree.h"
#include "Link_List.h"	

void LoadBTree(BTree& T) {	
	FILE* fp = NULL;
	errno_t err;
	Result result;
	Record temp = NULL;
	KeyType key;
	if ((err = fopen_s(&fp, BOOKFILE, "r")) != 0) {
		printf("不能打开文献信息文件,请确认%s文件已放到盘根目录...", BOOKFILE);
		return;
	}
	printf("\n下面将从文件%s读入文献信息。", BOOKFILE);
	system("pause");
	system("cls");
	InitBtree(T);
	while (!feof(fp))	//读取到文件结尾
	{
		temp = (Record)malloc(sizeof(Rcd));
		char* bookname = (char*)malloc(sizeof(char) * BOOKNAME_SIZE);
		char* author = (char*)malloc(sizeof(char) * AUTHOR_SIZE);
		if (temp == NULL)	return;
		fscanf_s(fp, "%d %s %s %d %d", &key, 
			bookname, BOOKNAME_SIZE,
			author, AUTHOR_SIZE, 
			&temp->now_count, 
			&temp->all_count);
		temp->bookname = bookname;
		temp->author = author;
		temp->now_count = temp->all_count;
		temp->information.head = NULL;
		temp->information.len = 0;
		SearchBTree(T, key, result);
		if (!result.tag) {
			InsertBTree(T, key, temp);
			printf("\n\n插入下面的文献\n");
			PrintOneBook(key, temp);
			printf("\nB树状态\n");
			TraverseBTree(T);
			system("pause");
			system("cls");	//清屏
		}
	}
	fclose(fp);
	printf("\n\n读入的所有文献信息");
	PrintALLBook(T);	// 显示所有文献
	printf("\n文件文献信息读入完毕!下面从文件读入借阅者信息。\n");
	system("pause");
	system("cls");

	// **********************************************************************************

	if ((err = fopen_s(&fp, BORROWERFILE, "r")) != 0) {
		printf("不能打开文献信息文件,请确认%s文件已放到盘根目录...", BORROWERFILE);
		return;
	}
	printf("\n下面将从文件%s读入借阅者信息。", BORROWERFILE);
	system("pause");
	char* deadline;
	int IDnumber;
	while (!feof(fp)) {
		deadline = (char*)malloc(sizeof(char) * DEADLINE_SIZE);
		fscanf_s(fp, "%d %d %s", &key,
			&IDnumber,
			deadline, DEADLINE_SIZE);
		SearchBTree(T, key, result);
		if (result.tag != 1) {
			printf("未找到文献号为：%d的文献！\n", key);
			return;
		}
		if(result.pt->rcd[result.i]->information.head==NULL)	//若未初始化
			InitList(result.pt->rcd[result.i]->information);
		if(InsertList(result.pt->rcd[result.i]->information, IDnumber, deadline)!=0)
			result.pt->rcd[result.i]->now_count--;	//相应的现存量-1
	}
	fclose(fp);
	PrintALLBook(T);	// 显示所有文献
	printf("\n所有文献信息读入完毕!。\n");
}

void saveBTree(BTree T) {
	FILE* fp = NULL;
	errno_t err;
	if ((err = fopen_s(&fp, BOOKFILE, "w")) != 0) {
		printf("不能打开文献信息文件,请确认%s文件已放到盘根目录...", BOOKFILE);
		return;
	}
	printf("\n下面将文献信息写入%s文件。", BOOKFILE);
	system("pause");
	InordersaveBNode(T, fp);
	if ((err = fopen_s(&fp, BORROWERFILE, "w")) != 0) {
		printf("不能打开文献信息文件,请确认%s文件已放到盘根目录...", BORROWERFILE);
		return;
	}
	printf("\n下面将借阅者信息写入%s文件。", BORROWERFILE);
	InordersaveList(T, fp);
	system("pause");
}

void InordersaveBNode(BTree T, FILE*fp) {	//中序遍历文献，将B树结点保存到文件
	if (T == NULL)return;
	int i;
	for (i = 0; i < T->keyNum; i++) {
		InordersaveBNode(T->child[i], fp);
		saveBTNode(T, i, fp);
	}
	InordersaveBNode(T->child[i], fp);
}

void InordersaveList(BTree T, FILE* fp) {	//中序遍历文献，将借阅者信息保存到文件
	if (T == NULL)return;
	int i;
	for (i = 0; i < T->keyNum; i++) {
		InordersaveList(T->child[i],fp);
		saveList(T->rcd[i+1]->information, T->key[i+1], fp);
	}
	InordersaveList(T->child[i], fp);
}

void saveBTNode(BTNode* node, int i, FILE*fp) {
	fprintf_s(fp, "%d %s %s %d %d\n", node->key[i+1],
		node->rcd[i+1]->bookname,
		node->rcd[i+1]->author,
		node->rcd[i+1]->now_count,
		node->rcd[i+1]->all_count);
}

void saveList(LinkList L, KeyType key, FILE*fp) {
	Link p;
	if (L.head == NULL|| ListEmpty(L))
		return;
	else {
		p = L.head->next;
		while (p->next != NULL) {
			fprintf_s(fp, "%d %d %s\n", key, p->IDnumber, p->deadline);
			p = p->next;
		}
		fprintf_s(fp, "%d %d %s\n", key, p->IDnumber, p->deadline);
	}
}


int menu() {//菜单
	int choice;
	struct tm* local = get_localtime();
	printf("\n\n");
	printf("\t\t\t|**********************************************|\n");
	printf("\t\t\t|**********************************************|\n");
	printf("\t\t\t|______________________________________________|\n");
	printf("\t\t\t|                 文献管理系统                 |\n");
	printf("\t\t\t|                                              |\n");
	printf("\t\t\t|   1.添加文献           2.清除某文献库存      |\n");
	printf("\t\t\t|                                              |\n");
	printf("\t\t\t|   3.借阅文献           4.归还文献            |\n");
	printf("\t\t\t|                                              |\n");
	printf("\t\t\t|   5.查看全部文献       6.查看某文献信息      |\n");
	printf("\t\t\t|                                              |\n");
	printf("\t\t\t|   7.查看某书借阅者信息 8.读取文献信息        |\n");
	printf("\t\t\t|                                              |\n");
	printf("\t\t\t|   9.查看某著者的所有文献                     |\n");
	printf("\t\t\t|                                              |\n");
	printf("\t\t\t|   0.退出                                     |\n");
	printf("\t\t\t|______________________________________________|\n");
	printf("\t\t\t|**********************************************|\n");
	printf("\t\t\t|**********************************************|\n");
	printf("\t\t\t|      20计科(4)班          3120005057         |\n");
	printf("\t\t\t|                   陈嘉浩                     |\n");
	printf("\t\t\t|      当前时间:%d-%02d-%02d  %02d:%02d              |\n",
		local->tm_year+1900,local->tm_mon+1,local->tm_mday,local->tm_hour, local->tm_min);
	printf("\t\t\t|**********************************************|\n");
	do {
		printf("\t\t\t请选择功能（输入0-9任意一个数字）:");
		scanf_s("%d", &choice);
		daily(choice);
		getchar();	//避免非法输入死循环输出
	} while (choice < 0 || choice > 9);		//避免非法输入
	return choice;
}


void daily(int choice) {
	struct tm* local = get_localtime();
	if (local == NULL)	return;
	errno_t err;
	FILE* fp = NULL;
	if ((err = fopen_s(&fp, DAILYFILE, "a")) != 0) {
		printf("不能打开操作日志文件,请确认%s文件已放到盘根目录...", DAILYFILE);
		return;
	}
	fprintf_s(fp, "[%d-%02d-%02d %02d:%02d:%02d]\t", local->tm_year+1900,
		local->tm_mon+1,
		local->tm_mday,
		local->tm_hour,
		local->tm_min,
		local->tm_sec);
	switch (choice) {
	case 1:
		fprintf_s(fp, "操作%d\t添加文献\n", choice);
		break;
	case 2:
		fprintf_s(fp, "操作%d\t清除某文献库存\n", choice);
		break;
	case 3:
		fprintf_s(fp, "操作%d\t借阅文献\n", choice);
		break;
	case 4:
		fprintf_s(fp, "操作%d\t归还文献\n", choice);
		break;
	case 5:
		fprintf_s(fp, "操作%d\t查看全部文献\n", choice);
		break;
	case 6:
		fprintf_s(fp, "操作%d\t查看某文献信息\n", choice);
		break;
	case 7:
		fprintf_s(fp, "操作%d\t查看某书借阅者信息\n", choice);
		break;
	case 8:
		fprintf_s(fp, "操作%d\t读取文献信息\n", choice);
		break;
	case 9:
		fprintf_s(fp, "操作%d\t查看某著者的所有文献\n", choice);
		break;
	case 0:
		fprintf_s(fp, "操作%d\t退出\n\n\n", choice);
		break;
	default:
		break;
	}
	fclose(fp);
}