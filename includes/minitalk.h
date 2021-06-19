/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taemkim <taemkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 14:06:21 by taemkim           #+#    #+#             */
/*   Updated: 2021/06/19 20:19:23 by taemkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include "libft.h"
# include <signal.h>
# include <errno.h>

# define MAX_CHARS 4096
# define MAX_BITS_PER_CHAR 8
# define INVALID_INPUT -1
# define KILL_ERROR -2
# define TOO_LONG -3
# define NO_FEEDBACK -4

typedef struct	s_data
{
	char			buffer[MAX_CHARS];
	unsigned char	c;
	int				index;
	int				client_pid;
}				t_data;

/*
**	server.c
*/

void			bit_on_handler(int sig, siginfo_t *info, void *ucontext);
void			bit_off_handler(int sig, siginfo_t *info, void *ucontext);
void			null_handler(int i, t_data *data);
void			loop_handler(t_data *data);

/*
**	client.c
*/

int				send_server(unsigned char c, int server_pid);
void			feedback_handler(int sig, siginfo_t *info, void *ucontext);

/*
**	utils.c
*/

void			error_handler(int error);
t_data			*get_data();

#endif
