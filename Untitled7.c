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
                printf("\033[0;30m");
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

                    printf("\033[0;34m\nEnter the code one more time: ");
                    printf("\033[0;30m");
                    gets(signUpProfile.doubleCheckingCode);
                    printf("\033[0;34m");
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
        fputs(signUpProfile.userCode, signUP);
        fprintf(signUP,"\n");
        fputs(signUpProfile.doubleCheckingCode, signUP);
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
        // a and b referenced to inputed user name and password.
        printf("Complete the form to login\n");
        printf("User Name: ");
        scanf("%s", &a);
        printf("\nEnter your password: ");
        printf("\033[0;30m");
        scanf("%s", &b);
        printf("\033[0;34m");
        if (sign_in(a, b))
        {
            printf("\nLogin successful! welcome back, %s. \n", a);
            fputs(signUpProfile.userName, file);
            fprintf(file"\n");
            fputs(signUpProfile.doubleCheckingCode, file);
            fprintf(file"\n");
        }
        else
        {
            printf("\nInvalid user name or password, try again later.\n");
        }
        exit;
    }
    Sleep(5000);
    system("cls");
    //i use sleep and cls here to stop some seconds
    if(choice==3)
    {
        //if user wants to exit, they have to press enter
        printf("\033[1;31mPress the Enter to exit");
        getche();
        exit;
    }
}
struct cresidentialList
{
    char propertyType[30];
    int propertySize[20];
    int infrastructure[30];
    int bedRooms[10];
    int bathRooms[10];
    int priceRage[30];
    int floor[4];
    char adress[200];
    char neighbourhood[200];
    char district[40];
    char amenities[200];
    int receptionRoom[3];
    int serviceCharge[30];
}
cresidentialList;
char  ResidentialPropertyFunc()
{
    FILE *file;
    file=fopen("ResidentialPropertyList.txt","w");
    if(file==NULL)
    {
        printf("Error opening the file.");
        exit;
        //now we just opened the file of residential list.
    }
    printf("\033[0;34m");
    printf("%c%c%c%cComplete the form below%c%c%c%c\n\n", 219, 219, 219, 219, 219, 219);
    printf("\033[0;36m");
    printf("Property Type: ");
    gets(cresidentialList.propertyType);
    getchar();
    printf("\nProperty Size: ");
    gets(cresidentialList.propertySize);
    printf("\nInfrastructure: ");
    gets(cresidentialList.infrastructure);
    getchar();
    printf("\nBed Rooms: ");
    gets(cresidentialList.bedRooms);
    printf("\nBath Rooms: ");
    gets(cresidentialList.bathRooms);
    printf("\nPrice Rage: ");
    gets(cresidentialList.priceRage);
    printf("\nFloor: ");
    gets(cresidentialList.floor);
    printf("\nAdress: ");
    gets(cresidentialList.adress);
    printf("\nNeighbourhood: ");
    gets(cresidentialList.neighbourhood);
    printf("\nDistrict: ");
    gets(cresidentialList.district);
    printf("\nAmenities: ");
    gets(cresidentialList.amenities);
    printf("\nReception Room: ");
    gets(cresidentialList.receptionRoom);
    printf("\nService Charge: ");
    gets(cresidentialList.serviceCharge);
    //now we are going to save them in the file.
    printf("\033[0;32m");
    printf("\n Do you want to save these informations??");
    printf("1.Yes");
    printf("2.No");
    printf("\033[0;36m");
    system("cls");
    int fChoice;
    scanf("%d", &fChoice);
    if(fChoice==1)
    {
        fputs(cresidentialList.propertyType, file);
        fprintf(file,"\n");
        fputs(cresidentialList.propertySize, file);
        fprintf(file,"\n");
        fputs(cresidentialList.infrastructure, file);
        fprintf(file,"\n");
        fputs(cresidentialList.bedRooms, file);
        fprintf(file,"\n");
        fputs(cresidentialList.bathRooms, file);
        fprintf(file,"\n");
        fputs(cresidentialList.priceRage, file);
        fprintf(file,"\n");
        fputs(cresidentialList.floor, file);
        fprintf(file,"\n");
        fputs(cresidentialList.adress, file);
        fprintf(file,"\n");
        fputs(cresidentialList.neighbourhood, file);
        fprintf(file,"\n");
        fputs(cresidentialList.district, file);
        fprintf(file,"\n");
        fputs(cresidentialList.amenities, file);
        fprintf(file,"\n");
        fputs(cresidentialList.receptionRoom, file);
        fprintf(file,"\n");
        fputs(cresidentialList.serviceCharge, file);
        fprintf(file,"\n");
        printf("The Information Saved successfully, click enter to exit.");
        getchar();
    }
    else
    {
        system("cls");
        exit;
    }
}
char secondMenu()
{
    //this function is for second menu
    char choice, bChoice, cChoice;
    printf("Please enter a number and click the enter to continue.\n");
    printf("\033[0;36m");
    printf("1.Adding Data.\n");
    printf("2.Deleting Data.\n");
    printf("3.Reportage.\n");
    printf("4.Setting.\n");
    printf("5.Reportage.\n");
    printf("6.Exit.\n");
    scanf("%d", &choice);
    system("cls");
    if(choice==1)
    {
        printf("1.For sale.\n");
        printf("2.For rent.\n");
        printf("3.Exit.\n");
        scanf("%d", &bChoice);
        system("cls");
        if(bChoice==1)
        {
            printf("1.Residential property.\n");
            printf("2.Commercial property.\n");
            printf("3.Country land.\n");
            printf("4.Exit.\n");
            scanf("%d", &cChoice);
            system("cls");
            if(cChoice==1)
            {
                ResidentialPropertyFunc();
                exit;
            }
        }
    }
}
void main()
{
    //here is the first page, using color.
    printf("\033[0;34m");
    printf("%cWelcome to the real estate company%c", 185, 204);
    printf("\033[0;36m");
    printf("\n\n\n %cClick the Enter to continue...", 22472);
    getchar();
    system("cls");
    menu();
    secondMenu();
}










