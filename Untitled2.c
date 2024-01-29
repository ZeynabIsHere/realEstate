#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>
#include<conio.h>
#include<string.h>
#include<windows.h>
#include<time.h>
int checkingPassword(char *firstCode, char *secCode)
{
    //this function checks the second code and compare it to the first one.
    char wrong, tru, userCode[80], doubleCheckingCode[80];
    int result=strcmp(userCode, doubleCheckingCode);
    if(result!=0)
    {
        return 1;
    }
    else return 0;
}
char checkingPhoneNumber(char *num)
{
//this function checks for number, not bigger than 10 numbers
    char can, cant, phoneNum[10];
    int length=strlen(phoneNum);

    if(length==11 && phoneNum[0]=='9')
        //checking length of array
    {
        return can;
    }
    else
        return cant;
}
char checkingCode(char *code)
//this function is for checking the code
{
    char tr, fl;
    char password[80];
    int length=0, upperCase=0, lowerCase=0, digit=0;
    length=strlen(password);
    // the password should be at least 8 character, with lower case and upper case and number, so we consider that here.
    for(int i=0; i<length; i++)
    {
        if(password[i]>='A' && password[i]<='Z')
        {
            upperCase=1;
            //at least having 1 uppercase
        }
        else if(password[i]>='a' && password[i]<='z')
        {
            lowerCase=1;
            //at least having 1 lower case
        }
        else if(password[i]>='0' && password[i]<='9')
        {
            digit=1;
            //at least having 1 digit
        }
    }
    if(length>=8 && upperCase && lowerCase && digit)
        return 1;
    else
    {
        return 0;
    }
}
// if its right it returns 1, otherwise 0.
char checkingEmail(char *email)
//this function is for checking email.
{
    char i, truee, fals;
    int atCounter=0, dotCounter=0, index=0, lastDotIndex=0;
    //cheking email for having . and @
    for(int i=0; email[i] !='\0'; i++)
    {
        //check for having @ but not at first
        if(email[i]=='@')
        {
            index=i;
            if(index==0)
            {
                return 0; //first character cant be @
            }
            atCounter++;
            if(atCounter>1)
            {
                return 0; // there was more than one @, so its invalid
            }
        }
        if(email[i]=='.')
        {
            dotCounter++;
            lastDotIndex=i;
        }

        if((atCounter==1 && dotCounter>0)&&(lastDotIndex>index))
            //it was for checking at least '.' after @
        {
            return truee;
            //for valid email
        }
        else
        {
            return fals;
            //for invalid email
        }
    }
}
struct signUpProfile
//this structure has built for profile for signing up.
{
    char userName[40];
    char firstName[60];
    char lastName[60];
    char idNumber[12];
    char phoneNumber[14];
    char Email[60];
    char userCode[80];
    char doubleCheckingCode[40];
} signUpProfile;
char sign_up()
//this is the menu for getting sign up profile
{
    int n, m, len, s, f;
    char fals, fl, cant, wrong;
    // fals and fl stands for false
    FILE *signUP;
    signUP=fopen("members_list.txt","w");
    if(signUP==NULL)
    {
        printf("Error opening the file.");
        exit(0);
    }
    printf("User Name: ");
    getchar();
    gets(signUpProfile.userName);
    printf("\nFirst Name: ");
    gets(signUpProfile.firstName);
    printf("\nLast Name: ");
    gets(signUpProfile.lastName);
    printf("\nID Number: ");
    gets(signUpProfile.idNumber);
    printf("\nPhone Number: 98");
    gets(signUpProfile.phoneNumber);
    s=checkingPhoneNumber(signUpProfile.phoneNumber);
    //here i just call the function which checks the phone number for me.
    if(s==cant)
        printf("Invalid phone number");
    else
    {
        printf("\nEmail: ");
        gets(signUpProfile.Email);
        n=checkingEmail(signUpProfile.Email);
        //here i just call the function which checks the email for me.
        if(n=='fals')
            printf("Invalid Email");
        else
        {
            printf("\nEnter your code(more than 8 character): ");
            gets(signUpProfile.userCode);
            m=checkingCode(signUpProfile.userCode);
            if(m==1)
                printf("Invalid code");
            else
            {
                printf("\nEnter the code one more time: ");
                gets(signUpProfile.doubleCheckingCode);
                f=checkingPassword(signUpProfile.doubleCheckingCode, signUpProfile.userCode);
                if(f==1)
                {
                    printf("invalid cpode");
                }
            }
        }
        struct signUpProfile *start, *temp, *end;
        start=malloc(sizeof(struct signUpProfile));
        temp=malloc(sizeof(struct signUpProfile));
        //start shows the first node so the temp shows second
    }
}
char menu()
//this is the first menu with sign up, sign in and exit.
{
    int choice;
    char aChoice;
    printf("1.Sign up\n");
    printf("2.Sign in\n");
    printf("3.Exit\n");
    scanf("%d", &choice);
    system("cls");
    if(choice==1)
    {
        sign_up();
        exit(0);
    }
    if(choice==2)
    {
        exit(0);
    }
    if(choice==3)
    {
        //if user wants to exit, they have to press enter
        printf("\033[1;31m.Press the Enter to exit.");
        getch();
        exit(0);
    }
    else
    {
        printf("Wrong Number");
        exit(0);
    }
}
void main()
{
    //here is the first page, using color.
    printf("\033[1;34m[Welcome to the real estate company\]");
    printf("\n\n\033[1;36mClick the Enter to continue...");
    getchar();
    system("cls");
    menu();
}




