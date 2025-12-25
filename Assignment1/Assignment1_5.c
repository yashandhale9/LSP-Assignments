#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<fcntl.h>

void ReadBytes(char *fileName, int numberOfBytes)
{
    int fd=0;
    int bytesRead=0;
    char buffer[1024];

    //Open file in read-only mode
    fd=open(fileName,O_RDONLY);
    if(fd==-1)
    {
        perror("Unable to open file");
        return;
    }

    //Read N bytes from file
    bytesRead=read(fd,buffer,numberOfBytes);

    if(bytesRead==-1)
    {
        perror("Read failed");
        close(fd);
        return;
    }

    //write only the bytes that are read
    write(1,buffer,bytesRead);

    close(fd);
    
}

int main(int argc,char *argv[])
{
    int N=0;

    if(argc!=3)
    {
        printf("Usage:%s <FileName> <NumberOfBytes>\n",argv[0]);
        return -1;
    }

    //Convert N from string to integer
    N=atoi(argv[2]);


    //Call Function
    ReadBytes(argv[1],N);

    return 0;

}