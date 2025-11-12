/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbride <pbride@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 16:50:01 by pbride            #+#    #+#             */
/*   Updated: 2025/11/12 14:58:48 by pbride           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strdup(const char *s)
{
	char	*no;
	int		i;
	int		size;

	size = 0;
	while (s[size])
		size++;
	no = malloc(sizeof(char) * (size + 1));
	if (!no)
		return (NULL);
	i = 0;
	while (s[i])
	{
		no[i] = s[i];
		i++;
	}
	no[i] = '\0';
	return (no);
}

size_t	ft_strlcpy(char *dst, char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	if (dstsize == 0)
		return (ft_strlen(src));
	while (src[i] != '\0' && i < dstsize - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (ft_strlen(src));
}

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	char	*ret;
	size_t	s_len;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (start >= s_len)
		return (ft_strdup(""));
	if (s_len - start < len)
		len = s_len - start;
	ret = malloc(sizeof(char) * (len + 1));
	if (!ret)
		return (NULL);
	ft_strlcpy(ret, s + start, len + 1);
	return (ret);
}

char	*ft_strchr(char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if ((char)c == '\0')
		return ((char *)s);
	return (NULL);
}

static void	*ft_free(char **s, size_t i)
{
	while (i--)
		free(s[i]);
	free(s);
	return (NULL);
}

static size_t	ft_countwords(char *s, char c)
{
	size_t	count;

	if (!*s)
		return (0);
	count = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
		{
			count++;
			while (*s && *s != c)
				s++;
		}
	}
	return (count);
}

static char	**ft_fill_split(char **split, char *s, char c)
{
	size_t	word_len;
	int		i;

	i = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
		{
			if (ft_strchr(s, c))
				word_len = (size_t)(ft_strchr(s, c) - s);
			else
				word_len = ft_strlen(s);
			split[i] = ft_substr(s, 0, word_len);
			if (!split[i])
				return (ft_free(split, i));
			s += word_len;
			i++;
		}
	}
	split[i] = NULL;
	return (split);
}

char	**ft_split(char *s, char c)
{
	char	**split;

	if (!s)
		return (NULL);
	split = (char **)malloc(sizeof(char *) * (ft_countwords(s, c) + 1));
	if (!split)
		return (NULL);
	return (ft_fill_split(split, s, c));
}
void	*ft_memcpy(void *dst, void *src, size_t n)
{
	unsigned char	*ptr_dst;
	unsigned char	*ptr_src;
	size_t			i;

	i = 0;
	if ((!dst && !src) || n == 0)
		return (dst);
	ptr_dst = (unsigned char *)dst;
	ptr_src = (unsigned char *)src;
	while (i < n)
	{
		*(ptr_dst++) = *(ptr_src++);
		i++;
	}
	return (dst);
}

char *join_path(char *dir, char *cmd) {
	size_t dl = ft_strlen(dir);
	size_t cl = ft_strlen(cmd);
	int need_slash = (dl > 0 && dir[dl-1] != '/');
	char *out = malloc(dl + need_slash + cl + 1);

	if (!out) return NULL;
	ft_memcpy(out, dir, dl);
	if (need_slash) { out[dl] = '/'; }
	ft_memcpy(out + dl + need_slash, cmd, cl);
	out[dl + need_slash + cl] = '\0';
	return (out);
}

int	main(int argc, char **argv, char **envp)
{
	char	*path;
	int		size;
	char **directories;
	struct stat st;

	size = ft_strlen(getenv("PATH"));
	path = malloc(sizeof(char) * size);
	path = getenv("PATH");
	printf("PATH environment variable == %s\nsize == %d\n", path, size);
	//stat()
	directories = ft_split(path, ':');
	int	j = 0;
	while (directories[j])
	{
		printf("%s\n", directories[j]);
		printf("retour de stat()=%d\n",
			stat(join_path(directories[j], "cat"), &st));

		if (stat(join_path(directories[j], "cat"), &st) == 0)
			execve(join_path(directories[j], "cat"), argv + 1, envp);
		j++;
	}
	return (0);
}
