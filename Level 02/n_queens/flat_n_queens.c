#include <stdio.h>
#include <stdlib.h>

int n;
int *g_board, *g_solution;

void    print_solution()
{
    for (int i=0; i<n; i++)
        fprintf(stdout, "%d ", g_solution[i]);
    fprintf(stdout, "\n");
}

int    is_valid(int raw, int col)
{
    int q_raw, q_col;
    for (int i=0; i<raw; i++)
    {
        q_raw = i;
        q_col = g_solution[i];
        if (col == q_col)
            return (0);
        else if (q_raw - q_col == raw - col)
            return (0);
        else if (q_raw + q_col == raw + col)
            return (0);
    }
    return (1);
}

void    n_queens(int raw)
{
    if (raw == n)
    {
        print_solution();
        return ;
    }
    for (int col=0; col<n; col++)
    {
        if (is_valid(raw, col))
        {
            g_solution[raw] = col;
            n_queens(raw+1);
        }
    }
}

int main(int argc, char **argv)
{
    if (argc != 2 || atoi(argv[1]) == 0)
        return (1);
    n = atoi(argv[1]);
    int board[n], solution[n];
    g_board = board, g_solution = solution;
    n_queens(0);
    return (0);
}