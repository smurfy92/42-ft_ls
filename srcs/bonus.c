/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtranchi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/16 16:25:32 by jtranchi          #+#    #+#             */
/*   Updated: 2016/02/16 16:25:39 by jtranchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

t_lstdir		*ft_ls_t(t_lstdir *lst)
{
	t_lstdir *tmp;
	t_lstdir *tmp2;

	tmp = NULL;
	while (lst)
	{
		tmp2 = ft_ls_t_init(lst);
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

t_lstdir		*ft_add_lst_by_date(t_lstdir *tmp, t_lstdir *lst)
{
	t_lstdir		*tmp2;

	if (!lst)
		return (tmp);
	tmp->next = NULL;
	if (tmp->mdateint - lst->mdateint > 0)
	{
		tmp->next = lst;
		return (tmp);
	}
	tmp2 = lst;
	while (lst->next && (tmp->mdateint - (lst->next)->mdateint) < 0)
		lst = lst->next;
	while (lst->next && (tmp->mdateint - (lst->next)->mdateint) == 0 && (tmp->nano - (lst->next)->nano) <= 0)
		lst = lst->next;
	if (lst->next)
		tmp->next = lst->next;
	lst->next = tmp;
	return (tmp2);
}

void			ft_print_total(int total)
{
	ft_putstr("total ");
	ft_putnbr(total);
	ft_putchar('\n');
}

t_options		*ft_refresh_opt(t_options *opt)
{
	opt->max_lnk = 0;
	opt->max_uid = 0;
	opt->max_gid = 0;
	opt->max_minor = 0;
	opt->max_major = 0;
	return (opt);
}
