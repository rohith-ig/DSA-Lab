#include<stdio.h>
#include<stdlib.h>

struct node {
    int key;
}typedef node;

node* createnode(int key) {
    node* y = (node*)malloc(sizeof(node));
    y->key = key;
    return y;
}

void linear(int* arr,int n,int m) {
    node** tab = (node**)calloc(m,sizeof(node*)); 
    int c = 0; 
    for (int i = 0;i<n;i++) {
        int j = 0;
        int h = ((arr[i]%m)+j)%m;
        if (!tab[h]) {
            tab[h] = createnode(arr[i]);
            printf("%d ",h);
        }
        else {
            while (tab[h]) {
                j++;
                h = ((arr[i]%m)+j)%m;
            }
            tab[h] = createnode(arr[i]);
            printf("%d ",h);
        } 
        c += j;
    }
    printf("\n%d\n",c);
}

void quadratic(int* arr,int n,int m) {
    node** tab = (node**)calloc(m,sizeof(node*)); 
    int c = 0; 
    for (int i = 0;i<n;i++) {
        int j = 0;
        int h = ((arr[i]%m)+(j*j))%m;
        if (!tab[h]) {
            tab[h] = createnode(arr[i]);
            printf("%d ",h);
        }
        else {
            while (tab[h]) {
                j++;
                h = ((arr[i]%m)+(j*j))%m;
            }
            tab[h] = createnode(arr[i]);
            printf("%d ",h);
        } 
        c += j;
    }
    printf("\n%d\n",c);
}

int isPrime(int x) {
    if (x == 2) return 1;
    for (int i=2;i<x;i++) if (x%i == 0) return 0;
    return 1;
}

void double_hash(int* arr,int n,int m) {
    node** tab = (node**)calloc(m,sizeof(node*)); 
    int c = 0,r = 0; 
    for (int i =m-1;i>0;i--) {
        if (isPrime(i)) {
            r = i;
            break;
        }
    }
    for (int i = 0;i<n;i++) {
        int j = 0;
        int h = ((arr[i]%m)+j*(r - (arr[i]%r)))%m;
        if (!tab[h]) {
            tab[h] = createnode(arr[i]);
            printf("%d ",h);
        }
        else {
            while (tab[h]) {
                j++;
                h = ((arr[i]%m)+j*(r - (arr[i]%r)))%m;
            }
            tab[h] = createnode(arr[i]);
            printf("%d ",h);
        } 
        c += j;
    }
    printf("\n%d\n",c);
}


int main() {
    int m,n;
    scanf("%d %d",&m,&n);
    int arr[n];
    for (int i=0;i<n;i++) scanf("%d",arr+i);
    char c = ' ';
    while (c != 'd') {
        scanf("%c",&c);
        if (c == 'a') linear(arr,n,m);
        if (c == 'b') quadratic(arr,n,m);
        if (c == 'c') double_hash(arr,n,m);
     }
    return 0;
}