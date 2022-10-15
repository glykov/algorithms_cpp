#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/**
 * Реализовать простейшую хеш-функцию. На вход функции подается строка, на выходе сумма кодов символов.
*/
int simple_hash_code(char *str)
{
    int result = 0;
    for (int i = 0; i < (strlen(str)); ++i) {
        result += str[i];
    }
    return result;
}

/**
 * 2. Имеются монеты номиналом 50, 10, 5, 2, 1 коп. 
 * Напишите функцию которая минимальным количеством монет наберет сумму 98 коп. 
 * Для решения задачи используйте “жадный” алгоритм.
*/
int coins[] = {50, 10, 5, 2, 1};

int find_min_coins(int* coins, int target)
{
    int n = target;
    int num_coins = 0;
    int curr_coin = 0;
    int *coins_list = (int*)malloc(sizeof(int) * target);

    while (target > 0) {
        if (coins[curr_coin] <= target) {
            target -= coins[curr_coin];
            coins_list[num_coins++] = coins[curr_coin];
        } else {
            curr_coin++;
        }
    }

    printf("%d копеек можно набрать %d монетами,\n", n, num_coins);
    printf("следующим образом: ");
    for (int i = 0; i < num_coins; ++i) {
        printf("%d ", coins_list[i]);
    }
    printf("\n");
}

int main(void)
{
    // тест задания 1
    char *hello = "hello";
    printf("Simple hash code for %s is %d\n", hello, simple_hash_code(hello));
    // тест задания 2
    find_min_coins(coins, 98);

    return 0;
}

