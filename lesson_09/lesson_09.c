#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>

/*
* 1. Описать очередь с приоритетным исключением
*/
/* структура, представляющая элемент очереди */
struct Item
{
    int priority;
    int value;
};

/* структура, представляющая очередь */
struct PriorityQueue
{
    struct Item *data;
    int size;
    int count;
};

/* создает очередь */
struct PriorityQueue *create_queue(int size)
{
    struct PriorityQueue *queue  = (struct PriorityQueue*)malloc(sizeof(struct PriorityQueue));
    queue->size = size;
    queue->count = 0;
    queue->data = (struct Item*)malloc(sizeof(struct Item) * size);
    return queue;
}

/* проверяет заполнена ли очередь */
bool is_queue_full(struct PriorityQueue *queue)
{
    return queue->count == queue->size;
}

/* проверяет пуста ли очередь */
bool is_queue_empty(struct PriorityQueue *queue)
{
    return queue->count == 0;
}

/* вставляет элемент в конец очереди, если очередь не заполнена*/
void enqueue(struct PriorityQueue *queue, int value, int priority)
{
    if (is_queue_full(queue)) {
        printf("Queue is full");
        return;
    }
    struct Item item;
    item.priority = priority;
    item.value = value;
    queue->data[queue->count++] = item;
}

/*
* удаляет элемент из очереди в соответсвии с проиритетом
* так как приоритет является в большей степени служебной
* информацией, я решил возвращать только значение, а не всю структуру Item  
*/
int dequeue(struct PriorityQueue *queue)
{
    if (is_queue_empty(queue)) {
        printf("Queue is empty");
        exit(1);
    }

    int max_idx = 0;
    int max_priority = 0;
    for (int i = 0; i < queue->count; ++i) {
        if (queue->data[i].priority > max_priority) {
            max_priority = queue->data[i].priority;
            max_idx = i;
        }
    }

    int result = queue->data[max_idx].value;
    queue->data[max_idx] = queue->data[queue->count - 1];
    queue->count--;
    return result;
}

/*
* 2. Реализовать перевод из десятичной в двоичную систему счисления
* с использованием стека.
*/
struct Stack{
    int top;
    int size;
    int* data;
};

/* создает стек в куче, возвращает указатель на него */
struct Stack* create_stack(int size)
{
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    stack->size = size;
    stack->top = -1;
    stack->data = (int*)malloc(sizeof(int) * size);
    return stack;
}

/* проверяет заполнен ли стек */
bool is_stack_full(struct Stack* stack) 
{
    return stack->top == stack->size - 1;
}

/* проверяет пуст ли стек */
bool is_stack_empty(struct Stack* stack)
{
    return stack->top == -1;
}

/* 
* добавляет значение на вершину стека
* в случае, если стек не заполнен
*/
void push(struct Stack* stack, int value)
{
    if (is_stack_full(stack)) {
        printf("Stack is full\n");
        return;
    }
    stack->data[++stack->top] = value;
}

/* 
* возвращает значение с вершины стека
* в случае, если стек не пуст
*/
int pop(struct Stack* stack)
{
    if (is_stack_empty(stack)) {
        printf("Stack is empty\n");
        exit(1);
    }
    return stack->data[stack->top--];
}

/* 
* конвертирует десятичное число в двоичное представление
* с помощью стека
*/
char* itob(int value) {
    struct Stack* stack = create_stack(32);
    while (value > 0) {
        push(stack, value & 1);
        value >>= 1;
    }
    char* result = (char*)malloc(sizeof(char) * stack->size + 1);
    int i = 0;
    while (!is_stack_empty(stack)) {
        char ch = pop(stack) + '0';
        result[i++] = ch;
    }
    result[i] = '\0';
    return result;
}

int main(void)
{
    // тестирование приоритетной очереди
    struct PriorityQueue *queue = create_queue(10);
    enqueue(queue, 10, 10);
    enqueue(queue, 50, 50);
    enqueue(queue, 20, 20);
    enqueue(queue, 40, 40);
    enqueue(queue, 30, 30);
    enqueue(queue, 20, 20);

    while (!is_queue_empty(queue)) {
        printf("%3d", dequeue(queue));      /*50 40 30 20 20 10*/
    }
    printf("\n===================\n");
    
    // тестирование конверсии десятичного числа
    // в двоичное представление с помощью самого стека
    struct Stack* st = create_stack(32);
    int i = 2;
    while (i > 0) {
        push(st, i & 1);
        i >>= 1;
    } 

    while (!is_stack_empty(st)) {
        printf("%d", pop(st));              /*10*/
    }
    printf("\n");
    
    // с помощью фуркции, использующей стек под капотом
    char *str = itob(INT_MAX);
    printf("%s: %d\n", str, strlen(str));   /*1111111111111111111111111111111: 31*/
}