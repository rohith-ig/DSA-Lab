#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
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

void dfs_dag(node** arr,int s,int* vis,int* rec,int* c) {
    (vis)[s] = 1;
    (rec)[s] = 1;
    node* t = arr[s]->next;
    while (t) {
        if (!(vis)[t->key]) dfs_dag(arr,t->key,vis,rec,c);
        else if ((rec)[t->key]) (*c) = 1;
        t = t->next;
    }   
    (rec)[s] = 0;
}

void dag(node** arr,int n) {
    int* vis = (int*)calloc((n+1),sizeof(int));
    int* rec = (int*)calloc((n+1),sizeof(int));
    int c = 0;
    for (int i=0;i<n;i++) {
        if (arr[i] && !vis[i]) dfs_dag(arr,i,vis,rec,&c);
    }
    if (c) printf("-1\n");
    else printf("1\n");
}

void dfs_first(node** arr,int s,int* vis,int* stack,int* x) {
    vis[s] = 1;
    node* t = arr[s]->next;
    while(t) {
        if (!vis[t->key]) dfs_first(arr,t->key,vis,stack,x);
        t = t->next;
    }
    stack[(*x)++] = s;
}
void dfs_second(node** trans,int s,int* vis) {
    vis[s] = 1;
    node* t = trans[s]->next;
    while(t) {
        if (!vis[t->key]) dfs_second(trans,t->key,vis);
        t = t->next;
    }
}
void conn(node** arr,int n) {
    node** trans = (node**)calloc(n+1,sizeof(node*));
    for (int i=0;i<=n;i++) {
        if (arr[i]) {
            node* temp = arr[i]->next;;
            if (!trans[i]) trans[i] = createnode(i); 
            while (temp) {
                if (!trans[temp->key]) trans[temp->key] = createnode(temp->key);
                node* t = trans[temp->key];
                while (t->next) t = t->next;
                t->next = createnode(i);
                temp = temp->next;
            }
        }
    }
    int* stack = (int*)malloc(sizeof(int)*(n+1));
    int stackSize = 0;
    int* vis = (int*)calloc(n+1,sizeof(int));
    for (int i=0;i<=n;i++) {
        if (arr[i] && !vis[i]) dfs_first(arr,i,vis,stack,&stackSize);
    }
    for (int i=0;i<=n;i++) vis[i] = 0;
    int count = 0;
    while (stackSize!=0) {
        int x = stack[--stackSize];
        if (!vis[x]) {
            count++;
            dfs_second(trans,x,vis);
        }
    } 
    printf("%d\n",count);
}

int main() {
    int n,e;
    scanf("%d %d",&n,&e);
    getchar();
    node** arr = (node**)calloc((n+1),sizeof(node*));
    for (int i=0;i<n;i++) {
        char s[100];
        fgets(s,100,stdin);
        s[strlen(s)-1] = '\0';
        int j = 0;
        int flag = 1;
        while (j < strlen(s)) {
            node* y = (node*)malloc(sizeof(node));
            y->next = NULL;
            int key = 0;
            while (s[j] == ' ') j++;
            while (isdigit(s[j])) {
                key = key*10 + s[j] - '0';
                j++;
            }
            int main;
            y->key = key;
            if (flag) {
                arr[key] = y;
                main = key;
                flag = 0;
            }
            else {
                node* t = arr[main];
                while (t->next) t = t->next;
                t->next = y;
            }
        }
    }
    char c = ' ';
    while (c!='x') {
        scanf("%c",&c);
        if (c == 'a') dag(arr,n);
        else if (c == 'b') conn(arr,n);
    }
    return 0;
}