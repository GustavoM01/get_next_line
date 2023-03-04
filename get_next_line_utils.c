#include "get_next_line.h"

char    *gnl_main(char *buffer, size_t size, int fd)
{
    char    *double_buffer;
    int     i;
    size_t  read_bytes;

    i = 0;
    double_buffer = malloc(sizeof(char) * size + 1);
    double_buffer[size] = '\0';
    if (double_buffer != NULL) {
        while (buffer[i] != '\0')
        {
            double_buffer[i] = buffer[i];
            i++;
        }
        free(buffer); // Check for leaks
        read_bytes = read(fd, double_buffer + i, BUFFER_SIZE);
    }
    return double_buffer;
}

char    *double_buffer(char *buffer, size_t size, int fd)
{
    char    *double_buffer;
    int     i;
    size_t  read_bytes;

    i = 0;
    double_buffer = malloc(sizeof(char) * size + 1);
    double_buffer[size] = '\0';
    if (double_buffer != NULL) {
        while (buffer[i] != '\0')
        {
            double_buffer[i] = buffer[i];
            i++;
        }
        free(buffer); // Check for leaks
        read_bytes = read(fd, double_buffer + i, BUFFER_SIZE);
    }
    return double_buffer;
}


int   find_next_line(char *buffer)
{
    int     i;

    i = 0;
    while (buffer[i] != '\0')
    {
        if (buffer[i] == '\n')
        {
            return (i);
        }
        i++;
    }
    return (0);
}

char    *line_buffer(char *buffer, char *remainder, int found_nl)
{
    int i;
    int j;
    char    *line_buffer;
    i = 0;
    j = 0;
    line_buffer = (char *) malloc(sizeof(char) * found_nl + 2);
    line_buffer[found_nl + 2] = '\0';
    while(i < (found_nl + 1))
    {
        line_buffer[i] = buffer[i];
        i++;
    }
    while(buffer[i] != '\0')
    {
        remainder[j] = buffer[i];
        i++;
        j++;
    }
    remainder[i] = '\0';
    return (line_buffer);
}

int bookmark_manager(t_bookmark *bookmark, int fd)
{
    int i;

    i = 1;
    if (bookmark[0].init != 'Y' && bookmark[0].fd != -1) // Could add chech for remainder last place equal to '/0'
    {
        bookmark[0].init = 'Y';
        bookmark[0].fd = -1;
        while (i++ < BOOKMARK_SIZE)
            bookmark[i].init = 'N';
        i -= BOOKMARK_SIZE;
    }
    while (bookmark[i].init == 'Y')
    {
        if (bookmark[i].fd == fd)
            return (i);
        i++;
    }
    bookmark[i].init = 'Y';
    bookmark[i].fd = fd;
    bookmark[i].remainder[0] = '\0';
    return (i);
}

char *get_line(char *buf, int fd,  t_bookmark *bookmark)
{
    // check if there is any remainder in the fd-bookmark
        // YES
            // malloc with  size (BUFFER_SIZE + remainder_size + 1)
            // Add remainder to buf, ***including or except '/0'***
            // empty remainder
        // NO
            // malloc to read.size of BUFFER_SIZE + 1
    // check malloc ok
    // read
    // assign '\0' to buf[read_bytes]
    //check buf for new line or eof
}