#include <stdio.h>
#include <stdlib.h>
#include "RBTree.h"

int main(){
   Tree t = newTree();
   TreeInsert(t, 10);
   TreeInsert(t, 5);
   TreeInsert(t, 12);
   showTree(t);
}

