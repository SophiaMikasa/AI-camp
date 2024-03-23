#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

//存放整数的栈
typedef struct StackNode {
	int num;
	struct StackNode* next;
}StackNode, * StackLine;

typedef struct WholeStackList {
	int count;
	StackLine top;
}WholeStackList;

//存放运算符的栈
typedef struct StackNodeChar {
	char operation;
	struct StackNodeChar* next;
}StackNodeChar, * StackLineChar;

typedef struct WholeStackListChar {
	int count;
	StackLineChar top;
}WholeStackListChar;

//存放浮点数的栈
typedef struct StackNodeFloat {
	float num;
	struct StackNodeFloat* next;
}StackNodeFloat, * StackLineFloat;

typedef struct WholeStackListFloat {
	int count;
	StackLineFloat top;
}WholeStackListFloat;

//初始化
void InitStack(StackLine* S, WholeStackList* SList);
//判断是否为空
void IsEmpty(StackLine* S, WholeStackList* SLis);
//多次输入
void MultiPush(StackLine* S, WholeStackList* SLis);
//单次输入
bool Push(StackLine* S, WholeStackList* SLis);
//将栈顶输出
void Pop(StackLine* S, WholeStackList* SLis);
//得到栈顶元素
void GetTop(StackLine* S, WholeStackList* SLis);
//删除栈
void DeleteStack(StackLine* S, WholeStackList* SLis);
//打印栈
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
		printf("该栈为空\n");
	else
		printf("该栈不为空\n");
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
		printf("请输入要插入的整数(输入114514退出doge):");
		flag = scanf_s("%d", &num);
		if (flag) {
			printf("输入成功\n");
			flag = 0;
		}
		else {
			printf("输入错误,请重新输入\n");
			system("pause");
			system("cls");
		}
		if (num == 114514) {
			printf("退出成功\n");
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
		printf("栈已为空,不可出栈\n");
		system("pause");
		system("cls");
		return;
	}
	StackLine p = (StackLine)malloc(sizeof(StackNode));
	p = SList->top;
	SList->top = SList->top->next;
	SList->count--;
	printf("移除成功,移除的栈的整数变量为:%d\n", p->num);
	free(p);
	SList->count--;
	system("pause");
	system("cls");
}

void GetTop(StackLine* S, WholeStackList* SList) {
	if (SList->count == 0)
		printf("该栈没有元素\n");
	else
		printf("栈顶的元素为:%d\n", SList->top->num);
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
	printf("销毁栈成功\n");
	system("pause");
	system("cls");
}

void PrintStack(StackLine* S, WholeStackList* SList) {
	printf("该栈的元素为:\n");
	printf("栈顶：");
	StackLine p = SList->top;
	while (1) {
		if (p->num == 114514)
			break;
		printf("%d->", p->num);
		p = p->next;
		if (p == NULL)
			break;
	}
	printf("栈尾\n");
	system("pause");
	system("cls");
}