#include <stdio.h>
#include <stdlib.h>

int        len;
char       **g_av;
int        *result;
int        resultsize;
int        target;
int        finwslres;

int jm3(void)
{
    int res = 0;
    for (int i = 0; i < resultsize; i++) res += result[i];
    return (res);
}

void printi(void)
{
    int i;
    for (i = 0; i < resultsize - 1; i++) printf("%d ", result[i]);
    if (resultsize != 0) printf("%d\n", result[i]); else printf("\n");
}

void powerset(int finwslna)
{
    if (jm3() == target) printi();
    for (int i = finwslna; i < len ; i++)
    {
        result[resultsize++] = atoi(g_av[i]);
        powerset(i + 1);
        resultsize--;
    }
}

int main(int ac, char **av)
{
    if (ac <= 2)
        return 1;
    int temp[ac - 2];
    len = ac;
    g_av = av;
    target = atoi(av[1]);
    finwslres = 0;
    result = temp;
    resultsize = 0;
    powerset(2);
}