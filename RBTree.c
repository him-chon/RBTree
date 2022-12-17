// Red-Black Tree ADT implementation ... COMP9024 22T3

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include "RBTree.h"

#define PRINT_COLOR_RED   "\x1B[31m"
#define PRINT_COLOR_RESET "\x1B[0m"

#define data(tree)   ((tree)->data)
#define left(tree)   ((tree)->left)
#define right(tree)  ((tree)->right)
#define color(tree) ((tree)->color)
#define NodeisRed(t) ((t) != NULL && (t)->color == RED)

typedef enum {RED,BLACK} Colr;

typedef struct Node {
   Item data;
   Colr color;
   Tree left, right;
} Node;

// create a new empty Tree
Tree newTree() {
   return NULL;
}

// make a new node containing data
Tree newNode(Item it) {
   Tree new = malloc(sizeof(Node));
   assert(new != NULL);
   data(new) = it;
   color(new) = RED;
   left(new) = right(new) = NULL;
   return new;
}

Tree rotateRight(Tree);
Tree rotateLeft(Tree);
Tree insertRB(Tree, Item, bool); // recursive RB insertion definition

Tree TreeInsert(Tree t, Item it) {
   t = insertRB(t, it, false);
   color(t) = BLACK;
   return t;
}

Tree insertRB(Tree t, Item it, bool inRight) {
   if (t == NULL)
      return newNode(it);
   if (it == data(t))
      return t;

   //Splitting 4-node before traversing for insertion
   if(NodeisRed(left(t)) && NodeisRed(right(t))){
      color(left(t))=BLACK;
      color(right(t))=BLACK;color(t)=RED;
   }

   if (it < data(t)) {
      left(t) = insertRB(left(t), it, false);

      if (inRight && NodeisRed(t) && NodeisRed(left(t)))
         t = rotateRight(t);
      else if (!inRight && NodeisRed(t) && NodeisRed(right(t)))
            t = rotateLeft(t);

   } else if (it > data(t)) {
      right(t) = insertRB(right(t), it, true);

      if(!inRight && NodeisRed(t) && NodeisRed(right(t)))
            t = rotateLeft(t);
      else if (inRight && NodeisRed(t) && NodeisRed(left(t)))
            t = rotateRight(t);
   }

   if (NodeisRed(right(t)) && NodeisRed(right(right(t)))) {
      color(t) = RED;
      color(right(t)) = BLACK;
      t = rotateLeft(t);
   }
   else if (NodeisRed(left(t)) && NodeisRed(left(left(t)))) {
      color(t) = RED;
      color(left(t)) = BLACK;
      t = rotateRight(t);
   }
   return t;
}


// check whether a key is in a Tree
bool TreeSearch(Tree t, Item it) {
   if (t == NULL)
      return false;
   else if (it < data(t))
      return TreeSearch(left(t), it);
   else if (it > data(t))
      return TreeSearch(right(t), it);
   else                                 // it == data(t)
      return true;
}

Tree rotateRight(Tree n1) {
   if (n1 == NULL || left(n1) == NULL)
      return n1;
   Tree n2 = left(n1);
   left(n1) = right(n2);
   right(n2) = n1;
   return n2;
}

Tree rotateLeft(Tree n2) {
   if (n2 == NULL || right(n2) == NULL)
      return n2;
   Tree n1 = right(n2);
   right(n2) = left(n1);
   left(n1) = n2;
   return n1;
}

// free memory associated with Tree
void freeTree(Tree t) {
   if (t != NULL) {
      freeTree(left(t));
      freeTree(right(t));
      free(t);
   }
}

// display Tree sideways
void showTreeR(Tree t, int depth) {
   if (t != NULL) {
      showTreeR(right(t), depth+1);
      int i;
      for (i = 0; i < depth; i++)
	 putchar('\t');            // TAB character
      if (NodeisRed(t))
	 printf("%s%d%s\n", PRINT_COLOR_RED, data(t), PRINT_COLOR_RESET);
      else
	 printf("%d\n", data(t));
      showTreeR(left(t), depth+1);
   }
}

void showTree(Tree t) {
   showTreeR(t, 0);
}
