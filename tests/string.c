#include <stdio.h>
#include <stdlib.h>
#include <string.h>

 int main(int argc, char const *argv[]) {
//	char s[10] = "hello";
char *s = malloc(10*sizeof(char));
strcpy(s,"hello");
   strcmp(s,"hello");
   free(s);
	return 0;
}
