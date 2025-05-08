#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct three {
    char data[10], temp[7];
} s[30];

int main() {
    char d1[7], d2[7] = "t", *token;
    int i = 0, j = 1, len = 0;
    FILE *f1, *f2;
    char defaultInput[] = "out = in1 + in2 + in3 - in4"; // Default input

    f1 = fopen("sum.txt", "r");
    if (f1 == NULL) {
        printf("sum.txt not found. Using default input.\n");

        // Tokenize default input
        token = strtok(defaultInput, " ");
        while (token != NULL) {
            strcpy(s[len].data, token);
            len++;
            token = strtok(NULL, " ");
        }
    } else {
        // Read from file
        while (fscanf(f1, "%s", s[len].data) != EOF)
            len++;
        fclose(f1);
    }

    f2 = fopen("out.txt", "w");
    if (f2 == NULL) {
        printf("Error opening out.txt for writing.\n");
        return 1;
    }

    // First operation
    sprintf(d1, "%d", j);
    strcat(d2, d1);
    strcpy(s[j].temp, d2);
    d1[0] = '\0';          // Clear d1
    strcpy(d2, "t");       // Reset d2

    if (strcmp(s[3].data, "+") == 0) {
        fprintf(f2, "%s = %s + %s", s[j].temp, s[2].data, s[4].data);
        j++;
    } else if (strcmp(s[3].data, "-") == 0) {
        fprintf(f2, "%s = %s - %s", s[j].temp, s[2].data, s[4].data);
        j++;
    }

    // Remaining operations
    for (i = 4; i < len - 2; i += 2) {
        sprintf(d1, "%d", j);
        strcat(d2, d1);
        strcpy(s[j].temp, d2);

        if (strcmp(s[i + 1].data, "+") == 0)
            fprintf(f2, "\n%s = %s + %s", s[j].temp, s[j - 1].temp, s[i + 2].data);
        else if (strcmp(s[i + 1].data, "-") == 0)
            fprintf(f2, "\n%s = %s - %s", s[j].temp, s[j - 1].temp, s[i + 2].data);

        d1[0] = '\0';      // Clear d1
        strcpy(d2, "t");   // Reset d2
        j++;
    }

    // Final assignment
    fprintf(f2, "\n%s = %s", s[0].data, s[j - 1].temp);
    fclose(f2);

    printf("Three address code generated successfully in out.txt\n");

    printf("Press Enter to exit...");
    getchar(); // to consume leftover newline
    getchar(); // to pause

    return 0;
}
