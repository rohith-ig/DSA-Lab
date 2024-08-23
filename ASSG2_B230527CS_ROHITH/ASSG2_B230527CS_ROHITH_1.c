#include<stdio.h>
#include<stdlib.h>

struct node {
    int data;
    int height;
    struct node* left;
    struct node* right;
}typedef node;

int max(int x,int y) {
    return x>y?x:y;
}

node* createnode(int x) {
    node* y = (node*)malloc(sizeof(node));
    y->left = NULL;
    y->right = NULL;
    y->data = x;
    y->height = 0;
    return y;
}

int balance(node* root) {
    int lh = root && root->left?root->left->height:-1;
    int rh = root && root->right?root->right->height:-1;
    return lh-rh;
}

int height(node* root) {
    int lh = root && root->left?root->left->height:-1;
    int rh = root && root->right?root->right->height:-1;
    return max(rh,lh)+1;
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

node* avl_insert(node* root,int key,int* l,int* r) {
    if (root == NULL) return createnode(key);
    if (root->data <= key) root->right = avl_insert(root->right,key,l,r);
    else root->left = avl_insert(root->left,key,l,r);
    root->height = height(root);
    if (balance(root) == 2 && balance(root->left) == 1) {
        (*r)++;
        return LLrotation(root);
    }
    if (balance(root) == -2 && balance(root->right) == -1) {
        (*l)++;
        return RRrotation(root);
    }
    if (balance(root) == 2 && balance(root->left) == -1) {
        (*r)++;
        (*l)++;
        return LRrotation(root);
    }
    if (balance(root) == -2 && balance(root->right) == 1) {
        (*r)++;
        (*l)++;
        return RLrotation(root);
    }
    return root;
}

int avl_search(node* root,int key,int flag) {
    node** q = (node**)(malloc(sizeof(node*)*100));
    int tail = 0;
    while (root && root->data!=key) {
        if (root->data < key) {
            q[tail++] = root;
            root = root->right;
        }
        else {
            q[tail++] = root;
            root = root->left;
        }
    }
    if (!root) {
        printf("-1\n");
        free(q);
        return 0;
    }
    q[tail++] = root;
    if (!flag) for (int i=0;i<tail;i++) printf("%d ",q[i]->data);
    else for (int i=tail-1;i>=0;i--) printf("%d ",q[i]->data);
    printf("\n");
    free(q);    
    return 1;
} 

void postorder(node* root) {
    if (root == NULL) return;
    postorder(root->left);
    postorder(root->right);
    printf("%d ",root->data);
}

void avl_balance(node* root,int key) {
    while (root && root->data!=key) {
        if (root->data>key) root = root->left;
        else root = root->right;
    }
    if (root == NULL) {
        printf("-1\n");
        return;
    }
    printf("%d\n",balance(root));
}

node* delete(node* root,int key,int* l,int* r) {
    if (root == NULL) {
        return NULL;
    }
    if (root->data>key) root->left = delete(root->left,key,l,r);
    else if (root->data<key) root->right = delete(root->right,key,l,r);
    else {
        if (!root->left && !root->right) {
            free(root);
            return NULL;
        }
        if (root->left && root->right) {
            node* succ = root->right;
            while (succ->left) succ = succ->left;
            root->data = succ->data;
            root->right = delete(root->right,root->data,l,r);
        }
        else if (root->left) {
            node* temp = root->left;
            free(root);
            return temp;
        }
        else if (root->right) {
            node* temp = root->right;
            free(root);
            return temp;
        }
    }

    root->height = height(root);
    if (balance(root) > 1 && balance(root->left) >= 0) {
        (*r)++;
        return LLrotation(root);
    }
    else if (balance(root) < -1 && balance(root->right) <= 0) {
        (*l)++;
        return RRrotation(root);
    }
    else if (balance(root) > 1 && balance(root->left) < 0) {
        (*r)++;
        (*l)++;
        return LRrotation(root);
    }
    else if (balance(root) < -1 && balance(root->right) > 0) {
        (*r)++;
        (*l)++;
        return RLrotation(root);
    }
    return root;
}

int main() {
    node* root = NULL;
    int l=0,r = 0,key;
    char c =' ';
    while (c!='e') {
        scanf("%c",&c);
        if (c == 'i') {
            scanf("%d",&key);
            root = avl_insert(root,key,&l,&r);
        }
        else if (c == 'p') {
            postorder(root);
            printf("\n");
        }
        else if (c == 'f') {
            scanf("%d",&key);
            avl_search(root,key,0);
        }
        else if (c == 's') printf("%d %d\n",l,r);
        else if (c == 'b') {
            scanf("%d",&key);
            avl_balance(root,key);
        }
        else if (c == 'd') {
            scanf("%d",&key);
            if (avl_search(root,key,1)) root = delete(root,key,&l,&r);
        }
    }
}