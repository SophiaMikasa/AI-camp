#pragma once
#include<stdio.h>
#include<stdlib.h>
#include"Stack.h"

//��������
void InsertSort(int nums[], int l,int r);
//�鲢����
void merge(int arr[], int l, int m, int r);
void MergeSort(int arr[], int l, int r);
//��������(�ݹ��)
int medianOfThree(int nums[], int low, int high);
int partition(int nums[], int low, int high);
void QuickSort_recursion(int nums[], int low, int high);
//��������(�ǵݹ��)
int partition_None(int nums[], int low, int high);
void QuickSort_None(int nums[], int low, int high);
//��������
void MinAndMax(int nums[], int len, int* min, int* max);
void CountSort(int nums[], int l,int r);
//��������
int GetCount(int flag, int num);
void SingleCountSort(int nums[], int flag, int len);
void RadixCountSort(int nums[], int l, int r);
//ð������(�Ż�)
void Bubble_Sort(int nums[], int l, int r);
//��������
void Swap(int* a, int* b);
//��ӡ����
void PrintNums(int nums[], int len);

//��������
void Swap(int* a, int* b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

//��ӡ����
void PrintNums(int nums[], int len) {
	for (int i = 0; i < len; i++) {
		if (i % 10 == 0)
			printf("\n");
		printf("%d ", *(nums + i));
	}
	printf("\n");
}

//��������
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

//�鲢����
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

//��������(�ݹ��)(�Ż�)
int medianOfThree(int nums[], int low, int high) {
	int mid = low + (high - low) / 2;
	// ��nums[low]��nums[mid]��nums[high]��������
	if (nums[low] > nums[mid])
		Swap(nums+low, nums+mid);
	if (nums[low] > nums[high])
		Swap(nums+low, nums +high);
	if (nums[mid] > nums[high])
		Swap(nums+mid, nums+high);
	// ���м�Ԫ����Ϊ���᷵��
	return mid;
}
int partition(int nums[], int low, int high) {
	//int mid = low + (high - low) / 2;
	//int pivotIndex = (nums[low] < nums[mid]) ?
	//	((nums[mid] < nums[high]) ? mid : ((nums[low] < nums[high]) ? high : low)) :
	//	((nums[low] < nums[high]) ? low : ((nums[mid] < nums[high]) ? high : mid));
	int pivotIndex = medianOfThree(nums, low, high); // ѡȡ����, low, high); // ѡȡ����
	int pivot = nums[high];
	Swap(nums + pivotIndex, nums + high); // ������ŵ�����ĩβ
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

//��������(�ǵݹ��)
int partition_None(int nums[], int low, int high) {
	int pivot = nums[high]; // ѡ�����һ��Ԫ����Ϊ��׼ֵ
	int i = (low - 1); // ��ʼ���������λ��

	for (int j = low; j < high; j++)
		if (nums[j] <= pivot)
			Swap(nums + ++i, nums + j);
	Swap(nums + i + 1, nums + high);
	return (i + 1);
}
void QuickSort_None(int nums[], int low, int high) {
	// ��������ջ
	Stack* stack = createStack(high - low + 1);

	// ����ʼ�ĵ�λ�����͸�λ������ջ
	push(stack, low);
	push(stack, high);

	// ѭ������ջ�е�Ԫ��
	while (!isEmpty(stack)) {
		// ��ջ����ȡ��ǰ������ĵ�λ�͸�λ����
		high = pop(stack);
		low = pop(stack);

		// �Ե�ǰ��������з���
		int pi = partition_None(nums, low, high);

		// �����������໹��Ԫ�أ������������ı߽���ջ
		if (pi - 1 > low) {
			push(stack, low);
			push(stack, pi - 1);
		}

		// ����������Ҳ໹��Ԫ�أ����Ҳ�������ı߽���ջ
		if (pi + 1 < high) {
			push(stack, pi + 1);
			push(stack, high);
		}
	}

	// �ͷŶ�̬������ڴ�
	free(stack->arr);
	free(stack);
}

//��������
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

//��������
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

//ð������
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

//ʧ������
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