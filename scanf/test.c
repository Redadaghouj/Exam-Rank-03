#include <stdio.h>
#include <stdarg.h>
#include <ctype.h>

int ft_scanf(const char *format, ...) {
    va_list args;
    va_start(args, format);
    int ret = 0;

    while (*format) {
        if (*format == '%') {
            format++;
            if (*format == 'd') {
                // Integer conversion
                int num = 0;
                int c;
                while ((c = fgetc(stdin)) != EOF && isdigit(c)) {
                    num = num * 10 + (c - '0');
                }
                if (c != EOF) ungetc(c, stdin);
                *va_arg(args, int *) = num;
                ret++;
            }
            else if (*format == 'c') {
                // Character conversion
                *va_arg(args, char *) = fgetc(stdin);
                ret++;
            }
            format++;
        }
        else {
            // Skip non-format characters
            format++;
        }
    }

    va_end(args);
    return ret;
}

int main() {
    int num;
    char c;

    printf("Testing ft_scanf with %%d%%c:\n");
    printf("Input: 2A\n");
    printf("Expected: 2 and 'A'\n");
    
    int ret = ft_scanf("%d%c", &num, &c);
    printf("Got: %d and '%c' (ret=%d)\n", num, c, ret);
    
    return 0;
}