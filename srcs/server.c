/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taemkim <taemkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 14:07:15 by taemkim           #+#    #+#             */
/*   Updated: 2021/06/19 20:03:44 by taemkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	null_handler(int i, t_data *data)
{
	ft_putstr_fd(data->buffer, 1);
	ft_putstr_fd("\n", 1);
	ft_bzero(data->buffer, i);
	kill(data->client_pid, SIGUSR1);
	data->client_pid = 0;
}

void	loop_handler(t_data *data)
{
	int		i;

	i = 0;
	while (1)
	{
		pause();
		if (data->index == 8)
		{
			while (data->buffer[i] && i < MAX_CHARS)
				i++;
			if (i == MAX_CHARS)
				error_handler(TOO_LONG);
			if (data->c == 0)
				null_handler(i, data);
			data->buffer[i] = data->c;
			data->c = 0;
			data->index = 0;
			i = 0;
		}
	}
}

void	bit_off_handler(int sig, siginfo_t *info, void *ucontext)
{
	t_data	*data;

	(void)ucontext;
	(void)sig;
	data = get_data();
	data->index++;
	if (!data->client_pid)
		data->client_pid = info->si_pid;
}

void	bit_on_handler(int sig, siginfo_t *info, void *ucontext)
{
	unsigned char	bit;
	t_data			*data;

	(void)ucontext;
	(void)sig;
	bit = 0b10000000;
	data = get_data();
	data->c |= bit >> data->index;
	data->index++;
	if (!data->client_pid)
		data->client_pid = info->si_pid;
}

int		main(void)
{
	struct sigaction	bit_on;
	struct sigaction	bit_off;
	t_data				*data;
	char				*str;

	bit_on.sa_sigaction = &bit_on_handler;
	bit_off.sa_sigaction = &bit_off_handler;
	bit_on.sa_flags = SA_SIGINFO;
	bit_off.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &bit_on, NULL);
	sigaction(SIGUSR2, &bit_off, NULL);
	data = get_data();
	*data = (t_data){0};
	ft_putstr_fd("Server PID: ", 1);
	ft_putstr_fd(str = ft_itoa(getpid()), 1);
	ft_putstr_fd("\n", 1);
	free(str);
	loop_handler(data);
}
