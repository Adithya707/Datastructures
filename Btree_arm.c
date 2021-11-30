 
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
 

#define MAX 3
#define MIN 1
 
 
struct BTreeNode {
   int val[MAX + 1], count;
   struct BTreeNode *link[MAX + 1];
};
 
 
struct BTreeNode *root;
double cost=0.0;
 
 
// Create a node
struct BTreeNode *createNode(int val, struct BTreeNode *child) {
   struct BTreeNode *newNode;
   newNode = (struct BTreeNode *)malloc(sizeof(struct BTreeNode));
   newNode->val[1] = val;
   newNode->count = 1;
   newNode->link[0] = root;
   newNode->link[1] = child;
    cost +=6;
   return newNode;

}
 
 
// Insert node
void insertNode(int val, int pos, struct BTreeNode *node,
struct BTreeNode *child) {

  int j = node->count;
  while (j > pos) {
    node->val[j + 1] = node->val[j];
    node->link[j + 1] = node->link[j];
    j--;
    cost++;
  }
  node->val[j + 1] = val;
  node->link[j + 1] = child;
  node->count++;
  cost += 4;
}
 
 
// Split node
void splitNode(int val, int *pval, int pos, struct BTreeNode *node,
struct BTreeNode *child, struct BTreeNode **newNode) {
  int median, j;
 
  if (pos > MIN)
     median = MIN + 1;
  else
    median = MIN;
  cost++;
  *newNode = (struct BTreeNode *)malloc(sizeof(struct BTreeNode));
  j = median + 1;
   cost +=2;
  while (j <= MAX) {
    (*newNode)->val[j - median] = node->val[j];
    (*newNode)->link[j - median] = node->link[j];
    j++;
    cost+=3;
  }
  node->count = median;
  (*newNode)->count = MAX - median;
   cost += 2;
  if (pos <= MIN) {
    insertNode(val, pos, node, child);
  }else {
    insertNode(val, pos - median, *newNode, child);
  }
  cost++;
  *pval = node->val[node->count];
  (*newNode)->link[0] = node->link[node->count];
  node->count--;
   cost +=3;
}
 
 
// Set the value
int setValue(int val, int *pval,
  struct BTreeNode *node, struct BTreeNode **child) {
  int pos;
  if (!node) {
    *pval = val;
    *child = NULL;
    cost+=3;
    return 1;
  }
  if (val < node->val[1]) {
     pos = 0;
  } else {
    for (pos = node->count;
      (val < node->val[pos] && pos > 1); pos--,cost++);
    if (val == node->val[pos]) {
      printf("Duplicates are not permitted\n");
      cost+=2;
      return 0;
    }
  }
  if (setValue(val, pval, node->link[pos], child)) {
       if (node->count < MAX) {
         insertNode(*pval, pos, node, *child);
        } else {
         splitNode(*pval, pval, pos, node, *child, child);
         return 1;
        }
  }
  cost+=1;
  return 0;
}
 
 
// Insert the value
void insert(int val) {
   int flag, i;
   struct BTreeNode *child;
   flag = setValue(val, &i, root, &child);
   if (flag)
     root = createNode(i, child);
   cost+=3;
}
 
 
// Search node
void search(int val, int *pos, struct BTreeNode *myNode) {
   if (!myNode) {
      return;
   }
 
   if (val < myNode->val[1]) {
      *pos = 0;
   } else {
      for (*pos = myNode->count;
      (val < myNode->val[*pos] && *pos > 1); (*pos)--);

      if (val == myNode->val[*pos]) {
        printf("%d is found\n", val);
        return;
      }
  }
  search(val, pos, myNode->link[*pos]);
  return;
}
 

// Traverse then nodes
void traversal(struct BTreeNode *myNode) {
   int i;
   if (myNode) {
     for (i = 0; i < myNode->count; i++) {
       traversal(myNode->link[i]);
       printf("%d\t", myNode->val[i + 1]);
       cost++;
     }
    traversal(myNode->link[i]);
    cost++;
  }
}
 

int main() {
  int val, ch,n,i;
 
  printf("Enter insertion of key value\n");
  scanf("%d",&n);
  cost +=1;
  for(i=0;i<n;i++){
    printf("Enter value\n");
    scanf("%d",&val);
    cost++;
    insert(val);
  }
  cost +=n;
  traversal(root);
 
  printf("\n");
  //printf("Enter value to be searched\n");
  //scanf("%d",&val);
  //search(val, &ch, root);
  double a;
  a = log(n)/log((MAX-MIN));
 
  a = (MAX-MIN)*a;
   cost+=2;
  printf("\nTotal cost of all operation is %lf \n",a);
  printf("Armotized cost after %d insertion is %lf \n",n,(a/n));
  printf("Manual Armotized cost %lf \n",((cost)/(5*n+60)));
}
