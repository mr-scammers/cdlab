#include <stdio.h>
#include <ctype.h>
#include <string.h>

void oneaddr();
void twoaddr();
void threeaddr();
void store();

char alp[10], op[10];
int j = 0, i = 0, h = 0, m = 0, k = 0;

int main() {
    char ip[10];
    int choice;

    printf("\n***** MENU *****\n");
    printf("1. Single Address Instruction\n");
    printf("2. Two Address Instruction\n");
    printf("3. Three Address Instruction\n");
    printf("Enter the postfix expression: ");
    scanf("%s", ip);

    printf("Select the TARGET CODE instruction format: ");
    scanf("%d", &choice);

    printf("\nOPCODE ADDRESS\n------------\n");

    while (ip[h] != '\0') {
        if (isalpha(ip[h])) {
            alp[i++] = ip[h++];
        } else {
            op[j] = ip[h++];
            switch (choice) {
                case 1: oneaddr(); break;
                case 2: twoaddr(); break;
                case 3: threeaddr(); break;
                default: printf("Invalid choice\n"); return 1;
            }
        }
    }

    return 0;
}

void twoaddr() {
    if (m <= 0) {
        printf("LOAD\t%c, R1\n", alp[--i]);
        printf("LOAD\t%c, R2\n", alp[--i]);
        m++;
    } else {
        printf("LOAD\t%c, R2\n", alp[--i]);
    }

    switch (op[j]) {
        case '+': printf("ADD\tR2, R1\n"); break;
        case '*': printf("MUL\tR2, R1\n"); break;
        case '-': printf("SUB\tR2, R1\n"); break;
        case '/': printf("DIV\tR2, R1\n"); break;
        default: printf("INVALID OPERATOR\n"); break;
    }
}

void threeaddr() {
    if (m <= 0) {
        printf("LOAD\t%c, R1\n", alp[--i]);
        printf("LOAD\t%c, R2\n", alp[--i]);
        m++;
    } else {
        printf("LOAD\t%c, R2\n", alp[--i]);
    }

    if (k == 2) k = 0;

    switch (op[j]) {
        case '+': printf("ADD\t%s\n", k++ == 0 ? "R1, R2, R3" : "R3, R2, R1"); break;
        case '*': printf("MUL\t%s\n", k++ == 0 ? "R1, R2, R3" : "R3, R2, R1"); break;
        case '-': printf("SUB\t%s\n", k++ == 0 ? "R1, R2, R3" : "R3, R2, R1"); break;
        case '/': printf("DIV\t%s\n", k++ == 0 ? "R1, R2, R3" : "R3, R2, R1"); break;
        default: printf("INVALID OPERATOR\n"); break;
    }
}

void oneaddr() {
    printf("LOAD\t%c, R1\n", alp[--i]);
    switch (op[j]) {
        case '+': printf("ADD\t%c, R1\n", alp[--i]); store(); break;
        case '*': printf("MUL\t%c, R1\n", alp[--i]); store(); break;
        case '-': printf("SUB\t%c, R1\n", alp[--i]); store(); break;
        case '/': printf("DIV\t%c, R1\n", alp[--i]); store(); break;
        default: printf("INVALID OPERATOR\n"); break;
    }
}

void store() {
    printf("STORE\tR1, t\n");
    alp[i++] = 't'; // simulate temporary variable
}
