#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/stat.h>

/*Function to copy file*/
void CopyFile(char *src,char *dest)
{
    int fdSrc,fdDest;
    int bytesRead;
    char buffer[1024];
    struct stat s;

    /*Open source file*/
    fdSrc=open(src,O_RDONLY);
    if(fdSrc==-1)
    {
        perror("Unable to open source file");
        return;
    }

    //Get source file permissions
    stat(src,&s);

    //open destination file
    fdDest=open(dest,O_WRONLY | O_CREAT | O_TRUNC,s.st_mode);
    if(fdDest==-1)
    {
        perror("Unable to open destination file");
        close(fdSrc);
        return;
    }
    //Copy data
    while((bytesRead=read(fdSrc,buffer,sizeof(buffer)))>0)
    {
        write(fdDest,buffer,bytesRead);
    }
    printf("File copied successfully\n");

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

    CopyFile(argv[1],argv[2]);
    return 0;
}