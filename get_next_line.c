#include "get_next_line.h"
#include <errno.h>
#include <string.h>

int		rest_mgmt(char **rest, char **line)
{
	int i;

	if (!(*rest) || !(**rest))
		return (0);
	i = 0;
	while ((*rest)[i] && (*rest)[i] != '\n')
		i++;
	if (!(*line = (char *)malloc(sizeof(char) * (i + 1))))
		return (-1);
	i = 0;
	while ((*rest)[i])
	{
		if ((*rest)[i] == '\n')
		{
			*rest = &(*rest)[i + 1];
			(*line)[i] = '\0';
			return (1);
		}
		(*line)[i] = (*rest)[i];
		i++;
	}
	(*line)[i] = '\0';
	return (0);
}

int		buff_nl(char **rest, char **line, char *buff) 
{
	int		nl;

	nl = get_nl(buff);
	/*if (!(*line = (char *)malloc(sizeof(char) * (nl + 1))))
		return (-1);
	fill(*line, buff, '\n');*/
	if (!(*line))
	{
		if (!(*line = (char *)malloc(sizeof(char) * (nl + 1))))
			return (-1);
		fill(*line, buff, '\n');
	}
	else if (!(*line = str_join(*line, buff, '\n')))
		return (-1);
	if (!(*rest = (char *)malloc(sizeof(char) * (BUFFER_SIZE - nl + 1))))
		return (-1);
	fill(*rest, &buff[nl + 1], '\0');
	return (1);
}

int		buff_eof(char **line, char *buff)
{
	if (!(*line = str_join(*line, buff, '\0')))
		return (-1);
	return (0);
}

int		buff_full(char **line, char *buff)
{
	char	*new_line;

	if (*line)
	{
		if (!(new_line = str_join(*line, buff, '\0')))
			return (-1);
		free(*line);
		*line = new_line;
	}
	else
	{
		if (!(*line = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1))))
			return (-1);
		fill(*line, buff, '\0');
	}
	return (0);
}

int		get_next_line(int fd, char **line)
{
	static char *rest;
	char		buff[BUFFER_SIZE + 1];
	int			b_read;
	int			ret;
	int			test;

	if (!line)
	{
		//printf("no line ?\n");
		return (-1);
	}
	*line = NULL;
	//printf("->rest = %s\n", rest);
	if ((ret = rest_mgmt(&rest, line)))
	{
		//printf("--->ret part<---\n");
		//printf("=>ret rest_mgmt = %d\n", ret);
		return (ret);
	}
	//printf("=>ret rest_mgmt = %d\n", ret);
	//printf("--->line after rest = %s\n", *line);
	while (1)
	{
		if (!(b_read = read(fd, buff, BUFFER_SIZE)))
		{
			//printf("errno: %d\n", errno);
			//printf("%s\n", strerror(errno));
			return (-1);
		}
		buff[b_read] = '\0';
		//printf("buff = %s\n", buff);
		//printf("get_nl = %d\n", get_nl(buff));
		if (get_nl(buff) != -1)
		{
			//printf ("--->nl part<---\n");
			test = buff_nl(&rest, line, buff);
			//printf("buff_nl = %d\n", test);
			//printf("line in nl part = %s\n", *line); 
			return (test);
		}
		else if (get_nl(buff) == -1 && b_read < BUFFER_SIZE)
		{
			//printf("--->eof part<---\n");
			//printf("line in eof = %s\n", *line);
			test = buff_eof(line, buff);
			//printf("buff_eof = %d\n", test);
			return (test);
		}
		if (buff_full(line, buff))
		{
			//printf("--->full part<---\n");
			return (-1);
		}
	}
}

#include <fcntl.h>

int	main(void)
{
	char	*line;
	int		fd;
	int		ret;

	fd = open("./main.c", O_RDONLY);
	while (1)
	{

		ret = get_next_line(fd, &line);
		printf("%s\n", line);
		if (!ret || ret == -1)
			break ;
	}
	return (0);
}