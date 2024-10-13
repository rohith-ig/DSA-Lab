#include<stdio.h>
#include<stdlib.h>

void dfs_conn(int** arr,int n,int s,int** col) {
    (*col)[s] = 1;
    for (int i=0;i<n;i++) if (arr[s][i] && !(*col)[i]) dfs_conn(arr,n,i,col);
}

void connected(int** arr,int n) {
    int* col = (int*)malloc(sizeof(int)*n);
    for (int i = 0;i < n;i++) col[i] = 0;
    int c = 0;
    for (int i = 0;i<n;i++) {
        if (!col[i]) {
            dfs_conn(arr,n,i,&col);
            c++;
        }
    }
    printf("%d\n",c);
}

void dfs_art(int** arr,int n,int s,int** ap,int** vis,int** disc,int** parent,int** low,int* time) {
    int children = 0;
    (*vis)[s] = 1;
    (*disc)[s] = ++(*time);
    (*low)[s] = (*disc)[s]; 
    for (int i = 0;i<n;i++) {
        if (arr[s][i]) {
            if (!(*vis)[i]) {
                children++;
                (*parent)[i] = s;
                dfs_art(arr,n,i,ap,vis,disc,parent,low,time);
                (*low)[s] = (*low)[s] < (*low)[i] ? (*low)[s] : (*low)[i];
                if ((*parent)[s] == -1 && children > 1) (*ap)[s] = 1;
                if ((*parent)[s]!=-1 && (*low)[i] >= (*disc)[s]) (*ap)[s] = 1;     
            }
            else if ((*parent)[s] != i) {
                (*low)[s] = (*low)[s] < (*disc)[i] ? (*low)[s] : (*disc)[i];
            }
        }
    }

}

void articulation(int** arr,int n) {
    int* vis = (int*)calloc(n,sizeof(int));
    int* disc = (int*)malloc(sizeof(int)*n);
    int* parent = (int*)malloc(sizeof(int)*n);
    int* ap = (int*)calloc(n,sizeof(int));
    int* low = (int*)malloc(sizeof(int)*n);
    for (int i = 0;i<n;i++) {
        low[i] = __INT_MAX__;
        parent[i] = -1;
    }
    int time = 0;
    for (int i = 0;i<n;i++) {
        if (!vis[i]) {
            dfs_art(arr,n,i,&ap,&vis,&disc,&parent,&low,&time);
        }
    }
    int count = 0;
    for (int i = 0;i<n;i++) if (ap[i]) count++;
    printf("%d\n",count);
}

void dfs_count(int** arr,int n,int** vis,int s,int* count) {
    (*vis)[s] = 1;
    (*count)++;
    for (int i = 0;i<n;i++) {
        if (arr[s][i] && !(*vis)[i]) dfs_count(arr,n,vis,i,count);
    }
}
void count_conn(int** arr,int n) {
    int* vis = (int*)calloc(n,sizeof(int));
    int* num = (int*)malloc(sizeof(int));
    int k = 0;
    for (int i = 0;i < n;i++) {
        if (!vis[i]) {
            int count = 0;
            dfs_count(arr,n,&vis,i,&count);
            num[k++] = count;
            for (int j=i-1;j>=1;j--) {
                if (num[j] < num[j-1]) {
                    int temp = num[j];
                    num[j] = num[j-1];
                    num[j-1] = temp;
                }
            } 
        }
    }
    for (int j=0;j<k;j++) printf("%d ",num[j]);
    printf("\n");
}

void dfs_bridge(int** arr,int n,int s,int** vis,int** disc,int** low,int** parent,int* time,int* count) {
    (*vis)[s] = 1;
    (*disc)[s] = (++(*time));
    (*low)[s] = (*disc)[s];
    for (int i = 0;i<n;i++) {
        if (arr[s][i]) {
            if (!(*vis)[i]) {
                (*parent)[i] = s;
                dfs_bridge(arr,n,i,vis,disc,low,parent,time,count);
                (*low)[s] = (*low)[s] < (*low)[i] ? (*low)[s] : (*low)[i];
                if ((*low)[i] > (*disc)[s]) {
                    (*count)++;
                }
            }
            else {
                if ((*parent)[s] != i) (*low)[s] = (*low)[s] < (*disc)[i] ? (*low)[s] : (*disc)[i] ;
            }
        }
    }
} 

void bridges(int** arr,int n) {
    int* vis = (int*)calloc(n,sizeof(int));
    int* disc = (int*)malloc(sizeof(int)*n);
    int* parent = (int*)malloc(sizeof(int)*n);
    int* low = (int*)malloc(sizeof(int)*n);
    for (int i = 0;i<n;i++) {
        low[i] = __INT_MAX__;
        parent[i] = -1;
    }
    int time = 0;
    int count = 0;
    for (int i = 0;i<n;i++) {
        if (!vis[i]) {
            dfs_bridge(arr,n,i,&vis,&disc,&low,&parent,&time,&count);
        }
    }
    printf("%d\n",count);
}

int main() {
        int n;
        scanf("%d",&n);
        int** arr = (int**)malloc(sizeof(int*)*5);
         for (int i = 0; i < n; i++) {
            arr[i] = (int*)malloc(sizeof(int) * n); 
        }
        for (int i=0;i<n;i++) {
            for (int j = 0;j<n;j++) scanf("%d",&arr[i][j]);
        }
        char c = ' ';
        while (c!='x') {
            scanf("%c",&c);
            if (c == 'a') connected(arr,n);
            else if (c == 'b') count_conn(arr,n);
            else if (c == 'c') bridges(arr,n);
            else if (c == 'd') articulation(arr,n);
        }
        return 0;
}