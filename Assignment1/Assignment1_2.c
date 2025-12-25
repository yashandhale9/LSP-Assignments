#include<fcntl.h>
#include<stdio.h>
#include<unistd.h>
#include<string.h>

//Function which convert mode into open() flags
int Flags(char *mode)
{
    if(strcmp(mode,"R")==0)
    {
        return O_RDONLY;
    }
    else if(strcmp(mode,"W")==0)
    {
        return O_WRONLY;
    }
    else if(strcmp(mode,"RW")==0)
    {
        return O_RDWR | O_CREAT;
    }
    else if(strcmp(mode,"A")==0)
    {
        return O_APPEND | O_CREAT | O_WRONLY;
    }
    else
    {
        return -1; //Invalid mode
    }
}

//Function which opens file using filename and mode
int openFile(char *fileName,char*mode)
{
    int fd=0;
    int openFlags=0;

    openFlags=Flags(mode);

    if(openFlags==-1)
    {
        printf("Invalide mode provided\n");
        return -1;
    }
    //open file with permissions(when O_CREAT is there/present)
    fd=open(fileName,openFlags,0644);

    if(fd==-1)
    {
        perror("Unable to open file");
        return -1;
    }
    return fd;
}

int main(int argc,char *argv[])
{
    int fd=0;

    if(argc!=3)
    {
        printf("Usage:%s<FileName> <Mode(R/W/RW/A)>\n",argv[0]);
        return -1;
    }

    fd=openFile(argv[1],argv[2]);
    if(fd!=-1)
    {
        printf("File opened successfully\n");
        printf("File Descriptor:%d\n",fd);

        close(fd);
    }
    return 0;
}