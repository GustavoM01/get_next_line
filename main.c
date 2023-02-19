#include <stdio.h>
#include "get_next_line.h"
#include <fcntl.h>

int main()
{
    int fd;
    char *buf = (char *) malloc(sizeof(char) * 10);

    int i = 0;
    while (i < 9) {
        buf[i] = 'A';
        i++;
    }
    buf[i] = '\n';

    fd = open("test1.txt", O_RDONLY);
    if (fd == -1)
    {
        printf("Error");
        return (1);
    }
    // read(fd, buf, 50);
    // printf("%s\n", buf);
    // read(fd, buf, 50);
    // printf("%s\n", buf);
    // buf = get_next_line(fd);
    // printf("%s", buf);
    // buf = get_next_line(fd);
    // printf("%s", buf);
    // buf = get_next_line(fd);
    // printf("%s", buf);

    printf("%s", buf);

    free(buf);
    return (0);
}