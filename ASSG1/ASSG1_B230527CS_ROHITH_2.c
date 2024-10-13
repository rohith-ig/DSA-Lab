#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct node {
    int model;
    char name[100];
    int price;
    struct node *parent;
    struct node *left;
    struct node *right;
}typedef node; 

node* createnode(int model,char* name,int price) {
    node* y = (node*)malloc(sizeof(node));
    y->parent = NULL;
    y->left = NULL;
    y->right = NULL;
    y->model = model;
    y->price = price;
    strcpy(y->name,name);
    return y;
}

void insert(node** root,node* y) {
    if (*root == NULL) {
        *root = y;
        return;
    }
    node* temp = *root;
    node* p = NULL;
    while (temp!=NULL) {
        p = temp;
        if (temp->model<=y->model) temp = temp->right; 
        else temp = temp->left;
    }
    y->parent = p;
    if (p->model > y->model) p->left = y;
    else p->right = y;
}

node* search(node* root,int num) {
    while (root!=NULL && root->model!=num) {
        if (num>=root->model) root = root->right;
        else root = root->left;
    }
    return root;
}

void inorder(node* root) {
    if (root == NULL) return;
    inorder(root->left);
    printf("%d %s %d\n",root->model,root->name,root->price);
    inorder(root->right);
}
void preorder(node* root) {
    if (root == NULL) return;
    printf("%d %s %d\n",root->model,root->name,root->price);
    preorder(root->left);
    preorder(root->right);
}
void postorder(node* root) {
    if (root == NULL) return;
    postorder(root->left);
    postorder(root->right);
    printf("%d %s %d\n",root->model,root->name,root->price);
}
node* delete(node** p,node* root,node* y) {
    if (root == NULL) return NULL;
    if (y->model<root->model) root->left = delete(p,root->left,y);
    else if (y->model>root->model) root->right = delete(p,root->right,y);
    else {
        if (root->model == y->model) {
            if (!root->left && !root->right) {
                if (*p == root) *p = NULL;
                free(root);
                return NULL;
            }
            if (root->left && root->right) {
                node* x = root->right;
                while (x->left!=NULL) x = x->left;
                root->model = x->model;
                strcpy(root->name,x->name);
                root->price = x->price;
                root->right = delete(p,root->right,x);
            }
            else if (root->right) {
                root->model = root->right->model;
                strcpy(root->name,root->right->name);
                root->price = root->right->price;
                root->right = delete(p,root->right,root);
            }
            else if (root->left) {
                root->model = root->left->model;
                strcpy(root->name,root->left->name);
                root->price = root->left->price;
                root->left = delete(p,root->left,root);
            }
        }
    }
    return root;
}

void modify(node* root,int model,int newprice) {
    node* x = search(root,model);
    if (x == NULL) printf("-1\n");
    else {
        x->price = newprice;
        printf("%d %s %d\n",x->model,x->name,x->price);
    }
}

int main() {
    node* root = NULL,*x = NULL;
    char c = ' ';
    while (c!='e') {
        scanf(" %c",&c);
        int model,price;
        char name[100];
        switch (c) {
            case 'a' :
                scanf("%d %s %d",&model,name,&price);
                node* y = createnode(model,name,price);
                insert(&root,y);
                break;
            case 'd' :
                scanf("%d",&model);
                x = search(root,model);
                if (x == NULL) printf("-1\n");
                else {
                    printf("%d %s %d\n",x->model,x->name,x->price);
                    delete(&root,root,x);
                }
                break;
            case 's' :
                scanf("%d",&model);
                x = search(root,model);
                if (x == NULL) printf("-1\n");
                else printf("%d %s %d\n",x->model,x->name,x->price);
                break;
            case 'i' :
                inorder(root);
                break;
            case 'p' :
                preorder(root);
                break;
            case 't' :
                postorder(root);
                break;
            case 'm' :
                scanf("%d %d",&model,&price);
                modify(root,model,price);
                break;
            case '\n' :
                break;
            case 'e' :
                break;
            default :
                printf("Invalid Entry");
                break;
        }
    }
}

