#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include "trie.h"

/*
 * Using getopt to get command line arguments
*/
int mygetopt(int argc, char * const argv[], int *p,char **filename){
   int opt,k;
   char *file;
   while((opt = getopt(argc,argv,"i:k:") )!= -1)   {
      switch (opt) {
         case 'i':
         file = (char*) malloc((strlen(optarg)+1)*sizeof(char));
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

   // Get cl arguments
   mygetopt(argc,argv,&k,&file);

   // Create map and trie
   init(file);

   // Application Interface
   interface(k);

   // cleaning up space
   free(file);
   mfree();

   return 0;
}

double avgdl(){
   double sum = 0.0;

   if(N == 0) {
      perror("Error: N=0");
      return -1.0;
   }

   for(uint i=0;i<N-1;i++){
      sum += D[i];
   }
   return sum/(double)N;
}

double idf(int n){
   return log10((N-n+0.5)/(n+0.5));
}

double score(int n,p_list *p){
   double sum ;
   sum = idf(n)*((p->freq * (k_1 + 1))/(p->freq + k_1*(1 - b + b*(D[p->text_id]/avgdl() ) ) ) );
   return sum;
}

/*
 * Searching for key in trie, and return the p_list if exists
*/
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



/*
 * Initialize data structures like map and trie
*/
int init(const char* filename){
      str=get(filename);   // create the map
      char *token,*tmp;
      int j=0,inn;

      D = (uint*) malloc(sizeof(int)*N);     // Array containing # of words per text
      for(uint i=0;i<N;i++) D[i] = 0;

      while(str[j] != NULL) {
         tmp = (char*) malloc(sizeof(char)*(strlen(str[j])+1));
         strcpy(tmp,str[j]);

         // Break text to words and insert them to trie
         token = strtok(tmp," ");
         while(token != NULL){
            (D[j])++;
            if(token[strlen(token)-1] =='\n' || token[strlen(token)-1] ==' ') token[strlen(token)-1]='\0'; // =======
            if((inn=insert(token,j))<0) printf("%d\n", inn);
            token  = strtok(NULL," ");
         }
         j++;
         free(tmp);
         free(token);
      }

      return 0;
   }

/*
 * Recursive free of a p_list
*/
void p_free(p_list **p){
      p_list *tmp = *p;

      if(tmp == NULL) return;
      p_free(&(tmp->next));
      free(tmp);
}

/*
 * Recursive free of the trie
*/
void t_free(t_node **p){
      t_node *tmp = *p;
      if(tmp->child != NULL) t_free(&(tmp->child));
      if(tmp->sibling != NULL) t_free(&(tmp->sibling));
      if(tmp->plist != NULL) {
         p_free(&(tmp->plist));
      }
      free(tmp);
}

/*
 * Calls p_free and t_free and also frees some globals
*/
void mfree(){
      for(uint i=0;i<N;i++){
         free(str[i]);
      }
      free(str);
      free(D);
      t_free(&t);
}
