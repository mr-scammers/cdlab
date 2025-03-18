#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Maximum sizes for arrays
#define MAX_STATES 20
#define MAX_TOKEN 10
#define MAX_PRODUCTIONS 20

// Global tables and arrays
char action[MAX_STATES][MAX_TOKEN][3];  // ACTION table: state x terminal -> action string
char gto[MAX_STATES][MAX_TOKEN][3];     // GOTO table: state x nonterminal -> state string
char stateNames[MAX_STATES][3];         // Names of states (as strings)
char nonterminals[MAX_TOKEN];           // Array of nonterminals
char terminals[MAX_TOKEN];              // Array of terminals

char pro[MAX_PRODUCTIONS][10];          // Productions: indexed from 1
int numStates, numTerm, numNonterm, numProds, numGtoEntries;

int getNonterminalIndex(char ch) {
    for (int i = 0; i < numNonterm; i++) {
        if (nonterminals[i] == ch)
            return i;
    }
    return -1;
}

int getTerminalIndex(char ch) {
    for (int i = 0; i < numTerm; i++) {
        if (terminals[i] == ch)
            return i;
    }
    return -1;
}

int getStateIndex(char *st) {
    for (int i = 0; i < numStates; i++) {
        if (strcmp(st, stateNames[i]) == 0)
            return i;
    }
    return -1;
}

int main() {
    int i, j, k;
    int i1, j1;
    int index;  // used for temporary indices
    char ch;
    char temp[5];

    // Input the grammar tables from the user.
    printf("Enter number of terminals: ");
    scanf("%d", &numTerm);
    printf("Enter number of nonterminals: ");
    scanf("%d", &numNonterm);
    printf("Enter number of productions: ");
    scanf("%d", &numProds);

    // Read productions (indexed from 1)
    for (i = 1; i <= numProds; i++) {
        printf("Enter production %d (e.g., S->CC): ", i);
        scanf("%s", pro[i]);
    }
    for (i = 1; i <= numProds; i++) {
        printf("Production %d = %s\n", i, pro[i]);
    }

    printf("Enter all nonterminals (as a string, e.g., SC): ");
    scanf("%s", nonterminals);

    printf("Enter all terminals (as a string, e.g., cd$): ");
    scanf("%s", terminals);

    // Read state information
    printf("Enter number of states: ");
    scanf("%d", &numStates);
    for (i = 0; i < numStates; i++) {
        printf("Enter state name for state %d: ", i);
        scanf("%s", stateNames[i]);
    }

    // Fill ACTION table entries
    printf("Enter ACTION table entries:\n");
    // For each state and each terminal:
    for (i = 0; i < numStates; i++) {
        for (j = 0; j < numTerm; j++) {
            printf("Enter action for state %s and terminal %c: ", stateNames[i], terminals[j]);
            scanf("%s", action[i][j]);
        }
    }

    // Initialize GOTO table with spaces
    for (i = 0; i < numStates; i++) {
        for (j = 0; j < numNonterm; j++) {
            strcpy(gto[i][j], " ");
        }
    }

    // Read GOTO table entries from the user
    printf("Enter number of GOTO entries: ");
    scanf("%d", &numGtoEntries);
    for (k = 0; k < numGtoEntries; k++) {
        printf("Enter state number for GOTO entry: ");
        scanf("%d", &i1);
        printf("Enter nonterminal for this entry: ");
        scanf(" %c", &ch);
        j1 = getNonterminalIndex(ch);
        if (j1 == -1) {
            printf("Error: Nonterminal %c not found.\n", ch);
            exit(1);
        }
        printf("Enter GOTO value for state %d and nonterminal %c: ", i1, ch);
        scanf("%s", gto[i1][j1]);
    }

    // Display ACTION table
    printf("\n\t\tACTION TABLE\nStates");
    for (j = 0; j < numTerm; j++)
        printf("\t%c", terminals[j]);
    printf("\n********************************\n");
    for (i = 0; i < numStates; i++) {
        printf("|%s\t", stateNames[i]);
        for (j = 0; j < numTerm; j++) {
            printf("|%s\t", action[i][j]);
        }
        printf("|\n\n");
    }

    // Display GOTO table
    printf("\n\t\tGOTO TABLE\nStates");
    for (j = 0; j < numNonterm; j++)
        printf("\t%c", nonterminals[j]);
    printf("\n**************************\n");
    for (i = 0; i < numStates; i++) {
        printf("|%s\t", stateNames[i]);
        for (j = 0; j < numNonterm; j++) {
            printf("|%s\t", gto[i][j]);
        }
        printf("|\n\n");
    }

    // Parsing process: we use a simple stack for states and symbols.
    char stack[50][5];   // Stack array to hold symbols (each as a string)
    int top = 0;         // Stack pointer
    char input[50];
    int ip = 0;          // Pointer into input string

    // Initialize stack with "$" and state "0"
    strcpy(stack[top++], "$");
    strcpy(stack[top++], stateNames[0]);

    printf("Enter string to be parsed: ");
    scanf("%s", input);

    // Main parsing loop
    while (1) {
        int termIndex = getTerminalIndex(input[ip]);
        int stateIndex = getStateIndex(stack[top - 1]);
        if (termIndex == -1 || stateIndex == -1) {
            printf("Error: Invalid terminal or state.\n");
            break;
        }
        char act[10];
        strcpy(act, action[stateIndex][termIndex]);
        
        if (act[0] == 'a') { // Accept action ("ac")
            printf("String accepted\n");
            break;
        } else if (act[0] == 's') { // Shift action, e.g., "s2"
            char tempStr[5];
            // Shift the terminal from input to the stack
            tempStr[0] = input[ip++];
            tempStr[1] = '\0';
            strcpy(stack[top++], tempStr);
            // Extract the state number from action string
            strcpy(tempStr, act + 1);  // skip the 's'
            strcpy(stack[top++], tempStr);
        } else if (act[0] == 'r') { // Reduce action, e.g., "r3"
            int prodNo = atoi(act + 1); // production number
            char prod[10];
            strcpy(prod, pro[prodNo]); // production in the form "A->alpha"
            int prodLen = strlen(prod) - 3; // length of alpha (assuming production form "A->")
            // Pop 2 * prodLen items from stack (symbol and state for each symbol)
            top = top - (2 * prodLen);
            char lhs[5];
            lhs[0] = prod[0];  // LHS nonterminal of production
            lhs[1] = '\0';
            strcpy(stack[top++], lhs);
            // Now, get GOTO value for the new state.
            int s1 = getStateIndex(stack[top - 2]);
            int ntIndex = getNonterminalIndex(prod[0]);
            if (s1 == -1 || ntIndex == -1) {
                printf("Error: GOTO lookup failed.\n");
                break;
            }
            strcpy(stack[top++], gto[s1][ntIndex]);
            printf("Reduced using production %s\n", prod);
        } else {
            printf("Error: Invalid action encountered\n");
            break;
        }
    }

    printf("Parsing complete.\n");

    // Pause before exit
    printf("Press Enter to exit...");
    getchar(); // catch leftover newline
    getchar();
    return 0;
}
