#pragma once
#include<stdio.h>
#include<stdlib.h>
#include"Stack.h"

//插入排序
void InsertSort(int nums[], int l,int r);
//归并排序
void merge(int arr[], int l, int m, int r);
void MergeSort(int arr[], int l, int r);
//快速排序(递归版)
int medianOfThree(int nums[], int low, int high);
int partition(int nums[], int low, int high);
void QuickSort_recursion(int nums[], int low, int high);
//快速排序(非递归版)
int partition_None(int nums[], int low, int high);
void QuickSort_None(int nums[], int low, int high);
//计数排序
void MinAndMax(int nums[], int len, int* min, int* max);
void CountSort(int nums[], int l,int r);
//基数排序
int GetCount(int flag, int num);
void SingleCountSort(int nums[], int flag, int len);
void RadixCountSort(int nums[], int l, int r);
//冒泡排序(优化)
void Bubble_Sort(int nums[], int l, int r);
//两数交换
void Swap(int* a, int* b);
//打印数组
void PrintNums(int nums[], int len);

//两数交换
void Swap(int* a, int* b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

//打印数组
void PrintNums(int nums[], int len) {
	for (int i = 0; i < len; i++) {
		if (i % 10 == 0)
			printf("\n");
		printf("%d ", *(nums + i));
	}
	printf("\n");
}

//插入排序
void InsertSort(int nums[], int l,int r) {
	for (int i = 1; i < r + 1; i++) {
		int* current = nums + i;

		for (int j = i; j > 0; j--) {
			if (*(nums + i) < *(nums + j - 1))
				Swap(nums + i--, nums + j - 1);
			else
				break;
		}
	}
}

//归并排序
void merge(int nums[], int l, int m, int r) {
	int i = 0, j = 0, k = 1;
	int n1 = m - l + 1;
	int n2 = r - m;
	int* L = (int*)malloc(n1 * sizeof(int));
	int* R = (int*)malloc(n2 * sizeof(int));

	if (L == NULL || R == NULL)
		return;

	for (i = 0; i < n1; i++)
		L[i] = nums[l + i];
	for (j = 0; j < n2; j++)
		R[j] = nums[m + 1 + j];
	i = 0;
	j = 0;
	k = l;
	while (i < n1 && j < n2) {
		if (L[i] <= R[j])
			nums[k++] = L[i++];
		else
			nums[k++] = R[j++];
	}
	while (i < n1)
		nums[k++] = L[i++];
	while (j < n2)
		nums[k++] = R[j++];
}
void MergeSort(int nums[], int l, int r) {
	if (l < r) {
		int m = l + (r - l) / 2;

		MergeSort(nums, l, m);
		MergeSort(nums, m + 1, r);
		merge(nums, l, m, r);
	}
}

//快速排序(递归版)(优化)
int medianOfThree(int nums[], int low, int high) {
	int mid = low + (high - low) / 2;
	// 对nums[low]、nums[mid]、nums[high]进行排序
	if (nums[low] > nums[mid])
		Swap(nums+low, nums+mid);
	if (nums[low] > nums[high])
		Swap(nums+low, nums +high);
	if (nums[mid] > nums[high])
		Swap(nums+mid, nums+high);
	// 将中间元素作为枢轴返回
	return mid;
}
int partition(int nums[], int low, int high) {
	//int mid = low + (high - low) / 2;
	//int pivotIndex = (nums[low] < nums[mid]) ?
	//	((nums[mid] < nums[high]) ? mid : ((nums[low] < nums[high]) ? high : low)) :
	//	((nums[low] < nums[high]) ? low : ((nums[mid] < nums[high]) ? high : mid));
	int pivotIndex = medianOfThree(nums, low, high); // 选取枢轴, low, high); // 选取枢轴
	int pivot = nums[high];
	Swap(nums + pivotIndex, nums + high); // 将枢轴放到数组末尾
	int i = (low - 1);

	for (int j = low; j < high; j++)
		if (nums[j] <= pivot)
			Swap(nums + ++i, nums + j);
	Swap(nums + i + 1, nums + high);
	return (i + 1);
}
void QuickSort_recursion(int nums[], int low, int high) {
	if (high - low > 20) {
		if (low < high) {
			int pi = partition(nums, low, high);

			QuickSort_recursion(nums, low, pi - 1);
			QuickSort_recursion(nums, pi + 1, high);
		}
	}
	else
		InsertSort(nums, 0, high - low);
}

//快速排序(非递归版)
int partition_None(int nums[], int low, int high) {
	int pivot = nums[high]; // 选择最后一个元素作为基准值
	int i = (low - 1); // 初始化分区点的位置

	for (int j = low; j < high; j++)
		if (nums[j] <= pivot)
			Swap(nums + ++i, nums + j);
	Swap(nums + i + 1, nums + high);
	return (i + 1);
}
void QuickSort_None(int nums[], int low, int high) {
	// 创建辅助栈
	Stack* stack = createStack(high - low + 1);

	// 将初始的低位索引和高位索引入栈
	push(stack, low);
	push(stack, high);

	// 循环处理栈中的元素
	while (!isEmpty(stack)) {
		// 出栈，获取当前子数组的低位和高位索引
		high = pop(stack);
		low = pop(stack);

		// 对当前子数组进行分区
		int pi = partition_None(nums, low, high);

		// 如果分区点左侧还有元素，则将左侧子数组的边界入栈
		if (pi - 1 > low) {
			push(stack, low);
			push(stack, pi - 1);
		}

		// 如果分区点右侧还有元素，则将右侧子数组的边界入栈
		if (pi + 1 < high) {
			push(stack, pi + 1);
			push(stack, high);
		}
	}

	// 释放动态分配的内存
	free(stack->arr);
	free(stack);
}

//计数排序
void MinAndMax(int nums[], int len, int* min, int* max) {
	*min = *max = nums[0];

	for (int i = 0; i < len; i++) {
		if (*min > nums[i])
			*min = nums[i];
		else if (*max < nums[i])
			*max = nums[i];
	}
}
void CountSort(int nums[], int l,int r) {
	int min, max;
	MinAndMax(nums, r + 1, &min, &max);
	int bias = min;
	int relative_len = max - min + 1;
	int* temp = (int*)malloc(sizeof(int) * relative_len);

	if (temp == NULL)
		return;

	for (int i = 0; i < relative_len; i++)
		temp[i] = 0;
	for (int i = 0; i < r + 1; i++)
		temp[nums[i] - bias]++;
	for (int i = 0, k = 0; i < relative_len; i++) {
		for (int j = 0; j < temp[i]; j++)
			nums[k++] = i + bias;
	}
}

//基数排序
int GetCount(int flag, int num) {
	for (int i = flag; i > 0; i--) {
		if (i == 1)
			num %= 10;
		else
			num /= 10;
	}

	return num;
}
void SingleCountSort(int nums[], int flag, int len) {
	int length[10] = { 0 };
	int** p = (int**)malloc(sizeof(int*) * 10);

	if (p == NULL || *p == NULL)
		return;

	for (int i = 0; i < len; i++)
		length[GetCount(flag, nums[i])]++;
	for (int i = 0; i < 10; i++) {
		int* ip = (int*)malloc(sizeof(int) * length[i]);
		if (ip == NULL)
			return;
		p[i] = ip;
	}

	int move[10] = { 0 };

	for (int i = 0; i < len; i++) {
		int index = GetCount(flag, nums[i]);
		p[index][move[index]] = nums[i];
		move[index]++;
	}
	for (int j = 0, i = 0; j < 10; j++)
		for (int k = 0; k < length[j]; k++)
			nums[i++] = p[j][k];
}
void RadixCountSort(int nums[], int l,int r) {
	int max = nums[0];
	int flag = 1;

	for (int i = 0; i < r + 1; i++)
		if (nums[i] > max)
			max = nums[i];
	while (max /= 10)
		flag++;
	for (int i = 0; i < flag; i++)
		SingleCountSort(nums, i + 1, r + 1);
}

//冒泡排序
void Bubble_Sort(int nums[], int l, int r) {
	for (int i = 0; i < r; i++) {
		int flag = 1;
		int position = r + 1;
		for (int j = 0; j < r - i; j++) {
			if (position == j)
				break;
			if (nums[j] > nums[j + 1]) {
				Swap(nums + j, nums + j + 1);
				position = j;
				flag = 0;
			}
			//if (new_flag == old_flag)
			//	break;
		}
		if (flag)
			break;
	}
}

//失败用例
//void MergeSort(int nums[], int len) {
//	if (len > 1) {
//		int* fhalf_nums = nums + len / 2;
//		MergeSort(fhalf_nums, len / 2);
//		MergeSort(nums, len / 2);
//
//		int* temp = (int*)malloc(sizeof(int) * len);
//		int n = 0, m = len / 2, t = 0;
//		while (1) {
//			if (n < len / 2 || m < len) {
//				if (*(fhalf_nums + n) > *(nums + m)) {
//					*(temp + t) = *(nums + m++);
//				}
//				else
//					*(temp + t) = *(fhalf_nums + n++);
//				t += 1;
//			}
//			else
//				break;
//		}
//		for (; n < len / 2;)
//			*(temp + t++) = *(fhalf_nums + n++);
//		for (; m < len;)
//			*(temp + t++) = *(nums + m++);
//		for (int i = 0; i < len; i++)
//			*(nums + i) = *(temp + i);
//	}
//}