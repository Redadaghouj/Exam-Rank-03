#include <stdio.h>

int     minimum_to_remove = 0;
char    *argument;

int invalid()
{
    int count = 0;

    for (int i = 0; argument[i]; i++)
    {
        if (argument[i] == '(')
            count++;
        if (argument[i] == ')')
        {
            if (count > 0)
                count--;
            else
                count++;
        }
    }
    return (count);
}

void rip(int currently_removed, int pos)
{
    if (currently_removed == minimum_to_remove && !invalid())
    {
        puts(argument);
        return ;
    }
    for (int i = pos; argument[i]; i++)
    {
        char c = argument[i];
        if (argument[i] == '(' || argument[i] == ')')
        {
            argument[i] = '_';
            rip(currently_removed + 1, i + 1);
            argument[i] = c;
        }
    }
}

int main(int ac, char **av)
{
    if (ac != 2)
        return (1);
    argument = av[1];
    minimum_to_remove = invalid();
    rip(0, 0);
}