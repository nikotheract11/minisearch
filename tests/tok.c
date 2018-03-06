#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char const *argv[]) {
   /* code */
   char str[100] = "Testing   strtok for           tabs\n";
   const char s[2] = " ";
   char *token;

   token = strtok(str,s);

   while(token != NULL){
      printf("%s",token );

      if(token[strlen(token)-1] == '\n') token[strlen(token)-1]=' ';// printf("&&&&&&&&&&&&&&&&&&&&&\n" );
      printf("%c\n", token[strlen(token)-1]);
      token = strtok(NULL,s);
   }
   return 0;
}
