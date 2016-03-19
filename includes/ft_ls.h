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

#ifndef FT_LS_H
# define FT_LS_H

# include "../libft/includes/libft.h"
# include <dirent.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <errno.h>
# include <unistd.h>
# include <pwd.h>
# include <grp.h>
# include <time.h>
# include <sys/xattr.h>
# include <sys/acl.h>

typedef struct			s_options
{
	int					l;
	int					r;
	int					a;
	int					rec;
	int					t;
	int					o;
	int					p;
	int					g;
	int					bigt;
	int					max_lnk;
	int					max_uid;
	int					max_gid;
	int					max_major;
	int					max_minor;
	time_t				actualtime;
	char				**files;
	char				*tmp;
	int					total;
	int					nbfile;
	int					errors;
	int					actual;
}						t_options;

typedef struct			s_lstdir
{
	char				*name;
	char				*mdate;
	time_t				mdateint;
	long				nano;
	nlink_t				links;
	mode_t				mode;
	char				*pwname;
	char				*grpname;
	int					space_lnk;
	int					space_uid;
	int					space_gid;
	int					space_size;
	int					space_major;
	int					space_minor;
	int					old;
	int					major;
	int					minor;
	char				*mtime;
	int					isdir;
	struct s_lstdir		*next;
}						t_lstdir;

int						ft_check_cols(int tmp);
int						ft_compare_date(char *s1, char *s2);
int						ft_is_dir(char *dir);
void					ft_error_noend(char *str, int error);
void					ft_print_total(int total);
void					ft_illegal_opt(char c);
void					ft_error(char *str, int error);
void					ft_error_nofile(char *file);
void					ft_process(char *dir, t_options *opt);
void					ft_error_message(char *str);
void					ft_ls_l(t_lstdir *lst, t_options *opt);
void					ft_print_rights(t_lstdir *lst, t_options *opt);
void					ft_print_links_usr_grp(t_lstdir *lst, t_options *opt);
void					ft_print_sizes(t_lstdir *lst, t_options *opt);
void					ft_print_time(t_lstdir *lst, t_options *opt);
void					ft_print_acl(t_lstdir *lst, t_options *opt);
t_lstdir				*ft_ls_t_init(t_lstdir *lst);
t_lstdir				*ft_add_stats(t_lstdir *lst,
struct stat bufstat, t_options *opt);
t_lstdir				*ft_add_stats_suite(t_lstdir *lst,
struct stat bufstat, t_options *opt);
t_lstdir				*ft_add_lst(t_lstdir *tmp, t_lstdir *lst);
t_lstdir				*ft_add_lst_by_date(t_lstdir *tmp, t_lstdir *lst);
t_lstdir				*ft_create_lst(char *buf, t_options *opt);
t_lstdir				*ft_ls_t(t_lstdir *lst);
t_lstdir				*ft_ls_r(t_lstdir *lst);
t_lstdir				*ft_read_dir(char *dir, t_options *opt);
t_options				*ft_add_option(char c, t_options *opt);
t_options				*ft_parse(t_options *opt, int i, char **argv);
t_options				*ft_order_reverse(t_options *opt);
t_options				*ft_order_by_date(t_options *opt);
t_options				*ft_refresh_opt(t_options *opt);
t_options				*ft_parse_options(int argc, char **argv,
t_options *opt);
t_options				*ft_init_opt(t_options *opt);

#endif
