#include <stdio.h>
#include <string.h>
#include <ctype.h>
int n, m = 0;
char a[10][10], f[10];
void first(char c);
void follow(char c);
int is_present(char c);
int main() {
    int z;
    char c;
    printf("Enter the no. of productions: ");
    scanf("%d", &n);
    printf("Enter productions:\n");
    for (int i = 0; i < n; i++) {
        scanf("%s", a[i]);
    }
    do {
        m = 0;
        printf("Enter the element whose First and Follow is to be found: ");
        scanf(" %c", &c);
        first(c);
        printf("First(%c):{", c);
        for (int i = 0; i < m; i++) {
            printf("%c", f[i]);
            if (i < m - 1) printf(",");
        }
        printf("}\n");
        strcpy(f, "");
        m = 0;
        follow(c);
        printf("Follow(%c):{", c);
        for (int i = 0; i < m; i++) {
            printf("%c", f[i]);
            if (i < m - 1) printf(",");
        }
        printf("}\n");
        printf("Continue(0/1): ");
        scanf("%d", &z);

    } while (z == 1);
    return 0;
}
void first(char c) {
    if (!isupper(c)) { // If terminal, add to First set
        if (!is_present(c)) f[m++] = c;
        return;
    }
    for (int k = 0; k < n; k++) {
        if (a[k][0] == c) { // Match non-terminal
            if (a[k][2] == '$') { // ε-production
                if (!is_present('$')) f[m++] = '$';
            } else if (islower(a[k][2])) { // Terminal
                if (!is_present(a[k][2])) f[m++] = a[k][2];
            } else { // Non-terminal
                first(a[k][2]);
            }
        }
    }
}
void follow(char c) {
    if (a[0][0] == c) { // Add $ for start symbol
        if (!is_present('$')) f[m++] = '$';
    }
    for (int i = 0; i < n; i++) {
        for (int j = 2; j < strlen(a[i]); j++) {
            if (a[i][j] == c) {
                if (a[i][j + 1] != '\0') { // If there's a symbol after `c`
                    first(a[i][j + 1]);
                }
                if (a[i][j + 1] == '\0' && c != a[i][0]) { 
                    follow(a[i][0]);
                }
            }
        }
    }
}
int is_present(char c) {
    for (int i = 0; i < m; i++) {
        if (f[i] == c) return 1;
    }
    return 0;
}
