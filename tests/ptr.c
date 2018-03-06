#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int foo(int **k){
   *k = malloc(sizeof(int));
   int *i = *k;
   //if(i == NULL){
   //   printf("NULL\n" );
      //i = malloc(sizeof(int));
      *i = 5;
      return 0;
//   }
//   return -1;
}

int main(int argc, char const *argv[]) {
   int *i=NULL;
   foo(&i);
   if(i == NULL) printf("^^^^^^^^^^^^^\n" );
   return 0;
}
