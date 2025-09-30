/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 12:00:18 by miaviles          #+#    #+#             */
/*   Updated: 2025/02/20 18:16:46 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 12:00:18 by miaviles          #+#    #+#             */
/*   Updated: 2025/02/21 12:00:00 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* ----------------------------- helpers ---------------------------------- */

size_t	gnl_strlen(const char *s)
{
	size_t i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

char	*gnl_strchr(const char *s, int c)
{
	if (!s)
		return (NULL);
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		++s;
	}
	if (c == '\0')
		return ((char *)s);
	return (NULL);
}

char	*gnl_strdup(const char *s)
{
	size_t	len;
	char	*out;
	size_t	i;

	if (!s)
		return (NULL);
	len = gnl_strlen(s);
	out = (char *)malloc(len + 1);
	if (!out)
		return (NULL);
	i = 0;
	while (i < len)
	{
		out[i] = s[i];
		++i;
	}
	out[len] = '\0';
	return (out);
}

char	*gnl_substr(const char *s, size_t start, size_t len)
{
	size_t	i;
	size_t	slen;
	char	*out;

	if (!s)
		return (NULL);
	slen = gnl_strlen(s);
	if (start >= slen)
		return (gnl_strdup(""));
	if (len > slen - start)
		len = slen - start;
	out = (char *)malloc(len + 1);
	if (!out)
		return (NULL);
	i = 0;
	while (i < len)
	{
		out[i] = s[start + i];
		++i;
	}
	out[len] = '\0';
	return (out);
}

/* concatena s1 + s2; libera s1. (s2 no se libera) */
char	*gnl_join_free(char *s1, const char *s2)
{
	size_t	l1 = gnl_strlen(s1);
	size_t	l2 = gnl_strlen(s2);
	char	*out;
	size_t	i;

	out = (char *)malloc(l1 + l2 + 1);
	if (!out)
	{
		free(s1);
		return (NULL);
	}
	i = 0;
	while (i < l1)
	{
		out[i] = s1[i];
		++i;
	}
	i = 0;
	while (i < l2)
	{
		out[l1 + i] = s2[i];
		++i;
	}
	out[l1 + l2] = '\0';
	free(s1);
	return (out);
}

/* --------------------------- núcleo GNL --------------------------------- */

static int	load_until_nl(int fd, char **stash)
{
	char	buf[BUFFER_SIZE + 1];
	ssize_t	n;

	while (!gnl_strchr(*stash, '\n'))
	{
		n = read(fd, buf, BUFFER_SIZE);
		if (n < 0)
			return (-1);
		if (n == 0)
			break ;
		buf[n] = '\0';
		*stash = gnl_join_free(*stash, buf);
		if (!*stash)
			return (-1);
	}
	return (0);
}

static char	*pop_line(char **stash)
{
	char	*nl;
	size_t	len_to_nl;
	char	*line;
	char	*rest;

	if (!*stash || **stash == '\0')
		return (NULL);
	nl = gnl_strchr(*stash, '\n');
	if (nl)
	{
		len_to_nl = (size_t)(nl - *stash) + 1;
		line = gnl_substr(*stash, 0, len_to_nl);
		rest = gnl_strdup(*stash + len_to_nl);
		free(*stash);
		*stash = rest;
		return (line);
	}
	/* última línea sin '\n' */
	line = *stash;
	*stash = NULL;
	return (line);
}

char	*get_next_line(int fd)
{
	/* static local a la función: permitido por Norm; no hay variables globales de fichero */
	static char	*stash[GNL_MAX_FD];
	int			status;
	char		*line;

	if (fd < 0 || fd >= GNL_MAX_FD || BUFFER_SIZE <= 0)
		return (NULL);
	if (!stash[fd])
	{
		stash[fd] = gnl_strdup("");
		if (!stash[fd])
			return (NULL);
	}
	status = load_until_nl(fd, &stash[fd]);
	if (status < 0)
	{
		free(stash[fd]);
		stash[fd] = NULL;
		return (NULL);
	}
	line = pop_line(&stash[fd]);
	if (!line)
	{
		free(stash[fd]);
		stash[fd] = NULL;
	}
	return (line);
}