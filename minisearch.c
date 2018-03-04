#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "trie.h"


int find(t_node *t, const char* key, int text_id){
   if(t == NULL) return -1;      // empty trie
   t_node *tmp = t;

   for(unsigned int i=0;i<strlen(key);i++){

      while(tmp->sibling != NULL && key[i] != tmp->value)
         tmp = tmp->sibling;

      if(key[i] != tmp->value)
         return -1;     // not in trie

      else {
         if(i == (strlen(key) - 1)) return 0;//insert(tmp,text_id);   // key found, insert posting list
         else if(tmp->child != NULL) tmp = tmp->child;
         else return -1;      // not in trie
      }
   }
   return -2;     // general error
}




 int main(int argc, char const *argv[]) {

   t_node *t=NULL;
   //t = (t_node*) malloc(sizeof(t_node));
   printf("d=%d\n",insert(&t,"Hello",1) );
   printf("d=%d\n",insert(&t,"nikalos",1) );
   printf("d=%d\n",insert(&t,"Nikos",1) );
   printf("d=%d\n",insert(&t,"Nifkos",1) );
   insert(&t,"nikos",1);
   insert(&t,"nalos",0);
   insert(&t,"nikalos",0);
   printf("\n");
   //pr(t);
   char **str;
   str = get("./test.txt");
   int j=0;
   //insert(&t,"Nifkos",1);
   while(str[j] != NULL) {
      printf("Breaking \"%s\" to tokens\n", str[j]);
      char *token = strtok(str[j]," ");
      while(token != NULL){
         printf("%s\n",token );


      insert(&t,token,0);
         token  = strtok(NULL," ");
      }
      j++;
   }
   insert(&t,"Nifkos",1);
   return 0;
}
