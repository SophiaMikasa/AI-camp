#pragma once
#include<stdio.h>
#include<stdlib.h>

typedef struct AVLTreeNode {
    int data;
    struct AVLTreeNode* left;
    struct AVLTreeNode* right;
    int height;
}ALVTreeNode;

void WorkThreeMenu(void);
void AVL_Menu(void);
AVLTreeNode* CreateAVLTree(int data);
int GetHeight(AVLTreeNode* Node);
int GetBalanceNum(AVLTreeNode* Node);
AVLTreeNode* SingleRotateWithLeft(AVLTreeNode* k2);
AVLTreeNode* SingleRotateWithRight(AVLTreeNode* k2);
AVLTreeNode* InsertAVLTreeNode(AVLTreeNode* Node, int data);
void MiSkimAVLTree(AVLTreeNode* root);
AVLTreeNode* minValueNode(AVLTreeNode* node);
AVLTreeNode* deleteNode(AVLTreeNode* root, int data);
void R_B_Tree_Menu(void);

void WorkThreeMenu(void) {
    char choice;

    while (1) {
        system("cls");
        printf("==============\n");
        printf("选做二\n");
        printf("==============\n");
        printf("1.AVL\n");
        printf("2.红黑树\n");
        printf("3.退出\n");
        printf("==============\n");
        scanf_s("%c", &choice, 1);
        while (getchar() != '\n');
        switch (choice) {
        case '1':
            AVL_Menu();
            break;
        case '2':
            R_B_Tree_Menu();
            break;
        case '3':
            return;
        default:
            printf("输入错误,请重新输入\n");
            system("pause");
            break;
        }
    }
}

void AVL_Menu(void) {
    int num, flag = 0;
    AVLTreeNode* root = NULL;

    while (1) {
        flag = 0;
        printf("请输入整数,输入0退出\n");
        flag = scanf_s("%d", &num);
        while (getchar() != '\n');
        if (flag != 1) {
            printf("输入错误\n");
            while (getchar() != '\n');
            continue;
        }
        if (num == 0)
            break;
        root = InsertAVLTreeNode(root, num);
    }

    printf("中序遍历\n");
    MiSkimAVLTree(root);
    system("pause");

    char choice;

    while (1) {
        system("cls");
        printf("================\n");
        printf("AVL\n");
        printf("================\n");
        printf("1.插入\n");
        printf("2.遍历\n");
        printf("3.删除\n");
        printf("4.退出\n");
        printf("================\n");
        scanf_s("%c", &choice, 1);
        while (getchar() != '\n');
        switch (choice) {
        case '1':
            flag = 0;
            printf("请输入整数,输入0退出\n");
            flag = scanf_s("%d", &num);
            while (getchar() != '\n');
            if (flag != 1) {
                printf("输入错误\n");
                while (getchar() != '\n');
                continue;
            }
            if (num == 0)
                break;
            root = InsertAVLTreeNode(root, num);
            break;
        case '2':
            MiSkimAVLTree(root);
            system("pause");
            break;
        case '3':
            printf("请输入要删除的整数\n");
            flag = scanf_s("%d", &num);
            while (getchar() != '\n');
            if (flag != 1) {
                printf("输入错误\n");
                while (getchar() != '\n');
                continue;
            }
            if (num == 0)
                break;
            root = deleteNode(root, num);
            printf("操作完成\n");
            system("pause");
            break;
        case '4':
            return;
        default:
            printf("输入错误,请重新输入\n");
            system("pause");
            break;
        }
    }
}

AVLTreeNode* CreateAVLTree(int data) {
    AVLTreeNode* newNode = (AVLTreeNode*)malloc(sizeof(AVLTreeNode));
    if (newNode == NULL)
        return NULL;
    newNode->data = data;
    newNode->height = 1;
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}

int GetHeight(AVLTreeNode* Node) {
    if (Node == NULL)
        return 0;
    return Node->height;
}

int GetBalanceNum(AVLTreeNode* Node) {
    if (Node == NULL)
        return 0;
    return GetHeight(Node->left) - GetHeight(Node->right);
}

AVLTreeNode* SingleRotateWithLeft(AVLTreeNode* x) {
    AVLTreeNode* y = x->right;
    AVLTreeNode* T2 = y->left;

    y->left = x;
    x->right = T2;

    y->height = 1 + (GetHeight(y->left) > GetHeight(y->right) ? GetHeight(y->left) : GetHeight(y->right));
    x->height = 1 + (GetHeight(x->left) > GetHeight(x->right) ? GetHeight(x->left) : GetHeight(x->right));

    return y;
}

AVLTreeNode* SingleRotateWithRight(AVLTreeNode* y) {
    AVLTreeNode* x = y->left;
    AVLTreeNode* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = 1 + (GetHeight(y->left) > GetHeight(y->right) ? GetHeight(y->left) : GetHeight(y->right));
    x->height = 1 + (GetHeight(x->left) > GetHeight(x->right) ? GetHeight(x->left) : GetHeight(x->right));

    return x;
}

AVLTreeNode* InsertAVLTreeNode(AVLTreeNode* Node, int data) {
    if (Node == NULL)
        return CreateAVLTree(data);
    if (data > Node->data)
        Node->right = InsertAVLTreeNode(Node->right, data);
    else if (data < Node->data)
        Node->left = InsertAVLTreeNode(Node->left, data);
    else
        return Node;

    Node->height = 1 + (GetHeight(Node->left) > GetHeight(Node->right) ? GetHeight(Node->left) : GetHeight(Node->right));
    int balancenum = GetBalanceNum(Node);

    if (balancenum > 1 && data < Node->left->data)
        return SingleRotateWithRight(Node);
    if (balancenum > 1 && data > Node->left->data) {
        //Node = SingleRotateWithLeft(Node);
        return SingleRotateWithRight(Node);
    }
    if (balancenum < -1 && data > Node->right->data)
        return SingleRotateWithLeft(Node);
    if (balancenum < -1 && data < Node->right->data) {
        //Node = SingleRotateWithRight(Node);
        return SingleRotateWithLeft(Node);
    }

    return Node;
}

void MiSkimAVLTree(AVLTreeNode* root) {
    if (root != NULL) {
        MiSkimAVLTree(root->left);
        printf("%d ", root->data);
        MiSkimAVLTree(root->right);
    }
}

AVLTreeNode* minValueNode(AVLTreeNode* node) {
    AVLTreeNode* current = node;
    while (current && current->left != NULL)
        current = current->left;
    return current;
}

AVLTreeNode* deleteNode(AVLTreeNode* root, int data) {
    if (root == NULL) {
        printf("找不到要删除的节点\n");
        return root;
    }

    if (data < root->data)
        root->left = deleteNode(root->left, data);
    else if (data > root->data)
        root->right = deleteNode(root->right, data);
    else {
        if (root->left == NULL || root->right == NULL) {
            AVLTreeNode* temp = root->left ? root->left : root->right;

            if (temp == NULL) {
                temp = root;
                root = NULL;
            }
            else {
                *root = *temp;
            }
            free(temp); 
        }
        else {
            AVLTreeNode* temp = minValueNode(root->right); 
            root->data = temp->data; 
            root->right = deleteNode(root->right, temp->data); 
        }
    }

    if (root == NULL)
        return root;

    root->height = 1 + (GetHeight(root->left) > GetHeight(root->right) ? GetHeight(root->left) : GetHeight(root->right));

    int bf = GetBalanceNum(root);
    if (bf > 1 && GetBalanceNum(root->left) >= 0) 
        return SingleRotateWithRight(root);
    if (bf > 1 && GetBalanceNum(root->left) < 0) { 
        root->left = SingleRotateWithLeft(root->left);
        return SingleRotateWithRight(root);
    }
    if (bf < -1 && GetBalanceNum(root->right) <= 0) 
        return SingleRotateWithLeft(root);
    if (bf < -1 && GetBalanceNum(root->right) > 0) { 
        root->right = SingleRotateWithRight(root->right);
        return SingleRotateWithLeft(root);
    }

    return root;
}

void R_B_Tree_Menu(void) {
    printf("瞅啥呢,聪明的人才能看到(doge)(bushi)\n");
    system("pause");
}