#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdlib.h>

int main(int argc,char *argv[])
{   
    int fdSrc,fdDest;
    char buffer[1024];
    int bytesRead;

    if(argc!=3)
    {
        printf("Usage:%s SourceFile DestFile\n",argv[0]);
        return 1;
    }

    fdSrc=open(argv[1],O_RDONLY);
    if(fdSrc==-1)
    {
        perror("Unable to open source file");
        return 1;
    }

    fdDest=open(argv[2],O_WRONLY | O_CREAT | O_TRUNC,0644);
    if(fdDest==-1)
    {
        perror("Unable to open destination file");
        close(fdSrc);
        return 1;
    }

    while((bytesRead=read(fdSrc,buffer,sizeof(buffer)))>0)
    {
        write(fdDest,buffer,bytesRead);
    }
    printf("File copied successfully\n");

    close(fdSrc);
    close(fdDest);

    return 0;

}