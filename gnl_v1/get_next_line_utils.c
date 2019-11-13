#include "get_next_line.h"

static int	ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int			get_nl(char *buff)
{
	int	i;

	i = 0;
	while (buff[i])
	{
		if (buff[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

void		fill(char *dst, char *src, char end)
{
	int	i;

	i = 0;
	
	while (src[i] != end)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
}

char		*str_join(char *line, char *buff, char end)
{
	char	*new_line;
	int		size;

	if (end == '\n')
		size = ft_strlen(line) + get_nl(buff);
	else
		size = ft_strlen(line) + ft_strlen(buff);
	if (!(new_line = (char *)malloc(sizeof(char) * (size + 1))))
		return (NULL);
	fill(new_line, line, '\0');
	fill(&new_line[ft_strlen(line)], buff, end);
	return (new_line);
}

char		*make_new_rest(char **rest, int index)
{
	char	*new_rest;
	int		i;

	i = 0;
	if (!(new_rest = (char *)malloc(sizeof(char) * (ft_strlen(*rest) - index + 1))))
		return (NULL);
	while (rest[index])
	{
		new_rest[i] = (*rest)[index];
		index++;
		i++;
	}
	new_rest[i] = '\0';
	free(*rest);
	return (new_rest);
}
