#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "./trie.h"
#include "./heaps/PQInterface.h"


/*
 * Returns tokens of user input
*/
char **getok(char* s,int *k){
   char **st;
   int count=0;
   for(unsigned int i=0;i<=strlen(s);i++){
      if(s[i] == ' ' || s[i] == '\0') count++;
   }
   st = (char**) malloc(count*sizeof(char*));
   char *token;
   token = strtok(s," ");
   int j=0;
   while(token != NULL) {
      st[j] = (char*) malloc(sizeof(char)*(strlen(token)+1));
      strcpy(st[j++],token);
      token = strtok(NULL," ");
      if(j>11) break;
   }
   *k=count;
   free(token);
   return st;

}

/*
 * Searching on trie, implementation of /search feature
*/
int search(char** s,int j,int k){
   pair **Score = (pair**) malloc(sizeof(pair*)*N);      // create array with N elements to store score for each text
   for(uint i=0;i<N;i++)  Score[i] = NULL;             // init to NULL

   for(int i=1;i<j;i++){
      p_list *p = find(s[i]);    // p_list of this word if exists
      if(p == NULL) break;       // if not exists break

      int p_length = p->plen;    // # of texts containing s[i]
      while(p != NULL) {
         if(Score[p->text_id] == NULL){
             Score[p->text_id] = (pair*) malloc(sizeof(pair));
             Score[p->text_id]->text_id = p->text_id;
             Score[p->text_id]->score = 0.0;
          }
          Score[p->text_id]->score  += score(p_length,p);
          p = p->next;
      }
}
      PriorityQueue PQ;    // A maxHeap to get top K results
      Initialize(&PQ,N);
      for(uint k=0;k<N;k++){
         if(Score[k] != NULL) Insert(Score[k],&PQ);
      }
      int count=1;
      for(uint i=0;i<N-1;i++){
         if(count > k) break;
         pair *p = Remove(&PQ);
         if(p!=NULL) {
            printf("%d. (%d) [%.4f] ",count++,p->text_id,p->score);//%d, score=%f\n",p->text_id,p->score );
            //form_pr(str[p->text_id],s,j);
            printf("\n" );
            form_pr(str[p->text_id],s,j);
            printf("\n");
         }
         else break;
   }

   for(uint i=0;i<N;i++){
      if(Score[i] != NULL) free(Score[i]);
   }
   free(Score);
   free(PQ.ItemArray);

   printf("Search called to operate: %s\n",s[0] );
   return 0;
}

/*
 * /df implementation
*/
int df(char** s,int j){
   printf("Df called to operate: %s\n",s[0] );
   if(j==2){
      p_list *p = find(s[1]);
      if(p != NULL)  printf("%s %d\n",s[1],p->plen );
   }
   else{
      char *bf=malloc(32*sizeof(char));      // not possible word with length > 32
      pr_trie(t,bf,0);
      free(bf);
   }
   return 0;
}

/*
 * /tf implementation
*/
int tf(char** s){
   printf("Tf called to operate: %s\n",s[0] );
   int text_id = atoi(s[2]);
   p_list *p = find(s[1]);       // s[1] = key s[2] = id becuase s[0] = /tf
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

/*
 * Calls the right function
*/
int operate( char** s,int j,int k){
   if(!strcmp(s[0],"exit")) return -1;
   if(!strcmp(s[0],"/search")) return search(s,j,k);
   else if(!strcmp(s[0],"/df")) return df(s,j);
   else if(!strcmp(s[0],"/tf")) return tf(s);
   else {
      printf("Not such a command available\n");
      return -2;
   }
}

/*
 * The Application interface
*/
int interface(int k){
   char *buf, **s;

   int j=0;
   while(1){
      scanf("%m[^\n]s\n",&buf );
      getchar();

      if(buf != NULL) s=getok(buf,&j);
      free(buf);

      if(operate(s,j,k)== -1)
         break;
      for(int i=0;i<j;i++) free(s[i]);
      free(s);
   }
   for(int i=0;i<j;i++) free(s[i]);
   free(s);

   return 0;
}
