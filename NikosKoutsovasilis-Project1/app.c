#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "trie.h"

int main(int argc, char * const argv[]) {
   char *file;
   int k;

   if(argc < 4) {
      printf("Wrong input arguments\n");
      return -1;
   }

   // Get cl arguments
   mygetopt(argc,argv,&k,&file);

   // Create map and trie
   if(init(file) == -1) return -1;

   // Application Interface
   interface(k);

   // cleaning up space
   free(file);
   mfree();

   return 0;
}
