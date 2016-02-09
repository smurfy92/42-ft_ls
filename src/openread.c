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

t_lstdir		*ft_add_stats(t_lstdir *lst, struct stat bufstat)
{
	lst->mdate = ft_strdup(ctime(&bufstat.st_mtime));
	lst->links = bufstat.st_nlink;
	lst->mode = bufstat.st_mode;
	lst->pwname = getpwuid(bufstat.st_uid)->pw_name;
	lst->grpname = getgrgid(bufstat.st_gid)->gr_name;
	lst->size = bufstat.st_size;
	lst->mtime = ctime(&bufstat.st_mtime);
	lst->isdir = (S_IFDIR & bufstat.st_mode);
	return (lst);
}

t_lstdir		*ft_create_lst(struct dirent *buf, t_options *opt)
{
	t_lstdir		*lst;
	char			*tmp;
	struct stat		bufstat;

	lst = NULL;
	if (opt->nbfile > 0 && opt->files[opt->actual][0] == '.'
	&& opt->files[opt->actual][1] == '.')
	{
		tmp = ft_strjoin(opt->files[opt->actual], "/");
		stat(ft_strjoin(tmp, buf->d_name), &bufstat);
	}
	else
		stat(buf->d_name, &bufstat);
	lst = (t_lstdir*)malloc(sizeof(t_lstdir));
	lst->name = ft_strdup(buf->d_name);
	lst = ft_add_stats(lst, bufstat);
	lst->next = NULL;
	return (lst);
}

t_lstdir		*ft_read_dir(char *dir, t_options *opt)
{
	DIR				*dirp;
	struct dirent	*buf;
	t_lstdir		*lst;

	lst = NULL;
	dirp = (DIR*)malloc(sizeof(DIR));
	dirp = opendir(dir);
	if (!dirp)
		return (NULL);
	while ((buf = readdir(dirp)))
		lst = ft_add_lst(ft_create_lst(buf, opt), lst);
	closedir(dirp);
	return (lst);
}
