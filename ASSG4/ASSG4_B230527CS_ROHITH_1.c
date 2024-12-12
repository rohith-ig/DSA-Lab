#include<stdio.h>
#include<math.h>

int parent(int i) {
    return (i-1)/2;
}
void display(int* heap,int size) {
    for (int i=0;i<size;i++) printf("%d ",heap[i]);
    printf("\n");
}
void swap(int* a,int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}
void heapify(int* heap,int i,int size) {
    int left = 2*i + 1;
    int right = 2*i + 2;
    int max = i;
    if (left<size && heap[left]>heap[max]) max = left; 
    if (right<size && heap[right]>heap[max]) max = right;
    if (max != i) {
        swap(heap+i,heap+max);
        heapify(heap,max,size);
    }
}

void extract(int* heap,int* size) {
    if (*size == 0) {
        printf("-1\n");
        return;
    }
    printf("%d ",heap[0]);
    heap[0] = heap[*size-1];
    (*size)--;
    heapify(heap,0,*size);
    display(heap,*size);
}

void klarge(int* heap,int size,int key) {
    if (key > size) {
        printf("-1\n");
        return;
    }
    int temp[1000];
    for (int i=0;i<size;i++) temp[i] = heap[i];
    while (--key) {
        temp[0] = temp[size-1];
        size--;
        heapify(temp,0,size);
    }
    printf("%d\n",temp[0]);
} 

void delete(int* heap,int* size,int key) {
    int flag = 0,j;
    for (int i = 0;i<*size;i++) {
        if (heap[i] == key) {
            flag = 1;
            j = i;
            break;
        }
    }
    if (!flag) {
        printf("-1\n");
        return;
    }
    heap[j] = heap[*size-1];
    (*size)--;
    heapify(heap,j,*size);
    if (*size == 0) {
        printf("0\n");
        return;
    }
    display(heap,*size);
}

int insert(int key,int* heap,int* size) {
    heap[(*size)++] = key;
    int ind = *size - 1;
    while (ind>0 && heap[parent(ind)]<heap[ind]) {
        swap(heap+(parent(ind)),heap+ind);
        ind = parent(ind);
    }
}

void replace_key(int* heap,int size,int key,int new) {
    int flag = 0,j;
    for (int i = 0;i<size;i++) {
        if (heap[i] == key) {
            flag = 1;
            j = i;
            break;
        }
    }
    if (!flag) {
        printf("%d\n",(key-new)>0?key-new:new-key);
        return;
    }   
    heap[j] = new;
    if (new > key ) {
        int ind = j;
        while (ind>0 && heap[parent(ind)]<heap[ind]) {
            swap(heap+(parent(ind)),heap+ind);
            ind = parent(ind);
        }
    }
    else heapify(heap,j,size);
    display(heap,size);
}

int main() {
    int heap[1000];
    int size = 0;
    char c = ' ';
    int key;
    while (c != 'g') {
        scanf("%c",&c);
        if (c == 'a') {
            scanf("%d",&key);
            insert(key,heap,&size);
        }
        else if (c == 'b') {
            if (size == 0) printf("-1\n");
            else printf("%d\n",heap[0]);
        }
        else if (c == 'c') extract(heap,&size);
        else if (c == 'd') {
            scanf("%d",&key);
            klarge(heap,size,key);
        }
        else if (c == 'e') {
            scanf("%d",&key);
            delete(heap,&size,key);
        }
        else if (c == 'f') {
            int new;
            scanf("%d %d",&key,&new);
            replace_key(heap,size,key,new);
        }
    }
    return 0;
}