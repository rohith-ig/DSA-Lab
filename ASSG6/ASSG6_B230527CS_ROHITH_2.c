#include<stdlib.h>
#include<stdio.h>

void warshall(int** arr,int n) {
    int** dist = (int**)malloc(sizeof(int*)*n);
    for (int i=0;i<n;i++) dist[i] = (int*)malloc(sizeof(int)*n);
    for (int i=0;i<n;i++) {
        for (int j=0;j<n;j++) {
            dist[i][j] = arr[i][j];
        }
    }
    for (int k=0;k<n;k++) {
        for (int i=0;i<n;i++) {
            for (int j=0;j<n;j++) {
                if (dist[i][k] != __INT_MAX__ && dist[k][j] != __INT_MAX__)
                    if (dist[i][j] > dist[i][k] + dist[k][j]) dist[i][j] = dist[i][k] + dist[k][j];
            }
        }
    }
    for (int i=0;i<n;i++) {
        for (int j=0;j<n;j++) {
            if (dist[i][j] != __INT_MAX__) printf("%d ",dist[i][j]);
            else printf("-1 ");
        }
        printf("\n");
    }
}

int main() {
    int n;
    scanf("%d",&n);
    int** arr = (int**)malloc(sizeof(int*)*n);
    for (int i=0;i<n;i++) arr[i] = (int*)malloc(sizeof(int)*n);
    for (int i=0;i<n;i++) {
        for (int j=0;j<n;j++) {
            scanf("%d",&arr[i][j]);
            if (arr[i][j] == -1) arr[i][j] = __INT_MAX__;
        }
    }
    warshall(arr,n);
    return 0;
}