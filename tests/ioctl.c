#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
int a();

int ex(int *p,int n){
   int min = 0;
   while(p[min] == -1) min++;
   for(int i=(min+1);i<n;i++){
      if(p[i] != -1 && p[i] < p[min]) min = i;
   }

   return min;
}

int b(){
   struct winsize w;
   ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);


   char *s = (char*)malloc(sizeof("Hello Nikos Nikos Nikos"));
   strcpy(s,"Hello Nikos Nikos");
   int pos[2];
   char q[2][10];
   strcpy(q[0],"pello");
   strcpy(q[1],"Nikos");
   char *ret;
   int i=0,j=0;
   for(int k=0;k<2;k++){
      //if(pos[k] == -1) continue;
      if((ret=strstr(&(s[j]),q[k])) == NULL) pos[k]=-1;
      else {
         j= (int) ret - (int) s;
         pos[k]=j;
      }
   }
   j=0;
   while(i<strlen(s)){
      printf("%c",s[i] );
      if(i % (w.ws_col)== 0 && (i)!=0 || i==(strlen(s)-1)){

         int min = ex(pos,2);
         while(pos[min]<i) {
            printf("\n" );
            for(int k=0;k<pos[min]-j;k++) printf(" " );
            for(int k=0;k<strlen(q[min]);k++) printf("^");
            j+=pos[min];
            pos[min] = ;
            min = ex(pos,2)
         //   printf("\n" );
         }
         printf("\n" );
      }
      i++;
   }
   /*while((ret = strstr(&(s[j]),m)) != NULL){
      printf("i=%d\n",++i );
      j= (int) ret - (int) s;
      j+= strlen(m);
   }
   if((ret=strstr(s,m) ) == NULL) printf("%s not in string \n", m);
   if((ret=strstr(s,"Haloipoi") ) == NULL) printf("%s not in string\n","Haloipoi" );*/

   return 0;
}

int main (int argc, char **argv)
{
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

    printf ("lines %d\n", w.ws_row);
    printf ("columns %d\n", w.ws_col);
   // for(int i=0;i<w.ws_col;i++) printf("a");
    b();
    //a();
    return 0;  // make sure your main returns int
}


int a(){
   struct winsize w;
   ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

   char s[2048] = "Gallery unveils interactive tree  A Christmas tree that can receive text messages has been unveiled at London's Tate Britain art gallery.  The spruce has an antenna which can receive Bluetooth texts sent by visitors to the Tate. The messages will be \"unwrapped\" by sculptor Richard Wentworth, who is responsible for decorating the tree with broken plates and light bulbs. It is the 17th year that the gallery has invited an artist to dress their Christmas tree. Artists who have decorated the Tate tree in previous years include Tracey Emin in 2002.  The plain green Norway spruce is displayed in the gallery's foyer. Its light bulb adornments are dimmed, ordinary domestic ones joined together with string. The plates decorating the branches will be auctioned off for the children's charity ArtWorks. Wentworth worked as an assistant to sculptor Henry Moore in the late 1960s. His reputation as a sculptor grew in the 1980s, while he has been one of the most influential teachers during the last two decades. Wentworth is also known for his photography of mundane, everyday subjects such as a cigarette packet jammed under the wonky leg of a table." ;

   int l = strlen(s);
   int i=0;
   while(i<l){
      printf("%c",s[i] );
      if(i++ %(w.ws_col)== 0) printf("\n\n ^^^^^^^^\n\n");
   }
   return 0 ;
}
