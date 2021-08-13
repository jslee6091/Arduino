#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, char **argv)
{
    struct stat statbuf;

    if (argc < 3) {
        fprintf(stderr, "Usage: %s file1 file2\n", argv[0]);
        return -1;
    }

    /* Bring the information about exists or not in the file */
    if (stat(argv[1], &statbuf) < 0) {
        perror("stat");
        return -1;
    }

    /* Set set-group-ID and unlock the execution authority */
    if (chmod(argv[1], (statbuf.st_mode & ~S_IXGRP) | S_ISGID) < 0) {
        perror("chmod");
        return -1;
    }

    /* Set the authority of file to 644("rw-r--r--") */
    if (chmod(argv[2], S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH) < 0) {
        perror("chmod");
        return -1;
    }

    return 0;
}
