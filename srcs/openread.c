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

t_lstdir		*ft_add_stats(t_lstdir *lst, struct stat bufstat,
t_options *opt)
{
	lst->mdate = ft_strdup(ctime(&bufstat.st_mtime));
	lst->mdateint = bufstat.st_mtime;
	lst->nano = bufstat.st_mtimespec.tv_nsec;
	lst->ino = bufstat.st_ino;
	lst->links = bufstat.st_nlink;
	lst->mode = bufstat.st_mode;
	(getpwuid(bufstat.st_uid)) ?
	(lst->pwname = getpwuid(bufstat.st_uid)->pw_name) :
	(lst->pwname = ft_strdup(ft_itoa(bufstat.st_uid)));
	(getgrgid(bufstat.st_gid)) ?
	(lst->grpname = getgrgid(bufstat.st_gid)->gr_name) :
	(lst->grpname = ft_strdup(ft_itoa(bufstat.st_gid)));
	lst->mtime = ft_strdup(ctime(&bufstat.st_mtime));
	lst->isdir = S_ISDIR(bufstat.st_mode);
	lst->space_lnk = ft_check_cols(lst->links);
	(lst->space_lnk > opt->max_lnk &&
	(!(!opt->a && lst->name[0] == '.'))) ? (opt->max_lnk = lst->space_lnk) : 0;
	lst->space_uid = ft_strlen(lst->pwname);
	(lst->space_uid > opt->max_uid &&
	(!(!opt->a && lst->name[0] == '.'))) ? (opt->max_uid = lst->space_uid) : 0;
	lst->space_gid = ft_strlen(lst->grpname);
	(lst->space_gid > opt->max_gid &&
	(!(!opt->a && lst->name[0] == '.'))) ? (opt->max_gid = lst->space_gid) : 0;
	return (ft_add_stats_suite(lst, bufstat, opt));
}

t_lstdir		*ft_add_stats_suite(t_lstdir *lst, struct stat bufstat,
t_options *opt)
{
	if (S_ISCHR(lst->mode) || S_ISBLK(lst->mode))
	{
		lst->major = major(bufstat.st_rdev);
		lst->minor = minor(bufstat.st_rdev);
		lst->space_major = ft_check_cols(lst->major);
	}
	else
	{
		lst->major = 0;
		lst->minor = (int)bufstat.st_size;
		lst->space_major = 0;
	}
	lst->space_minor = ft_check_cols(lst->minor);
	(lst->space_minor > opt->max_minor &&
	(!(!opt->a && lst->name[0] == '.'))) ?
	(opt->max_minor = lst->space_minor) : 0;
	(lst->space_major > opt->max_major &&
	(!(!opt->a && lst->name[0] == '.'))) ?
	(opt->max_major = lst->space_major) : 0;
	return (lst);
}

t_lstdir		*ft_create_lst(char *buf, t_options *opt)
{
	t_lstdir		*lst;
	char			*tmpstat;
	struct stat		bufstat;

	lst = NULL;
	opt->lstnb++;
	if (opt->tmp[ft_strlen(opt->tmp) - 1] == '/')
		tmpstat = ft_strdup(ft_strjoin(opt->tmp, buf));
	else
	{
		tmpstat = ft_strdup(ft_strjoin(opt->tmp, "/"));
		tmpstat = ft_strdup(ft_strjoin(tmpstat, buf));
	}
	if (lstat(tmpstat, &bufstat) == -1)
		perror(tmpstat);
	lst = (t_lstdir*)malloc(sizeof(t_lstdir));
	lst->name = ft_strdup(buf);
	if (!(!opt->a && lst->name[0] == '.'))
		opt->total += bufstat.st_blocks;
	lst = ft_add_stats(lst, bufstat, opt);
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
		lst = ft_add_lst(ft_create_lst(buf->d_name, opt), lst);
	closedir(dirp);
	return (lst);
}
