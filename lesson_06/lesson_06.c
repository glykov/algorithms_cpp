#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Задание 1. Реализовать пузырьковую сортировку двумерного массива
// например, массив 1,9,2 5,7,6 4,3,8 должен на выходе стать 1,2,3 4,5,6 7,8,9
int** make_2d_array(int rows, int cols) {
    int **arr = malloc(sizeof(int*) * rows);
    for (int i = 0; i < rows; ++i) {
        *(arr + i) = malloc(sizeof(int) * cols);
    }
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            arr[i][j] = rand() % 10;
        }
    }
    return arr;
}

void print_2d_array(int** arr, int rows, int cols)
{
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            printf("%3d", arr[i][j]);
        }
        printf("\n");
    }
}

void swap(int *a, int *b)
{
    int t = *a;
    *a = *b;
    *b = t;
}


void sort_2d_array(int **arr, int rows, int cols)
{
    for (int i = 0; i < rows * cols; ++i) {
        int divisor = rows > cols ? rows : cols;
        int x = i / divisor;
        int y = i % divisor;
        for (int j = 0; j < i; ++j) {
            int v = j / divisor;
            int w = j % divisor;
            if (arr[x][y] < arr[v][w]) {
                swap(&arr[x][y], &arr[v][w]);
            }
        }
    }
}

// Задание 2. Реализовать алгоритм Трабба-Прадо-Кнута в коде на языке С
double* read_data_tpc(int n)
{
    double* data = (double*)malloc(sizeof(double) * n);
    
    for (int i = 0; i < n; ++i) {
        printf("Введите значение %d: ", i + 1);
        scanf("%lf", &data[i]);
    }

    return data;
}

void reverse_data(double* arr, int len)
{
    for (int i = 0; i < len / 2; ++i) {
        int temp = arr[i];
        arr[i] = arr[len - 1 - i];
        arr[len - 1 - i] = temp;
    }
}

double calc(double n)
{
    return sqrt(fabs(n)) + 0.5 * pow(n, 3.0);
}

void tpc(int number) 
{
    double *data = read_data_tpc(number);
    reverse_data(data, number);
    for (int i = 0; i < number; ++i) {
        double temp = calc(data[i]);
        if (temp > 400.0) {
            printf("Элемент %d слишком большой\n", i + 1);
        } else {
            printf("Элемент %d = %.2f\n", i + 1, temp);
        }
    }
}

int main(void)
{
    const int ROWS = 3;
    const int COLS = 3;

    // testing task 1
    int** matrix = make_2d_array(ROWS, COLS);
    print_2d_array(matrix, ROWS, COLS);
    printf("\n===============\n");
    sort_2d_array(matrix, ROWS, COLS);
    print_2d_array(matrix, ROWS, COLS);
    printf("\n===============\n");

    // testing task 2
    tpc(11);

    return 0;
}