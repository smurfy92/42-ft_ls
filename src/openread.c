/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   openread.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtranchi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/01 10:49:08 by jtranchi          #+#    #+#             */
/*   Updated: 2016/02/03 22:42:04 by jtranchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void		ft_add_lst(struct dirent *buf, t_lstdir *lst)
{
	t_lstdir 		*tmp;

	tmp = (t_lstdir*)malloc(sizeof(t_lstdir));
	tmp->name = ft_strdup(buf->d_name);
	tmp->next = NULL;
	while (lst->next)
		lst = lst->next;
	lst->next = tmp;
}

t_lstdir	*ft_create_lst(struct dirent *buf)
{
	t_lstdir		*lst;

	lst = (t_lstdir*)malloc(sizeof(t_lstdir));
	lst->name = buf->d_name;
	lst->next = NULL;
	return (lst);
}

t_lstdir	*ft_read_dir(char *dir)
{
	DIR				*dirp;
	struct dirent	*buf;
	t_lstdir		*lst;

	dirp = opendir(dir);
	if (!dirp)
		ft_error_nofile(dir);
	buf = readdir(dirp);
	lst = ft_create_lst(buf);
	while ((buf = readdir(dirp)))
		ft_add_lst(buf, lst);
	return (lst);
}
