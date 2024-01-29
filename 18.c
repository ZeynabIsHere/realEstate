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
    if(strlen(signUpProfile.idNumber)!=10)
    {
        printf("Invalid ID, the ID should contain 10 digit.");
        exit(0);
    }
    for(int l=0; l<10; l++)
    {
        if (!isdigit(signUpProfile.idNumber[l]))
        {
            printf("Invalid ID, the ID doesn't contain alphabet.");
            exit(0);
        }
    }
    printf("\nPhone Number: 98");
    gets(signUpProfile.phoneNumber);
    int checkInfo=0;
    while(checkInfo!=1)
    {
        int length=strlen(signUpProfile.phoneNumber);
        if(length!=10 && signUpProfile.phoneNumber[0]!='9')
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
            int i=0;
            char ch;
            if((atCounter==1 && dotCounter>0)&&(lastDotIndex>index))
                //it was for checking at least '.' after @
            {
                printf("\nEnter your password(more than 8 character contain uppercase, lowercase and number): ");
                // the while below just helps for security and turns every passwords that user gave to *
                while(1)
                {
                    ch=getch();
                    if(ch==13)
                        break;
                    printf("*");
                    signUpProfile.userCode[i]=ch;
                    i++;
                }
                signUpProfile.userCode[i]='\0';
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
                int i=0;
                char ch;
                if(length>=8 && upperCase==1 && lowerCase==1 && digit==1)
                {

                    printf("\nEnter the code one more time: \n");
                    while(1)
                    {
                        ch=getch();
                        if(ch==13)
                            break;
                        printf("*");
                        signUpProfile.doubleCheckingCode[i]=ch;
                        i++;
                    }
                    signUpProfile.doubleCheckingCode[i]='\0';
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
void delay(int seconds)
{
    int milli_seconds=1000*seconds;
    clock_t start_time=clock();
    while(clock()<start_time+milli_seconds);
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
        char a[60], b[60], ch;
        int j=0;
        // a and b referenced to inputed user name and password.
        printf("Complete the form to login\n");
        printf("User Name: ");
        scanf("%s", &a);
        printf("\nEnter your password: ");
        while(1)
        {
            ch=getch();
            if(ch==13)
                break;
            printf("*");
            b[j]=ch;
            j++;
        }
        b[j]='\0';
        int access=0;
        //this access helps for giving access to the person who has right information.
        if (sign_in(a, b))
        {
            printf("\nLogin successful! welcome back, %s. \n", a);
            access=1;
        }
        else
        {
            printf("\nInvalid user name or password, try again later.\n");
            exit(0);
        }
    }
    for(int i=7; i>0; i--)
    {
        printf("%d  ", i);
        delay(1);
    }
    //here it counts 7 to 0, then goes to another page
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
struct countrylandList
{
    char fn[60]; //its for customer's first name
    char ln[60];  //its for customer's last name
    char fan[60]; //its for customer's father name
    char mon[60]; //its for customer's mother name
    char idn[60]; //its for customer's id number
    char phn[60]; //its for customer's phone number
    char propertyType[30]; //type of estate, for example residential, commercial, raw land, industrial or special purpose
    char propertySize[20]; //foot or square feet
    char infrastructure[30]; //the basic facilities and system serving a country, region, or community. (persian=zir bana)
    char rooms[10];
    char bathRooms[10];
    char priceRage[30]; //the price
    char adress[200];
    char neighbourhood[200]; //river, village and..
    char district[40]; //an area of a country or city, especially one characterized by a particular feature or activity. (persian=mantaqe)
    char amenities[200]; //a desirable or useful feature or facility of a building or place. (persian= tashilat vasile refahi)
    char harvest[3]; //tree, fruits
    char serviceCharge[30]; //a charge made for maintenance on a property which has been leased. (persian= service hazine khadamat, karmozd, anam)
    int validation; // this is for checking if its valid or not.
    struct countrylandList *link;
} countrylandList;
typedef struct countrylandList bNode;
bNode* readCountryLandFromFile(char* CountryLandPropertyList)
//this action actually does read the file and create one linked list, to save the informations, it makes one or many nodes and returns propertyNodes
{
    FILE *file=fopen("CountryLandPropertyList.txt", "r");
    if (file==NULL)
    {
        printf("Error opening file\n");
        return NULL;
    }

    bNode *head=NULL;
    bNode *current=NULL;

    while(!feof(file))
    {
        bNode *newNode=(bNode*)malloc(sizeof(bNode));
        //here, it just scan everything in the file and \n is here to help going to next line
        if(fscanf(file, "%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n", newNode->fn, newNode->ln, newNode->fan, newNode->mon, newNode->idn, newNode->phn, newNode->propertyType, newNode->propertySize, newNode->infrastructure, newNode->rooms, newNode->bathRooms, newNode->priceRage, newNode->adress, newNode->neighbourhood, newNode->district, newNode->amenities, newNode->harvest, newNode->serviceCharge,newNode->validation) != 19)
        {
            free(newNode);
            continue;
        }
        newNode->link=NULL;

        if(head==NULL)
        {
            head=newNode;
            current=newNode;
        }
        else
        {
            current->link=newNode;
            current=newNode;
        }
    }

    fclose(file);
    return head;
}
void showPropertiesUnderPriceCou(struct countrylandList *head, char *maxPriceCou)
//in this function we just can report the lists that they are under the max price(which the user gave us)
{
    struct countrylandList *current;
    current=head;
    while(current!=NULL)
    {
        if(strcmp(current->priceRage, maxPriceCou)<0)
            //i get the user price string and compare it to the prices in the file, then show the under prices.
        {
            printf("\nFirst Name:%s\nLast Name:%s\nFather Name:%s\nMother Name:%s\nID Number:%s\nPhone Number:%s\nProperty Type:%s\nProperty Size:%s\nInfrastructure:%s\nRooms:%s\nBath Room:%s\nPrice Rage:%s\nAdress:%s\nNeighbourhood:%s\nDistrict:%s\nAmenities:%s\nHarvest:%s\nService Charge:%s\n", current->fn, current->ln, current->fan, current->mon, current->idn, current->phn, current->propertyType, current->propertySize, current->infrastructure, current->rooms, current->bathRooms, current->priceRage, current->adress, current->neighbourhood, current->district, current->amenities, current->harvest, current->serviceCharge,current->validation);
            printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 220, 220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220);
        }
        current=current->link;
    }
}
void showPropertiesInfrastructureCheckCou(struct countrylandList *head, char *infrastructureCheckCou)
//this function is for infrastructures that they are under the one which user gave us.
{
    struct countrylandList *current;
    current=head;
    while(current!=NULL)
    {
        if(strcmp(current->infrastructure,infrastructureCheckCou)<0)
            // it compares between users price and the prices in the file.
        {
           printf("\nFirst Name:%s\nLast Name:%s\nFather Name:%s\nMother Name:%s\nID Number:%s\nPhone Number:%s\nProperty Type:%s\nProperty Size:%s\nInfrastructure:%s\nRooms:%s\nBath Room:%s\nPrice Rage:%s\nAdress:%s\nNeighbourhood:%s\nDistrict:%s\nAmenities:%s\nHarvest:%s\nService Charge:%s\n", current->fn, current->ln, current->fan, current->mon, current->idn, current->phn, current->propertyType, current->propertySize, current->infrastructure, current->rooms, current->bathRooms, current->priceRage, current->adress, current->neighbourhood, current->district, current->amenities, current->harvest, current->serviceCharge,current->validation);
            printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 220, 220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220);
        }
        current=current->link;
    }
}
void showPropertiesDistrictCheckCou(struct countrylandList *head, char *districtCheckCou)
//this function is for checking district
{
    struct countrylandList *current;
    current=head;
    while(current!=NULL)
    {
        if(strcmp(current->district, districtCheckCou) < 0)
            //if the users district equals district in file, it shows.
        {
           printf("\nFirst Name:%s\nLast Name:%s\nFather Name:%s\nMother Name:%s\nID Number:%s\nPhone Number:%s\nProperty Type:%s\nProperty Size:%s\nInfrastructure:%s\nRooms:%s\nBath Room:%s\nPrice Rage:%s\nAdress:%s\nNeighbourhood:%s\nDistrict:%s\nAmenities:%s\nHarvest:%s\nService Charge:%s\n", current->fn, current->ln, current->fan, current->mon, current->idn, current->phn, current->propertyType, current->propertySize, current->infrastructure, current->rooms, current->bathRooms, current->priceRage, current->adress, current->neighbourhood, current->district, current->amenities, current->harvest, current->serviceCharge,current->validation);
            printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 220, 220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220);
        }
        current=current->link;
    }
}
void showPropertiesHarvestCheck(struct countrylandList *head, char *harvestCheck)
//this function is for harvest
{
    struct countrylandList *current;
    current=head;
    while(current!=NULL)
    {
        if(strstr(current->harvest,harvestCheck)==0)
            //if the users harvest equals harvest in file, it shows.
        {
           printf("\nFirst Name:%s\nLast Name:%s\nFather Name:%s\nMother Name:%s\nID Number:%s\nPhone Number:%s\nProperty Type:%s\nProperty Size:%s\nInfrastructure:%s\nRooms:%s\nBath Room:%s\nPrice Rage:%s\nAdress:%s\nNeighbourhood:%s\nDistrict:%s\nAmenities:%s\nHarvest:%s\nService Charge:%s\n", current->fn, current->ln, current->fan, current->mon, current->idn, current->phn, current->propertyType, current->propertySize, current->infrastructure, current->rooms, current->bathRooms, current->priceRage, current->adress, current->neighbourhood, current->district, current->amenities, current->harvest, current->serviceCharge,current->validation);
            printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 220, 220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220);
        }
        current=current->link;
    }
}
char CountryLandProperty()
{
    FILE *file;
    file=fopen("CountryLandPropertyList.txt","a");
    if(file==NULL)
    {
        printf("Error opening the file.");
        exit;
        //now we just opened the file of country land list.
    }
    printf("\033[0;34m");
    printf("%c%c%c%cCustomers Information%c%c%c%c\n\n", 219, 219, 219, 219, 219, 219, 219, 219);
    printf("\033[0;36m");
    getchar();
    printf("First name: ");
    gets(countrylandList.fn);
    printf("\nLast name: ");
    gets(countrylandList.ln);
    printf("\nFather's name: ");
    gets(countrylandList.fan);
    printf("\nMother's name: ");
    gets(countrylandList.mon);
    printf("\nID number: ");
    gets(countrylandList.idn);
    printf("\nPhone number: ");
    gets(countrylandList.phn);
    printf("\033[0;34m");
    printf("\n%c%c%c%cCountry Land INFO%c%c%c%c\n\n", 219, 219, 219, 219, 219, 219, 219, 219);
    printf("\033[0;36m");
    printf("Property Type: ");
    gets(countrylandList.propertyType);
    printf("\nProperty Size: ");
    gets(countrylandList.propertySize);
    printf("\nInfrastructure: ");
    gets(countrylandList.infrastructure);
    printf("\nRooms: ");
    gets(countrylandList.rooms);
    printf("\nBath Rooms: ");
    gets(countrylandList.bathRooms);
    printf("\nPrice Rage: ");
    gets(countrylandList.priceRage);
    printf("\nFloor: ");
    gets(countrylandList.adress);
    printf("\nNeighbourhood: ");
    gets(countrylandList.neighbourhood);
    printf("\nDistrict: ");
    gets(countrylandList.district);
    printf("\nAmenities: ");
    gets(countrylandList.amenities);
    printf("\nHarvest: ");
    gets(countrylandList.harvest);
    printf("\nService Charge: ");
    gets(countrylandList.serviceCharge);
    int val;
    printf("\nIs this file valid??: \n1.Yes.\n2.No.\n");
    gets(countrylandList.validation);
    val=atoi(countrylandList.validation);
    //now we are going to save them in the file.
    printf("\033[0;32m");
    printf("\n Do you want to save these informations??");
    printf("\033[0;36m");
    printf("\n1.Yes");
    printf("\n2.No\n");
    //getchar();
    int fChoice;
    scanf("%d", &fChoice);
    if(fChoice==1)
    {
        fputs(countrylandList.fn, file);
        fprintf(file,"\n");
        fputs(countrylandList.ln, file);
        fprintf(file,"\n");
        fputs(countrylandList.fan, file);
        fprintf(file,"\n");
        fputs(countrylandList.mon, file);
        fprintf(file,"\n");
        fputs(countrylandList.idn, file);
        fprintf(file,"\n");
        fputs(countrylandList.phn, file);
        fprintf(file,"\n");
        fputs(countrylandList.propertyType, file);
        fprintf(file,"\n");
        fputs(countrylandList.propertySize, file);
        fprintf(file,"\n");
        fputs(countrylandList.infrastructure, file);
        fprintf(file,"\n");
        fputs(countrylandList.rooms, file);
        fprintf(file,"\n");
        fputs(countrylandList.bathRooms, file);
        fprintf(file,"\n");
        fputs(countrylandList.priceRage, file);
        fprintf(file,"\n");
        fputs(countrylandList.adress, file);
        fprintf(file,"\n");
        fputs(countrylandList.neighbourhood, file);
        fprintf(file,"\n");
        fputs(countrylandList.district, file);
        fprintf(file,"\n");
        fputs(countrylandList.amenities, file);
        fprintf(file,"\n");
        fputs(countrylandList.harvest, file);
        fprintf(file,"\n");
        fputs(countrylandList.serviceCharge, file);
        fprintf(file,"\n");
        fputs(val, file);
        fprintf(file,"\n");
        printf("The Information Saved successfully, click enter to exit.");
        getchar();
    }
    else
    {
        system("cls");
        exit;
    }
    system("cls");
}
struct commercialList
{
    char fn[60]; //its for customer's first name
    char ln[60];  //its for customer's last name
    char fan[60]; //its for customer's father name
    char mon[60]; //its for customer's mother name
    char idn[60]; //its for customer's id number
    char phn[60]; //its for customer's phone number
    char propertyType[30]; //type of estate, for example residential, commercial, raw land, industrial or special purpose
    char propertySize[20]; //foot or square feet
    char infrastructure[30]; //the basic facilities and system serving a country, region, or community. (persian=zir bana)
    char rooms[10];
    char bathRooms[10];
    char priceRage[30]; //the price
    char floor[4];
    char adress[200];
    char neighbourhood[200];
    char district[40]; //an area of a country or city, especially one characterized by a particular feature or activity. (persian=mantaqe)
    char amenities[200]; //a desirable or useful feature or facility of a building or place. (persian= tashilat vasile refahi)
    char receptionRoom[3]; //a room in a private house suitable for entertaining visitors. (persian=otaq paziraii)
    char serviceCharge[30]; //a charge made for maintenance on a property which has been leased. (persian= service hazine khadamat, karmozd, anam)
    char shops[4]; //it means how many shops does it have
    char validation[10]; // this is for checking if its valid or not.
    struct commercialList *link;
} commercialList;
typedef struct commercialList PropertyNode;
PropertyNode* readCommercialListFromFile(char* CommercialPropertyList)
//this action actually does read the file and create one linked list, to save the informations, it makes one or many nodes and returns propertyNodes
{
    FILE *file=fopen("CommercialPropertyList.txt", "r");
    if (file==NULL)
    {
        printf("Error opening file\n");
        return NULL;
    }

    PropertyNode *head=NULL;
    PropertyNode *current=NULL;

    while(!feof(file))
    {
        PropertyNode *newNode=(PropertyNode*)malloc(sizeof(PropertyNode));
        //here, it just scan everything in the file and \n is here to help going to next line
        if(fscanf(file, "%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n", newNode->fn, newNode->ln, newNode->fan, newNode->mon, newNode->idn, newNode->phn, newNode->propertyType, newNode->propertySize, newNode->infrastructure, newNode->rooms, newNode->bathRooms, newNode->priceRage, newNode->floor, newNode->adress, newNode->neighbourhood, newNode->district, newNode->amenities, newNode->receptionRoom, newNode->serviceCharge,newNode->shops, newNode->validation) != 21)
        {
            free(newNode);
            continue;
        }
        newNode->link=NULL;

        if(head==NULL)
        {
            head=newNode;
            current=newNode;
        }
        else
        {
            current->link=newNode;
            current=newNode;
        }
    }

    fclose(file);
    return head;
}
void showPropertiesUnderPriceCom(struct commercialList *head, char *maxPriceCom)
//in this function we just can report the lists that they are under the max price(which the user gave us)
{
    struct commercialList *current;
    current=head;
    while(current!=NULL)
    {
        if(strcmp(current->priceRage, maxPriceCom)<0)
            //i get the user price string and compare it to the prices in the file, then show the under prices.
        {
            printf("\nFirst Name:%s\nLast Name:%s\nFather Name:%s\nMother Name:%s\nID Number:%s\nPhone Number:%s\nProperty Type:%s\nProperty Size:%s\nInfrastructure:%s\nBedroom:%s\nBath Room:%s\nPrice Rage:%s\nFloor:%s\nAdress:%s\nNeighbourhood:%s\nDistrict:%s\nAmenities:%s\nReception Room:%s\nService Charge:%s\n", current->fn, current->ln, current->fan, current->mon, current->idn, current->phn, current->propertyType, current->propertySize, current->infrastructure, current->rooms, current->bathRooms, current->priceRage, current->floor, current->adress, current->neighbourhood, current->district, current->amenities, current->receptionRoom, current->serviceCharge,current->shops, current->validation);
            printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 220, 220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220);
        }
        current=current->link;
    }
}
void showPropertiesInfrastructureCheckCom(struct commercialList *head, char *infrastructureCheckCom)
//this function is for infrastructures that they are under the one which user gave us.
{
    struct commercialList *current;
    current=head;
    while(current!=NULL)
    {
        if(strcmp(current->infrastructure,infrastructureCheckCom)<0)
            // it compares between users price and the prices in the file.
        {
            printf("\nFirst Name:%s\nLast Name:%s\nFather Name:%s\nMother Name:%s\nID Number:%s\nPhone Number:%s\nProperty Type:%s\nProperty Size:%s\nInfrastructure:%s\nBedroom:%s\nBath Room:%s\nPrice Rage:%s\nFloor:%s\nAdress:%s\nNeighbourhood:%s\nDistrict:%s\nAmenities:%s\nReception Room:%s\nService Charge:%s\n", current->fn, current->ln, current->fan, current->mon, current->idn, current->phn, current->propertyType, current->propertySize, current->infrastructure, current->rooms, current->bathRooms, current->priceRage, current->floor, current->adress, current->neighbourhood, current->district, current->amenities, current->receptionRoom, current->serviceCharge,current->shops, current->validation);
            printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 220, 220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220);
        }
        current=current->link;
    }
}
void showPropertiesDistrictCheckCom(struct commercialList *head, char *districtCheckCom)
//this function is for checking district
{
    struct commercialList *current;
    current=head;
    while(current!=NULL)
    {
        if(strcmp(current->district, districtCheckCom) < 0)
            //if the users district equals district in file, it shows.
        {
            printf("\nFirst Name:%s\nLast Name:%s\nFather Name:%s\nMother Name:%s\nID Number:%s\nPhone Number:%s\nProperty Type:%s\nProperty Size:%s\nInfrastructure:%s\nBedroom:%s\nBath Room:%s\nPrice Rage:%s\nFloor:%s\nAdress:%s\nNeighbourhood:%s\nDistrict:%s\nAmenities:%s\nReception Room:%s\nService Charge:%s\n", current->fn, current->ln, current->fan, current->mon, current->idn, current->phn, current->propertyType, current->propertySize, current->infrastructure, current->rooms, current->bathRooms, current->priceRage, current->floor, current->adress, current->neighbourhood, current->district, current->amenities, current->receptionRoom, current->serviceCharge,current->shops, current->validation);
            printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 220, 220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220);
        }
        current=current->link;
    }
}
void showPropertiesShopCheck(struct commercialList *head, char *shopCheck)
//this function is for number of the bed rooms
{
    struct commercialList *current;
    current=head;
    while(current!=NULL)
    {
        if(strcmp(current->shops,shopCheck)<0)
            //if the users bedrooms equals bedrooms in file, it shows.
        {
            printf("\nFirst Name:%s\nLast Name:%s\nFather Name:%s\nMother Name:%s\nID Number:%s\nPhone Number:%s\nProperty Type:%s\nProperty Size:%s\nInfrastructure:%s\nBedroom:%s\nBath Room:%s\nPrice Rage:%s\nFloor:%s\nAdress:%s\nNeighbourhood:%s\nDistrict:%s\nAmenities:%s\nReception Room:%s\nService Charge:%s\n", current->fn, current->ln, current->fan, current->mon, current->idn, current->phn, current->propertyType, current->propertySize, current->infrastructure, current->rooms, current->bathRooms, current->priceRage, current->floor, current->adress, current->neighbourhood, current->district, current->amenities, current->receptionRoom, current->serviceCharge,current->shops, current->validation);
            printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 220, 220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220);
        }
        current=current->link;
    }
}
void showPropertiesFloorCheckCom(struct commercialList *head, char *floorCheckCom)
//this function is for number of the floors
{
    struct commercialList *current;
    current=head;
    while(current!=NULL)
    {
        if(strcmp(current->floor,floorCheckCom)<0)
            //if the users floor equals floor in file, it shows.
        {
            printf("\nFirst Name:%s\nLast Name:%s\nFather Name:%s\nMother Name:%s\nID Number:%s\nPhone Number:%s\nProperty Type:%s\nProperty Size:%s\nInfrastructure:%s\nBedroom:%s\nBath Room:%s\nPrice Rage:%s\nFloor:%s\nAdress:%s\nNeighbourhood:%s\nDistrict:%s\nAmenities:%s\nReception Room:%s\nService Charge:%s\n", current->fn, current->ln, current->fan, current->mon, current->idn, current->phn, current->propertyType, current->propertySize, current->infrastructure, current->rooms, current->bathRooms, current->priceRage, current->floor, current->adress, current->neighbourhood, current->district, current->amenities, current->receptionRoom, current->serviceCharge,current->shops, current->validation);
            printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 220, 220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220);
        }
        current=current->link;
    }
}
char CommercialPropertyFunc()
{
    FILE *file;
    file=fopen("CommercialPropertyList.txt","a");
    if(file==NULL)
    {
        printf("Error opening the file.");
        exit;
        //now we just opened the file of commercial list.
    }
    printf("\033[0;34m");
    printf("%c%c%c%cCustomers Information%c%c%c%c\n\n", 219, 219, 219, 219, 219, 219, 219, 219);
    printf("\033[0;36m");
    getchar();
    printf("First name: ");
    gets(commercialList.fn);
    printf("\nLast name: ");
    gets(commercialList.ln);
    printf("\nFather's name: ");
    gets(commercialList.fan);
    printf("\nMother's name: ");
    gets(commercialList.mon);
    printf("\nID number: ");
    gets(commercialList.idn);
    printf("\nPhone number: ");
    gets(commercialList.phn);
    printf("\033[0;34m");
    printf("\n%c%c%c%cCommercial Property INFO%c%c%c%c\n\n", 219, 219, 219, 219, 219, 219, 219, 219);
    printf("\033[0;36m");
    printf("Property Type: ");
    gets(commercialList.propertyType);
    printf("\nProperty Size: ");
    gets(commercialList.propertySize);
    printf("\nInfrastructure: ");
    gets(commercialList.infrastructure);
    printf("\nRooms: ");
    gets(commercialList.rooms);
    printf("\nBath Rooms: ");
    gets(commercialList.bathRooms);
    printf("\nPrice Rage: ");
    gets(commercialList.priceRage);
    printf("\nFloor: ");
    gets(commercialList.floor);
    printf("\nAdress: ");
    gets(commercialList.adress);
    printf("\nNeighbourhood: ");
    gets(commercialList.neighbourhood);
    printf("\nDistrict: ");
    gets(commercialList.district);
    printf("\nAmenities: ");
    gets(commercialList.amenities);
    printf("\nReception Room: ");
    gets(commercialList.receptionRoom);
    printf("\nService Charge: ");
    gets(commercialList.serviceCharge);
    printf("\nShops: ");
    gets(commercialList.shops);
    //now we are going to save them in the file.
    printf("\033[0;32m");
    printf("\n Do you want to save these informations??");
    printf("\033[0;36m");
    printf("\n1.Yes");
    printf("\n2.No\n");
    //getchar();
    int fChoice;
    scanf("%d", &fChoice);
    if(fChoice==1)
    {
        fputs(commercialList.fn, file);
        fprintf(file,"\n");
        fputs(commercialList.ln, file);
        fprintf(file,"\n");
        fputs(commercialList.fan, file);
        fprintf(file,"\n");
        fputs(commercialList.mon, file);
        fprintf(file,"\n");
        fputs(commercialList.idn, file);
        fprintf(file,"\n");
        fputs(commercialList.phn, file);
        fprintf(file,"\n");
        fputs(commercialList.propertyType, file);
        fprintf(file,"\n");
        fputs(commercialList.propertySize, file);
        fprintf(file,"\n");
        fputs(commercialList.infrastructure, file);
        fprintf(file,"\n");
        fputs(commercialList.rooms, file);
        fprintf(file,"\n");
        fputs(commercialList.bathRooms, file);
        fprintf(file,"\n");
        fputs(commercialList.priceRage, file);
        fprintf(file,"\n");
        fputs(commercialList.floor, file);
        fprintf(file,"\n");
        fputs(commercialList.adress, file);
        fprintf(file,"\n");
        fputs(commercialList.neighbourhood, file);
        fprintf(file,"\n");
        fputs(commercialList.district, file);
        fprintf(file,"\n");
        fputs(commercialList.amenities, file);
        fprintf(file,"\n");
        fputs(commercialList.receptionRoom, file);
        fprintf(file,"\n");
        fputs(commercialList.serviceCharge, file);
        fprintf(file,"\n");
        fputs(commercialList.shops, file);
        fprintf(file,"\n");
        printf("The Information Saved successfully, click enter to exit.");
        getchar();
    }
    else
    {
        system("cls");
        exit;
    }
    system("cls");
}
struct cresidentialList
{
    char fn[60]; //its for customer's first name
    char ln[60];  //its for customer's last name
    char fan[60]; //its for customer's father name
    char mon[60]; //its for customer's mother name
    char idn[60]; //its for customer's id number
    char phn[60]; //its for customer's phone number
    char propertyType[30]; //type of estate, for example residential, commercial, raw land, industrial or special purpose
    char propertySize[20]; //foot or square feet
    char infrastructure[30]; //the basic facilities and system serving a country, region, or community. (persian=zir bana)
    char bedRooms[10];
    char bathRooms[10];
    char priceRage[30]; //the price
    char floor[4];
    char adress[200];
    char neighbourhood[200];
    char district[40]; //an area of a country or city, especially one characterized by a particular feature or activity. (persian=mantaqe)
    char amenities[200]; //a desirable or useful feature or facility of a building or place. (persian= tashilat vasile refahi)
    char receptionRoom[3]; //a room in a private house suitable for entertaining visitors. (persian=otaq paziraii)
    char serviceCharge[30]; //a charge made for maintenance on a property which has been leased. (persian= service hazine khadamat, karmozd, anam)
    char validation[10]; // this is for checking if its valid or not.
    struct cresidentialList *link;
} cresidentialList;
typedef struct cresidentialList aNode;
aNode* readResidentialListFromFile(char* ResidentialPropertyList)
//this action actually does read the file and create one linked list, to save the informations, it makes one or many nodes and returns propertyNodes
{
    FILE *file=fopen("ResidentialPropertyList.txt", "r");
    if (file==NULL)
    {
        printf("Error opening file\n");
        return NULL;
    }

    aNode *head=NULL;
    aNode *current=NULL;

    while(!feof(file))
    {
        aNode *newNode=(aNode*)malloc(sizeof(aNode));
        //here, it just scan everything in the file and \n is here to help going to next line
        if(fscanf(file, "%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n", newNode->fn, newNode->ln, newNode->fan, newNode->mon, newNode->idn, newNode->phn, newNode->propertyType, newNode->propertySize, newNode->infrastructure, newNode->bedRooms, newNode->bathRooms, newNode->priceRage, newNode->floor, newNode->adress, newNode->neighbourhood, newNode->district, newNode->amenities, newNode->receptionRoom, newNode->serviceCharge, newNode->validation) != 20)
        {
            free(newNode);
            continue;
        }
        newNode->link=NULL;

        if(head==NULL)
        {
            head=newNode;
            current=newNode;
        }
        else
        {
            current->link=newNode;
            current=newNode;
        }
    }

    fclose(file);
    return head;
}
void showPropertiesUnderPrice(struct cresidentialList *head, char *maxPrice)
//in this function we just can report the lists that they are under the max price(which the user gave us)
{
    struct cresidentialList *current;
    current=head;
    while(current!=NULL)
    {
        if(strcmp(current->priceRage, maxPrice)<0)
            //i get the user price string and compare it to the prices in the file, then show the under prices.
        {
            printf("\nFirst Name:%s\nLast Name:%s\nFather Name:%s\nMother Name:%s\nID Number:%s\nPhone Number:%s\nProperty Type:%s\nProperty Size:%s\nInfrastructure:%s\nBedroom:%s\nBath Room:%s\nPrice Rage:%s\nFloor:%s\nAdress:%s\nNeighbourhood:%s\nDistrict:%s\nAmenities:%s\nReception Room:%s\nService Charge:%s\n", current->fn, current->ln, current->fan, current->mon, current->idn, current->phn, current->propertyType, current->propertySize, current->infrastructure, current->bedRooms, current->bathRooms, current->priceRage, current->floor, current->adress, current->neighbourhood, current->district, current->amenities, current->receptionRoom, current->serviceCharge);
            printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 220, 220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220);
        }
        current=current->link;
    }
}
void showPropertiesInfrastructureCheck(struct cresidentialList *head, char *infrastructureCheck)
//this function is for infrastructures that they are under the one which user gave us.
{
    struct cresidentialList *current;
    current=head;
    while(current!=NULL)
    {
        if(strcmp(current->infrastructure,infrastructureCheck)<0)
            // it compares between users price and the prices in the file.
        {
            printf("First Name:%s\nLast Name:%s\nFather Name:%s\nMother Name:%s\nID Number:%s\nPhone Number:%s\nProperty Type:%s\nProperty Size:%s\nInfrastructure:%s\nBedroom:%s\nBath Room:%s\nPrice Rage:%s\nFloor:%s\nAdress:%s\nNeighbourhood:%s\nDistrict:%s\nAmenities:%s\nReception Room:%s\nService Charge:%s\n", current->fn, current->ln, current->fan, current->mon, current->idn, current->phn, current->propertyType, current->propertySize, current->infrastructure, current->bedRooms, current->bathRooms, current->priceRage, current->floor, current->adress, current->neighbourhood, current->district, current->amenities, current->receptionRoom, current->serviceCharge, current->validation);
            printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 220, 220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220);
        }
        current=current->link;
    }
}
void showPropertiesDistrictCheck(struct cresidentialList *head, char *districtCheck)
//this function is for checking district
{
    struct cresidentialList *current;
    current=head;
    while(current!=NULL)
    {
        if(strcmp(current->district, districtCheck) < 0)
            //if the users district equals district in file, it shows.
        {
            printf("First Name:%s\nLast Name:%s\nFather Name:%s\nMother Name:%s\nID Number:%s\nPhone Number:%s\nProperty Type:%s\nProperty Size:%s\nInfrastructure:%s\nBedroom:%s\nBath Room:%s\nPrice Rage:%s\nFloor:%s\nAdress:%s\nNeighbourhood:%s\nDistrict:%s\nAmenities:%s\nReception Room:%s\nService Charge:%s\n", current->fn, current->ln, current->fan, current->mon, current->idn, current->phn, current->propertyType, current->propertySize, current->infrastructure, current->bedRooms, current->bathRooms, current->priceRage, current->floor, current->adress, current->neighbourhood, current->district, current->amenities, current->receptionRoom, current->serviceCharge, current->validation);
            printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 220, 220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220);
        }
        current=current->link;
    }
}
void showPropertiesBedroomCheck(struct cresidentialList *head, char *bedroomCheck)
//this function is for number of the bed rooms
{
    struct cresidentialList *current;
    current=head;
    while(current!=NULL)
    {
        if(strcmp(current->bedRooms,bedroomCheck)<0)
            //if the users bedrooms equals bedrooms in file, it shows.
        {
            printf("First Name:%s\nLast Name:%s\nFather Name:%s\nMother Name:%s\nID Number:%s\nPhone Number:%s\nProperty Type:%s\nProperty Size:%s\nInfrastructure:%s\nBedroom:%s\nBath Room:%s\nPrice Rage:%s\nFloor:%s\nAdress:%s\nNeighbourhood:%s\nDistrict:%s\nAmenities:%s\nReception Room:%s\nService Charge:%s\n", current->fn, current->ln, current->fan, current->mon, current->idn, current->phn, current->propertyType, current->propertySize, current->infrastructure, current->bedRooms, current->bathRooms, current->priceRage, current->floor, current->adress, current->neighbourhood, current->district, current->amenities, current->receptionRoom, current->serviceCharge, current->validation);
            printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 220, 220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220);
        }
        current=current->link;
    }
}
void showPropertiesFloorCheck(struct cresidentialList *head, char *floorCheck)
//this function is for number of the floors
{
    struct cresidentialList *current;
    current=head;
    while(current!=NULL)
    {
        if(strcmp(current->floor,floorCheck)<0)
            //if the users floor equals floor in file, it shows.
        {
            printf("First Name:%s\nLast Name:%s\nFather Name:%s\nMother Name:%s\nID Number:%s\nPhone Number:%s\nProperty Type:%s\nProperty Size:%s\nInfrastructure:%s\nBedroom:%s\nBath Room:%s\nPrice Rage:%s\nFloor:%s\nAdress:%s\nNeighbourhood:%s\nDistrict:%s\nAmenities:%s\nReception Room:%s\nService Charge:%s\n", current->fn, current->ln, current->fan, current->mon, current->idn, current->phn, current->propertyType, current->propertySize, current->infrastructure, current->bedRooms, current->bathRooms, current->priceRage, current->floor, current->adress, current->neighbourhood, current->district, current->amenities, current->receptionRoom, current->serviceCharge, current->validation);
            printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 220, 220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220);
        }
        current=current->link;
    }
}
char  ResidentialPropertyFunc()
{
    FILE *file;
    file=fopen("ResidentialPropertyList.txt","a");
    if(file==NULL)
    {
        printf("Error opening the file.");
        exit;
        //now we just opened the file of residential list.
    }
    printf("\033[0;34m");
    printf("%c%c%c%cCustomers Information%c%c%c%c\n\n", 219, 219, 219, 219, 219, 219, 219, 219);
    printf("\033[0;36m");
    getchar();
    printf("First name: ");
    gets(cresidentialList.fn);
    printf("\nLast name: ");
    gets(cresidentialList.ln);
    printf("\nFather's name: ");
    gets(cresidentialList.fan);
    printf("\nMother's name: ");
    gets(cresidentialList.mon);
    printf("\nID number: ");
    gets(cresidentialList.idn);
    printf("\nPhone number: ");
    gets(cresidentialList.phn);
    printf("\033[0;34m");
    printf("\n%c%c%c%cResidential Property INFO%c%c%c%c\n\n", 219, 219, 219, 219, 219, 219, 219, 219);
    printf("\033[0;36m");
    printf("Property Type: ");
    gets(cresidentialList.propertyType);
    printf("\nProperty Size: ");
    gets(cresidentialList.propertySize);
    printf("\nInfrastructure: ");
    gets(cresidentialList.infrastructure);
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
    printf("\033[0;36m");
    printf("\n1.Yes");
    printf("\n2.No\n");
    int fChoice;
    scanf("%d", &fChoice);
    if(fChoice==1)
    {
        fputs(cresidentialList.fn, file);
        fprintf(file,"\n");
        fputs(cresidentialList.ln, file);
        fprintf(file,"\n");
        fputs(cresidentialList.fan, file);
        fprintf(file,"\n");
        fputs(cresidentialList.mon, file);
        fprintf(file,"\n");
        fputs(cresidentialList.idn, file);
        fprintf(file,"\n");
        fputs(cresidentialList.phn, file);
        fprintf(file,"\n");
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
    system("cls");
}
struct residentialListRent
//this structure is made for residential property for rent.
{
    char fn[60]; //its for customer's first name
    char ln[60];  //its for customer's last name
    char fan[60]; //its for customer's father name
    char mon[60]; //its for customer's mother name
    char idn[60]; //its for customer's id number
    char phn[60]; //its for customer's phone number
    char propertyType[30]; //type of estate, for example residential, commercial, raw land, industrial or special purpose
    char propertySize[20]; //foot or square feet
    char infrastructure[30]; //the basic facilities and system serving a country, region, or community. (persian=zir bana)
    char bedRooms[10];
    char bathRooms[10];
    char priceRage[30]; //the price
    char floor[4];
    char adress[200];
    char neighbourhood[200];
    char district[40]; //an area of a country or city, especially one characterized by a particular feature or activity. (persian=mantaqe)
    char amenities[200]; //a desirable or useful feature or facility of a building or place. (persian= tashilat vasile refahi)
    char receptionRoom[3]; //a room in a private house suitable for entertaining visitors. (persian=otaq paziraii)
    char serviceCharge[30]; //a charge made for maintenance on a property which has been leased. (persian= service hazine khadamat, karmozd, anam)
    char validation[10]; // this is for checking if its valid or not.
    struct residentialListRent *link;
} residentialListRent;
char  ResidentialPropertyFuncRent()
{
    FILE *file;
    file=fopen("ResidentialPropertyListForRent.txt","a");
    if(file==NULL)
    {
        printf("Error opening the file.");
        exit;
        //now we just opened the file of residential list for rent.
    }
    printf("\033[0;34m");
    printf("%c%c%c%cCustomers Information%c%c%c%c\n\n", 219, 219, 219, 219, 219, 219, 219, 219);
    printf("\033[0;36m");
    getchar();
    printf("First name: ");
    gets(residentialListRent.fn);
    printf("\nLast name: ");
    gets(residentialListRent.ln);
    printf("\nFather's name: ");
    gets(residentialListRent.fan);
    printf("\nMother's name: ");
    gets(residentialListRent.mon);
    printf("\nID number: ");
    gets(residentialListRent.idn);
    printf("\nPhone number: ");
    gets(residentialListRent.phn);
    printf("\033[0;34m");
    printf("\n%c%c%c%cResidential Property INFO for rent%c%c%c%c\n\n", 219, 219, 219, 219, 219, 219, 219, 219);
    printf("\033[0;36m");
    printf("Property Type: ");
    gets(residentialListRent.propertyType);
    printf("\nProperty Size: ");
    gets(residentialListRent.propertySize);
    printf("\nInfrastructure: ");
    gets(residentialListRent.infrastructure);
    printf("\nBed Rooms: ");
    gets(residentialListRent.bedRooms);
    printf("\nBath Rooms: ");
    gets(residentialListRent.bathRooms);
    printf("\nPrice Rage: ");
    gets(residentialListRent.priceRage);
    printf("\nFloor: ");
    gets(residentialListRent.floor);
    printf("\nAdress: ");
    gets(residentialListRent.adress);
    printf("\nNeighbourhood: ");
    gets(residentialListRent.neighbourhood);
    printf("\nDistrict: ");
    gets(residentialListRent.district);
    printf("\nAmenities: ");
    gets(residentialListRent.amenities);
    printf("\nReception Room: ");
    gets(residentialListRent.receptionRoom);
    printf("\nService Charge: ");
    gets(residentialListRent.serviceCharge);
    //now we are going to save them in the file.
    printf("\033[0;32m");
    printf("\n Do you want to save these informations??");
    printf("\033[0;36m");
    printf("\n1.Yes");
    printf("\n2.No\n");
    int fChoice;
    scanf("%d", &fChoice);
    if(fChoice==1)
    {
        fputs(residentialListRent.fn, file);
        fprintf(file,"\n");
        fputs(residentialListRent.ln, file);
        fprintf(file,"\n");
        fputs(residentialListRent.fan, file);
        fprintf(file,"\n");
        fputs(residentialListRent.mon, file);
        fprintf(file,"\n");
        fputs(residentialListRent.idn, file);
        fprintf(file,"\n");
        fputs(residentialListRent.phn, file);
        fprintf(file,"\n");
        fputs(residentialListRent.propertyType, file);
        fprintf(file,"\n");
        fputs(residentialListRent.propertySize, file);
        fprintf(file,"\n");
        fputs(residentialListRent.infrastructure, file);
        fprintf(file,"\n");
        fputs(residentialListRent.bedRooms, file);
        fprintf(file,"\n");
        fputs(residentialListRent.bathRooms, file);
        fprintf(file,"\n");
        fputs(residentialListRent.priceRage, file);
        fprintf(file,"\n");
        fputs(residentialListRent.floor, file);
        fprintf(file,"\n");
        fputs(residentialListRent.adress, file);
        fprintf(file,"\n");
        fputs(residentialListRent.neighbourhood, file);
        fprintf(file,"\n");
        fputs(residentialListRent.district, file);
        fprintf(file,"\n");
        fputs(residentialListRent.amenities, file);
        fprintf(file,"\n");
        fputs(residentialListRent.receptionRoom, file);
        fprintf(file,"\n");
        fputs(residentialListRent.serviceCharge, file);
        fprintf(file,"\n");
        printf("The Information Saved successfully, click enter to exit.");
        getchar();
    }
    else
    {
        system("cls");
        exit;
    }
    system("cls");
}
struct commercialListRent
{
    char fn[60]; //its for customer's first name
    char ln[60];  //its for customer's last name
    char fan[60]; //its for customer's father name
    char mon[60]; //its for customer's mother name
    char idn[60]; //its for customer's id number
    char phn[60]; //its for customer's phone number
    char propertyType[30]; //type of estate, for example residential, commercial, raw land, industrial or special purpose
    char propertySize[20]; //foot or square feet
    char infrastructure[30]; //the basic facilities and system serving a country, region, or community. (persian=zir bana)
    char rooms[10];
    char bathRooms[10];
    char priceRage[30]; //the price
    char floor[4];
    char adress[200];
    char neighbourhood[200];
    char district[40]; //an area of a country or city, especially one characterized by a particular feature or activity. (persian=mantaqe)
    char amenities[200]; //a desirable or useful feature or facility of a building or place. (persian= tashilat vasile refahi)
    char receptionRoom[3]; //a room in a private house suitable for entertaining visitors. (persian=otaq paziraii)
    char serviceCharge[30]; //a charge made for maintenance on a property which has been leased. (persian= service hazine khadamat, karmozd, anam)
    char shops[4]; //it means how many shops does it have
    char validation[10]; // this is for checking if its valid or not.
    struct commercialListRent *link;
} commercialListRent;
char CommercialPropertyFuncRent()
{
    FILE *file;
    file=fopen("CommercialPropertyListForRent.txt","a");
    if(file==NULL)
    {
        printf("Error opening the file.");
        exit;
        //now we just opened the file of commercial list.
    }
    printf("\033[0;34m");
    printf("%c%c%c%cCustomers Information%c%c%c%c\n\n", 219, 219, 219, 219, 219, 219, 219, 219);
    printf("\033[0;36m");
    getchar();
    printf("First name: ");
    gets(commercialListRent.fn);
    printf("\nLast name: ");
    gets(commercialListRent.ln);
    printf("\nFather's name: ");
    gets(commercialListRent.fan);
    printf("\nMother's name: ");
    gets(commercialListRent.mon);
    printf("\nID number: ");
    gets(commercialListRent.idn);
    printf("\nPhone number: ");
    gets(commercialListRent.phn);
    printf("\033[0;34m");
    printf("\n%c%c%c%cCommercial Property INFO for rent%c%c%c%c\n\n", 219, 219, 219, 219, 219, 219, 219, 219);
    printf("\033[0;36m");
    printf("Property Type: ");
    gets(commercialListRent.propertyType);
    printf("\nProperty Size: ");
    gets(commercialListRent.propertySize);
    printf("\nInfrastructure: ");
    gets(commercialListRent.infrastructure);
    printf("\nRooms: ");
    gets(commercialListRent.rooms);
    printf("\nBath Rooms: ");
    gets(commercialListRent.bathRooms);
    printf("\nPrice Rage: ");
    gets(commercialListRent.priceRage);
    printf("\nFloor: ");
    gets(commercialListRent.floor);
    printf("\nAdress: ");
    gets(commercialListRent.adress);
    printf("\nNeighbourhood: ");
    gets(commercialListRent.neighbourhood);
    printf("\nDistrict: ");
    gets(commercialListRent.district);
    printf("\nAmenities: ");
    gets(commercialListRent.amenities);
    printf("\nReception Room: ");
    gets(commercialListRent.receptionRoom);
    printf("\nService Charge: ");
    gets(commercialListRent.serviceCharge);
    printf("\nShops: ");
    gets(commercialListRent.shops);
    //now we are going to save them in the file.
    printf("\033[0;32m");
    printf("\n Do you want to save these informations??");
    printf("\033[0;36m");
    printf("\n1.Yes");
    printf("\n2.No\n");
    //getchar();
    int fChoice;
    scanf("%d", &fChoice);
    if(fChoice==1)
    {
        fputs(commercialListRent.fn, file);
        fprintf(file,"\n");
        fputs(commercialListRent.ln, file);
        fprintf(file,"\n");
        fputs(commercialListRent.fan, file);
        fprintf(file,"\n");
        fputs(commercialListRent.mon, file);
        fprintf(file,"\n");
        fputs(commercialListRent.idn, file);
        fprintf(file,"\n");
        fputs(commercialListRent.phn, file);
        fprintf(file,"\n");
        fputs(commercialListRent.propertyType, file);
        fprintf(file,"\n");
        fputs(commercialListRent.propertySize, file);
        fprintf(file,"\n");
        fputs(commercialListRent.infrastructure, file);
        fprintf(file,"\n");
        fputs(commercialListRent.rooms, file);
        fprintf(file,"\n");
        fputs(commercialListRent.bathRooms, file);
        fprintf(file,"\n");
        fputs(commercialListRent.priceRage, file);
        fprintf(file,"\n");
        fputs(commercialListRent.floor, file);
        fprintf(file,"\n");
        fputs(commercialListRent.adress, file);
        fprintf(file,"\n");
        fputs(commercialListRent.neighbourhood, file);
        fprintf(file,"\n");
        fputs(commercialListRent.district, file);
        fprintf(file,"\n");
        fputs(commercialListRent.amenities, file);
        fprintf(file,"\n");
        fputs(commercialListRent.receptionRoom, file);
        fprintf(file,"\n");
        fputs(commercialListRent.serviceCharge, file);
        fprintf(file,"\n");
        fputs(commercialListRent.shops, file);
        fprintf(file,"\n");
        printf("The Information Saved successfully, click enter to exit.");
        getchar();
    }
    else
    {
        system("cls");
        exit;
    }
    system("cls");
}
struct countrylandListRent
{
    char fn[60]; //its for customer's first name
    char ln[60];  //its for customer's last name
    char fan[60]; //its for customer's father name
    char mon[60]; //its for customer's mother name
    char idn[60]; //its for customer's id number
    char phn[60]; //its for customer's phone number
    char propertyType[30]; //type of estate, for example residential, commercial, raw land, industrial or special purpose
    char propertySize[20]; //foot or square feet
    char infrastructure[30]; //the basic facilities and system serving a country, region, or community. (persian=zir bana)
    char rooms[10];
    char bathRooms[10];
    char priceRage[30]; //the price
    char adress[200];
    char neighbourhood[200]; //river, village and..
    char district[40]; //an area of a country or city, especially one characterized by a particular feature or activity. (persian=mantaqe)
    char amenities[200]; //a desirable or useful feature or facility of a building or place. (persian= tashilat vasile refahi)
    char harvest[3]; //tree, fruits
    char serviceCharge[30]; //a charge made for maintenance on a property which has been leased. (persian= service hazine khadamat, karmozd, anam)
    char validation[10]; // this is for checking if its valid or not.
    struct countrylandListRent *link;
} countrylandListRent;
char CountryLandPropertyRent()
{
    FILE *file;
    file=fopen("CountryLandPropertyListForRent.txt","a");
    if(file==NULL)
    {
        printf("Error opening the file.");
        exit;
        //now we just opened the file of country land list.
    }
    printf("\033[0;34m");
    printf("%c%c%c%cCustomers Information%c%c%c%c\n\n", 219, 219, 219, 219, 219, 219, 219, 219);
    printf("\033[0;36m");
    getchar();
    printf("First name: ");
    gets(countrylandListRent.fn);
    printf("\nLast name: ");
    gets(countrylandListRent.ln);
    printf("\nFather's name: ");
    gets(countrylandListRent.fan);
    printf("\nMother's name: ");
    gets(countrylandListRent.mon);
    printf("\nID number: ");
    gets(countrylandListRent.idn);
    printf("\nPhone number: ");
    gets(countrylandListRent.phn);
    printf("\033[0;34m");
    printf("\n%c%c%c%cCountry Land INFO for rent%c%c%c%c\n\n", 219, 219, 219, 219, 219, 219, 219, 219);
    printf("\033[0;36m");
    printf("Property Type: ");
    gets(countrylandListRent.propertyType);
    printf("\nProperty Size: ");
    gets(countrylandListRent.propertySize);
    printf("\nInfrastructure: ");
    gets(countrylandListRent.infrastructure);
    printf("\nRooms: ");
    gets(countrylandListRent.rooms);
    printf("\nBath Rooms: ");
    gets(countrylandListRent.bathRooms);
    printf("\nPrice Rage: ");
    gets(countrylandListRent.priceRage);
    printf("\nFloor: ");
    gets(countrylandListRent.adress);
    printf("\nNeighbourhood: ");
    gets(countrylandListRent.neighbourhood);
    printf("\nDistrict: ");
    gets(countrylandListRent.district);
    printf("\nAmenities: ");
    gets(countrylandListRent.amenities);
    printf("\nHarvest: ");
    gets(countrylandListRent.harvest);
    printf("\nService Charge: ");
    gets(countrylandListRent.serviceCharge);
    //now we are going to save them in the file.
    printf("\033[0;32m");
    printf("\n Do you want to save these informations??");
    printf("\033[0;36m");
    printf("\n1.Yes");
    printf("\n2.No\n");
    //getchar();
    int fChoice;
    scanf("%d", &fChoice);
    if(fChoice==1)
    {
        fputs(countrylandListRent.fn, file);
        fprintf(file,"\n");
        fputs(countrylandListRent.ln, file);
        fprintf(file,"\n");
        fputs(countrylandListRent.fan, file);
        fprintf(file,"\n");
        fputs(countrylandListRent.mon, file);
        fprintf(file,"\n");
        fputs(countrylandListRent.idn, file);
        fprintf(file,"\n");
        fputs(countrylandListRent.phn, file);
        fprintf(file,"\n");
        fputs(countrylandListRent.propertyType, file);
        fprintf(file,"\n");
        fputs(countrylandListRent.propertySize, file);
        fprintf(file,"\n");
        fputs(countrylandListRent.infrastructure, file);
        fprintf(file,"\n");
        fputs(countrylandListRent.rooms, file);
        fprintf(file,"\n");
        fputs(countrylandListRent.bathRooms, file);
        fprintf(file,"\n");
        fputs(countrylandListRent.priceRage, file);
        fprintf(file,"\n");
        fputs(countrylandListRent.adress, file);
        fprintf(file,"\n");
        fputs(countrylandListRent.neighbourhood, file);
        fprintf(file,"\n");
        fputs(countrylandListRent.district, file);
        fprintf(file,"\n");
        fputs(countrylandListRent.amenities, file);
        fprintf(file,"\n");
        fputs(countrylandListRent.harvest, file);
        fprintf(file,"\n");
        fputs(countrylandListRent.serviceCharge, file);
        fprintf(file,"\n");
        printf("The Information Saved successfully, click enter to exit.");
        getchar();
    }
    else
    {
        system("cls");
        exit;
    }
    system("cls");
}
char secondMenu()
{
    //this function is for second menu
    char choice, bChoice, cChoice, mChoice, nChoice,pChoice, xChoice, vChoice, firstName[60], lastName[160];
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
                exit(0);
            }
            if(cChoice==2)
            {
                CommercialPropertyFunc();
                exit(0);
            }
            if(cChoice==3)
            {
                CountryLandProperty();
                exit(0);
            }
        }
        if(bChoice==2)
        {
            printf("1.Residential property.\n");
            printf("2.Commercial property.\n");
            printf("3.Country land.\n");
            printf("4.Exit.\n");
            scanf("%d", &mChoice);
            system("cls");
            if(mChoice==1)
            {
                ResidentialPropertyFuncRent();
                exit(0);
            }
            if(mChoice==2)
            {
                CommercialPropertyFuncRent();
                exit(0);
            }
            if(mChoice==3)
            {
                CountryLandPropertyRent();
                exit(0);
            }

        }
        if(bChoice==3)
        {
            exit(0);
        }
    }
    if(choice==2)
    {
        printf("%c%cWhat INFO you want do delete??\n", 178, 180);
        printf("1.\nResidential property(for sale).");
        printf("2.\nCommercial property(for sale).");
        printf("3.\nCountry land(for sale).");
        printf("4.\nResidential property(for rent).");
        printf("5.\nCommercial property(for rent).");
        printf("6.\nCountry land(for rent).");
        printf("6.\nExit.\n");
        scanf("%d", &nChoice);
        system("cls");
        if(nChoice==1)
        {
            printf("Please write the information of the seller: \n");
            printf("First name:");
            gets(firstName);
            printf("Last name:");
            gets(lastName);
        }

    }
    if(choice==3)
        //this one is the main part of this project that user can use it most of the time, the reportage
    {
        printf("Which part you want to see the reportage:");
        printf("\n\n1.Residential property");
        printf("\n2.Commercial property");
        printf("\n3.Country land property");
        printf("\n4.Admin access\n");
        scanf("\n%d", &pChoice);
        system("cls");
        if(pChoice==1)
        {
            printf("Reportage of(Please enter the maximum amount):");
            printf("\n\n1.The number of the Residential properties.");
            printf("\n2.List based on price");
            printf("\n3.List based on infrastructure");
            printf("\n4.List based on district");
            printf("\n5.List based on bedrooms");
            printf("\n6.List based on floor\n");
            scanf("\n%d", &xChoice);
            system("cls");
            if(xChoice==1)
            {
                FILE*file=fopen("ResidentialPropertyList.txt", "r");
                if(!file)
                {
                    printf("Error opening the file");
                }
                struct cresidentialList cresidentialList;
                int count=0;
                while(fscanf(file, "%s", &cresidentialList)!=EOF)
                {
                    count++;
                }
                fclose(file);
                count=count/19;
                //i disived them to 19 because every person has 19 lines informations
                printf("There is %d residential property.\n", count);
            }
            if(xChoice==2)
            {
                char n[] = "ResidentialPropertyList.txt";
                struct  cresidentialList *head;
                head=readResidentialListFromFile(n);
                //this is the pointer and link list that is saved in readResidentialListFromFile
                char maxPrice[30];
                printf("Enter the maximum price: ");
                scanf("%s", maxPrice);
                showPropertiesUnderPrice(head, maxPrice);
            }
            if(xChoice==3)
            {
                char m[] = "ResidentialPropertyList.txt";
                struct  cresidentialList *head;
                head=readResidentialListFromFile(m);
                //this is the pointer and link list that is saved in readResidentialListFromFile
                char infrastructureCheck[10];
                printf("Enter infrastructure: ");
                scanf("%s", infrastructureCheck);
                showPropertiesInfrastructureCheck(head, infrastructureCheck);
            }
            if(xChoice==4)
            {
                char h[] = "ResidentialPropertyList.txt";
                struct  cresidentialList *head;
                head=readResidentialListFromFile(h);
                //this is the pointer and link list that is saved in readResidentialListFromFile
                char districtCheck[10];
                printf("Enter District: ");
                scanf("%s", districtCheck);
                showPropertiesDistrictCheck(head, districtCheck);
            }
            if(xChoice==5)
            {
                char s[] = "ResidentialPropertyList.txt";
                struct  cresidentialList *head;
                head=readResidentialListFromFile(s);
                //this is the pointer and link list that is saved in readResidentialListFromFile
                char bedroomCheck[10];
                printf("Enter the Bedrooms: ");
                scanf("%s", bedroomCheck);
                showPropertiesBedroomCheck(head, bedroomCheck);
            }
            if(xChoice==6)
            {
                char u[] = "ResidentialPropertyList.txt";
                struct  cresidentialList *head;
                head=readResidentialListFromFile(u);
                //this is the pointer and link list that is saved in readResidentialListFromFile
                char floorCheck[10];
                printf("Enter the Floor: ");
                scanf("%s", floorCheck);
                showPropertiesFloorCheck(head, floorCheck);
            }
        }
        if(pChoice==2)
        {
            printf("Reportage of:");
            printf("\n\n1.The number of the Commercial properties.");
            printf("\n2.List based on price");
            printf("\n3.List based on infrastructure");
            printf("\n4.List based on District");
            printf("\n5.List based on Shops");
            printf("\n6.List based on floor\n");
            int sChoice;
            scanf("%d", &sChoice);
            system("cls");
            if(sChoice==1)
            {
                FILE*file=fopen("CommercialPropertyList.txt", "r");
                if(!file)
                {
                    printf("Error opening the file");
                }
                struct commercialList commercialList;
                int count=0;
                while(fscanf(file, "%s", &commercialList)!=EOF)
                {
                    count++;
                }
                fclose(file);
                count=count/21;
                //i disived them to 20 because every person has 21 lines informations
                printf("There is %d commercial property.\n", count);
            }
            if(sChoice==2)
            {
                char q[] = "CommercialPropertyList.txt";
                struct  commercialList *head;
                head=readCommercialListFromFile(q);
                //this is the pointer and link list that is saved in readCommercialListFromFile
                char maxPriceCom[30];
                printf("Enter the maximum price: ");
                scanf("%s", maxPriceCom);
                showPropertiesUnderPriceCom(head, maxPriceCom);
            }
            if(sChoice==3)
            {
                char r[] = "CommercialPropertyList.txt";
                struct  commercialList *head;
                head=readCommercialListFromFile(r);
                //this is the pointer and link list that is saved in readCommercialListFromFile
                char infrastructureCheckCom[10];
                printf("Enter infrastructure: ");
                scanf("%s", infrastructureCheckCom);
                showPropertiesInfrastructureCheckCom(head, infrastructureCheckCom);
            }
            if(sChoice==4)
            {
                char t[] = "CommercialPropertyList.txt";
                struct  commercialList *head;
                head=readCommercialListFromFile(t);
                //this is the pointer and link list that is saved in readCommercialListFromFile
                char districtCheckCom[10];
                printf("Enter District: ");
                scanf("%s", districtCheckCom);
                showPropertiesDistrictCheckCom(head, districtCheckCom);
            }
            if(sChoice==5)
            {
                char j[] = "CommercialPropertyList.txt";
                struct  commercialList *head;
                head=readCommercialListFromFile(j);
                //this is the pointer and link list that is saved in readCommercialListFromFile
                char shopCheck[10];
                printf("Enter the Bedrooms: ");
                scanf("%s", shopCheck);
                showPropertiesShopCheck(head, shopCheck);
            }
            if(sChoice==6)
            {
                char o[] = "CommercialPropertyList.txt";
                struct  commercialList *head;
                head=readCommercialListFromFile(o);
                //this is the pointer and link list that is saved in readCommercialListFromFile
                char floorCheckCom[10];
                printf("Enter the Floor: ");
                scanf("%s", floorCheckCom);
                showPropertiesFloorCheckCom(head, floorCheckCom);
            }

        }
        if(pChoice==3)
        {
            printf("Reportage of:");
            printf("\n\n1.The number of the CountryLand properties.");
            printf("\n2.List based on price");
            printf("\n3.List based on infrastructure");
            printf("\n4.List based on District");
            printf("\n5.List based on Harvest\n");
            int hChoice;
            scanf("%d", &hChoice);
            system("cls");
            if(hChoice==1)
            {
                FILE*file=fopen("CountryLandPropertyList.txt", "r");
                if(!file)
                {
                    printf("Error opening the file");
                }
                struct countrylandList countrylandList;
                int count=0;
                while(fscanf(file, "%s", &countrylandList)!=EOF)
                {
                    count++;
                }
                fclose(file);
                count=count/19;
                //i disived them to 19 because every person has 19 lines informations
                printf("There is %d Country land property.\n", count);
            }
            if(hChoice==2)
            {
                char w[] = "CountryLandPropertyList.txt";
                struct  countrylandList *head;
                head=readCountryLandFromFile(w);
                //this is the pointer and link list that is saved in readCountryLandListFromFile
                char maxPriceCou[30];
                printf("Enter the maximum price: ");
                scanf("%s", maxPriceCou);
                showPropertiesUnderPriceCou(head, maxPriceCou);
            }
            if(hChoice==3)
            {
                char y[] = "CountryLandPropertyList.txt";
                struct  countrylandList *head;
                head=readCountryLandFromFile(y);
                //this is the pointer and link list that is saved in readCountryLandListFromFile
                char infrastructureCheckCou[10];
                printf("Enter infrastructure: ");
                scanf("%s", infrastructureCheckCou);
                showPropertiesInfrastructureCheckCou(head, infrastructureCheckCou);
            }
            if(hChoice==4)
            {
                char i[] = "CountryLandPropertyList.txt";
                struct  countrylandList *head;
                head=readCountryLandFromFile(i);
                //this is the pointer and link list that is saved in readCountryLandListFromFile
                char districtCheckCou[10];
                printf("Enter District: ");
                scanf("%s", districtCheckCou);
                showPropertiesDistrictCheckCou(head, districtCheckCou);
            }
            if(hChoice==5)
            {
                char l[] = "CountryLandPropertyList.txt";
                struct  countrylandList *head;
                head=readCountryLandFromFile(l);
                //this is the pointer and link list that is saved in readCountryLandListFromFile
                char harvestCheck[10];
                printf("Enter the Harvest: ");
                scanf("%s", harvestCheck);
                showPropertiesHarvestCheck(head, harvestCheck);
            }

        }

    }
    if(pChoice==4)
    {
        printf("Admin access: ");
        printf("\n\n7.Total value ");
        printf("\n\n8.Employees actions");
        printf("\n\n9.Clients time checking");
        printf("\n\n10.Employees time checking");
        scanf("%d", &vChoice);
        system("cls");
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




















