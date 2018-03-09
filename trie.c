#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "trie.h"


int p_init(p_list ** p,int text_id,int freq){
   *p = (p_list*) malloc(sizeof(p_list));
   (*p)->next = NULL;
   (*p)->text_id = text_id;
   (*p)->freq = freq;
   return 0;
}

int addplist(int text_id){
   t_node *tmp = t;
   if(tmp->plist == NULL) {
      p_init(&(tmp->plist),text_id,1);
      return 0;
   }
   else{
      p_list *p = tmp->plist;
      while (p != NULL){
         if(p->text_id == text_id) {
            (p->freq)++;
            return 0;
         }
         if(p->next == NULL) {
            p_init(&(p->next),text_id,1);
            p = p->next;
            break;
         }
         p = p->next;
      }
   }
   return 0;
}

/*
 * Initialize a t_node
*/
int t_init(t_node ** t){
   *t = (t_node*)  malloc(sizeof(t_node));
   (*t)->sibling = NULL;
   (*t)->child = NULL;
   (*t)->plist = NULL;
   (*t)->value = 0;
   return 0;
}

/*
 * This function appends a key to trie t
*/
int append(t_node **t,const char *key,int text_id){
   unsigned int i=0;
   t_node *tmp = *t;
   while(i<(strlen(key)) ){
   //   printf("c=%c\n", tmp->value);
      if(key[i] == '\0') break;
      tmp->value = key[i];
      if(i== strlen(key)-1) break;
      t_init(&(tmp->child));
      tmp = tmp->child;    // xwris auto ti?

      i++;
   }

   addplist(&tmp,text_id);
   return 0;
}

/*
 * This functions inserts key with text_id to trie t
*/

int insert( const char* key, int text_id){
   t_node *tmp = t;
   unsigned int i = 0,j=0;

   // If trie is empty, create one
   if(t == NULL) {
      printf("j=%d\n", j++);
      t_init(&t);
      tmp = t;
      append(&tmp,key,text_id);
      return 22;
   }

   for(i=0;i<strlen(key);i++){
      while( key[i] != tmp->value ){
         if(tmp->sibling == NULL) break;
         tmp = tmp->sibling;
      }

      if(key[i] != tmp->value){
            t_init(&(tmp->sibling));
            tmp = tmp->sibling;
            append(&tmp,&(key[i]),text_id);
            return 3;
      }

      else if(i == (strlen(key) - 1) ) {
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
int a(t_node *t,int c){
   /*if(t->sibling != NULL) a(t->sibling);
   if(t->child != NULL) a(t->child);
   p_list *p = t->plist;
   while(p!=NULL){
      printf("tid=%d,freq=%d\n",p->text_id,p->freq );
      p = p->next;
   }*/
   if(t == NULL ) return -1;
   //if(t->sibling == NULL) printf("c=%c\n",t->value );
   if(t->child == NULL) printf("%c\n",t->value );
   else{
      t_node *p = t->child;
      while(p != NULL){
         printf("%c",t->value );
         a(p,0);
         p = p->sibling;
         if(t->child == NULL) printf("\n");
      }
      if(c==1) a(t->sibling,1);
   //   a(t->child,0);
   }


   return 0;
}

int getLinesNumber(FILE *fp){
	char c;// = fgetc(fp);
	int count = 0;
	while(!feof(fp)){
		c = fgetc(fp);
		if(c == '\n') count++;
	}
   fseek(fp,0,0);
	return ++count;
}

char** get(const char* file){

   FILE *fp;
   fp = fopen(file,"r");
   int i=0,j=0,id;
   char c;
   char **str;// =  *s;
   N = getLinesNumber(fp);
   str = (char**) malloc(N*sizeof(char*));
   if(feof(fp)) printf("************\n" );

   while( !feof(fp) ){
      c = fgetc(fp);
      if(c == EOF) break;
      if(i == 0) id = c - '0';
      if(id != j) printf("id=%d\n",id );//perror("ERROR\n");
      if(c == '\n' || feof(fp) ) {
         ungetc('!',fp);
	      if(!feof(fp)) i++;
         fseek(fp,-(i-2),SEEK_CUR);
         str[j] = (char*) malloc(i*sizeof(char));
         fgets(str[j++],i,fp);
         i=0;
      }
      else i++;
   }
   printf("i=%d, j=%d,s=%s\n",i,j,str[1] );
   fclose(fp);

   return str;
}
