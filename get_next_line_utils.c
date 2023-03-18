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
            return (i);
        i++;
    }
    return (0);
}

char    *line_buffer(char *buffer, t_bookmark *bm, int found_nl)
{
    int i;
    int j;
    char    *line_buffer;

    i = 0;
    j = 0;
    line_buffer = (char *) malloc(sizeof(char) * found_nl + 2);
    line_buffer[found_nl + 1] = '\0';
    while(i < (found_nl + 1))
    {
        line_buffer[i] = buffer[i];
        i++;
    }
    while(buffer[i] != '\0')
    {
        bm[0].remainder[j] = buffer[i];
        i++;
        j++;
    }
    bm[0].remainder[i] = '\0';
    bm[0].size = j - 1;
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
        while (i < BOOKMARK_SIZE)
        {
            bookmark[i].init = 'N';
            bookmark[i].eof = 'N';
            i++;
        }
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


static char *read_manager(int fd, char *buffer, int multiplier, int shift, t_bookmark *bm)
{
    char *inc_buffer;
    int i;
    int j;
    size_t bytes_read;

    i = 0;
    j = 0;
    bytes_read = 0;
    inc_buffer = (char *) malloc(sizeof(char) * ((BUFFER_SIZE * multiplier)  + shift));
    if (!inc_buffer)
        return (NULL);
    while (bm[0].remainder[i] != '\0')
    {
        inc_buffer[i] = bm[0].remainder[i];
        bm[0].remainder[i] = '\0';
        i++;
    }
    if (bm[0].remainder[0] == '\0')
        bm[0].size = 0;
    if (buffer)
    {
        while (buffer[j] != '\0')
        {
            inc_buffer[i] = buffer[j];
            i++;
            j++;
        }        
        free(buffer);
    }
    bytes_read = read(fd, inc_buffer + i, BUFFER_SIZE);
    inc_buffer[i + bytes_read] = '\0';
    if (bytes_read == 0)
        bm[0].eof = 'Y';
    else if (bytes_read == -1)
        bm[0].eof = 'E';
    return (inc_buffer);
}
/**
 * @brief This will return a line, which size is unknown.
 * It uses read() as many times as it takes to find '\n' or EOF.
 * 
 * @param fd the file descripter used by read(). It should be a valid file descriptor.
 * @param bookmark bookmark struct with fd information.
 * @param found_nl where and if '\n' is found in the line. 
 * A pointer is used to update this value in main function.
 * @return char* that points to line.
 */
char *get_line(int fd,  t_bookmark *bookmark, int *found_nl)
{
    char *buffer;
    int shift;
    int multiplier;

    shift = 1;
    multiplier = 1;
    buffer = NULL;
    if (bookmark[0].remainder[0] != '\0')
        shift += bookmark[0].size;
    while (*found_nl == 0 && bookmark[0].eof == 'N')
    {
        buffer = read_manager(fd, buffer, multiplier, shift, bookmark);
        if (!buffer)
            return (NULL);
        *found_nl = find_next_line(buffer);
        multiplier++;
    }
    return (buffer);
}
