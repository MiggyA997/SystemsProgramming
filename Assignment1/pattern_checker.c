#include "pa1.h"

// use strlen() to get the length of a string
// do NOT use any other functions from string.h

int is_palindrome(char str[])
{ //str[0] == str[strlen(str)-1], str[1] == str[strlen(str)-2]...
    int len = strlen(str);
    for (int i = 0; i < len / 2; i++) 
    {
        if (str[i] != str[len - i - 1])
        {
            return 0; //Not a palindrome  
        }
    }
    return 1; // Palindrome
}

int is_singleton(char str[]) {
    char firstChar = str[0];
    for (int i = 1; str[i] != '\0'; i++) {
        if (str[i] != firstChar) {
            return 0; // Not a singleton
        }
    }
    return 1; // Singleton
}

int is_arithmetic(char str[]) {
    for (int i = 0; str[i + 1] != '\0'; i++) {
        if (str[i] + 1 != str[i + 1]) {
            return 0; // Not an arithmetic pattern
        }
    }
    return 1; // Arithmetic pattern
}

int is_reverse_arithmetic(char str[]) {
    for (int i = 0; str[i + 1] != '\0'; i++) {
        if (str[i] - 1 != str[i + 1]) {
            return 0; // Not a reverse arithmetic pattern
        }
    }
    return 1; // Reverse arithmetic pattern
}

int is_balanced_tripartite(char str[]) {
    int len = strlen(str);
    if (len % 3 != 0) {
        return 0; // Length not divisible by 3
    }

    int partLen = len / 3;
    for (int i = 0; i < partLen; i++) {
        if (str[i] != str[i + partLen] || str[i] != str[i + 2 * partLen]) {
            return 0; // Not a balanced tripartite pattern
        }
    }
    return 1; // Balanced tripartite pattern
}

int is_balanced_bipartite(char str[]) {
    int len = strlen(str);
    if (len % 2 != 0) {
        return 0; // Length not divisible by 2
    }

    int halfLen = len / 2;
    for (int i = 0; i < halfLen; i++) {
        if (str[i] != str[i + halfLen]) {
            return 0; // Not a balanced bipartite pattern
        }
    }
    return 1; // Balanced bipartite pattern
}
