#include<stdio.h>

struct node {
    int jid;
    int p;
}typedef node;

int parent(int i) {
    return (i-1)/2;
}
void swap(node* a,node* b) {
    node temp = *a;
    *a = *b;
    *b = temp;
}
int insert(int id,int p,node* heap,int* size) {
    heap[(*size)].jid = id;
    heap[(*size)++].p = p;
    int ind = *size - 1;
    while (ind>0 && heap[parent(ind)].p>heap[ind].p) {
        swap(heap+(parent(ind)),heap+ind);
        ind = parent(ind);
    }
}

void display(node* heap,int size) {
    if (size == 0 ) {
        printf("-1\n");
        return;
    }
    for (int i=0;i<size;i++) printf("%d %d\n",heap[i].jid,heap[i].p);
}

void heapify(node* heap,int i,int size) {
    int left = 2*i + 1;
    int right = 2*i + 2;
    int max = i;
    if (left<size && heap[left].p<heap[max].p) max = left; 
    if (right<size && heap[right].p<heap[max].p) max = right;
    if (max != i) {
        swap(heap+i,heap+max);
        heapify(heap,max,size);
    }
}

void schedule(node* heap,int* size) {
    if (*size == 0) {
        printf("-1\n");
        return;
    }
    printf("%d\n",heap[0].jid);
    heap[0] = heap[*size-1];
    (*size)--;
    heapify(heap,0,*size);
}
void replace_key(node* heap,int size,int key,int new) {
    int flag = 0,j;
    for (int i = 0;i<size;i++) {
        if (heap[i].jid == key) {
            flag = 1;
            j = i;
            break;
        }
    }
    if (!flag) {
        printf("-1\n");
        return;
    }   
    int old = heap[j].p;
    heap[j].p = new;
    if (new < old ) {
        int ind = j;
        while (ind>0 && heap[parent(ind)].p>heap[ind].p) {
            swap(heap+(parent(ind)),heap+ind);
            ind = parent(ind);
        }
    }
    else heapify(heap,j,size);
}
int main() {
    char c = ' ';
    int id;
    int p;
    node heap[1000];
    int size = 0;
    while (c != 'g') {
        scanf("%c",&c);
        if (c == 'a') {
            scanf("%d %d",&id,&p);
            insert(id,p,heap,&size);
        }
        else if (c == 'b') schedule(heap,&size);
        else if (c == 'c') printf("%d\n",size != 0? heap[0].jid : -1);
        else if (c == 'd') {
            scanf("%d %d",&id,&p);
            replace_key(heap,size,id,p);
        }
        else if (c == 'e') display(heap,size);
    }
}