#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/**
 * Вспомогательные структуры и функции работы с ними
 * Stack (для метода dfs)
*/

struct Stack
{
    int *data;
    int top;
};

struct Stack *init_stack(int size)
{
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    stack->data = (int*)malloc(sizeof(int) * size);
    stack->top = -1;
}

bool is_stack_empty(struct Stack *stack)
{
    return stack->top == -1;
}

void push(struct Stack *stack, int value)
{
    stack->data[++(stack->top)] = value;
}

int pop(struct Stack *stack)
{
    return stack->data[(stack->top)--];
}

int peek(struct Stack *stack)
{
    return stack->data[stack->top];
}

/**
 * Queue (для метода bfs)
*/
struct Queue
{
    int *data;
    int head;
    int tail;
    int size;
};

struct Queue *init_queue(int size)
{
    struct Queue *q = (struct Queue*)malloc(sizeof(struct Queue));
    q->data = (int*)malloc(sizeof(int) * size);
    q->head = 0;
    q->tail = -1;
    q->size = size;
    return q;
}

void enqueue(struct Queue *q, int value)
{
    if (q->tail == q->size - 1) {
        q->tail = -1;
    }
    q->data[++(q->tail)] = value;
}

int dequeue(struct Queue *q)
{
    int tmp = q->data[(q->head)++];
    if (q->head == q->size) {
        q->head = 0;
    }
    return tmp;
}

bool is_queue_empty(struct Queue *q)
{
    return (q->tail + 1 == q->head || q->head + q->size - 1 == q->tail);
}

/**
 * определение вершины графа
*/
struct Vertex
{
    char label;
    bool visited;
};

struct Vertex make_vertex(char label)
{
    struct Vertex v;
    v.label = label;
    v.visited = false;
    return v;
}

void display_vertex(struct Vertex v)
{
    printf("%c ", v.label);
}

/**
 * определение графа
*/
struct Graph
{
    struct Vertex* vertex_list;
    int **adj_matrix;
    int num_vert;
    struct Stack *stack;
};

struct Graph* init_graph(int size)
{
    struct Graph *graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->vertex_list = (struct Vertex*)malloc(sizeof(struct Vertex) * size);
    graph->adj_matrix = (int**)malloc(sizeof(int*) * size);
    for (int i = 0; i < size; ++i) {
        graph->adj_matrix[i] = (int*)malloc(sizeof(int) * size);
    }

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            graph->adj_matrix[i][j] = 0;
        }
    }

    return graph;
}

void add_vertex(struct Graph *g, char label)
{
    g->vertex_list[g->num_vert++] = make_vertex(label);
}

void add_edge(struct Graph *g, int start, int end)
{
    g->adj_matrix[start][end] = 1;
    g->adj_matrix[end][start] = 1;
}

/**
 * Задание 1. Реализовать обход в глубину с использованием стека
*/
int get_adj_vertex(struct Graph *g, int v)
{
    for (int j = 0; j < g->num_vert; ++j) {
        if (g->adj_matrix[v][j] == 1 & !g->vertex_list[j].visited) {
            return j;
        }
    }
    return -1;
}

int degree(struct Graph *g, int v)
{
    int counter = 0;
    for (int i = 0; i < g->num_vert; ++i) {
        counter += g->adj_matrix[v][i];
    }

    return counter;
}

int *all_degrees(struct Graph *g)
{
    int *degrees = (int*)malloc(sizeof(int) * g->num_vert);
    for (int i = 0; i < g->num_vert; ++i) {
        degrees[i] = 0;
    }

    for (int i = 0; i < g->num_vert; ++i) {
        for (int j = 0; j < g->num_vert; ++j) {
            degrees[i] += g->adj_matrix[i][j];
        }
    }

    return degrees;
}

void dfs(struct Graph *g) 
{
    struct Stack *stack = init_stack(g->num_vert);
    g->vertex_list[0].visited = true;
    display_vertex(g->vertex_list[0]);
    push(stack, 0);

    while (!is_stack_empty(stack)) {
        int v = get_adj_vertex(g, peek(stack));
        if (v == -1) {
            pop(stack);
        } else {
            g->vertex_list[v].visited = true;
            display_vertex(g->vertex_list[v]);
            push(stack, v);
        }
    }

    for (int i = 0; i < g->num_vert; ++i) {
        g->vertex_list[i].visited = false;
    }
}

/* bfs для задания 2*/
void bfs(struct Graph* g)
{
    struct Queue *queue = init_queue(g->num_vert);
    g->vertex_list[0].visited = true;
    display_vertex(g->vertex_list[0]);
    enqueue(queue, 0);
    int v2;

    while (!is_queue_empty(queue)) {
        int v1 = dequeue(queue);

        while ((v2 = get_adj_vertex(g, v1)) != -1) {
            g->vertex_list[v2].visited = true;
            display_vertex(g->vertex_list[v2]);
            enqueue(queue, v2);
        }
    }

    for (int i = 0; i < g->num_vert; ++i) {
        g->vertex_list[i].visited = false;
    }
}

/**
 * 3. обход графа рекурсивной функцией (с подсчётом только смежных со стартовой вершин)
*/
void search_rec(struct Graph *g, int v, int *first_degree)
{
    g->vertex_list[v].visited = true;
    display_vertex(g->vertex_list[v]);
    if (*first_degree == -1) {
        *first_degree = degree(g, v);
    }

    for (int i = 0; i < g->num_vert; ++i) {
        if (g->adj_matrix[v][i] != 0 && !g->vertex_list[i].visited) {
            search_rec(g, i, first_degree);
        }
    }
}

/**
 * 4. обход графа по матрице смежности (с подсчётом всех вершин графа) 
 * В конце обхода вывести два получившихся списка всех узлов в порядке уменьшения количества ссылок на них.
*/
struct NodeDegree
{
    char label;
    int degree;
};

void sort_nodes_by_degree(struct NodeDegree *ndarray, int size)
{
    for (int i = 1; i < size; i++) {
        int j = i;
        struct NodeDegree temp = ndarray[i];

        while (j >= 0 && ndarray[j - 1].degree < temp.degree) {
            ndarray[j] = ndarray[j - 1];
            --j;
        }
        ndarray[j] = temp;
    }
}

void matrix_dfs(struct Graph* g, int v, struct NodeDegree *list)
{
    
    g->vertex_list[v].visited = true;
    struct NodeDegree temp;
    temp.degree = degree(g, v);
    temp.label = g->vertex_list[v].label;
    list[v] = temp;

    for (int i = 0; i < g->num_vert; ++i) {
        if (g->adj_matrix[v][i] != 0 && !g->vertex_list[i].visited) {
            matrix_dfs(g, i, list);
        }
    }
}

int main(void)
{
    const int SIZE = 6;
    struct Graph *graph = init_graph(SIZE);
    add_vertex(graph, 'A');
    add_vertex(graph, 'B');
    add_vertex(graph, 'C');
    add_vertex(graph, 'D');
    add_vertex(graph, 'E');

    add_edge(graph, 0, 1);
    add_edge(graph, 1, 2);
    add_edge(graph, 0, 3);
    add_edge(graph, 3, 4);

    // Проверка задания 1
    printf("Посещение: ");
    dfs(graph);                 // A B C D E
    printf("\n");


    /**
     * 2. Дан готовый простой граф с циклическими связями. 
     * Нужно обойти этот граф двумя способами и подсчитать количество ссылок на каждый из узлов графа (полустепень захода).
    */
    struct Graph *g = init_graph(7);
    add_vertex(g, 'A');
    add_vertex(g, 'B');
    add_vertex(g, 'C');
    add_vertex(g, 'D');
    add_vertex(g, 'E');
    add_vertex(g, 'F');
    add_vertex(g, 'G');

    add_edge(g, 0, 1);
    add_edge(g, 0, 2);
    add_edge(g, 0, 5);
    add_edge(g, 0, 6);
    add_edge(g, 6, 4);
    add_edge(g, 4, 6);
    add_edge(g, 4, 5);
    add_edge(g, 3, 5);

    printf("Посещение в глубину: ");
    dfs(g);                             // A B C F D E G 
    printf("\n");
    printf("Посещение в ширину: ");
    bfs(g);                             // A B C F G D E 
    printf("\n");
    printf("Степении вершин: ");        // A: 4 B: 1 C: 1 D: 1 E: 2 F: 3 G: 2 
    int *degrees = all_degrees(g);
    for (int i = 0; i < g->num_vert; ++i) {
        printf("%c: %d ", g->vertex_list[i], degrees[i]);
    }
    printf("\n");

    // Проверка задания 3
    int first_degree = -1;
    printf("Рекурсивный обход: ");
    search_rec(g, 0, &first_degree);                            // A B C F D E G
    printf("\nСтепень первой вершины: %d\n", first_degree);     // 4
    for (int i = 0; i < g->num_vert; ++i) {
        g->vertex_list[i].visited = false;
    }

    // Проверка задания 4
    struct NodeDegree nd[g->num_vert];
    matrix_dfs(g, 0, nd);
    sort_nodes_by_degree(nd, g->num_vert);
    for (int i = 0; i < g->num_vert; ++i) {
        printf("%c: %d ", nd[i].label, nd[i].degree);
    }
    printf("\n");
    
    return 0;
}