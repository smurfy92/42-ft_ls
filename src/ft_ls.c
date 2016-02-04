/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtranchi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/28 17:17:49 by jtranchi          #+#    #+#             */
/*   Updated: 2016/02/03 22:14:55 by jtranchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/ft_ls.h"

void		ft_print_rights(struct stat bufstat)
{

	mode_t val;

	val=(bufstat.st_mode & ~S_IFMT);
	(S_IFDIR & (bufstat.st_mode)) ? ft_putchar('d') : ft_putchar('-');
	(val & S_IRUSR) ? ft_putchar('r') : ft_putchar('-');
	(val & S_IWUSR) ? ft_putchar('w') : ft_putchar('-');
	(val & S_IXUSR) ? ft_putchar('x') : ft_putchar('-');
	(val & S_IRGRP) ? ft_putchar('r') : ft_putchar('-');
	(val & S_IWGRP) ? ft_putchar('w') : ft_putchar('-');
	(val & S_IXGRP) ? ft_putchar('x') : ft_putchar('-');
	(val & S_IROTH) ? ft_putchar('r') : ft_putchar('-');
	(val & S_IWOTH) ? ft_putchar('w') : ft_putchar('-');
	(val & S_IXOTH) ? ft_putchar('x') : ft_putchar('-');
	ft_putchar(' ');
}

void		ft_print_links(struct stat bufstat)
{
	if (bufstat.st_nlink < 100)
		ft_putchar(' ');
	if (bufstat.st_nlink < 10)
		ft_putchar(' ');
	ft_putchar(' ');
	ft_putnbr(bufstat.st_nlink);
}

void	ft_print_user(struct stat bufstat)
{
	struct passwd *user;
	user = getpwuid(bufstat.st_uid);
	ft_putchar(' ');
	ft_putstr(user->pw_name);
	ft_putchar(' ');
}

void	ft_print_group(struct stat bufstat)
{
	struct group *usergroup;

	usergroup = getgrgid(bufstat.st_gid);
	ft_putchar(' ');
	ft_putstr(usergroup->gr_name);
	ft_putchar(' ');
}

void		ft_print_size(struct stat bufstat)
{
	if (bufstat.st_size < 100000)
		ft_putchar(' ');
	if (bufstat.st_size < 10000)
		ft_putchar(' ');
	if (bufstat.st_size < 1000)
		ft_putchar(' ');
	if (bufstat.st_size < 100)
		ft_putchar(' ');
	if (bufstat.st_size < 10)
		ft_putchar(' ');
	ft_putnbr(bufstat.st_size);
	ft_putchar(' ');
}

void		ft_ls_l(t_lstdir *lst)
{
	struct stat 	bufstat;

	if (stat(lst->name, &bufstat) == -1)
	{
		perror("stat");
		ft_putstr("ls -r");
	}
	ft_print_rights(bufstat);
	ft_print_links(bufstat);
	ft_print_user(bufstat);
	ft_print_group(bufstat);
	ft_print_size(bufstat);
	//ft_print_date(gmtime(&bufstat.st_mtime));
	ft_putendl(lst->name);
}

void	ft_ls_r(char *dir)
{
	DIR				*dirp;
	struct dirent	*buf;
	struct stat 	bufstat;
	mode_t 			val;
	char 			*tmp;

	if ((dir[1] && dir[1] !='.') || ft_strlen(dir) > 2)
	{
		ft_putchar('\n');
		ft_putendl(dir);
	}
	dirp = opendir(dir);
	if (!dirp)
		ft_error_nofile(dir);
	while ((buf = readdir(dirp)))
	{
		if (stat(buf->d_name, &bufstat) == -1)
		{
			perror("stat");
			ft_putstr("ls -r");
		}
		else
		{
			val=(bufstat.st_mode & ~S_IFMT);
			if (S_IFDIR & bufstat.st_mode && buf->d_name[0] != '.')
			{
				printf("%s is a directory\n", buf->d_name);
				tmp = ft_strjoin(dir, "/");
				tmp = ft_strjoin(tmp, buf->d_name);
				ft_ls_r(tmp);
			}
		}
	}
	closedir(dirp);
}

void	process(t_lstdir *lst)
{
	while (lst->next)
	{
		ft_ls_l(lst);
		lst = lst->next;
	}
}

void	ft_parse_options(int argc, char **argv)
{
	int i;
	int	files;

	i = 0;
	files = 0;
	while (++i < argc)
	{
		if (argv[i][0] != '-' && files == 0)
		{
			files = 1;
			printf("file %s \n", argv[i]);
		}
		else if (argv[i][0] == '-' && files == 0)
		{
			int j = 0;
			while (argv[i][++j])
			{
				ft_putstr("options : ");
				ft_putchar(argv[i][j]);
				ft_putchar('\n');
			}
		}
		else
			printf("file %s \n", argv[i]);
	}
}

int		main(int argc, char **argv)
{
	t_lstdir *lst;

	if (argc == 1)
	{
		lst = ft_read_dir(".");
		process(lst);
	}
	else
		ft_parse_options(argc, argv);
	return (0);
}
