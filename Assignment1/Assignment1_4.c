#include<stdio.h>
#include<unistd.h>
#include<sys/stat.h>
#include<time.h>

void displayFileInfo(char *fileName)
{
    struct stat fileStat;

    if(stat(fileName,&fileStat)==-1)
    {
        perror("Stat failed");
        return;
    }
    printf("\nFile Information:\n");
    printf("---------------------\n");

    //file Size
    printf("File size:%ld bytes\n",fileStat.st_size);

    //Inode Number
    printf("Inode Number:%ld\n",fileStat.st_ino);

    //Hard Link Count
    printf("Hard Links:%ld\n",fileStat.st_nlink);

    //Owner IDs
    printf("Owner UID:%d\n",fileStat.st_uid);
    printf("Owner GID:%d\n",fileStat.st_gid);
    
    //File Type

    printf("File Type:");
    if(S_ISREG(fileStat.st_mode))
        printf("Regular File\n");
    else if(S_ISDIR(fileStat.st_mode))
        printf("Directory File\n");
    else if(S_ISCHR(fileStat.st_mode))
        printf("Character File\n");
    else if(S_ISBLK(fileStat.st_mode))
        printf("Block Device\n");
    else if(S_ISFIFO(fileStat.st_mode))
        printf("FIFO\n");
    else if(S_ISLNK(fileStat.st_mode))
        printf("Symbolic Link\n");
    else
        printf("Unknown");
    
    //Time Information
    printf("Last Access Time:%s",ctime(&fileStat.st_atime));
    printf("Last Modify Time:%s",ctime(&fileStat.st_mtime));
}

int main(int argc,char *argv[])
{
    if(argc!=2)
    {
        printf("Usage: %s <FileName>\n",argv[0]);
        return -1;
    }

    displayFileInfo(argv[1]);

    return 0;
}