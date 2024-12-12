#include<stdio.h>
#include<stdlib.h>

struct node {
    int key;
    int weight;
    int marker;
    struct node* next; 
}typedef node;

struct edge {
    int a;
    int b;
    int weight;
}typedef edge;

node* createnode(int key) {
    node* y = (node*)malloc(sizeof(node));
    y->next = NULL;
    y->key = key;
    y->weight = 0;
    y->marker = 0;
    return y;
}

edge findMin(node** graph,int n) {
    int min = __INT_MAX__;
    int x=-1,y=-1;
    for (int i=0;i<n;i++) {
        node* temp = graph[i]->next;
        while (temp) {
            if (temp->weight < min && !temp->marker) {
                min = temp->weight;
                x = i;
                y = temp->key;
            }
            temp = temp->next;
        }
    }
    if (min != __INT_MAX__) {
        node* c = graph[x];
        while (c->key != y) c = c->next;
        c->marker = 1;
        c = graph[y];
        while (c->key != x) c= c->next;
        c->marker = 1;
    }
    edge r;
    r.a = x;
    r.b = y;
    r.weight = min;
    return r; 
}

int find_parent(int* parent,int x) {
    if (parent[x] == x) return x;
    return find_parent(parent,parent[x]);
}

int union_add(int* parent,edge e) {
    int rootx = find_parent(parent,e.a);
    int rooty = find_parent(parent,e.b);
    if (rootx != rooty) {
        parent[rooty] = rootx;
        return 1;
    }
    else {
        return 0;
    }
}
void kruskal(node** graph,int n) {
    int* vis = (int*)calloc(n,sizeof(int));
    int sum = 0;
    int parent[n];
    for (int i=0;i<n;i++) parent[i] = i;
    while (1) {
        edge x = findMin(graph,n);
        if (x.weight == __INT_MAX__)break; 
        if (union_add(parent,x)) {
            sum += x.weight;
        }
    } 
    printf("%d",sum);
}

int main() {
    int n;
    scanf("%d",&n);
    node** graph = (node**)calloc(n,sizeof(node*));
    for (int i=0;i<n;i++) {
        int f = 0,p;
        while (1) {
            int temp;
            scanf("%d",&temp);
            if (!f) {
                p = temp;
                graph[p] = createnode(p);
                f = 1;
            }
            else {
                node* c = graph[p];
                while (c->next) c = c->next;
                c->next = createnode(temp);
            }
            if (getchar() == '\n') break;
        }
    }
    for (int i=0;i<n;i++) {
        int f = 0;
        node* p;
        while (1) {
            int temp;
            scanf("%d",&temp);
            if (!f) {
                p = graph[temp];
                f = 1;
            }
            else {
                p = p->next;
                p->weight = temp;
            }
            if (getchar() == '\n') break;
        }
    }
    
    kruskal(graph,n);
    return 0; 
}