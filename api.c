#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include "trie.h"



int main(int argc, char * const argv[]) {
   char *file;
   int k,opt;

   while((opt = getopt(argc,argv,"i:k:") )!= -1)   {
      switch (opt) {
         case 'i':
         file = (char*) malloc(strlen(optarg)*sizeof(char));
            strcpy(file,optarg);
            printf("file name=%s\n", file);
            break;

         case 'k':
            k = atoi(optarg);
            printf("k=%d\n",k);
            break;
         }
   }
   return 0;
}

double avgdl(){
   double sum = 0.0;

   if(N == 0) {
      perror("Error: N=0");
      return -1.0;
   }

   for(uint i=0;i<N;i++){
      sum += D[i];
   }
   return sum/(double)N;
}

double idf(int n){
   return log10((N-n+0.5)/(n+0.5));
}

double score(const char** q,uint q_num,int text_id,int f,int n){
   double sum = 0;

   for(uint i=0;i<q_num;i++){
      /*int f,n;
      if(find(q[i],&f,&n,text_id) < 0) {
         perror("find error on score");
         return -1;
      }*/

      sum += idf(n)*((f*(k_1 + 1))/(f + k_1*(1 - b + b*(D[i]/avgdl() ) ) ) );
   }

   return sum;
}


p_list* find(const char *key){
      t_node *tmp = t;
      if(tmp ==NULL) {
         perror("Empty Trie");
         return NULL;
      }

      for(uint i=0;i<strlen(key);i++){
         while(key[i] != tmp->value){
            if(tmp->sibling == NULL) return NULL;
            tmp = tmp->sibling;
         }
         if(tmp->child == NULL) return NULL;
         else if(i<(strlen(key)-1)) tmp = tmp->child;

      }
      if(tmp->plist == NULL) return NULL;
      else{
      //   *n = 0;
         p_list *p = tmp->plist;
         /*while(p != NULL){
            (*n)++;
            if(p->text_id == text_id) (*f) = p->freq;
            p = p->next;
         }*/
         return p;
      }
}




int init(const char* filename,char ***s,t_node **t){
      char **str = get(filename);
      char *token;
      int j=0;

      D = (uint*) malloc(sizeof(int)*N);
      //for(uint i=0;i<*N;i++) (*D)[i] = (int*) malloc(sizeof(int));

      while(str[j] != NULL) {
         token = strtok(str[j]," ");
         while(token != NULL){
            (D)[j]++;
            if(token[strlen(token)-1] =='\n' || token[strlen(token)-1] ==' ') token[strlen(token)-1]='\0'; // =======
            if(insert(t,token,j)<0) perror("*******  ");
            token  = strtok(NULL," ");
         }
         j++;
      }
      *s = str;
      return 0;
   }
