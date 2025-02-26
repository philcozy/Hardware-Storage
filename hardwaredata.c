#include <stdio.h>
#include <ctype.h>

unsigned int menu(void); //start menu
void printlist(void); //(1)
void addstorage(void); //(2)
void delete(void); //(3)

struct hardware_info
{
    unsigned int tag;
    char name[30];
    unsigned int amount;
    double cost;
};

int main()
{    
    unsigned int choice;

    while((choice = menu()) != 0)
    {
        switch(choice)
        {
            case 1:
                printlist();
                break;
            case 2:
                addstorage();
                break;
            case 3:
                delete();
                break;
        }
    }
}

unsigned int menu(void)
{   
    unsigned int user_choice;
    printf("This is the list of your hardware storage\n");
    printf("-----------------------------------------\n");
    printf("Menu: (1) to print the list\n");
    printf("      (2) to add storage\n");
    printf("      (3) to delete hardware data\n");
    printf("      (0) to exit\n");
    printf("      ? ");
    scanf("%u", &user_choice);
    return user_choice;
}

void printlist(void)
{
    FILE *txtptr;
    FILE *dataPtr;

    if((txtptr = fopen("list.txt","w")) == NULL || (dataPtr = fopen("hardware.dat", "r")) == NULL)
    {
        printf("Can't open file");
    }
    else
    {
        rewind(txtptr);
        rewind(dataPtr);

        fprintf(txtptr, "%-6s%-16s%-11s%-10s\n", "Tag", "Tool Name","Amount", "Cost");
        struct hardware_info printstruct = {0, "", 0, 0};
        while(fread(&printstruct, sizeof(struct hardware_info), 1, dataPtr) == 1)
        {
            if(printstruct.tag != 0)
            {
                fprintf(txtptr,"%-6u%-16s%-11u%-10.2lf\n", printstruct.tag, printstruct.name, printstruct.amount, printstruct.cost);
            }
        }

        fclose(txtptr);
    }
}

void addstorage(void)
{
    FILE *dataPtr;

    if((dataPtr = fopen("hardware.dat","rb+")) == NULL)
    {
        printf("Can't open file");
    }
    else
    {
        struct hardware_info hardware;
        unsigned int tagnumber;

        printf("Enter the tag#: ");
        scanf("%u", &tagnumber);

        fseek(dataPtr, sizeof(struct hardware_info) * (tagnumber - 1), SEEK_SET);
        fread(&hardware, sizeof(struct hardware_info), 1, dataPtr);

        if (hardware.tag == 0)
        {
            char answer;
            printf("There is no info by the tag in the list\n");
            printf("Do you want to create new hardware data type? (Y/N): ");
            scanf(" %c", &answer);
            answer = toupper(answer);

            if(answer == 'Y')
            {
                struct hardware_info newhardware;
                newhardware.tag = tagnumber;
                printf("Enter Name, amount, cost each\n");
                scanf("%29s%u%lf", newhardware.name, &newhardware.amount, &newhardware.cost);

                fseek(dataPtr, sizeof(struct hardware_info) * (tagnumber - 1), SEEK_SET);
                fwrite(&newhardware, sizeof(struct hardware_info), 1, dataPtr);

                fclose(dataPtr);
            }
        }
        else
        {
            printf("%u  %s  %u  %.2lf\n", hardware.tag, hardware.name, hardware.amount, hardware.cost);
            int change;
            printf("Enter the amount (+ or -): ");
            scanf("%d", &change);
            hardware.amount += change;
            fseek(dataPtr, sizeof(struct hardware_info) * (tagnumber - 1), SEEK_SET);
            fwrite(&hardware, sizeof(struct hardware_info), 1, dataPtr);
            fclose(dataPtr);
        }
    }
    
}

void delete(void)
{
    FILE *dataPtr;
    if((dataPtr = fopen("hardware.dat","rb+")) == NULL)
    {
        printf("Can't open file");
    }
    else
    {
        struct hardware_info del_hardware;
        unsigned int tagnumber;

        printf("Enter the tag#: ");
        scanf("%u", &tagnumber);
        fseek(dataPtr, sizeof(struct hardware_info) * (tagnumber - 1), SEEK_SET);
        fwrite(&del_hardware, sizeof(struct hardware_info), 1, dataPtr);
        printf("%u deleted", tagnumber);
    }
}