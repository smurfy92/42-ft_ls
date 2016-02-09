/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtranchi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/01 05:03:01 by jtranchi          #+#    #+#             */
/*   Updated: 2016/02/09 18:12:25 by jtranchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/includes/libft.h"
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
	char				*tmp;
	int					nbfile;
	int					actual;
}						t_options;

typedef struct			s_lstdir
{
	char 				*name;
	char				*mdate;
	nlink_t				links;
	mode_t				mode;
	char				*pwname;
	char				*grpname;
	off_t				size;
	char				*mtime;
	int					isdir;
	struct s_lstdir		*next;
}						t_lstdir;

void					ft_error(char *str, int error);
void					ft_error_nofile(char *file);
void					ft_process(char *dir, t_options *opt);
void					ft_error_message(char *str);
void					ft_ls_l(t_lstdir *lst, t_options *opt);
void					ft_print_rights(t_lstdir *lst);
void					ft_print_links_usr_grp(t_lstdir *lst);
void					ft_print_size(t_lstdir *lst);
void					ft_print_time(char *str);
int						ft_compare_date(char *s1, char *s2);
t_lstdir				*ft_add_lst(t_lstdir *tmp, t_lstdir *lst);
t_lstdir				*ft_add_lst_by_date(t_lstdir *tmp, t_lstdir *lst);
t_lstdir				*ft_ls_t(t_lstdir *lst);
t_lstdir				*ft_ls_r(t_lstdir *lst);
t_lstdir				*ft_read_dir(char *dir, t_options *opt);
t_options				*ft_parse_options(int argc, char **argv, t_options *opt);
t_options				*ft_init_opt(t_options *opt);
