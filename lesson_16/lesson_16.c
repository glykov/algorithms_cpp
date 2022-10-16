#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

/**
 * 1. Реализовать шифрование и расшифровку цезаря с передаваемым в функцию сообщением и ключом
*/

char *alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890 !?.,";

int get_symbol_index(char symbol)
{
    int i = 0;
    while (alphabet[i] != symbol) {
        ++i;
    }
    return i;
}

char *caesar_encrypt(char *message, int key)
{
    int size = strlen(message);
    char *encrypted = (char*)malloc(size * sizeof(char) + 1);
    encrypted[size] = '\0';
    for (int i = 0; i < size; ++i) {
        int symbol_index = get_symbol_index(message[i]);
        symbol_index += key;
        if (symbol_index >= strlen(alphabet)) {
            symbol_index -= strlen(alphabet);
        }
        encrypted[i] = alphabet[symbol_index];
    }

    return encrypted;
}

char *caesar_decrypt(char *message, int key)
{
    int size = strlen(message);
    char *decrypted = (char*)malloc(size * sizeof(char) + 1);
    decrypted[size] = '\0';
    for (int i = 0; i < size; ++i) {
        int symbol_index = get_symbol_index(message[i]);
        symbol_index -= key;
        if (symbol_index < 0) {
            symbol_index += strlen(alphabet);
        }
        decrypted[i] = alphabet[symbol_index];
    }

    return decrypted;
}

/**
 * 2. Реализовать шифрование и расшифровку перестановками с передаваемым в функцию сообщением и количеством столбцов
*/

char *transpose_encrypt(char *message, int key) 
{
    int rows = (strlen(message) + key - 1) / key;
    char matrix[rows][key];
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < key; ++j) {
            int index = i * key + j;
            if (index < strlen(message)) {
                matrix[i][j] = message[index];
            } else {
                matrix[i][j] = '-';
            }
        } 
    }

    char *encrypted = (char*)malloc(rows * key * sizeof(char) + 1);
    encrypted[rows * key] = '\0';
    for (int i = 0; i < key; ++i) {
        for (int j = 0; j < rows; ++j) {
            encrypted[i * rows + j] = matrix[j][i];
        }
    }

    return encrypted;
}

char *transpose_decrypt(char* message, int key)
{
    int rows = (strlen(message) + key - 1) / key;
    char matrix[rows][key];
    for (int i = 0; i < key; ++i) {
        for (int j = 0; j < rows; ++j) {
            int index = i * rows + j;
            matrix[j][i] = message[index];
        } 
    }

    char *decrypted = (char*)malloc(rows * key * sizeof(char) + 1);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < key; ++j) {
            decrypted[i * key + j] = matrix[i][j];
        }
    }

    int k = strlen(decrypted) - 1;
    while (decrypted[k] == '-') {
        --k;
    }
    decrypted[++k] = '\0';

    return decrypted;
}

int main(void)
{
    char *test = "Hello world!";
    int key = 5;

    // тест задания 1
    printf("Исходный текст:       %s\n", test);
    char *encrypted = caesar_encrypt(test, key);
    printf("Зашифрованный тескт:  %s\n", encrypted);        // MjqqtA2twqiB
    char *decrypted = caesar_decrypt(encrypted, key);
    printf("Расшифрованный текст: %s\n", decrypted);

    // тест задания 2
    printf("Исходный текст:       %s\n", test);
    encrypted = transpose_encrypt(test, key);
    printf("Зашифрованный тескт:  %s\n", encrypted);        // H dew!lo-lr-ol-
    decrypted = transpose_decrypt(encrypted, key);
    printf("Расшифрованный текст: %s\n", decrypted);
    
    return 0;
}