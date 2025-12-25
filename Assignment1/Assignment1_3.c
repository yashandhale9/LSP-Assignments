#include <stdio.h>
#include <unistd.h>
#include <string.h>

void checkAccess(char *fileName,char *mode)
{
    int result=0;
    int accessMode=0;

    if(strcmp(mode,"read")==0)
    {
        accessMode=R_OK;
    }
    else if(strcmp(mode,"write")==0)
    {
        accessMode=W_OK;
    }
    else if(strcmp(mode,"execute")==0)
    {
        accessMode=X_OK;
    }
    else
    {
        printf("Invalid mode\n");
    }

    result=access(fileName,accessMode);

    if(result==0)
    {
        printf("File is accessible\n");
    }
    else
    {
        printf("File is not accessible\n");
        perror("Reason");
    }
}

int main(int argc,char *argv[])
{
    if(argc!=3)
    {
        printf("Usage:%s <filename> <read/write/execute>\n",argv[0]);
        return -1;
    }
    
    checkAccess(argv[0],argv[2]);
    
    return 0;
}