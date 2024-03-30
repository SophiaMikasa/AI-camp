#pragma once
#include<stdio.h>
#include<stdlib.h>

// 创建辅助栈结构体
typedef struct {
    int* arr; // 栈的数组
    int capacity; // 栈的容量
    int top; // 栈顶指针
} Stack;

// 初始化栈
static Stack* createStack(int capacity) {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    if (stack == NULL)
        return NULL;
    stack->capacity = capacity;
    stack->top = -1;
    stack->arr = (int*)malloc(stack->capacity * sizeof(int));
    return stack;
}

// 判断栈是否为空
static int isEmpty(Stack* stack) {
    return stack->top == -1;
}

// 判断栈是否已满
static int isFull(Stack* stack) {
    return stack->top == stack->capacity - 1;
}

// 入栈操作
static void push(Stack* stack, int item) {
    if (isFull(stack)) return; // 如果栈已满，则不执行操作
    stack->arr[++stack->top] = item;
}

// 出栈操作
static int pop(Stack* stack) {
    if (isEmpty(stack)) return -1; // 如果栈为空，则返回-1
    return stack->arr[stack->top--];
}