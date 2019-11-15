#include "get_next_line.h"

void	fill(char *dst, const char *src, char end)
{
	int i;

	i = 0;
	while (src[i] && src[i] != end)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
}

int		concat(char **line, char *buff, char end)
{
	char	*new_line;
	int		len_line;
	int		len_buff;
	
	len_line = 0;
	if (*line)
	{
		len_line = 0;
		while ((*line)[len_line])
			len_line++;
	}
	len_buff = 0;
	while (buff[len_buff])
		len_buff++;
	if (!(new_line = (char *)malloc(sizeof(char) *
	(len_line + len_buff + 1))))
		return (-1);
	if (*line)
		fill(new_line, *line, end);
	fill(&new_line[len_line], buff, end);
	free(*line);
	*line = new_line;
	return (0);
}

int		only_eof(char **line)
{
	if (!*line)
	{
		if (!(*line = (char *)malloc(1)))
			return (-1);
		**line = '\0';
	}
	return (0);
}