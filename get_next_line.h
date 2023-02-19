#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1000
# endif
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>

typedef struct s_bookmark
{
    char    init;
    int     fd;
    char    remainder[100];
} t_bookmark;

char    *get_next_line(int fd);

#endif