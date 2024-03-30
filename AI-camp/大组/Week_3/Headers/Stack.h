#pragma once
#include<stdio.h>
#include<stdlib.h>

// ��������ջ�ṹ��
typedef struct {
    int* arr; // ջ������
    int capacity; // ջ������
    int top; // ջ��ָ��
} Stack;

// ��ʼ��ջ
static Stack* createStack(int capacity) {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    if (stack == NULL)
        return NULL;
    stack->capacity = capacity;
    stack->top = -1;
    stack->arr = (int*)malloc(stack->capacity * sizeof(int));
    return stack;
}

// �ж�ջ�Ƿ�Ϊ��
static int isEmpty(Stack* stack) {
    return stack->top == -1;
}

// �ж�ջ�Ƿ�����
static int isFull(Stack* stack) {
    return stack->top == stack->capacity - 1;
}

// ��ջ����
static void push(Stack* stack, int item) {
    if (isFull(stack)) return; // ���ջ��������ִ�в���
    stack->arr[++stack->top] = item;
}

// ��ջ����
static int pop(Stack* stack) {
    if (isEmpty(stack)) return -1; // ���ջΪ�գ��򷵻�-1
    return stack->arr[stack->top--];
}