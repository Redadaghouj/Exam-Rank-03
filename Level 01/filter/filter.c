#include <stdio.h>
#include <string.h>
#include <unistd.h>

char	buffer[70000];
int 	len;
int		b_read;

int	gnl()
{
	int b_read = read(STDIN_FILENO, buffer, sizeof(buffer));
	if (b_read <= 0) return (0);
	buffer[b_read] = '\0';
	return (1);
}

int	check_match(char *s, int i)
{
	int	j = 0;
	while (buffer[i] || j < len)
	{
		if (buffer[i + j] == s[j]) j++;
		else break ;
	}
	if (j == len) return (1);
	else return (0);
}

void	transform_phrase(int *i)
{
	int j = -1;
	while (++j < len)
		printf("*");
	*(i) += len;
}

int	filter(char *s)
{
	int	i;
	while (gnl())
	{
		i = 0;
		while (buffer[i])
		{
			if (check_match(s, i))
				transform_phrase(&i);
			else printf("%c", buffer[i++]);
		}
	}
	if (b_read < 0)
	{
		perror("Error");
		return (1);
	}
	return (0);
}

int	main(int argc, char *argv[])
{
	if (argc == 2)
	{
		(void)argc;
		len = strlen(argv[1]);
		if (len == 0 || filter(argv[1]))
			return (1);
		return (0);
	}
	return (1);
}