#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdlib.h>

void ReverseFile(char *filename)
{
    int fd;
    char ch;
    off_t size;

    fd=open(filename,O_RDONLY);
    if(fd<0)
    {
        perror("Unable to open file");
        return;
    }

    size=lseek(fd,0,SEEK_END);

    while(size>0)
    {
        size--;
        lseek(fd,size,SEEK_SET);
        read(fd,&ch,1);
        write(1,&ch,1);
    }
    close(fd);
}

int main(int argc,char *argv[])
{
    if(argc!=2)
    {
        printf("Usage: %s filename\n",argv[0]);
        return -1;
    }
    ReverseFile(argv[1]);
    return 0;
}