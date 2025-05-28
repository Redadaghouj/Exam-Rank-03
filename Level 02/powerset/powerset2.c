
#include <stdio.h>
#include <stdlib.h>

int goal;
int n;
int *nbs;
int printer = 0;

void    print_solution(int idx, int s[])
{
    int i;
    for (i=0; i<idx-1; i++)
        printf("%d ", s[i]);
    printf("%d\n", s[i]);
    printer = 1;
}

void powerset(int s[], int idx, int pos, int sum)
{
    if (sum == goal && idx != 0)
        print_solution(idx, s);
    for (int i=pos; i<n; i++)
    {
        s[idx] = nbs[i];
        sum += nbs[i];
        powerset(s, idx+1, i+1, sum);
        sum -= nbs[i];
    }
}

int main(int argc, char **argv)
{
    if (argc <= 2)
        return 1;
    goal = atoi(argv[1]);
    if (goal == 0)
        printf("\n");
    n = argc - 2;
    int nb[n];
    int s[n];
    for (int i=0; i<n; i++)
        nb[i] = atoi(argv[i+2]);
    nbs = nb;
    powerset(s, 0, 0, 0);
    if (!printer && goal != 0)
        printf("\n");
    return 0;
}