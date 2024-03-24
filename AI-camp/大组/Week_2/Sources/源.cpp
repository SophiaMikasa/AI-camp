#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "stackClass.h"
#include "count.h"
#include "queueClass.h"

#define MAXSIZE 50

//ջ��ҵ�Ĳ˵�
void StackMenu(void);
//ջ�Ļ�������
void StackOperationMenu(void);
//������
void CalculateMenu(void);
//ȫ����ҵ�Ĳ˵�
void WholeMenu(void);
//���в����Ĳ˵�
void QueueMenu(void);

int main() {
	WholeMenu();
}

void StackMenu(void) {
	char choice;

	while (1) {
		system("cls");
		printf("================================\n");
		printf("������ջ����ҵ\n");
		printf("================================\n");
		printf("1.����һ����ջ�����������ز���\n");
		printf("2.�򵥵��������������\n");
		printf("3.�˳�\n");
		printf("================================\n");
		scanf_s("%c", &choice,1);
		while (getchar() != '\n');
		switch (choice) {
		case '1':
			StackOperationMenu();
			break;
		case '2':
			CalculateMenu();
			break;
		case '3':
			printf("�˳��ɹ�\n");
			system("pause");
			return;
		default:
			printf("�����������������\n");
			system("pause");
			system("cls");
			break;
		}
	}
}

void CalculateMenu(void) {
	char temp[MAXSIZE] = {0};
	float result;

	while (1) {
		system("cls");
		printf("===============================================================\n");
		printf("���Ǹ�������\n");
		printf("===============================================================\n");
		printf("��������ʽ(������ط�������������ֻ��߷�����������˳�����):\n");
		printf("��ʱ��֧������С������,���ǿ����С��\n");
		scanf_s("%s", temp, (unsigned)_countof(temp));
		for (int i = 0; temp[i]!='\0'; i++) {
			if (temp[i] >= '0' && temp[i] <= '9')
				continue;
			else if (temp[i] == '+' || temp[i] == '-' || temp[i] == '*' || temp[i] == '/' || temp[i] == '(' || temp[i] == ')')
				continue;
			else {
				printf("�˳��ɹ�\n");
				system("pause");
				while (getchar() != '\n');
				system("cls");
				return;
			}
		}
		while (getchar() != '\n');
		//if (!IsRightFormula(temp)) {
		//	printf("�ⲻ�Ǹ���ȷ��ʽ�ӣ�����������\n");
		//	system("pause");
		//	system("cls");
		//	continue;
		//}
		result = StarCalculate(temp);
		printf("�����Ϊ%.2f", result);
		system("pause");
	}
}

void StackOperationMenu(void) {
	char choice;
	StackLine S = (StackLine)malloc(sizeof(StackNode));
	WholeStackList SList;
	InitStack(&S, &SList);

	while (1) {
		system("cls");
		printf("====================\n");
		printf("���ڿ��Զ�ջ���в���\n");
		printf("====================\n");
		printf("1.�ж�ջ�Ƿ�Ϊ��\n");
		printf("2.��ջ\n");
		printf("3.��ջ\n");
		printf("4.��ջ��Ԫ��\n");
		printf("5.ջ����\n");
		printf("6.��ӡ����ջ\n");
		printf("7.�˳�\n");
		printf("====================\n");
		scanf_s("%c", &choice,1);
		while (getchar() != '\n');
		switch (choice) {
		case '1':
			IsEmpty(&S, &SList);
			break;
		case '2':
			MultiPush(&S, &SList);
			break;
		case '3':
			Pop(&S, &SList);
			break;
		case '4':
			GetTop(&S, &SList);
			break;
		case '5':
			DeleteStack(&S, &SList);
			break;
		case '6':
			PrintStack(&S,&SList);
			break;
		case '7':
			printf("�˳��ɹ�\n");
			system("pause");
			return;
		default:
			printf("�����������������\n");
			system("pause");
			system("cls");
			break;
		}
	}
}

void WholeMenu(void) {
	char choice;

	while (1) {
		system("cls");
		printf("==========================\n");
		printf("��ѡ��Ҫ�鿴����ҵ.....\n");
		printf("==========================\n");
		printf("1.ջ����ҵ\n");
		printf("2.���е���ҵ\n");
		printf("3.�˳�\n");
		printf("==========================\n");
		scanf_s("%c", &choice, 1);
		while (getchar() != '\n');
		switch (choice){
			case '1':
				StackMenu();
				break;
			case '2':
				QueueMenu();
				break;
			case '3':
				printf("�˳��ɹ�\n");
				system("pause");
				exit(0);
				system("cls");
			default:
				printf("�������,����������\n");
				system("pause");
				break;
		}
	}
}

void QueueMenu(void) {
	char choice;
	WholeQueueList QList;
	InitQueue(&QList);

	while (1) {
		system("cls");
		printf("=====================\n");
		printf("�����ǶԶ��еĲ���\n");
		printf("=====================\n");
		printf("1.����\n");
		printf("2.���\n");
		printf("3.���ٶ���\n");
		printf("4.�����������\n");
		printf("5.�˳�\n");
		printf("=====================\n");
		scanf_s("%c", &choice, 1);
		while (getchar() != '\n');
		switch (choice){
			case '1':
				LeftQueue(&QList);
				printf("���ӳɹ�\n");
				system("pause");
				break;
			case '2':
				MultiEnterQueue(&QList);
				break;
			case '3':
				DestroyQueue(&QList);
				break;
			case '4':
				PrintQueue(&QList);
				break;
			case '5':
				printf("�˳��ɹ�\n");
				system("pause");
				system("cls");
				return;
			default:
				printf("�������,����������\n");
				system("pause");
				break;
		}
	}

}