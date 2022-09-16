#include <stdio.h>
#include <stdint.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>

// задание 1
// Реализовать функцию перевода чисел из десятичной системы в двоичную, используя рекурсию.
// в условии не указано требуется ли выводить двоичное число на экран или возвращать его (в виде числа)
void dec_to_bin(int n)
{
    if (n)
    {
        dec_to_bin(n / 2);
        printf("%d", n % 2);
    }
}
// поэтому сделаем возврат двоичного представления в виде десятичного числа
// лучше, конечно, использовать массив или строку (32 разряда не помесятся даже в long long)
// но, я что-то не смог заполнить строку в рекурсивных вызовах - только циклом
// в long long можно записать 10^18 нулей и единичек, т.е. чтобы точно поместиться можно переводить
// число не более 16 разраядов - 32 767 (short, он же int16_t) или 65 535 (unsigned short)
int64_t get_bin_from_dec(int16_t n)
{
    int64_t result = 0;
    if (n)
    {
        result += get_bin_from_dec(n / 2) * 10;
        result += n % 2;
    }
    return result;
}

// Задание 2
// Реализовать функцию возведения числа [a] в степень [b]
// Рекурсивно.
int simple_rec_pow(int base, int exp)
{
    if (exp == 1)
    {
        return base;
    }
    return base * simple_rec_pow(base, exp - 1);
}
// Задание 3
// Рекурсивно, используя свойство чётности степени
int fast_rec_pow(int base, int exp)
{
    if (exp == 1)
    {
        return base;
    }
    else if (exp % 2 == 1)
    {
        return base * fast_rec_pow(base, exp - 1);
    }
    return fast_rec_pow(base * base, exp / 2);
}

// Задание 4
// Реализовать нахождение количества маршрутов шахматного короля с учётом ограничений на перемещение из урока
// с препятствиями // (где единица - это наличие препятствия, а ноль - свободная для хода клетка)
int count_king_moves(int** obst, int x, int y)
{
    int row = x;
    int col = y;
    if (obst[row][col] == 1) {
        return 0;
    } else if (row == 0 || col == 0) {
        return 1;
    } else {
        return count_king_moves(obst, row - 1, col) + count_king_moves(obst, row, col - 1);
    }
}

int main(void)
{
    int16_t num;
    int base, exp;

    // тест перевода числа в двоичное представление
    do
    {
        printf("Введите число (0 - %d) для конвертации в двоичное представление: ", SHRT_MAX);
        scanf("%hd", &num);
    } while (num <= 0 || num > SHRT_MAX);

    dec_to_bin(num);
    printf("\n");
    printf("%ld\n", get_bin_from_dec(num));
    printf("%s\n", get_bin_str(num, 2));

    // тест возведения в степень
    printf("\nВведите основание степени: ");
    scanf("%d", &base);
    printf("Введите показатель степени: ");
    scanf("%d", &exp);
    printf("%d\n", simple_rec_pow(base, exp));
    printf("%d\n", fast_rec_pow(base, exp));
    
    // тест нахождения количества ходов короля
    const int WIDTH = 4;
    const int HEIGHT = 4;
    int **obst = (int**)malloc(HEIGHT * sizeof(int*));
    for (int i = 0; i < HEIGHT; ++i) {
        obst[i] = (int*)malloc(WIDTH * sizeof(int));
    }
    
    obst[1][1] = 1;
    obst[1][2] = 1;
    obst[2][3] = 1;

    // распечатываем в виде матрицы
    for (int i = 0; i < HEIGHT; ++i) {
        for (int j = 0; j < WIDTH; ++j) {
            printf("%4d ", count_king_moves(obst, i, j));
        }
        printf("\n");
    }
    // или просто в виде числа
    printf("%d\n", count_king_moves(obst, WIDTH - 1, HEIGHT - 1));

    return 0;
}