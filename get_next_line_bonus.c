//					header

#include "get_next_line_bonus.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strchr(char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
			return (s);
		s++;
	}
	if (c == '\0')
		return (s);
	return (NULL);
}

static char	*get_from_bfr(char **remain)
{
	char	*ligne;
	char	*new_remain;
	size_t	i;

	i = 0;
	while ((*remain)[i] && (*remain)[i] != '\n')
		i++;
	if ((*remain)[i] == '\n')
	{
		ligne = ft_substr(*remain, 0, i + 1);
		new_remain = ft_strdup(*remain + i + 1);
		free(*remain);
		*remain = new_remain;
		if (**remain == '\0')
			*remain = NULL;
	}
	else
	{
		ligne = ft_strdup(*remain);
		*remain = NULL;
	}
	return (free(*remain), ligne);
}

static int	read_bf(int fd, char **remain)
{
	char	buffer[BUFFER_SIZE + 1];
	char	*temp;
	ssize_t	read3d;

	read3d = read(fd, buffer, BUFFER_SIZE);
	if (read3d <= 0)
		return (read3d);
	buffer[read3d] = '\0';
	temp = ft_strjoin(*remain, buffer);
	free(*remain);
	*remain = temp;
	return (read3d);
}

char	*get_next_line(int fd)
{
	static t_list	*head;
	t_list			*current_fd;
	char			*ligne;
	ssize_t			ar3bi;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	current_fd = add_node_fd(&head, fd);
	if (!current_fd)
		return (NULL);
	ar3bi = 1;
	while (ar3bi > 0)
	{
		if (current_fd->buf_str && ft_strchr(current_fd->buf_str, '\n'))
			return (get_from_bfr(&current_fd->buf_str));
		ar3bi = read_bf(fd, &current_fd->buf_str);
		if (ar3bi == -1)
			return (NULL);
	}
	ligne = get_from_bfr(&current_fd->buf_str);
	if (!ligne)
		remove_fd(&head, fd);
	return (ligne);
}

----------------------------------------------------------------------------------------

#include "get_next_line_bonus.h"

static void	read_line(t_line **cache, int fd);
static int	is_new_line(t_line *cache);
static void	create_line(t_line *cache, char **line);
static void	refactor_line(t_line **cache);

char	*get_next_line(int fd)
{
	static t_line	*cache[OPEN_MAX] = {NULL};
	char			*line;

	line = NULL;
	if (fd < 0 || fd > OPEN_MAX || BUFFER_SIZE <= 0)
		return (NULL);
	read_line(&cache[fd], fd);
	if (!cache[fd])
		return (NULL);
	create_line(cache[fd], &line);
	refactor_line(&cache[fd]);
	return (line);
}

static void	read_line(t_line **cache, int fd)
{
	int		output;
	char	*buffer;
	t_line	*new_node;

	output = 0;
	while (!is_new_line(*cache))
	{
		buffer = NULL;
		new_node = ft_lstnew(buffer);
		new_node->content = ft_calloc(sizeof(*buffer), (BUFFER_SIZE + 1));
		output = read(fd, new_node->content, BUFFER_SIZE);
		if (output == 0 || output == -1)
		{
			free(new_node->content);
			free(new_node);
			return ;
		}
		new_node->content[BUFFER_SIZE] = '\0';
		ft_lstadd_back(cache, new_node);
	}
}

static int	is_new_line(t_line *cache)
{
	int		i;

	cache = ft_lstlast(cache);
	if (!cache)
		return (0);
	i = 0;
	while (cache->content[i] != '\0')
	{
		if (cache->content[i] == '\n')
		{
			cache->length = ++i;
			return (1);
		}
		i++;
	}
	cache->length = i;
	return (0);
}

static void	create_line(t_line *cache, char **line)
{
	int		ln_size;
	int		i;
	t_line	*temp;

	temp = cache;
	ln_size = 0;
	while (temp)
	{
		ln_size = ln_size + temp->length;
		temp = temp->next;
	}
	if (!ln_size)
		return ;
	*line = malloc(sizeof(**line) * (ln_size + 1));
	if (!line)
		return ;
	ln_size = 0;
	while (cache && cache->content)
	{
		i = 0;
		while (cache->content[i] && i < cache->length)
			(*line)[ln_size++] = cache->content[i++];
		cache = cache->next;
	}
	(*line)[ln_size] = '\0';
}

static void	refactor_line(t_line **cache)
{
	t_line	*temp;
	t_line	*new_node;
	char	*content;
	int		i;
	int		size;

	size = 0;
	temp = ft_lstlast(*cache);
	if (!temp)
		return ;
	content = temp->content;
	size = temp->length;
	temp->content = NULL;
	ft_lstclear(cache, free);
	i = 0;
	if (content[size] != '\0')
	{
		while (content[size] != '\0')
			content[i++] = content[size++];
		content[i] = '\0';
		new_node = ft_lstnew(content);
		ft_lstadd_back(cache, new_node);
	}
	else
		free(content);
}