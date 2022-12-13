#include "B_Tree.h"
#include "Link_List.h"	

void LoadBTree(BTree& T) {	
	FILE* fp = NULL;
	errno_t err;
	Result result;
	Record temp = NULL;
	KeyType key;
	if ((err = fopen_s(&fp, BOOKFILE, "r")) != 0) {
		printf("���ܴ�������Ϣ�ļ�,��ȷ��%s�ļ��ѷŵ��̸�Ŀ¼...", BOOKFILE);
		return;
	}
	printf("\n���潫���ļ�%s����������Ϣ��", BOOKFILE);
	system("pause");
	system("cls");
	InitBtree(T);
	while (!feof(fp))	//��ȡ���ļ���β
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
			printf("\n\n�������������\n");
			PrintOneBook(key, temp);
			printf("\nB��״̬\n");
			TraverseBTree(T);
			system("pause");
			system("cls");	//����
		}
	}
	fclose(fp);
	printf("\n\n���������������Ϣ");
	PrintALLBook(T);	// ��ʾ��������
	printf("\n�ļ�������Ϣ�������!������ļ������������Ϣ��\n");
	system("pause");
	system("cls");

	// **********************************************************************************

	if ((err = fopen_s(&fp, BORROWERFILE, "r")) != 0) {
		printf("���ܴ�������Ϣ�ļ�,��ȷ��%s�ļ��ѷŵ��̸�Ŀ¼...", BORROWERFILE);
		return;
	}
	printf("\n���潫���ļ�%s�����������Ϣ��", BORROWERFILE);
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
			printf("δ�ҵ����׺�Ϊ��%d�����ף�\n", key);
			return;
		}
		if(result.pt->rcd[result.i]->information.head==NULL)	//��δ��ʼ��
			InitList(result.pt->rcd[result.i]->information);
		if(InsertList(result.pt->rcd[result.i]->information, IDnumber, deadline)!=0)
			result.pt->rcd[result.i]->now_count--;	//��Ӧ���ִ���-1
	}
	fclose(fp);
	PrintALLBook(T);	// ��ʾ��������
	printf("\n����������Ϣ�������!��\n");
}

void saveBTree(BTree T) {
	FILE* fp = NULL;
	errno_t err;
	if ((err = fopen_s(&fp, BOOKFILE, "w")) != 0) {
		printf("���ܴ�������Ϣ�ļ�,��ȷ��%s�ļ��ѷŵ��̸�Ŀ¼...", BOOKFILE);
		return;
	}
	printf("\n���潫������Ϣд��%s�ļ���", BOOKFILE);
	system("pause");
	InordersaveBNode(T, fp);
	if ((err = fopen_s(&fp, BORROWERFILE, "w")) != 0) {
		printf("���ܴ�������Ϣ�ļ�,��ȷ��%s�ļ��ѷŵ��̸�Ŀ¼...", BORROWERFILE);
		return;
	}
	printf("\n���潫��������Ϣд��%s�ļ���", BORROWERFILE);
	InordersaveList(T, fp);
	system("pause");
}

void InordersaveBNode(BTree T, FILE*fp) {	//����������ף���B����㱣�浽�ļ�
	if (T == NULL)return;
	int i;
	for (i = 0; i < T->keyNum; i++) {
		InordersaveBNode(T->child[i], fp);
		saveBTNode(T, i, fp);
	}
	InordersaveBNode(T->child[i], fp);
}

void InordersaveList(BTree T, FILE* fp) {	//����������ף�����������Ϣ���浽�ļ�
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


int menu() {//�˵�
	int choice;
	struct tm* local = get_localtime();
	printf("\n\n");
	printf("\t\t\t|**********************************************|\n");
	printf("\t\t\t|**********************************************|\n");
	printf("\t\t\t|______________________________________________|\n");
	printf("\t\t\t|                 ���׹���ϵͳ                 |\n");
	printf("\t\t\t|                                              |\n");
	printf("\t\t\t|   1.�������           2.���ĳ���׿��      |\n");
	printf("\t\t\t|                                              |\n");
	printf("\t\t\t|   3.��������           4.�黹����            |\n");
	printf("\t\t\t|                                              |\n");
	printf("\t\t\t|   5.�鿴ȫ������       6.�鿴ĳ������Ϣ      |\n");
	printf("\t\t\t|                                              |\n");
	printf("\t\t\t|   7.�鿴ĳ���������Ϣ 8.��ȡ������Ϣ        |\n");
	printf("\t\t\t|                                              |\n");
	printf("\t\t\t|   9.�鿴ĳ���ߵ���������                     |\n");
	printf("\t\t\t|                                              |\n");
	printf("\t\t\t|   0.�˳�                                     |\n");
	printf("\t\t\t|______________________________________________|\n");
	printf("\t\t\t|**********************************************|\n");
	printf("\t\t\t|**********************************************|\n");
	printf("\t\t\t|      20�ƿ�(4)��          3120005057         |\n");
	printf("\t\t\t|                   �¼κ�                     |\n");
	printf("\t\t\t|      ��ǰʱ��:%d-%02d-%02d  %02d:%02d              |\n",
		local->tm_year+1900,local->tm_mon+1,local->tm_mday,local->tm_hour, local->tm_min);
	printf("\t\t\t|**********************************************|\n");
	do {
		printf("\t\t\t��ѡ���ܣ�����0-9����һ�����֣�:");
		scanf_s("%d", &choice);
		daily(choice);
		getchar();	//����Ƿ�������ѭ�����
	} while (choice < 0 || choice > 9);		//����Ƿ�����
	return choice;
}


void daily(int choice) {
	struct tm* local = get_localtime();
	if (local == NULL)	return;
	errno_t err;
	FILE* fp = NULL;
	if ((err = fopen_s(&fp, DAILYFILE, "a")) != 0) {
		printf("���ܴ򿪲�����־�ļ�,��ȷ��%s�ļ��ѷŵ��̸�Ŀ¼...", DAILYFILE);
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
		fprintf_s(fp, "����%d\t�������\n", choice);
		break;
	case 2:
		fprintf_s(fp, "����%d\t���ĳ���׿��\n", choice);
		break;
	case 3:
		fprintf_s(fp, "����%d\t��������\n", choice);
		break;
	case 4:
		fprintf_s(fp, "����%d\t�黹����\n", choice);
		break;
	case 5:
		fprintf_s(fp, "����%d\t�鿴ȫ������\n", choice);
		break;
	case 6:
		fprintf_s(fp, "����%d\t�鿴ĳ������Ϣ\n", choice);
		break;
	case 7:
		fprintf_s(fp, "����%d\t�鿴ĳ���������Ϣ\n", choice);
		break;
	case 8:
		fprintf_s(fp, "����%d\t��ȡ������Ϣ\n", choice);
		break;
	case 9:
		fprintf_s(fp, "����%d\t�鿴ĳ���ߵ���������\n", choice);
		break;
	case 0:
		fprintf_s(fp, "����%d\t�˳�\n\n\n", choice);
		break;
	default:
		break;
	}
	fclose(fp);
}