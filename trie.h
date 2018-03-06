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

int addplist(t_node **, int );
int append(t_node **,const char *,int);
int insert(t_node **,const char *,int);
void pr(t_node *);
char** get(const char*);
int getLinesNumber(FILE *);
int a(t_node *);
