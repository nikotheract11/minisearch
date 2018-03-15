#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "./trie.h"
#include "./heaps/PQInterface.h"

char** getok(char* s,int *k){
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
   *k=j;    // ========== mipws count
   return str;

}

int search(char** s,int j){
   pair **Score = (pair**) malloc(sizeof(pair*)*N);      // create array with N elements to store score for each text
   for(uint i=0;i<N;i++)  Score[i] = NULL;             // init to NULL

   for(int i=1;i<j;i++){
      p_list *p = find(s[i]);
      if(p == NULL) break;
      int p_length = p->plen;
      while(p != NULL) {
         if(Score[p->text_id] == NULL){
             Score[p->text_id] = (pair*) malloc(sizeof(pair));
             //*Score[p->text_id] = 0.0;
             Score[p->text_id]->text_id = p->text_id;
             Score[p->text_id]->score = 0.0;
          }

          Score[p->text_id]->score  += score(p_length,p);
          printf("Score=%f\n",Score[p->text_id]->score );
          p = p->next;
      }
      PriorityQueue PQ;
      Initialize(&PQ,N);
      for(uint k=0;k<N;k++){
         if(Score[k] != NULL) Insert(Score[k],&PQ);
      }
      for(uint k=0;k<N;k++){
         pair *p = Remove(&PQ);

         if(p!=NULL) printf("id=%d, score=%f\n",p->text_id,p->score );
      }



   }


   printf("Search called to operate: %s\n",s[0] );
   return 0;
}

int df(char** s){
   printf("Df called to operate: %s\n",s[0] );
   a(t,NULL,0);
   return 0;
}

int tf(char** s){
   printf("Tf called to operate: %s\n",s[0] );
   int text_id = atoi(s[2]);
   p_list *p = find(s[1]);       // s[1] = key s[2] = id
   if(p == NULL) printf("****************************\n");
   while(p != NULL){
      if(p->text_id==text_id) {
         printf("%d %s %d\n",p->text_id, s[1],p->freq );
         return 0;
      }
      else p = p->next;
   }

   return -2;
}

int operate( char** s,int j){
   if(!strcmp(s[0],"exit")) return -1;
   if(!strcmp(s[0],"/search")) return search(s,j);
   else if(!strcmp(s[0],"/df")) return df(s);
   else if(!strcmp(s[0],"/tf")) return tf(s);
   else {
      printf("Not such a command available\n");
      return -2;
   }
}

int interface(void){
   char *buf, **s;
   int j=0;
   while(1){
      scanf("%m[^\n]s\n",&buf );
      getchar();

      if(buf != NULL) s=getok(buf,&j);
      if(operate(s,j)== -1) break;
      free(buf);
   }
   return 0;
}
