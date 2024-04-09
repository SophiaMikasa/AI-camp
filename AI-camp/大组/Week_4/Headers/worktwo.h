#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include "workone.h"

#define MAX_HEAP_SIZE 100

// ����ѽṹ
typedef struct {
    int* elements; // �洢��Ԫ�ص�����
    int size;      // ��ǰ����Ԫ�ص�����
    int capacity;  // �ѵ�����
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
        printf("ѡ��һ\n");
        printf("==========\n");
        printf("1.����\n");
        printf("2.��С��\n");
        printf("3.�˳�\n");
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
            printf("�������,����������\n");
            system("pause");
            break;
        }
    }
}

void MaxHeapMenu(void) {
    MaxHeap maxheap = *createMaxHeap(MAX_HEAP_SIZE);
    int data;

    printf("������õ�����Ϊ%d�Ķ�\n", MAX_HEAP_SIZE);
    for (int i = 0; i < MAX_HEAP_SIZE; i++) {
        printf("�������%d������Ԫ��(����-1����):\n", i + 1);
        while (scanf_s("%d", &data) == 0) {
            while (getchar() != '\n');
            printf("�����������������\n");
        }
        while (getchar() != '\n');
        if (data == -1)
            break;
        insertMaxHeap(&maxheap, data);
    }
    if (maxheap.size == maxheap.capacity)
        printf("�ö��Ѿ�����\n");

    char choice;
    int top = 0;

    while (1) {
        system("cls");
        printf("===============\n");
        printf("��Ϊ�󶥶�\n");
        printf("===============\n");
        printf("1.����\n");
        printf("2.����\n");
        printf("3.��ȥ����\n");
        printf("4.�˳�\n");
        printf("===============\n");
        scanf_s("%c", &choice, 1);
        while (getchar() != '\n');
        switch (choice) {
        case '1':
            printf("������Ҫ���������Ԫ��:\n");
            while (scanf_s("%d", &data) == 0) {
                while (getchar() != '\n');
                printf("�����������������\n");
            }
            while (getchar() != '\n');
            insertMaxHeap(&maxheap, data);
            printf("����ɹ�!\n");
            system("pause");
            break;
        case '2':
            printHeap(&maxheap);
            system("pause");
            break;
        case '3':
            top = extractMax(&maxheap);
            printf("�õ��ĶѶ�Ϊ%d\n", top);
            system("pause");
            break;
        case '4':
            return;
        default:
            printf("�������,����������\n");
            system("pause");
            break;
        }
    }
}

void MinHeapMenu(void) {
    MinHeap minheap = *createMinHeap(MAX_HEAP_SIZE);
    int data;

    printf("������õ�����Ϊ%d�Ķ�\n", MAX_HEAP_SIZE);
    for (int i = 0; i < MAX_HEAP_SIZE; i++) {
        printf("�������%d������Ԫ��(����-1����):\n", i + 1);
        while (scanf_s("%d", &data) == 0) {
            while (getchar() != '\n');
            printf("�����������������\n");
        }
        while (getchar() != '\n');
        if (data == -1)
            break;
        insertMinHeap(&minheap, data);
    }
    if (minheap.size == minheap.capacity)
        printf("�ö��Ѿ�����\n");

    char choice;
    int top = 0;

    while (1) {
        system("cls");
        printf("===============\n");
        printf("��ΪС����\n");
        printf("===============\n");
        printf("1.����\n");
        printf("2.����\n");
        printf("3.��ȥ����\n");
        printf("4.�˳�\n");
        printf("===============\n");
        scanf_s("%c", &choice, 1);
        while (getchar() != '\n');
        switch (choice) {
        case '1':
            printf("������Ҫ���������Ԫ��:\n");
            while (scanf_s("%d", &data) == 0) {
                while (getchar() != '\n');
                printf("�����������������\n");
            }
            while (getchar() != '\n');
            insertMinHeap(&minheap, data);
            printf("����ɹ�!\n");
            system("pause");
            break;
        case '2':
            printHeap(&minheap);
            system("pause");
            break;
        case '3':
            top = extractMin(&minheap);
            printf("�õ��ĶѶ�Ϊ%d\n", top);
            system("pause");
            break;
        case '4':
            return;
        default:
            printf("�������,����������\n");
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
        printf("������,�����ٷ���Ԫ��\n");
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
        printf("���ѿ�,����ɾ���Ѷ�Ԫ��\n");
        return -1;
    }

    int minElement = heap->elements[0];
    heap->elements[0] = heap->elements[heap->size - 1];
    heap->size--;
    minHeapifyDown(heap, 0);
    return minElement;
}

void printHeap(Heap* heap) {
    printf("��Ԫ��:\n ");
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
        printf("�������������ٲ���Ԫ��\n");
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
        printf("���ѿգ�����ɾ���Ѷ�Ԫ��\n");
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