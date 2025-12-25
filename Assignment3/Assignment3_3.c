#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

/* Function to copy file */
void CopyFile(char *src, char *dest)
{
    int fdSrc, fdDest;
    int bytesRead;
    char buffer[1024];
    struct stat s;

    fdSrc = open(src, O_RDONLY);
    if (fdSrc == -1)
        return;

    stat(src, &s);

    fdDest = open(dest, O_WRONLY | O_CREAT | O_TRUNC, s.st_mode);
    if (fdDest == -1)
    {
        close(fdSrc);
        return;
    }

    while ((bytesRead = read(fdSrc, buffer, sizeof(buffer))) > 0)
    {
        write(fdDest, buffer, bytesRead);
    }

    close(fdSrc);
    close(fdDest);
}

/* Function to move all regular files */
void MoveFiles(char *srcDir, char *destDir)
{
    DIR *dp;
    struct dirent *d;
    struct stat s;
    char srcPath[300], destPath[300];
    int count = 0;

    dp = opendir(srcDir);
    if (dp == NULL)
    {
        perror("Unable to open source directory");
        return;
    }

    while ((d = readdir(dp)) != NULL)
    {
        if (strcmp(d->d_name, ".") == 0 ||
            strcmp(d->d_name, "..") == 0)
            continue;

        snprintf(srcPath, sizeof(srcPath), "%s/%s", srcDir, d->d_name);
        snprintf(destPath, sizeof(destPath), "%s/%s", destDir, d->d_name);

        if (stat(srcPath, &s) == -1)
            continue;

        if (S_ISREG(s.st_mode))
        {
            /* Try rename first */
            if (rename(srcPath, destPath) == 0)
            {
                count++;
            }
            else
            {
                /* Different filesystem: copy + delete */
                CopyFile(srcPath, destPath);
                unlink(srcPath);
                count++;
            }
        }
    }

    closedir(dp);

    printf("Total files moved : %d\n", count);
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Usage : ./Myexe SourceDir DestinationDir\n");
        return 0;
    }

    MoveFiles(argv[1], argv[2]);
    return 0;
}
