#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct s{
   int val;
   struct s *next;
};

struct s *s;
int *i;

int a(){
   s = (struct s*) malloc(sizeof(struct s));
   s->val = 1888;
   s->next = NULL;
   return 0;
}

int b(){

   struct s *t = s;
   printf("Before b, val=%d\n",s->val );
   t->next = (struct s*) malloc(sizeof(struct s));
   t = s->next;
   t->val = 2222;
   t->next = NULL;
   return 0;
}
int main(){
   a();
   printf("a=%d\n",s->val );
   b();
   printf("b=%d,b->next=%d\n",s->val,s->next->val );
}
