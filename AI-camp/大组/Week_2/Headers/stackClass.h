#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

//���������ջ
typedef struct StackNode {
	int num;
	struct StackNode* next;
}StackNode, * StackLine;

typedef struct WholeStackList {
	int count;
	StackLine top;
}WholeStackList;

//����������ջ
typedef struct StackNodeChar {
	char operation;
	struct StackNodeChar* next;
}StackNodeChar, * StackLineChar;

typedef struct WholeStackListChar {
	int count;
	StackLineChar top;
}WholeStackListChar;

//��Ÿ�������ջ
typedef struct StackNodeFloat {
	float num;
	struct StackNodeFloat* next;
}StackNodeFloat, * StackLineFloat;

typedef struct WholeStackListFloat {
	int count;
	StackLineFloat top;
}WholeStackListFloat;

//��ʼ��
void InitStack(StackLine* S, WholeStackList* SList);
//�ж��Ƿ�Ϊ��
void IsEmpty(StackLine* S, WholeStackList* SLis);
//�������
void MultiPush(StackLine* S, WholeStackList* SLis);
//��������
bool Push(StackLine* S, WholeStackList* SLis);
//��ջ�����
void Pop(StackLine* S, WholeStackList* SLis);
//�õ�ջ��Ԫ��
void GetTop(StackLine* S, WholeStackList* SLis);
//ɾ��ջ
void DeleteStack(StackLine* S, WholeStackList* SLis);
//��ӡջ
void PrintStack(StackLine* S, WholeStackList* SLis);

void InitStack(StackLine* S, WholeStackList* SList) {
	SList->count = 0;
	if (*S == NULL)
		return;
	(*S)->num = 114514;
	(*S)->next = NULL;
	SList->top = *S;
}

void IsEmpty(StackLine* S, WholeStackList* SList) {
	if (SList->count == 0)
		printf("��ջΪ��\n");
	else
		printf("��ջ��Ϊ��\n");
	system("pause");
}

void MultiPush(StackLine* S, WholeStackList* SList) {
	bool flag = true;
	while (flag) {
		flag = Push(S, SList);
	}
}

bool Push(StackLine* S, WholeStackList* SList) {
	int num;
	int flag = 1;

	while (flag) {
		system("cls");
		printf("������Ҫ���������(����114514�˳�doge):");
		flag = scanf_s("%d", &num);
		if (flag) {
			printf("����ɹ�\n");
			flag = 0;
		}
		else {
			printf("�������,����������\n");
			system("pause");
			system("cls");
		}
		if (num == 114514) {
			printf("�˳��ɹ�\n");
			system("pause");
			while (getchar() != '\n');
			system("cls");
			return false;
		}
	}
	StackLine p = (StackLine)malloc(sizeof(StackNode));
	if (p == NULL)
		return false;
	p->num = num;
	p->next = *S;
	SList->count++;

	if (*S == NULL) {
		*S = p;
		SList->top = *S;
	}
	else {
		p->next = SList->top;
		SList->top = p;
	}
	system("pause");
	while (getchar() != '\n');
	system("cls");
	return true;
}

void Pop(StackLine* S, WholeStackList* SList) {
	if (SList->count == 0) {
		printf("ջ��Ϊ��,���ɳ�ջ\n");
		system("pause");
		system("cls");
		return;
	}
	StackLine p = (StackLine)malloc(sizeof(StackNode));
	p = SList->top;
	SList->top = SList->top->next;
	SList->count--;
	printf("�Ƴ��ɹ�,�Ƴ���ջ����������Ϊ:%d\n", p->num);
	free(p);
	SList->count--;
	system("pause");
	system("cls");
}

void GetTop(StackLine* S, WholeStackList* SList) {
	if (SList->count == 0)
		printf("��ջû��Ԫ��\n");
	else
		printf("ջ����Ԫ��Ϊ:%d\n", SList->top->num);
	system("pause");
	system("cls");
}

void DeleteStack(StackLine* S, WholeStackList* SList) {
	StackLine p = (StackLine)malloc(sizeof(StackNode));
	if (p == NULL)
		return;
	while (1) {
		if (SList->top->num == 114514)
			break;
		p = SList->top;
		SList->top = SList->top->next;
		free(p);
		SList->count--;
	}
	printf("����ջ�ɹ�\n");
	system("pause");
	system("cls");
}

void PrintStack(StackLine* S, WholeStackList* SList) {
	printf("��ջ��Ԫ��Ϊ:\n");
	printf("ջ����");
	StackLine p = SList->top;
	while (1) {
		if (p->num == 114514)
			break;
		printf("%d->", p->num);
		p = p->next;
		if (p == NULL)
			break;
	}
	printf("ջβ\n");
	system("pause");
	system("cls");
}