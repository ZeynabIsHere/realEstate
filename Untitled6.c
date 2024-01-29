#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>
#include<conio.h>
#include<string.h>
#include<windows.h>
#include<time.h>
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
    struct signUpProfile *link;
} signUpProfile;
char sign_up()
//this is the menu for getting sign up profile
{
    int n, m, len, s, f;
    char fals, fl, cant, wrong;
    // fals and fl stands for false
    FILE *signUP;
    signUP=fopen("members_list.txt","a");
    if(signUP==NULL)
    {
        printf("Error opening the file.");
        exit(0);
    }
    printf("\033[1;34m[Complete the form below]\n\n");
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
    int checkInfo=0;
    while(checkInfo!=1)
    {
        int length=strlen(signUpProfile.phoneNumber);
        if(length!=11 && signUpProfile.phoneNumber[0]!='9')
            //checking length of array
        {
            printf("invalid phone number");
            break;
        }
        else
        {
            printf("\nEmail: ");
            gets(signUpProfile.Email);
            int atCounter=0, dotCounter=0, index, lastDotIndex;
            //cheking email for having . and @
            for(int i=0; signUpProfile.Email[i] !='\0'; i++)
            {
                //check for having @ but not at first
                if(signUpProfile.Email[i]=='@')
                {
                    index=i;
                    if(index==0)
                    {
                        printf("Invalid Email"); //first character cant be @
                        break;
                    }
                    atCounter++;
                    if(atCounter>1)
                    {
                        printf("Invalid Email");
                        break;
                    }
                }
                if(signUpProfile.Email[i]=='.')
                {
                    dotCounter++;
                    lastDotIndex=i;
                }
            }
            if((atCounter==1 && dotCounter>0)&&(lastDotIndex>index))
                //it was for checking at least '.' after @
            {
                printf("\nEnter your password(more than 8 character contain uppercase, lowercase and number): ");
                gets(signUpProfile.userCode);
                int length=0, upperCase=0, lowerCase=0, digit=0;
                length=strlen(signUpProfile.userCode);
                // the password should be at least 8 character, with lower case and upper case and number, so we consider that here.
                for(int i=0; i<length; i++)
                {
                    if(signUpProfile.userCode[i]>='A' && signUpProfile.userCode[i]<='Z')
                    {
                        upperCase=1;
                        //at least having 1 uppercase
                    }
                    else if(signUpProfile.userCode[i]>='a' && signUpProfile.userCode[i]<='z')
                    {
                        lowerCase=1;
                        //at least having 1 lower case
                    }
                    else if(signUpProfile.userCode[i]>='0' && signUpProfile.userCode[i]<='9')
                    {
                        digit=1;
                        //at least having 1 digit
                    }
                }
                if(length>=8 && upperCase==1 && lowerCase==1 && digit==1)
                {
                    printf("\nEnter the code one more time: ");
                    gets(signUpProfile.doubleCheckingCode);
                    int result=strcmp(signUpProfile.userCode, signUpProfile.doubleCheckingCode);
                    if(result!=0)
                    {
                        printf("Invalid Password");
                        break;
                    }
                }
                else
                {
                    printf("Invalid Password");
                    break;

                }
            }
            else
            {
                printf("Invalid Email");
                break;
            }
        }
        checkInfo=1;
    }
    struct signUpProfile *start, *temp, *end;
    start=malloc(sizeof(struct signUpProfile));
    temp=malloc(sizeof(struct signUpProfile));
    //start shows the first node so the temp shows second
    if(checkInfo==1)
        //this "if" helps for not saving all the info, it just let us save the right ones.
    {
        fputs(signUpProfile.userName, signUP);
        fprintf(signUP,"\n");
        fputs(signUpProfile.firstName, signUP);
        fprintf(signUP,"\n");
        fputs(signUpProfile.lastName, signUP);
        fprintf(signUP,"\n");
        fputs(signUpProfile.idNumber, signUP);
        fprintf(signUP,"\n");
        fputs(signUpProfile.phoneNumber, signUP);
        fprintf(signUP,"\n");
        fputs(signUpProfile.Email, signUP);
        fprintf(signUP,"\n");
        fputs(signUpProfile.userCode, signUP);
        fprintf(signUP,"\n");
        fputs(signUpProfile.doubleCheckingCode, signUP);
        fprintf(signUP,"\n");
        // i just save the infos on file
    }
}
int sign_in(char *logInUserName, char *logInPassword)
//this is the menu for sign in
{
    FILE *signIN;
    signIN=fopen("members_list.txt","r");
    if(signIN==NULL)
    {
        printf("Error opening the file.");
        exit;
    }
    while (fscanf(signIN, "%s %s", signUpProfile.userName, signUpProfile.doubleCheckingCode) != EOF)
    {
        if (strcmp(logInUserName, signUpProfile.userName) == 0 && strcmp(logInPassword, signUpProfile.doubleCheckingCode) == 0)
        {
            fclose(signIN);
            return 1;
        }
    }
    fclose(signIN);
    return 0;
}
char menu()
//this is the first menu with sign up, sign in and exit.
{
    int choice;
    char aChoice;
    printf("Please enter a number and click the enter to continue\n");
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
        char a[60], b[60];
        printf("Complete the form to login\n");
        printf("User Name: ");
        scanf("%s", &a);
        printf("\nEnter your password: ");
        scanf("%s", &b);
        if (sign_in(a, b))
        {
            printf("login successful! welcome back, %s. \n", a);
        }
        else
        {
            printf("Invalid username or password, try agan later.\n");
        }
        exit;


    }
    Sleep(5000);
    system("cls");
    //i use sleep and cls here to stop some seconds
    if(choice==3)
    {
        //if user wants to exit, they have to press enter
        printf("\033[1;31m.Press the Enter to exit.");
        getche();
        exit;
    }
    else
    {
        printf("Wrong Number");
        exit(0);
    }
}
char secondMenu()
{

}
void main()
{
    //here is the first page, using color.
    printf("\033[1;34m[Welcome to the real estate company\]");
    printf("\n\n\033[1;36mClick the Enter to continue...");
    getchar();
    system("cls");
    menu();
    secondMenu();
}









