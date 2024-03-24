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

//��ʼ��
void InitQueue(WholeQueueList* Q);
//�ж��Ƿ�Ϊ��
bool IsEmpty(WholeQueueList* Q);
//���
void EnterQueue(WholeQueueList* Q, void* data,int type);
//����
void* LeftQueue(WholeQueueList* Q);
//ɾ����
void DestroyQueue(WholeQueueList* Q);
//������
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
		printf("�ڴ����ʧ��\n");
		exit(1);
	}
	p->next = NULL;
	p->type = type;
	switch (type){
		case 4:
			p->data = malloc(sizeof(int));
			*(int*)p->data = *(int*)data;
			break;
		case 8:
			p->data = malloc(sizeof(float));
			*(float*)p->data = *(float*)data;
			break;
		case 1:
			p->data = malloc(sizeof(char));
			*(char*)p->data = *(char*)data;
			break;
		case MAXCHAR:{
			const char* strData = (const char*)data;
			size_t len = strlen(strData);
			p->data = malloc(len + 1);
			if (p->data != NULL)
				strcpy_s((char*)p->data, len + 1, strData);
			else {
				printf("�ڴ����ʧ��\n");
				free(p);
				return;
			}
			break;
		}
		default:
			free(p);
			return;
	}

	if (IsEmpty(Q))
		Q->head = p;
	else 
		Q->tail->next = p;
	Q->tail = p;
	printf("��ӳɹ�\n");
	system("pause");
}

void* LeftQueue(WholeQueueList* Q) {
	QueueLine p = (QueueLine)malloc(sizeof(QueueNode));
	void* data;
	if (p == NULL) {
		printf("�ڴ����ʧ��\n");
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
	printf("���ٳɹ�\n");
	system("pause");
}

void MultiEnterQueue(WholeQueueList* Q) {
	char choice;

	while (1) {
		system("cls");
		printf("=================================\n");
		printf("���ڿ��������Ԫ��\n");
		printf("=================================\n");
		printf("1.��������\n");
		printf("2.���븡����\n");
		printf("3.�����ַ�\n");
		printf("4.�����ַ���\n");
		printf("5.�˳�\n");
		printf("=================================\n");
		scanf_s("%c", &choice,1);
		while (getchar() != '\n');
		switch (choice){
		case '1': {
			int* temp = (int*)malloc(sizeof(int));
			printf("������Ҫ��ӵ�����\n");
			scanf_s("%d", temp);
			while (getchar() != '\n');
			EnterQueue(Q, temp,4);
			break;
		}
		case '2': {
			float* temp = (float*)malloc(sizeof(float));
			printf("������Ҫ��ӵĸ�����\n");
			scanf_s("%f", temp,1);
			while (getchar() != '\n');
			EnterQueue(Q, temp,8);
			break;
		}
		case '3': {
			char* temp = (char*)malloc(sizeof(char));
			printf("������Ҫ��ӵ��ַ�)\n");
			scanf_s("%c", temp,1);
			while (getchar() != '\n');
			EnterQueue(Q, temp,1);
			break;
		}
		case '4': {
			char* temp = (char*)malloc(sizeof(char) * MAXCHAR);
			printf("������Ҫ��ӵ��ַ���)(����20����Ŷ)\n");
			scanf_s("%s", temp, MAXCHAR);
			while (getchar() != '\n');
			if (strlen(temp) == 0) {
				printf("���벻�ܴ���20��Ŷ\n");
				system("pause");
				break;
			}
			EnterQueue(Q, temp, MAXCHAR);
			break;
		}

		case '5': {
			printf("�˳��ɹ�\n");
			system("pause");
			system("cls");
			return;
		}
		default: {
			printf("�������\n");
			system("pause");
			break;
		}
		}
	}
}

void PrintQueue(WholeQueueList* Q) {
	QueueLine p = (QueueLine)malloc(sizeof(QueueNode));
	p = Q->head;
	printf("��ͷ->");
	while (p) {
		if (p->type == 4)
			printf("%d", *(int*)(p->data));
		else if (p->type == 8)
			printf("%lf", *(float*)(p->data));
		else if (p->type == 1)
			printf("%c", *(char*)(p->data));
		else if (p->type == MAXCHAR)
			printf("%s", (char*)(p->data));
		p = p->next;
		printf("->");
	}
	printf("��β\n");
	system("pause");
}