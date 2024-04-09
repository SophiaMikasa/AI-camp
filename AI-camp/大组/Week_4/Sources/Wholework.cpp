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
		printf("��ҵ��\n");
		printf("============\n");
		printf("1.����\n");
		printf("2.ѡ��һ\n");
		printf("3.ѡ����\n");
		printf("4.�˳�\n");
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
			printf("�˳��ɹ�\n");
			system("pause");
			exit(1);
		default:
			printf("�������,����������\n");
			system("pause");
			break;
		}
	}
}

void WorkOneMenu(void) {
	TreeNode* root = InitTree();
	Menu(&root);
}