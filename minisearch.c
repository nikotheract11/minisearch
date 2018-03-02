#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct p_list{    // this is a posting list node
   int text_id;
   int freq;
   struct p_list *next;
};

struct t_node {   // this is a trie node
   struct t_node *child;
   struct t_node *sibling;
   char value;
   struct p_list *plist;

};
typedef struct t_node t_node;
typedef struct p_list p_list;

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

int addplist(t_node **t,int text_id){
   t_node *tmp = *t;
   if(tmp->plist == NULL) {
      tmp->plist = (p_list*) malloc(sizeof(p_list));
      tmp->plist->text_id = text_id;
      tmp->plist->freq = 1;
      return 0;
   }
   else{
      p_list *p = tmp->plist;
      while (p->next != NULL && p->text_id != text_id)
         p = p->next;
      if(p->text_id == text_id)
         (p->freq)++;
      else {
         while(p->next != NULL) p = p->next;
         p->next = (p_list*) malloc(sizeof(p_list));
         p = p->next;
         p->text_id = text_id;
         p->freq = 1;
         return 0;
      }
   }
   return -1;
}
void pr(t_node *t);
int append(t_node **t,const char *key,int text_id){
   unsigned int i=0;
   t_node *tmp = *t;
   while(i<(strlen(key)) ){
      tmp->value = key[i];
      tmp->child = (t_node*) malloc(sizeof(t_node));
      tmp = tmp->child;
      i++;
   }
   addplist(t,text_id);

   return 0;
}

int insert(t_node **t, const char* key, int text_id){
   t_node *tmp = *t;
   unsigned int i = 0;

   if(*t == NULL) perror("NO TRIE\n");
   for(i=0;i<strlen(key);i++){
      while(tmp->sibling != NULL && key[i] != tmp->value)
         tmp = tmp->sibling;
      if(key[i] != tmp->value){
         // string not exists, create trie node to it
         if(tmp->value == 0) append(&tmp,&(key[i]),text_id);
         else{
            tmp->sibling = (t_node*) malloc(sizeof(t_node));
            tmp = tmp->sibling;
            append(&tmp,&(key[i]),text_id);
         }

         return 3;
      }

      else if(i == (strlen(key) - 1)) {
         addplist(&tmp,text_id);
         return 0;
      }
      else if(tmp->child != NULL) tmp = tmp->child;
      else {
         append(&tmp,&(key[i]),text_id);
         return 88;
      }
   }
   return -2;
}

void pr(t_node *t){
   if(t == NULL) return;
   printf("%c", t->value);
   pr(t->child);
//   printf("\n" );
   pr(t->sibling);
   printf("\n" );
}


 int main(int argc, char const *argv[]) {

   t_node *t=NULL;
   t = (t_node*) malloc(sizeof(t_node));
   printf("d=%d\n",insert(&t,"hello",1) );
   printf("d=%d\n",insert(&t,"nikalos",1) );
   printf("d=%d\n",insert(&t,"nikos",1) );
   printf("d=%d\n",insert(&t,"nikos",1) );
   insert(&t,"nikos",1);
//   insert(&t,"nalos",0);
//   insert(&t,"nikalos",0);
   printf("\n");
   pr(t);
   return 0;
}
