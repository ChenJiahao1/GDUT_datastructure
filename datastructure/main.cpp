#include "B_Tree.h"
#include "Link_List.h"	

int main(void) {
	BTree T = NULL;
	Result result;
	Record record = NULL;
	char flag;
	int key, IDnumber;
	char* author = NULL;
	//Welcome();
	for(;;){
	switch (menu())
	{
	case 1://�������
		record = (Record)malloc(sizeof(Rcd));
		if (record == NULL)	break;
		record->information.head = NULL;
		record->information.len = 0;
		printf("������Ҫ�������׺ţ�\n");
		fflush(stdin);
		scanf_s("%d", &key);
		getchar();
		SearchBTree(T, key, result);
		if (result.tag==0) {
			record = import_Record();
			InsertBTree(T, key, record);
			printf("չʾB�����£�\n");
			TraverseBTree(T);
			printf("\n������������ɣ�\n");
			system("pause");
			system("cls");//����
			break;
		}
		else {//�����Ѵ��ڣ�ֻ���ӿ��
			printf("������и����׼�¼�����������ӵĲ�����\n");
			fflush(stdin);
			int increase=0;
			scanf_s("%d", &increase);
			result.pt->rcd[result.i]->now_count += increase;
			result.pt->rcd[result.i]->all_count += increase;
			printf("չʾB�����£�\n");
			TraverseBTree(T);
			printf("������������ɣ�\n");
			system("pause");
			system("cls");//����
			break;
		}
	case 2://��տ��
		printf("������Ҫɾ�����׵����׺ţ�\n");
		fflush(stdin);
		scanf_s("%d", &key);
		SearchBTree(T, key, result);
		if (result.tag==1) {
			PrintOneBook(key, result.pt->rcd[result.i]);
			printf("\n��ȷ��ɾ�����������<Yȷ�ϣ����ఴ���������˵�>?\n");
			fflush(stdin);
			getchar();
			flag = getchar();
			if (flag == 'Y' || flag == 'y') {
				DestroyList(result.pt->rcd[result.i]->information);
				DeleteBTree(T, key);
				printf("\n�����ϣ�\nɾ����չʾB�����£�\n");
				TraverseBTree(T);
			}
		}
		else {
			printf("\n��ⲻ���ڴ����ף�ɾ��ʧ�ܣ�\n");
		}
		system("pause");
		system("cls");//����
		break;
	case 3://��������
		printf("���������׺�:");
		fflush(stdin);
		if (!Borrow(T))
		{
			system("pause");
			system("cls");//����
			break;
		}
		printf("�������׳ɹ���\n");
		printf("չʾB�����£�\n");
		TraverseBTree(T);
		system("pause");
		system("cls");//����
		break;
	case 4://�黹����
		printf("\n���������׺ţ�\n");
		fflush(stdin);
		scanf_s("%d", &key);
		printf("���������Ľ�����֤��\n");
		fflush(stdin);
		scanf_s("%d", &IDnumber);
		if (DeleteBorrower(T, key, IDnumber)) {
			printf("\n������ɣ�");
		}
		system("pause");
		system("cls");//����
		break;
	case 5://�ܿ����Ϣ
		system("pause");
		system("cls");//����
		printf("\n\n�ܿ����Ϣ���£�\n");
		PrintALLBook(T);
		system("pause");
		system("cls");//����
		break;
	case 6://����ĳ������
		printf("������Ҫ�������׵����׺ţ�\n");
		scanf_s("%d", &key);
		SearchBTree(T, key, result);
		if (result.tag == 0) {
			printf("δ�ҵ�������!\n");
			system("pause");
			system("cls");//����
			break;
		}
		PrintHead();
		PrintOneBook(key, result.pt->rcd[result.i]);
		PrintTail();
		system("pause");
		system("cls");//����
		break;
	case 7://���ĳ���׵Ľ�������Ϣ
		printf("������Ҫ�������׽�������Ϣ�����׺ţ�\n");
		scanf_s("%d", &key);
		SearchBTree(T, key, result);
		if (result.tag==1) {
			if (result.pt->rcd[result.i]->information.head == NULL)
			{
				printf("���޽�����!");
				system("pause");
				system("cls");//����
				break;
			}
			ListTraverse(result.pt->rcd[result.i]->information);
		}
		else {
			printf("\n��ⲻ���ڴ����ף�����ʧ�ܣ�\n");
		}
		system("pause");
		system("cls");//����
		break;
	case 8://��ȡ������Ϣ
		LoadBTree(T);
		system("pause");
		system("cls");
		break;
	case 9://�鿴ĳ���ߵ���������
		printf("������Ҫ��ѯ�����ߣ�");
		author = (char*)malloc(sizeof(char) * AUTHOR_SIZE);
		scanf_s("%s", author, AUTHOR_SIZE);
		PrintAuthorBook(T, author);
		system("pause");
		system("cls");
		break;
	case 0:  //�˳�����ϵͳ
		printf("\n���Ƿ�ȷ�ϱ������ݣ�<Yȷ�ϣ����ఴ����ֱ���˳�>\n");
		fflush(stdin);
		flag = getchar();
		if (flag == 'Y' || flag == 'y') {
			saveBTree(T);
			printf("������ɣ������˳���");
		}
		DestroyBTree(T);
		exit(0);
	default:
		break;
	}
}
	return 0;
}
