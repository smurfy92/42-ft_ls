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


t_lstdir		*ft_add_lst_by_date(t_lstdir *tmp, t_lstdir *lst)
{
	t_lstdir		*tmp2;

	if (!lst)
		return (tmp);
	if (!(ft_compare_date(tmp->mdate, lst->mdate)))
	{
		tmp->next = lst;
		return (tmp);
	}
	tmp2 = lst;
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
	if (ft_strcmp(tmp->name, lst->name) < 0)
	{
		tmp->next = lst;
		return (tmp);
	}
	tmp2 = lst;
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
	(getgrgid(bufstat.st_gid)) ? (lst->grpname = getgrgid(bufstat.st_gid)->gr_name) : (lst->grpname = ft_strdup("101"));
	lst->size = (int)bufstat.st_size;
	lst->mtime = ft_strdup(ctime(&bufstat.st_mtime));
	lst->isdir = (S_IFDIR & bufstat.st_mode);
	return (lst);
}

t_lstdir		*ft_create_lst(struct dirent *buf, t_options *opt)
{
	t_lstdir		*lst;
	char			*tmpstat;
	struct stat		bufstat;

	lst = NULL;
	if (opt->tmp[ft_strlen(opt->tmp) - 1] == '/')
		tmpstat = ft_strdup(ft_strjoin(opt->tmp, buf->d_name));
	else
	{
		tmpstat = ft_strdup(ft_strjoin(opt->tmp, "/"));
		tmpstat = ft_strdup(ft_strjoin(tmpstat, buf->d_name));
	}
	if (lstat(tmpstat, &bufstat) == -1)
	{
		//ft_putendl(tmpstat);
		//ft_error(tmpstat, 2);
	}
	lst = (t_lstdir*)malloc(sizeof(t_lstdir));
	lst->name = ft_strdup(buf->d_name);
	if (!(!opt->a && lst->name[0] == '.'))
		opt->total += bufstat.st_blocks;
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
	opt->total = 0;
	while ((buf = readdir(dirp)))
		lst = ft_add_lst(ft_create_lst(buf, opt), lst);
	closedir(dirp);
	return (lst);
}
