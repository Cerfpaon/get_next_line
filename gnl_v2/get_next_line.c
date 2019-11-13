#include "get_next_line.h"

int	rest_management(char **rest, char **line)
{
	char	*tmp_rest;
	int		i;
	int		j;

	if (!(*rest) || (!(**rest)))
		return (0);
	i = 0;
	while (rest[i] && rest[i] != '\n')
		i++;
	
	if (rest[i] == '\n')
	{
		if (!(tmp_rest = (char *)malloc(sizeof(char) * (i + 1))))
			return (-1);
		fill(*rest, *line, '\n');
		fill(&rest[i + 1], new_rest, '\0');
		free(*rest);
		*rest = new_rest;
		return (1);
	}
	else
	{
		fill(rest, )
	}
	free(rest);
}

int	get_next_line(int fd, char **line)
{
	static char *rest;
	int			ret;

	if ((ret = rest_management(&rest, line)))
		return (ret);
}