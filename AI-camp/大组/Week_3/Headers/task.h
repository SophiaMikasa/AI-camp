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
		printf("��ҵ�б�\n");
		printf("======================================\n");
		printf("1.���Գ���һ:��ͬ�Ĵ��������µ���ʱ\n");
		printf("2.���Գ����:����С�������µ�������ʱ\n");
		printf("3.�������ݲ��������ļ�\n");
		printf("4.��ȡ�ļ����ݣ�������������\n");
		printf("======================================\n");
		printf("�����㷨��Ӧ��\n");
		printf("5.��ɫ����\n");
		printf("6.��һ�������������ҵ���K��/С����\n");
		printf("7.�˳�\n");
		printf("======================================\n");
		scanf_s("%c", &choice, 1);
		while (getchar() != '\n');
		if (choice == '1' || choice == '2' || choice == '3' || choice == '4' || choice == '5' || choice == '6' || choice == '7')
			break;
		else {
			printf("�����������������\n");
			system("pause");
			while (getchar() != '\n');
			continue;
		}
	}
	if (choice == '7') {
		printf("�˳��ɹ�\n");
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
		printf("��ѡ��Ҫ����ķ�ʽ\n");
		printf("================================\n");
		printf("1,��������\n");
		printf("2.�鲢����\n");
		printf("3.��������(�ݹ��)(�Ż�)\n");
		printf("4.��������(�ǵݹ��)\n");
		printf("5.��������\n");
		printf("6.��������\n");
		printf("7.ð������(�Ż�)\n");
		printf("8.�˳�\n");
		printf("=================================\n");
		scanf_s("%c", &choice, 1);
		if (choice == '1' || choice == '2' || choice == '3' || choice == '4' || choice == '5' || choice == '6' || choice == '7' || choice == '8')
			break;
		else {
			printf("�����������������\n");
			system("pause");
			while (getchar() != '\n');
			continue;
		}
	}
	if (choice == '8') {
		printf("�˳��ɹ�\n");
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

		// �����������
		for (int j = 0; j < size; j++) {
			nums[j] = rand();
		}
		//printf("����ǰ\n");
		//PrintNums(nums, size - 1);
		clock_t start = clock();
		sort(nums, 0, size - 1);
		clock_t end = clock();
		double cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
		//printf("�����:\n");
		//PrintNums(nums,size - 1);
		printf("\n%d��������������Ҫ����%lf ms\n", size, cpu_time_used);
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
	printf("\n����%d������%d��ƽ����ʱ%lf ms\n", DATA_SIZE, NUM_TESTS, total_time / NUM_TESTS);
}

void Generate_File(int size) {
	FILE* fp = fopen(FILENAME, "w");

	if (fp == NULL) {
		printf("���ļ�ʧ��\n");
		return;
	}
#pragma warning(push)
#pragma warning(disable : 4244)
	srand(time(NULL));
#pragma warning(pop)
	for (int i = 0; i < size; i++) {
		fprintf(fp, "%d ", rand() % DATA_RANGE);
	}
	printf("���ɲ������ݳɹ�!(������%d��0��%d��Χ������)\n", size, DATA_RANGE);
	printf("���ұ��浽%s�ļ���\n", FILENAME);
	fclose(fp);
}

void Reed_File(SortFunc sort, int size) {
	FILE* fp = fopen(FILENAME, "r");
	int* nums = (int*)malloc(DATA_SIZE * sizeof(int));
	if (nums == NULL) {
		printf("��������ʧ��\n");
		return;
	}
	if (fp == NULL) {
		printf("���ļ�ʧ��\n");
		return;
	}

	for (int i = 0; i < size; ++i) {
		if (fscanf(fp, "%d ", nums + i) != 1) {
			printf("�ļ���ʱû������\n");
			return;
		}
	}

	fclose(fp);
	printf("==========================================\n");
	printf("�Ѵ�%s��ȡ����\n", FILENAME);
	printf("����ǰ��\n");
	PrintNums(nums, size);
	sort(nums, 0, size - 1);
	printf("==========================================\n");
	printf("�����\n");
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
	printf("�õ���ǰ��������Ϊ:\n");
	PrintNums(nums, MAXSIZE);
	int k;
	printf("��Ҫ���ҵڼ�С������\n");
	while (scanf_s("%d", &k) != 1) {
		while (getchar() != '\n');
		printf("�����������������\n");
	}
	while (getchar() != '\n');
	if (k >= 1 && k <= MAXSIZE)
		printf("�� %d С����Ϊ��%d\n", k, kthSmallest(nums, 0, MAXSIZE - 1, k));
	else
		printf("�������,�����������Ҫ��1~%d��Χ��\n", MAXSIZE);
}

void sortColors(void) {
	int* nums = (int*)malloc(DATA_SIZE * sizeof(int));
	if (nums == NULL)
		return;

	for (int i = 0; i < DATA_SIZE; i++) {
		nums[i] = rand() % 3;
	}
	int left = 0, right = DATA_SIZE - 1, current = 0;

	printf("����ǰ:\n");
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
	printf("�����:\n");
	PrintNums(nums, DATA_SIZE);
}