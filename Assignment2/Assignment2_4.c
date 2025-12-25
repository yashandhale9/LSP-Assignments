#include<stdio.h>
#include<dirent.h>
#include<sys/stat.h>
#include<string.h>


void ListFiles(char *dirname)
{
    DIR *dp;
    struct dirent *d;
    struct stat s;
    char path[300];

    dp=opendir(dirname);
    if(dp==NULL)
    {
        printf("Unable to open directory\n");
        return;
    }
    while((d=readdir(dp))!=NULL)
    {
        if(strcmp(d->d_name,".")==0 || strcmp(d->d_name,"..")==0)
        continue;

        snprintf(path,sizeof(path),"%s/%s",dirname,d->d_name);
        stat(path,&s);

        printf("%s :",d->d_name);

        if(S_ISREG(s.st_mode))
            printf("Regular File\n");
        else if(S_ISDIR(s.st_mode))
            printf("Directory\n");
        else if(S_ISLNK(s.st_mode))
            printf("Link\n");
        else if(S_ISFIFO(s.st_mode))
            printf("FIFO\n");
        else if(S_ISSOCK(s.st_mode))
            printf("Socket\n");
        else if(S_ISCHR(s.st_mode))
            printf("Character Device\n");
        else if(S_ISBLK(s.st_mode))
            printf("Block Device\n");
    }
    closedir(dp);
}

int main(int argc,char *argv[])
{
    if(argc!=2)
    {
        printf("Usage: ./Myexe DirectoryName\n");
        return 0;
    }

    ListFiles(argv[1]);
    return 0;
}