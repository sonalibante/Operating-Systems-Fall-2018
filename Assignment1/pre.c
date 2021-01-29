#include <stdio.h>
struct data
{
   char name[50];
   int population;
};
int main(){
    struct data data1[10], data2[10];
    FILE *fptr;
    int i;

    fptr = fopen("C:\\Users\\My Lappie\\Desktop\\Operating System Assignment1\\list.txt","wb");
    for(i = 0; i < 10; ++i)
    {
        fflush(stdin);
        printf("Enter State Name: ");
        gets(data1[i].name);

        printf("Enter Its population: ");
        scanf("%d", &data1[i].population);
    }

    fwrite(data1, sizeof(data1), 1, fptr);
    fclose(fptr);

    fptr = fopen("C:\\Users\\My Lappie\\Desktop\\Operating System Assignment1\\list.txt", "rb");
    fread(data2, sizeof(data2), 1, fptr);
    printf("the states whose population is above 10 million\n");
    for(i = 0; i < 10; ++i)
    {
        if(data2[i].population>=10)
        printf("%s\n", data2[i].name);
    }
    fclose(fptr);
}
