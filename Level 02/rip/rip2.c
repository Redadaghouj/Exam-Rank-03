
#include <stdio.h>

int must_fix;

int invalid(char *str)
{
    int unopened=0, unclosed=0;
    for (int i=0; str[i]; i++)
    {
        if (str[i] == '(') unclosed++;
        else if (str[i] == ')')
        {
            if (unclosed > 0) unclosed--;
            else unopened++;
        }
    }
    return (unopened + unclosed);
}

void    rip(char *s, int pos, int make_change)
{
    char c;
    if (must_fix == make_change && !invalid(s))
    {
        puts(s);
        return ;
    }
    for (int i=pos; s[i]; i++)
    {
        if (s[i] == '(' || s[i] == ')')
        {
            c = s[i];
            s[i] = ' ';
            rip(s, i+1, make_change+1);
            s[i] = c;
        }
    }
}

int main(int argc, char **argv)
{
    if (argc != 2)
        return 1;
    must_fix = invalid(argv[1]);
    rip(argv[1], 0, 0);
    return (0);
}