#include <stdio.h>
#include <string.h>

int main (void) {
   const char str[] = "http://www.tutorialspoint.com";
   const char ch = '.';
   char *ret;
   int flag;

   ret = strchr(str, ch);
   
   if (ret == str+10) {
       printf("ok\n");
       flag = 0;
   } else {
       printf("nok\n");
       flag = 1;
   }
   
   return(flag);
}
