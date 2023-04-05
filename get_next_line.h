#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1000
# endif
# ifndef BOOKMARK_SIZE
#  define BOOKMARK_SIZE 20
# endif
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdint.h>
# include <stdio.h> // DELETE

typedef struct s_bookmark
{
    int     fd;
    char    remainder[BUFFER_SIZE + 1];
    int     size;
    char    eof;
} t_bookmark;

char    *get_next_line(int fd);
char    *double_buffer(char *buffer, size_t size, int fd);
int	find_nl(char *buffer, int *index);
char    *line_buffer(char *buffer, t_bookmark *bm, int found_nl);
char *bookmark_manager(t_bookmark *bookmark, int fd, int *bm_i);
char *get_line(int fd,  t_bookmark *bookmark, int *found_nl);
char *find_bm_line(t_bookmark *bm);
char	*read_mng(int fd, t_bookmark *bm);
char	*get_buffer_line(char *buffer, t_bookmark *bm, int found_nl);
char	*keep_reading(int fd, char *buffer, t_bookmark *bm);

#endif
