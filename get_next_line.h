#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1000
# endif
# ifndef BOOKMARK_SIZE
#  define BOOKMARK_SIZE 100
# endif
# define BM_SIZE 100
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdint.h>

typedef struct s_bookmark
{
    char    init;
    int     fd;
    char    remainder[BUFFER_SIZE + 1];
    int     size;
    int     index;
    char    eof;
} t_bookmark;

char    *get_next_line(int fd);
char    *double_buffer(char *buffer, size_t size, int fd);
int     find_next_line(char *buffer);
char    *line_buffer(char *buffer, char *remainder, int found_nl);
int bookmark_manager(t_bookmark *bookmark, int fd);
char *get_line(int fd,  t_bookmark *bookmark, int index, int *found_nl);

#endif