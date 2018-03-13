#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include "trie.h"

int mygetopt(int argc, char * const argv[], int *p,char **filename){
   int opt,k;
   char *file;
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
   *p=k;
   *filename = file;
   return 0;

}

int main(int argc, char * const argv[]) {
   char *file;
   int k;
   mygetopt(argc,argv,&k,&file);
   char **str;
   init(file,&str);
   interface();

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

double score(int n,p_list *p){
   double sum ;
   sum = idf(n)*((p->freq*(k_1 + 1))/(p->freq + k_1*(1 - b + b*(D[p->text_id]/avgdl() ) ) ) );
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
         if(tmp->child == NULL && i<(strlen(key)-1)) return NULL;
         else if(i<(strlen(key)-1)) tmp = tmp->child;
         else continue; // ======== useless?

      }
      if(tmp->plist == NULL) return NULL;
      else{
         p_list *p = tmp->plist;
         return p;
      }
}




int init(const char* filename,char ***s){
      char **str = get(filename);
      char *token;
      int j=0;

      D = (uint*) malloc(sizeof(int)*N);
      //for(uint i=0;i<*N;i++) (*D)[i] = (int*) malloc(sizeof(int));

      while(str[j] != NULL) {
         token = strtok(str[j]," ");      // pros8etw edw gia id kai meta8etw tin 112->109
         while(token != NULL){
            (D)[j]++;
            if(token[strlen(token)-1] =='\n' || token[strlen(token)-1] ==' ') token[strlen(token)-1]='\0'; // =======
            if(insert(token,j)<0) perror("*******  ");
            token  = strtok(NULL," ");
         }
         j++;
      }
      *s = str;
      return 0;
   }
