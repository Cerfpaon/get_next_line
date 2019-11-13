#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <stdio.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 32
#endif

int		rest_mgmt(char **rest, char **line);
int		buff_nl(char **rest, char **line, char *buff);
int		buff_eof(char **line, char *buff);
int		buff_full(char **line, char *buff);
int		get_next_line(int fd, char **line);

int		get_nl(char *buff);
void	fill(char *dst, char *src, char end);
char	*str_join(char *line, char *buff, char end);

#endif