#include "B_Tree.h"
#include "Link_List.h"	

Status InitList(LinkList& L) { /* 置带头结点的空单链表*/
    Link p;
    p = (Link)malloc(sizeof(LNode)); /* 生成头结点 */
    if (p) {
        p->IDnumber = -1;
        p->next = NULL;
        p->deadline = NULL;
        L.head = p;
        L.len = 0;
        return OK;
    }
    else
        return OVERFLOW;
}


Status DestroyList(LinkList& L) { /* 销毁线性链表L，L不再存在 */
    Link p, q;
    if (L.head == NULL)    return OK;
    if (!ListEmpty(L)) { /* 不是空表 */
        p = q = L.head->next;
        L.head->next = NULL;
        while (p ->next!=NULL) {
            p = p->next;
            free(q);
            q = p;
        }
        free(q);
    }
    free(L.head);
    L.head= NULL;
    L.len = 0;
    return OK;
}

LNode* SearchList_num(LinkList L, int IDnumber) {   //根据借阅者证查找信息
    LNode* p;
    if (ListEmpty(L))	return NULL;
    p = L.head->next;
    while (p != NULL && p->IDnumber != IDnumber) p = p->next;
    return p;
}

Status ListEmpty(LinkList& L) { //已初始化但未插入结点
    if (L.head->next == NULL)	return TRUE;
    return FALSE;
}

Status InsertList(LinkList& L, int IDnumber, char* deadline) {      //
    int j = 0;
    Link node, p, q;
    Status flag = 0;
    node = (Link)malloc(sizeof(LNode));
    if (node == NULL) return OVERFLOW;
    node->IDnumber = IDnumber;
    node->deadline = deadline;
    if (!compare_time(node, node, flag)) {
        return ERROR;
    }
    if (L.head == NULL) {   //未初始化
        if (!InitList(L))
            return ERROR;
    }
    if (ListEmpty(L)) {     //已初始化但未插入结点
        L.head->next = node;
        node->next = NULL;
        L.len++;
        return OK;
    }
    p = L.head;
    q = p;
    while (flag!=-1 && p->next != NULL) {   
        q = p;
        p = p->next;
        compare_time(node, p, flag);
    }
    if (flag == -1)     //q与p之间插入node
    {
        q->next = node;
        node->next = p;
    }
    else {      
        p->next = node;
        node->next = NULL;
    }
    L.len++;
    return OK;
}


Status DeleteList(LinkList& L, int IDnumber) {    // 根据借阅者证删除元素
    Link p, q;
    int flag = 0; 
    if (L.head==NULL)  return ERROR;    //未初始化
    if (ListEmpty(L))  return ERROR;    //空表
    p = q = L.head;
    while (p->next != NULL) {
        q = p;
        p = p->next;
        if (p->IDnumber == IDnumber) {
            flag = 1;
            q->next = p->next;
            free(p);
            p = NULL;
            L.len--;
            return OK;
        }
    }
    if (flag==0)   return ERROR;    //未找到
    return OK;
}


void ListTraverse(LinkList L) { /* 依次显示表中元素 */
    Link p;
    printf("借阅者信息如下：\n");
    if (ListEmpty(L))
        printf("信息为空!");
    else {
        printf("\n共有 %d 名借阅者\n\n", L.len);
        printf("|*******借阅者信息*******|\n");
        printf("|借阅者证|归还期限       |\n");
        printf("|--------|---------------|\n");
        p = L.head->next;
        while (p->next != NULL) {
            printf("|%-8d|%-15s|\n", p->IDnumber, p->deadline);
            p = p->next;
        }
        printf("|%-8d|%-15s|\n", p->IDnumber, p->deadline);
        printf("|--------|---------------|\n");
    }
    printf("\n");
}


Status MakeList(LinkList& L){
    int num, IDnumber;
    char* deadline;
    if (!InitList(L)) return ERROR;
    scanf_s("%d", &num);
    for (int i = 1; i <= num; i++) {
        deadline = (char*)malloc(sizeof(char) * 15);
        if (deadline == NULL)  return OVERFLOW;
        scanf_s("%d", &IDnumber);
        scanf_s("%s", deadline, 15);
        deadline[4] = '-';
        deadline[7] = '-';
        if (!InsertList(L, IDnumber, deadline)) {
            num++;
        }
    }
    return OK;
}