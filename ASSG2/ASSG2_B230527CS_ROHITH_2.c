#include<stdio.h>
#include<stdlib.h>

struct node {
    int key;
    int value;
    struct node* left;
    struct node* right;
    int height;
}typedef node;

node* createnode(int key,int value) {
    node* y = (node*)malloc(sizeof(node));
    y->key = key;
    y->value = value;
    y->height = 0;
    y->left = NULL;
    y->right = NULL;
    return y;
}

int max(int a,int b) {
    return a>b?a:b;
}

int height(node* root) {
    int lh = (root && root->left)?root->left->height:-1;
    int rh = (root && root->right)?root->right->height:-1;
    return max(rh,lh)+1;
}

int balance(node* root) {
    int lh = root && root->left?root->left->height:-1;
    int rh = root && root->right?root->right->height:-1;
    return lh-rh;
}

node* LLrotation(node* root) {
    node* newr = root->left;
    root->left = newr->right;
    newr->right = root;
    root->height = height(root);
    newr->height = height(newr);
    return newr;
}

node* RRrotation(node* root) {
    node* newr = root->right;
    root->right = newr->left;
    newr->left = root;
    root->height = height(root);
    newr->height = height(newr);
    return newr;
}

node* LRrotation(node* root) {
    root->left = RRrotation(root->left);
    return LLrotation(root);
}

node* RLrotation(node* root) {
    root->right = LLrotation(root->right    );
    return RRrotation(root);
}

node* insert(node* root,int key,int value) {
    if (!root) return createnode(key,value);
    if (root->key<key) root->right = insert(root->right,key,value);
    else root->left = insert(root->left,key,value);
    root->height = height(root);
    if (balance(root) == 2 && balance(root->left) == 1) return LLrotation(root);
    if (balance(root) == -2 && balance(root->right) == -1) return RRrotation(root);
    if (balance(root) == 2 && balance(root->left) == -1) return LRrotation(root);
    if (balance(root) == -2 && balance(root->right) == 1) return RLrotation(root);
    return root; 
}

node* search(node* root,int key) {
    if (root == NULL) return NULL;
    if (root->key>key) return search(root->left,key);
    else if (root->key<key) return search(root->right,key);
    else return root;
}

void descending(node* root) {
    if (!root) return;
    descending(root->right);
    printf("%d ",root->key);
    descending(root->left);
}

void helper(node* root,int* max,int n,node** temp) {
    if (!root) return;
    helper(root->right,max,n,temp);
    if (root->key >= n && root->key<*max) {
        *max = root->key;
        *temp = root;
    }
    helper(root->left,max,n,temp);
}

void upper_bound(node* root,int key) {
    node* x = search(root,key);
    if (x) {
        printf("%d %d\n",x->key,x->value);
        return;
    }
    int max = __INT_MAX__;
    node* temp = NULL;
    helper(root,&max,key,&temp);
    if (!temp) printf("-1\n");
    else printf("%d %d\n",temp->key,temp->value);
}

int main() {
    node* root = NULL;
    int key,value,size=0;
    char c = ' ';
    while (c != 't') {
        scanf("%c",&c);
        if (c == 'i') {
            scanf("%d %d",&key,&value);
            node* x = search(root,key);
            if (!x) {
                root = insert(root,key,value);
                size++;
            }
            else x->value = value; 
        }
        else if (c == 'd') {
            descending(root);
            printf("\n");
        }
        else if (c == 'e') root==NULL?printf("1\n"):printf("0\n");
        else if (c == 'f') {
            scanf("%d",&key);
            node* x = search(root,key);
            if (!x) printf("-1\n");
            else printf("%d %d\n",key,x->value);
        }
        else if (c == 's') printf("%d\n",size);
        else if (c == 'u') {
            scanf("%d",&key);
            upper_bound(root,key);
        }
    }
}