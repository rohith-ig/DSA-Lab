#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
struct node {
    int key;
    struct node* next;
    int weight;
}typedef node;  
void takeEdges(node** arr,int n) {
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
                y->weight = 0;
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
}

void takeWeights(node** arr,int n) {
    node* t;
    for (int k=0;k<n;k++) {
        char s[100];
        fgets(s,100,stdin);
        s[strlen(s)-1] = '\0';
        int i = 0;
        int f = 1;
        node* t;
        while (s[i]) {
            if (s[i]==' ') i++;
            int num = 0;
            while (isdigit(s[i])) {
                num = num * 10;
                num += s[i] - '0';
                i++;
            }
            if (f) {
                t = arr[num];
                if (!t) continue;
                f = 0;
            }
            else {
                if (t->next) {
                    t = t->next;
                    t->weight = num;
                }
            }
        }
    }
}
int parent(int i) {
    return (i-1)/2;
}
void swap(int* a,int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}
void add(int* minHeap,int* x,int el,int* dist) {
    minHeap[(*x)++] = el;
    int curr = (*x)-1;
    while (curr>0 && dist[parent(curr)] > dist[curr]) {
        swap(minHeap+curr,minHeap+parent(curr));
        curr = parent(curr);
    }
}
void heapify(int* heap,int i,int p,int* dist) {
    int left = 2*i+1;
    int right = 2*i+2;
    int min = i;
    if (left<p && dist[left]<dist[min]) min = left;
    if (right<p && dist[right]<dist[min]) min = right;
    if (min != i) {
        swap(heap+i,heap+min);
        heapify(heap,min,p,dist);
    }
}
int extractMin(int* heap,int* n,int* dist) {
    int min = heap[0];
    heap[0] = heap[--(*n)];
    heapify(heap,0,*n,dist);
    return min;
}

void shortestPath(node** arr,int n,int s) {
    int* heap = (int*)malloc(sizeof(int)*n);
    int heapSize = 0;
    int* dist = (int*)malloc(sizeof(int)*n);
    for (int i=0;i<=n;i++) dist[i] = __INT_MAX__;
    add(heap,&heapSize,s,dist);
    dist[s] = 0;
    while (heapSize != 0) {
        int curr = extractMin(heap,&heapSize,dist);
        node* c = arr[curr]->next;
        while (c) {
            if (dist[c->key] > dist[curr] + c->weight) {
                dist[c->key] = dist[curr] + c->weight;
                add(heap,&heapSize,c->key,dist);
            }
            c = c->next;
        }
    }
    for (int i=0;i<=n;i++) if (arr[i]) printf("%d ",dist[i]);
    printf("\n");
}

int main() {
    int n,s;
    scanf("%d",&n);
    getchar();
    node** arr = (node**)calloc((n+1),sizeof(node*));
    takeEdges(arr,n);
    takeWeights(arr,n);
    scanf("%d",&s);
    shortestPath(arr,n,s);
    return 0;
}