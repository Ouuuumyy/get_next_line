#include "get_next_line.h"


char	*ft_strchr(const char *s, int c)
{
	char	ch;
	int		i;

	i = 0;
	ch = (char)c;
	while (s[i])
	{
		if (s[i] == ch)
			return ((char *)(s + i));
		i++;
	}
	if (ch == '\0')
		return ((char *)(s + i));
	return (NULL);
}

static char *next;
char *read_buff(int fd)
{
    char ch;
    char *buff;

    buff = malloc(BUFFER_SIZE);

    size_t len = 0;
    read(fd, buff, BUFFER_SIZE);
    return buff;
}

char *read_line(char *buffer)
{
    size_t i;
    size_t len;

    i = 0;
    len = 0;
    char *line;
    next = ft_strchr(buffer, '\n') + 1;
    while(buffer[len] != '\n')
        len++;
    line = (char *)malloc(len * sizeof(char));
    while(buffer[i] != '\n')
    {
        line[i] = buffer[i];
        i++;
    }
    line[i] = '\0';
    return line;
}

char *get_next_line(int fd)
{
    char *buff;
    char *line;

    if(next)
    {
        buff = next;
    }
    else
        buff = read_buff(fd);
    line = read_line(buff);
    return line;
}

int main()
{
    int fd;
    char *ptr;
    char *ptr1;
    int i = 0;
    fd = open("text.txt", O_RDWR, 0666);

    if(fd < 0)
    {
        printf("error opening file");
        return 1;
    }
    ptr = get_next_line(fd);
    while(ptr)
    {
        write(1, &ptr[i], 1);
        i++;
    }
    ptr1 = get_next_line(fd);
    i = 0;
    while(ptr1)
    {
        write(1, &ptr1[i], 1);
        i++;
    }
    free(ptr);
    free(ptr1);
    close(fd);
}