#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int getLinesNumber(FILE *fp){
	//FILE *fp=fopen(file,"r");
	char c;// = fgetc(fp);
	int count = 0;
	while(!feof(fp)){
		c = fgetc(fp);
		if(c == '\n') count++;
		//c = fgetc(fp);
	}
//	fclose(fp);
   fseek(fp,0,0);
	return count;
}

char ** ma(void) {
   FILE *fp;
   fp = fopen("../test.txt","r");
   int i=0,j=0,id;
   char c;
   char **str = (char**) malloc(getLinesNumber(fp)*sizeof(char*));
   if(feof(fp)) printf("************\n" );
   //printf("lines=%d\n",getLinesNumber(fp) );

   while( !feof(fp) ){
      c = fgetc(fp);
      if(c == EOF) break;
      if(i == 0) id = c - '0';
   //   printf("id=%d,j=%d\n",id,j );
      if(id != j) printf("id=%d\n",id );//perror("ERROR\n");
      if(c == '\n' || feof(fp) ) {
        // j++;
	 if(!feof(fp)) i++;
         fseek(fp,-(i-2),SEEK_CUR);
         str[j] = (char*) malloc(i*sizeof(char));
         fgets(str[j],i,fp);
         puts(str[j]);j++;
         i=0;
      }
      else i++;
   }
   printf("i=%d, j=%d,s=%s\n",i,j,str[2] );
   fclose(fp);

   return str;
}

int main(int argc, char const *argv[]) {
   char **str = ma();
   puts(str[1]);
   return 0;
}
