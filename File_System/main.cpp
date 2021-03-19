#include"FileOperate.h"
#include"DiskOperate.h"
//#include <iostream>
#include <stdio.h>
#include <string.h>
//using namespace std;
int key=1;//key=0为root
//输出帮助
void help();

int main()
{
    sysusrs users;
    users.usrnum=2;
    users.usrmap[0]=1;
    users.usrmap[1]=1;
    strcpy(users.infos[0].usrname,"root");
    strcpy(users.infos[0].usrpwd,"123456");
    strcpy(users.infos[1].usrname,"lyh");
    strcpy(users.infos[1].usrpwd,"");

    //初始化系统
    initSystem();
    //创建根目录
    initRootDir();

    //help();
    printf("\n***welcome to the designed linux shell!***\n\n");
    printf("input the password,or no root!\n");
    printf("password:");
    char password[60];
    scanf("%s",password);
    if(strcmp(password, users.infos[0].usrpwd) != 0){
        printf("pwd wrong,no root.\n\n");
        printf("%s@linux:\\>",users.infos[1].usrname);
    }else{
        printf("pwd correct\n\n");
        printf("%s@linux:\\#",users.infos[0].usrname);
        key=0;
    }
    char command[10];
    scanf("%s", command);
    while(strcmp(command, "quit") != 0)
    {
        if(strcmp(command, "ls") == 0)//列出目录下所有文件
        {
            showDir();
            //printf("ls\n");
        }else if(strcmp(command, "help") == 0)//帮助
        {
            help();
        }else if(strcmp(command, "cd") == 0)//切换目录
        {
            char name[60];
            scanf("%s", name);
            changeDir(name);
        }else if(strcmp(command, "pwd") == 0)//显示目录
        {
            printf("%s\n", getPath());
        }else if(strcmp(command, "mkdir") == 0)//创建目录
        {
            char name[60];
            scanf("%s", name);
            creatDir(name);
        }else if(strcmp(command, "rmdir") == 0)//删除目录
        {
            char name[60];
            scanf("%s", name);
            deleteDir(name);
        }else if(strcmp(command, "mv") == 0)//修改文件或者目录名
        {
            char oldname[60];
            scanf("%s", oldname);
            char newname[60];
            scanf("%s", newname);
            changeName(oldname, newname);
        }else if(strcmp(command, "touch") == 0)//创建文件
        {
            char name[60];
            scanf("%s", name);
            int fileSize;
            scanf("%d", &fileSize);
            creatFile(name, fileSize);
        }else if(strcmp(command, "rm") == 0)//删除文件
        {
            char name[60];
            scanf("%s", name);
            deleteFile(name);
        }else if(strcmp(command, "read") == 0)//读取文件
        {
            char name[60];
            scanf("%s", name);
            int length;
            scanf("%d", &length);
            
        }else if(strcmp(command, "reread") == 0)//重设读指针为起点
        {
            char name[60];
            scanf("%s", name);
            int length;
            scanf("%d", &length);
           
        }else if(strcmp(command, "write") == 0)//写文件,只支持从末尾写入
        {
            char name[60];
            scanf("%s", name);
            char content[1024];
            scanf("%s", content);
           
            write(name, content);
            
        }else if(strcmp(command, "rewrite") == 0)//重新写文件
        {
            char name[60];
            scanf("%s", name);
            char content[1024];
            scanf("%s", content);
            
            rewrite(name, content);
            
        }else if(strcmp(command, "cp") == 0)//重新写文件
        {
            char file1name[60];
            scanf("%s", file1name);
            char file2name[60];
            scanf("%s", file2name);
            file_cp(file1name,file2name);
            
        }else if(strcmp(command, "useradd") == 0)//root下添加用户
        {
            char usrname[60];
            scanf("%s", usrname);
            char password[60];
            scanf("%s", password);
            if(key==0){
                //考虑重名情况
                int i;
                for(i=0;i<100;i++){
                    if(strcmp(users.infos[i].usrname,usrname)==0){
                        printf("can not add same name user.\n");
                        return -1;
                    }
                }
                for(i=0;i<100;i++){
                    if(users.usrmap[i]!=1){
                        strcpy(users.infos[i].usrname,usrname);
                        strcpy(users.infos[i].usrpwd,password);
                        users.usrmap[i]=1;
                        users.usrnum++;
                        break;
                    }
                }
                printf("user add success.\n");
            }
            else{
                printf("no root,can not add user.\n");
            }
        }else if(strcmp(command, "userdel") == 0)//root下删除用户
        {
            char usrname[60];
            scanf("%s", usrname);
            if(key==0){
                int i;
                for(i=2;i<100;i++){
                    if(strcmp(users.infos[i].usrname,usrname)==0){
                        strcpy(users.infos[i].usrname,"");
                        strcpy(users.infos[i].usrpwd,"");
                        users.usrmap[i]=0;
                        users.usrnum--;
                        break;
                    }else{
                        printf("user not found.\n");
                    }
                }
            }
            else{
                printf("no root,can not del user.\n");
            }
        }else if(strcmp(command, "userchange") == 0)//root下改变用户
        {
            char usrname[60];
            scanf("%s", usrname);
            if(key==0){
                int i;
                for(i=0;i<100;i++){
                    if(strcmp(users.infos[i].usrname,usrname)==0){
                        key=i;
                        printf("change user success.\n");
                        break;
                    }
                }
                if(i==100){
                    printf("user not found.\n");
                }
            }
            else{
                printf("no root,can not change user.\n");
            }
        }else if(strcmp(command, "userlist") == 0)//root下改变用户
        {
            if(key==0){
                printf("USERS_NAME_LIST:\n");
                for(int i=0;i<100;i++){
                    if(users.usrmap[i]==1){
                    printf("%s\n",users.infos[i].usrname);
                    }
                }
            }else{
                printf("no root,can not list users.\n");
            }
        }else if(strcmp(command, "sudo") == 0)//root下改变用户
        {
            if(key!=0){
                printf("input the root password:");
                char password[60];
                scanf("%s",password);
                if(strcmp(password,users.infos[0].usrpwd)==0){
                    printf("root login success.\n");
                    key=0;
                }else{
                    printf("password wrong.\n");
                }
            }else{
                printf("root already.\n");
            }
        }
        else
        {
            printf("command error\n");
        }
        if(key==0){
            printf("%s@linux:%s#", users.infos[0].usrname,getPath());
            scanf("%s", command);
        }else{
            printf("%s@linux:%s>", users.infos[key].usrname,getPath());
            scanf("%s", command);
        }
        
    }
    exitSystem();

    return 0;
}
void help()
{
    printf("\n*******************************************\n");
    printf("目录操作命令：\n");
    printf("1.ls                            #显示当前目录中的具体信息\n");
    printf("2.pwd                           #定位当前目录位置\n");
    printf("3.cd <目录名>                    #切换目录\n");
    printf("4.mkdir <目录名>                 #创建目录\n");
    printf("5.rmdir <目录名>                 #删除目录\n");
    printf("6.mv <目录名> <新目录名>          #重命名目录\n");
    printf("*******************************************\n");
    printf("\n*******************************************\n");
    printf("文件操作命令：\n");
    printf("1.mv <文件名> <新文件名>          #重命名文件\n");
    printf("2.touch <文件名> <文件大小>(KB)   #创建文件\n");
    printf("3.rm <文件名>                    #删除文件\n");
    printf("4.read <文件名> <数据长度>(字节)   #读取文件数据(从前次读取位置开始读取)\n");
    printf("5.reread <文件名> <数据长度>(字节) #读取文件数据(从文件数据开头开始读取)\n");
    printf("6.write <文件名> <写入的内容>      #写入数据到文件(从文件数据末尾开始写入)\n");
    printf("7.rewrite <文件名> <写入的内容>    #写入数据到文件(从文件数据开头重新写入)\n");
    printf("8.cp <文件名1> <文件名2>          #将文件1中数据复制到文件2中\n");
    printf("*******************************************\n");
    printf("\n*******************************************\n");
    printf("用户管理操作命令：\n");
    printf("1.useradd <用户名> <密码>         #添加用户(需要root权限)\n");
    printf("2.userdel <用户名>               #删除用户(需要root权限)\n");
    printf("3.userchange <用户名>            #改变当前用户(需要root权限)\n");
    printf("4.userlist                      #显示所有用户名信息(需要root权限)\n");
    printf("5.sudo                          #申请root权限\n");
    printf("*******************************************\n");
}
