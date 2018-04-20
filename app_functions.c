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
   char *token;
   for(unsigned int i=0;i<=strlen(s);i++){
      if(s[i] == ' ' || s[i] == '\0') count++;
   }
   st = (char**) malloc(count*sizeof(char*));

   token = strtok(s," ");
   int j=0;
   while(token != NULL) {
      st[j] = (char*) malloc(sizeof(char)*(strlen(token)+1));
      strcpy(st[j++],token);
      token = strtok(NULL," ");
      if(j>11) break;
   }
   *k=j;
   free(token);
   return st;

}

int digit_precision(){     // Not more id's or texts than thin num
   int n=N,count=0;
   while(n!=0) {
      count++;
      n/=10;
   }
   return count;
}

int count(int i){
   int counter=0;
   if(i==0) return 1;
   while (i!=0) {
      counter++;
      i/=10;
   }
   return counter;
}

int count_digits(int id,int text, double score){
   int rest=14;      // 14 bcs of 4 digit_precision on score and the characters "." "()" etc
   if(score > 0) rest--;
   return count(id)+count(text)+count((int)score)+rest;
}



/*
 * Searching on trie, implementation of /search feature
*/
int search(char** s,int j,int k){
   if(j < 2) {
      printf("Wrong arguments for /search\n");
      return -1;
   }


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

      // Insert Pairs of scores and text_ids to the Heap
      for(uint k=0;k<N;k++){
         if(Score[k] != NULL) Insert(Score[k],&PQ);
      }

      // Extract top-K
      int count=1;
      for(uint i=0;i<N;i++){
         if(count > k) break;
         if(PQ.Count==0) break;
         pair *p = Remove(&PQ);
         if(p!=NULL) {
            printf("%d. (%d) [%.4f] ",count,p->text_id,p->score);
            form_pr(str[p->text_id],s,j,count_digits(count++,p->text_id,p->score));
            printf("\n");
         }
         else break;
   }

   // cleaning up space
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
      char *bf=malloc(256*sizeof(char));      // not possible word with length > 256
      pr_trie(t,bf,0);
      free(bf);
   }
   return 0;
}

/*
 * /tf implementation
*/
int tf(char** s,int j){
   printf("Tf called to operate: %s\n",s[0] );
   if(j<3) {
      printf("Not enough arguments\n");
      return -1;
   }
   int text_id = atoi(s[1]);
   p_list *p = find(s[2]);       // s[2] = key s[1] = id becuase s[0] = /tf
   if(p == NULL) {
      printf("Word \'%s\' not exists\n",s[2] );
   }
   while(p != NULL){
      if(p->text_id==text_id) {
         printf("%d %s %d\n",p->text_id, s[2],p->freq );
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
   if(!strcmp(s[0],"/exit")) return -1;
   if(!strcmp(s[0],"/search")) return search(s,j,k);
   else if(!strcmp(s[0],"/df")) return df(s,j);
   else if(!strcmp(s[0],"/tf")) return tf(s,j);
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
