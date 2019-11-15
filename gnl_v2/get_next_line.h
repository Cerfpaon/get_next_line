#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 32
#endif

# include <stdlib.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>

// get_next_line
int		rest_mgmt(char **rest, char **line);
int		buff_mgmt(char **rest, char **line, char *buff);
int		get_next_line(int fd, char **line);

// get_next_line_utils
void	fill(char *dst, const char *src, char end);
int		concat(char **line, char *buff, char end);
int		only_eof(char **line);


#endif