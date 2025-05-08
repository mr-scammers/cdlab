#include <stdio.h>
#include <conio.h>

void main() {
    char stack[20], ip[20], opt[10][10][1], ter[10];
    int i, j, k, n, top = 0;

    clrscr();
    
    for (i = 0; i < 10; i++) {
        stack[i] = '\0';
        ip[i] = '\0';
        for (j = 0; j < 10; j++) {
            opt[i][j][0] = '\0';  // Fixed access to the correct element
        }
    }

    printf("Enter no. of terminals: ");
    scanf("%d", &n);

    printf("\nEnter the terminals: ");
    scanf("%s", ter);

    printf("\nEnter the table values:\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            printf("Enter the value for %c %c: ", ter[i], ter[j]);
            scanf("%s", opt[i][j]);  // No need for an additional loop here
        }
    }

    printf("\nOperator precedence table:\n");
    printf("\t");
    for (i = 0; i < n; i++) {
        printf("%c\t", ter[i]);
    }
    printf("\n");

    for (i = 0; i < n; i++) {
        printf("%c\t", ter[i]);
        for (j = 0; j < n; j++) {
            printf("%s\t", opt[i][j]);  // Access the correct string value
        }
        printf("\n");
    }

    getch();
}
