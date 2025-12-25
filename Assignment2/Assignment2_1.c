#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>

void ReadWholeFile(char *fileName)
{
    int fd=0;
    int bytesRead=0;
    int totalBytes=0;
    char buffer[100];

    fd=open(fileName,O_RDONLY);

    if(fd==-1)
    {
        perror("Unable to open the file");
        return;
    }

    bytesRead=read(fd,buffer,sizeof(buffer));
    while(bytesRead>0)
    {
        write(1,buffer,bytesRead);
        totalBytes=totalBytes+bytesRead;

        bytesRead=read(fd,buffer,sizeof(buffer));
    }

    if(bytesRead==-1)
    {
        perror("Read Error");
    }

    printf("\nTotal bytes read:%d\n",totalBytes);
    close(fd);
}

int main(int argc, char *argv[])
{
    if(argc!=2)
    {
        printf("Usage:%s <FileName>\n",argv[0]);
        return -1;
    }

    ReadWholeFile(argv[1]);

    return 0;
}