 
#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#include<math.h>
 
struct node {
    int n;
    int degree;
    struct node* parent;
    struct node* child;
    struct node* sibling;
};
 
struct node* MAKE_bin_HEAP();
int bin_LINK(struct node*, struct node*);
struct node* CREATE_NODE(int);
struct node* bin_HEAP_UNION(struct node*, struct node*);
struct node* bin_HEAP_INSERT(struct node*, struct node*);
struct node* bin_HEAP_MERGE(struct node*, struct node*);
int DISPLAY(struct node*);
int FIND_NODE(struct node*);

 
int count = 1,min = 10000,least;

double cost = 2.0;
int cnt = 2;
 
struct node* MAKE_bin_HEAP() {
    struct node* np;
    np = NULL;
    cnt++;
    cost++;
    return np;
}
 
struct node * H = NULL;
struct node *Hr = NULL;

 
int bin_LINK(struct node* y, struct node* z) {
    y->parent = z;
    y->sibling = z->child;
    z->child = y;
    z->degree = z->degree + 1;
    cost+=4;
    cnt+=4;
}
 
struct node* CREATE_NODE(int k) {
    struct node* p;//new node;
    p = (struct node*) malloc(sizeof(struct node));
    p->n = k;
    cnt++;
    cost+=2;
    return p;
}
 
struct node* bin_HEAP_UNION(struct node* H1, struct node* H2) {
    struct node* prev_x;
    struct node* next_x;
    struct node* x;
    struct node* H = MAKE_bin_HEAP();
    H = bin_HEAP_MERGE(H1, H2);
    cost+=2;
    cnt+=2;
    if (H == NULL){
        cost+=2;
        cnt++;
        return H;
     }   
    prev_x = NULL;
    x = H;
    next_x = x->sibling;
    cost+=3;
    cnt+=3;
    while (next_x != NULL) {
        if ((x->degree != next_x->degree) || ((next_x->sibling != NULL)
                && (next_x->sibling)->degree == x->degree)) {
            prev_x = x;
            x = next_x;
            cost+=10;
            cnt+=4;
        } else {
            if (x->n <= next_x->n) {
                x->sibling = next_x->sibling;
                cost+=3;
                cnt+=2;
                bin_LINK(next_x, x);
            } else {
                if (prev_x == NULL){
                    H = next_x;
                    cost+=3;
                    cnt+=2;
                }    
                else{
                    prev_x->sibling = next_x;
                    cost++;
                    cnt++;
                }    
                bin_LINK(x, next_x);
                x = next_x;
                cnt++;
                cost++;
            }
        }
        next_x = x->sibling;
        cnt++;
        cost++;
    }
    return H;
}
 
struct node* bin_HEAP_INSERT(struct node* H, struct node* x) {
    struct node* H1 = MAKE_bin_HEAP();
    x->parent = NULL;
    x->child = NULL;
    x->sibling = NULL;
    x->degree = 0;
    H1 = x;
    H = bin_HEAP_UNION(H, H1);
    cnt+=6;
    cost+=6;
    return H;
}
 
struct node* bin_HEAP_MERGE(struct node* H1, struct node* H2) {
    struct node* H = MAKE_bin_HEAP();
    struct node* y;
    struct node* z;
    struct node* a;
    struct node* b;
    y = H1;
    z = H2;
    cost+=2;
    cnt+=2;
    if (y != NULL) {
        if (z != NULL && y->degree <= z->degree){
            H = y;
            cost+=7;
            cnt+=3;
        }    
        else if (z != NULL && y->degree > z->degree){
            /* need some modifications here;the first and the else conditions can be merged together!!!! */
            H = z;
            cost==7;
            cnt+=3;
        }    
        else{
            H = y;
            cost+=2;
            cnt++;
        }    
    } else{
        H = z;
        cost+=1;
        cnt+=1;
    }    
    while (y != NULL && z != NULL) {
        if (y->degree < z->degree) {
            cost+=5;
            cnt+=3;
            y = y->sibling;
        } else if (y->degree == z->degree) {
            a = y->sibling;
            y->sibling = z;
            y = a;
            cost+=7;
            cnt+=5;
        } else {
            b = z->sibling;
            z->sibling = y;
            z = b;
            cost+=5;
            cnt+=4;
        }
    }
    return H;
}
 
int DISPLAY(struct node* H) {
    struct node* p;
    if (H == NULL) {
        printf("\nHEAP EMPTY");
        return 0;
    }
    printf("\nTHE ROOT NODES ARE:-\n");
    p = H;
    while (p != NULL) {
        printf("%d", p->n);
        if (p->sibling != NULL)
            printf("-->");
        p = p->sibling;
    }
    printf("\n");
}
 

int FIND_NODE(struct node* H) {
    struct node* x = H;
    struct node* p = NULL;
    if (x->n < min) {
        min = x->n;
    }
    if (x->child != NULL && p == NULL) {
        min = FIND_NODE(x->child);
    }
 
    if (x->sibling != NULL && p == NULL) {
        min = FIND_NODE(x->sibling);
    }
    return min;
}
 
 
int main() {
    int i, n, m, l,a;
    struct node* p;
    struct node* np;
    char ch;
    printf("\nENTER THE NUMBER OF ELEMENTS:");
    scanf("%d", &n);
    printf("\nENTER THE ELEMENTS:\n");
    for (i = 1; i <= n; i++) {
        scanf("%d", &m);
        np = CREATE_NODE(m);
        H = bin_HEAP_INSERT(H, np);
    }
    DISPLAY(H);
    do {
        printf("\nMENU:-\n");
        printf("\n1)INSERT AN ELEMENT\n\n2)IDENTIFY MINIMUM\n\n3)QUIT\n");
        scanf("%d", &l);
        switch (l) {
        case 1:
                printf("\nENTER THE ELEMENT TO BE INSERTED:");
                scanf("%d", &m);
                p = CREATE_NODE(m);
                H = bin_HEAP_INSERT(H, p);
                printf("\nNOW THE HEAP IS:\n");
                DISPLAY(H);
                
            break;
        case 2:
              
                a = FIND_NODE(H);
                printf("\nThe minimum element is %d \n",a);
                min=10000;
                DISPLAY(H);
         
                
            break;
        case 3:
            printf("Manual Armotized cost %lf \n",(cost/cnt));
            printf("\n Theriotical cost %lf \n",log(n)/log(2));
            printf("\nTHANK U SIR\n");
            exit(0);
            break;
        default:
            printf("\nINVALID ENTRY...TRY AGAIN....\n");
        }
    } while (l != 5);
}


          
