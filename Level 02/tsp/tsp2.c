#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
#include <sys/types.h>

float best_distance = 9999999.9;
ssize_t city_count;
float (*cities)[2];
bool *visited;
ssize_t *path;
float dist;

// compute the distance between two points
float    distance(float a[2], float b[2])
{
    return sqrtf((b[0] - a[0]) * (b[0] - a[0]) + (b[1] - a[1]) * (b[1] - a[1]));
}

void    backtrack(ssize_t count, float current_dest)
{
    if (count == city_count)
    {
        current_dest += distance(cities[path[count-1]], cities[path[0]]);
        if (current_dest < best_distance)
            best_distance = current_dest;
        return ;
    }
    for (ssize_t i=0; i<city_count; i++)
    {
        if (visited[i]) continue;
        dist = 0;
        if (count > 0)
            dist = distance(cities[path[count-1]], cities[i]);
        if (dist + current_dest >= best_distance) continue;
        visited[i] = 1;
        path[count] = i;
        backtrack(count+1, dist+current_dest);
        visited[i] = 0;
    }

}

float   tsp(float (*array)[2], ssize_t size)
{
    if (size <= 1) return (0.0f);
    if (size == 2) return (2 * distance(array[0], array[1]));

    cities = array;
    city_count = size;
    visited = calloc(size, sizeof(bool));
    path = malloc(size * sizeof(ssize_t));
    visited[0] = 1;
    path[0] = 0;
    backtrack(1, 0);
    free(visited);
    free(path);
    return (best_distance);
}

ssize_t    file_size(FILE *file)
{
    char    *buffer = NULL;
    size_t    n = 0;
    ssize_t ret;

    errno = 0;

    for (ret = 0; getline(&buffer, &n, file) != -1; ret++);

    free(buffer);
    if (errno || fseek(file, 0, SEEK_SET))
        return -1;
    return ret;
}

int        retrieve_file(float (*array)[2], FILE *file)
{
    int tmp;
    for (size_t i = 0; (tmp = fscanf(file, "%f, %f\n", array[i] + 0, array[i] + 1)) != EOF; i++)
        if (tmp != 2)
        {
            errno = EINVAL;
            return -1;
        }
    if (ferror(file))
        return -1;
    return 0;
}

int        main(int ac, char **av)
{
    char *filename = "stdin";
    FILE *file = stdin;
    if (ac > 1)
    {
        filename = av[1];
        file = fopen(filename, "r");
    }

    if (!file)
    {
        fprintf(stderr, "Error opening %s: %m\n", filename);
        return 1;
    }

    ssize_t size = file_size(file);
    if (size == -1)
    {
        fprintf(stderr, "Error reading %s: %m\n", filename);
        fclose(file);
        return 1;
    }

    float (*array)[2] = calloc(size, sizeof (float [2]));
    if (!array)
    {
        fprintf(stderr, "Error: %m\n");
        fclose(file);
        return 1;
    }

    if (retrieve_file(array, file) == -1)
    {
        fprintf(stderr, "Error reading %s: %m\n", av[1]);
        fclose(file);
        free(array);
        return 1;
    }
    if (ac > 1)
        fclose(file);

    printf("%.2f\n", tsp(array, size));
    free(array);
    return (0);
}
