
#include <stdio.h>

struct cresidentialList {
    char name[50];
    int age;
};

int main() {
    FILE *file=fopen("ResidentialPropertyList.txt", "rb");
    if (!file)
    {
        printf("Error opening the file");
        return 1;
    }
    struct cresidentialList cresidentialList;
    int count = 0;

    while (fread(&cresidentialList, sizeof(struct cresidentialList), 1, file))

    {
        count++;
    }

    fclose(file);

    printf("number: %d\n", count);

    return 0;
}
