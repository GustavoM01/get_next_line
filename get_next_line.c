#include "get_next_line.h"

char    *get_next_line(int fd)
{
    static t_bookmark bookmark[100]; //
    int         i = 1; //
    int         j = 0; //
    int         k = 0; //
    int         l = 0; //
    int         m = 0; //
    int         n = 0; //
    int         o = 2; //
    int         z = 0; //
    char        found_fd = 0; //
    char        *buffer; //
    ssize_t     bytes_read = 0; //
    char        found_nl = 0; //
    char        *line; //

    // Check for valid fd
    if (fd < 0)
    {
        return (NULL);
    }
    // Check init for bookmark
    if (bookmark[0].init != 'Y' && bookmark[0].fd != -1) // Could add chech for remainder last place equal to '/0'
    {
        bookmark[0].init = 'Y';
        bookmark[0].fd = -1;
        while (i < 100) // Init
        {
            bookmark[i].init = 'N';
            i++;
        }
        i = 1;
    }
    // Check for existing file descriptor
    while (bookmark[i].init == 'Y' && found_fd == 0)
    {
        if (bookmark[i].fd == fd)
        {
            found_fd = 1;
            i--;
        }
        i++;
    }
    // Add fd if not found on bookmark
    if (found_fd == 0)
    {
        bookmark[i].init = 'Y';
        bookmark[i].fd = fd;
        bookmark[i].remainder[0] = '\0';
        bookmark[i].size = BUFFER_SIZE;
    }
    // Only read if fd first round or if returned full buf already
    if (bookmark[i].remainder[0] == '\0')
    {
        buffer = (char *) malloc(sizeof(char) * BUFFER_SIZE + 1); // Missing check if buffer is ok
        bytes_read = read(fd, buffer, BUFFER_SIZE); // Missing check for read
        buffer[bytes_read] = '\0';
        while (l < bytes_read) 
        {
            if (buffer[j] == '\n')
            {
                found_nl = 1;
                line = (char *) malloc(sizeof(char) * j + 1);
                line[j] = '\0';
                while (k <= j)
                {
                    line[k] = buffer[k];
                    k++;
                }
                k = 0;
                j++;
                while (buffer[j] != '\0')
                {
                    bookmark[i].remainder[k] = buffer[j];
                    j++;
                    k++;
                }
                bookmark[i].remainder[k] = '\0';
                free(buffer);
                return (line);
            }
            j++;
            l++;
        }
        while (found_nl == 0)
        {
            buffer = double_buffer(buffer, BUFFER_SIZE * o);
            found_nl = find_next_line(buffer);
            o++;
        }
    } 
    else 
    {
        while (bookmark[i].remainder[z] != '\0')
        { 
            if(bookmark[i].remainder[z] == '\n')
            {
                found_nl = 1;
                buffer = (char *) malloc(sizeof(char) * z + 2);
                buffer[z + 1] = '\0';
                while (k <= z)
                {
                    buffer[k] = bookmark[i].remainder[k];
                    k++;
                }
                k = 0;
                z++;
                while (bookmark[i].remainder[z + k] != '\0')
                {
                    bookmark[i].remainder[k] = bookmark[i].remainder[z + k];
                    k++;
                }
                bookmark[i].remainder[k] = '\0';
                return (buffer);
            }
            z++;
        }
    }
    if (found_nl == 0)
    {
        while (bookmark[i].remainder[n] != '\0')
        {
            n++;
        }
        buffer = (char *) malloc((sizeof(char) * (BUFFER_SIZE)) + n + 1);
        buffer[BUFFER_SIZE + n + 1] = '\0';
        n = 0;
        while (bookmark[i].remainder[n] != '\0')
        {
            buffer[n] = bookmark[i].remainder[n];
            n++;
        }
        bytes_read = read(fd, buffer + n, BUFFER_SIZE);
        if (bytes_read == 0)
        {
            return (buffer);
        }
        buffer[bytes_read + 2] = '\0';
        while (l < bytes_read + 2) 
        {
            if (buffer[j] == '\n')
            {
                found_nl = 1;
                line = (char *) malloc(sizeof(char) * j + 1);
                line[j] = '\0';
                while (k <= j)
                {
                    line[k] = buffer[k];
                    k++;
                }
                k = 0;
                j++;
                while (buffer[j] != '\0')
                {
                    bookmark[i].remainder[k] = buffer[j];
                    j++;
                    k++;
                }
                bookmark[i].remainder[k] = '\0';
                free(buffer);
                return (line);
            }
            j++;
            l++;
        }
    }
    return (NULL);  
}