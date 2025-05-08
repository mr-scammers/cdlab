#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

char action[20][10][3], nt[10], t[10], inp[20], stack[50][10], a[3];
char pro[20][10], str[10], str2[10], state[20][2], gto[20][10][2];
int t1, s1, x;
int nut, nun, i = 0, top = 0, np, numst, nent, k;

int getnt(char);
int gett(char);
int getst(char*);

void main() {
    int i, j, len, n1, n2, i1, j1;
    char ch, ans = 'y', temp[10];
    
    clrscr();

    printf("Enter number of terminals:\n");
    scanf("%d", &nut);

    printf("Enter number of non-terminals:\n");
    scanf("%d", &nun);

    printf("Enter number of productions:\n");
    scanf("%d", &np);

    for (i = 1; i <= np; i++) {
        printf("Enter production %d:\n", i);
        scanf("%s", pro[i]);
    }

    for (i = 1; i <= np; i++) {
        printf("Production %d = %s\n", i, pro[i]);
    }

    printf("Enter all non-terminals:\n");
    scanf("%s", nt);

    printf("Enter all terminals:\n");
    scanf("%s", t);

    printf("Enter number of states:\n");
    scanf("%d", &numst);

    for (i = 0; i < numst; i++) {
        printf("Enter state name:\n");
        scanf("%s", state[i]);
    }

    printf("Enter ACTION table (s2 for shift 2, r2 for reduce 2, ac for accept, e for error):\n");
    for (i = 0; i < numst; i++) {
        for (j = 0; j < nut; j++) {
            strcpy(action[i][j], " ");
            printf("Enter for state %d and terminal %c: ", i, t[j]);
            scanf("%s", action[i][j]);
        }
    }

    for (i = 0; i < numst; i++) {
        for (j = 0; j < nun; j++) {
            strcpy(gto[i][j], " ");
        }
    }

    printf("Enter number of GOTO entries:\n");
    scanf("%d", &nent);

    for (k = 0; k < nent; k++) {
        printf("Enter state number: ");
        scanf("%d", &i1);
        fflush(stdin);
        printf("Enter non-terminal: ");
        scanf("%c", &ch);
        j1 = getnt(ch);
        fflush(stdin);
        printf("Enter GOTO[%d][%d]: ", i1, j1);
        scanf("%s", gto[i1][j1]);
    }

    printf("\n\t\tACTION TABLE\nStates");
    for (j = 0; j < nut; j++) {
        printf("\t %c", t[j]);
    }
    printf("\n********************************\n");

    for (i = 0; i < numst; i++) {
        printf("|%s\t|", state[i]);
        for (j = 0; j < nut; j++) {
            printf("|%s\t|", action[i][j]);
        }
        printf("\n\n");
    }

    printf("\t\tGOTO TABLE\nStates");
    for (j = 0; j < nun; j++) {
        printf("|\t%c|", nt[j]);
    }
    printf("\n**************************\n");

    for (i = 0; i < numst; i++) {
        printf("|%s\t|", state[i]);
        for (j = 0; j < nun; j++) {
            printf("|%s\t|", gto[i][j]);
        }
        printf("\n\n");
    }

    do {
        strcpy(inp, "");
        printf("Enter string to parse:\n");
        scanf("%s", inp);

        top = 0;
        strcpy(stack[top++], "$");
        strcpy(stack[top++], "0");
        i = 0;

        while (1) {
            t1 = gett(inp[i]);
            s1 = getst(stack[top - 1]);
            strcpy(str, action[s1][t1]);

            if (strcmp(str, "ac") == 0) {
                printf("String accepted\n");
                break;
            } else if (str[0] == 's') {
                temp[0] = inp[i++];
                temp[1] = '\0';
                strcpy(stack[top++], temp);
                strcpy(temp, &str[1]);
                strcpy(stack[top++], temp);
            } else if (str[0] == 'r') {
                a[0] = str[1];
                a[1] = '\0';
                x = atoi(a);
                strcpy(str2, pro[x]);
                len = strlen(str2) - 3;
                top = top - 2 * len;
                temp[0] = str2[0];
                temp[1] = '\0';
                strcpy(stack[top++], temp);
                n1 = getst(stack[top - 2]);
                n2 = getnt(str2[0]);
                strcpy(stack[top++], gto[n1][n2]);
            } else {
                printf("Error: not a valid string\n");
                break;
            }
        }

        fflush(stdin);
        printf("Do you want to continue (y/n)? ");
        scanf("%c", &ch);
    } while (ch == 'y' || ch == 'Y');
}

int getnt(char x) {
    int a;
    for (a = 0; a < nun; a++)
        if (x == nt[a])
            return a;
    return 100;
}

int gett(char x) {
    int a;
    for (a = 0; a < nut; a++)
        if (x == t[a])
            return a;
    return 100;
}

int getst(char st[]) {
    int l;
    for (l = 0; l < numst; l++)
        if (strcmp(st, state[l]) == 0)
            return l;
    return 100;
}
