/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtranchi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/01 05:03:01 by jtranchi          #+#    #+#             */
/*   Updated: 2016/02/03 22:11:20 by jtranchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

typedef struct			s_options
{
	int					l;
	int					r;
	int					a;
	int					R;
	int					t;
	char				**files;
	int					nbfile;
}						t_options;

typedef struct			s_lstdir
{
	char 				*name;
	struct s_lstdir		*next;
}						t_lstdir;

void					ft_error(char *str, int error);
void					ft_error_nofile(char *file);
void					ft_ls_l(t_lstdir *lst, t_options *opt);
void					ft_print_rights(struct stat bufstat);
void					ft_print_links_usr_grp(struct stat bufstat);
void					ft_print_size(struct stat bufstat);
void					ft_print_time(char *str);
t_lstdir				*ft_read_dir(char *dir);
t_options				*ft_parse_options(int argc, char **argv, t_options *opt);
t_options				*ft_init_opt(t_options *opt);
