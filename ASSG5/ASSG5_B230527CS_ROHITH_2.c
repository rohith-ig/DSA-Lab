#include<stdio.h>
#include<stdlib.h>

int detectCycle(int** arr,int** col,int n,int s) {
    int q[n];
    int parent[n];
    int head = 0;
    int tail = 0;
    q[tail++] = s;
    parent[s] = -1;
    while (head != tail) {
        int curr = q[head++];
        (*col)[curr] = 1;
        for (int i = 0;i < n;i++) {
            if (arr[curr][i]) {
                if (!(*col)[i]) {
                    q[tail++] = i;
                    parent[i] = curr;
                }   
                else if (i != parent[curr]) return 1;
            }
        }
    }
    return 0;
}

void detectCycleH(int** arr,int n) {
    int* col = (int*)malloc(sizeof(int)*n);
    for (int i = 0;i<n;i++) col[i] = 0;
    int s = detectCycle(arr,&col,n,0);
    for (int i = 1;i < n;i++) if (!col[i]) s = s || detectCycle(arr,&col,n,i);
    if (s) printf("1\n");
    else printf("-1\n");
}

int isBipartite(int** arr,int** col,int n,int s) {
    int q[n];
    int head = 0;
    int tail = 0;
    int colour[n];
    q[tail++] = s;
    colour[s] = 1;
    while (head != tail) {
        int curr = q[head++];
        (*col)[curr] = 1; 
        for (int i = 0;i<n;i++) {
            if (arr[curr][i]) {
                if (!(*col)[i]) {
                    if (colour[curr]) colour[i] = 0;
                    else colour[i] = 1;
                    q[tail++] = i;
                }
                else {
                    if (colour[i] == colour[curr]) return 0;
                }
            } 
        } 
    }
    return 1;
}

void isBipartiteH(int** arr,int n) {
    int* col = (int*)malloc(sizeof(int)*n);
    for (int i = 0;i<n;i++) col[i] = 0;
    int s = isBipartite(arr,&col,n,0);
    for (int i = 1;i < n;i++) if (!col[i]) s = s && isBipartite(arr,&col,n,i);
    if (s) printf("1\n");
    else printf("-1\n");

}

void isTree(int** arr,int n) {
    int* col = (int*)malloc(sizeof(int)*n);
    for (int i = 0;i<n;i++) col[i] = 0;
    int s = detectCycle(arr,&col,n,0);
    for (int i = 1;i<n;i++) {
        if (!col[i]) {
            printf("-1\n");
            return;
        }
    }
    if (s) {
        printf("-1\n");
        return;
    } 
    printf("1\n");
}
int main() {
        int n;
        scanf("%d",&n);
        int** arr = (int**)malloc(sizeof(int*)*5);
         for (int i = 0; i < n; i++) {
            arr[i] = (int*)malloc(sizeof(int) * n); // Allocate each row
        }
        for (int i=0;i<n;i++) {
            for (int j = 0;j<n;j++) scanf("%d",&arr[i][j]);
        }
        char c = ' ';
        while (c != 'x') {
            scanf("%c",&c);
            if (c == 'a') isBipartiteH(arr,n);
            else if (c == 'b') detectCycleH(arr,n);
            else if (c == 'c') isTree(arr,n);
        }
        return 0;
}