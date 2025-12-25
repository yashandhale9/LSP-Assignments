#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>

//Function which open file using command line
int openFile(char *fileName)
{
    int fd=0;

    fd=open(fileName,O_RDWR);

    if(fd==-1)
    {
        perror("Unable to open file");
        return -1;
    }
    return fd;
}

int main(int argc, char*argv[])
{

    int fd=0;

    if(argc!=2)
    {
        printf("Use:%s<Filename>\n",argv[0]);
        return -1;
    }

    fd=openFile(argv[1]);

    if(fd!=-1)
    {
        printf("File gets successfully opened with fd:%d\n",fd);
        close(fd);
    }


    return 0;
}