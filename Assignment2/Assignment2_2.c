#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>

void WriteStringToFile(char *fileName,char *data)
{
    int fd=0;
    int bytesWritten=0;

    fd=open(fileName,O_WRONLY | O_APPEND | O_CREAT, 0644);

    if(fd==-1)
    {
        perror("Unable to open file");
        return;
    }

    bytesWritten=write(fd,data,strlen(data));

    if(bytesWritten==-1)
    {
        perror("Write failed");
        close(fd);
        return;
    }

    printf("Bytes written:%d\n",bytesWritten);

    close(fd);
}

int main(int argc,char*argv[])
{
    if(argc!=3)
    {
        printf("Usage:%s <FileName> <String>\n",argv[0]);
        return -1;
    }

    WriteStringToFile(argv[1],argv[2]);

    return 0;
}