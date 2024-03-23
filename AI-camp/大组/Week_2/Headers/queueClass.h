#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#define MAXCHAR 20


typedef struct QueueNode {
	int type;
	void* data;
	struct QueueNode* next;
}QueueNode,*QueueLine;

typedef struct WholeQueueList {
	int length;
	QueueLine head;
	QueueLine tail;
}WholeQueueList;

//初始化
void InitQueue(WholeQueueList* Q);
//判断是否为空
bool IsEmpty(WholeQueueList* Q);
//入队
void EnterQueue(WholeQueueList* Q, void* data,int type);
//出队
void* LeftQueue(WholeQueueList* Q);
//删除队
void DestroyQueue(WholeQueueList* Q);
//多次入队
void MultiEnterQueue(WholeQueueList* Q);
//void PrintQueue(WholeQueueList* Q);

void InitQueue(WholeQueueList* Q) {
	Q->head = NULL;
	Q->tail = NULL;
}

bool IsEmpty(WholeQueueList* Q) {
	return (Q->head == NULL);
}

void EnterQueue(WholeQueueList* Q, void* data,int type) {
	QueueLine p = (QueueLine)malloc(sizeof(QueueNode));
	if (p == NULL) {
		printf("内存分配失败\n");
		exit(1);
	}
	//if (type == 1) {
	//	(char*)(p->data);
	//	(char*)data;
	//}
	//else if (type == 4) {
	//	(int*)(p->data);
	//	(int*)data;
	//}
	//else if (type == 8) {
	//	(float*)(p->data);
	//	(float*)data;
	//}

	p->data = data;
	p->next = NULL;

	if (IsEmpty(Q))
		Q->head = p;
	else 
		Q->tail->next = p;
	Q->tail = p;
	printf("入队成功\n");
	system("pause");
}

void* LeftQueue(WholeQueueList* Q) {
	QueueLine p = (QueueLine)malloc(sizeof(QueueNode));
	void* data;
	if (p == NULL) {
		printf("内存分配失败\n");
		exit(1);
	}

	if (Q->head) {
		data = Q->head->data;
		p = Q->head;
		Q->head = Q->head->next;
		free(p);
	}
	else {
		data = NULL;
		Q->tail = NULL;
	}
	return data;
}

void DestroyQueue(WholeQueueList* Q) {
	while (!IsEmpty(Q))
		LeftQueue(Q);
	printf("销毁成功\n");
	system("pause");
}

void MultiEnterQueue(WholeQueueList* Q) {
	char choice;

	while (1) {
		system("cls");
		printf("=================================\n");
		printf("现在可输入队列元素\n");
		printf("=================================\n");
		printf("1.输入整数\n");
		printf("2.输入浮点数\n");
		printf("3.输入字符串\n");
		printf("4.退出\n");
		printf("=================================\n");
		scanf_s("%c", &choice,1);
		while (getchar() != '\n');
		switch (choice){
		case '1': {
			int* temp = (int*)malloc(sizeof(int));
			printf("请输入要入队的整数\n");
			scanf_s("%d", &temp);
			while (getchar() != '\n');
			EnterQueue(Q, temp,4);
			break;
		}
		case '2': {
			float* temp = (float*)malloc(sizeof(float));
			printf("请输入要入队的浮点数\n");
			scanf_s("%lf", &temp,1);
			while (getchar() != '\n');
			EnterQueue(Q, temp,8);
			break;
		}
		case '3': {
			char* temp = (char*)malloc(sizeof(char)* MAXCHAR);
			printf("请输入要入队的字符串(仅限20个字符)\n");
			scanf_s("%s", temp,MAXCHAR);
			while (getchar() != '\n');
			EnterQueue(Q, temp,1);
			break;
		}
		case '4': {
			printf("退出成功\n");
			system("pause");
			system("cls");
			return;
		}
		default: {
			printf("输入错误\n");
			system("pause");
			break;
		}
		}
	}
}

//void PrintQueue(WholeQueueList* Q) {
//	QueueLine p = (QueueLine)malloc(sizeof(QueueNode));
//	p = Q->head;
//	printf("队头->");
//	while (1) {
//		if (p->type == 4)
//			printf("%d", *(p->data));
//		else if (p->type == 8)
//			printf("%lf", *(p->data));
//		else
//			printf("%s", *(p->data));
//		p = p->next;
//		printf("->");
//	}
//	printf("队尾\n");
//}