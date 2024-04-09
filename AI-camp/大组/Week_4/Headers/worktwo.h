#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include "workone.h"

#define MAX_HEAP_SIZE 100

// 定义堆结构
typedef struct {
    int* elements; // 存储堆元素的数组
    int size;      // 当前堆中元素的数量
    int capacity;  // 堆的容量
} MinHeap, MaxHeap, Heap;

void WorkTwoMenu(void);
void MaxHeapMenu(void);
void MinHeapMenu(void);
MinHeap* createMinHeap(int capacity);
void minHeapifyUp(MinHeap* heap, int index);
void insertMinHeap(MinHeap* heap, int value);
void minHeapifyDown(MinHeap* heap, int index);
int extractMin(MinHeap* heap);
void printHeap(Heap* heap);
MaxHeap* createMaxHeap(int capacity);
void maxHeapifyUp(MaxHeap* heap, int index);
void insertMaxHeap(MaxHeap* heap, int value);
void maxHeapifyDown(MaxHeap* heap, int index);
int extractMax(MaxHeap* heap);

void WorkTwoMenu(void) {
    char choice;

    while (1) {
        system("cls");
        printf("==========\n");
        printf("选做一\n");
        printf("==========\n");
        printf("1.最大堆\n");
        printf("2.最小堆\n");
        printf("3.退出\n");
        printf("==========\n");
        scanf_s("%c", &choice, 1);
        while (getchar() != '\n');
        switch (choice) {
        case '1':
            MaxHeapMenu();
            break;
        case '2':
            MinHeapMenu();
            break;
        case '3':
            return;
        default:
            printf("输入错误,请重新输入\n");
            system("pause");
            break;
        }
    }
}

void MaxHeapMenu(void) {
    MaxHeap maxheap = *createMaxHeap(MAX_HEAP_SIZE);
    int data;

    printf("现在你得到容量为%d的堆\n", MAX_HEAP_SIZE);
    for (int i = 0; i < MAX_HEAP_SIZE; i++) {
        printf("请输入第%d个整数元素(输入-1结束):\n", i + 1);
        while (scanf_s("%d", &data) == 0) {
            while (getchar() != '\n');
            printf("输入错误请重新输入\n");
        }
        while (getchar() != '\n');
        if (data == -1)
            break;
        insertMaxHeap(&maxheap, data);
    }
    if (maxheap.size == maxheap.capacity)
        printf("该堆已经满了\n");

    char choice;
    int top = 0;

    while (1) {
        system("cls");
        printf("===============\n");
        printf("此为大顶堆\n");
        printf("===============\n");
        printf("1.插入\n");
        printf("2.遍历\n");
        printf("3.除去顶端\n");
        printf("4.退出\n");
        printf("===============\n");
        scanf_s("%c", &choice, 1);
        while (getchar() != '\n');
        switch (choice) {
        case '1':
            printf("请输入要插入的整数元素:\n");
            while (scanf_s("%d", &data) == 0) {
                while (getchar() != '\n');
                printf("输入错误请重新输入\n");
            }
            while (getchar() != '\n');
            insertMaxHeap(&maxheap, data);
            printf("插入成功!\n");
            system("pause");
            break;
        case '2':
            printHeap(&maxheap);
            system("pause");
            break;
        case '3':
            top = extractMax(&maxheap);
            printf("得到的堆顶为%d\n", top);
            system("pause");
            break;
        case '4':
            return;
        default:
            printf("输入错误,请重新输入\n");
            system("pause");
            break;
        }
    }
}

void MinHeapMenu(void) {
    MinHeap minheap = *createMinHeap(MAX_HEAP_SIZE);
    int data;

    printf("现在你得到容量为%d的堆\n", MAX_HEAP_SIZE);
    for (int i = 0; i < MAX_HEAP_SIZE; i++) {
        printf("请输入第%d个整数元素(输入-1结束):\n", i + 1);
        while (scanf_s("%d", &data) == 0) {
            while (getchar() != '\n');
            printf("输入错误请重新输入\n");
        }
        while (getchar() != '\n');
        if (data == -1)
            break;
        insertMinHeap(&minheap, data);
    }
    if (minheap.size == minheap.capacity)
        printf("该堆已经满了\n");

    char choice;
    int top = 0;

    while (1) {
        system("cls");
        printf("===============\n");
        printf("此为小顶堆\n");
        printf("===============\n");
        printf("1.插入\n");
        printf("2.遍历\n");
        printf("3.除去顶端\n");
        printf("4.退出\n");
        printf("===============\n");
        scanf_s("%c", &choice, 1);
        while (getchar() != '\n');
        switch (choice) {
        case '1':
            printf("请输入要插入的整数元素:\n");
            while (scanf_s("%d", &data) == 0) {
                while (getchar() != '\n');
                printf("输入错误请重新输入\n");
            }
            while (getchar() != '\n');
            insertMinHeap(&minheap, data);
            printf("插入成功!\n");
            system("pause");
            break;
        case '2':
            printHeap(&minheap);
            system("pause");
            break;
        case '3':
            top = extractMin(&minheap);
            printf("得到的堆顶为%d\n", top);
            system("pause");
            break;
        case '4':
            return;
        default:
            printf("输入错误,请重新输入\n");
            system("pause");
            break;
        }
    }
}

MinHeap* createMinHeap(int capacity) {
    MinHeap* heap = (MinHeap*)malloc(sizeof(MinHeap));
    if (heap == NULL)
        return NULL;
    heap->elements = (int*)malloc(capacity * sizeof(int));
    heap->size = 0;
    heap->capacity = capacity;
    return heap;
}

void minHeapifyUp(MinHeap* heap, int index) {
    int parent = (index - 1) / 2;
    while (index > 0 && heap->elements[index] < heap->elements[parent]) {
        int temp = heap->elements[index];
        heap->elements[index] = heap->elements[parent];
        heap->elements[parent] = temp;

        index = parent;
        parent = (index - 1) / 2;
    }
}

void insertMinHeap(MinHeap* heap, int value) {
    if (heap->size < heap->capacity) {
        heap->elements[heap->size] = value;
        heap->size++;
        minHeapifyUp(heap, heap->size - 1);
    }
    else {
        printf("堆已满,不能再放入元素\n");
    }
}

void minHeapifyDown(MinHeap* heap, int index) {
    int leftChild = 2 * index + 1;
    int rightChild = 2 * index + 2;
    int smallest = index;

    if (leftChild < heap->size && heap->elements[leftChild] < heap->elements[smallest]) {
        smallest = leftChild;
    }
    if (rightChild < heap->size && heap->elements[rightChild] < heap->elements[smallest]) {
        smallest = rightChild;
    }

    if (smallest != index) {
        int temp = heap->elements[index];
        heap->elements[index] = heap->elements[smallest];
        heap->elements[smallest] = temp;
        minHeapifyDown(heap, smallest);
    }
}

int extractMin(MinHeap* heap) {
    if (heap->size <= 0) {
        printf("堆已空,不能删除堆顶元素\n");
        return -1;
    }

    int minElement = heap->elements[0];
    heap->elements[0] = heap->elements[heap->size - 1];
    heap->size--;
    minHeapifyDown(heap, 0);
    return minElement;
}

void printHeap(Heap* heap) {
    printf("堆元素:\n ");
    for (int i = 0; i < heap->size; ++i) {
        printf("%d ", heap->elements[i]);
    }
    printf("\n");
}

MaxHeap* createMaxHeap(int capacity) {
    MaxHeap* heap = (MaxHeap*)malloc(sizeof(MaxHeap));
    if (heap == NULL)
        return NULL;
    heap->elements = (int*)malloc(sizeof(int) * capacity);
    heap->size = 0;
    heap->capacity = capacity;

    return heap;
}

void maxHeapifyUp(MaxHeap* heap, int index) {
    int parent = (index - 1) / 2;
    while (index > 0 && heap->elements[parent] < heap->elements[index]) {
        int temp = heap->elements[parent];
        heap->elements[parent] = heap->elements[index];
        heap->elements[index] = temp;

        index = parent;
        parent = (index - 1) / 2;
    }
}

void insertMaxHeap(MaxHeap* heap, int value) {
    if (heap->capacity == heap->size) {
        printf("堆已满，不能再插入元素\n");
        return;
    }
    else {
        heap->elements[heap->size] = value;
        heap->size++;
        maxHeapifyUp(heap, heap->size - 1);
    }
}

void maxHeapifyDown(MaxHeap* heap, int index) {
    int leftChild = index * 2;
    int rightChild = index * 2 + 1;
    int largest = index;

    if (heap->elements[leftChild] > heap->elements[largest] && leftChild < heap->size)
        largest = leftChild;
    if (heap->elements[rightChild] > heap->elements[largest] && rightChild < heap->size)
        largest = rightChild;

    if (largest != index) {
        int temp = heap->elements[largest];
        heap->elements[largest] = heap->elements[index];
        heap->elements[index] = temp;
        maxHeapifyDown(heap, largest);
    }
}

int extractMax(MaxHeap* heap) {
    if (heap->size <= 0) {
        printf("堆已空，不能删除堆顶元素\n");
        return -1;
    }
    else {
        int max = heap->elements[0];
        heap->elements[0] = heap->elements[heap->size - 1];
        heap->size--;
        maxHeapifyDown(heap, 0);
        return max;
    }
}