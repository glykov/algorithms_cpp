#include <iostream>

int main()
{
    int* arr;
    arr = new int[100];
    int num_elems = 0;
    int i;
    int search_key;

    arr[0] = 77;
    arr[1] = 99;
    arr[2] = 44;
    arr[3] = 55;
    arr[4] = 22;
    arr[5] = 88;
    arr[6] = 11;
    arr[7] = 00;
    arr[8] = 66;
    arr[9] = 33;
    num_elems = 10;

    for (i = 0; i < num_elems; ++i)
    {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;

    search_key = 66;
    for (i = 0; i < num_elems; ++i)
    {
        if (arr[i] == search_key) break;
    }
    if (i == num_elems)
    {
        std::cout << "Can't find " << search_key << std::endl;
    }
    else
    {
        std::cout << "Found " << search_key << std::endl;
    }

    search_key = 55;
    for (i = 0; i < num_elems; ++i)
    {
        if (arr[i] == search_key) break;
    }
    for (int k = i; k < num_elems - 1; ++k)
    {
        arr[k] = arr[k + 1];
    }
    num_elems--;

    for (i = 0; i < num_elems; ++i)
    {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}