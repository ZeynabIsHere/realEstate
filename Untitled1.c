#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>
#include<conio.h>
#include<string.h>
#include<windows.h>
#include<time.h>
char sign_up()
{
    FILE signUP*;
    signUP=fopen("members_list.txt","w");
    printf("User Name: ");
    printf("First Name: ");
    printf("Last Name: ");
    printf("ID Number: ");
    printf("Phone Number: ");
    printf("First Name: ");

}
char menu()
{
    int choice;
    printf("1.Sign up");
    printf("2.Sign in");
    printf("3.Exit");
    scanf("%d", &choice);
    switch(choice)
    case 1:
}

void main()
{
    printf("\033[1;34m[Welcome to the real estate company\]");
    printf("\n\n\033[1;36mClick the Enter to continue...");
    getchar();
    system("cls");
    printf("world");
}


