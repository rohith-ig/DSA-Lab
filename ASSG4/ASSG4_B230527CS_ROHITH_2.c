#include<stdio.h>
#include<string.h>

struct node {
    int pid;
    int s;
    char name[100];
}typedef node;

int parent(int i) {
    return (i-1)/2;
}
void swap(node* a,node* b) {
    node temp = *a;
    *a = *b;
    *b = temp;
}
void display(node* heap,int size) {
    if (size == 0 ) {
        printf("-1\n");
        return;
    }
    for (int i=0;i<size;i++) printf("%d %d\n",heap[i].pid,heap[i].s);
}
int insert(int id,int s,char* name,node* heap,int* size) {
    strcpy(heap[*size].name,name);
    heap[(*size)].pid = id;
    heap[(*size)++].s = s;
    int ind = *size - 1;
    while (ind>0 && heap[parent(ind)].s>heap[ind].s) {
        swap(heap+(parent(ind)),heap+ind);
        ind = parent(ind);
    }
    for (int i=0;i<*size;i++) printf("%d ",heap[i].pid);
    printf("\n");
}

void heapify(node* heap,int i,int size) {
    int left = 2*i + 1;
    int right = 2*i + 2;
    int max = i;
    if (left<size && heap[left].s<heap[max].s) max = left; 
    if (right<size && heap[right].s<heap[max].s) max = right;
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
    printf("%d %s\n",heap[0].pid,heap[0].name   );
    heap[0] = heap[*size-1];
    (*size)--;
    heapify(heap,0,*size);
}
void query(int pid,node* heap,int size) {
    int flag = 0,j;
    for (int i = 0;i<size;i++) {
        if (heap[i].pid == pid) {
            flag = 1;
            j = i;
            break;
        }
    }
    if (!flag) {
        printf("-1\n");
        return;
    }  
    printf("%s %d\n",heap[j].name,heap[j].s);
}
void replace_key(node* heap,int size,int key,int new) {
    int flag = 0,j;
    for (int i = 0;i<size;i++) {
        if (heap[i].pid == key) {
            flag = 1;
            j = i;
            break;
        }
    }
    if (!flag) {
        printf("-1\n");
        return;
    }   
    int old = heap[j].s;
    heap[j].s = new;
    if (new < old ) {
        int ind = j;
        while (ind>0 && heap[parent(ind)].s>heap[ind].s) {
            swap(heap+(parent(ind)),heap+ind);
            ind = parent(ind);
        }
    }
    else heapify(heap,j,size);
    for (int i=0;i<size;i++) printf("%d ",heap[i].pid);
    printf("\n");
}
void mostsevere(node* heap,int size) {
    if (size == 0) {
        printf("-1\n");
        return;
    }
    node temp[1000];
    for (int i=0;i<size;i++) temp[i] = heap[i];
    int k = 3;
    while (k--) {
        printf("%d %s %d\n",temp[0].pid,temp[0].name,temp[0].s);
        temp[0] = temp[--size];
        heapify(temp,0,size);
    }
}
int main() {
    char c = ' ';
    int id;
    int p;
    char name[100];
    node heap[1000];
    int size = 0;
    while (c != 'g') {
        scanf("%c",&c);
        if (c == 'a') {
            scanf("%d %d %s",&id,&p,name);
            insert(id,p,name,heap,&size);
        }
        else if (c == 'b') schedule(heap,&size);
        else if (c == 'c') {
            scanf("%d %d",&id,&p);
            replace_key(heap,size,id,p);
        }
        else if (c == 'd') {
            scanf("%d",&id);
            query(id,heap,size);
        }
        else if (c == 'e') mostsevere(heap,size);
    }
}