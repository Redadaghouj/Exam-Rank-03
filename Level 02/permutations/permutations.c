#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int n;
char *arg;

void    sort_arr(void)
{
    char tmp;
    for (int i=0; arg[i]; i++)
    {
        for (int j=i+1; arg[j]; j++)
        {
            if (arg[i] > arg[j])
            {
                tmp = arg[i];
                arg[i] = arg[j];
                arg[j] = tmp;
            }
        }
    }
}

int ft_strlen(char *s)
{
    int i=0;
    while (s[i])
        i++;
    return (i);
}

void permute(char *s, char *str, int idx, int used[])
{
    if (n == idx)
    {
        puts(str);
        return ;
    }
    for (int i=0; i<n; i++)
    {
        if (used[i])
            continue ;
        str[idx] = s[i];
        used[i] = 1;
        permute(s, str, idx + 1, used);
        used[i] = 0;
    }
}

int main(int argc, char *argv[])
{
    if (argc != 2)
        return (1);
    n = ft_strlen(argv[1]);
    int used[n];
    for (int i=0; i < n; i++)
        used[i] = 0;
    char *str = malloc((n + 1) * sizeof(char));
    str[n] = '\0';
    arg = argv[1];
    sort_arr();
    permute(arg, str, 0, used);
    free(str);
    str = NULL;
    return (0);
}