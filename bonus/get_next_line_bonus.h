//					header

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef struct s_list
{
	int				fd;
	char			*buf_str;
	struct s_list	*next;
}					t_list;

char				*get_next_line(int fd);
t_list				*add_node_fd(t_list **head, int fd);
void				remove_fd(t_list **head, int fd);
int					ft_strlen(char *str);
char				*ft_strjoin(char *s1, char *s2);
char				*ft_strdup(char *src);
char				*ft_substr(char *s, unsigned int start, size_t len);
char				*ft_strchr(char *s, int c);

#endif