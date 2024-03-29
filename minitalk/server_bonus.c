/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkeklik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 13:17:26 by bkeklik           #+#    #+#             */
/*   Updated: 2022/08/19 13:17:35 by bkeklik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

void	ft_signal_catch(int x, siginfo_t *info, void *unused)
{
	int			sig;
	static int	bit = 7;
	static int	set = 0;

	(void)unused;
	sig = 0;
	if (x == SIGUSR1)
		sig = 1;
	else if (x == SIGUSR2)
		sig = 0;
	set += sig << bit;
	if (bit == 0)
	{
		if (set == 0)
			kill(info->si_pid, SIGUSR1);
		ft_printf("%c", set);
		bit = 7;
		set = 0;
	}
	else
		bit--;
}

int	main(void)
{
	struct sigaction	client;

	client.sa_flags = SA_SIGINFO;
	client.sa_sigaction = ft_signal_catch;
	ft_printf("Server pid=%d\n", getpid());
	sigaction(SIGUSR1, &client, 0);
	sigaction(SIGUSR2, &client, 0);
	while (1)
		pause();
}
