#include<stdio.h>

int n;

int findMin(int vis[n],int dist[n]) {
    int min = __INT_MAX__;
    int r = -1;
    for (int i=0;i<n;i++) {
        if (!vis[i]) if (dist[i]<min) {
            min = dist[i];
            r = i;
        }
    }
    return r;
}

void prim(int graph[n][n],int in,int s) {
    int vis[n];
    int par[n];
    int dist[n];
    for (int i=0;i<n;i++) {
        vis[i] = 0;
        par[i] = -1;
        dist[i] = __INT_MAX__;
    }
    if (n == 0) {
        printf("No vertice\n");
        return;
    }
    dist[s] = 0;
    while (findMin(vis,dist) != -1) {
        int x = findMin(vis,dist);
        for (int i=0;i<n;i++) {
            if (graph[x][i] && !vis[i]) {
                if (dist[i]>graph[x][i]) {
                    dist[i] = graph[x][i];
                    par[i] = x;
                }
            }
        }
        vis[x] = 1;
        if (par[x]!=-1 && in) printf("%d %d (%d) ",par[x],x,graph[par[x]][x]);
    }
    int sum = 0;
    for (int i=0;i<n;i++) sum += dist[i];
    if (!in) printf("%d",sum);
    printf("\n");
}

int main() {
    scanf("%d",&n);
    int graph[n][n];
    for (int i=0;i<n;i++) {
        for (int j=0;j<n;j++) {
            scanf("%d",&graph[i][j]);
        }
    } 
    char c = ' ';
    while (c != 'e') {
        scanf("%c",&c);
        if (c == 's') {
            int p;
            scanf("%d",&p);
            prim(graph,1,p);
        }
        if (c == 'b') prim(graph,0,0);
    }
}