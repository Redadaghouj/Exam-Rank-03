#include <stdarg.h>
#include <stdio.h>
#include <ctype.h>

int check_sign(FILE *f)
{
	int sign = 1;
	char c = fgetc(f);
	if (c == '-' || c == '+')
	{
		if (c == '-')
			sign = -1;
	}
	else	
		ungetc(c, f);
	return (sign);
}

int match_space(FILE *f) // skip spaces
{
	char c;
	while (1)
	{
		c = fgetc(f);
		if (!isspace(c))
		{
			if (c == EOF) return (-1);
			ungetc(c, f);
			break ;
		}
	}
	return (0);
}

int match_char(FILE *f, char c) // match literal
{
	if (c == fgetc(f))
		return (1);
	return (0);
}

int scan_char(FILE *f, va_list ap) // %c
{
	char c = fgetc(f);
	if (c == EOF)
		return (-1);
	*va_arg(ap, char *) = c;
	return (1);
}

int scan_int(FILE *f, va_list ap) // %d
{
	int	res = 0;
	int sign = check_sign(f);
	char c;
	while (1)
	{
		c = fgetc(f);
		if (isdigit(c))
			res = res * 10 + (c - '0');
		else if (c == EOF)
			return (-1);
		else
		{
			ungetc(c, f);
			break ;
		}
	}
	*va_arg(ap, int *) = (res * sign);
	return (1);
}

int scan_string(FILE *f, va_list ap) // %s
{
	char c;
	char *s = va_arg(ap, char *);
	while (1)
	{
		c = fgetc(f);
		if (c == EOF) return (-1);
		else if (c == isspace(c))
			break ;
		*s++ = c;
	}
	*s = '\0';
	return (1);
}

int    match_conv(FILE *f, const char **format, va_list ap)
{
	switch (**format)
	{
		case 'c':
			return scan_char(f, ap);
		case 'd':
			match_space(f);
			return scan_int(f, ap);
		case 's':
			match_space(f);
			return scan_string(f, ap);
		case EOF:
			return -1;
		default:
			return -1;
	}
}

int ft_vfscanf(FILE *f, const char *format, va_list ap)
{
	int nconv = 0;

	int c = fgetc(f);
	if (c == EOF)
		return EOF;
	ungetc(c, f);

	while (*format)
	{
		if (*format == '%')
		{
			format++;
			if (match_conv(f, &format, ap) != 1)
				break;
			else
				nconv++;
		}
		else if (isspace(*format))
		{
			if (match_space(f) == -1)
				break;
		}
		else if (match_char(f, *format) != 1)
			break;
		format++;
	}
	if (ferror(f))
		return EOF;
	return nconv;
}

int ft_scanf(const char *format, ...)
{
	va_list ap;

	va_start(ap, format);
	int ret = ft_vfscanf(stdin, format, ap);
	va_end(ap);
	return ret;
}

int main(void)
{
	int nb;
	int ret = ft_scanf("%d", &nb);
	printf("nb = %d | ret = %d\n", nb, ret);
	return (0);
}