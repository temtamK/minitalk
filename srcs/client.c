/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taemkim <taemkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 14:07:09 by taemkim           #+#    #+#             */
/*   Updated: 2021/06/19 19:51:41 by taemkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	feedback_handler(int sig, siginfo_t *info, void *ucontext)
{
	(void)sig;
	(void)info;
	(void)ucontext;
	ft_putstr_fd("Success!", 1);
	exit(0);
}

int		send_server(unsigned char c, int server_pid)
{
	unsigned char		bit;

	bit = 0b10000000;
	while (bit)
	{
		if (bit & c)
		{
			if (kill(server_pid, SIGUSR1) == -1)
				return (0);
		}
		else
		{
			if (kill(server_pid, SIGUSR2) == -1)
				return (0);
		}
		bit >>= 1;
		usleep(100);
	}
	return (1);
}

int		main(int ac, char **av)
{
	struct sigaction	feedback;
	char				*str;
	int					server_pid;

	if (ac != 3)
		error_handler(INVALID_INPUT);
	feedback.sa_sigaction = &feedback_handler;
	feedback.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &feedback, NULL);
	str = av[2];
	server_pid = ft_atoi(av[1]);
	while (*str)
	{
		if (!send_server(*str, server_pid))
			error_handler(KILL_ERROR);
		str++;
	}
	system("leaks client");
	if (!send_server(0, server_pid))
		error_handler(KILL_ERROR);
	sleep(5);
	error_handler(NO_FEEDBACK);
}
