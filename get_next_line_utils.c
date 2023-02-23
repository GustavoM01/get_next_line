#include "get_next_line.h"

char    *double_buffer(char *buffer, size_t size)
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
        free(buffer);
        read_bytes = read()
    }
    return double_buffer;
}

short   find_next_line(char *buffer)
{
    int     i;

    i = 0;
    while (buffer[i] != '\0')
    {
        if (buffer[i] = '\n')
        {
            return (1);
        }
    }
    return (0);
}