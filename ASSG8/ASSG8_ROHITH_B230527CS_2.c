#include<stdio.h>
#include<String.h>

void bayermoore(char s[1000],char t[1000]) {
    int ct[200],pos;
    for (int i=0;i<200;i++) ct[i] = strlen(t); 
    for (int i=0;i<strlen(t);i++) {
       ct[t[i]] = strlen(t) - i - 1; 
    }
    int i = strlen(t)-1,k=0;
    while (i<strlen(s)) {
        int j = strlen(t)-1;
        while (j>=0 && s[i] == t[j]) {
            j--;
            i--;
        }
        if (j == -1) {
            if (!k) printf("%d\n",i+1);
            k++;
            i += 2 * strlen(t);

        }
        else if (!j) {
            j = strlen(t) - 1;
            i += strlen(t);
        }
        else i += ct[s[i]];
    }
    if (!k) printf("-1\n");
}

int main() {
    char s[1000],t[1000],buffer[100];
    while (1) {
        fgets(buffer, sizeof(buffer), stdin);
        if (strcmp(buffer, "\n") == 0) {
            break;
        }
        strcat(s, buffer);
    }
    fgets(t,100,stdin);
    t[strlen(t)-1] = '\0';
    bayermoore(s,t);
}