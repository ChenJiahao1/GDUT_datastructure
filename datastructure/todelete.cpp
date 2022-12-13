#include "B_Tree.h"

Status Successor(BTree& p, int i) {	//直接后驱
    if (p == NULL)	return ERROR;
    if (p->child[i] == NULL)	return ERROR;
    BTree node = p->child[i];
    while (node->child[0] != NULL) node = node->child[0];

    p->key[i] = node->key[1];
    p->rcd[i] = node->rcd[1];

    p = node;
    return OK;
}


Status Remove(BTree& p, int i) {
    int j;
    if (p == NULL)return ERROR;
    for (j = i; j <= p->keyNum; j++) {
        p->key[j] = p->key[j + 1];
        p->rcd[j] = p->rcd[j + 1];
    }
    p->key[p->keyNum] = 0;
    p->rcd[p->keyNum] = NULL;
    p->keyNum--;
    return OK;
}


Status Moveleft(BTree& father, int j) {     //j是father的child数组指向被调整结点的下标
    int i;
    BTNode* p;
    BTNode* L_bro;
    p = father->child[j];
    L_bro = father->child[j - 1];
    for (i = p->keyNum; i >= 0; i--) {  
        p->key[i + 1] = p->key[i];
        p->child[i + 1] = p->child[i];
        p->rcd[i+1] = p->rcd[i];
        //Move(p, i+1, p, i);
    }
    p->key[1] = father->key[j];
    p->rcd[1] = father->rcd[j];
    //if (L_bro->keyNum < 0) p->child[0] = NULL;
    //else p->child[0] = L_bro->child[L_bro->keyNum];
    p->child[0] = L_bro->child[L_bro->keyNum];
    p->keyNum++;

    if (L_bro->child[L_bro->keyNum]) {
        L_bro->child[L_bro->keyNum]->parent = p;
    }

    father->key[j] = L_bro->key[L_bro->keyNum];
    father->rcd[j] = L_bro->rcd[L_bro->keyNum];

    L_bro->child[L_bro->keyNum] = NULL;
    L_bro->rcd[L_bro->keyNum] = NULL;
    L_bro->key[L_bro->keyNum] = 0;
    L_bro->keyNum--;
    return OK;
}


Status Moveright(BTree& father, int j) {
    int i;
    BTNode* p;
    BTNode* R_bro;
    p = father->child[j];
    R_bro = father->child[j + 1];

    if (p->keyNum == 0)
    {
        p->key[1] = father->key[j + 1];
        p->rcd[1] = father->rcd[j + 1];
        p->child[1] = R_bro->child[0];
    }
    else {
        p->key[p->keyNum] = father->key[j + 1];
        p->rcd[p->keyNum] = father->rcd[j + 1];
        p->child[p->keyNum] = R_bro->child[0];
    }
    
    p->keyNum++;

    if (R_bro->child[0])
        R_bro->child[0]->parent = p;
    
    father->key[j + 1] = R_bro->key[1];
    father->rcd[j + 1] = R_bro->rcd[1];

    for (i = 1; i <= R_bro->keyNum; i++) {
        R_bro->key[i - 1] = R_bro->key[i];
        R_bro->child[i - 1] = R_bro->child[i];
        R_bro->rcd[i - 1] = R_bro->rcd[i];
    }
    R_bro->rcd[R_bro->keyNum] = NULL;
    R_bro->key[R_bro->keyNum] = 0;
    R_bro->child[R_bro->keyNum] = NULL;
    R_bro->rcd[0] = NULL;
    R_bro->key[0] = 0;
    R_bro->keyNum--;
    return OK;
}


Status Combine(BTree& father, int j) {
    int i;
    BTNode* p;
    BTNode* L_bro;
    BTNode* R_bro;
    p = father->child[j];
    if (j > 0 && j <= father->keyNum) {     //把p结点结合至左兄弟
        L_bro = father->child[j - 1];

        L_bro->keyNum++;
        L_bro->key[L_bro->keyNum] = father->key[j];
        L_bro->rcd[L_bro->keyNum] = father->rcd[j];
        L_bro->child[L_bro->keyNum] = p->child[0];

        if (p->child[0]) p->child[0]->parent = L_bro;

        i = 1;
        for (; i <= p->keyNum; i++) {
            L_bro->keyNum++;

            L_bro->key[L_bro->keyNum] = p->key[i];
            L_bro->rcd[L_bro->keyNum] = p->rcd[i];
            L_bro->child[L_bro->keyNum] = p->child[i];
            if (p->child[i]) p->child[i]->parent = L_bro;
        }
        
        father->child[j] = NULL;    //释放结点
        free(p);
        p = NULL;

        for (i = j; i < father->keyNum; i++) {
            father->key[i] = father->key[i + 1];
            father->rcd[i] = father->rcd[i + 1];
            father->child[i] = father->child[i + 1];
        }
        father->key[father->keyNum] = 0;
        father->rcd[father->keyNum] = NULL;
        father->child[father->keyNum] = NULL;
        father->keyNum--;
    }
    else {  //把右兄弟结合至p结点
        R_bro = father->child[j + 1];
        p->keyNum++;

        p->key[p->keyNum] = father->key[j + 1];
        p->rcd[p->keyNum] = father->rcd[j + 1];
        p->child[p->keyNum] = R_bro->child[0];
        if (R_bro->child[0]) R_bro->child[0]->parent = p;
        i = 1;
        for (; i <= R_bro->keyNum; i++) {
            p->keyNum++;
            p->key[p->keyNum] = R_bro->key[i];
            p->rcd[p->keyNum] = R_bro->rcd[i];
            p->child[p->keyNum] = R_bro->child[i];
            if (R_bro->child[i]) R_bro->child[i]->parent = p;
        }
        father->child[j + 1] = NULL;
        free(R_bro);
        R_bro = NULL;

        for (i = j + 1; i < father->keyNum; i++) {
            father->key[i] = father->key[i + 1];
            father->rcd[i] = father->rcd[i + 1];
            father->child[i] = father->child[i + 1];
        }
        father->key[father->keyNum] = 0;
        father->rcd[father->keyNum] = NULL;
        father->child[i] = NULL;
        father->keyNum--;
    }
    return OK;
}


Status Restore(BTree& p, BTree& T) {
    BTNode* father;
    father = p->parent;
    if (father == NULL) {
        if (p->keyNum == 0) {
            T = p->child[0];
            if (T) {
                T->parent = NULL;
            }
            free(p);
        }
        return OK;
    }
    int j = 0;  //j是father的child数组指向被调整结点的下标
    Status flag = 0;   //是否调整成功
    for (j = 0; j <= father->keyNum;) {
        if (p == father->child[j]) {
            break;
        }
        j++;
    }

    if (j > 0 && flag == 0) {
        if (father->child[j - 1]->keyNum > MIN_KEY) {   //找左兄弟
            Moveleft(father, j);
            flag = 1;
        }
        else flag = 0;
    }
    if (j < father->keyNum && flag == 0) {
        if (father->child[j + 1]->keyNum > MIN_KEY) {
            Moveright(father, j);   //找右兄弟
            flag = 1;
        }
        else flag = 0;
    }
    if (flag == 0) {
        Combine(father, j);
        flag = 1;
    }
    if (flag == 1 && father->keyNum < MIN_KEY) {
        Restore(father, T);
    }
    return OK;
}
