

 
#include <stdio.h>
int main(void)
{
    int ch;
 


 
    while ((ch = getchar()) != '1')
        putchar(ch);
 
    /* ungetc() returns '1' previously read back to stdin */
    ungetc('+', stdin);
 


    //ch = getchar();
 
    /* putchar() displays character */
    putchar(ch);
    
    puts("");
 
    printf("Thank you!\n");
    return 0;
}
