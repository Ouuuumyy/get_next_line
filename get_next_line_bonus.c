/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oukadir <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 13:52:17 by oukadir           #+#    #+#             */
/*   Updated: 2024/12/19 13:52:23 by oukadir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line_bonus.h"

char	*join_buffers(char *next_line, char *buff)
{
	char	*temp;

	temp = ft_strjoin(next_line, buff);
	free(next_line);
	return (temp);
}

char	*read_buff(int fd, char *next_line)
{
	char	*buff;
	int		read_size;

	read_size = 1;
	buff = malloc((size_t)(BUFFER_SIZE + 1) * sizeof(char));
	if (!buff)
		return (NULL);
	while (read_size > 0)
	{
		read_size = read(fd, buff, BUFFER_SIZE);
		if (read_size == -1)
		{
			free(buff);
			return (NULL);
		}
		buff[read_size] = '\0';
		next_line = join_buffers(next_line, buff);
		if (ft_strchr(next_line, '\n'))
			break ;
	}
	free(buff);
	return (next_line);
}

char	*one_line(char *next_line)
{
	char	*line;
	int		i;
	int		j;

	j = 0;
	i = 0;
	if (!next_line)
		return (NULL);
	while (next_line[i] && next_line[i] != '\n')
		i++;
	line = malloc((i + (next_line[i] == '\n') + 1) * sizeof(char));
	if (!line)
		return (NULL);
	while (j < i)
	{
		line[j] = next_line[j];
		j++;
	}
	if (next_line[j] == '\n')
		line[j++] = '\n';
	line[j] = '\0';
	return (line);
}

char	*remaining_line(char *next_line)
{
	char	*temp;

	temp = ft_strchr(next_line, '\n');
	if (!temp)
	{
		free(next_line);
		return (NULL);
	}
	temp = ft_strdup(temp + 1);
	free(next_line);
	return (temp);
}

char	*get_next_line(int fd)
{
	static char	*next_line[FD_MAX];
	char		*line;

	if (fd < 0 || read(fd, NULL, 0) < 0 || BUFFER_SIZE <= 0 || fd > 1024)
		return (NULL);
	if (!next_line[fd])
	{
		next_line[fd] = malloc(1);
		if (next_line[fd])
			next_line[fd][0] = '\0';
	}
	if (!ft_strchr(next_line[fd], '\n'))
	{
		next_line[fd] = read_buff(fd, next_line[fd]);
		if (!next_line[fd] || next_line[fd][0] == '\0')
		{
			free(next_line[fd]);
			return (NULL);
		}
	}
	line = one_line(next_line[fd]);
	next_line[fd] = remaining_line(next_line[fd]);
	return (line);
}

// int	main(void)
// {
// 	int fd;
// 	char *next_line;
// 	fd = open("text.txt", O_RDWR, 0666);
// 	if (fd < 0)
// 		printf("error when opening file");
// 	while ((next_line = get_next_line(fd)) != NULL)
// 	{
// 		printf("%s", next_line);
// 		free(next_line);
// 	}
// 	close(fd);
// 	return (0);
// }

// int	main(void)
// {
// 	int		fd;
// 	char	*next_line;
// 	int		fd1;

// 	fd = open("text.txt", O_RDWR, 0666);
// 	fd1 = open("text1.txt", O_RDWR);
// 	if (fd < 0)
// 		printf("error when opening file");
// 	next_line = get_next_line(fd);
// 	printf("%s", next_line);
// 	free(next_line);
// 	next_line = get_next_line(fd1);
// 	printf("%s", next_line);
// 	free(next_line);
// 	next_line = get_next_line(fd);
// 	printf("%s", next_line);
// 	free(next_line);
// 	next_line = get_next_line(fd1);
// 	printf("%s", next_line);
// 	free(next_line);
// 	close(fd);
// 	return (0);
// }
