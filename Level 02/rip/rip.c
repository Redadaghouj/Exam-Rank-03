#include <stdio.h>

int     minimum_to_remove = 0;
char    *argument;

int invalid()
{
    int unopened = 0;
    int unclosed = 0;

    for (int i = 0; argument[i]; i++)
    {
        if (argument[i] == '(')
        {
            unclosed++;
        }
        else if (argument[i] == ')')
        {
            if (unclosed > 0)
                unclosed--;
            else
                unopened++;
        }
    }
    return (unopened + unclosed);
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