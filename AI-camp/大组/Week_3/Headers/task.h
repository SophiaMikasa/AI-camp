#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include "Stack.h"
#include "sort.h"
typedef void (*SortFunc)(int arr[], int low, int high);

#define MAXSIZE 10
#define DATA_SIZE 100
#define DATA_RANGE 1000
#define NUM_TESTS 100000
#define FILENAME "test_data.txt"


char AglMenu(void);
char AppMenu(void);
void Test_one(SortFunc sort);
void Test_two(SortFunc sort);
void Generate_File(int size);
void Reed_File(SortFunc sort, int size);
void sortColors(void);
void create_and_fine_small(void);
int kthSmallest(int arr[], int low, int high, int k);


char AppMenu(void) {
	char choice;

	while (1) {
		system("cls");
		printf("======================================\n");
		printf("作业列表\n");
		printf("======================================\n");
		printf("1.测试程序一:不同的大数据量下的用时\n");
		printf("2.测试程序二:大量小数据量下的排序用时\n");
		printf("3.生成数据并保存在文件\n");
		printf("4.读取文件数据，并按需求排序\n");
		printf("======================================\n");
		printf("排序算法的应用\n");
		printf("5.颜色排序\n");
		printf("6.在一个无序序列中找到第K大/小的数\n");
		printf("7.退出\n");
		printf("======================================\n");
		scanf_s("%c", &choice, 1);
		while (getchar() != '\n');
		if (choice == '1' || choice == '2' || choice == '3' || choice == '4' || choice == '5' || choice == '6' || choice == '7')
			break;
		else {
			printf("输入错误，请重新输入\n");
			system("pause");
			while (getchar() != '\n');
			continue;
		}
	}
	if (choice == '7') {
		printf("退出成功\n");
		system("pause");
		exit(1);
	}
	return choice;
}

char AglMenu(void) {
	char choice;

	while (1) {
		system("cls");
		printf("================================\n");
		printf("请选择要排序的方式\n");
		printf("================================\n");
		printf("1,插入排序\n");
		printf("2.归并排序\n");
		printf("3.快速排序(递归版)(优化)\n");
		printf("4.快速排序(非递归版)\n");
		printf("5.计数排序\n");
		printf("6.基数排序\n");
		printf("7.冒泡排序(优化)\n");
		printf("8.退出\n");
		printf("=================================\n");
		scanf_s("%c", &choice, 1);
		if (choice == '1' || choice == '2' || choice == '3' || choice == '4' || choice == '5' || choice == '6' || choice == '7' || choice == '8')
			break;
		else {
			printf("输入错误，请重新输入\n");
			system("pause");
			while (getchar() != '\n');
			continue;
		}
	}
	if (choice == '8') {
		printf("退出成功\n");
		system("pause");
		exit(1);
	}
	return choice;
}

void Test_one(SortFunc sort) {
#pragma warning(push)
#pragma warning(disable : 4244)
	srand(time(NULL));
#pragma warning(pop)
	int allsize[3] = { 10000,50000,100000 };
	int i = 0;

	while (i < 3) {
		int size = allsize[i];
		int* nums = (int*)malloc(size * sizeof(int));
		if (nums == NULL)
			return;

		// 生成随机数组
		for (int j = 0; j < size; j++) {
			nums[j] = rand();
		}
		//printf("排序前\n");
		//PrintNums(nums, size - 1);
		clock_t start = clock();
		sort(nums, 0, size - 1);
		clock_t end = clock();
		double cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
		//printf("排序后:\n");
		//PrintNums(nums,size - 1);
		printf("\n%d个整数，排序需要花费%lf ms\n", size, cpu_time_used);
		free(nums);
		i++;
	}
}

void Test_two(SortFunc sort) {
#pragma warning(push)
#pragma warning(disable : 4244)
	srand(time(NULL));
#pragma warning(pop)
	clock_t start, end;
	double total_time = 0.0;

	for (int j = 0; j < NUM_TESTS; j++) {
		int* nums = (int*)malloc(DATA_SIZE * sizeof(int));
		if (nums == NULL)
			return;

		for (int i = 0; i < DATA_SIZE; i++) {
			nums[i] = rand();
		}
		start = clock();
		sort(nums, 0, DATA_SIZE - 1);
		end = clock();

		total_time += ((double)(end - start)) / CLOCKS_PER_SEC;

		free(nums);
	}
	printf("\n排序%d个整数%d次平均用时%lf ms\n", DATA_SIZE, NUM_TESTS, total_time / NUM_TESTS);
}

void Generate_File(int size) {
	FILE* fp = fopen(FILENAME, "w");

	if (fp == NULL) {
		printf("打开文件失败\n");
		return;
	}
#pragma warning(push)
#pragma warning(disable : 4244)
	srand(time(NULL));
#pragma warning(pop)
	for (int i = 0; i < size; i++) {
		fprintf(fp, "%d ", rand() % DATA_RANGE);
	}
	printf("生成测试数据成功!(生成了%d个0到%d范围的整数)\n", size, DATA_RANGE);
	printf("并且保存到%s文件中\n", FILENAME);
	fclose(fp);
}

void Reed_File(SortFunc sort, int size) {
	FILE* fp = fopen(FILENAME, "r");
	int* nums = (int*)malloc(DATA_SIZE * sizeof(int));
	if (nums == NULL) {
		printf("生成数组失败\n");
		return;
	}
	if (fp == NULL) {
		printf("打开文件失败\n");
		return;
	}

	for (int i = 0; i < size; ++i) {
		if (fscanf(fp, "%d ", nums + i) != 1) {
			printf("文件暂时没有数据\n");
			return;
		}
	}

	fclose(fp);
	printf("==========================================\n");
	printf("已从%s读取数据\n", FILENAME);
	printf("排序前：\n");
	PrintNums(nums, size);
	sort(nums, 0, size - 1);
	printf("==========================================\n");
	printf("排序后：\n");
	PrintNums(nums, size);
}

int kthSmallest(int nums[], int low, int high, int k) {
	if (k > 0 && k <= high - low + 1) {
		int pos = partition_None(nums, low, high);

		if (pos - low == k - 1)
			return nums[pos];
		if (pos - low > k - 1)
			return kthSmallest(nums, low, pos - 1, k);
		return kthSmallest(nums, pos + 1, high, k - pos + low - 1);
	}
	return -1;
}

void create_and_fine_small(void) {
	int* nums = (int*)malloc(MAXSIZE * sizeof(int));
	if (nums == NULL)
		return;

	for (int i = 0; i < MAXSIZE; i++) {
		nums[i] = rand() % 20;
	}
	printf("得到当前整数数组为:\n");
	PrintNums(nums, MAXSIZE);
	int k;
	printf("你要查找第几小的数？\n");
	while (scanf_s("%d", &k) != 1) {
		while (getchar() != '\n');
		printf("输入错误请重新输入\n");
	}
	while (getchar() != '\n');
	if (k >= 1 && k <= MAXSIZE)
		printf("第 %d 小的数为：%d\n", k, kthSmallest(nums, 0, MAXSIZE - 1, k));
	else
		printf("输入错误,输入的名次需要再1~%d范围内\n", MAXSIZE);
}

void sortColors(void) {
	int* nums = (int*)malloc(DATA_SIZE * sizeof(int));
	if (nums == NULL)
		return;

	for (int i = 0; i < DATA_SIZE; i++) {
		nums[i] = rand() % 3;
	}
	int left = 0, right = DATA_SIZE - 1, current = 0;

	printf("排序前:\n");
	PrintNums(nums, DATA_SIZE);
	while (current <= right) {
		if (nums[current] == 0) {
			int temp = nums[left];
			nums[left] = nums[current];
			nums[current] = temp;
			left++;
			current++;
		}
		else if (nums[current] == 1) {
			current++;
		}
		else {
			int temp = nums[current];
			nums[current] = nums[right];
			nums[right] = temp;
			right--;
		}
	}
	printf("排序后:\n");
	PrintNums(nums, DATA_SIZE);
}