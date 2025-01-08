#include <stdio.h>
#include <ctype.h>
#include <string.h>
FILE *fp;
static char ch;
char *keyword[20] = {"void", "main", "int", "float"};
char brace[20] = {'(', ')', '{', '}', '[', ']'};
char operator[20] = {'+', '-', '*', '/', '%', '<', '>', '='};
char symbol[20] = {';', '/', '"', ':', ','};
char identifier[32];
char number[3];
int i;
int chkkey();
void scantoken();
int main() {
    fp = fopen("prg.c", "w");
    if (fp == NULL) {
        printf("Unable to open file for writing\n");
        return 1;
    }
    printf("Write the input program (end input with '@'):\n");
    while ((ch = getchar()) != '@') {
        putc(ch, fp);
    }
    fclose(fp);
    fp = fopen("prg.c", "r");
    if (fp == NULL) {
        printf("Unable to open file for reading\n");
        return 1;
    }
    ch = getc(fp);
    printf("\n\n");
    printf("tokens\t\tlexemes\n");
    printf("\n");
    while (!feof(fp)) {
        scantoken();
    }
    fclose(fp);
    return 0;
}
void scantoken() {
    int j;
    for (i = 0; i < 4; i++) {
        if (ch == brace[i]) {
            printf("brace\t\t>%c\n", ch);
            ch = getc(fp);
            return;
        }
    }
    for (i = 0; i < 8; i++) {
        if (ch == operator[i]) {
            printf("operator\t>%c\n", ch);
            ch = getc(fp);
            return;
        }
    }
    for (i = 0; i < 5; i++) {
        if (ch == symbol[i]) {
            printf("symbol\t\t>%c\n", ch);
            ch = getc(fp);
            return;
        }
    }
    if (isalpha(ch)) { // Check for identifier or keyword
        identifier[0] = ch;
        identifier[1] = '\0';
        j = 1;
        ch = getc(fp);
        while (isalnum(ch)) {
            identifier[j++] = ch;
            ch = getc(fp);
        }
        identifier[j] = '\0';
        if (chkkey() == 1) {
            printf("keyword\t\t>%s\n", identifier);
        } else {
            printf("identifier\t>%s\n", identifier);
        }
    } else if (isdigit(ch)) { // Check for number
        number[0] = ch;
        j = 1;
        ch = getc(fp);
        while (isdigit(ch)) {
            number[j++] = ch;
            ch = getc(fp);
        }
        number[j] = '\0';
        printf("number\t\t>%s\n", number);
    } else if (isspace(ch)) {
        ch = getc(fp); // Skip spaces
    }
}
int chkkey() {
    int flag = 0;
    for (i = 0; i < 4; i++) {
        if (strcmp(keyword[i], identifier) == 0) {
            flag = 1;
            break;
        }
    }
    return flag;
}