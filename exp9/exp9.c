#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct three {
    char data[10], temp[7];
} s[30];

int main() {
    char d1[7], d2[7] = "t";
    int i = 0, j = 1, len = 0;
    FILE *f1, *f2;
    char defaultInput[] = "out = in1 + in2 + in3 - in4"; // Default input if sum.txt not found

    // Try to open sum.txt for reading
    f1 = fopen("sum.txt", "r");
    if (f1 == NULL) {
        // If sum.txt doesn't exist, use default input from the lab manual
        printf("sum.txt not found. Using default input.\n");
        // Tokenize the default input string
        char *token = strtok(defaultInput, " ");
        while (token != NULL) {
            strcpy(s[len].data, token);
            len++;
            token = strtok(NULL, " ");
        }
    } else {
        // Read tokens from sum.txt into the structure array
        while (fscanf(f1, "%s", s[len].data) != EOF)
            len++;
        fclose(f1);
    }

    // Open out.txt for writing the generated three-address code
    f2 = fopen("out.txt", "w");
    if (f2 == NULL) {
        printf("Error opening out.txt for writing.\n");
        return 1;
    }
    
    /* 
      The program assumes a specific token order:
      For a default input: 
         out = in1 + in2 + in3 - in4 
      tokens are:
         s[0].data = "out"
         s[1].data = "="
         s[2].data = "in1"
         s[3].data = "+"
         s[4].data = "in2"
         s[5].data = "+"
         s[6].data = "in3"
         s[7].data = "-"
         s[8].data = "in4"
    */

    // Generate the first temporary variable (t1) for the first operation
    sprintf(d1, "%d", j);
    strcat(d2, d1);
    strcpy(s[j].temp, d2);
    strcpy(d1, "");
    strcpy(d2, "t");
    
    // Process the first operation (in1 + in2 or in1 - in2)
    if (strcmp(s[3].data, "+") == 0) {
        fprintf(f2, "%s = %s + %s", s[j].temp, s[2].data, s[4].data);
        j++;
    } else if (strcmp(s[3].data, "-") == 0) {
        fprintf(f2, "%s = %s - %s", s[j].temp, s[2].data, s[4].data);
        j++;
    }
    
    // Process remaining operations. In the default input, we expect two operations:
    // Operation 2: t1 + in3
    // Operation 3: t2 - in4
    for (i = 4; i < len - 2; i += 2) {
        sprintf(d1, "%d", j);
        strcat(d2, d1);
        strcpy(s[j].temp, d2);
        if (strcmp(s[i+1].data, "+") == 0)
            fprintf(f2, "\n%s = %s + %s", s[j].temp, s[j-1].temp, s[i+2].data);
        else if (strcmp(s[i+1].data, "-") == 0)
            fprintf(f2, "\n%s = %s - %s", s[j].temp, s[j-1].temp, s[i+2].data);
        
        strcpy(d1, "");
        strcpy(d2, "t");
        j++;
    }
    
    // Finally, assign the last temporary result to the output variable.
    fprintf(f2, "\n%s = %s", s[0].data, s[j-1].temp);
    
    fclose(f2);
    
    printf("Three address code generated successfully in out.txt\n");
    
    // Pause before exit (press Enter to exit)
    printf("Press Enter to exit...");
    getchar(); // To catch any leftover newline from input
    getchar();
    
    return 0;
}
