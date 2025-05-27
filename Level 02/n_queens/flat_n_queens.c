#include <stdio.h>
#include <stdlib.h>

int n;

void    print_solution(int solution[n])
{
    for (int i=0; i<n; i++)
        fprintf(stdout, "%d ", solution[i]);
    fprintf(stdout, "\n");
}

int    is_valid(int solution[n], int raw, int col)
{
    int q_raw, q_col;
    for (int i=0; i<raw; i++)
    {
        q_raw = i;
        q_col = solution[i];
        if (col == q_col)
            return (0);
        else if (q_raw - q_col == raw - col)
            return (0);
        else if (q_raw + q_col == raw + col)
            return (0);
    }
    return (1);
}

void    n_queens(int raw, int board[n], int solution[n])
{
    if (raw == n)
    {
        print_solution(solution);
        return ;
    }
    for (int col=0; col<n; col++)
    {
        if (is_valid(solution, raw, col))
        {
            solution[raw] = col;
            n_queens(raw+1, board, solution);
        }
    }
}

int main(int argc, char **argv)
{
    if (argc != 2 || atoi(argv[1]) == 0)
        return (1);
    n = atoi(argv[1]);
    int board[n], solution[n];
    n_queens(0, board, solution);
    return (0);
}