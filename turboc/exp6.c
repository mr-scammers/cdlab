#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void main() {
    int i = 0, j = 0, l1, k = 0, m = 0, len, n = 0, o = 0, o1 = 0, var = 0, f = 0, c = 0, f1 = 0;
    char str[30], str1[40] = "E", temp[20], temp1[20], temp2[20], tt[20], t3[20], t[10];

    char array[6][5][10] = {
        {"NT", "<id>", "+", "*", "$"},
        {"E", "Te", "Error", "Error", "Error"},
        {"e", "Error", "+Te", "Error", "\0"},
        {"T", "Vt", "Error", "Error", "Error"},
        {"t", "Error", "\0", "*Vt", "\0"},
        {"V", "<id>", "Error", "Error", "Error"}
    };

    printf("\n\tLL(1) PARSER TABLE \n");
    for (i = 0; i < 6; i++) {
        for (j = 0; j < 5; j++) {
            printf("%s\t", array[i][j]);
        }
        printf("\n");
    }

rep:
    printf("\n\tENTER THE STRING :");
    gets(str);

    if (str[strlen(str) - 1] != '$') {
        printf("END OF STRING MARKER SHOULD BE '$'");
        goto rep;
    }

    printf("\n\tCHECKING VALIDATION OF THE STRING ");
    printf("\n\t%s", str1);
    i = 0;

    while (i < strlen(str)) {
    again:
        if (str[i] == ' ' && i < strlen(str)) {
            printf("\n\tSPACES ARE NOT ALLOWED IN SOURCE STRING ");
            exit(1);
        }

        temp[k] = str[i];
        temp[k + 1] = '\0';
        f1 = 0;

    again1:
        if (i >= strlen(str)) {
            exit(1);
        }

        for (l1 = 1; l1 <= 4; l1++) {
            if (strcmp(temp, array[0][l1]) == 0) {
                f1 = 1;
                m = 0, o = 0, var = 0, o1 = 0;
                strcpy(temp1, "\0");
                strcpy(temp2, "\0");

                while (m < strlen(str1) && m < strlen(str)) {
                    if (str1[m] == str[m]) {
                        var = m + 1;
                        temp2[o1] = str1[m];
                        m++;
                        o1++;
                    } else {
                        if ((m + 1) < strlen(str1)) {
                            m++;
                            temp1[o] = str1[m];
                            o++;
                        } else
                            m++;
                    }
                }

                temp2[o1] = '\0';
                temp1[o] = '\0';
                t[0] = str1[var];
                t[1] = '\0';

                for (n = 1; n <= 5; n++) {
                    if (strcmp(array[n][0], t) == 0)
                        break;
                }

                strcpy(str1, temp2);
                strcat(str1, array[n][l1]);
                strcat(str1, temp1);
                printf("\n\t%s", str1);

                if (strcmp(array[n][l1], "\0") == 0) {
                    if (i == (strlen(str) - 1)) {
                        len = strlen(str1);
                        str1[len - 1] = '\0';
                        printf("\n\t%s", str1);
                        printf("\n\n\tENTERED STRING IS VALID");
                        exit(1);
                    }
                    strcpy(temp1, "\0");
                    strcpy(temp2, "\0");
                    strcpy(t, "\0");
                    goto again1;
                }

                if (strcmp(array[n][l1], "Error") == 0) {
                    printf("\n\tERROR IN YOUR SOURCE STRING");
                    exit(1);
                }

                strcpy(tt, "\0");
                strcpy(tt, array[n][l1]);
                strcpy(t3, "\0");
                f = 0;

                for (c = 0; c < strlen(tt); c++) {
                    t3[c] = tt[c];
                    t3[c + 1] = '\0';

                    if (strcmp(t3, temp) == 0) {
                        f = 0;
                        break;
                    } else
                        f = 1;
                }

                if (f == 0) {
                    strcpy(temp, "\0");
                    strcpy(temp1, "\0");
                    strcpy(temp2, "\0");
                    strcpy(t, "\0");
                    i++;
                    k = 0;
                    goto again;
                } else {
                    strcpy(temp1, "\0");
                    strcpy(temp2, "\0");
                    strcpy(t, "\0");
                    goto again1;
                }
            }
        }
        i++;
        k++;
    }

    if (f1 == 0)
        printf("\nENTERED STRING IS INVALID");
    else
        printf("\n\n\tENTERED STRING IS VALID");
}
