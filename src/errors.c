/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtranchi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/01 05:26:56 by jtranchi          #+#    #+#             */
/*   Updated: 2016/02/01 17:06:51 by jtranchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void		ft_error(char *str)
{
	ft_putendl(str);
	exit(0);
}

void		ft_errno(char *file, int errno)
{
	ft_putstr("ls: ");
	ft_putstr(file);
	ft_putendl(errno);
}
