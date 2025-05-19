#include <stdio.h>
#include <string.h>

// Your ft_scanf declaration (implement this in ft_scanf.c)
int ft_scanf(const char *format, ...);

// Helper to print results
void print_test(const char *test_name, int ret_real, int ret_ft, const char *input) {
    printf("\nTest: %s\n", test_name);
    printf("Input: \"%s\"\n", input);
    printf("  scanf() return: %d\n", ret_real);
    printf("  ft_scanf() return: %d\n", ret_ft);
}

// Test cases
void run_tests() {
    int ret_real, ret_ft;
    int d_real, d_ft;
    char c_real, c_ft;
    char s_real[20], s_ft[20];

    // Test 1: Basic %d
    ret_real = scanf("%d", &d_real);
    rewind(stdin); // Reset stdin for ft_scanf
    ret_ft = ft_scanf("%d", &d_ft);
    print_test("%d (basic)", ret_real, ret_ft, "42");

    // Test 2: %d with trailing chars
    ret_real = scanf("%d", &d_real);
    rewind(stdin);
    ret_ft = ft_scanf("%d", &d_ft);
    print_test("%d (trailing chars)", ret_real, ret_ft, "123abc");

    // Test 3: %d with EOF
    printf("Simulate EOF (Ctrl+D after input):\n");
    ret_real = scanf("%d", &d_real);
    rewind(stdin);
    ret_ft = ft_scanf("%d", &d_ft);
    print_test("%d (EOF)", ret_real, ret_ft, "EOF");

    // Test 4: %c (basic)
    ret_real = scanf("%c", &c_real);
    rewind(stdin);
    ret_ft = ft_scanf("%c", &c_ft);
    print_test("%c (basic)", ret_real, ret_ft, "X");

    // Test 5: %c with space
    ret_real = scanf("%c", &c_real);
    rewind(stdin);
    ret_ft = ft_scanf("%c", &c_ft);
    print_test("%c (space)", ret_real, ret_ft, " X");

    // Test 6: %s (basic)
    ret_real = scanf("%s", s_real);
    rewind(stdin);
    ret_ft = ft_scanf("%s", s_ft);
    print_test("%s (basic)", ret_real, ret_ft, "hello");

    // Test 7: %s with trailing chars
    ret_real = scanf("%s", s_real);
    rewind(stdin);
    ret_ft = ft_scanf("%s", s_ft);
    print_test("%s (trailing)", ret_real, ret_ft, "world!");

    // Test 8: Mixed format "%d%c%s"
    ret_real = scanf("%d%c%s", &d_real, &c_real, s_real);
    rewind(stdin);
    ret_ft = ft_scanf("%d%c%s", &d_ft, &c_ft, s_ft);
    print_test("%d%c%s (mixed)", ret_real, ret_ft, "42Xhello");
}

int main() {
    printf("=== Starting ft_scanf vs scanf comparison ===\n");
    run_tests();
    printf("\n=== End of tests ===\n");
    return 0;
}