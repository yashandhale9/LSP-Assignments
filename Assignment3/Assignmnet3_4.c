#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

/* Function to delete empty regular files */
void DeleteEmptyFiles(char *dirname)
{
    DIR *dp;
    struct dirent *d;
    struct stat s;
    char path[300];
    int count = 0;

    dp = opendir(dirname);
    if (dp == NULL)
    {
        perror("Unable to open directory");
        return;
    }

    while ((d = readdir(dp)) != NULL)
    {
        if (strcmp(d->d_name, ".") == 0 ||
            strcmp(d->d_name, "..") == 0)
            continue;

        snprintf(path, sizeof(path), "%s/%s", dirname, d->d_name);

        if (stat(path, &s) == -1)
            continue;

        /* Check for empty regular file */
        if (S_ISREG(s.st_mode) && s.st_size == 0)
        {
            if (unlink(path) == 0)
            {
                printf("Deleted : %s\n", d->d_name);
                count++;
            }
        }
    }

    closedir(dp);

    printf("Total empty files deleted : %d\n", count);
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage : ./myexe DirectoryName\n");
        return 0;
    }

    DeleteEmptyFiles(argv[1]);
    return 0;
}
