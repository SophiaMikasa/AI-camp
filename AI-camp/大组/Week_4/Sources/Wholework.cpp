#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include "workone.h"
#include "worktwo.h"
#include "workthree.h"

void WholeMenu(void);
void WorkOneMenu(void);

int main() {
	WholeMenu();
}

void WholeMenu(void) {
	char choice;

	while (1) {
		system("cls");
		printf("============\n");
		printf("作业：\n");
		printf("============\n");
		printf("1.必做\n");
		printf("2.选做一\n");
		printf("3.选做二\n");
		printf("4.退出\n");
		printf("============\n");
		scanf_s("%c", &choice, 1);
		while (getchar() != '\n');
		switch (choice) {
		case '1':
			WorkOneMenu();
			break;
		case '2':
			WorkTwoMenu();
			break;
		case '3':
			WorkThreeMenu();
			break;
		case '4':
			printf("退出成功\n");
			system("pause");
			exit(1);
		default:
			printf("输入错误,请重新输入\n");
			system("pause");
			break;
		}
	}
}

void WorkOneMenu(void) {
	TreeNode* root = InitTree();
	Menu(&root);
}