#include "get_next_line.h"

char    *get_next_line(int fd)
{
    static t_fd fd_index[101];
    int         i;
    int         j;
    int         k;
    char        found_fd;
    char        *buf;
    ssize_t     bytes_read;
    int         rounds;
    char        found_nl;
    char        *line;
    
    found_fd = 0;
    i = 1;
    rounds = 0;
    j = 0;
    bytes_read = 0;
    found_nl = 0;
    k = 0;
    // Check for valid fd
    if (fd < 0)
    {
        return (NULL);
    }
    // Check init for fd_index
    if (fd_index[0].init != 'Y' && fd_index[0].fd != -1 && fd_index[0].index != -1)
    {
        fd_index[0].init = 'Y';
        fd_index[0].fd = -1;
        fd_index[0].fd = -1;
        while (i < 101) // Init
        {
            fd_index[i].init = 'N';
            i++;
        }
        i = 1;
    }
    // Check for existing file descriptor
    while (fd_index[i].init == 'Y' && found_fd == 0)
    {
        if (fd_index[i].fd == fd)
        {
            found_fd = 1;
            i--;
        }
        i++;
    }
    // Add fd if not found on fd_index
    if (found_fd == 0)
    {
        fd_index[i].init = 'Y';
        fd_index[i].fd = fd;
        fd_index[i].remainder[0] = '\0';
    }
    // Only read if fd first round or if returned full buf already
    if (fd_index[i].remainder[0] == '\0')
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
                    fd_index[i].remainder[h] = buf[g];
                    g++;
                    h++;
                }
            }
            g++;
        }
        printf("%s\n", fd_index[i].remainder);
    }
    return (NULL);  
}