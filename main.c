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
    // printf("size of size_t: %u\n", sizeof(unsigned int));
    // printf("%u\n", UINT_MAX);
    // printf("size of size_t: %lu\n", sizeof(size_t));
    // printf("%lu\n", ~max);
    // printf("size of unsigned long: %lu\n", sizeof(unsigned long));
    // printf("%lu\n", ULONG_MAX);
    // read(fd, buf, 50);
    // printf("%s\n\n", buf);
    // read(fd, buf, 50);
    // printf("%s\n\n", buf);
    buf = get_next_line(fd);
    printf("%s\n", buf);
    free(buf);
    buf = get_next_line(fd);
    printf("%s\n", buf);
    free(buf);
    buf = get_next_line(fd);
    printf("%s\n", buf);
    free(buf);
    buf = get_next_line(fd);
    printf("%s\n", buf);
    free(buf);
    buf = get_next_line(fd);
    printf("%s\n", buf);
    free(buf);
    buf = get_next_line(fd);
    printf("%s\n", buf);
    free(buf);
    buf = get_next_line(fd);
    printf("%s\n", buf);
    free(buf);
    buf = get_next_line(fd);
    printf("%s\n", buf);
    free(buf);
    buf = get_next_line(fd);
    printf("%s\n", buf);
    free(buf);
    // buf = get_next_line(fd);
    // printf("%s\n", buf);
    
    return (0);
}