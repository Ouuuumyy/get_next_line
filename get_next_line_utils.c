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

size_t	ft_strlen(const char *c)
{
	size_t	len;

	len = 0;
	while (c[len])
	{
		len++;
	}
	return (len);
}

char	*ft_strdup(const char *str)
{
	int		i;
	int		len;
	char	*c;

	i = 0;
	len = 0;
	while (str[len])
		len++;
	c = (char *)malloc((len + 1) * sizeof(char));
	if (c == NULL)
		return (NULL);
	while (i < len)
	{
		c[i] = str[i];
		i++;
	}
	c[i] = '\0';
	return (c);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	i;
	size_t	j;
	size_t	len1;
	size_t	len2;

	i = 0;
	j = 0;
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	if (!s1 || !s2)
		return (NULL);
	str = (char *)malloc(sizeof(char) * (len1 + len2 + 1));
	if (str == NULL)
		return (NULL);
	while (i < len1)
	{
		str[i] = s1[i];
		i++;
	}
	while (i < (len1 + len2))
		str[i++] = s2[j++];
	str[i] = '\0';
	return (str);
}