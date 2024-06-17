/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomtom <tomtom@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 19:07:42 by thobenel          #+#    #+#             */
/*   Updated: 2024/06/11 00:00:51 by tomtom           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 52
# endif

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_list
{
	char			*buf_str;
	struct s_list	*next;
}					t_list;

void				str_cpy(t_list *list, char *str);
int					found_nwl(t_list *s_list);
void				list_new(t_list **list, char *buf);
int					len_to_newline(t_list *list);
t_list				*find_last_node(t_list *list);
void				create_lst(t_list **list, int fd);
char				*get_line(t_list *list);
void				point_mort(t_list **list, t_list *cl_node, char *buf);
void				poff_list(t_list **list);
char				*get_next_line(int fd);

#endif
