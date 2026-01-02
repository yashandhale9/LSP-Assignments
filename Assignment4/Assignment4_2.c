#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdlib.h>

#define BUFFER_SIZE 1024

void CopyFileWithOffset(char *src,char *dest,int offset)
{
    int fdSrc,fdDest;
    char buffer[BUFFER_SIZE];
    int bytesRead;

    fdSrc=open(src,O_RDONLY);
    if(fdSrc==-1)
    {
        perror("Unable to open source file");
        return;
    }
    fdDest=open(dest,O_WRONLY | O_CREAT | O_TRUNC,0644);
    if(fdDest==-1)
    {
        perror("Unabale to open destination file");
        close(fdSrc);
        close(fdDest);
        return;
    }

    while((bytesRead=read(fdSrc,buffer,sizeof(buffer)))>0)
    {
        write(fdDest,buffer,bytesRead);
    }
    close(fdSrc);
    close(fdDest);
}

int main(int argc,char *argv[])
{
    int offset;

    if(argc!=4)
    {
        printf("Usage: %s SourceFile DestFile Offset\n",argv[0]);
        return 1;
    }

    offset=atoi(argv[3]);

    CopyFileWithOffset(argv[1],argv[2],offset);

    printf("File copied successfully from offset %d\n",offset);

    return 0;

}