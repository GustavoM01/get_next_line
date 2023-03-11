#include "get_next_line.h"

char    *get_next_line(int fd)
{
    static t_bookmark bookmark[BOOKMARK_SIZE]; // what to set the size of bookmarks
    int         i; 
    char        *buffer;
    int         found_nl;

    found_nl = 0;
    // Check for valid fd
    if (fd < 0)
        return (NULL);
    // Return saved fd info or add to bookmark
    i = bookmark_manager(bookmark, fd);
    // Read and return bf when nl is found
    buffer = get_line(fd, bookmark, i, &found_nl);
    // Save remainder after new line and change nl for '\0'
    buffer = line_buffer(buffer, bookmark + i, found_nl);
    return (buffer);  
}