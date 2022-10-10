#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*
* Функции для работы с бинарным деревом
*/
// #define T char
#define T int

struct Node
{
    T data;
    struct Node *left;
    struct Node *right;
};

struct BinTree
{
    struct Node *root;
};

// инициализация нового дерева
struct BinTree *init() 
{
    struct BinTree *t = (struct BinTree*)malloc(sizeof(struct BinTree));
}

// поиск в дереве
struct Node *find(struct BinTree *bintree, int key)
{
    struct Node *current = bintree->root;
    
    if (bintree->root == NULL) {
        return NULL;
    }

    while (current != NULL) {
        if (key < current->data) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    return current;
}

// вставка в дерево
void insert(struct BinTree *bintree, int key) 
{
    struct Node *new_node = (struct Node*)malloc(sizeof(struct Node));
    new_node->data = key;
    new_node->left = NULL;
    new_node->right = NULL;

    struct Node *current = bintree->root;
    struct Node *parent;

    if (bintree->root == NULL) {
        bintree->root = new_node;
        return;
    }

    while (current != NULL) {
        parent = current;
        if (key < current->data) {
            current = current->left;
            if (current == NULL) {
                parent->left = new_node;
                return;
            }
        } else {
            current = current->right;
            if (current == NULL) {
                parent->right = new_node;
                return;
            }
        }
    }
}

// удаление из дерева
struct Node *get_successor(struct Node *to_delete)
{
    struct Node *successor_parent = to_delete;
    struct Node *successor = to_delete;
    struct Node *current = to_delete->right;

    while (current != NULL) {
        successor_parent = successor;
        successor = current;
        current = current->left;
    }

    if (successor != to_delete->right) {
        successor_parent->left = successor->right;
        successor->right = to_delete->right;
    }

    return successor;
}

void delete(struct BinTree *bintree, int key) 
{
    struct Node *current = bintree->root;
    struct Node *parent;
    bool is_left = true;

    // ищем узел для удаления
    while (current != NULL && current->data != key) {
        parent = current;
        if (key < current->data) {
            current = current->left;
            is_left = true;
        } else {
            current = current->right;
            is_left = false;
        }
    }

    // узел не найден
    if (current == NULL) {
        return;
    }
    // узел найден
    if (current->left == NULL && current->right == NULL) {
        // узел не имеет наследников
        if (current == bintree->root) {
            bintree->root = NULL;
        } else if (is_left) {
            parent->left = NULL;
        } else {
            parent->right = NULL;
        }
    } else if (current->right == NULL) {
        // узел имеет одного наследника слева
        if (current == bintree->root) {
            bintree->root = current->left;
        } else if (is_left) {
            parent->left = current->left;
        } else {
            parent->right = current->left;
        }
    } else if (current->left == NULL) {
        // узел имеет одного наследника справа
        if (current == bintree->root) {
            bintree->root = current->right;
        } else if (is_left) {
            parent->left = current->right;
        } else {
            parent->right = current->left;
        }
    } else {
        // узел имеет двух наследников
        struct Node *successor = get_successor(current);
        if (current == bintree->root) {
            bintree->root = successor;
        } else if (is_left) {
            parent->left = successor;
        } else {
            parent->right = successor;
        }
        successor->left = current->left;
    }
    // current все еще хранит указатель на удаленный узел
    free(current);
}
// обход дерева
// печать дерева indorder
void print_tree(struct Node *node)
{
    if (node == NULL) {
        return;
    }
    print_tree(node->left);
    printf("%c ", node->data);
    print_tree(node->right);
}

/*
 * 1. Написать функцию проверяющую является ли переданное в неё бинарное дерево сбалансированным
*/
// проверка высоты дерева
int max(int a, int b)
{
    return a > b ? a : b;
}

int height(struct Node *node) 
{
    if (node == NULL) {
        return 0;
    }
    return 1 + max(height(node->left), height(node->right));
}

// если высота правого и левого поддеревьев отличаются более чем на 1
// дерево не сбвлвнсировано
bool is_balanced(struct BinTree* tree)
{
    if (abs(height(tree->root->left) - height(tree->root->right)) > 1) {
        return false;
    }
    return true;
}

/**
 * 4. Написать рекурсивную функцию бинарного поиска в дереве хранящемся в узлах, а не в массиве.
*/
bool bin_search(struct Node *root, T key) 
{
    struct Node *current = root;
    if (current == NULL) {
        return false;
    } else if (key == current->data) {
        return true;
    } else if (key < current->data) {
        return bin_search(current->left, key);
    } else {
        return bin_search(current->right, key);
    }
}

bool bin_search_tree(struct BinTree *tree, T key)
{
    return bin_search(tree->root, key);
}

int main(void)
{
    struct BinTree *tree = init();;
    // проверка вспомогательных функций
    // insert(tree, 'D');
    // insert(tree, 'B');
    // insert(tree, 'A');
    // insert(tree, 'C');
    // insert(tree, 'F');
    // insert(tree, 'E');
    // insert(tree, 'I');
    // insert(tree, 'G');
    // insert(tree, 'H');
    // insert(tree, 'J');

    // print_tree(tree->root);
    // printf("\n");

    // delete(tree, 'A');
    // delete(tree, 'B');
    // delete(tree, 'F');//
    // delete(tree, 'D');//

    // print_tree(tree->root);
    // printf("\nОжидается: C E G H I J\n");

    // проверка задания 1
    insert(tree, 2);
    insert(tree, 1);
    insert(tree, 3);
    insert(tree, 4);
    insert(tree, 5);
    print_tree(tree->root);
    printf("\n");
    printf("Высота дерева: %d\n", height(tree->root));                      // высота 4
    printf("Дерево %sсбалансировано\n", is_balanced(tree) ? "" : "не");    // несбалансировано

    delete(tree, 2);
    insert(tree, 2);
    printf("Высота дерева: %d\n", height(tree->root));                      // высота 3
    printf("Дерево %sсбалансировано\n", is_balanced(tree) ? "" : "не");    // сбалансировано


    // задание 2. создать [50] деревьев по [10000] узлов и заполнит узлы случайными целочисленными значениями;
    const int SIZE = 50;
    struct BinTree* tree_array[SIZE];
    for (int i = 0; i < SIZE; ++i) {
        tree_array[i] = init();
        for (int j = 0; j < 10000; ++j) {
            int vlaue = rand() % 20000;
            insert(tree_array[i], vlaue);
        }
    }

    int num_balanced = 0;
    for (int i = 0; i < SIZE; ++i) {
        if (is_balanced(tree_array[i])) {
            ++num_balanced;
        }
    }

    // Задание 3. рассчитает, какой процент из созданных деревьев является сбалансированными. 
    printf("Сбалансированных деревьев %d%%\n", 100.0 * num_balanced / SIZE);    // сбалансированных 26%

    // Проверка задания 4.
    int value = 4;
    printf("Значение %d%s содержится в дереве\n", value, bin_search_tree(tree, value) ? "" : " не");    // true
    value = 7;
    printf("Значение %d%s содержится в дереве\n", value, bin_search_tree(tree, value) ? "" : " не");    // false
    
    return 0;
}