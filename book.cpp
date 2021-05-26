#include<stdio.h>
#include<string.h>
#include<iostream>
using namespace std;

typedef struct booknode{
    char name[100];
    char author[100];
    char zone[100];
    char isbn[100];
    int io; // 0 - out & 1 - in
    int useable; 
    struct booknode *next;
}bnode,*blist;

blist creatnode(char name[],char author[],char zone[],char isbn[],int io,int useable){
    blist p;
    p=(bnode*)malloc(sizeof(bnode));
    if(!p) return 0;
    p->next = NULL;
    strcpy(p->name,name);
    strcpy(p->author,author);
    strcpy(p->zone,zone);
    strcpy(p->isbn,isbn);
    p->io = io;
    p->useable = useable;
    return p;
}

blist loadlist(){
    FILE *fp = NULL;
    fp = fopen("booklist","r");
    blist head,p,q;
    char name[100];
    char author[100];
    char zone[100];
    char isbn[100];
    int io; // 0 - out & 1 - in
    int useable;

    head = (bnode*)malloc(sizeof(bnode));
    if(!head)return 0;
    head->next = NULL;
    q = head;
    while(fscanf(fp,"%s%s%s%s%d%d",name,author,zone,isbn,&io,&useable)!=EOF){
        p = creatnode(name,author,zone,isbn,io,useable);
        q->next = p;
        q = p;
    }
    fclose(fp);
    return head;
}
 
void display_book(blist p){
    printf("%s %s %s %s %d %d\n",p->name,p->author,p->zone,p->isbn,p->io,p->useable);
}

void display_list(blist h){
    blist p = h->next;
    while(p!=NULL){
        display_book(p);
        p=p->next;
    }
}

void display_useable_list(blist h){
    blist p = h->next;
    while(p!=NULL){
        if(p->useable)
            display_book(p);
        p=p->next;
    }
}

int search_by_name(blist h){
    char name[100];
    printf("请输入需要的书名:");
    scanf("%s",name);

    blist p = h->next;
    int flag = 0;
    while(p!=NULL){
        if(strcmp(p->name,name)==0&&p->useable){
            display_book(p);
            flag = 1;
        }
        p=p->next;
    }
    if(flag==0) printf("查无此书\n");
    return flag;
}

int search_by_author(blist h){
    char author[100];
    printf("请输入需要的作者:");
    scanf("%s",author);

    blist p = h->next;
    int flag = 0;
    while(p!=NULL){
        if(strcmp(p->author,author)==0&&p->useable){
            display_book(p);
            flag = 1;
        }
        p=p->next;
    }
    if(flag==0) printf("查无此书\n");
    return flag;
}

int search_by_zone(blist h){
    char zone[100];
    printf("请输入需要的专业领域:");
    scanf("%s",zone);

    blist p = h->next;
    int flag = 0;
    while(p!=NULL){
        if(strcmp(p->zone,zone)==0&&p->useable){
            display_book(p);
            flag = 1;
        }
        p=p->next;
    }
    if(flag==0) printf("查无此书\n");
    return flag;
}

int remove_book(blist h){
    char name[100];
    printf("请输入想要移除的书名:");
    scanf("%s",name);

    blist p = h->next;
    int flag = 0;
    int sel = 0;
    while(p!=NULL){
        if(strcmp(p->name,name)==0&&p->useable){
            display_book(p);
            printf("输入1确认移除:");
            scanf("%d",&sel);
            if(sel){
                p->useable = 0;
            } 
            printf("移除成功\n");
            flag = 1;
        }
        p=p->next;
    }
    if(flag==0) printf("查无此书\n");
    return flag;
}

int revoke_book(blist h){
    char name[100];
    printf("请输入想要撤销移除的书名:");
    scanf("%s",name);

    blist p = h->next;
    int flag = 0;
    int sel = 0;
    while(p!=NULL){
        if(strcmp(p->name,name)==0&&!p->useable){
            display_book(p);
            printf("输入1确认撤销:");
            scanf("%d",&sel);
            if(sel){
                p->useable = 1;
            } 
            printf("撤销成功\n");
            flag = 1;
        }
        p=p->next;
    }
    if(flag==0) printf("查无此书\n");
    return flag;

}

int change_book_info(blist h){
    char name_in[100];
    printf("请输入需要的书名:");
    scanf("%s",name_in);

    blist p = h->next;
    blist q;
    char name[100];
    char author[100];
    char zone[100];
    char isbn[100];
    int io; // 0 - out & 1 - in

    int flag = 0;
    int sel = 0;
    while(p!=NULL){
        if(strcmp(p->name,name_in)==0&&p->useable){
            display_book(p);
            
            printf("是否改变书名(1 or 0):");
            scanf("%d",&sel);
            if(sel){
                printf("请输入新书名:");
                scanf("%s",name);
                strcpy(p->name,name);
            }

            printf("是否改变作者(1 or 0):");
            scanf("%d",&sel);
            if(sel){
                printf("请输入新作者:");
                scanf("%s",author);
                strcpy(p->author,author);
            }

            printf("是否改变专业领域(1 or 0):");
            scanf("%d",&sel);
            if(sel){
                printf("请输入新专业领域:");
                scanf("%s",zone);
                strcpy(p->zone,zone);
            }

            printf("是否改变图书编号(1 or 0):");
            scanf("%d",&sel);
            if(sel){
                printf("请输入新ISBN:");
                scanf("%s",isbn);
                strcpy(p->isbn,isbn);
            }

            printf("是否改变流通状态(1 or 0):");
            scanf("%d",&sel);
            if(sel){
                printf("请选择流通状态:");
                scanf("%d",&io);
                p->io = io;
            }
            flag = 1;
        }
        p=p->next;
    }
    if(flag==0) printf("查无此书\n");
    return flag;
}

void add_book(blist h){
    blist p = h->next;
    blist q;
    while(p!=NULL){
        // display_book(p);
        q = p;
        p = p->next;
    }
    char name[100];
    char author[100];
    char zone[100];
    char isbn[100];
    int io; // 0 - out & 1 - in
    int useable;
    printf("请输入新书名:");
    scanf("%s",name);
    printf("请输入新作者:");
    scanf("%s",author);
    printf("请输入新专业领域:");
    scanf("%s",zone);
    printf("请输入新ISBN:");
    scanf("%s",isbn);
    printf("请选择流通状态:");
    scanf("%d",&io);
    p = creatnode(name,author,zone,isbn,io,1);
    q->next = p;
}

void storelist(blist h){
    FILE *fp = NULL;
    fp = fopen("booklist","w");
    blist p = h->next;
    blist q;
    while(p!=NULL){
        fprintf(fp,"%s %s %s %s %d %d\n",p->name,p->author,p->zone,p->isbn,p->io,p->useable);
        q = p;
        p = p->next;
        free(q);
    }
    // fprintf(fp,"end");
    fclose(fp);
}


int main (){
    blist head;
    blist remove_temp_head;
    head = loadlist();
    // print(head);
    char name[100];
    char author[100];
    char zone[100];
    // scanf("%s",name);
    // change_book_info(name,head);
    display_list(head);
    // search_by_name(head);
    // search_by_author(head);
    // search_by_zone(head);
    // change_book_info(head);
    // revoke_book(head);
    // add_book(head);
    // remove_book(head);
    storelist(head);
    printf("end\n");

    return  0;
}