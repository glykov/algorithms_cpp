#include <stdio.h>

int is_prime(int num);

int main(void)
{
	int num;
	
	do {
		printf("Введите натуральное число большее 1 для проверки: ");
		scanf("%d", &num);
	} while (num < 2);
	
	printf("%d это %s число.\n", num, is_prime(num) ? "простое" : "составное");
	
	return 0;
}

int is_prime(int num)
{
	// отдельно обрабатываем четные числа, большие 2
	// в случае 2 сразу переходим к возврату из функции 
	if (num != 2 && num % 2 == 0) {
		return 0;
	}
	// нечетные числа обрабатываем по общей схеме
	for (int i = 3; i * i <= num; i += 2) {
		if (num % i == 0) {
			return 0;
		}
	}
	return 1;
}
