/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taemkim <taemkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 14:07:28 by taemkim           #+#    #+#             */
/*   Updated: 2021/06/18 16:28:46 by taemkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

t_data	*get_data()
{
	static t_data	data;
	return &data;
}

void	error_handler(int error)
{
	ft_putstr_fd("ERROR!\n", 2);
	if (error == INVALID_INPUT)
		ft_putendl_fd("ERROR: WRONG ARGUMENTS\n\
					USAGE : ./client <pid> <message>\n", 2);
	else if (error == KILL_ERROR)
	{
		ft_putstr_fd("errno code: ", 2);
		ft_putnbr_fd(errno, 2);
		ft_putstr_fd("\n", 2);
	}
	else if (error == TOO_LONG)
		ft_putstr_fd("MESSAGE TOO LONG", 2);
	else if (error == NO_FEEDBACK)
		ft_putstr_fd("NO FEEDBACK", 2);
	else
		ft_putstr_fd("UNKOWN ERROR!!", 2);
	exit(1);
}
