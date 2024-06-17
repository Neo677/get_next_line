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
	free(remain);
	return (ligne);
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