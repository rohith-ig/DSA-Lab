#include<stdio.h>
#include<stdlib.h>
#include<math.h>

struct node {
    int data;
    struct node* left;
    struct node* right;
}typedef node;

struct qnode {
    node* data;
    struct qnode* next;
}typedef qnode;

struct llnode {
    int data;
    struct llnode* next;
}typedef llnode;

node* createnode(int key) {
    node* y = (node*)malloc(sizeof(node));
    y->data = key;
    y->left = NULL;
    y->right = NULL;
    return y;
}

qnode* createqnode(node* x) {
    qnode* y = (qnode*)malloc(sizeof(qnode));
    y->next = NULL;
    y->data = x;
    return y;
}

int linear(int* arr, int key, int n) {
    for (int i = 0;i < n;i++) if (arr[i] == key) return i;
}

node* buildtree(int* i, int* ino, int* pre, int j, int k, int n) {
    if (j > k) return NULL;
    node* root = createnode(pre[(*i)++]);
    root->left = buildtree(i, ino, pre, j, linear(ino, root->data, n) - 1, n);
    root->right = buildtree(i, ino, pre, linear(ino, root->data, n) + 1, k, n);
    return root;
}

void enq(qnode** head, qnode** tail, node* x) {
    qnode* y = createqnode(x);
    if (*head == NULL && *tail == NULL) {
        *head = y;
        *tail = y;
        return;
    }
    (*tail)->next = y;
    *tail = y;
}

node* deq(qnode** head, qnode** tail) {
    if (*head == NULL) return NULL;
    qnode* temp = (*head);
    *head = (*head)->next;
    if (*head == NULL) *tail = NULL;
    node* x = temp->data;
    free(temp);
    return x;
}

int size(qnode* head) {
    int sum = 0;
    while (head != NULL) {
        sum++;
        head = head->next;
    }
    return sum;
}

void addbeg(llnode** head, int x) {
    llnode* temp = (llnode*)malloc(sizeof(llnode));
    temp->data = x;
    temp->next = NULL;
    if (*head == NULL) {
        *head = temp;
        return;
    }
    temp->next = *head;
    *head = temp;
}

void addend(llnode** head, int x) {
    llnode* temp = (llnode*)malloc(sizeof(llnode));
    temp->data = x;
    temp->next = NULL;
    if (*head == NULL) {
        *head = temp;
        return;
    }
    llnode* temp1 = *head;
    while (temp1->next != NULL) temp1 = temp1->next;
    temp1->next = temp;
}


/* void zigzag(node* root,int n) {
    node** que = (node**)malloc(sizeof(node*)*(n+1));
    int head = 0;
    int tail = 0;
    int level = 1;
    enqueue(root,que,&head,&tail,n);
    while (head!=tail) {
        int no = tail-head;
        for (int i=tail-1;i>=head;i--) {
            node* current = que[i];
            if (level%2==0) {
                if (current->right!=NULL) enqueue(current->right,que,&head,&tail,n);
                if (current->left!=NULL) enqueue(current->left,que,&head,&tail,n);
            }
            else {
                if (current->left!=NULL) enqueue(current->left,que,&head,&tail,n);
                if (current->right!=NULL) enqueue(current->right,que,&head,&tail,n);
            }
        }
        while(no--) {
            node* current = dequeue(que,&head,&tail);
            printf("%d ",current->data);
        }
        level++;
    }
} */

void zigzag(node* root) {
    qnode* head = NULL;
    qnode* tail = NULL;
    llnode* h = NULL;
    int flag = 0;
    enq(&head, &tail, root);
    while (head) {
        int ncl = size(head);
        while (ncl--) {
            node* x = deq(&head, &tail);
            if (flag == 1) addend(&h, x->data);
            else addbeg(&h, x->data);
            if (x->left != NULL) enq(&head, &tail, x->left);
            if (x->right != NULL) enq(&head, &tail, x->right);
        }
        flag = !flag;
        while (h != NULL) {
            llnode* temp = h;
            printf("%d ", h->data);
            h = h->next;
            free(temp);
        }
    }
}

void levelmax(node* root) {
    qnode* head = NULL;
    qnode* tail = NULL;
    enq(&head, &tail, root);
    while (head) {
        int ncl = size(head);
        int max = head->data->data;
        while (ncl--) {
            node* x = deq(&head, &tail);
            if (max < x->data) max = x->data;
            if (x->left != NULL) enq(&head, &tail, x->left);
            if (x->right != NULL) enq(&head, &tail, x->right);
        }
        printf("%d ", max);
    }
}

int rightLeafSum(node* root) {
    if (root == NULL) return 0;
    if (root->right != NULL && root->right->left == NULL && root->right->right == NULL) {
        return root->right->data + rightLeafSum(root->left);
    }
    int x = rightLeafSum(root->left);
    int y = rightLeafSum(root->right);
    return x + y;
}

void postorder(node* root) {
    if (!root) return;
    postorder(root->left);
    postorder(root->right);
    printf("%d ", root->data);
}

int height(node* root) {
    if (root == NULL) return 0;
    int lh = height(root->left);
    int rh = height(root->right);
    return fmax(lh, rh) + 1;
}

void diameter(node* root, int* max) {
    if (root == NULL) return;
    int lh = height(root->left);
    int rh = height(root->right);
    *max = fmax(*max, lh + rh + 1);
    diameter(root->left,max);
    diameter(root->right,max);
}

int main() {
    char c;
    int n;
    scanf("%d", &n);
    int* inorder = (int*)malloc(sizeof(int) * n);
    int* preorder = (int*)malloc(sizeof(int) * n);
    for (int i = 0;i < n;i++) scanf("%d", inorder + i);
    for (int i = 0;i < n;i++) scanf("%d", preorder + i);
    int i = 0;
    node* root = buildtree(&i, inorder, preorder, 0, n - 1, n);
    while (c != 'e') {
        scanf(" %c", &c);
        if (c == 'p') {
            postorder(root);
            printf("\n");
        }
        else if (c == 'z') {
            zigzag(root);
            printf("\n");
        }
        else if (c == 'm') {
            levelmax(root);
            printf("\n");
        }
        else if (c == 'd') {
            int d = 0;
            diameter(root, &d);
            printf("%d\n", d);
        }
        else if (c == 's') printf("%d\n", rightLeafSum(root));
        else continue;
    }
    return 0;
}