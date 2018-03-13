#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct s{
   int val;
   char *name;
};

int cmp(const void * a, const void * b){
   //printf("a=%d,b=%d\n",(*((struct s**) a))->val,(*((struct s**) b))->val );
   return -((*((struct s**) a))->val-(*((struct s**) b))->val );
}

int main(){
   struct s *a[3];
   a[0] = malloc(sizeof(struct s));
   a[0]->val = 34;
   a[0]-> name = malloc(10*sizeof(char));
   strcpy(a[0]->name,"a");

   a[1] = malloc(sizeof(struct s));
   a[1]->val = 394;
   a[1]-> name = malloc(10*sizeof(char));
   strcpy(a[1]->name,"b");

   a[2] = malloc(sizeof(struct s));
   a[2]->val = 4;
   a[2]-> name = malloc(10*sizeof(char));
   strcpy(a[2]->name,"c");

   qsort(a,3,sizeof(struct s* ),cmp);
   for(int i=0;i<3;i++){
      printf("%s:%d ", a[i]->name,a[i]->val);
   }
   printf("\n");

}
