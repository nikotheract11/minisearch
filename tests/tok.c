#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char const *argv[]) {
   /* code */
   char str[100] = "Testing   strtok for           tabs";
   const char s[2] = " ";
   char *token;

   token = strtok(str,s);

   while(token != NULL){
      printf("%s\n",token );
      token = strtok(NULL,s);
   }
   return 0;
}
