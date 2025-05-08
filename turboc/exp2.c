#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <ctype.h>

int n;
char productions[10][10];
char firstSet[10], followSet[10];
int firstIndex = 0, followIndex = 0;

void computeFirst(char c);
void computeFollow(char c);
int isAlreadyPresent(char arr[], int size, char c);

void main() {
    int i;
    int choice;
    char c;

    clrscr();

    printf("Enter number of productions: ");
    scanf("%d", &n);

    printf("Enter productions (e.g., A->aB or A->$):\n");
    for (i = 0; i < n; i++) {
        scanf("%s", productions[i]);
    }

    do {
        firstIndex = followIndex = 0;

        for (i = 0; i < 10; i++) {
            firstSet[i] = '\0';
            followSet[i] = '\0';
        }

        printf("\nEnter the non-terminal to compute First and Follow: ");
        flushall();
        scanf("%c", &c);

        computeFirst(c);
        printf("First(%c) = { ", c);
        for (i = 0; i < firstIndex; i++) {
            printf("%c", firstSet[i]);
            if (i < firstIndex - 1)
                printf(", ");
        }
        printf(" }\n");

        computeFollow(c);
        printf("Follow(%c) = { ", c);
        for (i = 0; i < followIndex; i++) {
            printf("%c", followSet[i]);
            if (i < followIndex - 1)
                printf(", ");
        }
        printf(" }\n");

        printf("Do you want to continue? (1 = Yes / 0 = No): ");
        scanf("%d", &choice);

    } while (choice == 1);

    getch();
}

void computeFirst(char c) {
    int i;
    if (!isupper(c)) {
        if (!isAlreadyPresent(firstSet, firstIndex, c))
            firstSet[firstIndex++] = c;
        return;
    }

    for (i = 0; i < n; i++) {
        if (productions[i][0] == c) {
            if (productions[i][3] == '$') {
                if (!isAlreadyPresent(firstSet, firstIndex, '$'))
                    firstSet[firstIndex++] = '$';
            } else if (islower(productions[i][3])) {
                if (!isAlreadyPresent(firstSet, firstIndex, productions[i][3]))
                    firstSet[firstIndex++] = productions[i][3];
            } else {
                computeFirst(productions[i][3]);
            }
        }
    }
}

void computeFollow(char c) {
    int i, j, k;
    int len;

    if (productions[0][0] == c) {
        if (!isAlreadyPresent(followSet, followIndex, '$'))
            followSet[followIndex++] = '$';
    }

    for (i = 0; i < n; i++) {
        len = strlen(productions[i]);
        for (j = 3; j < len; j++) {
            if (productions[i][j] == c) {
                if (productions[i][j + 1] != '\0') {
                    computeFirst(productions[i][j + 1]);
                    for (k = 0; k < firstIndex; k++) {
                        if (firstSet[k] != '$' && !isAlreadyPresent(followSet, followIndex, firstSet[k]))
                            followSet[followIndex++] = firstSet[k];
                    }
                }
                if (productions[i][j + 1] == '\0' && productions[i][0] != c) {
                    computeFollow(productions[i][0]);
                }
            }
        }
    }
}

int isAlreadyPresent(char arr[], int size, char c) {
    int i;
    for (i = 0; i < size; i++) {
        if (arr[i] == c)
            return 1;
    }
    return 0;
}
