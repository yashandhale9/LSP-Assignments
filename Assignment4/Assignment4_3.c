#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/stat.h>

#define BUFFER_SIZE 1024

void CopyFileUsingPreadPwrite(char *src,char*dest)
{
    int fdSrc,fdDest;
    char buffer[BUFFER_SIZE];
    ssize_t bytesRead;
    off_t offset=0;
    struct stat s;


    fdSrc=open(src,O_RDONLY);
    if(fdSrc==-1)
    {
        perror("Unable to open source file");
        return;
    }

    stat(src,&s);

    fdDest=open(dest,O_WRONLY | O_CREAT | O_TRUNC, s.st_mode);
    if(fdDest==-1)
    {
        perror("Unable to open destinatiom file");
        close(fdDest);
        return;
    }
    while((bytesRead=pread(fdSrc,buffer,BUFFER_SIZE,offset))>0)
    {
        pwrite(fdDest,buffer,bytesRead,offset);
        offset=offset+bytesRead;
    }
    close(fdSrc);
    close(fdDest);

}

int main(int argc,char *argv[])
{
    if(argc!=3)
    {
        printf("Usage: ./Myexe SourceFile DestinationFile\n");
        return 0;
    }

    CopyFileUsingPreadPwrite(argv[1],argv[2]);
    printf("File copied successfully using pread & pwrite\n");

    return 0;
}