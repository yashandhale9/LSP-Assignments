#include<stdio.h>
#include<dirent.h>
#include<string.h>

void ListFiles(char *dirName)
{
    DIR *dir=NULL;
    struct dirent *entry=NULL;

    dir=opendir(dirName);

    if(dir==NULL)
    {
        perror("Unable to open directory");
        return;
    }

    while((entry=readdir(dir))!=NULL)
    {
        if(strcmp(entry->d_name,".")==0 || strcmp(entry->d_name,"..")==0)
        {
            continue;
        }

        printf("%s\n",entry->d_name);
    }
    closedir(dir);
}

int main(int argc,char *argv[])
{

    if(argc!=2)
    {
        printf("Usage: %s <DirectoryName>\n",argv[0]);
        return -1;
    }

    ListFiles(argv[1]);

    return 0;
}