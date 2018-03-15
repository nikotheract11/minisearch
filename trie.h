#ifndef _INCL_GUARD
#define _INCL_GUARD

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define  k_1 1.2
#define b 5


uint N;     // Number of texts
uint *D;    // Array with the number of words from each text
struct t_node *t;  // Trie root node
char **str; // the map to the texts

struct pair {
   int text_id;
   double score;
};

struct p_list{    // this is a posting list node
   int text_id;
   int freq;
   int plen;      // the length of the plist only found on the first element of each p_list
   struct p_list *next;
};

struct t_node {   // this is a trie node
   struct t_node *child;
   struct t_node *sibling;
   char value;
   struct p_list *plist;

};

typedef struct pair pair;
typedef struct t_node t_node;
typedef struct p_list p_list;

int addplist(t_node **, int );
int append(t_node **,const char *,int);
int insert(const char *,int);
void pr(t_node *);
char** get(const char*);
int getLinesNumber(FILE *);
int a(t_node *,char *,int c);
p_list * find(const char *);
double score(int ,p_list *);
int interface(void);
int init(const char* filename,char ***s);

#endif
