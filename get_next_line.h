#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1000
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
} t_bookmark;

char    *get_next_line(int fd);

#endif