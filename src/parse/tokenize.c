#include "../../include/cub3d.h"

/* count words separated by spaces/tabs ----------------------------------- */
static int	word_count(char *s)
{
	int	words;

	words = 0;
	while (*s)
	{
		while (*s == ' ' || *s == '\t')
			++s;
		if (*s)
		{
			++words;
			while (*s && *s != ' ' && *s != '\t')
				++s;
		}
	}
	return (words);
}

/* duplicate a single word ------------------------------------------------- */
static char	*dup_word(char **s)
{
	char	*start;
	char	*dup;
	int		len;

	start = *s;
	len = 0;
	while (start[len] && start[len] != ' ' && start[len] != '\t')
		++len;
	dup = (char *)malloc(len + 1);
	if (!dup)
		return (NULL);
	ft_memcpy(dup, start, len);
	dup[len] = '\0';
	*s = start + len;
	return (dup);
}

/* public: split line into NULL-terminated array --------------------------- */
char	**tokenize_line(char *line)
{
	char	**arr;
	int		w;
	int		i;

	w = word_count(line);
	arr = (char **)ft_calloc(w + 1, sizeof(char *));
	if (!arr)
		return (NULL);
	i = 0;
	while (i < w)
	{
		while (*line == ' ' || *line == '\t')
			++line;
		arr[i] = dup_word(&line);
		if (!arr[i])
			return (free_arr(arr), NULL);
		++i;
	}
	arr[i] = NULL;
	return (arr);
}
