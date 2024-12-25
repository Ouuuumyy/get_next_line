/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oukadir <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 13:52:39 by oukadir           #+#    #+#             */
/*   Updated: 2024/12/19 13:52:43 by oukadir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

char	*ft_strchr(const char *s, int c);
char	*ft_strjoin(char const *s1, char const *s2);
char	*read_buff(int fd, char *next);
char	*ft_strdup(const char *str);
size_t	ft_strcpy(char *dst, const char *src);
char	*join_buffers(char *next_line, char *buff);
char	*one_line(char *next_line);
char	*remaining_line(char *next_line);
char	*get_next_line(int fd);
#endif
