#include <stdio.h>
#include <string.h>


int main(void)
{
    printf("Welcome to my text based adventure, created with C!\n");
    printf("Type 'next' to continue\n");
    
    int condition = 0;
    char input[20];
    while(condition == 0)
    {
        scanf("%s", input);
    
        if(strcmp(input, "next") == 0)
        {
            printf("%s\n", input);
            condition = 1;
        }
        else
        {
            printf("Please type 'next' \n");
            condition = 0;
        }
    
    
    }
    
    printf("Congratulations! You have demonstrated the skill level nessesary to complete this course. \n"
    "Only a very few select number of people have been able to complete this program. \nI hope, for your sake, you do well. \n \nWe will be observing you \n \nPlease type 'next' to continue. \n \n");
    
    /* code */
    return 0;
}
