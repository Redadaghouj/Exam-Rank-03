#include <stdio.h>
#include <stdlib.h>

int *result;
int resultsize;
int n;

void printi(void)
{
    int i;
    for(i = 0; i < resultsize - 1; i++) printf("%d ", result[i]);
    printf("%d\n", result[i]);
}

int valid(int x)
{
    for (int y = 0; y < resultsize; y++)
    {
        if (result[y] == x
        || result[y] - x == y - resultsize
        || result[y] - x == resultsize - y)
            return 0;
    }
    return 1;
}

void nqueens(void)
{
    if (resultsize == n)
        printi();
    for (int x = 0; x < n; x++)
        if (valid(x))
        {
            result[resultsize++] = x;
            nqueens();
            resultsize--;
        }
    
}

int main(int ac, char **av)
{
    if (ac != 2)
        return (1);
    n = atoi(av[1]);
    int temp[n];
    result = temp;
    resultsize = 0;
    nqueens();
}