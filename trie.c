#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "trie.h"

/*
 * create a p_list node
*/
int p_init(p_list ** p,int text_id,int freq){
   *p = (p_list*) malloc(sizeof(p_list));
   (*p)->next = NULL;
   (*p)->text_id = text_id;
   (*p)->freq = freq;
   (*p)->plen = 0;
   return 0;
}

/*
 * add a p_list node to trie
*/
int addplist(t_node **t,int text_id){
   t_node *tmp = *t;

   // if this word, found for first time, plist = NULL
   if(tmp->plist == NULL) {
      p_init(&(tmp->plist),text_id,1);
      (tmp->plist->plen)++;
      return 0;
   }

   // else append to the end one more p_list node to plist list, or increase frequency
   else{
      p_list *p = tmp->plist;
      while (p != NULL){
         if(p->text_id == text_id) {
            (p->freq)++;
            return 0;
         }

         // if text_id not in the list
         if(p->next == NULL) {
            p_init(&(p->next),text_id,1);
            (tmp->plist->plen)++;
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
      if(key[i] == '\0') break;
      tmp->value = key[i];
      if(i == strlen(key)-1) break;
      t_init(&(tmp->child));
      tmp = tmp->child;

      i++;
   }

   //add a plist for the key
   addplist(&tmp,text_id);
   return 0;
}

/*
 * This functions inserts key with text_id to trie t
*/

int insert( const char* key, int text_id){
   t_node *tmp = t;
   unsigned int i = 0;

   // If trie is empty, create one
   if(t == NULL) {
      t_init(&t);
      tmp = t;
      append(&tmp,key,text_id);
      return 22;
   }
   if(strlen(key) <= 0) return 0;

   // traversing trie
   for(i=0;i<strlen(key);i++){
      while( key[i] != tmp->value ){
         if(tmp->sibling == NULL) break;
         tmp = tmp->sibling;
      }

      // if key not in trie
      if(key[i] != tmp->value){
            t_init(&(tmp->sibling));
            tmp = tmp->sibling;
            append(&tmp,&(key[i]),text_id);
            return 3;
      }

      // key in trie, increase frequency
      if(i == (strlen(key) - 1) ) {
         addplist(&tmp,text_id);
         return 0;
      }

      // going down the trie
      if(tmp->child != NULL && i < (strlen(key) -1)) tmp = tmp->child;

      else {
         append(&tmp,&(key[i]),text_id);
         return 88;
      }
   }
   return -2;
}

/*
 * Print trie
*/
int pr_trie(t_node *t,char *buf,int i){
   t_node *tmp=t;
   if(t == NULL ) return -1;

   buf[i++] = tmp->value;
   if(tmp->plist != NULL) {
      buf[i]='\0';
      printf("%s %d\n",buf,tmp->plist->plen );
   }

   pr_trie(tmp->child,buf,i);
   pr_trie(tmp->sibling,buf,--i);

   return 0;
}

/*
 * Return the # of texts
*/
int getLinesNumber(FILE *fp){
	char c;
	int count = 0;
	while(!feof(fp)){
		c = fgetc(fp);
		if(c == '\n') count++;
	}
   fseek(fp,0,0);
	return ++count;
}

/*
 * Creates the map
*/
char** get(const char* file){

   FILE *fp;
   fp = fopen(file,"r");
   int i=0,j=0,id;
   char c;

   N = getLinesNumber(fp);
   str = (char**) malloc(N*sizeof(char*));
   for(int k=0;k<N;k++) str[k] = NULL;

   if(feof(fp)) printf("************\n" );

   char *ids = (char*) malloc(10*sizeof(char));    // 10 becuase not possible more than 9999999999 ids

   while( !feof(fp) ){
      c = fgetc(fp);
      if(c == EOF) break;
      else ungetc(c,fp);
      if(i == 0){
         fscanf(fp,"%s",ids);
         id = atoi(ids);
         if(id != j) printf("id=%d,j=%d\n",id,j );//perror("ERROR\n");
      }

      c = fgetc(fp);
      if(c == EOF) break;

      if(c == '\n' || feof(fp) ) {
	      if(!feof(fp)) i++;
         fseek(fp,-(i-strlen(ids)+2),SEEK_CUR);
         str[j] = (char*) malloc((i+1)*sizeof(char));
         fgets(str[j++],i,fp);
         i=0;
      }
      else i++;
   }
   fclose(fp);
   free(ids);

   return str;
}

int get_terminal_width(){
   struct winsize w;
   ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

   return w.ws_col;
}

/*
 * Called from form_pr to find positions to print ^^^^^
*/
void pr(char *str,char **arg,int j){
	char *tmp,*tok;
	int space = 1;
	struct st *A[10];
	for(int i=0;i<10;i++) A[i] = NULL;

	if(str[0] == ' ') space = 1;
   if(str[1] == ' ') space--;

	printf("%s\n",str);
	tmp = malloc((strlen(str)+1)*sizeof(char));
	strcpy(tmp,str);
	tok = strtok(tmp," ");
	int ii=0;

	while(tok != NULL){
			for(int k=0;k<j;k++){
				if(!strcmp(tok,arg[k])) {
					A[ii] = malloc(sizeof(struct st));
					A[ii]->pos = space;
					A[ii++]->len = strlen(tok);
				}
			}
			space += strlen(tok)+1;
			tok = strtok(NULL," ");
	}
	int i=0;
	for(int k=0;k<10;k++) {
		if(A[k] == NULL) break;
		while (i++<A[k]->pos) {
			printf(" ");
		}
		for(int l=0;l<A[k]->len;l++,i++) printf("^");
		printf(" ");
	}
	printf("\n");
}

/*
 * Formated print, to identify keywords
*/
void form_pr(char *str,char **arg,int j){
   int l = get_terminal_width();
   int len = strlen(str);
   char *s = malloc(l*sizeof(char));
   int counter = 0;
   while(counter < len){
      for(int i=0;i<l;i++) {
         if(i+counter == len-1) break;
         s[i]=str[i+counter];
      }
      s[l]='\0';

      pr(s,arg,j);
      counter += l;
   }

}
