#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

struct node {
    int data;
    struct node* left;
    struct node* right;
    int height;
}typedef node;

void preorder(node*);

node* createnode(int num) {
    node* y = (node*)malloc(sizeof(node));
    y->left = NULL;
    y->right = NULL;
    y->data = num;
    y->height = 0;
    return y;
}   

int max(int a,int b) {
    return a>b?a:b;
}

int balance(node* root) {
    int lh = root && root->left?root->left->height:-1;
    int rh = root && root->right?root->right->height:-1;
    return lh-rh;
}

int height(node* root) {
    int lh = root && root->left?root->left->height:-1;
    int rh = root && root->right?root->right->height:-1;
    return max(lh,rh)+1;
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

node* build_tree(char* str,int* i) {
    if (str[*i] == ' ') (*i)++;
    if (str[*i] == '\0' || str[*i] == ')') return NULL;
    int num = 0;
    while (isdigit(str[*i])) {
        num = num*10 + str[*i] - '0';
        (*i)++;
    }
    node* x = createnode(num);
    while (str[*i] == ' ') (*i)++;
    if (str[*i] == '(') {
        (*i)++;
        x->left = build_tree(str,i);
        if (str[*i] == ' ') (*i)++;
        if (str[*i] == ')') (*i)++;
    }
    if (str[*i] == ' ') (*i)++;
    if (str[*i] == '(') {
        (*i)++;
        x->right = build_tree(str,i);
        if (str[*i] == ' ') (*i)++;
        if (str[*i] == ')') (*i)++;
    }
    x->height = height(x);
    return x;
}

void inorder(node* root) {
    if (!root) return;
    inorder(root->left);
    printf("%d ",balance(root));
    inorder(root->right);
}

node* avl_insert(node* root,int key) {
    if (root == NULL) return createnode(key);
    if (root->data <= key) root->right = avl_insert(root->right,key);
    else root->left = avl_insert(root->left,key);
    root->height = height(root);
    if (balance(root) == 2 && balance(root->left) >= 0) 
        return LLrotation(root);
    if (balance(root) == -2 && balance(root->right) < 0) 
        return RRrotation(root);
    if (balance(root) == 2 && balance(root->left) < 0)    
        return LRrotation(root);
    if (balance(root) == -2 && balance(root->right) >= 0) 
        return RLrotation(root);
    return root;
}

node* search(node* root,int key) {
    if (root == NULL) return NULL;
    if (root->data>key) return search(root->left,key);
    else if (root->data<key) return search(root->right,key);
    else return root;
}

void paranthesis(node* root) {
    if (root == NULL) {
        return;
    }
    if (!root->left && !root->right) {
        printf("%d ",root->data);
        return;
    }
    printf("%d ",root->data);
    if (root->left || root->right) {
        printf("( ");
        paranthesis(root->left);
        printf(") ( ");
        paranthesis(root->right);
        printf(") ");
    }
}

int sumHelp(node* root) {
    int sum = 0;
    if (root == NULL) return 0;
    sum += root->data;
    sum += sumHelp(root->left);
    sum += sumHelp(root->right);
    return sum;
}

void subtreeSum(node* root,int n) {
    node* x = search(root,n);
    if (x) {
        printf("%d ",sumHelp(x));
        paranthesis(x);
        printf("\n");
    }
    else printf("-1\n");
}

node* delete(node* root,int key) {
    if (!root) return NULL;
    if (key>root->data) root->right = delete(root->right,key);
    else if (key<root->data) root->left = delete(root->left,key);
    else {
        if (!root->left && !root->right) {
            free(root);
            return NULL;
        }
        else if (!root->right) {
            node* temp = root->left;
            free(root);
            return temp;
        }
        else if (!root->left) {
            node* temp = root->right;
            free(root);
            return temp;
        }
        else if (root->left && root->right) {
            node* succ = root->right;
            while (succ->left) succ = succ->left;
            root->data = succ->data;
            root->right = delete(root->right,root->data);
        }
    }

    root->height = height(root);

    if (balance(root)>1 && balance(root->left)>=0) return LLrotation(root);
    if (balance(root)>1 && balance(root->left)<0) return LRrotation(root);
    if (balance(root)<-1 && balance(root->right)>=0) return RLrotation(root);
    if (balance(root)<-1 && balance(root->right)<0) return RRrotation(root);

    return root;

}

 node* rangeDelete(node* root,int l,int u,int *flag) {
    if (!root) return NULL;
    root->left = rangeDelete(root->left,l,u,flag);
    root->right = rangeDelete(root->right,l,u,flag);
    if (root->data>=l && root->data<=u) {
        (*flag)++;
        root = delete(root,root->data);
        return root;
    }
    root->height = height(root);

    if (balance(root)>1 && balance(root->left)>=0) return LLrotation(root);
    if (balance(root)>1 && balance(root->left)<0) return LRrotation(root);
    if (balance(root)<-1 && balance(root->right)>=0) return RLrotation(root);
    if (balance(root)<-1 && balance(root->right)<0) return RRrotation(root);

    return root;
} 

void preorder(node* root) {
    if (!root) return;
    printf("%d ",root->data);
    preorder(root->left);
    preorder(root->right);
}

void successor(node* root,int n) {
    node* x = search(root,n);
    if (x) {
        node* succ = NULL;
        if (x->right) {
            succ = x->right;
            while (succ->left)  succ = succ->left;
        }
        else {
            node* temp = root;
            while (temp != x) {
                if (temp->data>x->data) {
                    succ = temp;
                    temp = temp->left;
                }
                else temp = temp->right;
            }
        }
        if (succ) { 
            node* temp = root;
            while (temp != succ) {
                printf("%d ",temp->data);
                if (temp->data>succ->data) temp = temp->left;
                else temp = temp->right;
            }
            printf("%d\n",succ->data);
        }
        else printf("%d\n",height(root));
    }
    else printf("%d\n",height(root));
}
int abs(int a) {
    return a<0?-a:a;
}
void findClosest(node *root,int n) {
    node* x = search(root,n);
    if (!x) {
        printf("-1\n");
        return;
    }
    node *succ = NULL, *pred = NULL;
    if (x->right) {
        succ = x->right;
        while (succ->left) succ = succ->left;
    }
    else {
        node* temp = root;
        while (temp != x) {
            if (temp->data>x->data) {
                succ = temp;
                temp = temp->left;
            }
            else temp = temp->right;
        }
    }
    if (x->left) {
        pred = x->left;
        while (pred->right) pred = pred->right;
    }
    else {
        node* temp = root;
        while (temp != x) {
            if (temp->data<x->data) {
                pred = temp;
                temp = temp->right;
            }
            else temp = temp->left;
        }
    }
    if (!succ && !pred) {
        printf("-1\n");
        return;
    }
    if (!succ) printf("%d\n",pred->data);
    else if (!pred) printf("%d\n",succ->data);
    else {
        int d1 = abs(x->data - succ->data);
        int d2 = abs(x->data - pred->data);
        if (d1 == d2) {
            printf("%d\n",succ->data>pred->data?pred->data:succ->data);
            return;
        }
        printf("%d\n",d1>d2?pred->data:succ->data);
    }
}

int main() {
    char c;
    char str[100000];
    node* root = NULL;
    gets(str);
    int i = 0;
    root = build_tree(str,&i);
    int n,a,b;
    while (c != 'g') {
        scanf("%c",&c);
        if (c == 'a') {
            char str2[10000];
            gets(str2);
            int j = 0;
            while (str2[j] != '\0') {
                int num = 0;
                while (str2[j] == ' ') j++;
                if (str2[j] == '\0') break;
                while (isdigit(str2[j])) {
                    num = num*10 + str2[j] - '0';
                    j++;
                } 
                root = avl_insert(root,num);
            }
            paranthesis(root);
            printf("\n");
        }
        else if (c == 'b') {
            scanf("%d %d",&a,&b);
            int flag = 0;
            root = rangeDelete(root,a,b,&flag);
            if (!flag) printf("-1\n");
            else {
                printf("%d ",flag);
                preorder(root);
            }
            printf("\n");
        }
        else if (c == 'c') {
            scanf("%d",&n);
            successor(root,n);
        }
        else if (c == 'd') {
            scanf("%d",&n);
            subtreeSum(root,n);
        }
        else if (c == 'e') {
            scanf("%d",&n);
            findClosest(root,n);
        }
        else if (c == 'g') break;
    }
    return 0;
}