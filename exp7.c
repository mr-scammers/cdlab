#include <stdio.h>
#include <string.h>
#include <ctype.h>

char table[10][10][10], nt[10], t[10], inp[20], stack[20];
int nut, nun, i = 0, top = 0;

int getnt(char);
int gett(char);
void replace(char, char);

void main() {
    int i, j;
    printf("Enter no. of terminals: ");
    scanf("%d", &nut);
    printf("Enter no. of non-terminals: ");
    scanf("%d", &nun);

    printf("Enter all non-terminals: ");
    scanf("%s", nt);
    printf("Enter all terminals: ");
    scanf("%s", t);

    printf("\nEnter parsing table values:\n");
    for (i = 0; i < nun; i++)
        for (j = 0; j < nut; j++) {
            printf("Enter for %c and %c: ", nt[i], t[j]);
            scanf("%s", table[i][j]);
        }

    printf("\nParsing Table:\n");
    printf("\t");
    for (j = 0; j < nut; j++) printf("%c\t", t[j]);
    printf("\n");
    for (i = 0; i < nun; i++) {
        printf("%c\t", nt[i]);
        for (j = 0; j < nut; j++)
            printf("%s\t", table[i][j]);
        printf("\n");
    }

    printf("Enter string to be parsed: ");
    scanf("%s", inp);

    stack[top++] = '$';
    stack[top++] = nt[0]; // Start symbol

    i = 0;
    while (1) {
        if ((stack[top - 1] == '$') && (inp[i] == '$')) {
            printf("String Accepted!\n");
            return;
        } else if (!isupper(stack[top - 1])) {
            if (stack[top - 1] == inp[i]) {
                i++;
                top--;
            } else {
                printf("ERROR: Not Accepted!\n");
                break;
            }
        } else {
            replace(stack[top - 1], inp[i]);
        }
    }
}

int getnt(char x) {
    for (int a = 0; a < nun; a++)
        if (x == nt[a])
            return a;
    return -1;
}

int gett(char x) {
    for (int a = 0; a < nut; a++)
        if (x == t[a])
            return a;
    return -1;
}

void replace(char NT, char T) {
    int in1 = getnt(NT);
    int it1 = gett(T);
    
    if (in1 != -1 && it1 != -1) {
        char str[10];
        strcpy(str, table[in1][it1]);

        if (strcmp(str, "#") == 0) {
            top--; // Epsilon production
        } else if (strcmp(str, "Error") == 0) {
            printf("ERROR: Not Valid String!\n");
            return;
        } else {
            top--; // Pop NT
            int len = strlen(str);
            for (int j = len - 1; j >= 0; j--)
                stack[top++] = str[j]; // Push production in reverse
        }
    } else {
        printf("ERROR: Invalid input!\n");
    }
}
