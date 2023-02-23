#include "get_next_line.h"

char    *gnl_main(char *buffer, size_t size, int fd, t_bookmark *)
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