#include "get_next_line.h"
#include <errno.h>
#include <string.h>

int		rest_mgmt(char **rest, char **line)
{
	int i;

	i = 0;
	if (!(*rest) || !(**rest))
		return (0);
	while ((*rest)[i] && (*rest)[i] != '\n')
		i++;
	if (!(*line = (char *)malloc(sizeof(char) * (i + 1))))
		return (-1);
	i = 0;
	while ((*rest)[i])
	{
		if ((*rest)[i] == '\n')
		{
			// *rest = make_new_rest(rest, i + 1);
			*rest = &(*rest)[i + 1];
			(*line)[i] = '\0';
			return (1);
		}
		(*line)[i] = (*rest)[i];
		i++;
	}
	(*line)[i] = '\0';
	free(*rest);
	return (0);
}

int		buff_nl(char **rest, char **line, char *buff) 
{
	int		nl;

	nl = get_nl(buff);
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
	static char *rest = NULL;
	char		buff[BUFFER_SIZE + 1];
	int			b_read;
	int			ret;

	b_read = 0;
	ret = 0;
	if (!line)
		return (-1);
	*line = NULL;
	if ((ret = rest_mgmt(&rest, line)))
		return (ret);
	while (1)
	{
		if ((b_read = read(fd, buff, BUFFER_SIZE) < 0))
			return (-1);
		buff[b_read] = '\0';
		if (get_nl(buff) != -1)
			return(buff_nl(&rest, line, buff));
		else if (get_nl(buff) == -1 && b_read < BUFFER_SIZE)
			return(buff_eof(line, buff));
		if (buff_full(line, buff))
			return (-1);
	}
}

// #include <fcntl.h>

// int	main(void)
// {
// 	char	*line;
// 	int		fd;
// 	int		ret;

// 	fd = open("./test.txt", O_RDONLY);
// 	while (1)
// 	{
// 		ret = get_next_line(fd, &line);
// 		printf("%s\n", line);
// 		if (!ret || ret == -1)
// 			break ;
// 		free(line);
// 	}
// 	return (0);
// }

#include "get_next_line.h"
#include <fcntl.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
	int             fd;
	int             i;
	int             j;
	char    		*line = 0;
	char			*lineadress[66];
	
	j = 1;
	printf("\n==========================================\n");
	printf("========== TEST 1 : The Alphabet =========\n");
	printf("==========================================\n\n");

	if (!(fd = open("../42TESTERS-GNL/files/alphabet", O_RDONLY)))
	{
		printf("Error in open\n");
		return (0);
	}
	while ((i = get_next_line(fd, &line)) > 0)
	{
		printf("|%s\n", line);
		// write(1, "1", 1);
		lineadress[j - 1] = line;
		j++;
	}
	printf("|%s\n", line);
	free(line);
	close(fd);
	if (BUFFER_SIZE == 0 && i == -1)
		printf ("Well Done - Returned -1\n");
	else if (BUFFER_SIZE == 0 && i != -1)
		printf ("Not Good - Did not return -1 for BUFFER_SIZE=0\n");
	else if (i == -1)
		printf ("Error in Fonction - Returned -1\n");
	else if (j == 66)
		printf("Well Done\n");
	else if (j != 66)
		printf("Not Good - Wrong Number Of Lines\n");
	while (--j > 0)
		free(lineadress[j - 1]);
	j = 1;

	printf("\n==========================================\n");
	printf("========= TEST 2 : Empty Lines ===========\n");
	printf("==========================================\n\n");

	if (!(fd = open("files/empty_lines", O_RDONLY)))
	{
		printf("Error in open\n");
		return (0);
	}
	while ((i = get_next_line(fd, &line)) > 0)
	{
		printf("|%s\n", line);
		free(line);
		j++;
	}
	printf("|%s\n", line);
	free(line);
	close(fd);
	if (BUFFER_SIZE == 0 && i == -1)
		printf ("Well Done - Returned -1\n");
	else if (BUFFER_SIZE == 0 && i != -1)
		printf ("Not Good - Did not return -1 for BUFFER_SIZE=0\n");
	else if (i == -1)
		printf ("Error in Fonction - Returned -1\n");
	else if (j == 9)
		printf("Well Done\n");
	else if (j != 9)
		printf("Not Good - Wrong Number Of Lines\n");
	j = 1;
	printf("\n==========================================\n");
	printf("======== TEST 3 : The Empty File =========\n");
	printf("==========================================\n\n");

	if (!(fd = open("files/empty_file", O_RDONLY)))
	{
		printf("Error in open\n");
		return (0);
	}
	while ((i = get_next_line(fd, &line)) > 0)
	{
		printf("|%s\n", line);
		free(line);
		j++;
	}
	printf("|%s\n", line);
	free(line);
	close(fd);
	if (BUFFER_SIZE == 0 && i == -1)
		printf ("Well Done - Returned -1\n");
	else if (BUFFER_SIZE == 0 && i != -1)
		printf ("Not Good - Did not return -1 for BUFFER_SIZE=0\n");
	else if (i == -1)
		printf ("Error in Fonction - Returned -1\n");
	else if (j == 1)
		printf("Well Done\n");
	else if (j != 1)
		printf("Not Good - Wrong Number Of Lines\n");
	j = 1;
	printf("\n==========================================\n");
	printf("========= TEST 4 : One New Line ==========\n");
	printf("==========================================\n\n");

	if (!(fd = open("files/1_newline", O_RDONLY)))
	{
		printf("Error in open\n");
		return (0);
	}
	while ((i = get_next_line(fd, &line)) > 0)
	{
		printf("|%s\n", line);
		free(line);
		j++;
	}
	printf("|%s\n", line);
	free(line);
	close(fd);
	if (BUFFER_SIZE == 0 && i == -1)
		printf ("Well Done - Returned -1\n");
	else if (BUFFER_SIZE == 0 && i != -1)
		printf ("Not Good - Did not return -1 for BUFFER_SIZE=0\n");
	else if (i == -1)
		printf ("Error in Fonction - Returned -1\n");
	else if (j == 2)
		printf("Well Done\n");
	else if (j != 2)
		printf("Not Good - Wrong Number Of Lines\n");
	j = 1;
	printf("\n==========================================\n");
	printf("========= TEST 5 : Four New Lines ========\n");
	printf("==========================================\n\n");

	if (!(fd = open("files/4_newlines", O_RDONLY)))
	{
		printf("Error in open\n");
		return (0);
	}
	while ((i = get_next_line(fd, &line)) > 0)
	{
		printf("|%s\n", line);
		free(line);
		j++;
	}
	printf("|%s\n", line);
	free(line);
	close(fd);
	if (BUFFER_SIZE == 0 && i == -1)
		printf ("Well Done - Returned -1\n");
	else if (BUFFER_SIZE == 0 && i != -1)
		printf ("Not Good - Did not return -1 for BUFFER_SIZE=0\n");
	else if (i == -1)
		printf ("Error in Fonction - Returned -1\n");
	else if (j == 5)
		printf("Well Done\n");
	else if (j != 5)
		printf("Not Good - Wrong Number Of Lines\n");
	j = 1;
	printf("\n==========================================\n");
	printf("========= TEST 6 : Wrong Input ===========\n");
	printf("==========================================\n\n");

	if (!(fd = open("files/alphabet", O_RDONLY)))
	{
		printf("Error in open\n");
		return (0);
	}
	if (get_next_line(180, &line) == -1)
		printf("Well Done, you return -1 if no FD\n");
	else
		printf("Not Good, you don't return -1 if no FD\n");
	if (get_next_line(fd, 0) == -1)
		printf("Well Done, you return -1 if no line\n");
	else
		printf("Not Good, you don't return -1 if no line\n");
	close(fd);
	j = 1;
	printf("\n==========================================\n");
	printf("============== TEST 7 : 42 ===============\n");
	printf("==========================================\n\n");

	if (!(fd = open("files/41_char", O_RDONLY)))
	{
		printf("Error in open\n");
		return (0);
	}
	while ((i = get_next_line(fd, &line)) > 0)
	{
		printf("|%s\n", line);
		free(line);
		j++;
	}
	printf("|%s\n", line);
	free(line);
	close(fd);
	if (!(fd = open("files/42_char", O_RDONLY)))
	{
		printf("Error in open\n");
		return (0);
	}
	while ((i = get_next_line(fd, &line)) > 0)
	{

		printf("|%s\n", line);
		free(line);
		j++;
	}
	printf("|%s\n", line);
	free(line);
	close(fd);
	if (!(fd = open("files/43_char", O_RDONLY)))
	{
		printf("Error in open\n");
		return (0);
	}
	while ((i = get_next_line(fd, &line)) > 0)
	{
		printf("|%s\n", line);
		free(line);
		j++;
	}
	printf("|%s\n", line);
	free(line);
	close(fd);
	if (BUFFER_SIZE == 0 && i == -1)
		printf ("Well Done - Returned -1\n");
	else if (BUFFER_SIZE == 0 && i != -1)
		printf ("Not Good - Did not return -1 for BUFFER_SIZE=0\n");
	else if (i == -1)
		printf ("Error in Fonction - Returned -1\n");
	else if (j == 1)
		printf("Well Done\n");
	else if (j != 1)
		printf("Not Good - Wrong Number Of Lines\n");
	j = 1;
	printf("\n==========================================\n");
	printf("============= TEST 8 : Marge =============\n");
	printf("==========================================\n\n");

	int fd2;

	if (!(fd = open("files/half_marge_top", O_RDONLY)))
	{
		printf("Error in open\n");
		return (0);
	}
	if (!(fd2 = open("files/half_marge_bottom", O_RDONLY)))
	{
		printf("Error in open\n");
		return (0);
	}
	while ((i = get_next_line(fd, &line)) > 0)
	{
		printf("%s\n", line);
		free(line);
		j++;
	}
	while ((i = get_next_line(fd2, &line)) > 0)
	{
		printf("%s\n", line);
		free(line);
		j++;
	}
	printf("%s\n", line);
	close(fd);
	close(fd2);
	if (BUFFER_SIZE == 0 && i == -1)
		printf ("Well Done - Returned -1\n");
	else if (BUFFER_SIZE == 0 && i != -1)
		printf ("Not Good - Did not return -1 for BUFFER_SIZE=0\n");
	else if (i == -1)
		printf ("Error in Fonction - Returned -1\n");
	else if (j == 25)
		printf("Well Done\n");
	else if (j != 25)
		printf("Not Good - Wrong Number Of Lines\n");
	return (0);
}