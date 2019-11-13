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

	//printf("--->wtf line?? = %s\n", line);
	//printf("ft_strlen(line) = %d\n", ft_strlen(line));
	//printf("get_nl(buff) = %d\n", get_nl(buff));
	if (end == '\n')
		size = ft_strlen(line) + get_nl(buff);
	else
		size = ft_strlen(line) + ft_strlen(buff);
	if (!(new_line = (char *)malloc(sizeof(char) * (size + 1))))
		return (NULL);
	fill(new_line, line, '\0');
	fill(&new_line[ft_strlen(line)], buff, end);

	//printf("new_line = %s\n", new_line);
	return (new_line);
}