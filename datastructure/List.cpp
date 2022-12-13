#include "B_Tree.h"
#include "Link_List.h"	

Status InitList(LinkList& L) { /* �ô�ͷ���Ŀյ�����*/
    Link p;
    p = (Link)malloc(sizeof(LNode)); /* ����ͷ��� */
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


Status DestroyList(LinkList& L) { /* ������������L��L���ٴ��� */
    Link p, q;
    if (L.head == NULL)    return OK;
    if (!ListEmpty(L)) { /* ���ǿձ� */
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

LNode* SearchList_num(LinkList L, int IDnumber) {   //���ݽ�����֤������Ϣ
    LNode* p;
    if (ListEmpty(L))	return NULL;
    p = L.head->next;
    while (p != NULL && p->IDnumber != IDnumber) p = p->next;
    return p;
}

Status ListEmpty(LinkList& L) { //�ѳ�ʼ����δ������
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
    if (L.head == NULL) {   //δ��ʼ��
        if (!InitList(L))
            return ERROR;
    }
    if (ListEmpty(L)) {     //�ѳ�ʼ����δ������
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
    if (flag == -1)     //q��p֮�����node
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


Status DeleteList(LinkList& L, int IDnumber) {    // ���ݽ�����֤ɾ��Ԫ��
    Link p, q;
    int flag = 0; 
    if (L.head==NULL)  return ERROR;    //δ��ʼ��
    if (ListEmpty(L))  return ERROR;    //�ձ�
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
    if (flag==0)   return ERROR;    //δ�ҵ�
    return OK;
}


void ListTraverse(LinkList L) { /* ������ʾ����Ԫ�� */
    Link p;
    printf("��������Ϣ���£�\n");
    if (ListEmpty(L))
        printf("��ϢΪ��!");
    else {
        printf("\n���� %d ��������\n\n", L.len);
        printf("|*******��������Ϣ*******|\n");
        printf("|������֤|�黹����       |\n");
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