#include "get_next_line.h"

char    *get_next_line(int fd)
{
    static t_bookmark bookmark[BOOKMARK_SIZE]; // what to set the size of bookmarks
    int         i; 
    char        *buffer;
    int         found_nl;

    found_nl = 0;
    // Check for valid fd
    buffer = NULL;
    if (fd > -1)
    {
        // Return saved fd info or add to bookmark
        i = bookmark_manager(bookmark, fd);
        buffer = find_bm_line(bookmark + i);
        if (buffer == NULL)
        {
            buffer = get_line(fd, bookmark + i, &found_nl);
            if(buffer != NULL)
            {
                if (bookmark[i].eof != 'Y')
                    buffer = line_buffer(buffer, bookmark + i, found_nl);
            }     
        }
    }
    return (buffer);  
}