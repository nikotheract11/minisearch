/* This is the file �PQTypes.h� */
#include "../trie.h"
#define MAXCOUNT 10
typedef int PQItem;
typedef PQItem PQArray[MAXCOUNT+1];

typedef struct {
           int Count;
           pair **ItemArray;
        } PriorityQueue;
