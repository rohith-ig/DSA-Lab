#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

struct node {
    char name[100];
    char rolln[100];
    int age;
    struct node* next;
}typedef node;

node* createnode(char* name,char* roll,int age) {
    node* y = (node*)malloc(sizeof(node));
    strcpy(y->name,name);
    strcpy(y->rolln,roll);
    y->age = age;
    y->next = NULL;
    return y;
}

int hash_function(char* name,int age) {
    int sum = 0;
    for (int i=0;i<strlen(name);i++) sum += (int)name[i];
    sum += age;
    return sum%4;
}

void group_index(node** arr,char* name) {
    for (int i=0;i<4;i++) {
        node* temp = arr[i];
        while (temp) {
            if (!strcmp(temp->name,name)) {
                printf("%d\n",i);
                return;
            }
            temp = temp->next;
        }
    }
    printf("-1\n");
}

void swaps(char* s1,char* s2) {
    char temp[100];
    strcpy(temp,s1);
    strcpy(s1,s2);
    strcpy(s2,temp);
}

void group_count(node** arr,int k) {
    if (k<4) {
        node* temp = arr[k];
        int a = 0;
        while (temp) {
            a++;
            temp = temp->next;
        }
        printf("%d ",a);
        temp = arr[k];
        while (temp && temp->next) {
            node* temp2 = temp->next;
            node* min = temp;
            while (temp2) {
                if (strcmp(min->name,temp2->name)>0) min = temp2;
                temp2 = temp2->next;
            }
            swaps(temp->name,min->name);
            swaps(temp->rolln,min->rolln);
            int tempx = temp->age;
            temp->age = min->age;
            min->age = tempx;
            temp = temp->next;
        }
        temp = arr[k];
        while (temp) {
            printf("%s ",temp->name);
            temp = temp->next;
        }
    }
    else printf("-1");
    printf("\n"); 
}

void group_listbranch(node** arr,int n,char* roll) {
    node* temp = arr[n];
    int f = 0;
    while (temp) {
        if (tolower(temp->rolln[strlen(temp->rolln)-2]) == tolower(roll[0]) && tolower(temp->rolln[strlen(temp->rolln)-1]) == tolower(roll[1])) {
            printf("%s",temp->name);
            f = 1;
        }
        temp = temp->next;
    }
    if (!f) printf("-1");
    printf("\n");
}

void studentBranch(node** arr,char* roll) {
    for (int i=0;i<4;i++) {
        node* temp = arr[i];
        while (temp) {
            if (!strcmp(temp->rolln,roll)) {
                printf("%s %d %c%c\n",temp->name,temp->age,temp->rolln[strlen(temp->rolln)-2],temp->rolln[strlen(temp->rolln)-1]);
                return;
            }
            temp = temp->next;
        }
    }
    printf("-1\n");
}

void group_transfer(node** arr,int s,int d,char *roll) {
    node* dest = arr[d];
    while (dest && dest->next) dest = dest->next;
    int f = 0;
    node* temp = arr[s];
    node* y = NULL;
    while (temp) {
        if (tolower(temp->rolln[strlen(temp->rolln)-2]) == tolower(roll[0]) && tolower(temp->rolln[strlen(temp->rolln)-1]) == tolower(roll[1])) {
            f++;
            if (y)  y->next = temp->next;
            else arr[s] = temp->next;
            if (dest) dest->next = temp;
            else arr[d] = temp;
            dest = temp;
            temp = temp->next;
            dest->next = NULL;
        }
        else {
            y = temp;
            temp = temp->next;
        }
    }
    printf("%d\n",f);
}


int main() {
    char temp[1000];
    char name[100];
    char roll[100];
    int age;
    int n;
    node** arr = (node**)calloc(4,sizeof(node*));
    scanf("%d",&n);
    char c;
    getchar();
    while (n--) {
        scanf("%s %s %d[^\n]",name,roll,&age);
        node* x = createnode(name,roll,age);
        int h = hash_function(name,age);
        if (!arr[h]) arr[h] = x;
        else {
            node* temp = arr[h];
            while (temp->next) temp = temp->next;
            temp->next = x;
        }
    }
    while (c!='f') {
        scanf("%c",&c);
        if (c == 'a') {
            scanf(" %s",name);
            group_index(arr,name);
        }
        else if (c == 'b') {
            scanf("%d",&n);
            group_count(arr,n);
        }
        else if (c == 'c') {
            scanf("%d %s",&n,roll);
            group_listbranch(arr,n,roll);
        }
        else if (c == 'd') {
            scanf("%s",roll);
            studentBranch(arr,roll);
        }
        else if (c == 'e') {
            int s,d;
            scanf("%d %d %s",&s,&d,roll);
            group_transfer(arr,d,s,roll);
        }
    }   
    return 0;
}