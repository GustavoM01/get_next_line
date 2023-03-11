#include <stdio.h>
#include "get_next_line.h"
#include <fcntl.h>
#include <limits.h>

int main()
{
    int fd;
    char *buf;
    size_t max = 0; 

    fd = open("test.txt", O_RDONLY);
    setbuf(stdout, NULL);
    if (fd == -1)
    {
        printf("Error");
        return (1);
    }

    buf = get_next_line(fd);
    printf("%s\n", buf);
    // free(buf);
    // buf = get_next_line(fd);
    // printf("%s\n", buf);
    // free(buf);
    // buf = get_next_line(fd);
    // printf("%s\n", buf);
    // free(buf);
    // buf = get_next_line(fd);
    // printf("%s\n", buf);
    // free(buf);
    // buf = get_next_line(fd);
    // printf("%s\n", buf);
    // free(buf);
    // buf = get_next_line(fd);
    // printf("%s\n", buf);
    // free(buf);
    // buf = get_next_line(fd);
    // printf("%s\n", buf);
    // free(buf);
    // buf = get_next_line(fd);
    // printf("%s\n", buf);
    // free(buf);
    // buf = get_next_line(fd);
    // printf("%s\n", buf);
    // free(buf);
    // buf = get_next_line(fd);
    // printf("%s\n", buf);
    
    return (0);
}