#include <stdio.h>
#include <stdlib.h>

#define MAX_NUM 30
#define MAX_SIZE 100

int tab[MAX_SIZE];
int size_tab;

int compare(const void* a, const void* b)
{
    int const* pa = a;
    int const* pb = b;
    return (*pb - *pa);
}

void* produce(void* idx)
{
    uint* index = (uint*)idx;
    uint count = 0;

    while (count < 5)
    {
        // debut section critique

        tab[size_tab++] = rand() % MAX_NUM;
        printf("produce: %d\n", tab[size_tab - 1]);

        // fin section critique

        count++;
    }
}

void* consume(void* idx)
{
    uint* index = (uint*)idx;
    uint count = 0;

    while (count != 5)
    {
        if (count < size_tab)
        {
            // debut section critique

            qsort(tab, MAX_SIZE / sizeof(int), sizeof(int), compare);
            printf("consume: sort [%d elements] =>", size_tab);
            for (uint i = 0; i < size_tab; i++)
                printf(" %d", tab[i]);
            printf("\n");
            count = size_tab;

            // fin section critique
        }
    }
}

int main()
{
    size_tab = 0;

    // a compléter

    return EXIT_SUCCESS;
}