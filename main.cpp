#include<stdio.h>
#include<string.h>
#include<iostream>
// #include"date.h"

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

class people{    
    private:
        char name[100];
        int sex; // 0-female 1-male;
        int id;
        char password[100];

    public:
        void set_info(char name[],int sex,int id,char password[]){
            strcpy(this->name,name);
            this->sex = sex;
            this->id = id;
            strcpy(this->password,password);
        }

        char* get_name(){
            return this->name;
        }

        int get_sex(){
            return this->sex;
        }

        int get_id(){
            return this->id;
        }

        char* get_password(){
            return this->password;
        }

        void display_book(blist p){
            printf("%s %s %s %s %s %s\n",p->name,p->author,p->zone,p->isbn,p->io?"在馆":"出借",p->useable?"有效":"已移除");
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
        
        void display_disable_list(blist h){
            blist p = h->next;
            while(p!=NULL){
                if(!p->useable)
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
};

class admin : public people {
    private:
        static int num;
    public:
        int create_node(){
            return num++;
        }
        void set_info(char name[],int sex,int id,char password[]){
            people::set_info(name,sex,id,password);
        }
        int get_num(){
            return this->num;
        }

        int remove_book(blist h){
            display_useable_list(h);
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
            display_disable_list(h);
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
            blist q = h;
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
    
        void admin_menu(blist h){
            int sel = 0;
            int flag = 0;

            while(1){
                printf("管理员菜单\n");
                printf("1.显示所有书\n");
                printf("2.显示有效书\n");
                printf("3.根据书名查找\n");
                printf("4.根据作者查找\n");
                printf("5.根据专业领域查找\n");
                printf("6.录入新书\n");
                printf("7.移除书籍\n");
                printf("8.撤销移除\n");
                printf("9.修改书籍信息\n");
                printf("10.退出\n");
                printf("请输入数字选项:");
                scanf("%d",&sel);
                while(sel>10||sel<1){
                    printf("无该选项，请重新输入:");
                    scanf("%d",&sel);
                }
                switch(sel){
                    case 1:{
                        this->display_list(h);
                        break;
                    }
                    case 2:{
                        this->display_useable_list(h);
                        break;
                    }
                    case 3:{
                        this->search_by_name(h);
                        break;
                    }
                    case 4:{
                        this->search_by_author(h);
                        break;
                    }
                    case 5:{
                        this->search_by_zone(h);
                        break;
                    }
                    case 6:{
                        this->add_book(h);
                        break;
                    }
                    case 7:{
                        this->remove_book(h);
                        break;
                    }
                    case 8:{
                        this->revoke_book(h);
                        break;
                    }
                    case 9:{
                        this->change_book_info(h);
                        break;
                    }
                    case 10:{
                        flag = 1;
                        break;
                    }

                }
                printf("\n");
                if(flag) break;
            }

        }
};
int admin::num = 0;


class reader : public people {
    private:
        static int num;
        int book_num;
        blist borrow_list;
    public:
        int create_node(){
            book_num = 0;
            return num++;
        }
        void set_info(char name[],int sex,int id,char password[]){
            people::set_info(name,sex,id,password);
        }
        
        void set_booknum(int book_num){
            this->book_num = book_num;
        }

        int get_num(){
            return this->num;
        }

        int get_booknum(){
            return this->book_num;
        }

        void loadlist(FILE *fp,int booknum){
            blist p,q;
            char name[100];
            char author[100];
            char zone[100];
            char isbn[100];
            int io; // 0 - out & 1 - in
            int useable;

            this->borrow_list = (bnode*)malloc(sizeof(bnode));
            this->borrow_list->next = NULL;
            q = this->borrow_list;
            for(int i=0;i<booknum;i++){
                fscanf(fp,"%s%s%s%s%d%d",name,author,zone,isbn,&io,&useable);
                p = creatnode(name,author,zone,isbn,io,useable);
                q->next = p;
                q = p;
            }
        }

        void display_list(){
            blist p = this->borrow_list->next;
            while(p!=NULL){
                display_book(p);
                p=p->next;
            }
        }

        void store_list(FILE *fp){
            blist p = this->borrow_list->next;
            blist q;
            while(p!=NULL){
                fprintf(fp,"%s %s %s %s %d %d\n",p->name,p->author,p->zone,p->isbn,p->io,p->useable);
                q=p;
                p=p->next;
                // free(p);
            }
        }

        void state(){
            printf("借书数量:%d\n",this->book_num);
        }

        void change_password(){
            char new_password[100];
            printf("请输入新密码:");
            scanf("%s",new_password);
            this->set_info(this->get_name(),this->get_sex(),this->get_id(),new_password);
            printf("修改完成\n");

        }

        void add_book(blist new_book){
            blist p = this->borrow_list->next;
            blist q = this->borrow_list;
            while(p!=NULL){
                display_book(p);
                q = p;
                p = p->next;
            }
            char name[100];
            char author[100];
            char zone[100];
            char isbn[100];
            int io; // 0 - out & 1 - in
            int useable;
            strcpy(name,new_book->name);
            strcpy(author,new_book->author);
            strcpy(zone,new_book->zone);
            strcpy(isbn,new_book->isbn);
            
            p = creatnode(name,author,zone,isbn,0,1);
            q->next = p;
        }


        int borrow_book(blist h){
            char name[100];
            printf("请输入需要的书名:");
            scanf("%s",name);

            blist p = h->next;
            int flag = 0;
            int num = this->book_num;
            if(num>10){
                printf("借阅数量达到上限，借书失败\n");
                return flag;
            }
            while(p!=NULL){
                if(strcmp(p->name,name)==0&&p->useable&&p->io){
                    display_book(p);
                    p->io = 0;
                    this->add_book(p);
                    printf("借书成功!\n");
                    this->book_num++;
                    flag = 1;
                    break;
                }
                p=p->next;
            }
            if(flag==0) printf("无可借书\n");
            return flag;
        }

        void remove_book(char name[]){
            blist p = this->borrow_list;
            blist q;
            while(p!=NULL){
                if(strcmp(p->name,name)==0){
                    q->next = p->next;
                    free(p);
                    p = q->next;
                    break;
                }
                else {
                    q = p;
                    p = p->next;
                }        
            }
        }

        int return_book(blist h){
            char name[100];
            printf("请输入需要的书名:");
            scanf("%s",name);

            blist p = h->next;
            int flag = 0;
            while(p!=NULL){
                if(strcmp(p->name,name)==0&&p->useable&&!p->io){
                    display_book(p);
                    p->io = 1;
                    this->remove_book(name);
                    printf("还书成功!\n");
                    this->book_num--;
                    flag = 1;
                    break;
                }
                p=p->next;
            }
            if(flag==0) printf("无法还书\n");
            return flag;
        }

        void reader_menu(blist h){
            int sel = 0;
            int flag = 0;

            while(1){
                printf("读者菜单\n");
                printf("1.修改密码\n");
                printf("2.显示所有书\n");
                printf("3.根据书名查找\n");
                printf("4.根据作者查找\n");
                printf("5.根据专业领域查找\n");
                printf("6.借书\n");
                printf("7.还书\n");
                printf("8.查询借书情况\n");
                printf("9.退出\n");
                printf("请输入数字选项:");
                scanf("%d",&sel);
                while(sel>9||sel<1){
                    printf("无该选项，请重新输入:");
                    scanf("%d",&sel);
                }
                switch(sel){
                    case 1:{
                        this->change_password();
                        break;
                    }
                    case 2:{
                        this->display_useable_list(h);
                        break;
                    }
                    case 3:{
                        this->search_by_name(h);
                        break;
                    }
                    case 4:{
                        this->search_by_author(h);
                        break;
                    }
                    case 5:{
                        this->search_by_zone(h);
                        break;
                    }
                    case 6:{
                        this->borrow_book(h);
                        break;
                    }
                    case 7:{
                        this->return_book(h);
                        break;
                    }
                    case 8:{
                        this->state();
                        this->display_list();
                        break;
                    }
                    case 9:{
                        flag = 1;
                        break;
                    }

                }
                printf("\n");
                if(flag) break;
            }
        }
};
int reader::num = 0;


reader reader_arr[100];

class libsystem{
    public:
        admin arr[100];
        reader reader_arr[100];
        blist head;

        void load_reader(){
            FILE *fp = NULL;
            fp = fopen("reader","r");

            int i=0;
            char name[100];
            int sex;
            int id;
            char password[100];
            int booknum;

            while(fscanf(fp,"%s%d%d%s%d",name,&sex,&id,password,&booknum)!=EOF){
                this->reader_arr[i].create_node();
                this->reader_arr[i].set_info(name,sex,id,password);
                this->reader_arr[i].set_booknum(booknum);
                this->reader_arr[i].loadlist(fp,booknum);
                i++;
            }
            fclose(fp);
        }

        void store_reader(){
            FILE *fp = NULL;
            fp = fopen("reader","w");

            int n = this->reader_arr[0].get_num();
            for(int i=0;i<n;i++){
                fprintf(fp,"%s %d %d %s %d\n",reader_arr[i].get_name(),reader_arr[i].get_sex(),reader_arr[i].get_id(),reader_arr[i].get_password(),reader_arr[i].get_booknum());
                this->reader_arr[i].store_list(fp);
            }
            fclose(fp);
        }

        int login_reader(){
            int id;
            char password[100];
            printf("请输入学号:");
            scanf("%d",&id);
            printf("请输入密码:");
            scanf("%s",password);

            int n = this->reader_arr[0].get_num();
            int flag = 0;
            int sp = 0;
            for(int i=0;i<n;i++){
                if(this->reader_arr[i].get_id()==id){
                    if(strcmp(this->reader_arr[i].get_password(),password)==0){
                        printf("登录成功!\n\n");
                        flag = 1;
                        sp = i;
                    }
                    else{
                        printf("密码错误，请重试!\n\n");
                        flag = 2;
                        sp = -1;
                    }
                }
            }
            if(flag==0){
                printf("没有对应帐号!\n\n");
                sp = -2;
            }
            return sp;
        }

        int add_reader(){
            int sp = this->reader_arr[0].get_num();
            char name[100];
            int sex;
            int id;
            char password[100];
            printf("请输入姓名:");
            scanf("%s",name);
            printf("请输入性别(0-female or 1-male):");
            scanf("%d",&sex);
            printf("请输入学号:");
            scanf("%d",&id);
            printf("请输入密码:");
            scanf("%s",password);
            this->reader_arr[sp].create_node();
            this->reader_arr[sp].set_info(name,sex,id,password);
            printf("添加完成!\n\n");
            return 0;
        }

        void load_admin(){
            FILE *fp = NULL;
            fp = fopen("admin","r");

            int i=0;
            char name[100];
            int sex;
            int id;
            char password[100];

            while(fscanf(fp,"%s%d%d%s",name,&sex,&id,password)!=EOF){
                this->arr[i].create_node();
                this->arr[i].set_info(name,sex,id,password);
                i++;
            }
            fclose(fp);
        }

        void store_admin(){
            FILE *fp = NULL;
            fp = fopen("admin","w");

            int n = this->arr[0].get_num();
            for(int i=0;i<n;i++){
                fprintf(fp,"%s %d %d %s\n",arr[i].get_name(),arr[i].get_sex(),arr[i].get_id(),arr[i].get_password());
            }
            fclose(fp);
        }
        
        int login_admin(){
            int id;
            char password[100];
            printf("请输入学号:");
            scanf("%d",&id);
            printf("请输入密码:");
            scanf("%s",password);

            int n = this->arr[0].get_num();
            int flag = 0;
            int sp = 0;
            for(int i=0;i<n;i++){
                if(this->arr[i].get_id()==id){
                    if(strcmp(this->arr[i].get_password(),password)==0){
                        printf("登录成功!\n\n");
                        flag = 1;
                        sp = i;
                    }
                    else{
                        printf("密码错误，请重试!\n\n");
                        flag = 2;
                        sp = -1;
                    }
                }
            }
            if(flag==0){
                printf("没有对应帐号!\n\n");
                sp = -2;
            }
            return sp;
        }

        int add_admin(){
            int sp = this->arr[0].get_num();
            char name[100];
            int sex;
            int id;
            char password[100];
            printf("请输入姓名:");
            scanf("%s",name);
            printf("请输入性别(0-female or 1-male):");
            scanf("%d",&sex);
            printf("请输入学号:");
            scanf("%d",&id);
            printf("请输入密码:");
            scanf("%s",password);
            this->arr[sp].create_node();
            this->arr[sp].set_info(name,sex,id,password);
            printf("添加完成!\n\n");
            return 0;
        }

        void common_menu(){
            this->load_reader();
            this->load_admin();
            this->head = loadlist();
            int sel = 0;
            int flag = 0;
            // arr[0].display_list(this->head);
            while(1){
                printf("图书管理系统\n");
                printf("1.管理员登录\n");
                printf("2.管理员注册\n");
                printf("3.用户登录\n");
                printf("4.用户注册\n");
                printf("5.退出\n");
                printf("请输入数字选项:");
                scanf("%d",&sel);
                while(sel>5||sel<1){
                    printf("无该选项，请重新输入:");
                    scanf("%d",&sel);
                }
                switch(sel){
                    case 1:{
                        int sp = this->login_admin();
                        if(sp>=0)
                            arr[sp].admin_menu(this->head);
                        break;
                    }
                    case 2:{
                        this->add_admin();
                        break;
                    }
                    case 3:{
                        int sp = this->login_reader();
                        if(sp>=0) reader_arr[sp].reader_menu(this->head);
                        break;
                    }
                    case 4:{
                        this->add_reader();
                        break;
                    }
                    case 5:{
                        flag = 1;
                        break;
                    }
                    default:{
                        break;
                    }
                }
                if(flag) break;
            }
            this->store_reader();
            this->store_admin();
            storelist(this->head);
        }
};

int main(){
    libsystem s1;

    // char name[100]="nrt";
    // char password[100]="0000";
    // s1.load_admin();
    // s1.arr[0].create_node();
    // printf("%d",s1.arr[0].get_num());
    // s1.arr[0].set_info(name,1,1,password);

    // printf("%s\n", s1.arr[0].get_name());

    // s1.login_admin();
    // s1.add_admin();
    // s1.store_admin();
    s1.common_menu();
    
    printf("end\n");


    return 0;
}