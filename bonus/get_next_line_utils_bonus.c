//		header

#include "get_next_line_bonus.h"

t_list	*add_node_fd(t_list **head, int fd)
{
	t_list	*actuelle;

	actuelle = *head;
	while (actuelle)
	{
		if (actuelle->fd == fd)
			return (actuelle);
		actuelle = actuelle->next;
	}
	actuelle = (t_list *)malloc(sizeof(t_list));
	if (!actuelle)
		return (free(actuelle), NULL);
	actuelle->fd = fd;
	actuelle->buf_str = NULL;
	actuelle->next = *head;
	*head = actuelle;
	return (actuelle);
}

void	remove_fd(t_list **head, int fd)
{
	t_list	*act;
	t_list	*prevo;

	act = *head;
	prevo = NULL;
	while (act)
	{
		if (act->fd == fd)
		{
			if (prevo)
				prevo->next = act->next;
			else
				*head = act->next;
			free(act->buf_str);
			free(act);
			return ;
		}
		prevo = act;
		act = act->next;
	}
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*new;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (NULL);
	new = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!new)
		return (free(new), NULL);
	i = 0;
	while (s1[i])
	{
		new[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
		new[i++] = s2[j++];
	new[i] = '\0';
	return (new);
}

char	*ft_strdup(char *src)
{
	char	*dest;
	int		i;

	i = 0;
	dest = (char *)malloc(sizeof(char) * (ft_strlen(src) + 1));
	if (!dest)
		return (free(dest), NULL);
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	char *sub;
	size_t i;

	if (!s || start >= (unsigned int)ft_strlen(s))
		return (ft_strdup(""));
	sub = (char *)malloc(sizeof(char) * (len + 1));
	if (!sub)
		return (free(sub), NULL);
	i = 0;
	while (i < len && s[start + i])
	{
		sub[i] = s[start + i];
		i++;
	}
	sub[i] = '\0';
	return (sub);
}