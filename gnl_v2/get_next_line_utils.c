#include "get_next_line.h"

void	fill(char *src, char *dst, char end)
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