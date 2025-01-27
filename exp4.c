#include<stdio.h> 
#include<conio.h> 
#include<string.h>
void main()
{
    char exp[20],id[10],dig[10],ch;
    int i,j;
    clrscr();
    printf("enter expression:");
    scanf("%s",&exp);
    for(i=0;i<strlen(exp);)
    {
        ch=exp[i]; j=0;
        if(ch>='a'&&ch<='z')
        {
            id[j++]=ch; 
            i++;
            while((exp[i]>='a'&&exp[i]<='z')||(exp[i]>='0'&&exp[i]<='9'))
            {
                id[j++]=exp[i++];
            }
            id[j]='\0';
            printf("\nidentifier:%s",id);
        }
        else if(ch=='+'||ch=='-'||ch=='*'||ch=='/'||ch=='%'||ch=='=')
        {
            printf("\noperator:%c",ch); 
            i++;
        }
        else if(ch>='0'&&ch<='9')
        {
            dig[j++]=ch;
            i++;
            while(exp[i]>='0'&&exp[i]<='9') 
            dig[j++]=exp[i++];
        dig[j]='\0';
        printf("\nconstant:%s",dig);
        }

    }//for 
        getch();
}