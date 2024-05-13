/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabboud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 14:21:54 by nabil             #+#    #+#             */
/*   Updated: 2024/05/13 15:28:48 by nabboud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "minitalk.h"
#include <signal.h>

static int	g_flag;

void	write_message(char *message, int server_pid, int i)
{
	while (*message)
	{
		g_flag = 0;
		i = -1;
		while (++i < 8)
		{
			if (*message & (1 << i))
				kill(server_pid, SIGUSR1);
			else
				kill(server_pid, SIGUSR2);
			while (g_flag == 0)
				;
		}
		message++;
	}
	i = -1;
	while (++i < 8)
	{
		g_flag = 0;
		kill(server_pid, SIGUSR2);
		while (g_flag == 0)
			;
	}
}

static void	sig_handler(int sig)
{
	if (sig == SIGUSR1)
	{
		g_flag = 1;
		ft_printf("FLAG\n");
	}
}

int	main(int argc, char **argv)
{
	int					server_pid;
	struct sigaction	sa;
	int					i;

	i = 0;
	if (argc != 3)
		return (ft_dprintf(2, "Erreur : Nombre d'argument\n"));
	server_pid = ft_atoi(argv[1]);
	if (server_pid < 1)
		return (ft_dprintf(2, "Erreur : PID invalide\n"));
	sa.sa_handler = &sig_handler;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGUSR1, &sa, NULL) == -1)
	{
		ft_dprintf(2, "Error: PID");
		exit(EXIT_FAILURE);
	}
	write_message(argv[2], server_pid, i);
}
