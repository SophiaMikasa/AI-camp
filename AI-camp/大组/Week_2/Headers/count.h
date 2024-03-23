#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include "stackClass.h"

#define MAXSIZE 50

//bool IsRightFormula(char* temp);
float StarCalculate(char* temp);
float trueCalculate(char* newTemp, WholeStackListFloat* SList);
void PushNum(WholeStackListFloat* SList, float num);
float PopNum(WholeStackListFloat* SList);
char* Convert(WholeStackListChar* SList, char* temp);
char PopOperation(StackLineChar* S, WholeStackListChar* SList);
void PushOperation(StackLineChar* S, WholeStackListChar* SList, char operation);
int Priority(char operation);
void error(void);

void error(void) {
	printf("ʽ������ֻ��ǿ���˳�\n");
	system("pause");
	exit(1);
	system("cls");
}

//�жϷ��ŵ����ȼ�
int Priority(char operation) {
	if (operation == '+' || operation == '-')
		return 2;
	else if (operation == '*' || operation == '/')
		return 3;
	else
		return 0;
}

void PushOperation(StackLineChar* S, WholeStackListChar* SList, char operation) {
	StackLineChar p = (StackLineChar)malloc(sizeof(StackNodeChar));
	if (p == NULL)
		return;
	p->operation = operation;
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
}

char PopOperation(StackLineChar* S, WholeStackListChar* SList) {
	if (SList->count == 0)
		return NULL;
	StackLineChar p = (StackLineChar)malloc(sizeof(StackNodeChar));
	p = SList->top;
	SList->top = SList->top->next;
	SList->count--;
	char popchar = p->operation;
	free(p);
	return popchar;
}

//����׺���ʽת��Ϊ��׺���ʽ
char* Convert(WholeStackListChar* SList,char* temp) {
	StackLineChar S = (StackLineChar)malloc(sizeof(StackNodeChar));
	SList->count = 0;
	SList->top = NULL;
	char* newTemp = (char*)malloc(sizeof(char) * MAXSIZE);
	if (newTemp == NULL)
		return NULL;
	*newTemp = { 0 };
	int j = 0;
	//��������Ƿ����
	int flag1 = 0, flag2 = 0;
	for (int i = 0; temp[i] != '\0'; i++) {
		if (temp[i] == '(')
			flag1++;
		if (temp[i] == ')')
			flag2++;
	}
	if (flag1 != flag2)
		error();


	for (int i = 0; *(temp + i) != '\0'; i++) {
		if (temp[i] <= '9' && temp[i] >= '0') {
			int num = temp[i]-'0', flag = 0;
			//�ж����ֵ�λ��
			for (int k = 0; *(temp + k+i) >= '0'&&*(temp + k+i) <= '9'; k++)
				flag++;
			//���临�Ƶ����ַ�����
			newTemp[j++] = temp[i];
			for (int k = 1; k < flag; k++)
				newTemp[j++] = temp[++i];
			newTemp[j++] = ' ';
		}
		else if (temp[i] == '+' || temp[i] == '-' || temp[i] == '/' || temp[i] == '*' || temp[i] == '(' || temp[i] == ')') {
			if (SList->count == 0) {
				//���ջ���޷����ҵ�ǰ����Ϊ")"�򱨴�
				if (temp[i] == ')')
					error();
				else
					PushOperation(&S, SList, temp[i]);
			}
			else if (temp[i] == '(')
				//��������ź����ǷǸ�������򱨴�(����������)
				if (temp[i+1] == '+' || temp[i+1] == '/' || temp[i+1] == '*')
					error();
				else 
					PushOperation(&S, SList, temp[i]);
			else if (temp[i] == ')') {
				//��������ź����������򱨴�
				if (temp[i + 1] >= '0' && temp[i + 1] <= '9')
					error();
				else
					while (1) {
						//����������ķ���ȫ�������
						char temp = PopOperation(&S, SList);
						if (temp == '(')
							break;
						newTemp[j++] = temp;
					}
			}
			//�Ƚ����ȼ�,�����ǰ���ŵ����ȼ���ջ������ֱ��ѹ��ջ������ջ����������滻Ϊ��ǰ����
			else if (Priority(SList->top->operation) >= Priority(temp[i])) {
				newTemp[j++] = PopOperation(&S, SList);
				PushOperation(&S, SList, temp[i]);
			}
			else if (Priority(SList->top->operation) < Priority(temp[i]))
				PushOperation(&S, SList, temp[i]);
			else
				return NULL;
		}
	}
	//��ʣ��ķ��������
	while (1) {
		newTemp[j++] = PopOperation(&S, SList);
		if (SList->count == 0)
			break;
		newTemp[j++] = ' ';
	}
	newTemp[j] = '\0';
	return newTemp;
}

float PopNum(WholeStackListFloat* SList) {
	if (SList->count == 0)
		return NULL;
	StackLineFloat p = (StackLineFloat)malloc(sizeof(StackNodeFloat));
	p = SList->top;
	SList->top = SList->top->next;
	SList->count--;
	float popNum = p ->num;
	free(p);
	return popNum;
}

void PushNum(WholeStackListFloat* SList, float num) {
	StackLineFloat p = (StackLineFloat)malloc(sizeof(StackNodeFloat));
	if (p == NULL)
		return;
	p->num = num;
	SList->count++;

	if (SList->top != NULL)
		p->next = SList->top;	
	SList->top = p;
}

float trueCalculate(char* newTemp, WholeStackListFloat* SList) {
	for (int i = 0; *(newTemp + i) != '\0'; i++) {
		if (newTemp[i] >= '0' && newTemp[i] <= '9') {
			int flag = 0;
			float num = newTemp[i] - '0';
			//��ȡ����
			for (int k = 0; newTemp[k + i] != ' '; k++)
				flag++;
			for (int k = 1; k < flag; k++)
				num = num * 10 + (newTemp[++i] - '0');
			PushNum(SList, num);
			continue;
		}
		else if (newTemp[i] == '+') {
			//��������
			PushNum(SList, PopNum(SList) + PopNum(SList));
			continue;
		}
		else if (newTemp[i] == '-') {
			//��������
			PushNum(SList, -PopNum(SList) + PopNum(SList));
			continue;
		}
		else if (newTemp[i] == '*') {
			//��������
			PushNum(SList, PopNum(SList) * PopNum(SList));
			continue;
		}
		else if (newTemp[i] == '/') {
			//��������
			float head = PopNum(SList), behind = PopNum(SList);
			//�жϱ������Ƿ�Ϊ0
			if (head) {
				PushNum(SList, behind / head);
				continue;
			}
			else {
				printf("\n�������,����������Ϊ��\n");
				system("pause");
				system("cls");
				exit(0);
			}
		}
		else if (newTemp[i] == ' ')
			continue;
	}
	return PopNum(SList);
}

float StarCalculate(char* temp) {
	WholeStackListChar SListChar;
	WholeStackListFloat NumList;
	NumList.count = 0;
	NumList.top = NULL;
	//StackLine SNode = (StackLine)malloc(sizeof(StackNode));
	//InitStack(&SNode, &NumList);
	printf("��׺���ʽ:%s",temp);
	char* newTemp = Convert(&SListChar,temp);
	printf("\n��׺���ʽ:%s",newTemp);
	float result = trueCalculate(newTemp, &NumList);
	system("pause");
	return result;
}

//bool IsRightFormula(char* temp) {
//	if (temp[0] < '0' || temp[0] > '9' || temp[0] != '-')
//		return false;
//	for (int i = 0; *(temp + i) == '\0'; i++) {
//
//	}
//	return true;
//}