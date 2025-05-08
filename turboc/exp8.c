#include <stdio.h>
#include <string.h>
#include <stdlib.h>  // For system()

int top = 0, l = 0, j, k;
char st[20], ip[20], str[20], op[20];

void push(char c);
void pop();
void disp();

int main() {
    int i, n = 0;
    // Uncomment the next line if you want to clear the screen (works on Windows, use "clear" on Linux)
    // system("cls");
    printf("Enter the input string: ");
    scanf("%s", ip);

    j = 0;
    strcat(ip, "$");
    l = strlen(ip);
    push('$');

    printf("\n\t\tStack\t\tInput\t\tAction");
    disp();

    for (i = 0; i <= l; i++) {
        if (ip[j] == 'i') {
            printf("\n\t\tShift");
            push(ip[j]);
            j++;
            disp();
        } else if (ip[j] == '+' || ip[j] == '-' || ip[j] == '*' || ip[j] == '/') {
            n++;
            printf("\n\t\tShift");
            push(ip[j]);
            j++;
            disp();
        }
        if (st[k] == 'i') {
            st[k] = 'E';
            printf("\n\t\tReduce");
            disp();
        }
    }

    while (n > 0) {
        pop();
        pop();
        printf("\n\t\tReduce");
        disp();
        n--;
    }

    if ((strcmp(str, "$E") == 0) && (ip[j] == '$'))
        printf("\n\t\tAccepted");
    else
        printf("\n\n\t\tError");

    // Pause the program by waiting for user input
    printf("\nPress Enter to exit...");
    getchar();  // To catch newline left by scanf
    getchar();
    return 0;
}

void push(char c) {
    k = top;
    st[top++] = c;
}

void pop() {
    top--;
}

void disp() {
    int i;
    printf("\n\t\t");
    for (i = 0; i < top; i++) {
        printf("%c", st[i]);
        str[i] = st[i];
    }
    str[i] = '\0';
    printf("\t\t");
    for (i = j; i < l; i++)
        printf("%c", ip[i]);
}
