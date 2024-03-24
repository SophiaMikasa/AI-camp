#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "stackClass.h"
#include "count.h"
#include "queueClass.h"

#define MAXSIZE 50

//栈作业的菜单
void StackMenu(void);
//栈的基本操作
void StackOperationMenu(void);
//计算器
void CalculateMenu(void);
//全部作业的菜单
void WholeMenu(void);
//队列操作的菜单
void QueueMenu(void);

int main() {
	WholeMenu();
}

void StackMenu(void) {
	char choice;

	while (1) {
		system("cls");
		printf("================================\n");
		printf("以下是栈的作业\n");
		printf("================================\n");
		printf("1.生成一个链栈并对其进行相关操作\n");
		printf("2.简单的四则运算计算器\n");
		printf("3.退出\n");
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
			printf("退出成功\n");
			system("pause");
			return;
		default:
			printf("输入错误，请重新输入\n");
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
		printf("这是个计算器\n");
		printf("===============================================================\n");
		printf("请输入表达式(再任意地方输入任意非数字或者非运算符号则退出计算):\n");
		printf("暂时不支持输入小数运算,但是可输出小数\n");
		scanf_s("%s", temp, (unsigned)_countof(temp));
		for (int i = 0; temp[i]!='\0'; i++) {
			if (temp[i] >= '0' && temp[i] <= '9')
				continue;
			else if (temp[i] == '+' || temp[i] == '-' || temp[i] == '*' || temp[i] == '/' || temp[i] == '(' || temp[i] == ')')
				continue;
			else {
				printf("退出成功\n");
				system("pause");
				while (getchar() != '\n');
				system("cls");
				return;
			}
		}
		while (getchar() != '\n');
		//if (!IsRightFormula(temp)) {
		//	printf("这不是个正确的式子，请重新输入\n");
		//	system("pause");
		//	system("cls");
		//	continue;
		//}
		result = StarCalculate(temp);
		printf("最后结果为%.2f", result);
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
		printf("现在可以对栈进行操作\n");
		printf("====================\n");
		printf("1.判断栈是否为空\n");
		printf("2.进栈\n");
		printf("3.出栈\n");
		printf("4.读栈顶元素\n");
		printf("5.栈销毁\n");
		printf("6.打印整个栈\n");
		printf("7.退出\n");
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
			printf("退出成功\n");
			system("pause");
			return;
		default:
			printf("输入错误，请重新输入\n");
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
		printf("请选择要查看的作业.....\n");
		printf("==========================\n");
		printf("1.栈的作业\n");
		printf("2.队列的作业\n");
		printf("3.退出\n");
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
				printf("退出成功\n");
				system("pause");
				exit(0);
				system("cls");
			default:
				printf("输入错误,请重新输入\n");
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
		printf("以下是对队列的操作\n");
		printf("=====================\n");
		printf("1.出队\n");
		printf("2.入队\n");
		printf("3.销毁队列\n");
		printf("4.输出整个队列\n");
		printf("5.退出\n");
		printf("=====================\n");
		scanf_s("%c", &choice, 1);
		while (getchar() != '\n');
		switch (choice){
			case '1':
				LeftQueue(&QList);
				printf("出队成功\n");
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
				printf("退出成功\n");
				system("pause");
				system("cls");
				return;
			default:
				printf("输入错误,请重新输入\n");
				system("pause");
				break;
		}
	}

}