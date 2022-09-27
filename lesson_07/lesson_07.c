#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*
* Вспомогательные функции
*/

// заполнение массива случайными числами в диапазоне 0..limit
void fill_array(int* arr, int size, int limit) 
{
    for (int i = 0; i < size; ++i) {
        arr[i] = random() % limit;
    }
}

// печать массива в формате Array: {a[0], a[1] .. a[size - 1]}
void print_array(int* arr, int size)
{
    printf("Array: { ");
    for (int i = 0; i < size; ++i) {
        if (i > 0) {
            printf(", ");
        }
        printf("%d", arr[i]);
    }
    printf(" }\n");
}

// обмен значений с индексами idx1 и idx2 в массиве arr
void swap(int* arr, int idx1, int idx2)
{
    int tmp = arr[idx1];
    arr[idx1] = arr[idx2];
    arr[idx2] = tmp;
}


/*
* Задание 1. Описать в коде улучшенный алгоритм быстрой сортировки
*/

// нахождение медианы из 3-х элементов arr[left], arr[right] и arr[(left + right) / 2]
// после нахождения медана помещается во вторую справа позицию массива
// (в крайней правой находится элемент заведомо больший медианы)
int median_of_3(int* arr, int left, int right) 
{
    int mid = left + (right - left) / 2;
    if (arr[left] > arr[mid]) {
        swap(arr, left, mid);
    }
    if (arr[left] > arr[right]) {
        swap(arr, left, right);
    }
    if (arr[mid] > arr[right]) {
        swap(arr, mid, right);
    }

    swap(arr, mid, right - 1);
    return arr[right - 1];
}

// разбиение массива на элементы большие pivot и меньшие pivot
// в конце элемент pivot помещается на свою позицию
int partition(int* arr, int left, int right, int pivot)
{
    int l = left;
    int r = right - 1;

    while (true) {
        while (arr[++l] < pivot);
        while (arr[--r] > pivot);
        if (l >= r) {
            break;
        }
        swap(arr, l, r);
    }
    swap(arr, l, right - 1);
    return l;
}

// сортировка вставкой для ускорения сортирвки массивов размером < 10 элементов
void insertion_sort(int* arr, int left, int right)
{
    int i, j;
    
    for (i = 1; i <= right; ++i) {
        int tmp = arr[i];
        j = i;
        while (j > left && arr[j - 1] > tmp) {
            arr[j] = arr[j - 1];
            --j;
        }
        arr[j] = tmp;
    }
}

// улучшенная функция быстрой сортировки
void quick_sort(int* arr, int left, int right)
{
    int size = right - left + 1;
    
    if (size < 10) {
        insertion_sort(arr, left, right);
    } else {
        int pivot = median_of_3(arr, left, right);
        int part = partition(arr, left, right, pivot);
        quick_sort(arr, left, part - 1);
        quick_sort(arr, part + 1, right);
    }
}

/*
* Задание 2. Сортировать в массиве целых положительных чисел только чётные числа,
* нечётные оставив на своих местах при помощи алгоритма блочной сортировки,
* то есть массив вида [0 2 8 3 4 6 5 9 8 2 7 3] превратить в [0 2 2 3 4 4 5 9 8 8 7 3]
*/

// функция блочной сортировки
void bucket_sort(int *arr, int size)
{
    const int MAX = size;
    
    int buckets[MAX][MAX + 1];
    for (int i = 0; i < MAX; ++i) {
        for (int j = 0; j < MAX + 1; ++j) {
            buckets[i][j] = 0;
        }
    }

    for (int i = 0; i < MAX; ++i) {
        if (arr[i] % 2 == 0) {
            buckets[arr[i]][buckets[arr[i]][MAX]++] = arr[i];
        }
    }

    int idx = 0;
    for (int i = 0; i < MAX; ++i) {
        for (int j = 0; j < buckets[i][MAX]; ++j) {
            while(arr[idx] % 2 != 0){
                idx++;
            }
            arr[idx++] = buckets[i][j];
        }
    }
}


int main(void)
{
    const int SIZE = 30;
    // testing task 1
    int data[SIZE];
    fill_array(data, SIZE, 100);
    print_array(data, SIZE);
    quick_sort(data, 0, SIZE - 1);
    print_array(data, SIZE);

    // testing task 2
    int arr[] =  {0, 2, 8, 3, 4, 6, 5, 9, 8, 2, 7, 3};
    int size = sizeof(arr) / sizeof(int);
    print_array(arr, size);
    bucket_sort(arr, size);
    print_array(arr, size);

    return 0;
}