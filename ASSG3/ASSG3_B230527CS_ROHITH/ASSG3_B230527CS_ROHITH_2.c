#include<stdio.h>
#include<stdlib.h>


struct node {
    int key;
    struct node* next;
}typedef node;

node* createnode(int key) {
    node* y = (node*)malloc(sizeof(node));
    y->key = key;
    y->next = NULL;
    return y;
}

int hash_function(int key,int n) {
    return key%n;
}

void insert(node** arr,int key,int n) {
    int h = hash_function(key,n);   
    node* temp = arr[h];
    node* x = createnode(key);
    node* y = NULL;
    if (!temp) {
        arr[h] = x;
        return;
    }
    else {
        while (temp) {
            if (temp->key == key) {
                printf("-1\n");
                return;
            }
            if (temp->key>key) {
                if (!y) {
                    arr[h] = x;
                    x->next = temp;
                }
                else {
                    y->next = x;
                    x->next = temp;
                }
                return;
            }
            y = temp;
            temp = temp->next;
        }
        y->next = x;
    }
} 

void print(node** arr,int key,int n) {
    if (key>=n) {
        printf("-1\n");
        return;
    }
    node* temp = arr[key];
    if (!temp) printf("-1\n");
    else {
        while (temp) {
            printf("%d ",temp->key);
            temp = temp->next;
        }
        printf("\n");
    }
}

void search(int key,node** arr,int n) {
    int h = hash_function(key,n);
    if (h>=n) {
        printf("-1\n");
        return;
    }
    node* temp = arr[h];
    if (!temp) printf("-1\n");
    else {
        int i = 0;
        while (temp) {
            i++;
            if (temp->key == key) {
                printf("%d %d\n",h,i);
                return;
            }
            temp = temp->next;
        } 
        printf("-1\n");
    }
}

void delete(node** arr,int key,int n){
    int h = hash_function(key,n);
    node* temp = arr[h];
    if (!temp) printf("-1\n");
    else {
        int i = 0;
        node* y = NULL;
        while (temp) {
            i++;
            if (temp->key == key) {
                printf("%d %d\n",h,i);
                if (!y) arr[h] = temp->next;
                else y->next = temp->next;
                free(temp);
                return;
            }
            y = temp;
            temp = temp->next;
        } 
        printf("-1\n");
    }
}

void update(node** arr,int key1,int key2,int n) {
    int h = hash_function(key1,n);
    node* temp = arr[h];
    if (!temp) printf("-1\n");
    else {
        int i = 0;
        node* y = NULL;
        int hx = hash_function(key2,n);
        node* p = arr[hx];
        int f = 0;
        while (p) {
            if (p->key == key2) {
                f = 1;
                break;
            }
            p = p->next;
        }
        if (f) {
            printf("-1\n");
            return;
        }
        while (temp) {
            i++;
            if (temp->key == key1) {
                insert(arr,key2,n);
                printf("%d %d\n",h,i);
                if (!y) arr[h] = temp->next;
                else y->next = temp->next;
                free(temp);
                return;
            }
            y = temp;
            temp = temp->next;
        } 
        printf("-1\n");
    }
}


int main() {
    int n,key;
    scanf("%d",&n);
    node** arr = (node**)calloc(n,sizeof(node*));
    char c = ' ';
    while (c!='f') {
        scanf("%c",&c);
        if (c == 'a') {
            scanf("%d",&key);
            insert(arr,key,n);
        }
        else if (c == 'b') {
            scanf("%d",&key);
            search(key,arr,n);
        }
        else if (c == 'c') {
            scanf("%d",&key);
            delete(arr,key,n);
        }
        else if (c == 'd'){
            int key1;
            scanf("%d %d",&key,&key1);
            update(arr,key,key1,n);
        }
        else if (c == 'e') {
            scanf("%d",&key);
            print(arr,key,n);
        }
    }
}