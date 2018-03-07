#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char **getok(char* s,int *k){
   char **str;
   int count=0;
   for(unsigned int i=0;i<=strlen(s);i++){
      if(s[i] == ' ' || s[i] == '\0') count++;
   }
   str = (char**) malloc(count*sizeof(char*));
   char *token;
   token = strtok(s," ");
   int j=0;
   while(token != NULL) {
      str[j] = (char*) malloc(sizeof(char)*strlen(token));
      strcpy(str[j++],token);
      token = strtok(NULL," ");
      if(j>11) break;
   }
   *k=j;
   return str;
   printf("c=%d\n",count );
}

int search(char** s){
   printf("Search called to operate: %s\n",s[0] );
   return 0;
}

int df(char** s){
   printf("Df called to operate: %s\n",s[0] );
   return 0;
}

int tf(char** s){
   printf("Tf called to operate: %s\n",s[0] );
   return 0;
}

int operate( char** s){
   if(!strcmp(s[0],"exit")) return -1;
   if(!strcmp(s[0],"/search")) return search(s);
   else if(!strcmp(s[0],"/df")) return df(s);
   else if(!strcmp(s[0],"/tf")) return tf(s);
   else {
      printf("Not such a command available\n");
      return -2;
   }
}

int main(void){
   char *buf, **s;
   int j=0;
   while(1){
      scanf("%m[^\n]s\n",&buf );
      getchar();

      if(buf != NULL) s=getok(buf,&j);
      if(operate(s)== -1) break;
      free(buf);
   }
}
