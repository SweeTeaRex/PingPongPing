#include <stdio.h>


int main(void)
{
    printf("Welcome to my text based adventure, created with C!\n");
    printf("Type 'next' to continue\n");
    
    char input[10];
    scanf("%s", input);
    
    printf("%s\n", input);
    /* code */
    return 0;
}
