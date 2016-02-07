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
/*
t_lstdir		*ft_ls_t(t_lstdir *lst, t_options *opt)
{
	t_lstdir *tmp;
	t_lstdir *tmp2;

	tmp = lst;
	while (tmp)
	{
		if (ft_s)
		{
			
		}
		else
			tmp = tmp->next
	}
}
*/
t_lstdir		*ft_ls_r(t_lstdir *lst)
{
	t_lstdir *tmp;
	t_lstdir *tmp2;

 	tmp = NULL;
	while (lst)
	{
			tmp2 = lst->next;
			lst->next = tmp;
			tmp = lst;
			lst = tmp2;
	}
	return (tmp);
}

t_lstdir		*ft_add_lst(t_lstdir *tmp, t_lstdir *lst)
{
	t_lstdir		*tmp2;

	if (!lst)
		return (tmp);
	tmp2 = lst;
	if (ft_strcmp(tmp->name, lst->name) < 0)
	{
		tmp->next = lst;
		return (tmp);
	}
	while (lst->next && ft_strcmp(tmp->name, (lst->next)->name) > 0)
		lst = lst->next;
	if (lst->next)
		tmp->next = lst->next;
	lst->next = tmp;
	return (tmp2);
}

t_lstdir	*ft_create_lst(struct dirent *buf)
{
	t_lstdir		*lst;

	lst = (t_lstdir*)malloc(sizeof(t_lstdir));
	lst->name = ft_strdup(buf->d_name);
	lst->next = NULL;
	return (lst);
}

t_lstdir	*ft_read_dir(char *dir)
{
	DIR				*dirp = NULL;
	struct dirent	*buf;
	t_lstdir		*lst = NULL;

	dirp = (DIR*)malloc(sizeof(DIR));
	dirp = opendir(dir);
	if (!dirp)
		return (NULL);
	while ((buf = readdir(dirp)))
		lst = ft_add_lst(ft_create_lst(buf), lst);
	closedir(dirp);
	return (lst);
}
