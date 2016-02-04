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
	t_lstdir		*tmp2;

	tmp = (t_lstdir*)malloc(sizeof(t_lstdir));
	tmp->name = buf->d_name;
	tmp->next = NULL;
	tmp2 = lst;
	/*
	if (ft_strcmp((tmp->buf)->d_name, (lst->buf)->d_name) < 0)
	{
		tmp->next = lst;
		return (tmp);
	}
	while (lst->next && ft_strcmp((tmp->buf)->d_name,((lst->next)->buf)->d_name) > 0)
		lst = lst->next;
	if (lst->next)
		tmp->next = lst->next;
	lst->next = tmp;
	return (tmp2);*/
	while (tmp2->next)
		tmp2 = tmp2->next;
	tmp2->next = tmp;
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
