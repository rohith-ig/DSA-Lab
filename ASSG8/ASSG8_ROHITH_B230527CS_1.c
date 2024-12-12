#include<stdio.h>
#include<String.h>

void kmp(char s[100],char t[100]) {
    int lps[100] = {0};
    int i=1,prevLPS=0,top = 0;
    int st;
    while (i < strlen(t)) {
        if (t[i] == t[prevLPS]) lps[i++] = ++prevLPS;    
        else if (!prevLPS) lps[i++] = 0;
        else prevLPS = lps[prevLPS-1];
    }
    i = 0;
    int j = 0;
    while (i < (strlen(s))) {
        if (s[i] == t[j]) {
            i++;
            j++;
        }
        else {
            if (!j) i++; 
            else j = lps[j-1];
        }
        if (j == strlen(t)) {
            st = (i - strlen(t));
            top++;
        }
    }
    if (!top) {
        printf("-1\n");
        return;
    }
    printf("%d %d",st,top);
}


int main() {
    char s[1000],t[1000],buffer[100];
    scanf("%s %s",s,t);
    kmp(s,t);
}