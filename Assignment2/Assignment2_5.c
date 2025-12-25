#include<stdio.h>
#include<dirent.h>
#include<sys/stat.h>
#include<string.h>

/*Function to find largest file*/

void FindLargestFile(char *dirname)
{
    DIR *dp;
    struct dirent *d;
    struct stat s;
    char path[300];
    char largestFile[256]="";
    long maxSize=0;

    dp=opendir(dirname);

    if(dp==NULL)
    {
        perror("Unable to open directory");
        return;
    }

    while((d=readdir(dp))!=NULL)
    {
        /*Skip . and .. */
        if(strcmp(d->d_name,".")==0 || strcmp(d->d_name,"..")==0)
        continue;

        snprintf(path,sizeof(path),"%s/%s",dirname,d->d_name);

        if(stat(path,&s)==-1)
        continue;

        /*Consider only regular file*/
        if(S_ISREG(s.st_mode))
        {
            if(s.st_size>maxSize)
            {
                maxSize=s.st_size;
                strcpy(largestFile,d->d_name);
            }
        }
    }
    closedir(dp);

    if(maxSize>0)
    {
        printf("Largest File:%s\n",largestFile);
        printf("Size:%ld bytes\n",maxSize);
    }
    else
    {
        printf("No regular files found\n");
    }

}

int main(int argc,char *argv[])
{
    if(argc!=2)
    {
        printf("Usage: ./Myexe DirectoryName\n");
        return 0;
    }
    FindLargestFile(argv[1]);
    return 0;
}
