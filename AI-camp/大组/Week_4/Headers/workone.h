#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include <limits.h>
#define MAXSIZE 30

typedef struct TreeNode {
	int num;
	struct TreeNode* left;
	struct TreeNode* right;
}TreeNode;

typedef struct QueueNode {
	TreeNode* data;
	struct QueueNode* next;
} QueueNode;

typedef struct {
	QueueNode* front;
	QueueNode* rear;
} Queue;

TreeNode* InitTree(void);
void Menu(TreeNode** root);
TreeNode* CreateNode(int num);
void Insert(TreeNode** root, int num);
void MiSkim_Dig(TreeNode* root);
void FrontSkim_Dig(TreeNode* root);
void BehindSkim_Dig(TreeNode* root);
void CengSkim(TreeNode* root);
void SearchMenu(TreeNode* root);
int Search(TreeNode* root, int num, int* floor);
void InsertMenu(TreeNode** root);
void DeleteMenu(TreeNode** root);
void Delete(TreeNode** root, int num);
void PrintMenu(TreeNode* root);
Queue* CreateQueue();
void Enqueue(Queue* queue, TreeNode* data);
TreeNode* Dequeue(Queue* queue);
int isEmpty(Queue* queue);

TreeNode* InitTree(void) {
	int num, flag = 0;
	TreeNode* root = NULL;

	while (1) {
		flag = 0;
		printf("����������,����0�˳�\n");
		flag = scanf_s("%d", &num);
		while (getchar() != '\n');
		if (flag != 1) {
			printf("�������\n");
			while (getchar() != '\n');
			continue;
		}
		if (num == 0)
			break;
		Insert(&root, num);
	}

	printf("�������\n");
	MiSkim_Dig(root);
	printf("\n");
	printf("ǰ�����\n");
	FrontSkim_Dig(root);
	printf("\n");
	printf("�������\n");
	BehindSkim_Dig(root);
	printf("\n");
	printf("��ʼ���ɹ�\n");
	system("pause");

	return root;
}

void Menu(TreeNode** root) {
	char choice;
	while (1) {
		system("cls");
		printf("=================\n");
		printf("����������в���\n");
		printf("=================\n");
		printf("1.����\n");
		printf("2.����\n");
		printf("3.ɾ��\n");
		printf("4.����\n");
		printf("5.�˳�\n");
		printf("=================\n");
		scanf_s("%c", &choice, 1);
		while (getchar() != '\n');
		switch (choice) {
		case '1':
			SearchMenu(*root);
			break;
		case '2':
			InsertMenu(root);
			break;
		case '3':
			DeleteMenu(root);
			break;
		case '4':
			PrintMenu(*root);
			break;
		case '5':
			printf("�˳��ɹ�\n");
			system("pause");
			return;
		default:
			printf("�������,����������\n");
			system("pause");
			break;
		}
	}
}

TreeNode* CreateNode(int num) {
	TreeNode* p = (TreeNode*)malloc(sizeof(TreeNode));
	if (p == NULL)
		return NULL;
	p->num = num;
	p->left = NULL;
	p->right = NULL;

	return p;
}

void Insert(TreeNode** root, int num) {
	if (*root == NULL) {
		*root = CreateNode(num);
	}
	else {
		if ((*root)->num == num) {
			printf("���ܲ�����ͬ����\n");
		}
		else {
			if ((*root)->num > num)
				Insert(&((*root)->left), num);
			else
				Insert(&((*root)->right), num);
		}
	}
}

void MiSkim_Dig(TreeNode* root) {
	if (root != NULL) {
		MiSkim_Dig(root->left);
		printf("%d ", root->num);
		MiSkim_Dig(root->right);
	}
}

void FrontSkim_Dig(TreeNode* root) {
	if (root != NULL) {
		printf("%d ", root->num);
		FrontSkim_Dig(root->left);
		FrontSkim_Dig(root->right);
	}
}

void BehindSkim_Dig(TreeNode* root) {
	if (root != NULL) {
		BehindSkim_Dig(root->left);
		BehindSkim_Dig(root->right);
		printf("%d ", root->num);
	}
}

void MiSkim_NoDig(TreeNode* root) {
	if (root == NULL)
		return;

	TreeNode* stack[MAXSIZE];
	int top = -1;
	TreeNode* current = root;

	while (current != NULL || top != -1) {
		while (current != NULL) {
			stack[++top] = current;
			current = current->left;
		}

		current = stack[top--];
		printf("%d ", current->num);
		current = current->right;
	}
}

void FrontSkim_NoDig(TreeNode* root) {
	if (root == NULL)
		return;

	TreeNode* stack[MAXSIZE];
	int top = -1;
	stack[++top] = root;

	while (top != -1) {
		TreeNode* current = stack[top--];
		printf("%d ", current->num);

		if (current->right != NULL)
			stack[++top] = current->right;

		if (current->left != NULL)
			stack[++top] = current->left;
	}
}

void BehindSkim_NoDig(TreeNode* root) {
	if (root == NULL)
		return;

	TreeNode* stack[MAXSIZE];
	int top = -1;
	TreeNode* current = root;
	TreeNode* last_visited = NULL;

	while (current != NULL || top != -1) {
		while (current != NULL) {
			stack[++top] = current;
			current = current->left;
		}

		TreeNode* temp = stack[top]->right;
		if (temp == NULL || temp == last_visited) {
			printf("%d ", stack[top]->num);
			last_visited = stack[top--];
		}
		else {
			current = temp;
		}
	}
}

void SearchMenu(TreeNode* root) {
	int num, flag1 = 0, flag2 = -1, floor = 0;
	int* pfloor = &floor;

	printf("��������Ҫ���ҵ�����\n");
	flag1 = scanf_s("%d", &num);
	while (getchar() != '\n');
	if (flag1) {
		flag2 = Search(root, num, pfloor);
		if (flag2 == -1)
			printf("�Ҳ���������\n");
		else
			printf("�ҵ��ˣ��ڵ�%d��\n", *pfloor);
	}

	system("pause");
}

int Search(TreeNode* root, int num, int* floor) {
	if (root == NULL)
		return -1;
	else {
		*floor += 1;
		if (num > root->num) {
			*floor = Search(root->right, num, floor);
		}
		else if (num < root->num) {
			*floor = Search(root->left, num, floor);
		}
		return *floor;
	}
}

void InsertMenu(TreeNode** root) {
	int num, flag = 0;

	while (!flag) {
		flag = 0;
		printf("��������Ҫ���������\n");
		flag = scanf_s("%d", &num);
		while (getchar() != '\n');
		if (flag) {
			Insert(root, num);
			system("pause");
			break;
		}
		else {
			printf("�������,����������\n");
		}
	}
}

void DeleteMenu(TreeNode** root) {
	int num;
	int flag1 = 0;
	int* floor = &flag1;

	printf("��������Ҫɾ������\n");
	while (scanf_s("%d", &num) != 1) {
		printf("�����������������\n");
		while (getchar() != '\n');
	}
	while (getchar() != '\n');
	int flag = Search(*root, num, floor);
	if (flag == -1) {
		printf("�Ҳ���Ҫɾ������\n");
		system("pause");
		return;
	}
	else
		Delete(root, num);
}

void Delete(TreeNode** root, int num) {
	if ((*root)->num > num)
		Delete(&((*root)->left), num);
	else if ((*root)->num < num)
		Delete(&((*root)->right), num);
	else {
		if ((*root)->left == NULL && (*root)->right == NULL) {
			free(*root);
			*root = NULL;
		}
		else if ((*root)->left == NULL || (*root)->right == NULL) {
			if ((*root)->left == NULL) {
				TreeNode* p = *root;
				*root = (*root)->right;
				free(p);
				p = NULL;
			}
			else {
				TreeNode* p = *root;
				*root = (*root)->left;
				free(p);
				p = NULL;
			}
		}
		else {
			TreeNode* p1 = *root;
			p1 = p1->right;

			while (p1->left)
				p1 = p1->left;
			(*root)->num = p1->num;
			Delete(&((*root)->right), p1->num);
		}
		printf("ɾ���ɹ�\n");
		system("pause");
	}
}

void PrintMenu(TreeNode* root) {
	char choice;

	while (1) {
		system("cls");
		printf("==================\n");
		printf("1.�������\n");
		printf("2.�������\n");
		printf("3.�������\n");
		printf("4.�������\n");
		printf("5.�˳�\n");
		printf("==================\n");
		scanf_s("%c", &choice, 1);
		while (getchar() != '\n');
		switch (choice) {
		case '1':
			printf("�������\n");
			FrontSkim_Dig(root);
			break;
		case '2':
			printf("�������\n");
			MiSkim_Dig(root);
			break;
		case '3':
			printf("�������\n");
			BehindSkim_Dig(root);
			break;
		case '4':
			printf("�������\n");
			CengSkim(root);
			break;
		case '5':
			printf("�˳��ɹ�\n");
			system("pause");
			return;
		default:
			printf("�������,����������\n");
			system("pause");
			break;
		}
		system("pause");
	}
}

void CengSkim(TreeNode* root) {
	if (root == NULL)
		return;

	Queue* queue = CreateQueue();
	Enqueue(queue, root);

	while (!isEmpty(queue)) {
		TreeNode* current = Dequeue(queue);
		printf("%d ", current->num);

		if (current->left != NULL)
			Enqueue(queue, current->left);
		if (current->right != NULL)
			Enqueue(queue, current->right);
	}

	free(queue);
}

Queue* CreateQueue() {
	Queue* queue = (Queue*)malloc(sizeof(Queue));
	if (queue == NULL)
		return NULL;
	queue->front = queue->rear = NULL;
	return queue;
}

void Enqueue(Queue* queue, TreeNode* data) {
	QueueNode* newNode = (QueueNode*)malloc(sizeof(QueueNode));
	if (newNode == NULL)
		return;
	newNode->data = data;
	newNode->next = NULL;
	if (queue->rear == NULL) {
		queue->front = queue->rear = newNode;
		return;
	}
	queue->rear->next = newNode;
	queue->rear = newNode;
}

TreeNode* Dequeue(Queue* queue) {
	if (queue->front == NULL)
		return NULL;
	QueueNode* temp = queue->front;
	TreeNode* data = temp->data;
	queue->front = queue->front->next;
	if (queue->front == NULL)
		queue->rear = NULL;
	free(temp);
	return data;
}

int isEmpty(Queue* queue) {
	return queue->front == NULL;
}