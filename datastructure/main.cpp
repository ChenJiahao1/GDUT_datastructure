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
	case 1://添加文献
		record = (Record)malloc(sizeof(Rcd));
		if (record == NULL)	break;
		record->information.head = NULL;
		record->information.len = 0;
		printf("请输入要入库的文献号：\n");
		fflush(stdin);
		scanf_s("%d", &key);
		getchar();
		SearchBTree(T, key, result);
		if (result.tag==0) {
			record = import_Record();
			InsertBTree(T, key, record);
			printf("展示B树如下：\n");
			TraverseBTree(T);
			printf("\n文献入库操作完成！\n");
			system("pause");
			system("cls");//清屏
			break;
		}
		else {//文献已存在，只增加库存
			printf("书库已有该文献记录，请输入增加的册数：\n");
			fflush(stdin);
			int increase=0;
			scanf_s("%d", &increase);
			result.pt->rcd[result.i]->now_count += increase;
			result.pt->rcd[result.i]->all_count += increase;
			printf("展示B树如下：\n");
			TraverseBTree(T);
			printf("文献入库操作完成！\n");
			system("pause");
			system("cls");//清屏
			break;
		}
	case 2://清空库存
		printf("请输入要删除文献的文献号：\n");
		fflush(stdin);
		scanf_s("%d", &key);
		SearchBTree(T, key, result);
		if (result.tag==1) {
			PrintOneBook(key, result.pt->rcd[result.i]);
			printf("\n您确认删除上面的文献<Y确认，其余按键返回主菜单>?\n");
			fflush(stdin);
			getchar();
			flag = getchar();
			if (flag == 'Y' || flag == 'y') {
				DestroyList(result.pt->rcd[result.i]->information);
				DeleteBTree(T, key);
				printf("\n清除完毕！\n删除后展示B树如下：\n");
				TraverseBTree(T);
			}
		}
		else {
			printf("\n书库不存在此文献，删除失败！\n");
		}
		system("pause");
		system("cls");//清屏
		break;
	case 3://借阅文献
		printf("请输入文献号:");
		fflush(stdin);
		if (!Borrow(T))
		{
			system("pause");
			system("cls");//清屏
			break;
		}
		printf("借阅文献成功！\n");
		printf("展示B树如下：\n");
		TraverseBTree(T);
		system("pause");
		system("cls");//清屏
		break;
	case 4://归还文献
		printf("\n请输入文献号：\n");
		fflush(stdin);
		scanf_s("%d", &key);
		printf("请输入您的借阅者证：\n");
		fflush(stdin);
		scanf_s("%d", &IDnumber);
		if (DeleteBorrower(T, key, IDnumber)) {
			printf("\n还书完成！");
		}
		system("pause");
		system("cls");//清屏
		break;
	case 5://总库存信息
		system("pause");
		system("cls");//清屏
		printf("\n\n总库存信息如下：\n");
		PrintALLBook(T);
		system("pause");
		system("cls");//清屏
		break;
	case 6://查找某种文献
		printf("请输入要查找文献的文献号：\n");
		scanf_s("%d", &key);
		SearchBTree(T, key, result);
		if (result.tag == 0) {
			printf("未找到该文献!\n");
			system("pause");
			system("cls");//清屏
			break;
		}
		PrintHead();
		PrintOneBook(key, result.pt->rcd[result.i]);
		PrintTail();
		system("pause");
		system("cls");//清屏
		break;
	case 7://输出某文献的借阅者信息
		printf("请输入要查找文献借阅者信息的文献号：\n");
		scanf_s("%d", &key);
		SearchBTree(T, key, result);
		if (result.tag==1) {
			if (result.pt->rcd[result.i]->information.head == NULL)
			{
				printf("暂无借阅者!");
				system("pause");
				system("cls");//清屏
				break;
			}
			ListTraverse(result.pt->rcd[result.i]->information);
		}
		else {
			printf("\n书库不存在此文献，查找失败！\n");
		}
		system("pause");
		system("cls");//清屏
		break;
	case 8://读取文献信息
		LoadBTree(T);
		system("pause");
		system("cls");
		break;
	case 9://查看某著者的所有文献
		printf("请输入要查询的著者：");
		author = (char*)malloc(sizeof(char) * AUTHOR_SIZE);
		scanf_s("%s", author, AUTHOR_SIZE);
		PrintAuthorBook(T, author);
		system("pause");
		system("cls");
		break;
	case 0:  //退出管理系统
		printf("\n您是否确认保存数据？<Y确认，其余按键将直接退出>\n");
		fflush(stdin);
		flag = getchar();
		if (flag == 'Y' || flag == 'y') {
			saveBTree(T);
			printf("保存完成，即将退出。");
		}
		DestroyBTree(T);
		exit(0);
	default:
		break;
	}
}
	return 0;
}
