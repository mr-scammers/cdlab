#include <stdio.h>

// Global variables
char str[20];
int flag = 1;
int i = 0;

// Function prototypes
void S();
void A();

void main() {
    printf("Enter input string: ");
    gets(str); // Warning: Unsafe function, may cause buffer overflow

    S();

    if (flag == 1 && str[i] == '\0') {
        printf("\nGiven string '%s' is completely parsed.\n", str);
    } else {
        printf("\nSorry! Not parsed.\n");
    }
}

void S() {
    if (str[i] == 'a') {
        i++;
        A();
        if (str[i] == 'd') {
            i++;
            return 0;
        } else {
            flag = 0;
            return 0;
        }
    } else {
        flag = 0;
        return 0;
    }
}

void A() {
    if (str[i] == 'a') {
        i++;
        if (str[i] == 'b') {
            i++;
            return 0;
        } else {
            A();
            return 0;
        }
    }
    else{
        flag=1;
        return 0;
    }
}
