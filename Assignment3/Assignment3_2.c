#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>

/* Function to check whether file exists in given directory */
void CheckFile(char *dirname, char *filename)
{
    DIR *dp;
    struct dirent *d;
    char path[PATH_MAX];
    char absPath[PATH_MAX];

    dp = opendir(dirname);
    if (dp == NULL)
    {
        perror("Unable to open directory");
        return;
    }

    while ((d = readdir(dp)) != NULL)
    {
        if (strcmp(d->d_name, filename) == 0)
        {
            snprintf(path, sizeof(path), "%s/%s", dirname, filename);

            if (realpath(path, absPath) != NULL)
            {
                printf("File Found\n");
                printf("Absolute Path : %s\n", absPath);
            }
            else
            {
                perror("realpath failed");
            }

            closedir(dp);
            return;
        }
    }

    printf("File not found in directory\n");
    closedir(dp);
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Usage : ./myexe DirectoryName FileName\n");
        return 0;
    }

    CheckFile(argv[1], argv[2]);
    return 0;
}
