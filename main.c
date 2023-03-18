#include <stdio.h>
#include "get_next_line.h"
#include <fcntl.h>
#include <limits.h>

int main()
{
    int fd;
    int fd2;
    char *buf;
    size_t max = 0; 
    char *buffer = (char *) malloc(sizeof(char) * 100);

    fd = open("test.txt", O_RDONLY);
    setbuf(stdout, NULL);
    if (fd == -1)
    {
        printf("Error");
        return (1);
    }
    fd2 = open("test1.txt", O_RDONLY);
    if (fd2 == -1)
    {
        printf("Error");
        return (1);
    }
    // max = read(1000, buffer, BUFFER_SIZE);
    // size_t myMax = (size_t) -1;
    // printf("read_bytes is: %zu and max:%zu\n", myMax, max);
    // buf = get_next_line(1000);
    // printf("%s\n", buf);
    buf = get_next_line(fd2);
    printf("%s", buf);
    // buf = get_next_line(fd);
    // printf("%s", buf);
    buf = get_next_line(fd2);
    printf("%s", buf);
    free(buf);
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