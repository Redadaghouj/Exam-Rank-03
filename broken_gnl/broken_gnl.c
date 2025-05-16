#include <stdlib.h>
#include <string.h>
#include <unistd.h>
// main use
#include <fcntl.h> // for open
#include <stdio.h> // for printf

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 1
#endif

char    *ft_strdup(char *str)
{
    if (str == NULL)
        return (NULL);
    char *line = (char *) malloc(sizeof(char) * strlen(str) + 1);
    if (!line)
        return (NULL);
    int i = 0;
    while (str[i])
    {
        line[i] = str[i];
        i++;
    }
    line[i] = '\0';
    return (line);
}

char    *get_next_line(int fd)
{
    static char buffer[BUFFER_SIZE];
    char        line[70000];
    static int  b_pos;
    int         b_read;
    int         i;

    i = 0;
    if (fd < 0 || BUFFER_SIZE < 0)
        return (NULL);
    while (1)
    {
        if (b_pos >= b_read)
        {
            b_pos = 0;
            b_read = read(fd, buffer, BUFFER_SIZE);
            if (b_read <= 0)
                break ;
        }
        line[i++] = buffer[b_pos++];
        if (buffer[b_pos - 1] == '\n')
            break ;
    }
    line[i] = '\0';
    if (i == 0)
        return (NULL);
    return (ft_strdup(line));
}

int	main(void)
{
	int	fd = open("file.txt", O_RDONLY);
	// char *line = get_next_line(fd);
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	// while (line)
	// {
	// 	printf("%s", line);
	// 	free(line);
	// 	line = get_next_line(0);
	// }
	return (0);
}