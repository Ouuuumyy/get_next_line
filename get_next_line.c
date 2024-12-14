#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include "get_next_line.h"


char *join_buffers(char *next_line, char *buff)
{
    char *temp;

    temp = ft_strjoin(next_line, buff);
    free(next_line);
    return temp;
}

char *read_buff(int fd, char *next_line)
{
    char *buff;
    int read_size;

    read_size = 1;
    buff = malloc((size_t)(BUFFER_SIZE + 1) * sizeof(char));
    if(!buff)
        return(NULL);
    while(read_size > 0)
    {
        read_size = read(fd, buff, BUFFER_SIZE);
        if(read_size <= 0)
        {
            free(buff);
            return(NULL);
        }
        buff[read_size] = '\0';
        next_line = join_buffers(next_line, buff);
        if(ft_strchr(next_line, '\n'))
            break;
    }
    free(buff);
    return next_line;
}

char *one_line(char *next_line)
{
    char *line;
    int i;
    int j = 0;

    i = 0;
    if(!next_line)
        return NULL;
    while(next_line[i] && next_line[i] != '\n')
        i++;
    line = malloc((i + (next_line[i] == '\n') + 1) * sizeof(char));
    if(!line)
        return NULL;
    while(j < i)
    {
        line[j] = next_line[j];
        j++;
    }
    if(next_line[j] == '\n')
        line[j++] = '\n';
    line[j] = '\0';
    return line;
}

char *remaining_line(char *next_line)
{
    char *temp;

    temp = ft_strchr(next_line, '\n');
    if(!temp)
    {
        free(next_line);
        return NULL;
    }
   
    temp = ft_strdup(temp + 1);
    free(next_line);
    return temp;
    
}
char *get_next_line(int fd)
{
    static char *next_line;
    char *line;

    if(fd < 0 || read(fd, NULL, 0) < 0 || BUFFER_SIZE <= 0)
        return(NULL);
    if(!next_line)
        next_line = malloc(1);
    if(!ft_strchr(next_line, '\n'))
    {
        next_line = read_buff(fd, next_line);
        if(!next_line)
        {
            free(next_line);
            return(NULL);
        }
    }
    line = one_line(next_line);
    next_line = remaining_line(next_line);
  //  printf("%s\n", next_line);
    return line;
}

int main()
{
    int fd;
    char *next_line;
    fd = open("text.txt", O_RDWR, 0666);
    if(fd < 0)
    printf("error when opening file");
    while((next_line = get_next_line(fd)) != NULL)
    {
        printf("%s",next_line);
        free(next_line);
    }
    close(fd);
    return 0;
}