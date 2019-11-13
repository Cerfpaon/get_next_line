#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

# define BUFFER_SIZE 32

int		get_nl(char *buff);

void	hihi(char *rest)
{
	*(rest) = 'a';
	*(rest + 1) = 'b';
	*(rest + 2) = 'c';
	*(rest + 3) = '\0';
}

void	function(char *buff)
{
	printf("%s\n", buff);
}

int		main(void)
{
	char buff[BUFFER_SIZE + 1];
	int fd = open("./test.txt", O_RDONLY);
	int ret = read(fd, buff, BUFFER_SIZE);
	buff[ret] = '\0';
	function(buff);


	return (0);
}