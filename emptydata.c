#include <stdio.h>

struct hardware_info
{
    unsigned int tag;
    char name[30];
    unsigned int amount;
    double cost;
};


int main()
{
    FILE *dataptr;

    if((dataptr = fopen("hardware.dat", "wb")) == NULL)
    {
        printf("Can't open file");
    }
    else
    {
        struct hardware_info empty = {0, "", 0, 0};

        for(size_t i = 1; i <= 100; i++)
        {
            fwrite(&empty, sizeof(struct hardware_info), 1, dataptr);
        }
    }

    fclose(dataptr);
}