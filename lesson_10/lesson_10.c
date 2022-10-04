#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/*
* 1. Написать программу, которая определяет, является ли введенная скобочная последовательность правильной.
*/
struct Item
{
    char ch;
    struct Item *next;
};

struct Stack
{
    struct Item *head;
    int size;
};

struct Stack *init_stack() 
{
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    stack->head = NULL;
    stack->size = 0;
}
int is_empty(struct Stack *stack)
{
    return stack->head == NULL;
}

void push(struct Stack *stack, char bracket)
{
    struct Item *t = malloc(sizeof(struct Item));
    t->ch = bracket;
    t->next = stack->head;
    stack->head = t;
    stack->size++;
}

char pop(struct Stack *stack)
{
    struct Item *t = stack->head;
    stack->head = stack->head->next;
    stack->size--;
    char ch = t->ch;
    free(t);
    return ch;
}

void check_brackets(char* expression)
{
    struct Stack *brackets = init_stack();
    for (int i = 0; i < strlen(expression); ++i) {
        char ch = expression[i];
        switch (ch) {
            case '(':
                push(brackets, ')');
                break;
            case '[':
                push(brackets, ']');
                break;
            case '{':
                push(brackets, '}');
                break;
            case ')':
            case ']':
            case '}':
                if (!is_empty(brackets)) {
                    char chx = pop(brackets);
                    if (ch != chx) {
                        printf("Ошибка на позиции %d: %c вместо %c\n", i, chx, ch);
                    }
                } else {
                    printf("Ошибка на позиции %d: непарная закрывающая скобка\n", i);
                }
        }
    }
    if (!is_empty(brackets)) {
        printf("Cкобочная последовательность неправильная: нет закрывающих скобок\n");
    } else {
        printf("Cкобочная последовательность правильная\n");
    }
}

/*
 * 2. Создать функцию, копирующую односвязный список (без удаления первого списка).
 * для копирования решил использовать уже определенный список Stack и функции, работающие с ним
*/
struct Stack* copy_stack(struct Stack *orig)
{
    struct Stack *copy = init_stack();

    struct Item *copy_curr = NULL;
    struct Item *orig_curr = orig->head;
    
    while (orig_curr != NULL) {
        struct Item *t = (struct Item*)malloc(sizeof(struct Item));
        t->ch = orig_curr->ch;
        t->next = NULL;

        if (copy->head == NULL) {
            copy_curr = t;
            copy->head = copy_curr;
            copy->size++;
        } else {
            copy_curr->next = t;
            copy_curr = copy_curr->next;
            copy->size++;
        }

        orig_curr = orig_curr->next;
    }

    return copy;
}

void print_list(struct Stack* stack) {
    struct Item *it = stack->head;
    for (int i = 0; i < stack->size; ++i) {
        printf("[%c]", it->ch);
        it = it->next;
    }
    printf("\n");
}

/*
 * 3. Реализуйте алгоритм, который определяет, отсортирован ли связный список.
*/
bool is_sorted(struct Stack* stack)
{
    bool ascending = false;
    bool descending = false;

    struct Item *prev = stack->head;
    struct Item *curr = stack->head->next;

    while (curr != NULL) {
        if (prev->ch <= curr->ch) {
            ascending = true;
        } else {
            descending = true;
        }
        if (ascending == descending) {
            return false;
        }
        prev = prev->next;
        curr = curr->next;
    }

    return true;
}

int main(void)
{
    // тест задания 1
    char *expr1 = "([{}])";
    check_brackets(expr1);
    char *expr2 = "([(])";
    check_brackets(expr2);

    // тест задания 2
    char *str1 = "abcd";
    struct Stack *s1 = init_stack();
    while (*str1 != '\0') {
        push(s1, *str1++);
    }
    print_list(s1);
    struct Stack *s2 = copy_stack(s1);
    print_list(s2);

    // тест задания 3 
    printf("Стек 1 %s\n", is_sorted(s1) ? "отсортирован" : "неотсортирован");
    struct Stack *s3 = init_stack();
    char *str2 = "qwerty";
    while (*str2 != '\0') {
        push(s3, *str2++);
    }
    printf("Стек 3 %s\n", is_sorted(s3) ? "отсортирован" : "неотсортирован");

    return 0;
}