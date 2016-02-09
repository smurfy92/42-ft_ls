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

int				ft_compare_date(char *s1, char *s2)
{
	if (ft_strncmp((s1 + 20), (s2 + 20), 4) > 0)
		return (0);
	if (ft_strncmp((s1 + 9), (s2 + 9), 10) > 0)
		return (0);
	return (1);
}

t_lstdir		*ft_add_lst_by_date(t_lstdir *tmp, t_lstdir *lst)
{
	t_lstdir		*tmp2;

	if (!lst)
		return (tmp);
	tmp2 = lst;
	if (!(ft_compare_date(tmp->mdate, lst->mdate)))
	{
		tmp->next = lst;
		return (tmp);
	}
	while (lst->next && ft_compare_date(tmp->mdate, (lst->next)->mdate))
		lst = lst->next;
	if (lst->next)
		tmp->next = lst->next;
	lst->next = tmp;
	return (tmp2);
}

t_lstdir		*ft_ls_t(t_lstdir *lst)
{
	t_lstdir *tmp;
	t_lstdir *tmp2;

	tmp = NULL;
	while (lst)
	{
		tmp2 = (t_lstdir*)malloc(sizeof(t_lstdir));
		tmp2->name = ft_strdup(lst->name);
		tmp2->mdate = ft_strdup(lst->mdate);
		tmp2->next = NULL;
		tmp = ft_add_lst_by_date(tmp2, tmp);
		lst = lst->next;
	}
	return (tmp);
}

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

t_lstdir	*ft_create_lst(struct dirent *buf, t_options *opt)
{
	t_lstdir		*lst = NULL;;
	char 			*tmp;
	struct stat 	bufstat;

	if (opt->nbfile > 0 && opt->files[opt->actual][0] == '.' && opt->files[opt->actual][1] == '.')
	{
		tmp = ft_strjoin(opt->files[opt->actual], "/");
		stat(ft_strjoin(tmp,buf->d_name), &bufstat);
	}
	else
		stat(buf->d_name, &bufstat);
	lst = (t_lstdir*)malloc(sizeof(t_lstdir));
	lst->name = ft_strdup(buf->d_name);
	lst->mdate = ft_strdup(ctime(&bufstat.st_mtime));
	lst->next = NULL;
	return (lst);
}

t_lstdir	*ft_read_dir(char *dir, t_options *opt)
{
	DIR				*dirp = NULL;
	struct dirent	*buf;
	t_lstdir		*lst = NULL;

	dirp = (DIR*)malloc(sizeof(DIR));
	dirp = opendir(dir);
	if (!dirp)
		return (NULL);
	while ((buf = readdir(dirp)))
		lst = ft_add_lst(ft_create_lst(buf, opt), lst);
	closedir(dirp);
	return (lst);
}
