#include "get_next_line.h"

char    *get_next_line(int fd)
{
    static t_bookmark bookmark[101];
    int         i;
    char        found_fd;
    char        *buf;
    ssize_t     bytes_read;
    char        found_nl;
    char        *line;
    
    found_fd = 0;
    i = 1;
    bytes_read = 0;
    found_nl = 0;
    // Check for valid fd
    if (fd < 0)
    {
        return (NULL);
    }
    // Check init for bookmark
    if (bookmark[0].init != 'Y' && bookmark[0].fd != -1)
    {
        bookmark[0].init = 'Y';
        bookmark[0].fd = -1;
        while (i < 101) // Init
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
    }
    // Only read if fd first round or if returned full buf already
    if (bookmark[i].remainder[0] == '\0')
    {
        buf = (char *) malloc(sizeof(char) * 100);
        bytes_read = read(fd, buf, BUFFER_SIZE - 1);
        buf[bytes_read] = '\0';
        int g = 0;
        while (buf[g] != '\0' && found_nl == 0) 
        {
            if (buf[g] == '\n')
            {
                found_nl = 1;
                line = (char *) malloc(sizeof(char) * g);
                int h = 0;
                while (h <= g)
                {
                    line[h] = buf[h];
                    h++;
                }
                h = 0;
                g++;
                while (buf[g] != '\0')
                {
                    bookmark[i].remainder[h] = buf[g];
                    g++;
                    h++;
                }
                bookmark[i].remainder[h] = '\0';
                free(buf);
                return (line);
            }
            g++;
        }
    } 
    else 
    {
        int z = 0;
        while (bookmark[i].remainder[z] != '\0')
        {
            z++;
        }
        line = (char *) malloc(sizeof(char) * z);
        z = 0;
        while (bookmark[i].remainder[z] != '\0')
        {
            line[z] = bookmark[i].remainder[z];
            z++;
        }
        line[z] = '\0';
        return (line);
    }
    return (NULL);  
}