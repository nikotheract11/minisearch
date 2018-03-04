#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "trie.h"

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
//void pr(t_node *t);
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

int getLinesNumber(FILE *fp){
	//FILE *fp=fopen(file,"r");
	char c;// = fgetc(fp);
	int count = 0;
	while(!feof(fp)){
		c = fgetc(fp);
		if(c == '\n') count++;
		//c = fgetc(fp);
	}
//	fclose(fp);
   fseek(fp,0,0);
	return ++count;
}

char** get(const char* file){

   FILE *fp;
   fp = fopen(file,"r");
   int i=0,j=0,id;
   char c;
   char **str;// =  *s;
   str = (char**) malloc(getLinesNumber(fp)*sizeof(char*));
   if(feof(fp)) printf("************\n" );

   while( !feof(fp) ){
      c = fgetc(fp);
      if(c == EOF) break;
      if(i == 0) id = c - '0';
      if(id != j) printf("id=%d\n",id );//perror("ERROR\n");
      if(c == '\n' || feof(fp) ) {
        // j++;
         //ungetc(1,fp);
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
