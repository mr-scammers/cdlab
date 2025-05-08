#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>

char table[10][10][10], nt[10], t[10], inputStr[20], stack[20];
int nut, nun, i = 0, top = 0;

int getnt(char);
int gett(char);
void replace(char, char);

int main() {
    int i, j;
    char temp[10];  // For safe input of table entries
    clrscr();

    printf("Enter no. of terminals:\n");
    scanf("%d", &nut);

    printf("Enter no. of non terminals:\n");
    scanf("%d", &nun);

    printf("Enter all nonterminals:\n");
    scanf("%s", nt);

    printf("Enter all terminals:\n");
    scanf("%s", t);

    printf("\nEnter Parsing Table values:\n");
    for (i = 0; i < nun; i++) {
        for (j = 0; j < nut; j++) {
            printf("Enter for %c and %c: ", nt[i], t[j]);
            scanf("%s", temp);
            strcpy(table[i][j], temp); // Use temp buffer
        }
    }

    printf("\nParsing Table:\n");
    printf("\t");
    for (j = 0; j < nut; j++) {
        printf("%c\t", t[j]);
    }
    printf("\n");

    for (i = 0; i < nun; i++) {
        printf("%c\t", nt[i]);
        for (j = 0; j < nut; j++) {
            printf("%s\t", table[i][j]);
        }
        printf("\n");
    }

    printf("Enter string to be parsed:\n");
    scanf("%s", inputStr);
    strcat(inputStr, "$");

    stack[top++] = '$';
    stack[top++] = nt[0]; // Push start symbol

    i = 0;
    while (1) {
        if ((stack[top - 1] == '$') && (inputStr[i] == '$')) {
            printf("String Accepted.\n");
            break;
        } else if (!isupper(stack[top - 1])) {
            if (stack[top - 1] == inputStr[i]) {
                i++;
                top--;
            } else {
                printf("ERROR!! Not accepted.\n");
                break;
            }
        } else {
            char NT = stack[top - 1];
            char T = inputStr[i];
            replace(NT, T);
        }
    }

    getch();
    return 0;
}

int getnt(char x) {
    int a;
    for (a = 0; a < nun; a++) {
        if (x == nt[a])
            return a;
    }
    return 100;
}

int gett(char x) {
    int a;
    for (a = 0; a < nut; a++) {
        if (x == t[a])
            return a;
    }
    return 100;
}

void replace(char NT, char T) {
    int in1, it1, len, j;
    char str[10];

    in1 = getnt(NT);
    it1 = gett(T);

    if ((in1 != 100) && (it1 != 100)) {
        strcpy(str, table[in1][it1]);

        if (strcmp(str, "#") == 0) {
            printf("Error: No rule.\n");
            return;
        } else if (strcmp(str, "@") == 0) { // epsilon production
            top--;
        } else {
            len = strlen(str);
            top--;  // Pop NT
            for (j = len - 1; j >= 0; j--) {
                stack[top++] = str[j]; // Push in reverse
            }
        }
    } else {
        printf("Not valid.\n");
    }
}
