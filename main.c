#include <stdio.h>
#include<stdlib.h>

#define MAX_FOOD_NAME 20
#define MAX_TYPE_NAME 25
#define MAX_DRINK_NAME 15
#define MAX_LINE 10

void readType(char * type);
double returnPrice(char * line);
void saveData(FILE *fptr, int noOfFood, char ** food, int * noOfTypes, char *** types, double ** prices, int noOfDrinks, char ** drinks, double * priceDrinks);

int main() {
    //read no of food dishes
    int noOfFood;
    printf("Please input number of food types\n");
    scanf("%d",&noOfFood);
    getchar();    // read enter

    //read food dishes
    char ** food;
    food = (char**)malloc(noOfFood* sizeof(char*));
    printf("Please input food types (each on a new line, may contain spaces)\n");
    for(int i=0;i<noOfFood;i++){
        food[i] = (char*)malloc(MAX_FOOD_NAME* sizeof(char));
        //scanf("%s",food[i]);
        gets(food[i]);
    }

    int * noOfTypes = (int*)malloc(noOfFood * sizeof(int));
    char *** types = (char***)malloc(noOfFood * sizeof(char**));
    double ** prices = (double**)malloc(noOfFood * sizeof(double*));
    for(int i=0;i<noOfFood;i++) {
        //read no of types
        printf("Please input no of specific foods for food \"%s\"\n", food[i]);
        scanf("%d", &noOfTypes[i]);
        getchar();

        //reads types and prices
        types[i] = (char**)malloc(noOfTypes[i] * sizeof(char*));
        prices[i] = (double*)malloc(noOfTypes[i] * sizeof(double));

        printf("Please input \"%s\" specific foods &prices: each line in the format <specific food> (price):\n",food[i]);
        for (int j = 0; j < noOfTypes[i]; j++) {
            types[i][j]=(char*)malloc(MAX_TYPE_NAME * sizeof(char));
            readType(types[i][j]);
            char line[MAX_LINE];
            gets(line);
            prices[i][j]=returnPrice(line);
        }
    }

    //read drinks
    int noOfDrinks;
    printf("Please input no of drinks\n");
    scanf("%d",&noOfDrinks);
    getchar();
    printf("Please input the drinks: each line in the format <drink> (price):\n");
    //read drinks and prices
    char ** drinks = (char**)malloc(noOfDrinks * sizeof(char*));
    double * priceDrinks = (double*)malloc(noOfDrinks * sizeof(double));
    for(int i=0;i<noOfDrinks;i++){
        drinks[i] = (char*)malloc(MAX_DRINK_NAME * sizeof(char));
        readType(drinks[i]);
        char line[MAX_LINE];
        gets(line);
        priceDrinks[i]=returnPrice(line);
    }

    //display data on the console
    printf("The food data is: \n");
    for(int i=0;i<noOfFood;i++)
    {
        printf("%s: ", food[i]);
        for(int j=0;j<noOfTypes[i];j++) {
            printf("(%s - %.2lf) ",types[i][j],prices[i][j]);
        }
        printf("\n");
    }
    printf("The drinks data is:\n");
    printf("drinks: ");
    for(int i=0;i<noOfDrinks;i++){
        printf("%s",drinks[i]);
        if(i!=noOfDrinks-1)
            printf(", ");
    }
    printf("\n");
    printf("prices: ");
    for(int i=0;i<noOfDrinks;i++){
        printf("%.0lf",priceDrinks[i]);
        if(i!=noOfDrinks-1)
            printf(", ");
    }

    // open file
    FILE *fptr;
    fptr = fopen("D:\\CP\\food-data-provider\\data.txt","w");

    if(fptr == NULL){
        printf("Error!");
        exit(1);
    }
    //save data to the file
    saveData(fptr,noOfFood,food,noOfTypes,types,prices,noOfDrinks,drinks,priceDrinks);

    //free memory
    for(int i=0;i<noOfFood;i++){
        for(int j=0;j<noOfTypes[i];j++){
            free(types[i][j]);
        }
        free(types[i]);
        free(prices[i]);
        free(food[i]);
    }
    free(types);
    free(prices);
    free(food);
    free(noOfTypes);
    for(int i=0;i<noOfDrinks;i++) {
        free(drinks[i]);
    }
    free(drinks);
    free(priceDrinks);

    return 0;
}
void readType(char * type){
    char c=getchar();
    int i=0;
    while(c!='('){
        type[i] = c;
        c=getchar();
        i++;
    }
    type[i-1]='\0';
}
double returnPrice(char * line){
    int i;
    double price=0;
    i=0;
    while(line[i]!=')') {
        price = price * 10 + line[i] - '0';
        i++;
    }
    return price;
}
void saveData(FILE *fptr, int noOfFood, char ** food, int * noOfTypes, char *** types, double ** prices, int noOfDrinks, char ** drinks, double * priceDrinks)
{
    fprintf(fptr,"%d:\n",noOfFood);
    for(int i=0;i<noOfFood;i++){
        fprintf(fptr,"%s: ",food[i]);
        for(int j=0;j<noOfTypes[i];j++){
            fprintf(fptr,"(%s - %.2lf)", types[i][j],prices[i][j]);
            if(j==noOfTypes[i]-1)
                fprintf(fptr,"\n");
            else
                fprintf(fptr," ");
        }
    }
    fprintf(fptr,"%d:\n",noOfDrinks);
    for(int i=0;i<noOfDrinks;i++){
        fprintf(fptr,"(%s - %.0lf)",drinks[i],priceDrinks[i]);
        if(i!=noOfDrinks-1)
            fprintf(fptr,", ");
    }
    fclose(fptr);
}