#include <stdio.h>
#include <string.h>

void generateBinaryStrings(int n, char *str, int index) {
    // Base case: if we've reached the desired length
    if (index == n) {
        str[index] = '\0'; // Null-terminate the string
        printf("%s\n", str);
        return;
    }
    
    // Choice 1: place '0'
    str[index] = '0';
    generateBinaryStrings(n, str, index + 1);
    
    // Choice 2: place '1'
    str[index] = '1';
    generateBinaryStrings(n, str, index + 1);
}

int main() {
    int n = 3;
    char str[n + 1]; // +1 for null terminator
    generateBinaryStrings(n, str, 0);
    return 0;
}