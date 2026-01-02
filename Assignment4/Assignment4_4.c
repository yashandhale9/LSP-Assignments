#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdlib.h>

#define BUFFER_SIZE 1024

void CopyFileToFD(char *filename,int fdDest)
{
    int fdSrc;
    char buffer[BUFFER_SIZE];
    int bytesRead=0;

    fdSrc=open(filename,O_RDONLY);
    if(fdSrc<0)
    {
        perror("Error opening source file");
        return;
    }

    while((bytesRead=read(fdSrc,buffer,BUFFER_SIZE))>0)
    {
        write(fdDest,buffer,bytesRead);
    }
    close(fdSrc);
}

void MergeFiles(char *output,char *file1,char *file2)
{
    int fdOut;

    fdOut=open(output,O_CREAT | O_WRONLY | O_TRUNC,0644);
    if(fdOut<0)
    {
        perror("Error opening output file");
        return;
    }
    CopyFileToFD(file1,fdOut);
    CopyFileToFD(file2,fdOut);

    close(fdOut);
}

int main(int argc,char *argv[])
{
    if(argc!=4)
    {
        printf("Usage: %s output_file file1 file2\n",argv[0]);
        return -1;
    }
    MergeFiles(argv[1],argv[2],argv[3]);

    printf("Files merged successfully\n");
    return 0;
}