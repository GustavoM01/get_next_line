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
    int found_fd;

    i = 1;
    found_fd = 0;
    if (bookmark[0].init != 'Y' && bookmark[0].fd != -1) // Could add chech for remainder last place equal to '/0'
    {
        bookmark[0].init = 'Y';
        bookmark[0].fd = -1;
        while (i < BOOKMARK_SIZE)
        {
            bookmark[i].init = 'N';
            i++;
        }
        i -= BOOKMARK_SIZE;
    }
    while (bookmark[i].init == 'Y' && found_fd == 0)
    {
        if (bookmark[i].fd == fd)
        {
            found_fd = 1;
            i--;
        }
        i++;
    } // 25 lines
    if (found_fd == 0)
    {
        bookmark[i].init = 'Y';
        bookmark[i].fd = fd;
        bookmark[i].remainder[0] = '\0';
        bookmark[i].size = BUFFER_SIZE;
    }
    return (i);
}